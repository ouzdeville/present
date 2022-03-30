#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "param.h"
#include "present.h"

int main()
{
    int i=0;
    init();
    keygen();
    sub_key();
    print_byte(register_key, PRESENT_KEY_SIZE);
    print_byte(round_key, PRESENT_CRYPT_SIZE);

     uint8_t state1[]={0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF2,0xF1};
    memcpy( state, state1, PRESENT_CRYPT_SIZE );
    add_round_key();

    print_byte(state, PRESENT_CRYPT_SIZE);
    return 0;
}
