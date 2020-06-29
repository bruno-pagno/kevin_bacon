/*
Nome: Bruno de Sousa Pagno		NUSP: 11366872
Nome: João Vitor de Mello Gomes	NUSP: 11218622
Professor: Elaine Parros Machado de Sousa
Disciplina: SCC0503
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kevin-bacon.h>

int main() {
	printf("construindo o grafo com o arquivo input-top-grossing.txt\n");
	read_input();
	
	/* Construir o grafo */

	/* Interação com o usuário */
	int result = 0;
	while(result != 3){
		result = show_menu();
		switch (result) {
			case 1:		/* consultar numero de KB */

				break;
			case 2:		/* media e desvio padrao */

				break;
		}
	}

	printf("Finalizando execução e liberando o grafo ... \n");
	return 0;
}

/* Funçoes */
int show_menu() {
	int result = 0;
	while(result < 1 || result > 3) {
		printf("\n");
		printf("|------------------------MENU------------------------|\n");
		printf("|1 - Consultar numero de Kevin Bacon de um ator/atriz|\n");
		printf("|2 - Média / Desvio Padrão do universo Kevin Bacon   |\n");
		printf("|3 - Sair do programa                                |\n");
		printf("|----------------------------------------------------|\n");
		scanf("%d", &result);
	}
	return result;
}

void read_input() {
	FILE *arq_input = fopen("input-top-grossing.txt", "r");
	if(!arq_input) {
		printf("Erro ao abrir arquivo...\n");
		exit(0);
	}

	/* ler as linhas inteiras e armazenar */

	fclose(arq_input);
}