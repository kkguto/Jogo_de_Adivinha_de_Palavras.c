#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

int i;

char* palavras(const char *nome_arquivo){
	
	FILE *arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        printf("\n\tErro ao abrir o arquivo");
        return NULL;
    }

    char palavras[100][60];
    int total_palavras = 0;

    while (fscanf(arquivo, "%s", palavras[total_palavras]) != EOF) {
        total_palavras++;
    }
    fclose(arquivo);
    
    if(total_palavras == 0){
    	printf("\n\tO arquivo está vazio.\n");
    	return NULL;
	}

    srand(time(NULL));
    
    int indice = rand() % total_palavras;
    char *palavra_escolhida = malloc(strlen(palavras[indice] + 1));
    
    if (palavra_escolhida == NULL) {
        printf("\n\tErro ao alocar memória.\n");
        return NULL;
    }
    strcpy(palavra_escolhida, palavras[indice]);
    
    return palavra_escolhida;	
}

void jogo(const char* palavra_secreta){
	
    int tam = strlen(palavra_secreta);
    char resposta[tam + 1];
    
    for(i = 0; i < tam; i++){
        resposta[i] = '_';
    }
    resposta[tam] = '\0';
    
    char chute;
    int acertos = 0;
    int tentativas = 0;

    while (true){
    	
    	sleep(1);
    	system("cls");
		
        printf("\n\tPalavra: ");
        for(i = 0; i < tam; i++){
            printf("%c ", resposta[i]);
        }

        printf("\n\tTente um letra (caso queira ver se tem espaçamento, digite - ): ");
        scanf(" %c", &chute);

        int letra_rept = true;

        for(i = 0; i < tam; i++){
            if(chute == palavra_secreta[i]){
                if(resposta[i] == '_'){
                    resposta[i] = chute;
                    acertos++;
                    letra_rept = false;
                }
            }
        }

        if(letra_rept){
            printf("\n\tEssa letra não tem na palavra ou ja foi usada.\n");
        }

		tentativas++;
		
        if(acertos == tam){
            printf("\n\tParabÃ©ns! VocÃª adivinhou a palavra em %d tentativas: %s\n", tentativas, palavra_secreta);
            break;
        }
    }
}

int main(){
	
	setlocale(LC_ALL, "");
	
	bool continuar = true;
	int escolha;
	
	do{
		
		printf("\n\t  MENU PARA O JOGO");
		printf("\n\t====================");
		printf("\n\t [1] Frutas");
		printf("\n\t [2] Países");
		printf("\n\t [3] Filmes");
		printf("\n\n\t [0] Encerrar");
		printf("\n\t====================");
		printf("\n\t Sua escolha é: ");
		scanf("%d", &escolha);
		
		if(escolha == 0){
			printf("\n\tEncerrado!");
			continuar = false;
		}else if(escolha == 1){
			char *palavra_secreta = palavras("frutas.txt");
			
			if(palavra_secreta != NULL){
				jogo(palavra_secreta);
				free(palavra_secreta);
			}
		}else if(escolha == 2){
			char *palavra_secreta = palavras("paises.txt");
			
			if(palavra_secreta != NULL){
				jogo(palavra_secreta);
				free(palavra_secreta);
			}
		}else if(escolha == 3){
			char *palavra_secreta = palavras("filmes.txt");
			
			if(palavra_secreta != NULL){
				jogo(palavra_secreta);
				free(palavra_secreta);
			}
		}else{
			printf("\n\tOpçao Invalida.\n");
		}
		
	}while(continuar);


    return 0;
}
