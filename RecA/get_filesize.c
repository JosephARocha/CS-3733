#include <sys/stat.h>

int get_filesize(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      perror("Failed to get file status");
   else
	  return (int)statbuf.st_size;
      //printf("%s last accessed at %s", path, ctime(&statbuf.st_atime));
}
