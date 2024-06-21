#include <stdio.h>
#include <unistd.h>     /* for chdir */
#include <dirent.h>     /* for opendir, readdir, and closedir */
#include <string.h>     /* for strcmp */
#include <stdlib.h>     /* for exit */
#include "syscalls.h"

/* prototypes and dirent structure; references to help in code development 
  int chdir(const char *path);
  DIR *opendir(const char *name);
  struct dirent *readdir(DIR *dirp);
  int closedir(DIR *dirp);
  int strcmp(const char *s1, const char *s2);
  struct dirent {
    ino_t          d_ino;       // Inode number 
    off_t          d_off;       // Not an offset; see below 
    unsigned short d_reclen;    // Length of this record/
    unsigned char  d_type;      // Type of file; not supported by all filesystem types 
    char           d_name[256]; // Null-terminated filename 
  };
*/


typedef struct { // Citation: I needed a way to return multiple values in a function so I adapted code from: https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/
  // I think it is fairgame to use this as we learned typedef and structs in class and Dr.Erle said "you may want to return multiple items in parseArgs"
  char *filetype;
  char *directory;
} Args;

Args parseArgs(int argc, char *argv[]);
int searchDir(char *filetype,char *dirStream);
int printResults(char *filetype, int fileCount);


int subDirCount = 0; // variable to count the sub-directories. I needed it to be outside because I discovered that it was being reset after every recursive searchDir function.

int main(int argc, char *argv[]) {
  Args args = parseArgs(argc,argv); // parsing the user arguments from the command line
  char *filetype = args.filetype; // since parseArgs returns struct Args, i can set filetype and directory so i can pass them later to searchDir and printDir
  char *directory = args.directory;
  int fileCount = searchDir(filetype,directory);
  printResults(filetype,fileCount);
  return 0;
}


Args parseArgs(int argc, char *argv[]) {
  Args args; // declaring the struct that I defined using typedef
  if(argc !=3) { // this will check if the number of arguments which is stored in argc by default is not what I expect (3). it's three because user enters countFiletype -someFileType someDir
    fprintf(stderr, "Please enter the arguments countFileTypes -{a|all|b|c|d|f|l|p|r|s|u} <directory>\n"); // exit if not expected arguments
    exit(99);
  }
  // this if statement will ensure that the whatever the second argument the user input matches to the filetypes Dr.Erle wanted.
  // from man strcmp, it will return a zero value when the strings match 
  if( (strcmp(argv[1], "-a") == 0) || 
      (strcmp(argv[1], "-all") == 0) || 
      (strcmp(argv[1], "-b") == 0) ||
      (strcmp(argv[1], "-c") == 0) ||
      (strcmp(argv[1], "-d") == 0) ||
      (strcmp(argv[1], "-f") == 0) ||
      (strcmp(argv[1], "-l") == 0) ||
      (strcmp(argv[1], "-p") == 0) ||
      (strcmp(argv[1], "-r") == 0) ||
      (strcmp(argv[1], "-s") == 0) ||
      (strcmp(argv[1], "-u") == 0)
      ) {
    
    args.filetype = argv[1]; // now that we confirmed it matches, store it, and store the directory
    args.directory = argv[2]; // I don't need to check anything for the directory as we did that in reciation 4 in the syscalls.c file we check if the directory is valid or not.
  
  }
  else { // if user input doesn't match the -filetype, then exit with error. 
    fprintf(stderr, "Invalid filetype, please select from these types: -{a|all|b|c|d|f|l|p|r|s|u}\n");
    exit(98);
  }
  return args;
}

// Citation: I found the following about what struct dirent can hold as d_types on stackoverflo (scroll all the way down)
//https://stackoverflow.com/questions/23958040/checking-if-a-dir-entry-returned-by-readdir-is-a-directory-link-or-file-dent  
/* 
#define DT_UNKNOWN       0  (u)
#define DT_FIFO          1  (f or p)
#define DT_CHR           2  (c)
#define DT_DIR           4  (d)
#define DT_BLK           6  (b)
#define DT_REG           8  (r)
#define DT_LNK          10  (l)
#define DT_SOCK         12  (s)
*/

