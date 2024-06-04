#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// SIZE_MAX is defined here
//#include <stdint.h>

#define MAX_DATA 512
//#define MAX_ROWS 100
//#define MAX_ROWS 8937376004704240

// Nested structures are beneficial in scenarios where data has a hierarchical relationship. Examples include representing a university with departments and students, or a company with divisions and employees. They provide a natural way to model complex real-world entities. Nested structures can be used with arrays.
// Nested structures provide a way to represent complex relationships between data elements more intuitively. They enhance code organization and readability by grouping related information within a structured hierarchy.
// You can declare arrays of structures and nest those arrays within other structures to create multidimensional data structures.
// The use for nested structures and getting the address of array elements is code that's easier to read, write, maintain, and perhaps more?

struct Address {
	int id;
	//size_t id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
	// strdup introduced in ex16 I believe, may be helpful when changing name and email to char *
	//char *name;
	//char *email;
};

struct Database {
	//size_t max_data;
	size_t max_rows;
	struct Address *rows;
	//struct Address **rows;
	//struct Address rows[MAX_ROWS];
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
		// following 2 lines were causing a seg. fault bc flcose accepts a FILE * and nothing else (conn->db is type struct Database *)
//		if(conn->db)
//			fclose(conn->db);
		if(conn->db->rows)
			free(conn->db->rows);
		if(conn->db)
			free(conn->db);
		free(conn);
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
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	// On success, fread() and fwrite() return the number of items read or written which is nmemb items of data which is 1 in this case (third param)
	if(rc != 1)
		die("Failed to load database.", conn);

	printf("Max rows in load function after reading Database struct from stream: %ld\n", conn->db->max_rows);
	printf("Rows in load function after reading Database struct from stream: %zu\n", (void *) conn->db->rows);
	printf("Rows in load function after reading Database struct from stream: %p\n", (void *) conn->db->rows);
	assert(conn->db->max_rows > 0);
	//assert(conn->db->rows == NULL);

	rc = fread(conn->db->rows, sizeof(struct Address) * conn->db->max_rows, 1, conn->file);
	//rc = fread(conn->db->rows, sizeof(struct Address) * 100, 1, conn->file);
	printf("Rows in load function after reading rows from stream: %zu\n", (void *) conn->db->rows);
	printf("Rows in load function after reading rows from stream: %p\n", (void *) conn->db->rows);
	if(rc != 1)
		die("Failed to load rows.", conn);

	printf("Address of file: %zu\n", (void *) conn->file);
	printf("Address of file: %p\n", (void *) conn->file);
	if(!conn->file)
		die("Memory error", conn);
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	// On error, malloc returns NULL and sets errno. NULL is basically just 0 and !0 is true (0 is false and 1 is true in boolean algebra). You could be explicit and say if(conn == NULL), as well. In some rare systems, NULL will be stored in the computer (represented) as something not 0, but the C standard says you should still be able to write code as if it has a 0 value. This link helps clear things up here and elsewhere in this program: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Null-Pointers.html
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
	//	size_t max_data, max_rows;
	//	printf("Enter maximum data: ");
	//	scanf("%llu", &max_data);
	//	printf("Enter maximum rows: ");
	//	scanf("%llu", &max_rows);

	//	printf("Enter maximum data: ");
	//	scanf("%llu", &conn->db->max_data);
	//	printf("Enter maximum rows: ");
	//	scanf("%llu", &conn->db->max_rows);

		//conn->db->max_data = 512;
		//printf("%ld\n", conn->db->max_data);

		// See comment above Database_create; this shouldn't be here at all
		conn->db->max_rows = 100;
		//printf("%ld\n", conn->db->max_rows);
	}

	//printf("Max rows in open after mallocing conn and db: %ld\n", conn->db->max_rows);
	
	//conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
	conn->db->rows = malloc(sizeof(struct Address) * 100);
	printf("Address of rows: %zu\n", (void *) conn->db->rows);
	printf("Address of rows: %p\n", (void *) conn->db->rows);
	if(!conn->db->rows)
		die("Memory error", conn);

