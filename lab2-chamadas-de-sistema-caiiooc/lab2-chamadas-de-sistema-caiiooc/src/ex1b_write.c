/*
 * Exercício 1b - Observando write()
 * 
 * OBJETIVO: Entender como write() se comporta com strace
 * 
 * TAREFA: Este código está completo. Você só precisa:
 * 1. Compilar: gcc src/ex1b_write.c -o ex1b_write
 * 2. Executar: ./ex1b_write
 * 3. Observar com strace: strace -e write ./ex1b_write
 */

#include <unistd.h>
#include <string.h>

int main() {
    // write() é uma syscall direta
    // Cada chamada vai direto para o kernel
    char msg1[] = "=== Demonstração: write() ===\n\n";
    char msg2[] = "Primeira mensagem via write\n";
    char msg3[] = "Segunda mensagem via write\n";
    char msg4[] = "Terceira mensagem via write\n";
    char msg5[] = "\n=== Análise ===\n";
    char msg6[] = "Execute: strace -e write ./ex1b_write\n";
    char msg7[] = "Observe: Cada write() gera uma syscall\n";
    
    // File descriptor 1 = stdout (saída padrão)
    write(1, msg1, strlen(msg1));
    write(1, msg2, strlen(msg2));
    write(1, msg3, strlen(msg3));
    write(1, msg4, strlen(msg4));
    write(1, msg5, strlen(msg5));
    write(1, msg6, strlen(msg6));
    write(1, msg7, strlen(msg7));
    
    return 0;
}

/*
 * CONCEITOS:
 * - write() é syscall direta (realiza a comunicação com kernel)
 * - File descriptor 1 = stdout
 * - Cada write() = uma transição modo usuário → kernel
 */