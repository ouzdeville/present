#ifndef PRESENT_H_INCLUDED
#define PRESENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Lookup table for PRESENT substitution process.
 */
static uint8_t const sbox[] = {0x0Cu, 0x05u, 0x06u, 0x0Bu, \
                                 0x09u, 0x00u, 0x0Au, 0x0Du, \
                                 0x03u, 0x0Eu, 0x0Fu, 0x08u, \
                                 0x04u, 0x07u, 0x01u, 0x02u};

/**
 * Lookup table for PRESENT inverse substitution process.
 */
static uint8_t const sbox_inv[] = {0x05u, 0x0Eu, 0x0Fu, 0x08u, \
                                     0x0Cu, 0x01u, 0x02u, 0x0Du, \
                                     0x0Bu, 0x04u, 0x06u, 0x03u, \
                                     0x00u, 0x07u, 0x09u, 0x0Au};

uint8_t * state;
uint8_t * register_key;
uint8_t *round_key;

void init();
void keygen();

void circle_shift(uint8_t *register_key);
void update( uint8_t *register_key, uint32_t round_counter, int mode);
void sub_key();

void add_round_key();

void two_sbox(uint8_t * input,  uint8_t * output);
void simple_sbox(uint8_t * input,  uint8_t * register_key);
void sBoxLayer(uint8_t * state);
void pLayer(uint8_t * state);
void encrypt(uint8_t * msg, uint8_t const * register_key);

void print_byte(uint8_t * bytes, int size);




void decrypt(uint8_t * msg, uint8_t const * register_key);

#endif // PRESENT_H_INCLUDED