//	size_t i = 0;
//
//	for(i = 0; i < conn->db->max_rows; i++)
//	{
//		conn->db->rows[i]->name = malloc(sizeof(char *));
//		if(!conn->db->rows->name)
//			die("Memory error", conn);
//
//		conn->db->rows[i]->email = malloc(sizeof(char *));
//		if(!conn->db->rows->email)
//			die("Memory error", conn);
//
//		//strategy below may not work since *addr will be popped off the stack once the function exits but it might work because I'm assigning it to the address of each Address struct so that may be enough to change the Address struct even after the function exits and *addr is popped from the stack
//		struct Address *addr = &conn->db->rows[i];
//
//		addr->name = malloc(sizeof(char *));
//		if(!addr->name)
//			die("Memory error", conn);
//
//		addr->email = malloc(sizeof(char *));
//		if(!addr->email)
//			die("Memory error", conn);
//	}

	if(mode == 'c')
	{
	//	size_t max_data, max_rows;
	//	printf("Enter maximum data: ");
	//	scanf("%llu", &max_data);
	//	printf("Enter maximum rows: ");
	//	scanf("%llu", &max_rows);

	//	printf("Enter maximum data: ");
	//	scanf("%llu", &conn->db->max_data);
	//	printf("Enter maximum rows: ");
	//	scanf("%llu", &conn->db->max_rows);

//		conn->db->max_data = 512;
//		//printf("%ld\n", conn->db->max_data);
//		conn->db->max_rows = 100;
//		//printf("%ld\n", conn->db->max_rows);

		conn->file = fopen(filename, "w");
	}
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

void Database_write(struct Connection *conn)
//void Database_write(struct Connection *conn, char mode)
{
	rewind(conn->file);

	printf("Max rows in write before writing db to stream: %ld\n", conn->db->max_rows);
	// GET RID OF AFTER WRITING AND LOADING SUCCESSFULLY SO ROWS WONT BE LEAKED (VALGRIND SHOWS THIS)
	//conn->db->rows = 0;
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	// On success, fread() and fwrite() return the number of items read or written which is nmemb items of data which is 1 in this case (third param). This number equals the number of bytes transferred only when size is 1 (second parma - not the case here). 
	if(rc != 1)
		die("Failed to write database.", conn);

//	printf("Max rows in write before writing rows to stream: %ld\n", conn->db->max_rows);
	// GET RID OF AFTER WRITING AND LOADING SUCCESSFULLY SO ROWS WONT BE LEAKED (VALGRIND SHOWS THIS)
//	conn->db->rows = 0;
	printf("Rows in write function before writing rows to stream: %zu\n", (void *) conn->db->rows);
	printf("Rows in write function before writing rows to stream: %p\n", (void *) conn->db->rows);
	rc = fwrite(conn->db->rows, sizeof(struct Address) * conn->db->max_rows, 1, conn->file);
	printf("Rows in write function after writing rows to stream: %zu\n", (void *) conn->db->rows);
	printf("Rows in write function after writing rows to stream: %p\n", (void *) conn->db->rows);
	if(rc != 1)
		die("Failed to write rows.", conn);

	printf("Address of file: %zu\n", (void *) conn->file);
	printf("Address of file: %p\n", (void *) conn->file);
	if(!conn->file)
		die("Memory error", conn);

//	struct Address *addr = &conn->db->rows[2];
//	printf("%ld\n", addr->id);
//	printf("%d\n", addr->set);
	//addr->name = "zed";
	//addr->email = "zed@zedshaw.com";
	//printf("%s\n", addr->name);
	//printf("%s\n", addr->email);

//	size_t i = 0;
//
//	for(i = 0; i < conn->db->max_rows; i++)
//	{
//		struct Address *addr = &conn->db->rows[i];
//
//		rc = fwrite(addr, sizeof(struct Address), 1, conn->file);
//		if(rc != 1)
//			die("Failed to write database.", conn);
//
//		if(mode != 'c')
//		{
//			rc = fwrite(addr->name, conn->db->max_data, 1, conn->file);
//			if(rc != 1)
//				die("Failed to write database.", conn);
//
//			rc = fwrite(addr->email, conn->db->max_data, 1, conn->file);
//			if(rc != 1)
//				die("Failed to write database.", conn);
//		}
//	}

//	rc = fwrite(conn->db->rows->name, max_data, 1, conn->file);
//	if(rc != 1)
//		die("Failed to write database.", conn);
//
//	rc = fwrite(conn->db->rows->email, max_data, 1, conn->file);
//	if(rc != 1)
//		die("Failed to write database.", conn);

	// Why use `fflush(conn->file)` in Database_write if `fclose(conn->file)` in Database_close is already flushing the stream with fflush? Database_close is called at the bottom of main, outside of the switch(action) statement, so it's called no matter the action selected and the only time Database_write isn't called is if the action chosen is g=get, l=list, or default (meaning the action isn't defined). Database_open is always called though and so conn->file is always malloc'd and therefore needs to be fclosed. According to the man page of fclose(3): The fclose() function flushes the stream pointed to by stream (writing any buffered output data using fflush(3)) and closes the underlying file descriptor.
	rc = fflush(conn->file);
	// EOF is -1 and EOF is returned on error w/ errno set
	if(rc == -1)
		die("Cannot flush database.", conn);
}

