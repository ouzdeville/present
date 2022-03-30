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
   register_key = (uint8_t *) calloc( PRESENT_KEY_SIZE, sizeof(uint8_t) );
   round_key = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
}

void keygen(){
    time_t t;
    register_key = (uint8_t *) calloc( PRESENT_KEY_SIZE, sizeof(uint8_t) );
    srand((unsigned) time(&t));
    int i=0;
   for( i = 0 ; i < PRESENT_KEY_SIZE ; i++ ) {
      register_key[i]=(uint8_t)rand();
   }
}

void sub_key(){
   round_key = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
   int i=0;
   for( i = 2 ; i < PRESENT_KEY_SIZE ; i++ ) {
      round_key[i-2]=register_key[i];
   }
}


