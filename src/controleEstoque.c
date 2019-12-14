#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dadosEstoque.h>
#include <estoque.h>
#include <utilidades.h>
#include <string.h>

void menu();
void darBaixaEstoque(estoque * _estoque);
void listarProdutoPorCodigo(estoque * _estoque);
void listarProdutoPorNome(estoque * _estoque);
void cadastrarProduto(estoque * _estoque);
void pesquisarProduto(estoque * _estoque);
void alterarProduto(estoque * _estoque);
void deletarProduto(estoque * _estoque);

int main(int argc, char const *argv[])
{
    int opcao;
    estoque * _estoque = carregarEstoque();
    do
    {
        menu();
        while(!scanf("%d", &opcao)) {
            flush_in();
            printf("\n\tA opcao precisa ser um numero inteiro!\n");
        }
        switch (opcao)
        {
            case 1:
                darBaixaEstoque(_estoque);
                break;
            case 2:
                listarProdutoPorCodigo(_estoque);
                break;
            case 3:
                listarProdutoPorNome(_estoque);
                break;
            case 4:
                cadastrarProduto(_estoque);
                break;
            case 5:
                pesquisarProduto(_estoque);
                break;
            case 6:
                alterarProduto(_estoque);
                break;
            case 7:
                deletarProduto(_estoque);
                break;
        }
    } while (opcao >= 1 && opcao <= 7);
    
    salvarEstoque(_estoque);

    liberarAlocacaoEstoque(_estoque);

    return 0;
}

void menu() {
    limpar();
    printf("\n\t\t\tControle\n");
    printf("\t\t       de estoque\n\n");
    printf("\t1 - Baixar estoque (Entrada/Saida de produto)\n");
    printf("\t2 - Listar produto por codigo\n");
    printf("\t3 - Listar produto por nome\n");
    printf("\t4 - Cadastrar produto\n");
    printf("\t5 - Pesquisar produto\n");
    printf("\t6 - Alterar produto\n");
    printf("\t7 - Remover produto\n");
    printf("\tInforme outro valor para sair\n");
    printf("\n\n");
}

void darBaixaEstoque(estoque * _estoque) {
    int cod, quantidade;
    char opcao;
    limpar();
    printf("Informe o codigo do produto: ");
    scanf("%d", &cod);
    flush_in();
    
    produto * prod = encontrarProdutoPeloCodigo(_estoque, cod);
    if(prod == NULL) {
        printf("\n\tO produto nao foi encontrado\n");
        pause();
        return;
    
    }

    imprimirProduto(prod);
    
    do
    {
        printf("\nDar baixa neste produto? n - nao  s - sim\n");
        scanf("%c", &opcao);
        opcao = tolower(opcao);
    } while (opcao != 'n' && opcao != 's');
    if(opcao == 'n') {
        return;
    }

    flush_in();
    do
    {
        printf("\nEntrada ou saida de produto? e - entrada  s - saida\n");
        scanf("%c", &opcao);
        opcao = tolower(opcao);
    } while (opcao != 'e' && opcao != 's');
    
    printf("Qual a quantidade de");
    printf(opcao == 'e' ? " entrada: " : " saida: ");
    scanf("%d", &quantidade);
    flush_in();

    int sucesso;

    if(opcao == 'e') {
        sucesso = entradaEstoque(_estoque, cod, quantidade);
    } else {
        sucesso = baixarEstoque(_estoque, cod, quantidade);
    }

    if(sucesso) {
        printf("\n\t\tOperacao realizada com sucesso\n");
    } else {
        printf("\n\t\tErro ao realizar a operacao\n");
    }
    printf("\n");
    imprimirProduto(prod);

    pause();
}

void listarProdutoPorCodigo(estoque * _estoque) {
    int i;
    limpar();
    flush_in();
    ordenarEstoque(_estoque, &compararPorCodigo);
    printf("\tTOTAL DE PRODUTOS: %d\n", _estoque->tamanho);
    for (i = 0; i < _estoque->tamanho; i++)
    {
        imprimirProduto(&_estoque->produtos[i]);
    }
    pause();
}

