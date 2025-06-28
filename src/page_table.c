#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_table.h"

// Cria e inicializa uma tabela de páginas para um processo
PageTable* create_page_table(size_t num_pages) {
    PageTable *pt = (PageTable*)malloc(sizeof(PageTable)); // Aloca struct
    if (!pt) return NULL;
    pt->num_pages = num_pages;
    pt->entries = (PageEntry*)malloc(num_pages * sizeof(PageEntry)); // Aloca vetor de entradas
    if (!pt->entries) {
        free(pt);
        return NULL;
    }
    for (size_t i = 0; i < num_pages; i++) {
        pt->entries[i].frame_number = -1; // -1 indica página não mapeada a nenhum quadro
    }
    return pt;
}

// Libera a memória da tabela de páginas
void free_page_table(PageTable *pt) {
    if (pt) {
        free(pt->entries);
        free(pt);
    }
}

// Exibe a tabela de páginas: para cada página, mostra o quadro correspondente (ou '-' se não mapeada)
void print_page_table(const PageTable *pt) {
    if (!pt) return;
    printf("Tabela de Páginas (%zu páginas):\n", pt->num_pages);
    printf("Página\tQuadro\n");
    for (size_t i = 0; i < pt->num_pages; i++) {
        if (pt->entries[i].frame_number == -1)
            printf("%zu\t-\n", i);
        else
            printf("%zu\t%d\n", i, pt->entries[i].frame_number);
    }
}
