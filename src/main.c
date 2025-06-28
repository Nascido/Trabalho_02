#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_manager.h"
#include "process.h"
#include "page_table.h"
#include "utils.h"

int main() {
    size_t mem_size, frame_size; // Tamanhos da memória física e do quadro
    int running = 1;             // Flag de controle do loop principal
    char id[64];                 // Buffer para ID do processo
    size_t proc_size;            // Tamanho do processo
    int opt;                     // Opção do menu

    // Inicialização do simulador
    printf("Simulador de Gerenciamento de Memória por Paginação\n");
    printf("Informe o tamanho da memória física (bytes): ");
    scanf("%zu", &mem_size);
    printf("Informe o tamanho do quadro (bytes): ");
    scanf("%zu", &frame_size);
    memory_init(mem_size, frame_size); // Inicializa memória física
    process_init_list();               // Inicializa lista de processos

    // Loop principal do menu
    while (running) {
        system("clear");
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
                system("clear");
                // Criação de processo
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
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            case 2:
                system("clear");
                // Listagem de processos
                print_processes();
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            case 3:
                system("clear");
                // Remoção de processo
                printf("ID do processo a remover: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = 0;
                if (remove_process(id))
                    printf("Processo removido.\n");
                else
                    printf("Processo não encontrado.\n");
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            case 4:
                system("clear");
                // Exibição do estado da memória física
                print_memory();
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            case 0:
                running = 0; // Sai do loop
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    // Libera recursos antes de sair
    cleanup_process_list();
    memory_cleanup();
    return 0;
}
