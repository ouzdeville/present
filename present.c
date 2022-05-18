#include <stdio.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <math.h>
#include "param.h"
#include "present.h"


uint8_t * state;
uint8_t * register_key;
uint8_t *round_key;

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
//    ASSERT(NULL != register_key);
   round_key = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
   int i=0;
   for( i = 2 ; i < PRESENT_KEY_SIZE ; i++ ) {
      round_key[i-2]=register_key[i];
   }
}

void add_round_key(){
 // ASSERT(NULL != state);
  //ASSERT(NULL != round_key);
  int i=0;
  for(i=0; i<PRESENT_CRYPT_SIZE ; i++ ){
    state[i]=state[i]^round_key[i];
  }
}

void print_byte(uint8_t * bytes, int size){
 int i=0;
 printf("\n");
 for(i=size-1; i >= 0; i--)
        printf("%d ", bytes[i]);
 printf("\n");
}

uint8_t two_sbox(uint8_t input){
    uint8_t high=(input>>4) & 0x0F;
    high=sbox[high];
    uint8_t low=(input) & 0x0F;
    low=sbox[low];
    return ((high<<4) | low)& 0xFF;
}

void sBoxLayer(){
    int i=0;
    for(i=0; i<PRESENT_CRYPT_SIZE ; i++ ){
    state[i]=two_sbox(state[i]);
  }
}

