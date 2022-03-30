#include <stdio.h>
#include <stdlib.h>


#include "param.h"
#include "present.h"

int main()
{
    int i=0;
    init();
     for(i=0; i < PRESENT_KEY_SIZE; i++)
        printf("%d", *(register_key+i));


    return 0;
}
