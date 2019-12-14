#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limpar() {
    #ifdef unix
    system("clear");
    #elif _WIN32
    system("cls");
    #endif
}

void pause() {
    #ifdef unix
    printf("Pressione ENTER para continuar...");
    fgetc(stdin);
    #elif _WIN32
    system("pause");
    #endif
}

void removerQuebraLinha(char * string) {
    int ch = 0;
    while (string[ch] != '\0')
    {
        if(string[ch] == '\n') {
            string[ch] = '\0';
        }
        ch++;
    }
}

void flush_in() {
    int ch;
    while(!feof(stdin) && (ch = fgetc(stdin)) && ch != '\n');
}

void lerCampo(const char * mensagem, char * campo, const int tamanho) {
    printf("%s", mensagem);
    fgets(campo, tamanho, stdin);
    removerQuebraLinha(campo);
}

int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}

void str_tolower(const char * string, const int lenght, char * lowerString) {
    int i;
    for (i = 0; i < lenght; i++)
    {
        lowerString[i] = tolower(string[i]);
    }
}

int strcmp_ignoreCase(const char * stringA, const char * stringB) {
    int lenghtA = strlen(stringA);
    int lenghtB = strlen(stringB);
    char lowerA[lenghtA];
    char lowerB[lenghtB];
    str_tolower(stringA, lenghtA, lowerA);
    str_tolower(stringB, lenghtB, lowerB);

    return strcmp(lowerA, lowerB);
}

char * strstr_ignoreCase(const char * string, const char * substring) {
    int lenghtA = strlen(string);
    int lenghtB = strlen(substring);
    char lowerA[lenghtA];
    char lowerB[lenghtB];
    str_tolower(string, lenghtA + 1, lowerA);
    str_tolower(substring, lenghtB + 1, lowerB);

    return strstr(lowerA, lowerB);
}