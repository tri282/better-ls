/*
 * src/print.c
 */

#include <stdio.h>
#include <time.h>
#include "../include/print.h"

/*
 * This function takes a FileInfo pointer and prints its metadata to terminal in a verticle manner
 */

void print_vertical(const FileInfo * info) {
  char timebuf[64];
  struct tm * tm_info = localtime(&info->mtime);
  strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);

  printf("File Info:\n");
  printf("  Path      : %s\n", info->path);
  printf("  Type      : %s\n", info->is_dir ? "Directory" : "File");
  printf("  Extension : %s\n", info->extension);
  printf("  Size      : %lld bytes\n", (long long)info->size);
  printf("  Modified  : %s\n", timebuf);
} /* print_verticle */

/*
 * This function takes a FileInfo pointer and prints its metadata to terminal
 * in a horizontal manner (classic ls -al style)
 */

void print_horizontal(const FileInfo * info) {
  if (!info) {
    printf("[NULL]\n");
    return;
  }

  char timebuf[32];
  struct tm * tm_info = localtime(&info->mtime);
  strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", tm_info);

  printf("%-10s %10lld %s %-8s %s\n",
         info->is_dir ? "Directory" : "File",
         (long long)info->size,
         timebuf,
         info->extension,
         info->path
         );
} /* print_horizontal */
