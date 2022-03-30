#ifndef PRESENT_H_INCLUDED
#define PRESENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t * state;
uint8_t * register_key;
uint8_t *round_key;

void init();
void keygen();

void circle_shift(uint8_t *register_key);
void update( uint8_t *register_key, uint32_t round_counter, int mode);
void sub_key();

void add_round_key(uint8_t * state, uint8_t const * key);

void two_sbox(uint8_t * input,  uint8_t * output);
void simple_sbox(uint8_t * input,  uint8_t * register_key);
void sBoxLayer(uint8_t * state);
void pLayer(uint8_t * state);
void encrypt(uint8_t * msg, uint8_t const * register_key);




void decrypt(uint8_t * msg, uint8_t const * register_key);

#endif // PRESENT_H_INCLUDED
