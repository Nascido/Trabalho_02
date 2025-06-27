# Trabalho 2: Gerenciamento de Memória com Paginação

## Introdução

O objetivo desta atividade é exercitar conceitos relacionados à gerência de memória explorados na Unidade 2 da disciplina de Sistemas Operacionais. Neste trabalho, você deverá implementar um programa que simula o gerenciamento de memória usando paginação.

## Descrição do Trabalho

O programa deve implementar o mecanismo de **paginação** para **alocação não contígua de memória** para processos. Isso inclui a implementação dos **algoritmos e das estruturas de dados** necessárias.

- A **memória física** pode ser representada por um vetor de bytes, com **tamanho configurável**.
- A **memória lógica** de cada processo também é representada por um vetor de bytes, com tamanho definido na criação do processo.
- O **tamanho máximo de um processo**, o **tamanho da página** e, consequentemente, o **tamanho do quadro**, devem ser configuráveis.
- Os tamanhos devem ser **potências de dois**.

Durante a **criação de um processo**:
- A memória lógica deve ser inicializada (preferencialmente com valores aleatórios).
- Suas páginas devem ser carregadas em quadros da memória física.
- Deve ser criada uma **tabela de páginas** com o mapeamento entre páginas e quadros (sem bits auxiliares).
- **Não** é necessário implementar algoritmos de substituição de páginas.

Para a **alocação de memória**, o gerenciador deve manter uma estrutura com os **quadros livres**, utilizando uma lista encadeada ou um mapa de bits.

## Interface do Simulador com o Usuário

A interface será por **linha de comando** e deve oferecer as seguintes opções:

1. **Visualizar memória**:
   - Exibe o **porcentual de memória livre**.
   - Mostra o conteúdo de cada **quadro da memória física**.

2. **Criar processo**:
   - O usuário informa um **ID do processo** e o **tamanho do processo (em bytes)**.
   - Se o tamanho ultrapassar o máximo configurado, uma nova entrada deve ser solicitada.
   - Caso não haja memória suficiente, uma mensagem deve ser exibida.

3. **Visualizar tabela de páginas**:
   - Exibe o **tamanho do processo** e a **tabela de páginas** do processo informado.

## Requisitos

- O programa deve ser implementado em **linguagem C**.
- As seguintes informações devem ser **configuráveis**:
  - Tamanho da **memória física**;
  - Tamanho da **página/quadro**;
  - Tamanho **máximo de um processo**.

## Entrega do Trabalho

A entrega será feita em **grupos de até três participantes**, em um arquivo `.zip` contendo:

- Código-fonte do programa;
- Relatório com:
  - Descrição das principais partes do código;
  - Instruções de compilação e execução;
  - Casos de teste com as respectivas saídas;
- Todos os arquivos necessários para **compilação e execução** devem estar inclusos;
- A entrega será feita pelo **Moodle**.

⚠️ **Atenção**: Trabalhos que não puderem ser compilados/executados pelo professor **não serão avaliados**.
