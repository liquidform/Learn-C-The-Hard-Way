#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

// When to set pointers to NULL to prevent dangling pointer vulnerabilites: https://stackoverflow.com/a/1025604

// Nested structures are beneficial in scenarios where data has a hierarchical relationship. Examples include representing a university with departments and students, or a company with divisions and employees. They provide a natural way to model complex real-world entities. Nested structures can be used with arrays.
// Nested structures provide a way to represent complex relationships between data elements more intuitively. They enhance code organization and readability by grouping related information within a structured hierarchy.
// You can declare arrays of structures and nest those arrays within other structures to create multidimensional data structures.
// The use for nested structures and getting the address of array elements is code that's easier to read, write, maintain, and perhaps more?

struct Address {
	int id;
	int set;
	char *name;
	char *email;
	int age;
	char sex;
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
		conn = NULL;
	}
}

void die(const char *message, struct Connection *conn)
{
	// if negative or positive number then this evaluates to if(TRUE)
	if(errno)
		perror(message);
	else
		printf("ERROR: %s\n", message);

	Database_close(conn);

	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s %d %c\n", addr->id, addr->name, addr->email, addr->age, addr->sex);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	// On success, fread() and fwrite() return the number of items read or written which is nmemb items of data which is 1 in this case (third param)
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

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	// On error, malloc returns NULL and sets errno. NULL is basically just 0 and !0 is true (0 is false and 1 is true in boolean algebra). You could be explicit and say if(conn == NULL), as well. In some rare systems, NULL will be stored in the computer (represented) as something not 0, but the C standard says you should still be able to write code as if it has a 0 value. This link helps clear things up here and elsewhere in this program: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Null-Pointers.html
	if(!conn)
		die("Memory error", conn);

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db)
		die("Memory error", conn);

	if(mode == 'c')
		conn->file = fopen(filename, "w");
	else
	{
		conn->file = fopen(filename, "r+");

		if(conn->file)
			Database_load(conn);
	}

	// on error, fopen returns NULL and sets errno
	if(!conn->file)
		die("Failed to open the file", conn);

	return conn;
}

void Database_set(struct Connection *conn, size_t id, const char *name, const char *email, int age, char sex, char mode)
{
	struct Address *addr = &conn->db->rows[id];
	if(addr->set)
		die("Already set, delete it first", conn);

	if(mode != 'c' && mode != 'd')
		addr->set = 1;

	char *res = strncpy(addr->name, name, conn->db->max_data);
	// When the string is not terminated correctly then it looks like it is longer but what you are actually seeing is the data that is placed after your buffer in memory. See comment below for more about this topic.
	addr->name[conn->db->max_data - 1] = '\0';
	// if(!0) if the address of dst which is returned from strncpy is NULL aka an integer constant expression with the value 0 or such an expression cast to type void * aka a null pointer aka a pointer that does not point to any object (see following sentences for clarification). In C, the term "null" is often used to refer to a null pointer. A null pointer is a pointer that does not point to any memory location. It is represented by the constant value "NULL" in C, which is typically defined as 0 or (void *)0. Null pointers are commonly used to indicate that a pointer does not currently point to a valid memory location. It's important to handle null pointers properly in C to avoid issues like segmentation faults or undefined behavior when trying to dereference them.
	// strncpy_s is the newer, more secure version according to https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strncpy-s-strncpy-s-l-wcsncpy-s-wcsncpy-s-l-mbsncpy-s-mbsncpy-s-l?view=msvc-170. Documentation for strncpy_s is here and you only need <string.h> just like with strncpy: https://www.typeerror.org/docs/c/string/byte/strncpy . strncpy_s stands for strncpy secure?
	// demonstrate the strncpy bug if you don't terminate the string correctly
	if(!res)
		die("Name copy failed", conn);

	res = strncpy(addr->email, email, conn->db->max_data);
	addr->email[conn->db->max_data - 1] = '\0';
	if(!res)
		die("Email copy failed", conn);

	addr->age = age;
	addr->sex = sex;
}

