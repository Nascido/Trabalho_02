#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>
#include <stdint.h>

// Estrutura para gerenciar quadros livres (exemplo: bitmap)
void memory_init(size_t mem_size, size_t frame_size);
void memory_cleanup();
int allocate_frame();
void free_frame(int frame_idx);
size_t get_free_frames_count();
int memory_has_enough_frames(size_t process_size);
void print_memory();

#endif // MEMORY_MANAGER_H