void listarProdutoPorNome(estoque * _estoque) {
    int i;
    limpar();
    flush_in();
    ordenarEstoque(_estoque, &compararPorNome);
    printf("\tTOTAL DE PRODUTOS: %d\n", _estoque->tamanho);
    for (i = 0; i < _estoque->tamanho; i++)
    {
        imprimirProduto(&_estoque->produtos[i]);
    }
    pause();
}

void cadastrarProduto(estoque * _estoque) {
    limpar();
    flush_in();
    produto _produto;
    lerCampo("Nome do produto: ", _produto.nome, TAMANHO_NOME);
    printf("Estoque inicial: ");
    do
    {
        scanf("%d", &_produto.quantidadeEmEstoque);
    } while (_produto.quantidadeEmEstoque < 0);
    printf("Preco: ");
    do
    {
        scanf("%lf", &_produto.preco);
    } while (_produto.preco < 0);
    if(adicionarProduto(_estoque, _produto)) {
        printf("\t\tProduto cadastrado com sucesso!\n");
    } else {
        printf("\t\tNao foi possivel cadastrar o produto\n");
    }
    pause();
    limpar();
}

void pesquisarProduto(estoque * _estoque) {
    char nome[TAMANHO_NOME];
    int i;

    limpar();
    
    flush_in();
    printf("\n\tTOTAL DE PRODUTOS CADASTRADOS: %d\n", _estoque->tamanho);
    lerCampo("\nPesquisar (por nome): ", nome, TAMANHO_NOME);

    estoque * produtos = buscarProdutosPeloNome(_estoque, nome);
    
    if(produtos == NULL) {
        printf("\n\tProduto nao encontrado\n");
    } else {
        printf("\n\n\tENCONTRADOS %d PRODUTOS PARA O NOME: %s\n\n", produtos->tamanho, nome);
        for(i = 0; i < produtos->tamanho; i++) {
            imprimirProduto(&produtos->produtos[i]);
        }
        printf("\n\n");
        liberarAlocacaoEstoque(produtos);
    }
    pause();

}


void alterarProduto(estoque * _estoque) {
    int cod;
    char opcao;
    limpar();
    printf("Informe o codigo do produto: ");
    scanf("%d", &cod);
    flush_in();

    produto * _produto = encontrarProdutoPeloCodigo(_estoque, cod);
    if(_produto == NULL) {
        printf("\n\tO produto nao foi encontrado\n");
        pause();
        return;
    
    }
    imprimirProduto(_produto);
    
    do
    {
        printf("\nEditar este produto? n - nao  s - sim\n");
        scanf("%c", &opcao);
        opcao = tolower(opcao);
    } while (opcao != 'n' && opcao != 's');
    if(opcao == 'n') {
        return;
    }

    flush_in();
    lerCampo("Informe o novo nome do produto: ", _produto->nome, TAMANHO_NOME);
    
    printf("Informe o novo preco: ");
    do
    {
        scanf("%lf", &_produto->preco);
    } while (_produto->preco < 0);
    flush_in();
    printf("\nProduto editado com sucesso\n");
    pause();
}


void deletarProduto(estoque * _estoque) {
    int cod;
    char opcao;
    limpar();
    printf("Informe o codigo do produto: ");
    scanf("%d", &cod);
    flush_in();
    
    produto * _produto = encontrarProdutoPeloCodigo(_estoque, cod);
    if(_produto == NULL) {
        printf("\n\tO produto nao foi encontrado\n");
        pause();
        return;
    
    }

    imprimirProduto(_produto);
    
    do
    {
        printf("\nApagar este produto? n - nao  s - sim\n");
        scanf("%c", &opcao);
        opcao = tolower(opcao);
    } while (opcao != 'n' && opcao != 's');
    if(opcao == 'n') {
        return;
    }

    removerProduto(_estoque, cod);
    
    flush_in();
    pause();
}