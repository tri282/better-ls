/*
 * include/print.h
 */

#ifndef PRINT_H
#define PRINT_H

#include "../include/fileinfo.h"

void print_dir_header(const FileInfo * info);
void print_vertical(const FileInfo * info);
void print_horizontal(const FileInfo * info);

#endif // PRINT_H

