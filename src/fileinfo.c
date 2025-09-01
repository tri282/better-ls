/*
 * src/fileinfo.c
 */

#include "../include/fileinfo.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DEFAULT_EXT -1

/*
 * This function extracts the extension of a file by finding the last dot '.' in the file name
 * and returns the dot's index in the string. If not extension is found, return DEFAULT_EXT
 */

int extract_extension(const char * filepath) {
  const char * dot = strrchr(filepath, '.');

  if ((!dot) || (dot == filepath)) {
    return DEFAULT_EXT;
  }

  return (int)(dot - filepath);
} /* extract_extension */

/*
 * This function takes a string path-to-file, and allocate its neccessary metadata. It returns
 * a FileInfo object, else returns NULL
 */

FileInfo * create_fileinfo(const char * filepath) {
    struct stat st;
    if (stat(filepath, &st) != 0) {
        return NULL;
    }

    FileInfo * info = malloc(sizeof(FileInfo));
    if (!info) return NULL;

    info->path = strdup(filepath);
    info->size = st.st_size;
    info->mtime = st.st_mtime;
    info->is_dir = S_ISDIR(st.st_mode);

    int dot = extract_extension(filepath);

    if (dot == DEFAULT_EXT) {
      info->extension = strdup("none");
    }
    else {
      info->extension = strdup(filepath + dot + 1);
    }

    return info;
} /* create_fileinfo */

/*
 * This function takes a FileInfo object and deallocate its memory
 */

void destroy_fileinfo(FileInfo *info) {
    if (!info) return;
    free(info->path);
    free(info->extension);
    free(info);
} /* destroy_fileinfo */
