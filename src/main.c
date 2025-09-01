/*
 * src/main.c
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include "../include/fileinfo.h"
#include "../include/print.h"
#include "../include/dir.h"

#define SUCCESS 0
#define ERROR -1

#define MAX_ENTRIES 5

const char * USAGE =
  "Usage: bls filename/dirname [options]\n"
  "Options:\n"
  "  -h, --help:  Show this help message\n"
  "  TODO: -s (--sort) [name][size][default:name]\n";

int main(int argc, char ** argv) {
  int num_entries = 0;
  const char * entries[MAX_ENTRIES];

  for (int i = 1; i < argc; i++) {

    if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
      printf("%s", USAGE);
      return SUCCESS;
    }
    else {
      if (num_entries < MAX_ENTRIES) {
        entries[num_entries++] = argv[i];
      }
      else {
        fprintf(stderr, "Too many file/directory entries (max %d)\n", MAX_ENTRIES);
        return ERROR;
      }
    }
  }

  for (int i = 0; i < num_entries; i++) {
    DIR * dir = opendir(entries[i]);

    if (!dir) {
      FileInfo * temp = create_fileinfo(entries[i]);
      print_vertical(temp);
      destroy_fileinfo(temp);
    }
    else {
      closedir(dir);
      print_dir(entries[i]);
    }
  }

  return SUCCESS;
}
