/*
 * src/fileinfo.c
 */
#include "../include/fileinfo.h"
//#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

FileInfo *create_fileinfo(const char * filepath) {
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

    // TODO
    //info->name = extract_name(filepath);
    //info->extension = extract_extension(filepath); // default: none

    return info;
}

void destroy_fileinfo(FileInfo *info) {
    if (!info) return;
    free(info->path);
    free(info->name);
    free(info->extension);
    free(info);
}

