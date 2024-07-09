#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// NULL is a standard macro defined here
#include <stddef.h>

struct Address {
	int id;
	int set;
	char *name;
	char *email;
};

struct Database {
	size_t max_rows;
	size_t max_data;
	struct Address *rows;
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void Database_close(struct Connection *conn)
{
	if(conn)
	{
		if(conn->file)
			fclose(conn->file);
		for(size_t i = 0; i < conn->db->max_rows; i++)
		{
			if(conn->db->rows[i].name)
				free(conn->db->rows[i].name);

			if(conn->db->rows[i].email)
				free(conn->db->rows[i].email);
		}
		if(conn->db->rows)
			free(conn->db->rows);
		if(conn->db)
			free(conn->db);
		free(conn);
	}
}

void die(const char *message, struct Connection *conn)
{
	if(errno)
		perror(message);
	else
		printf("ERROR: %s\n", message);

	Database_close(conn);

	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1)
		die("Failed to load database.", conn);
	
	conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
	if(!conn->db->rows)
		die("Memory error", conn);

	for(size_t i = 0; i < conn->db->max_rows; i++)
	{
		rc = fread(&conn->db->rows[i], sizeof(struct Address), 1, conn->file);
		if(rc != 1)
			die("Failed to load address struct.", conn);

		conn->db->rows[i].name = malloc(conn->db->max_data);
		if(!conn->db->rows[i].name)
			die("Memory error", conn);

		rc = fread(conn->db->rows[i].name, conn->db->max_data, 1, conn->file);
		if(rc != 1)
			die("Failed to load name.", conn);

		conn->db->rows[i].email = malloc(conn->db->max_data);
		if(!conn->db->rows[i].email)
			die("Memory error", conn);
		
		rc = fread(conn->db->rows[i].email, conn->db->max_data, 1, conn->file);
		if(rc != 1)
			die("Failed to load email.", conn);
	}
}

struct Connection *Database_open(const char *filename, char mode, size_t max_rows, size_t max_data)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn)
		die("Memory error", conn);

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db)
		die("Memory error", conn);

	if(mode == 'c')
	{
		conn->db->max_rows = max_rows;
		conn->db->max_data = max_data;

		conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
		if(!conn->db->rows)
			die("Memory error", conn);

		conn->file = fopen(filename, "w");
	}
	else
	{
		conn->file = fopen(filename, "r+");

		if(conn->file)
			Database_load(conn);
	}

	if(!conn->file)
		die("Failed to open the file", conn);

	return conn;
}

void Database_set(struct Connection *conn, size_t id, const char *name, const char *email, char mode)
{
	struct Address *addr = &conn->db->rows[id];
	if(addr->set)
		die("Already set, delete it first", conn);

	if(mode != 'c' && mode != 'd')
		addr->set = 1;

	char *res = strncpy(addr->name, name, conn->db->max_data);
	addr->name[conn->db->max_data - 1] = '\0';
	// demonstrate the strncpy bug if you don't terminate the string correctly
	if(!res)
		die("Name copy failed", conn);

	res = strncpy(addr->email, email, conn->db->max_data);
	addr->email[conn->db->max_data - 1] = '\0';
	if(!res)
		die("Email copy failed", conn);
}

