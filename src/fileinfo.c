/*
 * src/fileinfo.c
 */
#include "../include/fileinfo.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DEFAULT_EXT -1

int extract_extension(const char * filepath) {
  const char * dot = strrchr(filepath, '.');

  if ((!dot) || (dot == filepath)) {
    return DEFAULT_EXT;
  }

  return (int)(dot - filepath);
}

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
}

void destroy_fileinfo(FileInfo *info) {
    if (!info) return;
    free(info->path);
    free(info->extension);
    free(info);
}
