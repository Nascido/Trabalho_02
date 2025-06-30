#include "process.h"
#include "memory_manager.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ponteiro para o início da lista encadeada de processos
static Process *process_list_head = NULL;
static size_t current_frame_size = 4096; // Tamanho padrão, será atualizado
static size_t max_process_size = 0; // Tamanho máximo de processo permitido

// Inicializa a lista de processos (define como vazia)
void process_init_list() {
    process_list_head = NULL;
}

// Define o tamanho do quadro/página para o módulo de processos
void process_set_frame_size(size_t frame_size) {
    current_frame_size = frame_size;
}

// Define o tamanho máximo de processo permitido
void process_set_max_size(size_t max_size) {
    max_process_size = max_size;
}

// Cria um novo processo, aloca memória lógica e tabela de páginas, e insere na lista
Process* create_process(const char *id, size_t size) {

    if (find_process(id) != NULL) {
        fprintf(stderr, "Erro: já existe um processo com o ID '%s'\n", id);
        return NULL;
    }

    // Validação do tamanho do processo
    if (max_process_size > 0 && size > max_process_size) {
        return NULL; // Tamanho excede o máximo permitido
    }
    
    // Verifica se há quadros suficientes disponíveis
    size_t num_pages = size / current_frame_size + (size % current_frame_size != 0);
    if (!memory_has_enough_frames(size)) {
        return NULL; // Não há memória suficiente
    }
    
    Process *proc = (Process*)malloc(sizeof(Process)); // Aloca struct do processo
    if (!proc) return NULL;
    
    strncpy(proc->id, id, MAX_PROCESS_ID_LEN); // Copia o ID
    proc->id[MAX_PROCESS_ID_LEN-1] = '\0';
    proc->size = size;
    
    // Aloca memória lógica do processo
    proc->logical_memory = (uint8_t*)malloc(size);
    if (!proc->logical_memory) {
        free(proc);
        return NULL;
    }
    
    // Inicializa a memória lógica com valores aleatórios
    fill_random_bytes(proc->logical_memory, size);
    
    // Cria tabela de páginas com tamanho dinâmico baseado no frame_size atual
    proc->page_table = create_page_table(num_pages);
    if (!proc->page_table) {
        free(proc->logical_memory);
        free(proc);
        return NULL;
    }
    
    // Aloca quadros físicos para as páginas do processo
    for (size_t i = 0; i < num_pages; i++) {
        int frame_idx = allocate_frame();
        if (frame_idx == -1) {
            // Falha na alocação - libera recursos já alocados
            for (size_t j = 0; j < i; j++) {
                free_frame(proc->page_table->entries[j].frame_number);
            }
            free_page_table(proc->page_table);
            free(proc->logical_memory);
            free(proc);
            return NULL;
        }
        proc->page_table->entries[i].frame_number = frame_idx;
    }
    
    proc->next = process_list_head; // Insere no início da lista
    process_list_head = proc;
    return proc;
}

// Procura um processo pelo ID na lista
Process* find_process(const char *id) {
    for (Process *p = process_list_head; p != NULL; p = p->next) {
        if (strncmp(p->id, id, MAX_PROCESS_ID_LEN) == 0) {
            return p;
        }
    }
    return NULL;
}

// Exibe todos os processos e suas tabelas de páginas
void print_processes() {
    printf("Lista de Processos:\n");
    if (!process_list_head) {
        printf("Nenhum processo criado.\n");
        return;
    }
    
    for (Process *p = process_list_head; p != NULL; p = p->next) {
        printf("ID: %s | Tamanho: %zu bytes\n", p->id, p->size);
        print_page_table(p->page_table);
        printf("\n");
    }
}

// Exibe a tabela de páginas de um processo específico
void print_process_page_table(Process *proc) {
    if (!proc) {
        printf("Processo inválido.\n");
        return;
    }
    
    printf("Tabela de Páginas do Processo '%s':\n", proc->id);
    printf("Tamanho do processo: %zu bytes\n", proc->size);
    printf("Tamanho da página: %zu bytes\n", current_frame_size);
    
    size_t num_pages = proc->size / current_frame_size + (proc->size % current_frame_size != 0);
    printf("Número de páginas: %zu\n", num_pages);
    printf("Mapeamento Página -> Quadro:\n");
    
    for (size_t i = 0; i < num_pages; i++) {
        printf("  Página %zu -> Quadro %d\n", i, proc->page_table->entries[i].frame_number);
    }
}

// Libera toda a memória de um processo
void free_process(Process *proc) {
    if (!proc) return;
    free(proc->logical_memory);
    free_page_table(proc->page_table);
    free(proc);
}

// Libera toda a lista de processos
void cleanup_process_list() {
    Process *p = process_list_head;
    while (p) {
        Process *next = p->next;
        
        // Libera os quadros ocupados pelo processo
        if (p->page_table) {
            size_t num_pages = p->size / current_frame_size + (p->size % current_frame_size != 0);
            for (size_t i = 0; i < num_pages; i++) {
                if (p->page_table->entries[i].frame_number != -1) {
                    free_frame(p->page_table->entries[i].frame_number);
                }
            }
        }
        
        free_process(p);
        p = next;
    }
    process_list_head = NULL;
}

// Remove um processo da lista pelo id. Retorna 1 se removido, 0 se não encontrado.
int remove_process(const char *id) {
    Process *p = process_list_head, *prev = NULL;
    while (p && strncmp(p->id, id, MAX_PROCESS_ID_LEN) != 0) {
        prev = p;
        p = p->next;
    }
    if (p) {
        // Libera os quadros ocupados pelo processo antes de removê-lo
        if (p->page_table) {
            size_t num_pages = p->size / current_frame_size + (p->size % current_frame_size != 0);
            for (size_t i = 0; i < num_pages; i++) {
                if (p->page_table->entries[i].frame_number != -1) {
                    free_frame(p->page_table->entries[i].frame_number);
                }
            }
        }
        
        if (prev) prev->next = p->next;
        else process_list_head = p->next;
        free_process(p);
        return 1;
    }
    return 0;
}
