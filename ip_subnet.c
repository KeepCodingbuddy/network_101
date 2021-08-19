// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <arpa/inet.h>
#include <math.h>

// Macros
#define IS_BIT_SET(value, pos) ( (value & (1 << (pos))) != 0 )
#define TOGGLE_BIT(value, pos) ( value ^= (1 << (pos)) )
#define COMPLEMENT(value) ( value ^= 0xFFFFFFFF )
#define UNSET_BIT(value, pos) ( value &= ( (1 << pos) ^ 0xFFFFFFFF) )
#define SET_BIT(value, pos) ( value |= (1 << pos) )

#define PREFIX_LEN 15       // Max length of IP address in A.B.C.D format
#define MAX_MASK_LEN 32     // Maximum mask value in decimal notation

/*
    For example, if mask = 24 is passed as an argument, function should return
    and unsigned integer equivalent to this below  bit settings
    11111111 11111111 11111111 00000000 
*/

static unsigned int 
get_mask_value_in_integer_format(char mask_value) {

    unsigned int mask = 0xFFFFFFFF;
    char n_trail_bits = MAX_MASK_LEN - mask_value;

    for (int i = 0; i < n_trail_bits; i++) {

        UNSET_BIT(mask, i);

    }
    return mask;
}

void 
get_broadcast_address(char *ip_addr, char mask, char *output_buffer) {

                        
}

int main(int argc, char **argv) {

    // Test
    // printf("%x", get_mask_value_in_integer_format(32));

    return 0;       // Exit program
}