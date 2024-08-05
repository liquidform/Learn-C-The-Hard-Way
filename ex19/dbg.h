// This is the definition of a header file. These 2 lines set up a guard (defense against accidentally including the file twice) so we can include the header file as many times as we want but it will only be included once. So next time this gets included, it will be defined and this whole block of code will be skipped. 
#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

// This helps clear up the last para. in the section, "How the CPP Expands Macros". The C preprocessor (cpp) is not a compiler. It is a program that processes the source code before compilation. The preprocessor performs tasks like macro expansions, conditional compilation, and inclusion of header files, preparing the code for the compiler to process.

// common idiom for no debugging in this code. You can put `#define NDEBUG` before the includes in your code or in your Makefile too (`CFLAGS = -DNDEBUG` or `CPPFLAGS = -DNDEBUG`).
#ifdef NDEBUG
// M is your message
#define debug(M, ...)
#else
// Better than printf. This translates any use of debug("format", ...) into an fprintf call to stderr. Many C programmers don't know, but you can create macros that actually work like printf and take variable arguments. Some C compilers don't support this, but the ones that matter do. ##__VA_ARGS__ says "put whatever they had for extra arguments (...) here."
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
