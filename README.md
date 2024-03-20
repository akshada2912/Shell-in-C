# Project

Shell in C

# Description
- prompt.c: Is the function that prints the username and shell name as the system prompt, with flags for whether it needs to print the time of a foreground process that ran for >2s and reflects the change in directoy.

- A2.c: divides the input string based on whether it has ; or & and executes the commands, whether foreground or background

- A3.c: provides the functionality of warp, depending on the given input it will redirect to the home directory/ previous directory/ current directory/ absolute path

- A4.c: displays the files and folders of the inputted directory, taking input of flags and calling the required functions based on them

- A4ls.c: provides the functionality of -l flag of peek, printing the sorted file names with the permissions, user id, group id, time of creation and total block size, color coding files/directories/executables in white/blue/green

- A4print.c: provides the functionality of -a flag of peek, printing the sorted file names including hidden files/directories, color coding files/directories/executables in white/blue/green

- A5.c: provides the functionality of pastevents(prints last 15 commands) and pastevents execute x, executing the xth last command, whether erroneous or not

- A6.c: executes a process whether in foreground or background, particulary Linux shell commands and stores background processes to be printed when they finish executing

- A7.c: provides the info of the process inputted/shell process, including process status, group, virtaul memory and executable path, including whether it is a foreground or background process

- A8.c: searches for a given file in the given directory/home directory, printing its relative path, color-coded based on whether it is a file or directory, and implements flags like -d, -e and -f


