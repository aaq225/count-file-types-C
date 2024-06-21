# This is C code to count the number of various file types in a given directory

The user is to run the program as follows:

1. Run: ``` make ```
2. ```countFileTypes -{a|all|b|c|d|f|l|p|r|s|u} <directory>```

NOTE: the curly braces means the user is required to enter one and only one option, and the chevrons on either side of the word directory indicate a directory name or path must be entered; the user is NOT to enter any curly braces or chevrons!  

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
