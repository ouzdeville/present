#include <stdio.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <math.h>
#include <string.h>
#include "param.h"
#include "present.h"


uint8_t * state;
uint8_t * register_key;
uint8_t *round_key;

/**
* Ici on fait l'allocation dynamique de la m�moire avec calloc pour mettre les valeur � z�ro
*/
void init()
{
    state = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
    register_key = (uint8_t *) calloc( PRESENT_KEY_SIZE, sizeof(uint8_t) );
    round_key = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );

}

void keygen()
{
    time_t t;
    register_key = (uint8_t *) calloc( PRESENT_KEY_SIZE, sizeof(uint8_t) );
    srand((unsigned) time(&t));
    int i=0;
    for( i = 0 ; i < PRESENT_KEY_SIZE ; i++ )
    {
        register_key[i]=(uint8_t)rand();
    }
}

void sub_key()
{
//    ASSERT(NULL != register_key);
    round_key = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
    int i=0;
    for( i = 2 ; i < PRESENT_KEY_SIZE ; i++ )
    {
        round_key[i-2]=register_key[i];
    }
}

void add_round_key()
{
// ASSERT(NULL != state);
    //ASSERT(NULL != round_key);
    int i=0;
    for(i=0; i<PRESENT_CRYPT_SIZE ; i++ )
    {
        state[i]=state[i]^round_key[i];
    }
}



uint8_t two_sbox(uint8_t input)
{
    uint8_t high=(input>>4) & 0x0F;
    high=sbox[high];
    uint8_t low=(input) & 0x0F;
    low=sbox[low];
    return ((high<<4) | low)& 0xFF;
}

void sBoxLayer()
{
    int i=0;
    for(i=0; i<PRESENT_CRYPT_SIZE ; i++ )
    {
        state[i]=two_sbox(state[i]);
    }
}
void pLayer(op_mode mode)
{
    int i, poz=0;
    uint8_t * int_state;
    uint8_t UN=1u;
    uint8_t bit=0;
    uint8_t offset=(mode==ENCRYPT_MODE)?16:4;
    int_state = (uint8_t *) malloc( PRESENT_CRYPT_SIZE);
    memcpy( int_state, state, PRESENT_CRYPT_SIZE);

    for(i=0; i<PRESENT_CRYPT_BIT_SIZE-1 ; i++ )
    {
        poz=(offset*i) % 63;
        bit=(int_state[i/8]>>(i%8)) & UN;
        if(bit)state[poz/8] |= UN<<(poz%8);
        else state[poz/8] &= (UN<<(poz%8))^0xFF;
    }
}
void right_circle_shift()
{
    if(PRESENT==80)
    {
        //permute les deux premier bloc
        int i=0;
        uint8_t temp1=register_key[0];
        uint8_t temp2=register_key[1];
        for(i=0; i<PRESENT_KEY_SIZE-2 ; i++ )
        {
            register_key[i]=register_key[i+2];
        }
        register_key[PRESENT_KEY_SIZE-1]=temp2;
        register_key[PRESENT_KEY_SIZE-2]=temp1;

        //Permuter les 3 bit restant
        temp1=register_key[0];
        for(i=0; i<PRESENT_KEY_SIZE-1 ; i++ )
        {
            register_key[i]=(register_key[i]>>3)|(register_key[i+1]<< 5);
        }
        register_key[PRESENT_KEY_SIZE-1]=(register_key[PRESENT_KEY_SIZE-1]>>3)|(temp1<< 5);
    }
}


void update(uint8_t round_counter, op_mode mode)
{
    if(PRESENT==80 && mode==ENCRYPT_MODE)
    {
        right_circle_shift();

        uint8_t high=sbox[(register_key[PRESENT_KEY_SIZE-1]>>4) & 0x0F];
        uint8_t low=(register_key[PRESENT_KEY_SIZE-1]) & 0x0F;
        register_key[PRESENT_KEY_SIZE-1]=((high<<4) | low)& 0xFF;


        high=(register_key[2]>>4) & 0x0F;
        low=(register_key[2]& 0x0F);
        low^=round_counter>>1;
        register_key[2]=((high<<4) | low)& 0xFF;

        register_key[1]^=(round_counter& 0x01)<<7;



    }

}

void encrypt(uint8_t * msg, uint8_t const * key)
{
    init();
    memcpy(state, msg, PRESENT_CRYPT_SIZE);
    memcpy(register_key, key, PRESENT_KEY_SIZE);
    uint8_t round;
    round = 1u;

    while (round <= PRESENT_ROUND_COUNT)
    {
        sub_key();
        add_round_key();
        sBoxLayer();
        pLayer(ENCRYPT_MODE);
        update(round,ENCRYPT_MODE);

        round++;
    };
    sub_key();
    add_round_key();


}

state[j] = temp[j];
        }
    }
}

uint8_t gmul(uint8_t a, uint8_t b)
{
    uint8_t p = 0;
    uint8_t counter;
    uint8_t hi_bit_set;
    for (counter = 0; counter < 8; counter++) {
        if (b & 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void inverseMixColumns(uint8_t state[PRESENT_CRYPT_SIZE])
{
    int i, j, k;
    uint8_t temp[PRESENT];

    for (i = 0; i < PRESENT_CRYPT_BIT_SIZE; i++) {
        for (j = 0; j < PRESENT; j++) {
            temp[j] = 0;
            for (k = 0; k < PRESENT_CRYPT_BIT_SIZE; k++) {
                temp[j] ^= gmul(sbox_inv[j][k], state[k * PRESENT_CRYPT_BIT_SIZE + i]);
            }
        }
        for (j = 0; j < PRESENT; j++) {
            state[j * PRESENT_CRYPT_BIT_SIZE + i] = temp[j];
        }
    }
}


void keySchedule(uint8_t *key)
{
uint8_t round_constant = 0x80;
uint8_t temp[8];

for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 8; j++) {
        temp[j] = key[(i*8 + j + 8) % 64];
    }
    temp[0] ^= sbox[temp[7]] ^ round_constant;
    round_constant = (round_constant << 1) ^ ((round_constant & 0x80) ? 0x1B : 0x00);

    for (int j = 0; j < 8; j++) {
        key[(i*8 + j + 8) % 64] = temp[j];
    }
}
}

void decrypt(uint8_t *ciphertext, uint8_t *key) {
    uint8_t i, j, round;
    uint16_t sk[32];

    memcpy(state, ciphertext, PRESENT_CRYPT_SIZE);

    keySchedule(key, sk);

    for (round = 31; round > 0; round--) {
        inverseSubBytes();
        inverseShiftRows();
        if (round > 1) {
            inverseMixColumns();
        }
        addRoundKey(sk[round]);
    }
    inverseSubBytes();
    inverseShiftRows();
    addRoundKey(sk[0]);
}



void print_byte(uint8_t * bytes, int size)
{
    int i=0;
    printf("\n");
    for(i=size-1; i >= 0; i--)
        printf("%d ", bytes[i]);
    printf("\n");
}
void printHex(uint8_t * bytes, int size)
{
    int i;
    for (i=size-1; i >= 0; i--)
    {
        if (i < size-1) printf(":");
        printf("%02X", bytes[i]);
    }
    printf("\n");
}
void toBinary(uint8_t a)
{
    uint8_t i;

    for(i=0x80;i!=0;i>>=1) {
        printf("%c",(a&i)?'1':'0');
        if (i==0x10)
            printf(" ");
    }
}

void printBinary(uint8_t * bytes, int size)
{
    int i;
    for (i=size-1; i >= 0; i--)
    {
        toBinary(bytes[i]);
        printf(" ");
    }
    printf("\n");
}
