#include <stdio.h>
#include <stdlib.h>
#include <dadosEstoque.h>
#include <utilidades.h>

estoque * carregarEstoque() {
    estoque * _estoque = criarEstoque();
    
    FILE * file = fopen(ARQUIVO_ESTOQUE, "r");

    if(!file) {
        _estoque->produtos = (produto *) malloc(sizeof(produto) * _estoque->capacidade);
        return _estoque;
    }

    fread(&_estoque->tamanho, sizeof(int), 1, file);
    fread(&_estoque->proximoCodigo, sizeof(int), 1, file);
    _estoque->capacidade = max(_estoque->tamanho, _estoque->capacidade) * 2;
    _estoque->produtos = (produto *) malloc(sizeof(produto) * _estoque->capacidade);
    fread(_estoque->produtos, sizeof(produto), _estoque->tamanho, file);
    fclose(file);
    return _estoque;
}
void salvarEstoque(const estoque * _estoque) {
    FILE * file = fopen(ARQUIVO_ESTOQUE, "w");
    fwrite(&_estoque->tamanho, sizeof(int), 1, file);
    fwrite(&_estoque->proximoCodigo, sizeof(int), 1, file);
    fwrite(_estoque->produtos, sizeof(produto), _estoque->tamanho, file);
    fclose(file);
}