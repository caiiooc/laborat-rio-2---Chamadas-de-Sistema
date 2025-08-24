# Relatório do Laboratório 2 - Chamadas de Sistema

---

## Exercício 1a - Observação printf() vs 1b - write()

### Comandos executados:
```bash
strace -e write ./ex1a_printf
strace -e write ./ex1b_write
```

### Análise

**1. Quantas syscalls write() cada programa gerou?**
- ex1a_printf: 9 syscalls
- ex1b_write: 7 syscalls

**2. Por que há diferença entre os dois métodos? Consulte o docs/printf_vs_write.md**

```
A diferença entre os dois métodos está no uso do buffering. O write() envia os dados diretamente ao sistema operacional sempre que é chamado tornando o comportamento imediato, mas com maior custo de chamadas ao kernel; já o printf() utiliza um buffer interno que guarda os dados temporariamente e só os envia em situações específicas como quando o buffer enche, quando há uma quebra de linha (\n), quando o programa termina ou quando se força o envio com fflush().

Na prática, isso significa que um único printf() com várias strings pode gerar menos chamadas ao sistema do que várias chamadas a write() separadas porque os dados ficam acumulados no buffer antes de serem enviados. Por outro lado, um printf() com muitos \n pode acabar gerando mais writes do que o esperado já que cada quebra de linha força o flush do buffer. Portanto, o número de syscalls no printf() depende do conteúdo e do uso de quebras de linha, enquanto no write() cada chamada corresponde sempre a uma syscall.
```

**3. Qual método é mais previsível? Por quê?**

```
O método mais previsível é o write() porque cada chamada envia os dados imediatamente ao sistema operacional gerando sempre uma syscall. Não depende de buffering, quebras de linha ou tamanho de string. 
```

---

## Exercício 2 - Leitura de Arquivo

### Resultados da execução:
- File descriptor: 3
- Bytes lidos: 127

### Comando strace:
```bash
strace -e openat,read,close ./ex2_leitura
```

### Análise

**1. Qual file descriptor foi usado? Por que não 0, 1 ou 2?**

```
O file descriptor usado foi o 3 porque no Linux os descriptors 0, 1 e 2 já estão reservados para entrada padrão (stdin) [0], saída padrão (stdout) [1], erro padrão (stderr) [2].

Portanto, o primeiro descriptor livre para arquivos abertos pelo programa é o 3.
```

**2. Como você sabe que o arquivo foi lido completamente?**

```
O arquivo teste1.txt possui 124 bytes e o programa utiliza um buffer de 128 bytes, mas lê no máximo 127 bytes reservando 1 byte para o \0.

Como o tamanho do arquivo é menor que a capacidade do buffer, todos os bytes foram lidos de uma vez garantindo que o arquivo inteiro foi carregado na memória.
```

**3. O que acontece se esquecer de fechar o arquivo?**

```
Se close(fd) não for chamado o Linux fecha automaticamente os descriptors ao final da execução do programa.
```

**4. Por que verificar retorno de cada syscall?**

```
Porque verificar o retorno de cada syscall permite que o programa identifique erros se houver algum.
```

---

## Exercício 3 - Contador com Loop

### Resultados (BUFFER_SIZE = 64):
- Linhas: 25 (esperado: 25)
- Caracteres: 1300
- Chamadas read(): 21
- Tempo: 0.000000 segundos

### Experimentos com buffer:

| Buffer Size | Chamadas read() | Tempo (s) |
|-------------|-----------------|-----------|
| 16          |       84        |  0.000000 |
| 64          |       23        |  0.000000 |
| 256         |        8        |  0.000000 |
| 1024        |        4        |  0.000000 |

### Análise

**1. Como o tamanho do buffer afeta o número de syscalls?**

```
O tamanho do buffer afeta diretamente o número de chamadas read() necessárias para ler um arquivo. Buffers maiores permitem que o programa leia uma quantidade maior de dados em cada chamada diminuindo o número total de syscalls. Por outro lado, buffers menores limitam a quantidade de dados lidos a cada chamada aumentando significativamente o número de chamadas necessárias.

Exemplo: Com buffer de 16 bytes foram feitas 84 chamadas read(), com 64 bytes foram 23 chamadas, com 256 bytes apenas 8 chamadas e com 1024 bytes apenas 4 chamadas. Portanto, quanto maior o buffer, menor a sobrecarga causada pelas syscalls.
```

**2. Como você detecta o fim do arquivo?**

```
O fim do arquivo (EOF) é detectado quando a chamada read() retorna 0 bytes indicando que não há mais dados a serem lidos. No teste com buffer de 1024 bytes foram feitas 4 chamadas read() para processar o arquivo de 1300 bytes, cada leitura retornou parte dos dados do arquivo e na última tentativa de leitura read() retornaria 0 bytes, sinalizando o fim do arquivo (EOF).
```

**3. Todas as chamadas read() retornaram BUFFER_SIZE bytes?**

