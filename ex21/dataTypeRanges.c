// These header files (except float.h) can be found in /usr/include/
#include <stdio.h>
// The stdint.h defines both a set of typdefs for exact sized integer types, as well as a set of macros for the sizes of all the types. This is easier to work with than the older limits.h since it is platform independent. 
#include <stdint.h>
#include <limits.h>
#include <float.h>
// ptrdiff_t (more info near the end of this file)
#include <stddef.h>
// sig_atomic_t (more info near the end of this file)
#include <signal.h>
// wint_t (more info near the end of this file)
#include <wchar.h>

// The size of data types and their range in C depends on the compiler

// some of the format specifiers below come from the table at https://en.wikipedia.org/wiki/C_data_types#Main_types. There are more to view there.

// The [u]int_fastN_t types are usually faster and they also are more portable than the fixed-width [u]intN_t types.

// Summary of summary of stdint.h from wikibooks (https://en.wikibooks.org/wiki/C_Programming/stdint.h):
// stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments. stdint.h (for C or C++), and cstdint (for C++) can be downloaded or quickly created if they are not provided. 
// The exact-width types and their corresponding ranges are only included in that header if they exist for that specific compiler/processor. Note that even on the same processor, two different compiler implementations can differ. The use of #if or #ifdef would allow the inclusion or exclusion of types by the use of compilers preprocessor so that the correct exact-width set is selected for a compiler and its processor target. 
//The related include file <limits.h> provides macros values for the range limits of common integer variable types. In C <limits.h> is already included in <stdint.h>, but in contrast to <stdint.h> which is implementation independent; all maximum and minimum integer values defined in <limits.h> are compiler implementation specific. For example a compiler generating 32 bit executables will define LONG_MIN as −2,147,483,648 [−2^31] however for 64 bit processors targets, LONG_MIN can be −9,223,372,036,854,775,808 [−2^63]. 

// Summary of limits.h from wikibooks (link below):
// limits.h includes definitions of the characteristics of common variable types. The values are implementation specific, but may not be of lower magnitude than certain specified values in a conforming C implementation.
// The C99 standard also specifies the <stdint.h> header file, which provides names and limits for explicitly-sized platform-independent integer datatypes (e.g. int32_t for a 32-bit signed integer).
// More about limits.h, including ranges based on compiler bits: https://en.wikibooks.org/wiki/C_Programming/limits.h

