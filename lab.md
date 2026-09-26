# Relatório Prático: Hierarquia de Memória, Otimizações de Cache e Pthreads
**Disciplina:** Computação Paralela  
**Faculdade de Computação e Informática (FCI)**

## Integrantes do Grupo
* **Guilherme Rainho Geraldo** — TIA: 10418251
* **Marcos Arambasic** — TIA: 10443260
* **Matheus Alonso Varjão** — TIA: 10417888

---

## 1. Introdução e Objetivos
O desempenho de aplicações de computação científica raramente é limitado apenas pela capacidade de processamento aritmético da CPU (FLOPS). O principal fator de restrição é o acesso à hierarquia de memória (*Memory Wall*). Este laboratório teve como objetivos práticos:
1. Avaliar o impacto da localidade espacial comparando varreduras por linha (*Row-Major*) versus colunas (*Column-Major*)[cite: 4].
2. Aplicar a técnica de blocagem (*tiling*) na multiplicação de matrizes densas para otimizar o uso do cache L1/L2[cite: 4].
3. Realizar o *profiling* de faltas de cache utilizando o Valgrind (Cachegrind)[cite: 4].
4. Implementar paralelismo em memória compartilhada com Pthreads, avaliando escalabilidade, *speedup* e o cuidado com a falsa partilha (*False Sharing*)[cite: 4].

---

## 2. Metodologia e Caracterização do Ambiente
* **Ambiente de Execução:** WSL / Ubuntu no Windows, compilador GCC com otimizações `-O3` e `-pthread`.
* **Programas Desenvolvidos:** 
  * `varredura_linha.c` e `varredura_coluna.c`[cite: 4]
  * `matmul_padrao.c`[cite: 4]
  * `matmul_bloco.c`[cite: 4]
  * `matmul_pthreads_bloco.c`[cite: 4]

---

## 3. Evidências Experimentais e Resultados

### 3.1 Experimento de Localidade (Linha vs. Coluna)
* **Tabela 1:** Tempos de execução variando $N \in \{512, 1024, 2048, 4096, 8192\}$[cite: 4].
  * *Inserir aqui a captura de ecrã demonstrando os testes de varredura.*

### 3.2 Análise de Cache com Valgrind (Cachegrind)
* **Tabela 2:** Comparação entre `matmul_padrao` e `matmul_bloco` ($N=512$, Bloco $B=64$)[cite: 4].
  * Redução expressiva de *D1 misses* e *LLd misses* com a blocagem.
  * *Inserir aqui a captura de ecrã com as saídas do Cachegrind.*

### 3.3 Escalabilidade com Pthreads
* **Tabela 3:** Desempenho variando de 1 a 16 threads para matrizes de tamanho elevado[cite: 4].
  * *Inserir aqui a captura de ecrã do loop de execução paralela via terminal.*

---

## 4. Respostas às Questões de Reflexão
*(Resumo técnico abordando a localidade espacial, comportamento de cache misses, escolha do tamanho do bloco $B$, impacto das flags `-O3`, e a ausência de Falsa Partilha ao decompor a matriz por blocos contíguos de linhas).*

---

## 5. Dificuldades Técnicas e Soluções
* **Calibração do Bloco ($B$):** Ajustar o tamanho ideal do tile para garantir que as submatrizes coubessem confortavelmente nos níveis de cache L1/L2 sem causar excesso de *overhead* de laços aninhados.
* **Alocação Contígua:** Substituição de matrizes de ponteiros (`double**`) por blocos lineares contíguos (`double*` alocados com `malloc`) indexados como `A[i * N + j]`, garantindo a previsibilidade estrita exigida pelas linhas de cache.
* **Interpretação do Cachegrind:** Compreensão inicial da diferença entre referências de dados (`D refs`) e faltas de último nível (`LLd misses`), superada através da análise minuciosa das métricas de leitura e escrita.

---

## 6. Seção Obrigatória: Declaração e Análise do Uso de IA
Em conformidade com as diretrizes do laboratório[cite: 4], declara-se que ferramentas de Inteligência Artificial generativa foram utilizadas de forma complementar no decorrer do projeto para:
* **Auxílio na Estruturação:** Organização e formatação da documentação técnica e relatórios nos formatos Markdown e HTML.
* **Revisão de Sintaxe:** Verificação de boas práticas em C, estruturação de laços aninhados para blocagem e sintaxe de criação de threads POSIX (`pthread_create`/`pthread_join`).

**Análise Crítica:**  
As respostas e sugestões fornecidas pela IA serviram como suporte de verificação e agilização de formatação. Toda a conceção lógica, escrita e depuração dos códigos-fonte, execução dos testes práticos no ambiente WSL, coleta das métricas via Valgrind e análise crítica dos resultados de desempenho foram conduzidas de forma independente pelos autores do grupo.

---

## 7. Conclusão
O laboratório permitiu comprovar empiricamente a teoria da hierarquia de memória. Ficou evidente que otimizar o padrão de acesso aos dados (*Row-Major*) e aplicar técnicas de blocagem e concorrência estruturada (*Pthreads*) reduz drasticamente as viagens à DRAM, elevando o rendimento computacional dos algoritmos.