int searchDir(char *filetype, char *dirStream) {
  if (strcmp(dirStream, ".") == 0) { // Citation: The next two lines are inspired by ChatGPT, I asked for a function to get the current working directory
  // and how to use it in an arbitrary setting.
  // I did this because I had an issue after I finished the recursive code, I couldn't run it with . or .. anymore
  // I couldn't fix it any other way, so I looked for a function to retrieve the current working directory. 
        dirStream = getcwd(NULL, 0);
    }
  DIR *directory = Opendir(dirStream);
  struct dirent *dirPtrStruct = NULL;
  int fileCount = 0;
  while((dirPtrStruct = Readdir(directory))) { /// while the next dir is not null
    if (strcmp(dirPtrStruct->d_name, ".") && strcmp(dirPtrStruct->d_name, "..") && (dirPtrStruct->d_name[0]!='.')) { /* uncomment the last condition if you want to see hidden files too
    first two string comparisons exclude the directories named . and ..  The third condition checks if the first char of the name is . to exclude hidden files/directories       */
      
      if(dirPtrStruct->d_type == DT_DIR) {
        char recursiveDir[256];
        strcpy(recursiveDir, dirStream); // to avoid looping through the charecters of the, I looked for a function that can copy a string into another: https://www.geeksforgeeks.org/strcpy-in-c/
        // I understand strcpy is not perfect as it can cause overflow if sizes vary a lot, but I think it'll be fine for our case.
        strcat(recursiveDir, "/"); // I referenced the following site for info on string concatination: https://www.geeksforgeeks.org/strcat-in-c/#
        strcat(recursiveDir, dirPtrStruct->d_name);
        subDirCount++;
        // printf("\nthe current recursive dir is: %s and %d\n", recursiveDir,subDirCount); // uncomment this to see all the directories
        fileCount+= searchDir(filetype, recursiveDir);
      } 
      else 
      { // if it's not a directory (or recursive ends)
          if((strcmp(filetype,"-all") == 0) || (strcmp(filetype,"-a")==0)) {
            ++fileCount;
          }
          else if((strcmp(filetype,"-b") == 0)) {
            if(dirPtrStruct->d_type == DT_BLK) ++fileCount;
          }
          else if((strcmp(filetype,"-c") == 0)) {
            if(dirPtrStruct->d_type == DT_CHR) ++fileCount;
          }
          else if((strcmp(filetype,"-d") == 0)) {
            if(dirPtrStruct->d_type == DT_DIR) ++fileCount;
          }
          else if((strcmp(filetype,"-f") == 0) || (strcmp(filetype,"-p") == 0)) {
            if(dirPtrStruct->d_type == DT_FIFO) ++fileCount;
          }
          else if((strcmp(filetype,"-l") == 0)) {
            if(dirPtrStruct->d_type == DT_LNK) ++fileCount;
          }
          else if((strcmp(filetype,"-r") == 0)) {
            if(dirPtrStruct->d_type == DT_REG) ++fileCount;
          }
          else if((strcmp(filetype,"-s") == 0)) {
            if(dirPtrStruct->d_type == DT_SOCK) ++fileCount;
          }
          else if((strcmp(filetype,"-u") == 0)) {
            if(dirPtrStruct->d_type == DT_UNKNOWN) ++fileCount;
          }
    }
    }
  }

  Closedir(directory);
  if((strcmp(filetype,"-d") == 0 )) { // if the user wants to count dir (and subdirectories), we will then count the sub-Directory Counter
    return subDirCount;
  }
  else{
  return fileCount;
  }
}
///////////////////

int printResults(char *filetype, int fileCount) { // this function will print the results  depending on the filetype
    if (strcmp(filetype, "-all") == 0 || strcmp(filetype, "-a") == 0) {
        printf("\nAll: %d\n", fileCount);
    } else if (strcmp(filetype, "-b") == 0) {
        printf("\nBlock Files: %d\n", fileCount);
    } else if (strcmp(filetype, "-c") == 0) {
        printf("\nCharacter Files: %d\n", fileCount);
    } else if (strcmp(filetype, "-d") == 0) {
        printf("\nDirectories: %d\n", fileCount);
    } else if (strcmp(filetype, "-f") == 0 || strcmp(filetype, "-p") == 0) {
        printf("\nFIFO Files: %d\n", fileCount);
    } else if (strcmp(filetype, "-l") == 0) {
        printf("\nSymbolic Link Files: %d\n", fileCount);
    } else if (strcmp(filetype, "-r") == 0) {
        printf("\nRegular Files: %d\n", fileCount);
    } else if (strcmp(filetype, "-s") == 0) {
        printf("\nSocket Files: %d\n", fileCount);
    } else if (strcmp(filetype, "-u") == 0) {
        printf("\nUnknown Files: %d\n", fileCount);
    }
  return 0;
}

