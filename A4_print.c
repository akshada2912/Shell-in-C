#include "headers.h"
#include "A4print.h"
void printa(char **array, int arrind, int first, int flaga, int flagl,int flagal,int flagla)
{
    if ((first == 'a' && flaga == 1 && flagl == 1))
    {

        for (int i = 0; i < arrind; i++)
            printf("%s\n", array[i]);
        printf("\n");
        /*l array*/
    }
    else if (flagal == 1)
    {
        
        for (int i = 0; i < arrind; i++)
            printf("%s\n", array[i]);
        printf("\n");

        /*l array*/
    }
    else if ((first == 'l' && flaga == 1 && flagl == 1))
    {
        
         /*l array*/
        printf("\n");
        for (int i = 0; i < arrind; i++)
            printf("%s\n", array[i]);
        printf("\n");
    }
    else if (flagla == 1)
    {
        
        /*l array*/
        printf("\n");
    for (int i = 0; i < arrind; i++)
            printf("%s\n", array[i]);
        printf("\n");
    }
    else if (flaga == 1 && flagl == 0)
    {
        for (int i = 0; i < arrind; i++)
            printf("%s\n", array[i]);
        printf("\n");
    }
    else if (flagl == 1 && flaga == 0)
    {
        /*l array*/
    }
    else if (flaga == 0 && flagl == 0)
    {
        /*l array*/
    }
}