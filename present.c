#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "param.h"
#include "present.h"

/**
* Ici on fait l'allocation dynamique de la mémoire avec calloc pour mettre les valeur à zéro
*/
void init(){
   state = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
   r_key = (uint8_t *) calloc( PRESENT_KEY_SIZE, sizeof(uint8_t) );
   round_key = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
}


