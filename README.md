[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/0bWB5nAr)
# p2-fall2023 - countFileTypes

The user is to run the program as follows, where \<directory\> is a string such as ., .., or /usr/include.  

NOTE: the curly braces means the user is required to enter one and only one option, and the chevrons on either side of the word directory indicate a directory name or path must be entered; the user is NOT to enter any curly braces or chevrons!  

```
  countFileTypes -{a|all|b|c|d|f|l|p|r|s|u} <directory>
```
Options description:
- -a count occurrences of each of the various filetypes (known and unknown)
- -all count occurrences of each of the various filetypes (known and unknown)
- -b count occurrences of block device file type  
- -c count occurrences of character device file type  
- -d count occurrences of directory file type  
- -f count occurrences of named pipe (FIFO) file type  
- -p count occurrences of named pipe (FIFO) file type  
- -l count occurrences of symbolic link file type  
- -s count occurrences of socket file type  
- -u count occurrences of unknown file type  

Important Notes:
- Use Steven's-style wrapping on all your system calls.
- Name your wrapper functions the same as the system call, except capitalize the first letter.
- Follow the format of countFileTypes.c starter code I provided (prototypes at top, function definitions below main). You can rename the functions and/or create additional functions. However, you need to keep your main() function very short by using a modular approach.
- You should not need to edit the makefile; to compile your code, simply type "make".
- Executing "make clean" removes the executable and the intermediate compiled code; you may never need to run this.
- Test your code by creating a directory hierarchy and populating it with empty or nearly empty files of various types.
- Search online to learn how to create various file types on Linux.
- You may find the Linux "find" command useful/interesting, as it can search a directory hierarchy for files of a particular type. The "tree" command is also cool; it displays the directory/file structure in graphical form.
- To run the compile.sh code in your cloned repo (which runs automatically when you push any changes), execute "bash compile.sh".
