#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdint.h>

int is_power_of_two(size_t x);
size_t next_power_of_two(size_t x);
void fill_random_bytes(uint8_t *buf, size_t len);

#endif // UTILS_H
