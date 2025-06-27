# Simulador de Gerenciamento de Memória por Paginação

## Descrição

Este projeto implementa um simulador didático de gerenciamento de memória por paginação, conforme requisitos de Sistemas Operacionais. Permite alocação não contígua de memória para processos, utilizando tabelas de páginas, quadros e páginas de tamanho configurável (potências de dois).

## Configuração Inicial

Ao iniciar o simulador, o usuário deve informar:
- Tamanho da memória física (em bytes, potência de dois)
- Tamanho do quadro/página (em bytes, potência de dois)
- Tamanho máximo permitido para um processo (em bytes, potência de dois)

Entradas inválidas (não potências de dois) não são aceitas.

## Funcionalidades do Menu

- **Criar processo:**
  - Solicita ID e tamanho do processo.
  - Valida se o tamanho não excede o máximo permitido.
  - Verifica disponibilidade de memória.
  - Inicializa memória lógica do processo com valores aleatórios.
  - Carrega páginas em quadros livres e cria tabela de páginas.
  - Exibe mensagem de erro se não houver memória suficiente.

- **Listar processos:**
  - Exibe todos os processos ativos, seus tamanhos e tabelas de páginas.

- **Remover processo:**
  - Remove o processo informado e libera seus quadros.

- **Exibir estado da memória:**
  - Mostra percentual de memória livre.
  - Exibe o conteúdo de cada quadro da memória física.

- **Visualizar tabela de páginas de um processo:**
  - Exibe o tamanho e o mapeamento página-quadro do processo informado.

- **Sair:**
  - Libera todos os recursos e encerra o simulador.

## Compilação

Requisitos: GCC (C99)

```bash
make
```

## Execução

```bash
./simulador
```

## Exemplo de Uso

```
Simulador de Gerenciamento de Memória por Paginação
Informe o tamanho da memória física (bytes): 16384
Informe o tamanho do quadro (bytes): 1024
Informe o tamanho máximo de um processo (bytes): 4096

Menu:
1. Criar processo
2. Listar processos
3. Remover processo
4. Exibir estado da memória
5. Visualizar tabela de páginas de um processo
0. Sair
Escolha: 1
ID do processo: P1
Tamanho do processo (bytes): 2048
Processo criado com sucesso!
...
```

## Observações e Limitações
- Todos os tamanhos devem ser potências de dois.
- Não há algoritmos de substituição de páginas.
- Não há bits auxiliares na tabela de páginas.
- O código é modularizado e compatível com C99.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

- `src/`: Contém o código-fonte principal do simulador.
    - `main.c`: Ponto de entrada do programa. Responsável pela inicialização e execução do menu principal.
    - `memory_manager.c`: Implementa as funções de gerenciamento da memória física e dos quadros livres.
    - `page_table.c`: Implementa as funções de manipulação das tabelas de páginas dos processos.
    - `process.c`: Implementa as funções de criação, busca, impressão e remoção de processos, além de gerenciar suas memórias lógicas e tabelas de páginas.
    - `utils.c`: Funções auxiliares, como geração de números aleatórios e utilidades matemáticas.

- `include/`: Contém os arquivos de cabeçalho (headers) com as definições das estruturas e funções públicas de cada módulo.
    - `memory_manager.h`: Interface para o gerenciamento de memória física.
    - `page_table.h`: Interface para a manipulação das tabelas de páginas.
    - `process.h`: Interface para a manipulação de processos e suas estruturas.
    - `utils.h`: Interface para funções utilitárias gerais.

- `obj/`: Diretório destinado aos arquivos objeto gerados durante a compilação. É criado automaticamente pelo `Makefile`.

- `Makefile`: Script de automação para compilar, gerar os arquivos objeto e o executável principal (`simulador`). Também possui alvo para limpeza dos arquivos gerados (`make clean`).

- `README.md`: Este arquivo, com instruções de uso e explicação da estrutura do projeto.

- `Descricao_Completa_Passos_Trabalho02.md`: Documento com o roteiro detalhado e requisitos do trabalho.

- `Trabalho2_SistemasOperacionais.md`: Documento complementar com informações do trabalho.

Essa estrutura modular facilita a manutenção, testes e expansão do simulador, separando claramente as responsabilidades de cada componente.

## Estrutura em ASCII

```text
Trabalho_02/
├── Descricao_Completa_Passos_Trabalho02.md
├── Makefile
├── README.md
├── Trabalho2_SistemasOperacionais.md
├── include/
│   ├── memory_manager.h
│   ├── page_table.h
│   ├── process.h
│   └── utils.h
├── obj/
├── src/
│   ├── main.c
│   ├── memory_manager.c
│   ├── page_table.c
│   ├── process.c
│   └── utils.c
```

## Próximos Passos
- Implemente as funções em cada módulo conforme o cabeçalho.
- Siga o roteiro do trabalho para cada funcionalidade.
