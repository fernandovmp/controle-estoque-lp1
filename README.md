# Controle de estoque
> Projeto final da disciplina de Linguagem de programação I da Fatec Sorocaba

## Funcionalidades
- Cadastrar produto
- Editar produto
- Dar baixa no produto
- Listar produtos
- Pesquisar produtos
- Deletar produto
- Salvar dados em arquivos

## Gerar build com o CMake

Em uma interface de linha de comando usar os seguintes comandos posicionado na raiz do projeto:
(é necessário uma pasta "build" na raiz do projeto)
```cmd
    cmake -B build
    cmake --build build
    ./build/controleEstoque
```

## Compilar e executar direto com o gcc

Em uma interface de linha de comando usar os seguintes comandos posicionado na raiz do projeto:
```cmd
    mkdir out
    gcc -o out/utilidades.o -c src/utilidades.c -I include/
    gcc -o out/estoque.o -c src/estoque.c -I include/
    gcc -o out/dadosEstoque.o -c src/dadosEstoque.c -I include/
    gcc -o out/controleEstoque.o -c src/controleEstoque.c -I include/
    gcc out/utilidades.o out/estoque.o out/dadosEstoque.o out/controleEstoque.o -o out/controleEstoque.exe
    ./out/controleEstoque.exe
```
