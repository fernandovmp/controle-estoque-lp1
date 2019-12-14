#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utilidades.h>
#include <estoque.h>

estoque * criarEstoque() {
    estoque * _estoque = (estoque *) malloc(sizeof(estoque));
    _estoque->tamanho = 0;
    _estoque->capacidade = 4;
    _estoque->proximoCodigo = 0;
    return _estoque;
}

int compararPorNome(const void * a, const void * b) {
    return strcmp_ignoreCase(((produto *)a)->nome, ((produto *)b)->nome);
}

int compararPorCodigo(const void * a, const void * b) {
    return ((produto *)a)->codigo - ((produto *)b)->codigo;
}

void ordenarEstoque(const estoque * estoque, const int comparador(const void*, const void*)) {
    qsort(estoque->produtos, estoque->tamanho, sizeof(produto), comparador);
}

produto * encontrarProdutoPeloCodigo(const estoque * estoque, const int codProduto) {
    int i;
    for (i = 0; i < estoque->tamanho; i++)
    {
        if(codProduto == estoque->produtos[i].codigo) {
            return &estoque->produtos[i];
        }
    }
    return NULL;
}

estoque * buscarProdutosPeloNome(estoque * _estoque, const char * nome) {
    int i;
    estoque * produtos = criarEstoque();
    produtos->produtos = (produto *) malloc(sizeof(produto) * produtos->capacidade);
    for (i = 0; i < _estoque->tamanho; i++) {
        if(strstr_ignoreCase(_estoque->produtos[i].nome, nome)) {
            if(!adicionarProduto(produtos, _estoque->produtos[i])) {
                break;
            }
            produtos->produtos[i].codigo = _estoque->produtos[i].codigo;
        }
    }
    return produtos;
} 

int baixarEstoque(const estoque * estoque, const int codProduto, const int quantidade) {
    produto * prod = encontrarProdutoPeloCodigo(estoque, codProduto);
    if(!prod || prod->quantidadeEmEstoque < quantidade) {
        return 0;
    }

    prod->quantidadeEmEstoque -= quantidade;
    return 1;
}

int adicionarProduto(estoque * estoque, produto novoProduto) {
    if(estoque->tamanho == estoque->capacidade) {
        estoque->capacidade *= 2;
        estoque->produtos = (produto *) realloc(estoque->produtos, sizeof(produto) * estoque->capacidade);
        if(estoque->produtos == NULL) {
            return 0;
        }
    }
    novoProduto.codigo = estoque->proximoCodigo++;
    estoque->produtos[estoque->tamanho++] = novoProduto;
    return 1;
}

void removerProduto(estoque * estoque, const int codProduto) {
    int i, j;
    for (i = 0; i < estoque->tamanho; i++)
    {
        if(codProduto == estoque->produtos[i].codigo) {
            for (j = i + 1; j < estoque->tamanho; j++)
            {
                estoque->produtos[j - 1] = estoque->produtos[j];
            }
            break;
        }
    }
    estoque->tamanho--;
    if(estoque->tamanho < estoque->capacidade / 3 && estoque->tamanho > 1) {
        estoque->capacidade = estoque->tamanho * 2;
        estoque->produtos = (produto *) realloc(estoque->produtos, sizeof(produto) * estoque->capacidade);
    }
}

int entradaEstoque(const estoque * estoque, const int codProduto, const int quantidade) {
    return baixarEstoque(estoque, codProduto, -quantidade);
}

void imprimirProduto(produto * produto) {
    printf("\n-----Codigo: %4d------------------------\n", produto->codigo);
    printf("Nome: %s\n", produto->nome);
    printf("Quantidade em estoque: %d\n", produto->quantidadeEmEstoque);
    printf("Preco: %.2lf\n", produto->preco);
    printf("-----------------------------------------\n");
}


void liberarAlocacaoEstoque(estoque * estoque) {
    free(estoque->produtos);
    free(estoque);
}
