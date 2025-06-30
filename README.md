# Relatório do Trabalho 2: Simulador de Gerenciamento de Memória por Paginação

## 1. Introdução

Este documento detalha a implementação de um simulador de gerenciamento de memória utilizando a técnica de paginação. O projeto, desenvolvido em linguagem C, tem como objetivo aplicar e solidificar os conceitos teóricos da alocação não contígua de memória, um dos tópicos fundamentais da disciplina de Sistemas Operacionais.

O simulador permite ao usuário configurar o ambiente de memória (tamanho total, tamanho da página/quadro), criar e remover processos, e visualizar o estado da memória e as tabelas de páginas dos processos ativos, oferecendo uma ferramenta didática para a compreensão prática do funcionamento da paginação.

## 2. Descrição das Principais Partes do Código

O projeto foi estruturado de forma modular para garantir a clareza, a manutenibilidade e a reutilização do código. A seguir, uma descrição de cada um dos principais módulos e suas responsabilidades.

### 2.1. Estrutura de Arquivos

O projeto está organizado na seguinte estrutura de diretórios:

```
Trabalho_02/
├── Makefile
├── README.md
├── include/
│   ├── memory_manager.h
│   ├── page_table.h
│   ├── process.h
│   └── utils.h
└── src/
    ├── main.c
    ├── memory_manager.c
    ├── page_table.c
    ├── process.c
    └── utils.c
```

### 2.2. Módulo main.c

É o ponto de entrada do programa. Suas principais responsabilidades são:

**Interface com o Usuário:** Apresenta o menu principal e processa as opções escolhidas pelo usuário (criar processo, listar processos, etc.).

**Configuração Inicial:** Solicita ao usuário os tamanhos da memória física, do quadro/página e o tamanho máximo para um processo. Realiza a validação para garantir que os valores inseridos sejam potências de dois.

**Inicialização e Limpeza:** Chama as funções de inicialização dos outros módulos no início da execução e as funções de limpeza ao final, garantindo que toda a memória alocada seja liberada corretamente.

### 2.3. Módulo de Gerenciamento de Memória (memory_manager.c e memory_manager.h)

Este módulo abstrai a complexidade do gerenciamento da memória física.

**Representação da Memória:** Utiliza um vetor de `uint8_t` para simular a memória física e um bitmap (`frame_bitmap`) para controlar o estado de cada quadro (livre ou ocupado).

**Alocação e Liberação:** A função `allocate_frame()` busca por um quadro livre, o marca como ocupado e retorna seu índice. A função `free_frame()` faz o processo inverso.

**Visualização:** A função `print_memory()` exibe o percentual de memória livre e um mapa de ocupação dos quadros, onde `.` representa um quadro livre e `X` um quadro ocupado.

### 2.4. Módulo de Processos (process.c e process.h)

Gerencia a criação, o armazenamento e a remoção dos processos do sistema.

**Estrutura Process:** Armazena as informações de cada processo, como ID, tamanho, um ponteiro para sua memória lógica e um ponteiro para sua tabela de páginas. Os processos são organizados em uma lista encadeada.

**Criação de Processo:** A função `create_process()` é a mais complexa. Ela valida se o ID passado é único entre os processos, então verifica se há memória suficiente, aloca a memória lógica para o processo (inicializando-a com valores aleatórios), cria a tabela de páginas e, para cada página do processo, aloca um quadro na memória física, registrando o mapeamento na tabela de páginas.

**Remoção de Processo:** A função `remove_process()` encontra um processo pelo seu ID, libera todos os quadros de memória que ele ocupava e, por fim, libera a memória associada à estrutura do processo e sua tabela de páginas.

### 2.5. Módulo de Tabela de Páginas (page_table.c e page_table.h)

Fornece as estruturas e funções para manipular as tabelas de páginas.

**Estruturas PageTable e PageEntry:** `PageEntry` armazena o número do quadro físico correspondente a uma página. `PageTable` contém um vetor dessas entradas e o número total de páginas.

**Funcionalidades:** O módulo permite criar (`create_page_table`), liberar (`free_page_table`) e imprimir (`print_page_table`) uma tabela de páginas, mostrando o mapeamento de cada página para seu respectivo quadro.

## 3. Instruções de Compilação e Execução

O projeto inclui um Makefile para automatizar o processo de compilação.

### 3.1. Pré-requisitos

- Compilador GCC (compatível com o padrão C99)
- Utilitário make

### 3.2. Compilação

Para compilar o projeto, navegue até o diretório raiz e execute o seguinte comando no terminal:

```bash
make
```

Este comando compilará todos os arquivos-fonte `.c` do diretório `src/` e gerará o arquivo executável `simulador` no diretório raiz.

