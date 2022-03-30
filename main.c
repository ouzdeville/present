#include <stdio.h>
#include <stdlib.h>


#include "param.h"
#include "present.h"

int main()
{
    int i=0;
    init();
    keygen();
    sub_key();
     for(i=PRESENT_KEY_SIZE-1; i >= 0; i--)
        printf("%d ", *(register_key+i));
    printf("\n");
    for(i=PRESENT_CRYPT_SIZE-1; i >= 0; i--)
        printf("%d ", *(round_key+i));


    return 0;
}