void Database_write(struct Connection *conn, char mode, size_t id)
{
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	// On success, fread() and fwrite() return the number of items read or written which is nmemb items of data which is 1 in this case (third param). This number equals the number of bytes transferred only when size is 1 (second parma - not the case here). 
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

			Database_set(conn, i, "", "", 0, 'x', 'c'); 

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

				Database_set(conn, i, "", "", 0, 'x', 'd'); 
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

	// Why use `fflush(conn->file)` in Database_write if `fclose(conn->file)` in Database_close is already flushing the stream with fflush? Database_close is called at the bottom of main, outside of the switch(action) statement, so it's called no matter the action selected and the only time Database_write isn't called is if the action chosen is g=get, l=list, f=find, or default (meaning the action isn't defined). Database_open is always called though and so conn->file is always malloc'd and therefore needs to be fclosed. According to the man page of fclose(3): The fclose() function flushes the stream pointed to by stream (writing any buffered output data using fflush(3)) and closes the underlying file descriptor.
	rc = fflush(conn->file);
	// EOF is -1 and EOF is returned on error w/ errno set
	if(rc == -1)
		die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn, size_t max_rows, size_t max_data)
{
	if(max_rows <= 1000000 && max_data <= 50)
	{
		conn->db->max_rows = max_rows;
		conn->db->max_data = max_data;

		conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
		if(!conn->db->rows)
			die("Memory error", conn);

		for(size_t i = 0; i < conn->db->max_rows; i++)
		{
			// make a prototype to initialize it
			struct Address addr = {.id = i,.set = 0 };

			// then just assign it
			conn->db->rows[i] = addr;
		}
	}
	else
	{
		conn->db->max_rows = 1;
		conn->db->max_data = 1;

		conn->db->rows = malloc(sizeof(struct Address));
		if(!conn->db->rows)
			die("Memory error", conn);

		conn->db->rows->name = malloc(conn->db->max_data);
		if(!conn->db->rows->name)
			die("Memory error", conn);

		conn->db->rows->email = malloc(conn->db->max_data);
		if(!conn->db->rows->email)
			die("Memory error", conn);

		die("Database supports up to 1 million records and 50 characters per record.", conn);
	}
}

void Database_get(struct Connection *conn, size_t id)
{
	struct Address *addr = &conn->db->rows[id];

	// if (!0). Remember 0 is the default for all Address structs set field in Database_create and the set field is changed to 1 in Database_set when adding a record to the database
	if(addr->set)
		Address_print(addr);
	else
		die("ID is not set", conn);
}

void Database_delete(struct Connection *conn, size_t id)
{
	if(conn->db->rows[id].name)
	{
		free(conn->db->rows[id].name);
		conn->db->rows[id].name = NULL;
	}

	if(conn->db->rows[id].email)
	{
		free(conn->db->rows[id].email);
		conn->db->rows[id].email = NULL;
	}

	struct Address addr = {.id = id,.set = 0,};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	struct Database *db = conn->db;

	for(size_t i = 0; i < conn->db->max_rows; i++)
	{
		struct Address *cur = &db->rows[i];

		if(cur->set)
		{
			Address_print(cur);
		}
	}
}

void Database_find(struct Connection *conn, char searchBy, const char *expression)
{
	struct Database *db = conn->db;
	size_t matchingLetters = 0;

	for(size_t i = 0; i < conn->db->max_rows; i++)
	{
		struct Address *cur = &db->rows[i];

		if(cur->set)
		{
			size_t i = 0;

			// find by name
			if(searchBy == 'n' || searchBy == 'N')
			{
				while(i < strlen(cur->name))
				{
					if(cur->name[i] == expression[matchingLetters])
					{
						matchingLetters++;

						if(matchingLetters == strlen(expression))
						{
							Address_print(cur);
							i = strlen(cur->name);
						}
					}
					else
						matchingLetters = 0;

					i++;
				}
			}
			// find by email
			else if(searchBy == 'e' || searchBy == 'E')
			{
				while(i < strlen(cur->email))
				{
					if(cur->email[i] == expression[matchingLetters])
					{
						matchingLetters++;

						if(matchingLetters == strlen(expression))
						{
							Address_print(cur);
							i = strlen(cur->email);
						}
					}
					else
						matchingLetters = 0;

					i++;
				}
			}
			// find by age
			else if(searchBy == 'a' || searchBy == 'A')
			{
				if(cur->age == atoi(expression))
					Address_print(cur);
			}
			// find by sex
			else if(searchBy == 's' || searchBy == 'S')
			{
				if(cur->sex == tolower(expression[0]) || cur->sex == toupper(expression[0]))
					Address_print(cur);
			}
			else
				die("Must search by (n)ame, (e)mail, (a)ge, or (s)ex.", conn);
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
	char searchBy;
	const char *expr = NULL;
	size_t id = 0;

	if(action == 'c')
	{
		max_rows = atoi(argv[3]);
		max_data = atoi(argv[4]);
	}
	else if(action == 'f')
	{
		searchBy = argv[3][0];
		expr = argv[4];
	}
	else if (argc > 3)
		id = atoi(argv[3]);

	struct Connection *conn = Database_open(filename, action);

    if (action != 'c' && id >= conn->db->max_rows)
		die("There's not that many records.", conn);

    switch (action) {
        case 'c':
          	Database_create(conn, max_rows, max_data);
            Database_write(conn, action, id);
            break;

        case 'g':
            if (argc != 4)
                die("Need an id to get", conn);

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 8)
                die("Need id, name, email, age, sex to set", conn);

            Database_set(conn, id, argv[4], argv[5], atoi(argv[6]), argv[7][0], 's');
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

		case 'f':
			Database_find(conn, searchBy, expr);
			break;

        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);

    return 0;
}
