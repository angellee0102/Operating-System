#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    int A[] = {1, 2, 3, 4, 5};
    int sum = 0;
    int fid, i;
    int *p = (int *)malloc(2);
    *p = 0;
    fid = fork();

    if (fid > 0)
    {
        for (i = 0; i < 5; i += 2)
        {
            sum = sum + (i) + 1;
        }
        printf("Parent fid: %d\n", fid);
        printf("Parent sum: %d\n", sum);
        printf("Address of malloced mem child = %p and value is %d\n", p, *p);
    }

    // if (fid == 0)
    // {
    //     for (i = 0; i < 5; i += 2)
    //     {
    //         sum = sum + (i);
    //     }
    //     printf("Parent fid: %d\n", fid);
    //     printf("Parent sum: %d\n", sum);
    //     printf("Address of malloced mem child = %p and value is %d\n", p, *p);
    // }

    if (fid == 0)
    {
        for (i = 0; i < 5; i += 2)
        {
            sum = sum + (i);
        }
        printf("Child fid: %d\n", fid);
        printf("Child sum: %d\n", sum);
        printf("Address of malloced mem child = %p "
               "and value is %d\n",
               p, *p);
    }

    return 0;
}
