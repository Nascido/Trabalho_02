#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_manager.h"

// Variáveis estáticas para gerenciar a memória física
static uint8_t *physical_memory = NULL; // Vetor que representa a memória física
static size_t total_mem_size = 0;       // Tamanho total da memória física
static size_t frame_size = 0;           // Tamanho de cada quadro
static size_t num_frames = 0;           // Número total de quadros
static uint8_t *frame_bitmap = NULL;    // Bitmap: 0 = livre, 1 = ocupado

// Inicializa a memória física e o bitmap de quadros livres
void memory_init(size_t mem_sz, size_t frm_sz) {
    total_mem_size = mem_sz;
    frame_size = frm_sz;
    num_frames = mem_sz / frm_sz;
    physical_memory = (uint8_t*)malloc(total_mem_size); // Aloca memória física
    frame_bitmap = (uint8_t*)calloc(num_frames, sizeof(uint8_t)); // Todos quadros livres
}

// Libera a memória física e o bitmap
void memory_cleanup() {
    free(physical_memory);
    free(frame_bitmap);
    physical_memory = NULL;
    frame_bitmap = NULL;
    total_mem_size = 0;
    frame_size = 0;
    num_frames = 0;
}

// Procura um quadro livre, marca como ocupado e retorna seu índice
int allocate_frame() {
    for (size_t i = 0; i < num_frames; i++) {
        if (frame_bitmap[i] == 0) {
            frame_bitmap[i] = 1;
            return (int)i;
        }
    }
    return -1; // Sem quadros livres
}

// Libera (marca como livre) o quadro de índice fornecido
void free_frame(int frame_idx) {
    if (frame_idx >= 0 && (size_t)frame_idx < num_frames) {
        frame_bitmap[frame_idx] = 0;
    }
}

// Conta e retorna o número de quadros livres
size_t get_free_frames_count() {
    size_t count = 0;
    for (size_t i = 0; i < num_frames; i++) {
        if (frame_bitmap[i] == 0) count++;
    }
    return count;
}

// Exibe o estado da memória física e o mapa de quadros (X = ocupado, . = livre)
void print_memory() {
    printf("Memória Física: %zu bytes (%zu quadros de %zu bytes)\n", total_mem_size, num_frames, frame_size);
    printf("Quadros livres: %zu\n", get_free_frames_count());
    printf("Mapa de quadros: ");
    for (size_t i = 0; i < num_frames; i++) {
        printf("%c", frame_bitmap[i] ? 'X' : '.');
    }
    printf("\n");
}
