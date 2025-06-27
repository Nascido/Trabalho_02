#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "utils.h"

// Implementação das funções auxiliares

int is_power_of_two(size_t x) {
    return x != 0 && (x & (x - 1)) == 0;
}

size_t next_power_of_two(size_t x) {
    if (x == 0) return 1;
    x--;
    for (size_t i = 1; i < sizeof(size_t) * 8; i <<= 1) {
        x |= x >> i;
    }
    return x + 1;
}

void fill_random_bytes(uint8_t *buf, size_t len) {
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
    for (size_t i = 0; i < len; i++) {
        buf[i] = (uint8_t)(rand() % 256);
    }
}
