cmake_minimum_required(VERSION 3.13)

project("Controle de estoque")

add_library(utilidades src/utilidades.c include/utilidades.h)

add_library(estoque src/estoque.c include/estoque.h)
target_include_directories(estoque PUBLIC include)

add_library(dadosEstoque src/dadosEstoque.c include/dadosEstoque.h)

target_link_libraries(dadosEstoque PUBLIC estoque utilidades)

add_executable(controleEstoque src/controleEstoque.c)

target_link_libraries(controleEstoque dadosEstoque estoque utilidades)
