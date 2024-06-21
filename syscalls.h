#ifndef SYSCALLS_H
#define SYSCALLS_H
 
/* put all the prototypes of your wrapped system calls in here */
int Chdir(const char *path);
DIR *Opendir(const char *name);
struct dirent *Readdir(DIR *dirp);
int Closedir(DIR *dirp);
#endif
