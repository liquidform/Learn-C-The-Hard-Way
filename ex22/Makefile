# Macros are defined as = pairs.

# For better descriptions of flags used, see https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
# -Wall tells the compiler, cc, to report all warnings (which, in a sick twist of fate, isn't actually all the warnings possible)
# -Wextra prints more warnings but still not all - see `man gcc` for more about these flags if interested
# -pedantic: In short (first paragraph from link above), "Issue all the warnings demanded by strict ISO C and ISO C++; diagnose all programs that use forbidden extensions, and some other programs that do not follow ISO C and ISO C++. This follows the version of the ISO C or C++ standard specified by any -std option used."
# -g flag to get debugging
# TRY -Werror: Make all warnings into errors.
# had to add these flags to the `all:` lines for them to work
#CFLAGS = -Wall -Wextra -pedantic -g

# The general syntax of a Makefile target rule where target [and target ...] is dependent on [dependent ...] and brackets indicate optional args
# target [target ...] : [dependent ....]
#	  [ command ...]
# In the above code, the arguments in brackets are optional and ellipsis means one or more. Here, note that the tab to preface each command is required.

all:
	# creates a .o (object) file so a linker can access them, such as ld (the gnu linker)
	cc -Wall -Wextra -pedantic -g -c -o ex22.o ex22.c
	#cc -Wall -Wextra -pedantic -g -DNDEBUG -c -o ex22.o ex22.c
	# compile ex22_main together with ex22.o
	cc -Wall -Wextra -pedantic -g ex22_main.c ex22.o -o ex22_main
	#cc -Wall -Wextra -pedantic -g -DNDEBUG ex22_main.c ex22.o -o ex22_main

clean:
	rm -f ex22_main ex22.o
