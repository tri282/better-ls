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
#include "../include/globals.h"

#define MAX_PATH 64

/*
 * This function returns true if an entry is a hidden file or a hidden directory,
 * returning false otherwise
 */

bool check_hidden(const char * entry) {
  return ((entry[0] == '.') &&
          (strcmp(entry, ".") != 0) && // checks for current dir
          (strcmp(entry, "..") != 0)); // checks for parent dir
} /* check_hidden */

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
    const char * entry_name = ent->d_name;

    if ((!g_hidden) &&
        (check_hidden(entry_name))) {
        continue;
    }

    if (strcmp(entry_name, ".") == 0 || strcmp(entry_name, "..") == 0) {
      continue;
    }

    // build path for current entry inside the directory
    char full_path[MAX_PATH];
    snprintf(full_path, sizeof(full_path), "%s/%s", dirpath, entry_name);

    FileInfo * info = create_fileinfo(full_path);
    if (!info) {
      fprintf(stderr, "error create_fileinfo for dir entry %s\n", dirpath);
      continue;
    }

    // dir
    // calls print_dir recursively
    if (info->is_dir) {
      print_dir_header(info);
      if (info->is_dir && strcmp(entry_name, ".") != 0 && strcmp(entry_name, "..") != 0) {
        print_dir(full_path);
      }
    }
    // file
    else {
      print_horizontal(info);
    }

    destroy_fileinfo(info);
  }

  closedir(dir);
} /* print_dir */
