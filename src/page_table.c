
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_table.h"

// Implementação das funções de manipulação da tabela de páginas

PageTable* create_page_table(size_t num_pages) {
    PageTable *pt = (PageTable*)malloc(sizeof(PageTable));
    if (!pt) return NULL;
    pt->num_pages = num_pages;
    pt->frame_indices = (int*)malloc(num_pages * sizeof(int));
    if (!pt->frame_indices) {
        free(pt);
        return NULL;
    }
    for (size_t i = 0; i < num_pages; i++) {
        pt->frame_indices[i] = -1; // -1 indica página não mapeada
    }
    return pt;
}

void free_page_table(PageTable *pt) {
    if (pt) {
        free(pt->frame_indices);
        free(pt);
    }
}

void print_page_table(const PageTable *pt) {
    if (!pt) return;
    printf("Tabela de Páginas (%zu páginas):\n", pt->num_pages);
    printf("Página\tQuadro\n");
    for (size_t i = 0; i < pt->num_pages; i++) {
        if (pt->frame_indices[i] == -1)
            printf("%zu\t-\n", i);
        else
            printf("%zu\t%d\n", i, pt->frame_indices[i]);
    }
}