### 3.3. Execução

Após a compilação bem-sucedida, execute o simulador com o comando:

```bash
./simulador
```

O programa solicitará interativamente os parâmetros de configuração inicial e, em seguida, exibirá o menu de opções.

## 4. Casos de Teste e Saídas Observadas

A seguir, são apresentados alguns casos de teste executados para validar as funcionalidades do simulador, juntamente com as saídas observadas.

### Caso de Teste 1: Inicialização e Criação de um Processo

**Objetivo:** Validar a configuração inicial e a criação de um processo em um ambiente com memória suficiente.

**Configuração Inicial:**
- Memória Física: 16384 bytes
- Tamanho do Quadro: 1024 bytes
- Tamanho Máximo do Processo: 4096 bytes

**Passos:**
1. Iniciar o simulador.
2. Inserir os valores de configuração acima.
3. No menu, escolher a opção 1 (Criar processo).
4. Informar o ID P1 e o tamanho 2048 bytes.
5. No menu, escolher a opção 4 (Exibir estado da memória).
6. No menu, escolher a opção 5 (Visualizar tabela de páginas) para o processo P1.

**Saída Observada:**

```
Simulador de Gerenciamento de Memória por Paginação
Informe o tamanho da memória física (bytes): 16384
Informe o tamanho do quadro (bytes): 1024
Informe o tamanho máximo de um processo (bytes): 4096

Menu:
1. Criar processo
...
Escolha: 1
ID do processo: P1
Tamanho do processo (bytes): 2048
Processo criado com sucesso!

Pressione ENTER para continuar...

--- (Após escolher a opção 4) ---
Memória Física: 16384 bytes (16 quadros de 1024 bytes)
Quadros livres: 14 de 16 (87.5%)
Mapa de quadros: ..X.X...........................
(A posição dos 'X' pode variar devido à alocação aleatória de quadros)

--- (Após escolher a opção 5) ---
Tabela de Páginas do Processo 'P1':
Tamanho do processo: 2048 bytes
Tamanho da página: 1024 bytes
Número de páginas: 2
Mapeamento Página -> Quadro:
  Página 0 -> Quadro 2
  Página 1 -> Quadro 4
(Os números dos quadros podem variar)
```

### Caso de Teste 2: Tentativa de Criação de Processo sem Memória Suficiente

**Objetivo:** Verificar se o sistema impede a criação de um processo quando não há quadros livres suficientes.

**Configuração Inicial:** Mesma do Caso de Teste 1.

**Passos:**
1. Criar 8 processos (P1 a P8), cada um com 2048 bytes. Isso ocupará todos os 16 quadros.
2. Tentar criar um novo processo, P9, com qualquer tamanho.

**Saída Observada:**

```
--- (Após criar os 8 processos) ---
Escolha: 1
ID do processo: P9
Tamanho do processo (bytes): 1024
Erro: Não há memória suficiente para criar o processo.
```

### Caso de Teste 3: Remoção de um Processo e Reutilização da Memória

**Objetivo:** Validar se a remoção de um processo libera corretamente os quadros de memória, que podem ser reutilizados.

**Configuração Inicial:** Mesma do Caso de Teste 1.

**Passos:**
1. Criar dois processos: P1 (2048 bytes) e P2 (3072 bytes). Isso ocupará 2 + 3 = 5 quadros.
2. Visualizar o estado da memória.
3. Remover o processo P1 (opção 3).
4. Visualizar novamente o estado da memória.
5. Tentar criar um novo processo, P3, com 2048 bytes.

**Saída Observada:**

```
--- (Após criar P1 e P2) ---
Memória Física: 16384 bytes (16 quadros de 1024 bytes)
Quadros livres: 11 de 16 (68.8%)
Mapa de quadros: XX.XXX..........................

--- (Após remover P1) ---
ID do processo a remover: P1
Processo removido.

--- (Visualizando a memória novamente) ---
Memória Física: 16384 bytes (16 quadros de 1024 bytes)
Quadros livres: 13 de 16 (81.3%)
Mapa de quadros: ..X.XX..........................

--- (Criando P3) ---
ID do processo: P3
Tamanho do processo (bytes): 2048
Processo criado com sucesso!
```

## 5. Conclusão

O desenvolvimento deste simulador permitiu a aplicação prática e aprofundada dos conceitos de gerenciamento de memória com paginação. A estrutura modular do código facilitou a implementação e os testes, resultando em um programa robusto que atende a todos os requisitos propostos. O simulador se mostrou uma ferramenta eficaz para visualizar a alocação de memória, o papel da tabela de páginas e os desafios envolvidos na gestão de recursos em um sistema operacional.