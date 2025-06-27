<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" class="logo" width="120"/>

## Descrição Completa dos Passos para o Trabalho 2 de Sistemas Operacionais: Simulação de Gerenciamento de Memória por Paginação

A seguir está um roteiro detalhado, estruturado para ser entendido e processado por uma IA como o Copilot, visando gerar tanto a estrutura de arquivos quanto a implementação do simulador em C, conforme as orientações do documento do trabalho[^1].

---

### **1. Objetivo Geral**

- Implementar um simulador de gerenciamento de memória usando paginação, em C, para fins didáticos em Sistemas Operacionais.
- O simulador deve permitir a alocação não contígua de memória para processos, utilizando tabelas de páginas, quadros e páginas de tamanho configurável (potências de dois)[^1].

---

### **2. Estruturas de Dados Principais**

- **Memória Física:** Vetor de bytes, tamanho configurável.
- **Memória Lógica do Processo:** Vetor de bytes, tamanho definido na criação do processo.
- **Tabela de Páginas:** Estrutura de mapeamento entre páginas lógicas e quadros físicos, sem bits auxiliares.
- **Gerenciador de Quadros Livres:** Lista encadeada ou bitmap para controle dos quadros disponíveis.
- **Lista de Processos:** Estrutura para armazenar informações dos processos ativos (ID, tamanho, tabela de páginas, etc.)[^1].

---

### **3. Configurações Iniciais**

- O programa deve aceitar, via parâmetros ou configuração, os seguintes valores (sempre potências de dois):
    - Tamanho da memória física.
    - Tamanho da página/quadro.
    - Tamanho máximo de um processo[^1].

---

### **4. Funcionalidades da Interface de Linha de Comando**

- **Visualizar Memória:**
    - Exibir o percentual de memória livre.
    - Mostrar o conteúdo de cada quadro da memória física.
- **Criar Processo:**
    - Solicitar ID e tamanho do processo.
    - Validar tamanho (não exceder o máximo).
    - Verificar disponibilidade de memória.
    - Inicializar memória lógica do processo (preferencialmente com valores aleatórios).
    - Carregar páginas em quadros livres.
    - Criar tabela de páginas.
    - Mensagem de erro caso não haja memória suficiente.
- **Visualizar Tabela de Páginas:**
    - Exibir tamanho do processo e o mapeamento página-quadro para um processo informado[^1].

---

### **5. Passos de Implementação**

**a) Estrutura de Arquivos**

- `main.c`: Função principal e parser de argumentos.
- `memory_manager.c/h`: Gerenciamento da memória física e dos quadros livres.
- `process.c/h`: Estruturas e funções para criação e manipulação de processos.
- `page_table.c/h`: Manipulação das tabelas de páginas.
- `utils.c/h`: Funções auxiliares (ex: geração de valores aleatórios, validações).
- `Makefile`: Automação da compilação.
- `README.md` e/ou `relatorio.txt`: Instruções, descrição do código, casos de teste e resultados esperados[^1].

**b) Inicialização**

- Ler parâmetros de configuração.
- Inicializar memória física.
- Inicializar estrutura de quadros livres (lista ou bitmap).
- Preparar lista de processos.

**c) Implementação das Funcionalidades**

- **Visualização da memória:**
    - Calcular e mostrar percentual de quadros livres.
    - Exibir conteúdo de cada quadro.
- **Criação de processo:**
    - Solicitar dados ao usuário.
    - Validar tamanho.
    - Calcular número de páginas necessárias.
    - Verificar disponibilidade de quadros.
    - Alocar quadros e atualizar estrutura de quadros livres.
    - Inicializar memória lógica do processo.
    - Criar tabela de páginas (mapeamento página → quadro).
    - Adicionar processo à lista de processos.
- **Visualização de tabela de páginas:**
    - Solicitar ID do processo.
    - Exibir tamanho e tabela de páginas correspondente.

**d) Relatório e Casos de Teste**

- Documentar as principais partes do código.
- Instruções de compilação e execução.
- Descrever casos de teste (exemplo: criar processo, visualizar memória, visualizar tabela de páginas) e apresentar as saídas esperadas[^1].

---

### **6. Restrições e Observações Importantes**

- Não implementar algoritmos de substituição de páginas.
- Não incluir bits auxiliares (ex: bit de presença, modificação) na tabela de páginas.
- Todos os tamanhos devem ser potências de dois.
- O código deve ser compatível com C99 e de fácil leitura.
- Todos os arquivos necessários para compilação e execução devem estar incluídos no pacote de entrega.
- O trabalho será entregue em um arquivo `.zip` contendo código-fonte, relatório e arquivos de teste[^1].

---

### **7. Sugestão de Modularização**

- Funções para inicialização e limpeza de estruturas.
- Função para alocação de quadros livres.
- Função para liberação de quadros (caso deseje implementar remoção de processos).
- Função para exibição formatada da memória e tabelas.
- Funções de validação dos parâmetros de entrada.

---

### **8. Comandos de Compilação**

- Usar `gcc` com as opções adequadas para C99, por exemplo:

```bash
gcc -std=c99 -Wall -Wextra -o simulador main.c memory_manager.c process.c page_table.c utils.c
```


---

### **Resumo para Copilot**

Implemente um simulador em C de gerenciamento de memória por paginação, com configuração flexível dos tamanhos (potências de dois), controle de quadros livres (lista ou bitmap), tabelas de páginas sem bits auxiliares, interface de linha de comando para criar processos, visualizar memória e tabelas de páginas, e documentação detalhada. Modularize o código conforme sugerido acima, garantindo clareza e compatibilidade com C99[^1].

<div style="text-align: center">⁂</div>

[^1]: Trabalho2_SistemasOperacionais.md

