#ifndef FOUND_H
#define FOUND_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int elem_t;

//#include "../stack/func.cpp"

#define CHECK_ERR(condition, message_error) \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                        }                                 \
                } while(0)

typedef unsigned long long CANARY_TYPE;

typedef struct
{
    CANARY_TYPE LEFT_MASTER;
    elem_t* data;
    int*    next;
    int*    prev;
    int head;
    int tail;
    int size;
    int capacity;
    CANARY_TYPE RIGHT_MASTER;
}QUEUE;

enum errCodes
{
    QUEUE_OK                  = 0,
    QUEUE_NULL                = 1,
    QUEUE_DATA_NULL           = 1 << 1,
    BAD_POINTER               = 1 << 2,
    QUEUE_DELETED             = 1 << 3,
    DAMAGED_RIGHT_CANARY      = 1 << 4,
    DAMAGED_LEFT_CANARY       = 1 << 5,
    DAMAGED_LEFT_DATA_CANARY  = 1 << 6,
    DAMAGED_RIGHT_DATA_CANARY = 1 << 7
};

const int START_CAPACITY  = 15;
const int POISON          = -2281337;
const int FREE_CELL       = -1;

const CANARY_TYPE LEFT_CANARY       = 0xBEADFACE; 
const CANARY_TYPE LEFT_DATA_CANARY  = 0xCAFEBABE; 
const CANARY_TYPE RIGHT_DATA_CANARY = 0xDEADBABE;
const CANARY_TYPE RIGHT_CANARY      = 0xBAADF00D; 

void StartInit(QUEUE* queue);
void CreateList(QUEUE* queue);
int  ListInsert(QUEUE* queue, int* element, int index);
void ListDump(QUEUE* queue, FILE* dumpfile);

#endif
