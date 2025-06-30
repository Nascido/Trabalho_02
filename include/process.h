#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>
#include <stdint.h>
#include "page_table.h"

#define MAX_PROCESS_ID_LEN 32

typedef struct Process {
    char id[MAX_PROCESS_ID_LEN];
    size_t size;
    uint8_t *logical_memory;
    PageTable *page_table;
    struct Process *next;
} Process;

void process_init_list();
void process_set_frame_size(size_t frame_size);
void process_set_max_size(size_t max_size);
Process* create_process(const char *id, size_t size);
Process* find_process(const char *id);
void print_processes();
void print_process_page_table(Process *proc);
void free_process(Process *proc);
void cleanup_process_list();
int remove_process(const char *id);

#endif // PROCESS_H