void Database_write(struct Connection *conn, char mode, size_t id)
{
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1)
		die("Failed to write database.", conn);

	if(mode == 'c')
	{
		for(size_t i = 0; i < conn->db->max_rows; i++)
		{
			rc = fwrite(&conn->db->rows[i], sizeof(struct Address), 1, conn->file);
			if(rc != 1)
				die("Failed to write address struct.", conn);

			conn->db->rows[i].name = malloc(conn->db->max_data);
			if(!conn->db->rows[i].name)
				die("Memory error", conn);

			conn->db->rows[i].email = malloc(conn->db->max_data);
			if(!conn->db->rows[i].email)
				die("Memory error", conn);

			Database_set(conn, i, "", "", 'c'); 

			rc = fwrite((void *) conn->db->rows[i].name, conn->db->max_data, 1, conn->file);
			if(rc != 1)
				die("Failed to write name.", conn);

			rc = fwrite((void *) conn->db->rows[i].email, conn->db->max_data, 1, conn->file);
			if(rc != 1)
				die("Failed to write email.", conn);
		}
	}
	// only malloc and set name and email for affected db entry by id
	else if(mode == 'd')
	{
		for(size_t i = 0; i < conn->db->max_rows; i++)
		{
			rc = fwrite(&conn->db->rows[i], sizeof(struct Address), 1, conn->file);
			if(rc != 1)
				die("Failed to write address struct.", conn);

			if(id == i)
			{
				conn->db->rows[i].name = malloc(conn->db->max_data);
				if(!conn->db->rows[i].name)
					die("Memory error", conn);

				conn->db->rows[i].email = malloc(conn->db->max_data);
				if(!conn->db->rows[i].email)
					die("Memory error", conn);

				Database_set(conn, i, "", "", 'd'); 
			}

			rc = fwrite((void *) conn->db->rows[i].name, conn->db->max_data, 1, conn->file);
			if(rc != 1)
				die("Failed to write name.", conn);

			rc = fwrite((void *) conn->db->rows[i].email, conn->db->max_data, 1, conn->file);
			if(rc != 1)
				die("Failed to write email.", conn);
		}
	}
	// no need to malloc or set
	else
	{
		for(size_t i = 0; i < conn->db->max_rows; i++)
		{
			rc = fwrite(&conn->db->rows[i], sizeof(struct Address), 1, conn->file);
			if(rc != 1)
				die("Failed to write address struct.", conn);

			rc = fwrite((void *) conn->db->rows[i].name, conn->db->max_data, 1, conn->file);
			if(rc != 1)
				die("Failed to write name.", conn);
			
			rc = fwrite((void *) conn->db->rows[i].email, conn->db->max_data, 1, conn->file);
			if(rc != 1)
				die("Failed to write email.", conn);
		}
	}

	if(!conn->file)
		die("Memory error", conn);

	rc = fflush(conn->file);
	if(rc == -1)
		die("Cannot flush database.", conn);
}

// In the video Zed says to have max_data and max_rows be a parameter to the create function. He also gives other useful hints for the other ec such as the find function
void Database_create(struct Connection *conn)
{
	for(size_t i = 0; i < conn->db->max_rows; i++)
	{
		// make a prototype to initialize it
		struct Address addr = {.id = i,.set = 0 };

		// then just assign it
		conn->db->rows[i] = addr;
	}
}

void Database_get(struct Connection *conn, size_t id)
{
	struct Address *addr = &conn->db->rows[id];

	if(addr->set)
		Address_print(addr);
	else
		die("ID is not set", conn);
}

void Database_delete(struct Connection *conn, size_t id)
{
	if(conn->db->rows[id].name)
		free(conn->db->rows[id].name);

	if(conn->db->rows[id].email)
		free(conn->db->rows[id].email);

	struct Address addr = {.id = id,.set = 0,};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	size_t i = 0;
	struct Database *db = conn->db;

	for(i = 0; i < conn->db->max_rows; i++)
	{
		struct Address *cur = &db->rows[i];

		if(cur->set)
		{
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3)
		die("USAGE: ./ex17 <dbfile> <action> [action params]", NULL);

	char *filename = argv[1];
	char action = argv[2][0];
	size_t max_rows;
	size_t max_data;
	size_t id = 0;

	if(action == 'c')
	{
		max_rows = atoi(argv[3]);
		max_data = atoi(argv[4]);
	}
	else if (argc > 3)
		id = atoi(argv[3]);

	struct Connection *conn = Database_open(filename, action, max_rows, max_data);

    if (action != 'c' && id >= conn->db->max_rows)
		die("There's not that many records.", conn);

    switch (action) {
        case 'c':
          	Database_create(conn);
            Database_write(conn, action, id);
            break;

        case 'g':
            if (argc != 4)
                die("Need an id to get", conn);

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6)
                die("Need id, name, email to set", conn);

            Database_set(conn, id, argv[4], argv[5], 's');
            Database_write(conn, action, id);
            break;

        case 'd':
            if (argc != 4)
                die("Need id to delete", conn);

            Database_delete(conn, id);
            Database_write(conn, action, id);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);

    return 0;
}
