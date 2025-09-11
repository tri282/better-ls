/*
 * src/print.c
 */

#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "../include/print.h"

static int g_index = 1;

/*
 * This functions takes a FileInfo pointer and if it's a directory
 * print the directory header
 */

void print_dir_header(const FileInfo * info) {
  if (!info) return;

  assert(info->is_dir);
  printf("[%03d] | Directory: %s\n", g_index++, info->path);
}

/*
 * This function takes a FileInfo pointer and prints its metadata to terminal in a verticle manner
 */

void print_vertical(const FileInfo * info) {
  if (!info) return;

  char timebuf[64];
  struct tm * tm_info = localtime(&info->mtime);
  strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);

  printf("File Info:\n");
  printf("  Path      : %s\n", info->path);
  printf("  Extension : %s\n", info->extension);
  printf("  Size      : %lld bytes\n", (long long)info->size);
  printf("  Modified  : %s\n", timebuf);
} /* print_vertical */

/*
 * This function takes a FileInfo pointer and prints its metadata to terminal
 * in a horizontal manner (classic ls -al style)
 */

void print_horizontal(const FileInfo * info) {
  if (!info) return;

  char timebuf[32];
  struct tm * tm_info = localtime(&info->mtime);
  strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", tm_info);

  printf("[%03d] | %-30s | %-5s | %8lld | %s\n",
        g_index++,
        info->path,
        info->extension,
        (long long)info->size,
        timebuf);
} /* print_horizontal */
