#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "memory_manager.h"

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

// Procura um quadro livre de forma aleatória, marca como ocupado e retorna seu índice
int allocate_frame() {
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL)); // Inicializa gerador aleatório apenas uma vez
        seeded = 1;
    }
    
    // Conta quantos quadros livres existem
    size_t free_count = 0;
    for (size_t i = 0; i < num_frames; i++) {
        if (frame_bitmap[i] == 0) {
            free_count++;
        }
    }
    
    if (free_count == 0) {
        return -1; // Sem quadros livres
    }
    
    // Escolhe aleatoriamente qual quadro livre usar (índice de 0 a free_count-1)
    size_t target_free_index = rand() % free_count;
    
    // Encontra o quadro livre correspondente ao índice escolhido
    size_t current_free_index = 0;
    for (size_t i = 0; i < num_frames; i++) {
        if (frame_bitmap[i] == 0) {
            if (current_free_index == target_free_index) {
                frame_bitmap[i] = 1; // Marca como ocupado
                return (int)i;       // Retorna o índice do quadro
            }
            current_free_index++;
        }
    }
    
    return -1; // Não deveria chegar aqui
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

// Verifica se há quadros suficientes para um processo de tamanho específico
int memory_has_enough_frames(size_t process_size) {
    size_t frames_needed = process_size / frame_size + (process_size % frame_size != 0);
    return get_free_frames_count() >= frames_needed;
}

// Exibe o estado da memória física e o mapa de quadros (X = ocupado, . = livre)
void print_memory() {
    size_t free_frames = get_free_frames_count();
    double free_percentage = (double)free_frames / num_frames * 100.0;
    
    printf("Memória Física: %zu bytes (%zu quadros de %zu bytes)\n", total_mem_size, num_frames, frame_size);
    printf("Quadros livres: %zu de %zu (%.1f%%)\n", free_frames, num_frames, free_percentage);
    printf("Mapa de quadros: ");
    for (size_t i = 0; i < num_frames; i++) {
        printf("%c", frame_bitmap[i] ? 'X' : '.');
        if ((i + 1) % 50 == 0) printf("\n                "); // Quebra linha a cada 50 quadros
    }
    printf("\n");
}
