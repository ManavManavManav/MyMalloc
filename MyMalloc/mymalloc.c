#include "mymalloc.h"

static char memory[4096];
// the main memoryblock |[1]|[2]|[3]|[4]|[5]|[6]|[7]|[8]|[9]| heap

struct memNode
{
    int closed, size;
    // closed=1 filled up
    // closed=0 open for storing
    struct memNode *prev, *next;

    // int 4*2
    // ptrs 8*2
};
// ll to keep track of allocations
const int mcSize = sizeof(struct memNode);

void *mymalloc(size_t size, char *file, int line)
{
    struct memNode *root = (struct memNode *)memory;

    if (size <= 0 || size > 4096 - 24)
    {
        printf("Error: invalid size(less that 4072 and greater than 0 required)");
        return 0;
    }

    if (root->size == 0)
    {
        root->size = 4096 - mcSize;
        root->next = NULL;
        root->prev = NULL;
        root->closed = 0;
    }

    struct memNode *temp = root;
    struct memNode *temp2;

    do
    {

        if (temp->size < size || temp->closed == 1)
        {
            temp = temp->next;
        }
        else if (temp->size > size && temp->size < size + mcSize)
        {
            temp->closed = 1;
            return (char *)temp + mcSize;
        }
        else
        {

            temp2 = (struct memNode *)((char *)temp + mcSize + size);
            temp2->prev = temp;
            temp2->next = temp->next;
            temp->next = temp2;
            temp2->size = temp->size - (mcSize + size);
            temp2->closed = 0;
            temp->size = size;
            temp->closed = 1;
            return (char *)temp + mcSize;
        }
    } while ((char *)temp < memory + 4096);

    printf("Error:%s - %d Out of memory\n", file, line);
    return 0;
}

void myfree(void *p, char *file, int line)
{

    if (p != NULL)
    {
        if (p < (void *)memory || p > (void *)(memory + 4096))
        {
            printf("Error:%s - %d Address is outside the memory\n", file, line);
            return;
        }
        struct memNode *root = (struct memNode *)memory;

        while (root != NULL)
        {
            if (p == root + 1)
            {
                break;
            }
            root = root->next;
        }

        if (root == NULL)
        {
            printf("Error:%s - %d Address not at the start of the chunk\n", file, line);
            return;
        }

        struct memNode *temp3 = (struct memNode *)(p - mcSize);

        if (temp3->closed == 0)
        {
            printf("Error:%s - %d Memory not allocated\n", file, line);
            return;
        }
        if (temp3->next != NULL && temp3->next->closed == 0)
        {
            temp3->size += temp3->next->size + mcSize;
            struct memNode *temp4 = temp3->next->next;
            if (temp4 != NULL)
            {
                temp4->prev = temp3;
                temp3->next = temp4;
            }
        }
        if (temp3->prev != NULL && temp3->prev->closed == 0)
        {
            temp3->prev->size += temp3->size + mcSize;
            temp3->prev->next = temp3->next;
        }
        temp3->closed = 0;
    }
}