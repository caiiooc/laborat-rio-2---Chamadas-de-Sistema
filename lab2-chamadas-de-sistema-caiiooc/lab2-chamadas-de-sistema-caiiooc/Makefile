# Makefile para o Laboratório 2 - Chamadas de Sistema
#
# Este Makefile facilita a compilação dos exercícios.
# Os alunos podem usar gcc diretamente, mas este arquivo
# automatiza o processo para facilitar correção e testes.

# Configurações do compilador
CC = gcc
CFLAGS = -Wall -g -std=c99
SRCDIR = src
DATADIR = dados
TRACEDIR = traces

# Lista de exercícios
EXERCISES = ex1a_printf ex1b_write ex2_leitura ex3_contador ex4_copia

# Regra padrão: compilar todos os exercícios
all: $(EXERCISES)
	@echo "Todos os exercícios compilados com sucesso!"
	@echo "Execute 'make help' para ver comandos disponíveis."

# Regras para compilar cada exercício individualmente
ex1a_printf: $(SRCDIR)/ex1a_printf.c
	$(CC) $(CFLAGS) $< -o $@

ex1b_write: $(SRCDIR)/ex1b_write.c
	$(CC) $(CFLAGS) $< -o $@

ex2_leitura: $(SRCDIR)/ex2_leitura.c
	$(CC) $(CFLAGS) $< -o $@

ex3_contador: $(SRCDIR)/ex3_contador.c
	$(CC) $(CFLAGS) $< -o $@

ex4_copia: $(SRCDIR)/ex4_copia.c
	$(CC) $(CFLAGS) $< -o $@

# Criar diretórios necessários e arquivos de teste
dados: 
	@echo "Criando diretórios e arquivos de teste..."
	@mkdir -p $(DATADIR)
	@mkdir -p $(TRACEDIR)
	@echo "Arquivos de teste já existem!"

# Limpar arquivos compilados e temporários
clean:
	@echo "Limpando arquivos temporários..."
	rm -f $(EXERCISES)
	rm -f $(DATADIR)/destino.txt
	rm -f core
	@echo "Limpeza concluída!"

# Limpar tudo, incluindo traces salvos
distclean: clean
	rm -rf $(TRACEDIR)/*
	@echo "Limpeza completa realizada!"

# Testar se todos os exercícios compilam
test-compile: all
	@echo "Teste de compilação: OK"
	@echo "Todos os exercícios compilaram sem erros."

# Executar exercícios 1a e 1b (demonstração)
run-ex1: ex1a_printf ex1b_write
	@echo "=== Executando Exercício 1a ==="
	./ex1a_printf
	@echo "=== Executando Exercício 1b ==="
	./ex1b_write

# Executar exercícios 1a e 1b com strace
trace-ex1: ex1a_printf ex1b_write
	@echo "=== Exercício 1a com strace ==="
	strace -e write ./ex1a_printf
	@echo "=== Exercício 1b com strace ==="
	strace -e write ./ex1b_write

# Compilar exercício específico
ex1: ex1a_printf ex1b_write
	@echo "Exercício 1 (1a e 1b) compilado."

ex2: ex2_leitura
	@echo "Exercício 2 compilado."

ex3: ex3_contador
	@echo "Exercício 3 compilado."

ex4: ex4_copia
	@echo "Exercício 4 compilado."

# Mostrar ajuda
help:
	@echo "Makefile do Laboratório 2 - Chamadas de Sistema"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make all          - Compilar todos os exercícios"
	@echo "  make ex1          - Compilar exercícios 1a e 1b"
	@echo "  make ex2          - Compilar exercício 2"
	@echo "  make ex3          - Compilar exercício 3"
	@echo "  make ex4          - Compilar exercício 4"
	@echo "  make dados        - Criar arquivos de teste"
	@echo "  make clean        - Remover executáveis"
	@echo "  make distclean    - Limpeza completa"
	@echo "  make test-compile - Testar se tudo compila"
	@echo "  make run-ex1      - Executar exercícios 1a e 1b"
	@echo "  make trace-ex1    - Executar exercícios 1a e 1b com strace"
	@echo "  make help         - Mostrar esta ajuda"
	@echo ""
	@echo "Compilação manual (alternativa):"
	@echo "  gcc -Wall -g src/ex1a_printf.c -o ex1a_printf"
	@echo "  gcc -Wall -g src/ex1b_write.c -o ex1b_write"
	@echo "  gcc -Wall -g src/ex2_leitura.c -o ex2_leitura"
	@echo "  gcc -Wall -g src/ex3_contador.c -o ex3_contador"
	@echo "  gcc -Wall -g src/ex4_copia.c -o ex4_copia"

# Regras especiais
.PHONY: all clean distclean dados help test-compile run-ex1 trace-ex1 ex1 ex2 ex3 ex4

# Evitar remoção de arquivos intermediários
.PRECIOUS: $(EXERCISES)

# Configuração para debug (usar com make DEBUG=1)
ifdef DEBUG
CFLAGS += -DDEBUG -O0
else
CFLAGS += -O2
endif

# Informações adicionais quando VERBOSE=1
ifdef VERBOSE
.SILENT:
else
.SILENT: clean distclean dados
endif