// In the video Zed says to have max_data and max_rows be a parameter to the create function. He also gives other useful hints for the other ec such as the find function
//void Database_create(struct Connection *conn)
void Database_create(struct Connection *conn, size_t max_rows)
//void Database_create(struct Connection *conn, size_t max_data, size_t max_rows)
{
//	size_t max_data, max_rows;
//	printf("Enter maximum data: ");
//	scanf("%llu", &max_data);
//	printf("Enter maximum rows: ");
//	scanf("%llu", &max_rows);

//	printf("Enter maximum data: ");
//	scanf("%llu", &conn->db->max_data);
//	printf("Enter maximum rows: ");
//	scanf("%llu", &conn->db->max_rows);

	//conn->db->max_data = 512;
	//printf("%ld\n", conn->db->max_data);
//	conn->db->max_rows = max_rows;
	//printf("%ld\n", conn->db->max_rows);

	size_t i = 0;

	for(i = 0; i < conn->db->max_rows; i++)
	{
		// make a prototype to initialize it
		struct Address addr = {.id = i,.set = 0 };
		// then just assign it
		conn->db->rows[i] = addr;
		//printf("%ld\n", conn->db->rows[i].id);
		//printf("%d\n", conn->db->rows[i].set);
	}
}

void Database_set(struct Connection *conn, size_t id, const char *name, const char *email)
{
	printf("Inside Database_set\n");

	struct Address *addr = &conn->db->rows[id];
//	printf("%d\n", conn->db->rows->id);
//	printf("%d\n", conn->db->rows->set);
//	printf("%s\n", conn->db->rows->name);
//	printf("%s\n", conn->db->rows->email);
//	printf("%d\n", addr->id);
//	printf("%d\n", addr->set);
//	printf("%s\n", addr->name);
//	printf("%s\n", addr->email);
	if(addr->set)
		die("Already set, delete it first", conn);

	addr->set = 1;
	//char *res = strncpy(addr->name, name, conn->db->max_data);
	char *res = strncpy(addr->name, name, MAX_DATA);
	// When the string is not terminated correctly then it looks like it is longer but what you are actually seeing is the data that is placed after your buffer in memory. See comment below for more about this topic.
	//addr->name[conn->db->max_data - 1] = '\0';
	addr->name[MAX_DATA - 1] = '\0';
	// if(!0) if the address of dst which is returned from strncpy is NULL aka an integer constant expression with the value 0 or such an expression cast to type void * aka a null pointer aka a pointer that does not point to any object (see following sentences for clarification). In C, the term "null" is often used to refer to a null pointer. A null pointer is a pointer that does not point to any memory location. It is represented by the constant value "NULL" in C, which is typically defined as 0 or (void *)0. Null pointers are commonly used to indicate that a pointer does not currently point to a valid memory location. It's important to handle null pointers properly in C to avoid issues like segmentation faults or undefined behavior when trying to dereference them.
	// strncpy_s is the newer, more secure version according to https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strncpy-s-strncpy-s-l-wcsncpy-s-wcsncpy-s-l-mbsncpy-s-mbsncpy-s-l?view=msvc-170. Documentation for strncpy_s is here and you only need <string.h> just like with strncpy: https://www.typeerror.org/docs/c/string/byte/strncpy . strncpy_s stands for strncpy secure?
	// demonstrate the strncpy bug if you don't terminate the string correctly
	if(!res)
		die("Name copy failed", conn);

	//res = strncpy(addr->email, email, conn->db->max_data);
	res = strncpy(addr->email, email, MAX_DATA);
	addr->email[MAX_DATA - 1] = '\0';
	if(!res)
		die("Email copy failed", conn);
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

//		if(i == conn->db->max_rows - 1)
//		{
//			printf("Address of address struct %ld: %p\n", i, (void *) &db->rows[i]);
//			printf("ID of address struct %ld: %d\n", i, db->rows[i].id);
//			printf("Set status of address struct %ld: %d\n", i, db->rows[i].set);
//		}

//		printf("%ld\n", i);

		//printf("%ld %s %s\n", cur->id, cur->name, cur->email);
//		printf("Before if in for loop of Database_list.\n"); 
		if(cur->set)
		{
//			printf("Inside if in for loop of Database_list.\n"); 
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

	//struct Address *addr = &conn->db->rows[2];
	//addr->id = 2;
	//printf("%ld\n", addr->id);
	//addr->set = 1;
	//printf("%d\n", addr->set);
	//addr->name = "zed";
	//addr->email = "zed@zedshaw.com";
	//printf("%s\n", addr->name);
	//printf("%s\n", addr->email);

    if (argc > 3) id = atoi(argv[3]);
    //if (id >= conn->db->max_rows) die("There's not that many records.", conn);
	// may use this when taking max_rows and max_data from the user in Database_create or Database_open in the if(action == 'c') conditional or on the command line. Originally was thinking these paramaters would be argv[3] and argv[4]
    if (action != 'c' && id >= conn->db->max_rows) die("There's not that many records.", conn);
	
	printf("Before switch.\n"); 

    switch (action) {
        case 'c':
            //Database_create(conn, max_data, max_rows);
			//max_rows = 100;
			max_rows = 0;
          	Database_create(conn, max_rows);
//			Database_create(conn);
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
            //Database_write(conn, action);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list", conn);
    }

	struct Address *addr = &conn->db->rows[2];
	addr = &conn->db->rows[9];
//	printf("%d\n", addr->id);
//	printf("%d\n", addr->set);
	//addr->name = "zed";
	//addr->email = "zed@zedshaw.com";
	//printf("%s\n", addr->name);
	//printf("%s\n", addr->email);

	// output when struct Database contains the following and everything else in header is the same as original program code on ex17 lesson webpage:
	//size_t max_rows;
	//struct Address *rows;
//	printf("%ld\n", sizeof(conn->db)); // 8
//	printf("%ld\n", sizeof(conn->db->rows)); // 8
//	printf("%ld\n", sizeof(conn->db->max_rows)); // 8
//	printf("%ld\n", sizeof(struct Database)); // 16
//	printf("%ld\n", sizeof(struct Database *)); // 8
//	printf("%ld\n", sizeof(struct Address)); // 1032 // 1040 when id is of type size_t in struct Address but output of everything else in the print block remains the same. 512 * 2 for each char array = 1024. Adding this to int set which is 4 = 1028. This perhaps implies that size_t id is 12 but how can that be if it outputs 8 below? One would expect the output to be 1036 instead of 1040.
//	printf("%ld\n", sizeof(struct Address *)); // 8
//	struct Database *base = conn->db;
//	printf("%ld\n", sizeof(base)); // 8
//	printf("%ld\n", sizeof(base->max_rows)); // 8
//	printf("%ld\n", sizeof(int)); // 4
//	printf("%ld\n", sizeof(size_t)); // 8
//	printf("End of size test\n");

    Database_close(conn);

    return 0;
}