int main()
{   
	printf("stdint.h and limits.h header files can be found in /usr/include/\n\n");

	printf("Macros for sizes of integers in stdint.h (allows more portable code because it provides names and limits for explicitly-sized platform-independent integer datatypes [particularly useful in embedded programming])\n\n");

	// minimum and maximum positive number of type int8_t
    printf("Range of Signed Characters   = %d to %d\n", INT8_MIN, INT8_MAX);
    
	// minimum and maximum positive number of type uint8_t
    printf("Range of Unsigned Characters = 0 to %u\n", UINT8_MAX);

	// similarly for the following in stdint.h, just replace the 8 with the appropriate bits (perhaps up to 128 if your platform currently supports)
    printf("Range of Signed Short Int    = %d to %d\n", INT16_MIN, INT16_MAX);
    
    printf("Range of Unsigned Short Int  = 0 to %u\n", UINT16_MAX);

    printf("Range of Signed Integer      = %d to %d\n", INT32_MIN, INT32_MAX);
    
    printf("Range of Unsigned Integer    = 0 to %u\n", UINT32_MAX);

    printf("Range of Signed Long         = %ld to %ld\n", INT64_MIN, INT64_MAX);
    
    printf("Range of Unsigned Long       = 0 to %lu\n", UINT64_MAX);

    printf("Range of Signed Long Long    = %ld to %ld\n", INTMAX_MIN, INTMAX_MAX);

    printf("Range of Unsigned Long Long  = 0 to %lu\n\n\n", UINTMAX_MAX);


	printf("Macros for sizes of integers in limits.h (not preferred because all maximum and minimum integer values are compiler implementation specific)\n\n");
	
    printf("Range of Signed Characters   = %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    
    printf("Range of Unsigned Characters = 0 to %u\n", UCHAR_MAX);

    printf("Range of Signed Short Int    = %d to %d\n", SHRT_MIN, SHRT_MAX);
    
    printf("Range of Unsigned Short Int  = 0 to %u\n", USHRT_MAX);

    printf("Range of Signed Integer      = %d to %d\n", INT_MIN, INT_MAX);
    
    printf("Range of Unsigned Integer    = 0 to %u\n", UINT_MAX);

    printf("Range of Signed Long         = %ld to %ld\n", LONG_MIN, LONG_MAX);
    
    printf("Range of Unsigned Long       = 0 to %lu\n", ULONG_MAX);

	// in some compilers LONG_LONG_MIN, LONG_LONG_MAX
    printf("Range of Signed Long Long    = %lld to %lld\n", LLONG_MIN, LLONG_MAX);

	// in some compilers ULONG_LONG_MIN, ULONG_LONG_MAX
    printf("Range of Unsigned Long Long  = 0 to %llu\n\n\n", ULLONG_MAX);

	
	printf("Macros for sizes of floating point numbers in floats.h\n\n");
	
   	printf("Range of Float               = %E to %E\n", FLT_MIN, FLT_MAX);

    printf("Range of Double              = %E to %E\n", DBL_MIN, DBL_MAX);

    printf("Range of Long Double         = %LE to %LE\n\n\n", LDBL_MIN, LDBL_MAX);


	printf("Exact-width integer types max size examples (from stdint.h)\n\n");
	
	printf("Signed:\n");
	// 8-bit signed integer and so on
	int8_t int8 = INT8_MAX;
	int16_t int16 = INT16_MAX;
	int32_t int32 = INT32_MAX;
	int64_t int64 = INT64_MAX;
	printf("int8_t example: %d\n", int8);
	printf("int16_t example: %d\n", int16);
	printf("int32_t example: %d\n", int32);
	printf("int64_t example: %ld\n\n", int64);

	printf("Unsigned:\n");
	uint8_t uint8 = UINT8_MAX;
	uint16_t uint16 = UINT16_MAX;
	uint32_t uint32 = UINT32_MAX;
	uint64_t uint64 = UINT64_MAX;
	printf("uint8_t example: %u\n", uint8);
	printf("uint16_t example: %u\n", uint16);
	printf("uint32_t example: %u\n", uint32);
	printf("uint64_t example: %lu\n\n\n", uint64);


	printf("Minimum-width integer types (holds at least (N) bits) max size examples (from stdint.h)\n\n");

	printf("Signed small types:\n");
	int_least8_t int_least8 = INT_LEAST8_MAX;
	int_least16_t int_least16 = INT_LEAST16_MAX;
	int_least32_t int_least32 = INT_LEAST32_MAX;
	int_least64_t int_least64 = INT_LEAST64_MAX;
	printf("int_least8_t example: %d\n", int_least8);
	printf("int_least16_t example: %d\n", int_least16);
	printf("int_least32_t example: %d\n", int_least32);
	printf("int_least64_t example: %ld\n\n", int_least64);

	printf("Unsigned small types:\n");
	uint_least8_t uint_least8 = UINT_LEAST8_MAX;
	uint_least16_t uint_least16 = UINT_LEAST16_MAX;
	uint_least32_t uint_least32 = UINT_LEAST32_MAX;
	uint_least64_t uint_least64 = UINT_LEAST64_MAX;
	printf("uint_least8_t example: %u\n", uint_least8);
	printf("uint_least16_t example: %u\n", uint_least16);
	printf("uint_least32_t example: %u\n", uint_least32);
	printf("uint_least64_t example: %lu\n\n\n", uint_least64);


	// The [u]int_fastN_t types are usually faster and they also are more portable than the fixed-width [u]intN_t types. Per the C Standard (https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf), 7.20.1.1 Exact-width integer types, paragraph 3: "These types are optional" whereas 7.20.1.3 Fastest minimum-width integer types, paragraph 3 states: "The following types are required". This agrees with wikibooks link on stdint.h.
	printf("Fastest minimum-width integer types (similar to int_least(N)_t but asking for the 'fastest' with at least that precision) max size examples (from stdint.h)\n\n");

	printf("Signed fast types:\n");
	int_fast8_t int_fast8 = INT_FAST8_MAX;
	int_fast16_t int_fast16 = INT_FAST16_MAX;
	int_fast32_t int_fast32 = INT_FAST32_MAX;
	int_fast64_t int_fast64 = INT_FAST64_MAX;
	printf("int_fast8_t example: %d\n", int_fast8);
	printf("int_fast16_t example: %ld\n", int_fast16);
	printf("int_fast32_t example: %ld\n", int_fast32);
	printf("int_fast64_t example: %ld\n\n", int_fast64);

	printf("Unsigned fast types:\n");
	uint_fast8_t uint_fast8 = UINT_FAST8_MAX;
	uint_fast16_t uint_fast16 = UINT_FAST16_MAX;
	uint_fast32_t uint_fast32 = UINT_FAST32_MAX;
	uint_fast64_t uint_fast64 = UINT_FAST64_MAX;
	printf("uint_fast8_t example: %u\n", uint_fast8);
	printf("uint_fast16_t example: %lu\n", uint_fast16);
	printf("uint_fast32_t example: %lu\n", uint_fast32);
	printf("uint_fast64_t example: %lu\n\n\n", uint_fast64);


	printf("Integer types wide enough to hold `void *` pointers (from stdint.h)\n\n");

	intptr_t intptr = INTPTR_MAX;
	uintptr_t uintptr = UINTPTR_MAX;
	printf("intptr_t example: %ld\n", intptr);
	printf("uintptr_t example: %lu\n\n\n", uintptr);


	printf("Greatest-width integer types (biggest number possible on this system; from stdint.h)\n\n");

	intmax_t intmax = INTMAX_MAX;
	uintmax_t uintmax = UINTMAX_MAX;
	printf("intmax_t example: %ld\n", intmax);
	printf("uintmax_t example: %lu\n\n\n", uintmax);


	// The C <stddef.h> ptrdiff_t type is an alias of one of the fundamental signed integer type. This is a type able to represent the difference of two pointers.
	// ptrdiff_t is used for pointer arithmetic and array indexing. A pointer difference is only guaranteed to have a valid defined value for pointers to elements of the same array (or for past-the-last element of the same array).
	// Source: https://www.alphacodingskills.com/c/notes/c-stddef-ptrdiff-t.php
	printf("Integer type to represent the difference of two pointers (from stddef.h)\n\n");
	ptrdiff_t ptrdiff = PTRDIFF_MAX;
	printf("ptrdiff_t example: %ld\n", ptrdiff);
	int Arr[10];
	//pointer to the end of the array
	//(past-the-last element of the array)
	int* end = Arr + 10;
	//pointer to the start of the array
	int* start = Arr;
	//size of the array
	ptrdiff_t length = end - start;
	printf("Size of the array: %ld\n\n\n", length);


	// Used to represent the size of objects in bytes and is therefore used as the return type by the sizeof operator. It is guaranteed to be big enough to contain the size of the biggest object the host system can handle. Basically the maximum permissible size is dependent on the compiler; if the compiler is 32 bit then it is simply a typedef(i.e., alias) for unsigned int but if the compiler is 64 bit then it would be a typedef for unsigned long long. The size_t data type is never negative.
	printf("Integer type to represent the size of objects in bytes (from stdio.h, stdlib.h, string.h, stddef.h, etc.)\n\n");

	size_t size = SIZE_MAX;
	printf("size_t example: %lu\n\n\n", size);


	// According to https://www.gnu.org/software/libc/manual/html_node/Atomic-Types.html, the data type sig_atomic_t guarantees reading and writing to happen in a single instruction, so there's no way for a signal handler to run "in the middle" of an access. See beej comment below before reading into this further.
	// According to the first paragraph of chapter 29, the first paragraph (and beyond) of section 29.4, and section 29.5 at https://beej.us/guide/bgc/html/split/signal-handling.html, before we start, I'm just going to advise you to generally ignore this entire chapter and use your OS's (very likely) superior signal handling functions. Unix-likes have the sigaction() family of functions (signal 2 man page says use this instead of signal 2), and Windows has... whatever it does [footnote 171]. Turns out we're pretty limited in what we can and can't do in our signal handlers. This is one of the reasons why I say you shouldn't even bother with this and instead use your OS's signal handling instead (e.g. sigaction() for Unix-like systems). Again, use your OS’s built-in signal handling or the equivalent. It’s not in the spec, not as portable, but probably is far more capable. Plus your OS probably has a number of signals defined that aren’t in the C spec. And it’s difficult to write portable code using signal() anyway.
	// If for some reason you decide to use not use your OS's built-in signal handling or the equivalent, see https://www.gnu.org/software/libc/manual/html_node/Atomic-Data-Access.html and especially Problems with Non-Atomic Access for an easy to understand example of when sig_atomic_t may be helpful.
	printf("Atomic integer data type (used for atomic data access and signal handling. Defined in signal.h). Use your OS's built-in signal handling or the equivalent instead of sig_atomic_t always or almost always.\n\n");

	volatile sig_atomic_t sig_atomic_max = SIG_ATOMIC_MAX;
	printf("sig_atomic_t example: %d\n\n\n", sig_atomic_max);


	printf("wchar_t wide string constant data type (equiv to an array of ints. Defined in stddef.h). They are rarely used; if you're just learning C, may as well skip it according to gnu.org, Wide String Constants.\n\n\n");


	printf("wint_t wide character data type (Defined in wchar.h). An integral type capable of storing any valid value of wchar_t, or WEOF. Because wchar_t is rarely used (explained above) and this is roughly the same I'm skipping this too.\n");

    return 0;
}
