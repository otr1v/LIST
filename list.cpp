#include "listfunc.h"

int main()
{
    QUEUE list = {};
    CreateList(&list);
    int a = 0;
    ListInsert(&list, &a, 2);
    ListInsert(&list, &a, 3);

    FILE* dumpfile = fopen("dumpfile.txt", "w");
    ListDump(&list, dumpfile);
    return 0;
}
