/*
 * include/fileinfo.h
 */

#ifndef FILEINFO_H
#define FILEINFO_H

#include <time.h>
#include <sys/types.h>

typedef struct {
  char * path;
  char * name;
  char * extension;
  off_t size;
  time_t mtime;
  int is_dir;
} FileInfo;

FileInfo *create_fileinfo(const char *filepath);
void destroy_fileinfo(FileInfo *info);

#endif // FILEINFO_H
