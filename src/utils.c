#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "utils.h"

// Verifica se um número é potência de dois
int is_power_of_two(size_t x) {
    return x != 0 && (x & (x - 1)) == 0;
}

// Preenche um buffer com bytes aleatórios (útil para inicializar memória lógica de processos)
void fill_random_bytes(uint8_t *buf, size_t len) {
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL)); // Garante que a semente do rand é diferente a cada execução
        seeded = 1;
    }
    for (size_t i = 0; i < len; i++) {
        buf[i] = (uint8_t)(rand() % 256); // Gera um byte aleatório
    }
}
