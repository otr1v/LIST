#include "foundation.h"

void StartInit(QUEUE* queue)
{
    queue->head     = 0;
    queue->tail     = 0;
    queue->capacity = START_CAPACITY;
    queue->size     = 0;

    *(CANARY_TYPE *)(queue->data)                         = LEFT_DATA_CANARY;
       // printf("st%d", queue->data);
    queue->data = queue->data + sizeof(CANARY_TYPE) / sizeof(elem_t);
    *(CANARY_TYPE *)(queue->data + START_CAPACITY)       = RIGHT_DATA_CANARY;
    queue->RIGHT_MASTER = RIGHT_CANARY;
    queue->LEFT_MASTER  = LEFT_CANARY;
    memset(queue->data, POISON, queue->capacity);
    memset(queue->next + 1, FREE_CELL, queue->capacity - 1);
}

void CreateList(QUEUE* queue)
{
    
    queue->data = (elem_t *) calloc(START_CAPACITY * sizeof(elem_t) + 2 * sizeof(CANARY_TYPE) + 0 , sizeof(char));
    CHECK_ERR(queue->data = NULL, "NOT ENOUGH MEMORY");

    queue->next = (int *)    calloc(START_CAPACITY, sizeof(elem_t));
    CHECK_ERR(queue->data = NULL, "NOT ENOUGH MEMORY");

    queue->prev = (int *)    calloc(START_CAPACITY, sizeof(elem_t));
    CHECK_ERR(queue->data = NULL, "NOT ENOUGH MEMORY");

    StartInit(queue);
    
}

//==========================================================

int PushElem(QUEUE* queue, int* element)
{
    if (queue->size >= queue->capacity)
    {
        //ResizeQueue()

    }
    //linear search
    // queue->data[queue->size] = *element;
    int freecell = 0;
    for (int i = 1; i < queue->capacity; i++)
    {
        if (queue->next[i] == FREE_CELL)
        {
            freecell = queue->next[i - 1];
            break;
        }
    }
    if (freecell != 0 )
    {
        queue->data[freecell] = *element;
    }
    else 
    {
        printf("queue is full");
        return 0;
    }
    queue->size += 1;
    queue->tail += 1;

    if (queue->tail == queue->capacity)
    {
        queue->tail = 0;
    }
    queue->next[queue->size + 1] = queue->tail + 1;
    
}

//=================================================

void PopElem(QUEUE* queue)
{
    queue->data[queue->head] = POISON;
    queue->head += 1;     //TODO head not +=1, to work with next and prev!!
    queue->next[queue->head] = FREE_CELL;
    // if (queue->head == queue->capacity)
    // {

    // }
}

//=======================================

int Listerror(QUEUE* queue)
{
    int sum_of_errors = 0;
    if (queue == NULL)
    {
        sum_of_errors |= QUEUE_NULL;
    }
    if ((queue->data) == NULL)
    {
        sum_of_errors |= QUEUE_DATA_NULL;
    }
    if ((queue->size) > (queue->capacity))
    {
        sum_of_errors |= BAD_POINTER;
    }
    if ((queue->size) == -1) // TODO queue->size is unsigned!!!
    {
        sum_of_errors |= QUEUE_DELETED;
    }
    if ((queue->RIGHT_MASTER) != RIGHT_CANARY)
    {
        sum_of_errors |= DAMAGED_RIGHT_CANARY;
    }
    if ((queue->LEFT_MASTER) != LEFT_CANARY)
    {
        sum_of_errors |= DAMAGED_LEFT_CANARY;
    }
    if ((*(CANARY_TYPE*)(queue->data - sizeof(CANARY_TYPE) / sizeof(elem_t))) != LEFT_DATA_CANARY)
    {
        sum_of_errors |= DAMAGED_LEFT_DATA_CANARY;
    }
    if ((*(CANARY_TYPE*)(queue->data + queue->capacity)) != RIGHT_DATA_CANARY)
    {
        sum_of_errors |= DAMAGED_RIGHT_DATA_CANARY;
    }
    // TODO compare haches
    return sum_of_errors; 
}

//=============================================

void ListDump(QUEUE* queue, FILE* dumpfile)
{

}
