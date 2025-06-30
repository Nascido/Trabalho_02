#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_manager.h"
#include "process.h"
#include "page_table.h"
#include "utils.h"

int main() {
    size_t mem_size, frame_size, max_process_size; // Tamanhos da memória física, quadro e processo máximo
    int running = 1;             // Flag de controle do loop principal
    char id[64];                 // Buffer para ID do processo
    size_t proc_size;            // Tamanho do processo
    int opt;                     // Opção do menu

    printf("Simulador de Gerenciamento de Memória por Paginação\n");
    
    do {
        printf("Informe o tamanho da memória física (bytes): ");
        scanf("%zu", &mem_size);
        if (!is_power_of_two(mem_size)) {
            printf("Erro: O tamanho da memória física deve ser uma potência de dois!\n");
        }
    } while (!is_power_of_two(mem_size));
    
    do {
        printf("Informe o tamanho do quadro (bytes): ");
        scanf("%zu", &frame_size);
        if (!is_power_of_two(frame_size)) {
            printf("Erro: O tamanho do quadro deve ser uma potência de dois!\n");
        }
    } while (!is_power_of_two(frame_size));
    
    do {
        printf("Informe o tamanho máximo de processo (bytes): ");
        scanf("%zu", &max_process_size);
        if (!is_power_of_two(max_process_size)) {
            printf("Erro: O tamanho máximo de processo deve ser uma potência de dois!\n");
        }
        if (max_process_size > mem_size) {
            printf("Erro: O tamanho máximo de processo não pode ser maior que a memória física!\n");
            max_process_size = 0; // Force loop continuation
        }
    } while (!is_power_of_two(max_process_size) || max_process_size > mem_size);
    
    memory_init(mem_size, frame_size); 
    process_init_list();              
    process_set_frame_size(frame_size); 
    process_set_max_size(max_process_size); 

    while (running) {
        system("clear");
        printf("\nMenu:\n");
        printf("1. Criar processo\n");
        printf("2. Listar processos\n");
        printf("3. Remover processo\n");
        printf("4. Exibir estado da memória\n");
        printf("5. Visualizar tabela de páginas de um processo\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opt);
        getchar();
        switch (opt) {
            case 1:
                system("clear");
                printf("ID do processo: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = 0;
                printf("Tamanho do processo (bytes): ");
                scanf("%zu", &proc_size);
                getchar();
                
                if (proc_size > max_process_size) {
                    printf("Erro: O tamanho do processo (%zu bytes) excede o máximo permitido (%zu bytes).\n", proc_size, max_process_size);
                } else if (!memory_has_enough_frames(proc_size)) {
                    printf("Erro: Não há memória suficiente para criar o processo.\n");
                } else {
                    if (create_process(id, proc_size))
                        printf("Processo criado com sucesso!\n");
                    else
                        printf("Erro ao criar processo.\n");
                }
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            case 2:
                system("clear");
                print_processes();
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            case 3:
                system("clear");
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
                print_memory();
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            case 5:
                system("clear");
                printf("ID do processo para visualizar tabela de páginas: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = 0;
                Process *proc = find_process(id);
                if (proc) {
                    print_process_page_table(proc);
                } else {
                    printf("Processo '%s' não encontrado.\n", id);
                }
                printf("Pressione ENTER para continuar...");
                getchar();
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
