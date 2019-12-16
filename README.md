### GRASP
          grasp [OPTION] ... PATTERN [FILE]...
grasp searches through input files given as an argument for the PATTERN. If grasp finds the pattern in the given file, it prints the file name with the line of text. This program can take two types of option arguments (flags), i.e., -i and -c and if given any random flag, the program will exit with status EXIT_FAILURE.

**-i flag** will ignore the upper and lower case when searching for lies that contain STRING. If the -i option is used, the string "cat", "CAT", "Cat" all are same, if not used, they all are considered different.

**-c flag** will prints the total number of lines processed after the program finishes.

If the program terminates normally after attempting to open and process all of the files listed on the command line, it should terminate with an exit status of EXIT_SUCCESS.


