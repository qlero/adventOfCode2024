#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void openFile(FILE *fp, char *filename, long *offset)
{
    fp = fopen(filename, "r");

    if ( fp == NULL ) {
        printf("Failed to fopen %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    if ( fseek(fp, 0, SEEK_END) == -1 ) {
        printf("Failed to fseek %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    *offset = ftell(fp);
    if ( *offset == -1 ){
        printf("Failed to ftell %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    if ( fseek(fp, 0, SEEK_SET) == -1 ) {
        printf("Failed to fseek %s back to start.\n", filename);
        exit(EXIT_FAILURE);
    }
}

void loadFile(FILE *fp, char *filename, char *content, long offset)
{
    // content = malloc(sizeof(char)*offset);
    if (!content)
    {
        printf("Could not allocate %ld bytes.\n", offset);
        free(content);
        exit(EXIT_FAILURE);
    }

    int count = fread(content, sizeof(char), offset, fp);
    if (count != offset) 
    {
        printf("Failed to load file %s.\n", filename);
        free(content);
        exit(EXIT_FAILURE);
    }
}

void oldLoadFile(FILE *fp, char *filename, char *content, long offset)
{
    // content = malloc(sizeof(char)*offset);
    if (!content)
    {
        printf("Could not allocate %ld bytes.\n", offset);
        free(content);
        exit(EXIT_FAILURE);
    }

    int count = fread(content, sizeof(char), offset, fp);
    if (count != offset) 
    {
        printf("Failed to load file %s.\n", filename);
        free(content);
        exit(EXIT_FAILURE);
    }
}

void cleanup(FILE *fp, char *filename)
{
    if (fclose(fp) != 0)
    {
        printf("failed to fclose %s\n", filename);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}