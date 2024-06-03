# Aliases Used in Video

alias gdbSupervisor='gdb --batch --ex run --ex bt --ex q --args' 
// valgrind commands
// As long as you have -g debugging flag when compiling your program with gcc the output of valgrind should tell you WHERE the memory leak(s) occurred
// Make sure to pass these after the `valgrind` alias: ./executable exampleParam1
// The flags are, in short:
//    --leak-check=full: "each individual leak will be shown in detail"
//    --show-leak-kinds=all: Show all of "definite, indirect, possible, reachable" leak kinds in the "full" report.
//    --track-origins=yes: Favor useful output over speed. This tracks the origins of uninitialized values, which could be very useful for memory errors. Consider turning off if Valgrind is unacceptably slow.
//    --verbose: Can tell you about unusual behavior of your program. Repeat for more verbosity.
//    --log-file: Write to a file. Useful when output exceeds terminal space.
alias valgrind='valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose'


# Explanation

All database actions work under these aliases but only the create action works when running the program without a debugger. If you try any other actions without a debugger, a seg. fault occurs when loading rows in Database_load on line 89. In order to get this point, I had to manually enter 100 when mallocing for rows in Database_open on line 137. I'm not sure why malloc wasn't working with conn->db->rows instead on this line.
