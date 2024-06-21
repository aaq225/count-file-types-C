#include <stdio.h>       /* for fprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* for errno */
#include <string.h>      /* for strerror */
#include <unistd.h>      /* for chdir */
#include <sys/types.h>   /* for opendir and closedir*/
#include <dirent.h>      /* for opendir, readdir, and closedir*/

  /*
  int chdir(const char *path);
  DIR *opendir(const char *name);
  struct dirent *readdir(DIR *dirp);
  int closedir(DIR *dirp);
  */

int Chdir(const char *path) {  //On  success,  zero  is  returned.   On  error,  -1 is returned, and errno is set appropriately.        
                                                                      /* error checking/handling wrapper around chdir system call */
  if (chdir(path)) {                                                  /* if chdir system calls returns nonzero value, we have an error */
     fprintf(stderr, "chdir error (%s)- %s\n", path, strerror(errno));  /* use errno global variable to retrieve error message */
     exit(errno);                                                     /* exit with the errno global variable value */
  }
  else{
    //  fprintf(stdout,"direcotry was successfully changed to: %s\n", path);  
  }
  return 0;                                                           /* if no error, return 0 (which is what chdir returned) */
}

DIR *Opendir(const char *name) { // The opendir() function will return a pointer to the directory stream.  On error, NULL is returned, and errno is set appropriately.
  DIR *dirPtr = opendir(name);
  if(dirPtr == NULL){
      fprintf(stderr, "opendir error (%s)- %s\n", name, strerror(errno));
      exit(errno);
  }
  return dirPtr;
}

/*To distinguish end of
  stream from an error, set errno to zero before calling readdir()
  and then check the value of errno if NULL is returned.*/

struct dirent *Readdir(DIR *dirp) { // On success, readdir() returns a pointer to a dirent structure.   
  errno = 0;
  struct dirent* dirPtr = readdir(dirp);
  if(dirPtr== NULL && errno != 0) {
      fprintf(stderr, "readdir error - %s\n", strerror(errno));
      exit(errno);
  }
  return dirPtr;
}

int Closedir(DIR *dirp){ // The closedir() function returns 0 on success.  On error, -1 is returned, and errno is set appropriately.
  if(closedir(dirp) == -1){
      fprintf(stderr, "closedir error - %s\n", strerror(errno));
      exit(errno);
  }
  return 0;
}




