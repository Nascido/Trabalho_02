#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stddef.h>

typedef struct PageTable {
    int *frame_indices; // page -> frame
    size_t num_pages;
} PageTable;

PageTable* create_page_table(size_t num_pages);
void free_page_table(PageTable *pt);
void print_page_table(const PageTable *pt);

#endif // PAGE_TABLE_H
