#include "foundation.h"

void CreateList(QUEUE* queue)
{
    queue->head = 0;
    queue->tail = 0;
    queue->size = START_SIZE;
    
    queue->data = (elem_t *) calloc(START_SIZE, sizeof(elem_t));
    CHECK_ERR(queue->data = NULL, "NOT ENOUGH MEMORY");

    queue->next = (int *)    calloc(START_SIZE, sizeof(elem_t));
    CHECK_ERR(queue->data = NULL, "NOT ENOUGH MEMORY");

    queue->prev = (int *)    calloc(START_SIZE, sizeof(elem_t));
    CHECK_ERR(queue->data = NULL, "NOT ENOUGH MEMORY");
}

//==========================================================

void AddElem(QUEUE* queue, int element)
{

}
