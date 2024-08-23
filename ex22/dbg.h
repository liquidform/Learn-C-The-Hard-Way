// This is the definition of a header file. These 2 lines set up a guard (defense against accidentally including the file twice) so we can include the header file as many times as we want but it will only be included once. So next time this gets included, it will be defined and this whole block of code will be skipped. 
#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

// This helps clear up the last para. in ex19, section, "How the CPP Expands Macros". The C preprocessor (cpp) is not a compiler. It is a program that processes the source code before compilation. The preprocessor performs tasks like macro expansions, conditional compilation, and inclusion of header files, preparing the code for the compiler to process.

// Debug Techniques (elaborated around 13:00 of ex20 video but probably not needed):
// 1. You can't debug code by just lookin at it.
// 2. Repeat the bug with an automated test.
// 3. Run the program under a debugger and valgrind and lint.
// 4. Find the backtrace and print out all the variables on the path.
// 5. Once you fix it, add check() to prevent it.

// A breakdown of when Zed uses GDB verses tool like Valgrind verses debug printing:
//    Valgrind to catch all memory errors. I use GDB if Valgrind is having problems or if using Valgrind would slow the program down too much.
//    Print with debug to diagnose and fix defects related to logic or usage. This amounts to about 90% of the defects after you start using Valgrind.
//    GDB for the remaining mysteriously weird stuff or emergency situations to gather information. If Valgrind isn't turning anything up, and I can't even print out the information that I need, then I bust out GDB and start poking around. My use of GDB in this case is entirely to gather information. Once I have an idea of what's going on, I'll go back to writing a unit test to cause the defect, and then do print statements to find out why.
//    Graphical debugger such as DDD (can run many debuggers including gdb) can be useful when you're having trouble with the command line debuggers and when the program you're looking at is local, but they are pointless if you have to debug a program on a server.

// A Debugging Strategy
// This process will actually work with any debugging technique you're using, whether that's Valgrind, debug printing, or using a debugger. I'm going to describe it in terms of using gdb since it seems people skip this process the most when using debuggers. Use this for every bug until you only need it on the very difficult ones.
//    Start a little text file called notes.txt and use it as a kind of lab notes for ideas, bugs, problems, etc.
//    Before you use gdb, write out the bug you're going to fix and what could be causing it.
//    For each cause, write out the files and functions where you think the cause is coming from, or just write that you don't know.
//    Now start gdb and pick the first possible cause with good file and function variables and set breakpoints there. The best way is to see if you can use the set command to either fix the program easily or cause the error immediately.
//    To expand on what Zed is saying above: when using the `set` command it is a good idea to use the `set variable` or `set var` command instead of just set because the set command has many subcommands that can conflict with the names of program variables (ex. `set gnutarget`, abbreviated `set g`, and your program may have a variable called g). To store values into arbitrary places in memory, use the ‘{…}’ construct to generate a value of specified type at a specified address (see Expressions). For example, {int}0x83040 refers to memory location 0x83040 as an integer (which implies a certain size and representation in memory), and `set {int}0x83040 = 4` stores the value 4 into that memory location. These are my highlights from https://sourceware.org/gdb/current/onlinedocs/gdb.html/Assignment.html.
//    If this isn't the cause, then mark in the notes.txt that it wasn't and why. Move on to the next possible cause that's easiest to debug, and keep adding information.
// This is basically the scientific method. You write down a set of hypotheses, then you use debugging to prove or disprove them. This gives you insight into more possible causes and eventually you find it. This process helps you avoid going over the same possible causes repeatedly after you've found that they aren't possible.
// With debug printing, the only difference is you actually write out your hypotheses in the source code instead of the notes.txt. In a way, debug printing forces you to tackle bugs scientifically because you have to write out hypotheses as print statements.

// common idiom for no debugging in this code. You can put `#define NDEBUG` before the includes in your code or in your Makefile too (need to create rules and/or targets I think to make this work: `CFLAGS = -DNDEBUG` or `CPPFLAGS = -DNDEBUG`).
#ifdef NDEBUG
// M is your message
#define debug(M, ...)
#else
// Better than printf. This translates any use of debug("format", ...) into an fprintf call to stderr. Many C programmers don't know, but you can create macros that actually work like printf and take variable arguments. Some C compilers don't support this, but the ones that matter do. ##__VA_ARGS__ says "put whatever they had for extra arguments (...) here." Zed uses the debug macro almost exclusively when debugging code.
#define debug(M, ...) fprintf(stderr, "DEBUG (%s:%d) " M "\n",\
		__FILE__, __LINE__, ##__VA_ARGS__)
#endif

// using ternary operator (if something ? do this : else do this)
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

// logs are for everybody, whereas debugging is only for programmers. That's why there's the option to turn off debugging with `#define NDEBUG` above
#define log_err(M, ...) fprintf(stderr,\
		"[ERROR] (%s:%d errno: %s) " M "\n", __FILE__, __LINE__,\
		clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
        "[WARN] (%s:%d errno: %s) " M "\n",\
        __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)

// A is your assertion. You have to wrap A in parentheses otherwise you can have errors in how it gets interpreted by the C compiler if someone uses their own parentheses or doesn't. The reason we set `errno=0` is if your error label needs to set errno then it should. You don't want to blow errnos up (but some disagree)
#define check(A, M, ...) if(!(A)) {\
	log_err(M, ##__VA_ARGS__); errno=0; goto error; }

// mark a chunk of code in a function that shouldn't run, and if it does, print an error message and jump to the error label. You put this in if-statements and switch-statements to catch conditions that shouldn't happen, like the `default:`.
#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__);\
	errno=0; goto error; }

// check that the RAM is there (makes sure a pointer is valid) after a malloc or something like that
#define check_mem(A, F) check((A), "%s: Out of memory.", F)

// A soft error: you won't see the message unless you have debugging turned on (so if you don't have `#define NDEBUG` in your code). Maybe it's a common error and/or you don't want to log the message in production all the time and just want to clean up. 
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
	errno=0; goto error; }

#endif
