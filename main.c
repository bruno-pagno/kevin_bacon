/*
Nome: Bruno de Sousa Pagno		NUSP: 11366872
Nome: João Vitor de Mello Gomes	NUSP: 11218622
Professor: Elaine Parros Machado de Sousa
Disciplina: SCC0503
*/

/*
OBSERVAÇÕES:
    criei esse main.c pras funcoes entre os .h

	o valor das arestas vai ser o titulo do filme
	o valor dos vértices vai ser o nome do ator
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kevin_bacon.h>

#define DEBUG 1

int show_menu();
void read_inputs();

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
	/* liberar grafo */
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

	while(1) {
		char line[2000];
		strcpy(line, "");
		int i = 0;

		/* leitura das linhas por completo */
		char aux;
		while(fscanf(arq_input, "%c", &aux) != EOF && aux != '\n')
			line[i++] = aux;
		line[i] = '\0';

		if(i == 0) break;

		if(DEBUG)
			printf("[%d] %s\n", i, line);	/* linha toda */

		char *movie_name = strtok(line, "/");

		char *actor_name = strtok(NULL, "/");
		while(actor_name) {
			if(DEBUG)
				printf("\t%s\n", actor_name);

			/* faz alguma coisa aqui */
			
			actor_name = strtok(NULL, "/");
		}

		printf("\n");
	}

	fclose(arq_input);
}