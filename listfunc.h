#include "foundation.h"

void StartInit(QUEUE* queue)
{
    queue->head     = 0;
    queue->tail     = 0;
    queue->capacity = START_CAPACITY;
    queue->size     = 0;
    *(CANARY_TYPE *)(queue->data)                         = LEFT_DATA_CANARY;
    //    // printf("st%d", queue->data);
    queue->data = queue->data + sizeof(CANARY_TYPE) / sizeof(elem_t);
    *(CANARY_TYPE *)(queue->data + START_CAPACITY)       = RIGHT_DATA_CANARY;
    queue->RIGHT_MASTER = RIGHT_CANARY;
    queue->LEFT_MASTER  = LEFT_CANARY;

    queue->data[0] = 0;
    queue->next[0] = 0;
    queue->prev[0] = 0;
    for (int i = 1; i < START_CAPACITY; i++)
    {
        queue->data[i] = POISON;
        queue->next[i] = FREE_CELL;
        queue->prev[i] = FREE_CELL;
    }
    queue->prev[1] = 0;
}

void CreateList(QUEUE* queue)
{
    
    queue->data = (elem_t *) calloc(START_CAPACITY * sizeof(elem_t) + 2 * sizeof(CANARY_TYPE) + 0 , sizeof(char));
    CHECK_ERR(queue->data == NULL, "NOT ENOUGH MEMORY");

    queue->next = (int *)    calloc(START_CAPACITY * sizeof(int), sizeof(char));
    CHECK_ERR(queue->next == NULL, "NOT ENOUGH MEMORY");

    queue->prev = (int *)    calloc(START_CAPACITY, sizeof(int));
    CHECK_ERR(queue->prev == NULL, "NOT ENOUGH MEMORY");

    StartInit(queue);
    
}

//==========================================================

int ListInsert(QUEUE* queue, int* element, int index)           //index - before our number
{
    if (queue->size >= queue->capacity)
    {
        //ResizeQueue()

    }
    //linear search
    // queue->data[queue->size] = *element;
    if (queue->size == 0)
    {
        queue->data[1] = *element;
        queue->prev[1] = 0;
        queue->size++;
        queue->head = 1;
        queue->tail = 1;
    }
    else
    {
        int freecell = 0;
        for (int i = 1; i < queue->capacity; i++)
        {
            if (queue->next[i] == FREE_CELL)
            {
                freecell = i + 1;
                //printf("%d", queue->next[i - 1]);
                break;
            }
        }
        if (freecell != 0 )
        {
            if (queue->size + 1 != index)
            {

            }
            queue->data[freecell]     = *element;
            queue->next[freecell - 1] = index;
            queue->next[index - 1]    = freecell;
            queue->prev[index + 1]    = freecell;
            queue->prev[freecell + 1] = index;
        }
        else 
        {
            printf("queue is full");
            return 0;
        }
    }
   
    // queue->size += 1;
    // queue->tail += 1;

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
    fprintf(dumpfile, "digraph structs{\n");
    // fprintf(dumpfile, "0 [shape=box, style = filled, color = blue, peripheries = 8]");
    // fprintf(dumpfile, "%d -> %d\n", queue->data[1], queue->data[2]);
    // fprintf(dumpfile, "0 -> 3338\n1 ->3338}");
    fprintf(dumpfile, "struct1 [shape = record, color = grey, style = filled, label =\"{");
    for (int i = 0; i < queue->capacity; i++)
    {
        fprintf(dumpfile, " %d.|%d}|{", i, queue->data[i]);
    }
    fprintf(dumpfile, "}\"]\n");


    fprintf(dumpfile, "}");
    
}
