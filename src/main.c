#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_manager.h"
#include "process.h"
#include "page_table.h"
#include "utils.h"

int main() {
    size_t mem_size, frame_size;
    int running = 1;
    char id[64];
    size_t proc_size;
    int opt;

    printf("Simulador de Gerenciamento de Memória por Paginação\n");
    printf("Informe o tamanho da memória física (bytes): ");
    scanf("%zu", &mem_size);
    printf("Informe o tamanho do quadro (bytes): ");
    scanf("%zu", &frame_size);
    memory_init(mem_size, frame_size);
    process_init_list();

    while (running) {
        printf("\nMenu:\n");
        printf("1. Criar processo\n");
        printf("2. Listar processos\n");
        printf("3. Remover processo\n");
        printf("4. Exibir estado da memória\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opt);
        getchar(); // Limpa buffer
        switch (opt) {
            case 1:
                printf("ID do processo: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = 0;
                printf("Tamanho do processo (bytes): ");
                scanf("%zu", &proc_size);
                getchar();
                if (create_process(id, proc_size))
                    printf("Processo criado com sucesso!\n");
                else
                    printf("Erro ao criar processo.\n");
                break;
            case 2:
                print_processes();
                break;
            case 3:
                printf("ID do processo a remover: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = 0;
                if (remove_process(id))
                    printf("Processo removido.\n");
                else
                    printf("Processo não encontrado.\n");
                break;
            case 4:
                print_memory();
                break;
            case 0:
                running = 0;
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    cleanup_process_list();
    memory_cleanup();
    return 0;
}
