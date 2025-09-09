/*
 * include/fileinfo.h
 */

#ifndef FILEINFO_H
#define FILEINFO_H

#include <time.h>
#include <sys/types.h>

typedef struct {
  // TODO
  char * path;
  char * extension;
  off_t size;
  time_t mtime;
  int is_dir;
} FileInfo;

FileInfo * create_fileinfo(const char * file_path);
void destroy_fileinfo(FileInfo * info);

#endif // FILEINFO_H
