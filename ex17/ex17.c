#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512

struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database {
	size_t max_rows;
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

	printf("Max rows in load function after reading Database struct from stream: %ld\n", conn->db->max_rows);
	printf("Rows in load function after reading Database struct from stream: %zu\n", (void *) conn->db->rows);
	printf("Rows in load function after reading Database struct from stream: %p\n", (void *) conn->db->rows);
	assert(conn->db->max_rows > 0);
	
	printf("Address of file after loading db from stream: %zu\n", (void *) conn->file);
	printf("Address of file after loading db from stream: %p\n", (void *) conn->file);
	if(!conn->file)
		die("Memory error", conn);

	rc = fread(conn->db->rows, sizeof(struct Address) * conn->db->max_rows, 1, conn->file);
	printf("Rows in load function after reading rows from stream: %zu\n", (void *) conn->db->rows);
	printf("Rows in load function after reading rows from stream: %p\n", (void *) conn->db->rows);
	if(rc != 1)
		die("Failed to load rows.", conn);
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	printf("Address of conn: %zu\n", (void *) conn);
	printf("Address of conn: %p\n", (void *) conn);
	if(!conn)
		die("Memory error", conn);

	conn->db = malloc(sizeof(struct Database));
	printf("Address of db: %zu\n", (void *) conn->db);
	printf("Address of db: %p\n", (void *) conn->db);
	if(!conn->db)
		die("Memory error", conn);

	if(mode == 'c')
	{
		// See comment above Database_create; this shouldn't be here at all
		conn->db->max_rows = 100;
	}

	conn->db->rows = malloc(sizeof(struct Address) * 100);
	printf("Address of rows: %zu\n", (void *) conn->db->rows);
	printf("Address of rows: %p\n", (void *) conn->db->rows);
	if(!conn->db->rows)
		die("Memory error", conn);

	if(mode == 'c')
	{
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

void Database_write(struct Connection *conn)
{
	rewind(conn->file);

	printf("Max rows in write before writing db to stream: %ld\n", conn->db->max_rows);
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1)
		die("Failed to write database.", conn);

	printf("Rows in write function before writing rows to stream: %zu\n", (void *) conn->db->rows);
	printf("Rows in write function before writing rows to stream: %p\n", (void *) conn->db->rows);
	rc = fwrite(conn->db->rows, sizeof(struct Address) * conn->db->max_rows, 1, conn->file);
	printf("Rows in write function after writing rows to stream: %zu\n", (void *) conn->db->rows);
	printf("Rows in write function after writing rows to stream: %p\n", (void *) conn->db->rows);
	if(rc != 1)
		die("Failed to write rows.", conn);

	printf("Address of file after writing rows to stream: %zu\n", (void *) conn->file);
	printf("Address of file after writing rows to stream: %p\n", (void *) conn->file);
	if(!conn->file)
		die("Memory error", conn);

	rc = fflush(conn->file);
	if(rc == -1)
		die("Cannot flush database.", conn);
}

// In the video Zed says to have max_data and max_rows be a parameter to the create function. He also gives other useful hints for the other ec such as the find function
void Database_create(struct Connection *conn, size_t max_rows)
{
	size_t i = 0;

	for(i = 0; i < conn->db->max_rows; i++)
	{
		// make a prototype to initialize it
		struct Address addr = {.id = i,.set = 0 };
		// then just assign it
		conn->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *conn, size_t id, const char *name, const char *email)
{
	printf("Inside Database_set\n");

	struct Address *addr = &conn->db->rows[id];
	if(addr->set)
		die("Already set, delete it first", conn);

	addr->set = 1;
	char *res = strncpy(addr->name, name, MAX_DATA);
	addr->name[MAX_DATA - 1] = '\0';
	// demonstrate the strncpy bug if you don't terminate the string correctly
	if(!res)
		die("Name copy failed", conn);

	res = strncpy(addr->email, email, MAX_DATA);
	addr->email[MAX_DATA - 1] = '\0';
	if(!res)
		die("Email copy failed", conn);
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
	struct Address addr = {.id = id,.set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	size_t i = 0;
	struct Database *db = conn->db;

	printf("Before for loop in Database_list.\n"); 
	for(i = 0; i < conn->db->max_rows; i++)
	{
		struct Address *cur = &db->rows[i];

		if(cur->set)
		{
			if(i == conn->db->max_rows - 1)
			{
				printf("Address of address struct %ld: %p\n", i, (void *) &cur);
				printf("ID of address struct %ld: %d\n", i, cur->id);
				printf("Set status of address struct %ld: %d\n", i, cur->set);
			}

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
	struct Connection *conn = Database_open(filename, action);
	size_t id = 0;
	size_t max_rows;

    if (argc > 3) id = atoi(argv[3]);
    if (action != 'c' && id >= conn->db->max_rows) die("There's not that many records.", conn);
	
	printf("Before switch.\n"); 

    switch (action) {
        case 'c':
			max_rows = 0;
          	Database_create(conn, max_rows);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4)
                die("Need an id to get", conn);

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6)
                die("Need id, name, email to set", conn);

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4)
                die("Need id to delete", conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list", conn);
    }

	struct Address *addr = &conn->db->rows[2];
	addr = &conn->db->rows[9];

    Database_close(conn);

    return 0;
}
