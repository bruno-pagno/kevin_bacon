/*
Nome: Bruno de Sousa Pagno		NUSP: 11366872
Nome: João Vitor de Mello Gomes	NUSP: 11218622
Professor: Elaine Parros Machado de Sousa
Disciplina: SCC0503
*/

#include <stdio.h>
#include <stdlib.h>
#include <kevin-bacon.h>

int main () {

    printf("construindo o grafo com o arquivo input-top-grossing.txt\n");
    // Construir o grafo


    // Interação com o usuário
    int result = 1;
    while(result == 1 || result == 2){
        result = showMenu();
        if(result == 1) {
            printf("fazer algo 1\n");
        } else if(result == 2) {
            printf("fazer algo 2\n");
        }
    }

    printf("Finalizando execução e liberando o grafo ... \n");
    return 0;
}

// Funçoes
int showMenu() {
    printf("|---------------------------------------------------|\n");
    printf("|1- Consultar numero de Kevin Bacon de um ator/atriz|\n");
    printf("|2- Média / Desvio Padrão do universo Kevin Bacon   |\n");
    printf("|3- Sair do programa                                |\n");
    printf("|---------------------------------------------------|\n");
    int result;
    scanf("%d", &result);
    return result;
}