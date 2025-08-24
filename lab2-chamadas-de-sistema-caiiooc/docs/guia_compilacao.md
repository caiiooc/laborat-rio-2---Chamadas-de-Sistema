# Guia de Compilação com GCC

Este breve guia ensina como usar o compilador GCC para compilar os exercícios do laboratório.
## O que é o GCC?

GCC (GNU Compiler Collection) é o compilador padrão para C em sistemas Linux. Ele transforma seu código fonte (`.c`) em um programa executável.

## Verificando se o GCC está Instalado

```bash
# Verificar versão
gcc --version

# Se não estiver instalado (Ubuntu/Debian)
sudo apt update
sudo apt install gcc
```

## Compilação Básica

### Sintaxe Simples
```bash
gcc arquivo_fonte.c -o nome_do_executável
```

### Exemplo Prático
```bash
# Compilando o exercício 0
gcc src/ex0_observar.c -o ex0_observar

# Executar
./ex0_observar
```

## Flags Úteis do GCC

### Flags Básicas Recomendadas

```bash
# Compilação com warnings e debug
gcc -Wall -g src/ex1_leitura.c -o ex1_leitura
```

**Explicação das flags:**
- `-Wall`: Mostra todos os warnings importantes
- `-g`: Inclui informações de debug (útil para encontrar erros e usar outros programas de depuração)

### Outras Flags Úteis

```bash
# Compilação com otimização
gcc -O2 src/ex2_contador.c -o ex2_contador

# Compilação pedante (com mais warnings)
gcc -Wall -Wextra -pedantic src/ex3_copia.c -o ex3_copia

# Especificar padrão C
gcc -std=c99 src/ex1_leitura.c -o ex1_leitura
```

## Exemplos para Cada Exercício

### Exercício 0 - Observar
```bash
# Compilar
gcc src/ex0_observar.c -o ex0_observar

# Executar normalmente
./ex0_observar

# Executar com strace
strace ./ex0_observar
```

### Exercício 1 - Leitura
```bash
# Compilar com debug e warnings
gcc -Wall -g src/ex1_leitura.c -o ex1_leitura

# Testar se compila sem erros
./ex1_leitura

# Se der erro, verificar warnings de compilação
```

### Exercício 2 - Contador
```bash
# Compilar
gcc -Wall -g src/ex2_contador.c -o ex2_contador

# Testar
./ex2_contador

# Observar com strace
strace -c ./ex2_contador
```

### Exercício 3 - Cópia
```bash
# Compilar
gcc -Wall -g src/ex3_copia.c -o ex3_copia

# Testar
./ex3_copia

# Verificar se arquivo foi copiado
ls -la
```

## Lidando com Erros de Compilação

### Erro: "No such file or directory"
```bash
# Verifique se o arquivo existe
ls src/ex1_leitura.c

# Verifique se está no diretório correto
pwd
ls
```

### Erro: "undefined reference"
Geralmente significa que você esqueceu de incluir uma biblioteca:
```c
// Adicione os includes necessários
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
```

### Warnings de Compilação
Sempre corrija os warnings:
```bash
# Exemplo de warning comum
src/ex1_leitura.c:15: warning: unused variable 'buffer'

# Solução: use a variável ou remova se não precisar
```

## Script de Compilação Rápida

Crie um script simples para compilar todos os exercícios:

```bash
# Crie arquivo compile.sh
nano compile.sh

# Conteúdo do arquivo:
#!/bin/bash
echo "Compilando exercícios..."
gcc -Wall -g src/ex0_observar.c -o ex0_observar
gcc -Wall -g src/ex1_leitura.c -o ex1_leitura  
gcc -Wall -g src/ex2_contador.c -o ex2_contador
gcc -Wall -g src/ex3_copia.c -o ex3_copia
echo "Compilação concluída!"

# Tornar executável
chmod +x compile.sh

# Usar
./compile.sh
```

## Makefile vs GCC Direto

### Usando GCC Diretamente (Recomendado para iniciantes)
```bash
# Simples e direto
gcc -Wall -g src/ex1_leitura.c -o ex1_leitura
```

**Vantagens:**
- Você vê exatamente o que está acontecendo
- Aprende os comandos de compilação
- Sem dependências de Makefile

### Usando Makefile (Opcional)
```bash
# Se preferir automação
make ex1
```

**Vantagens:**
- Compilação automática
- Facilita quando há muitos arquivos

## Fluxo de Trabalho Recomendado

```bash
# 1. Editar código
nano src/ex1_leitura.c

# 2. Compilar com warnings
gcc -Wall -g src/ex1_leitura.c -o ex1_leitura

# 3. Se houver erros, corrigir e repetir passo 2

# 4. Testar programa
./ex1_leitura

# 5. Se funcionar, testar com strace
strace ./ex1_leitura

# 6. Continuar com próximo exercício
```

## Organizando Executáveis

### Manter Organizado
```bash
# Criar pasta para executáveis (opcional)
mkdir bin

# Compilar para pasta específica
gcc src/ex1_leitura.c -o bin/ex1_leitura

# Executar
./bin/ex1_leitura
```

### Limpeza
```bash
# Remover executáveis antigos
rm ex0_observar ex1_leitura ex2_contador ex3_copia

# Ou com padrão
rm ex*
```

## Dicas Importantes

### 1. Sempre Use Flags de Warning
```bash
# Bom
gcc -Wall -g src/ex1_leitura.c -o ex1_leitura

# Ruim (sem warnings)
gcc src/ex1_leitura.c -o ex1_leitura
```

### 2. Nome do Executável
```bash
# Bom (nome claro)
gcc src/ex1_leitura.c -o ex1_leitura

# Ruim (nome genérico)
gcc src/ex1_leitura.c -o a.out
```

### 3. Teste Imediatamente
```bash
# Compile e teste logo
gcc -Wall -g src/ex1_leitura.c -o ex1_leitura && ./ex1_leitura
```

### 4. Verifique Arquivos Necessários
```bash
# Antes de compilar exercícios que usam arquivos
ls dados/teste1.txt
```

## Exemplo Completo

Vamos compilar e testar o exercício 1 completo:

```bash
# 1. Verificar se arquivo existe
ls src/ex1_leitura.c

# 2. Verificar se arquivo de dados existe
ls dados/teste1.txt

# 3. Compilar
gcc -Wall -g src/ex1_leitura.c -o ex1_leitura

# 4. Se houver warnings, corrigir código

# 5. Testar execução
./ex1_leitura

# 6. Testar com strace
strace -e open,read,close ./ex1_leitura

# 7. Salvar trace
strace -o traces/ex1_trace.txt ./ex1_leitura
```

## Problemas Comuns

### "Permission denied"
```bash
# Dar permissão de execução
chmod +x ex1_leitura
```

### "Command not found"
```bash
# Usar ./
./ex1_leitura

# Não apenas
ex1_leitura
```

### Programa não faz nada
```bash
# Verificar se há arquivos de entrada necessários
ls dados/
```

## Resumo dos Comandos

| Comando | O que faz |
|---------|-----------|
| `gcc arquivo.c -o programa` | Compilação básica |
| `gcc -Wall -g arquivo.c -o programa` | Compilação com warnings e debug |
| `./programa` | Executar programa |
| `chmod +x programa` | Dar permissão de execução |
| `ls -la programa` | Verificar se arquivo existe |

**Lembre-se:** Compile sempre com `-Wall -g` para pegar erros cedo!