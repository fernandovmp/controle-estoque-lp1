#ifndef ESTOQUE_H
#define ESTOQUE_H

#define TAMANHO_NOME 30

typedef struct produto
{
    int codigo;
    char nome[TAMANHO_NOME];
    int quantidadeEmEstoque;
    double preco;
} produto;

typedef struct estoque
{
    int capacidade;
    int tamanho;
    produto * produtos;
    int proximoCodigo;
} estoque;

estoque * criarEstoque();
int compararPorNome(const void * a, const void * b);
int compararPorCodigo(const void * a, const void * b);
void ordenarEstoque(const estoque * estoque, const int comparador(const void*, const void*));
produto * encontrarProdutoPeloCodigo(const estoque * estoque, const int codProduto);
estoque * buscarProdutosPeloNome(estoque * _estoque, const char * nome);
int baixarEstoque(const estoque * estoque, const int codProduto, const int quantidade);
int adicionarProduto(estoque * estoque, produto novoProduto);
void removerProduto(estoque * estoque, const int codProduto);
int entradaEstoque(const estoque * estoque, const int codProduto, const int quantidade);
void imprimirProduto(produto * produto);
void liberarAlocacaoEstoque(estoque * estoque);

#endif