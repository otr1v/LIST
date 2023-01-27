#ifndef FOUND_H
#define FOUND_H
#include <stdio.h>
#include "../stack/func.cpp"

#define CHECK_ERR(condition, message_error) \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                        }                                 \
                } while(0)

typedef struct
{
    elem_t* data;
    int*    next;
    int*    prev;
    int head;
    int tail;
    int size;
}QUEUE;

const int START_SIZE = 15;

void CreateList(QUEUE* queue);
void AddElem(QUEUE* queue, int element);
#endif;
