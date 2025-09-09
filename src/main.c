/*
 * src/main.c
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include "../include/fileinfo.h"
#include "../include/print.h"
#include "../include/dir.h"

#define SUCCESS 0
#define ERROR -1

// this flag only used for files inside a directory, or a hidden directory
// if the user input is a hidden file itself, this flag will be ignored
// by default, hidden file is skipped
int g_hidden = 0;

#define MAX_ENTRIES 5

const char * USAGE =
  "Usage: bls filename/dirname [options]\n"
  "Options:\n"
  "  -h, --help:  Show this help message\n"
  "  TODO: -s (--sort) [name][size][default:name]\n";

bool check_hidden(const char * fileEntry) {
  if ((strlen(fileEntry) > 1) &&
    (fileEntry[0] == '.') &&
    (fileEntry[1] != '.')) {// for parent dir
    return true;
  }

  return false;
}


int main(int argc, char ** argv) {
  int numEntries = 0;
  const char * entries[MAX_ENTRIES];

  for (int i = 1; i < argc; i++) {

    if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
      printf("%s", USAGE);
      return SUCCESS;
    }
    else {
      if (numEntries < MAX_ENTRIES) {
        entries[numEntries++] = argv[i];
      }
      else {
        fprintf(stderr, "Too many file/directory entries (max %d)\n", MAX_ENTRIES);
        return ERROR;
      }
    }
  }

  for (int i = 0; i < numEntries; i++) {
    // hidden directory
    if ((g_hidden == 1) &&
      (check_hidden(entries[i]) == false)) {
      continue;
    }

    DIR * dir = opendir(entries[i]);

    if (dir == NULL) {
      FileInfo * temp = create_fileinfo(entries[i]);
      if (temp) {
        print_vertical(temp);
        destroy_fileinfo(temp);
      }
    }
    else {
      closedir(dir);
      print_dir(entries[i]);
    }
  }

  return SUCCESS;
}
