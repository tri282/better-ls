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
#include "../include/globals.h"

#define SUCCESS 0
#define ERROR -1

#define MAX_ENTRIES 5

const char * USAGE =
    "Usage: bls [OPTION]...\n"
    "List directory contents.\n\n"
    "Options:\n"
    "  -a, --all       include hidden files in a directory, overwritten if the entry is a hidden file itself\n"
    "  -h, --help      display this help again and exit\n";

/*
 * This function prints the header for the output of better-ls
 */

void print_output_header() {
    printf("INDEX | PATH                          | EXT   | SIZE     | MODIFIED\n");
    printf("----------------------------------------------------------------------\n");
} /* print_output_header */

int main(int argc, char ** argv) {
  if (argc == 1) {
    printf("%s", USAGE);
    return SUCCESS;
  }

  int numEntries = 0;
  const char * entries[MAX_ENTRIES];

  // argument parsing
  for (int i = 1; i < argc; i++) {

    // print usage
    if ((strcmp(argv[i], "-h") == 0) ||
        (strcmp(argv[i], "--help") == 0)) {
      printf("%s", USAGE);
      return SUCCESS;
    }
    // print hidden file in a directory
    else if ((strcmp(argv[i], "-a") == 0) ||
             (strcmp(argv[i], "--all") == 0)) {
      g_hidden = 1;
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

  // header
  print_output_header();

  // entries parsing
  for (int i = 0; i < numEntries; i++) {
    DIR * dir = opendir(entries[i]);

    // file
    if (dir == NULL) {
      FileInfo * temp = create_fileinfo(entries[i]);
      if (temp) {
        print_vertical(temp);
        destroy_fileinfo(temp);
      }
    }

    // directory
    else {
      print_dir(entries[i]);
      closedir(dir);
    }
  }

  return SUCCESS;
} /* main */