```
Não, nem todas as chamadas read() retornaram exatamente o tamanho do buffer solicitado. 

- No log do programa com buffer de 1024 bytes a primeira leitura retornou 1024 bytes preenchendo completamente o buffer.
- A segunda leitura retornou apenas 276 bytes porque eram os últimos bytes restantes do arquivo de 1300 bytes.
- A terceira leitura retornou 0 bytes indicando o fim do arquivo (EOF).
```

**4. Qual é a relação entre syscalls e performance?**

```
A relação entre syscalls e performance é que o número de syscalls impacta diretamente a performance do programa, pois cada chamada read() envolve uma transição entre o espaço do usuário e o kernel que é relativamente custosa. Quanto maior o número de chamadas, maior será a sobrecarga do sistema podendo reduzir a eficiência da leitura. Por isso, utilizar buffers maiores diminui o número de syscalls, reduz a sobrecarga e melhora a performance.
```

---

## Exercício 4 - Cópia de Arquivo

### Resultados:
- Bytes copiados: 1364
- Operações: 22
- Tempo: 0.000000 segundos
- Throughput: (1364 / 1024) / 0.014 = 95 KB/s

### Verificação:
```bash
diff dados/origem.txt dados/destino.txt
```
Resultado: [X] Idênticos [ ] Diferentes

### Análise

**1. Por que devemos verificar que bytes_escritos == bytes_lidos?**

```
Porque o write() pode escrever menos bytes do que o read() retornou, por motivos como buffers cheios ou erros de E/S. Essa verificação garante que todos os dados lidos realmente foram gravados no destino.
```

**2. Que flags são essenciais no open() do destino?**

```
O_WRONLY - abrir para escrita.
O_CREAT - criar o arquivo caso não exista.
O_TRUNC - limpar o conteúdo do arquivo se já existir.
```

**3. O número de reads e writes é igual? Por quê?**

```
Sim, porque cada chamada read() que retorna dados válidos é seguida por um write() com exatamente o mesmo conteúdo.
```

**4. Como você saberia se o disco ficou cheio?**

```
Eu saberia se o disco ficou cheio caso o write() retornasse um valor menor que bytes_lidos (ou -1 com ENOSPC) indicando que não foi possível gravar todos os bytes porque o espaço em disco acabou.
```

**5. O que acontece se esquecer de fechar os arquivos?**

```

Se esquecer de fechar os arquivos, os file descriptors ficam presos até o programa terminar, podendo causar vazamentos de descriptors se vários arquivos forem abertos.

No caso de arquivos gravados pode haver dados não "flushados" (sem sincronizar no disco).
```

---

## Análise Geral

### Conceitos Fundamentais

**1. Como as syscalls demonstram a transição usuário → kernel?**

```
As syscalls (open, read, write, close) são chamadas feitas pelo programa em modo usuário para solicitar serviços do kernel. O strace mostra essa transição: cada vez que o programa precisa de acesso ao disco ele pede ao kernel via syscall, pois o usuário não tem acesso direto ao hardware.
```

**2. Qual é o seu entendimento sobre a importância dos file descriptors?**

```
Segundo o meu entendimento, os file descriptors são importantes porque funcionam como identificadores inteiros que o kernel usa para controlar arquivos abertos e direcionar as operações de leitura e escrita.
```

**3. Discorra sobre a relação entre o tamanho do buffer e performance:**

```
A relação entre o tamanho do buffer e a performance é que buffers maiores reduzem a quantidade de chamadas read() e write() diminuindo o custo das transições para o kernel e aumentando a eficiência da cópia de dados.
```

### Comparação de Performance

```bash
# Teste seu programa vs cp do sistema
time ./ex4_copia
time cp dados/origem.txt dados/destino_cp.txt
```

**Qual foi mais rápido?** [./ex4_copia] foi mais rápido (0.012s) do que o [cp dados/origem.txt dados/destino_cp.txt] (0.020s).

**Por que você acha que foi mais rápido?**

```
O ./ex4_copia foi mais rápido porque é um executável compilado que realiza apenas a cópia do arquivo de forma direta, lendo e escrevendo bytes sem verificações adicionais; Já o comando cp, mesmo copiando apenas dois arquivos .txt precisa lidar com verificações de permissões, links simbólicos, diretórios e manter compatibilidade com várias opções, o que adiciona sobrecarga. Por isso, para uma cópia simples o programa compilado é mais eficiente que o cp.
```

---

## Entrega

Certifique-se de ter:
- [X] Todos os códigos com TODOs completados
- [X] Traces salvos em `traces/`
- [X] Este relatório preenchido como `RELATORIO.md`

```bash
strace -e write -o traces/ex1a_trace.txt ./ex1a_printf
strace -e write -o traces/ex1b_trace.txt ./ex1b_write
strace -o traces/ex2_trace.txt ./ex2_leitura
strace -c -o traces/ex3_stats.txt ./ex3_contador
strace -o traces/ex4_trace.txt ./ex4_copia
```