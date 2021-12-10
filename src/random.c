#include "random.h"

//https://wiki.osdev.org/Random_Number_Generator
// The following functions define a portable implementation of rand and srand.

static unsigned long int next = 1;  // NB: "unsigned long int" is assumed to be 32 bits wide
 
int rand(void)  // RAND_MAX assumed to be 32767
{
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65536) % 32768;
}
 
void srand(unsigned char seed)
{
    next = (unsigned long int) seed;
}