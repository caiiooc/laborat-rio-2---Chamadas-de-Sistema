# Guia Básico do Git

Este guia apresenta os comandos essenciais do Git para completar o laboratório.

## O que é Git?

Git é um sistema de controle de versão que permite:
- Salvar diferentes versões do seu código
- Sincronizar trabalho com repositórios remotos (como GitHub)
- Colaborar com outras pessoas em projetos

## Conceitos Básicos

### Working Directory (Diretório de Trabalho)
É onde você edita seus arquivos. As mudanças aqui ainda não foram salvas no Git.

### Staging Area (Área de Preparação) 
Local temporário onde você prepara quais mudanças quer salvar. Use `git add` para mover arquivos para aqui.

### Repository (Repositório)
Onde o Git armazena todas as versões salvas do seu projeto. Use `git commit` para salvar mudanças definitivamente.

## Comandos Essenciais

### 1. Clonar o Repositório

No GitHub Classroom, você receberá um link. Depois de aceitar, clone assim:

```bash
# Substitua a URL pela do seu repositório
git clone https://github.com/disciplina-so/lab2-syscalls-SEU_USUARIO.git

# Entre no diretório
cd lab2-syscalls-SEU_USUARIO
```

### 2. Verificar Status

Sempre verifique o status antes de fazer qualquer operação:

```bash
# Ver quais arquivos foram modificados
git status
```

**Exemplo de saída:**
```
On branch main
Changes not staged for commit:
  modified:   src/ex1_leitura.c

Untracked files:
  traces/ex1_trace.txt
```

### 3. Adicionar Arquivos (Staging)

Adicione os arquivos que você quer salvar:

```bash
# Adicionar arquivo específico
git add src/ex1_leitura.c

# Adicionar todos os arquivos modificados
git add .

# Adicionar todos os arquivos de uma pasta
git add traces/
```

### 4. Fazer Commit (Salvar)

Salve suas mudanças com uma mensagem descritiva:

```bash
# Commit com mensagem
git commit -m "Completar exercício 1 de leitura de arquivo"

# Mensagem mais detalhada
git commit -m "Implementar leitura de arquivo
- Adicionar verificação de erro
- Implementar loop de leitura
- Salvar trace do strace"
```

**Dicas para boas mensagens para os commits:**
- Use presente: "Adicionar" não "Adicionei"
- Seja específico: "Corrigir bug no ex2" não "Corrigir bug"
- Primeira linha com até 50 caracteres

### 5. Enviar para o GitHub (Push)

Envie suas mudanças para o repositório remoto:

```bash
# Enviar para branch main
git push origin main

# Ou simplesmente (depois da primeira vez)
git push
```

## Fluxo do Laboratório

Aqui está o fluxo típico que você seguirá:

```bash
# 1. Clone (só uma vez, no início)
git clone https://github.com/disciplina-so/lab2-syscalls-SEU_USUARIO.git
cd lab2-syscalls-SEU_USUARIO

# 2. Trabalhe nos exercícios
# (edite arquivos, compile, teste)

# 3. Veja o que mudou
git status

# 4. Adicione suas mudanças (o . vai adicionar todas as mudancas no staging)
git add .

# 5. Faça commit
git commit -m "Completar exercícios 1 e 2"

# 6. Envie para o GitHub
git push

# Repita passos 2-6 conforme necessário
```

## Exemplo Prático

Vamos simular o fluxo de completar o exercício 1:

```bash
# Ver estado atual
git status

# Editar o arquivo (usando seu editor preferido)
vim src/ex1_leitura.c

# Compilar e testar
gcc src/ex1_leitura.c -o ex1_leitura
./ex1_leitura

# Gerar trace
strace -o traces/ex1_trace.txt ./ex1_leitura

# Ver o que mudou
git status
# Saída: modified: src/ex1_leitura.c
#        untracked: traces/ex1_trace.txt

# Adicionar mudanças (voce pode usar git add . para adicionar todas as mudancas)
git add src/ex1_leitura.c
git add traces/ex1_trace.txt

# Verificar que está pronto para commit
git status
# Saída: Changes to be committed:
#          modified: src/ex1_leitura.c
#          new file: traces/ex1_trace.txt

# Fazer commit
git commit -m "Implementar exercício 1 - leitura de arquivo"

# Enviar
git push
```

## Comandos Úteis Extras

### Ver Histórico de Commits
```bash
# Ver últimos commits
git log --oneline

# Ver com detalhes
git log
```

### Ver Diferenças
```bash
# Ver o que mudou em arquivos modificados
git diff

# Ver diferenças de arquivo específico
git diff src/ex1_leitura.c
```

### Desfazer Mudanças (CUIDADO!)
```bash
# Desfazer mudanças em arquivo específico (perde trabalho!)
git checkout -- src/ex1_leitura.c

# Remover arquivo do staging
git reset src/ex1_leitura.c
```

## Problemas Comuns

### "Permission denied" no push
Se você não conseguir fazer push, verifique se:
1. Aceitou o convite do GitHub Classroom
2. Está usando a URL correta do seu repositório
3. Está logado no GitHub (pode precisar configurar SSH ou token)

### "Nothing to commit"
Se aparecer esta mensagem:
1. Verifique se salvou os arquivos editados
2. Use `git status` para ver se há mudanças
3. Use `git add` para adicionar arquivos ao staging

### Mensagem de commit obrigatória
Se esquecer da mensagem:
```bash
# Git vai abrir um editor. Digite a mensagem, salve e feche
git commit

# Ou sempre use -m
git commit -m "Sua mensagem aqui"
```

## Configuração Inicial (Opcional)

Se for a primeira vez usando Git no sistema:

```bash
# Configurar nome e email (aparece nos commits)
git config --global user.name "Seu Nome"
git config --global user.email "seu.email@exemplo.com"

# Editor padrão (opcional)
git config --global core.editor vim
```

## Resumo dos Comandos

| Comando | O que faz |
|---------|-----------|
| `git clone <url>` | Baixa repositório do GitHub |
| `git status` | Mostra estado atual |
| `git add <arquivo>` | Adiciona arquivo ao staging |
| `git add .` | Adiciona todos os arquivos |
| `git commit -m "msg"` | Salva mudanças com mensagem |
| `git push` | Envia para GitHub |
| `git log` | Mostra histórico |
| `git diff` | Mostra diferenças |

## Para Saber Mais

- [Git - Guia Prático](https://rogerdudler.github.io/git-guide/index.pt_BR.html)
- [GitHub Docs](https://docs.github.com/pt)
- [Atlassian Git Tutorial](https://www.atlassian.com/git/tutorials)

**Lembre-se:** No laboratório, você só precisa dos comandos básicos: `clone`, `add`, `commit`, `push`. Não precisa complicar!