# PARA_FAZER

## Análise de Incompletudes e Pontos de Melhoria

Este arquivo lista, por módulo, os pontos que precisam ser corrigidos, implementados ou revisados para atender completamente aos requisitos do trabalho, conforme os documentos "Trabalho2_SistemasOperacionais.md" e "Descricao_Completa_Passos_Trabalho02.md".

---

## main.c
- [x] Permitir configuração do tamanho máximo de processo (ler do usuário no início).
- [x] Validar se os tamanhos informados (memória física, quadro, máximo de processo) são potências de dois.
- [x] Adicionar opção no menu para visualizar tabela de páginas de um processo específico (solicitar ID, mostrar tamanho e mapeamento página-quadro).
- [x] Exibir mensagem de erro se o tamanho do processo informado exceder o máximo permitido.
- [x] Exibir mensagem de erro se não houver memória suficiente para criar o processo.
- [x] Passar o tamanho do quadro/página corretamente para todos os módulos (não fixar em 4096).

---

## memory_manager.c / memory_manager.h
- [x] Garantir que o tamanho do quadro e da memória física são potências de dois.
- [ ] Implementar função para exibir o conteúdo de cada quadro da memória física (não apenas o mapa de ocupação).
- [x] Exibir o percentual de memória livre (não apenas a contagem de quadros livres).

---

## process.c / process.h
- [x] Corrigir a criação da tabela de páginas: o tamanho da página/quadro deve ser dinâmico (não fixo em 4096).
- [x] Validar tamanho do processo na criação (não permitir maior que o máximo).
- [x] Inicializar a memória lógica do processo com valores aleatórios.
- [x] Verificar disponibilidade de quadros antes de criar o processo.
- [x] Implementar função para exibir a tabela de páginas de um processo específico (ID, tamanho, mapeamento página-quadro).
- [x] Implementar função para liberar os quadros ocupados ao remover um processo.

---

## page_table.c / page_table.h
- [x] Garantir que a estrutura da tabela de páginas não inclua bits auxiliares.
- [x] Permitir inicialização da tabela de páginas com tamanho dinâmico (conforme tamanho do quadro).

---

## utils.c / utils.h
- [x] Usar as funções de validação de potência de dois em todas as entradas relevantes.

---

## Documentação e Relatório
- [ ] Adicionar exemplos de uso, instruções de compilação e execução no README.md.
- [ ] Criar relatório detalhado com descrição das principais partes do código, casos de teste e saídas esperadas.
- [ ] Garantir que todos os arquivos necessários para compilação e execução estejam presentes.

---

## Observações Gerais
- [ ] Modularizar funções de inicialização, limpeza, alocação/liberação de quadros, exibição formatada de memória e tabelas.
- [ ] Garantir compatibilidade com C99.
- [ ] Não implementar bits auxiliares ou algoritmos de substituição de páginas.

---

> Atualize esta lista conforme for implementando as correções e melhorias.
