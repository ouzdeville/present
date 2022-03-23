#include <stdio.h>
#include <stdlib.h>


#include "param.h"
#include "present.h"

int main()
{
    int i=0;
    init();
     for(i=0; i < PRESENT_CRYPT_SIZE; i++) printf("%d", *(r_key+i));


    return 0;
}
