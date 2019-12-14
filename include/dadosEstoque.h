#ifndef DADOS_ESTOQUE_H
#define DADOS_ESTOQUE_H

#include <estoque.h>

#define ARQUIVO_ESTOQUE "estoque.dat"

estoque * carregarEstoque();
void salvarEstoque(const estoque * _estoque);

#endif