#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "utils/utils.h"

#define FILENAME "./files/input_day_1.txt"
#define CHUNK 256

int intComparator ( const void * first, const void * second );
int *growArray(int *array, int *mult, int count, int value);
void day_1_part_1(int *leftArray, int *rightArray, int leftCount, int rightCount);
void day_1_part_2(int *leftArray, int *rightArray, int leftCount, int rightCount);

int main() 
{
    // type declarations
    FILE *fp = NULL;
    long offset;
    int placeholder, leftMult = 1, rightMult = 1;
    int *leftArray, *rightArray;
    int size  = sizeof(int) * CHUNK;
    size_t leftCount = 0, rightCount = 0;

    // Opens the file
    fp = fopen(FILENAME, "r");
    checkFile(fp, FILENAME, &offset);
    printf("File %s of size %ld bytes is read.\n", FILENAME, offset);

    // Generates left and right value tables
    leftArray = malloc(size);
    rightArray = malloc(size);
    
    // Loads value into the two tables
    while ( fscanf(fp, "%d", &placeholder) == 1 )
    {
        if ( (leftCount + rightCount) % 2 == 0 ) 
        {
            leftArray = growArray(leftArray, &leftMult, leftCount, placeholder);
            leftCount++;
        }
        else
        {
            rightArray = growArray(rightArray, &rightMult, rightCount, placeholder);
            rightCount++;
        }
    }
    printf("\n");

    day_1_part_1(leftArray, rightArray, leftCount, rightCount);
    day_1_part_2(leftArray, rightArray, leftCount, rightCount);

    // Cleans up before closing
    cleanup(fp, FILENAME);
    free(leftArray);
    free(rightArray);

}

int intComparator (const void * first, const void * second) 
{
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}

int *growArray(int *array, int *mult, int count, int value)
{
    int *temp;
    int oldSize = CHUNK * (*mult);

    // Checks whether to grow the array
    if ( count >= oldSize )
    {
        (*mult) *= 2;
        int newSize = CHUNK * (*mult);

        temp = malloc(sizeof(int) * newSize);

        printf("Allocating a new array of size %d integers at address %p.\n", newSize, temp);
        
        memcpy(temp, array, sizeof(int) * oldSize);
        printf("Copy performed from %p to %p.\n", array, temp);
        
        free(array);
        printf("Old array freed at %p.\n", array);
        
        array = temp;
    }

    // Loads value to array
    array[count] = value;

    return array;
}

void day_1_part_1(int *leftArray, int *rightArray, int leftCount, int rightCount)
{
    int sum_dist = 0;
    
    // sort both arrays
    qsort(leftArray, leftCount, sizeof(int), intComparator);
    qsort(rightArray, rightCount, sizeof(int), intComparator);

    for (int i = 0; i < leftCount; i++)
    {
        sum_dist += abs(leftArray[i] - rightArray[i]);
    }

    // print out the total distance
    printf("[Day 1 Part 1] The total distance is: %d\n", sum_dist);
}

void day_1_part_2(int *leftArray, int *rightArray, int leftCount, int rightCount)
{
    int simscore = 0;
    int count;

    for (int i = 0; i < leftCount; i++)
    {
        count = 0;
        for (int j = 0; j < rightCount; j++)
        {
            if (leftArray[i] == rightArray[j])
            {
                count++;
            }
        }
        simscore += count * leftArray[i];
    }

    // print out the total distance
    printf("[Day 1 Part 2] The similarity score is: %d\n", simscore);
}