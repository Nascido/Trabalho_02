#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stddef.h>

typedef struct PageEntry {
    int frame_number; // Número do quadro físico
} PageEntry;

typedef struct PageTable {
    PageEntry *entries; // Array de entradas da tabela de páginas
    size_t num_pages;   // Número de páginas
} PageTable;

PageTable* create_page_table(size_t num_pages);
void free_page_table(PageTable *pt);
void print_page_table(const PageTable *pt);

#endif // PAGE_TABLE_H
