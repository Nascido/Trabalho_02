#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Process *process_list_head = NULL;

void process_init_list() {
    process_list_head = NULL;
}

Process* create_process(const char *id, size_t size) {
    Process *proc = (Process*)malloc(sizeof(Process));
    if (!proc) return NULL;
    strncpy(proc->id, id, MAX_PROCESS_ID_LEN);
    proc->id[MAX_PROCESS_ID_LEN-1] = '\0';
    proc->size = size;
    proc->logical_memory = (uint8_t*)malloc(size);
    if (!proc->logical_memory) {
        free(proc);
        return NULL;
    }
    size_t num_pages = size / 4096 + (size % 4096 != 0); // Exemplo: 4096 bytes por página
    proc->page_table = create_page_table(num_pages);
    if (!proc->page_table) {
        free(proc->logical_memory);
        free(proc);
        return NULL;
    }
    proc->next = process_list_head;
    process_list_head = proc;
    return proc;
}

Process* find_process(const char *id) {
    for (Process *p = process_list_head; p != NULL; p = p->next) {
        if (strncmp(p->id, id, MAX_PROCESS_ID_LEN) == 0) {
            return p;
        }
    }
    return NULL;
}

void print_processes() {
    printf("Lista de Processos:\n");
    for (Process *p = process_list_head; p != NULL; p = p->next) {
        printf("ID: %s | Tamanho: %zu bytes\n", p->id, p->size);
        print_page_table(p->page_table);
    }
}

void free_process(Process *proc) {
    if (!proc) return;
    free(proc->logical_memory);
    free_page_table(proc->page_table);
    free(proc);
}

void cleanup_process_list() {
    Process *p = process_list_head;
    while (p) {
        Process *next = p->next;
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
        if (prev) prev->next = p->next;
        else process_list_head = p->next;
        free_process(p);
        return 1;
    }
    return 0;
}
