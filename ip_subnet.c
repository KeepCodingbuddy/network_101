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

    unsigned int ip_addr_integer = 0;

    // convert ip address from A.B.C.D format to equivalent unsigned integer (binary) and store it in ip_addr_integer
    inet_pton(AF_INET, ip_addr, &ip_addr_integer);

    /* 
        htonl() takes a 32-bit long integer number in host byte order and returns a 
        32-bit number in the network byte order used in TCP/IP
    */
    ip_addr_integer = htonl(ip_addr_integer); 

    unsigned int mask_integer_format = get_mask_value_in_integer_format(mask);
    COMPLEMENT(mask_integer_format); // Invert bits eg. From 11111111 11111111 11111111 0000000 -> 00000000 00000000 00000000 11111111

    unsigned int broadcast_addr = ip_addr_integer | mask_integer_format;
    broadcast_addr = htonl(broadcast_addr);  // Convert IP_v4 in host byte order to IP_v4 in network byte order

    /* 
        Convert IP_v4 address in network byte format to IP_v4 in presentation format, 
        by setting the output buffer into a specified length capable of containing it.
    */
    inet_ntop(AF_INET, &broadcast_addr, output_buffer, PREFIX_LEN + 1);

    output_buffer[PREFIX_LEN] = '\0';

}

unsigned int
get_ip_integer_equivalent(char *ip_address) {

    unsigned int ip_addr_integer = 0;

    // Convert ip address from A.B.C.D format to equivalent unsigned integer
    inet_pton(AF_INET, ip_address, &ip_addr_integer);

    return htonl(ip_addr_integer);
}

void
get_abcd_ip_format(unsigned int ip_address, char *output_buffer) {

    // Convert an ip address from Integer to A.B.C.D format
    inet_ntop(AF_INET, &ip_address, output_buffer, PREFIX_LEN + 1);

    output_buffer[PREFIX_LEN] = '\0';
}

void 
get_network_id(char *ip_address, char mask, char *output_buffer) {

    // Get mask in integer format
    unsigned int mask_integer_format = get_mask_value_in_integer_format(mask);

    // To hold ip address in integer form
    unsigned int ip_address_integer = 0;

    // Convert from presentation format to integer format
    inet_pton(AF_INET, ip_address, &ip_address_integer);

    // Use & bitwise operator between IP address and mask to get network id
    unsigned int network_id = ip_address_integer & mask_integer_format;

    // Convert from host byte order to network byte order
    network_id = htonl(network_id);

    // Convert from network format to presentation format
    inet_ntop(AF_INET, &network_id, output_buffer, PREFIX_LEN + 1);
}

unsigned int
get_subnet_cardinality(char mask_value) {

    // possible ip address combination
    return pow(2,MAX_MASK_LEN - mask_value) -2;
}

int main(int argc, char **argv) {

/*
    // Test
    // printf("%x", get_mask_value_in_integer_format(32));

    // Testing get_broadcast_address()

    printf("Testing Question 1 ...\n");

    char ip_address[PREFIX_LEN + 1], output_buffer[PREFIX_LEN + 1];         // Allocate space for input and output

    memset(ip_address, 0, PREFIX_LEN + 1);                                  // Set ip_address to appropriate bytes
    memcpy(ip_address, "192.168.2.10", strlen("192.168.2.10"));             // Copy intended ip address

    ip_address[strlen(ip_address)] = '\0';                                  // Set last index to null

    char mask = 24;                                                         // Set mask value

    memset(output_buffer, 0, PREFIX_LEN + 1);                               // Get output ready to receive bytes format
    get_broadcast_address(ip_address, mask, output_buffer);                 // Function to deduce the Broadcast Address

    printf("Broadcast address = %s\n", output_buffer);                      // Display Broadcast Address
    printf("Testing Question 1 done.\n");                                   // Done.
*/

/*
    // Testing get_ip_integer_equivalent()
    printf("Testing Question 2 ... \n");

    char ip_address[PREFIX_LEN + 1];                                        // Space to hold ip address

    memset(ip_address, 0, PREFIX_LEN + 1);                                  // Set it ready to receive appropriate bytes
    memcpy(ip_address, "192.168.2.10", strlen("192.168.2.10"));             // Copy in intended ip address bytes

    ip_address[strlen(ip_address)] = '\0';                                  // Set last index to null

    unsigned int address = get_ip_integer_equivalent(ip_address);           // Function to deduce the integer equivalent of Broadcast Address

    printf("The address in integer format is = %u\n", address);             // Display it
    printf("Testing Question 2 Done.\n");                                   // Done.

*/

/*
    // Testing get_abcd_ip_format()
    printf("Testing Question 3 ...\n");

    char output_buffer[PREFIX_LEN + 1];                                     // Make buffer to hold address
    memset(output_buffer,0 , PREFIX_LEN + 1);                               // Set it ready for bytes formating

    unsigned int address = 2058138165;                                      // Address to be converted to presentation format
    get_abcd_ip_format(htonl(address), output_buffer);                      // Deduce A.B.C.D presentation format

    printf("Ip address in A.B.C.D format = %s\n", output_buffer);           // Display presentation format of IP address
    printf("Testinf Question 3 Done.\n");                                   // Done.
*/

/*
    // Testing get_network_id()
    printf("Testing Question 4 ...\n");

    char ip_address[PREFIX_LEN + 1], output_buffer[PREFIX_LEN + 1];         // Allocate space to get ip address

    memset(ip_address, 0, PREFIX_LEN + 1);                                  // Get ip_address ready for bytes format
    memcpy(ip_address, "192.168.2.10", strlen("192.168.2.10"));             // Fill in intended ip address

    ip_address[strlen(ip_address)] = '\0';                                  // Set last length to null
    char mask = 20;

    memset(output_buffer, 0, PREFIX_LEN + 1);                               // Set the output_buffer to appropriate length
    get_network_id(ip_address, mask, output_buffer);                        // Get network id

    printf("Network Id = %s / %u\n", output_buffer, mask);                  // Display network id
    printf("Testing Question 4 Done.\n");
*/

    // Testing get_subnet_cardinality()
    printf("Testing Question 5 ...\n");                                     

    char mask = 24;
    printf("Cardinality = %u\n", get_subnet_cardinality(mask));              // Calculate possible combination of ip addresses 

    printf("Testing Question 5 Done.\n");


    return 0;       // Exit program
}