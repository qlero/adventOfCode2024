#ifndef UTILS_H
#define UTILS_H

void checkFile(FILE *fp, char *filename, long *offset);
void importFile(FILE *fp, char *filename, char *content, long offset);
void cleanup(FILE *fp, char *filename);

#endif