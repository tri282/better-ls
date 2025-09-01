/*
 * src/dir.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "../include/dir.h"
#include "../include/print.h"
#include "../include/fileinfo.h"

#define MAX_PATH 64

/*
 * This function takes a string path-to-dir and opens it
 * for each entry inside the directory, if it's a file, print the file information
 * else, calls recursively this function
 */

void print_dir(const char * dirpath) {
  DIR * dir = opendir(dirpath);
  if (!dir) {
    perror("opendir\n");
    return;
  }

  struct dirent * ent;
  while ((ent = readdir(dir)) != NULL) {
    if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
      continue;


    char full_path[MAX_PATH];
    snprintf(full_path, sizeof(full_path), "%s/%s", dirpath, ent->d_name);

    FileInfo * info = create_fileinfo(full_path);
    if (!info) {
      fprintf(stderr, "create_fileinfo for dir entry %s\n", dirpath);
      continue;
    }

    if (info->is_dir) {
      print_dir(full_path);
    }
    else {
      print_horizontal(info);
    }

    destroy_fileinfo(info);
  }

  closedir(dir);
} /* print_dir */
