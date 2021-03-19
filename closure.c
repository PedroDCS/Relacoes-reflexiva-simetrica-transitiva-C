/*************************************************************************************************/
/*** Nome do aplicativo: Closure	**************************************************************/
/*************************************************************************************************/
/********************* Instruçoes para compilação e execução do programa *************************/
/*
		1.	Para compilar o arquivo, deve-se usar o compilador gcc do linux.
		2.	Usando o terminal, passe o seguinte comando:
		3.	gcc closure.c -o <nome do programa que sera gerado>
		4.	Exemplo:  gcc closure.c -o teste
		5.	Caso nao tenha ocorrido nenhum erro, o arquivo teste sera gerado
		6.	Para executar-lo, devera usar o seguinte comando
		7.	 ./<nome do programa que sera gerado> <arquivo-entrada> <nome do arquivo de saida>
		8.	Exemplo: ./teste relacao01.txt fecho
		9.	se tudo correr bem, os arquivos de saida com os fechos serao gerados.
*/
/*************************************************************************************************/
/*****  Ambiente(s) de Desenvolvimento utilizado(s): Dev-C++ 5.11 e	NetBeans IDE 8.2 *************/
/*************************************************************************************************/
/***** Data de inicio da implementação do codigo: 10/11/2017 *************************************/
/***** Data de verificação final do codigo: 28/11/2017 *******************************************/
/*************************************************************************************************/
/********** Algoritimo para verificar se a relação é reflexiva, simetrica e transitiva ***********/
/******* e caso nao atenda uma dessas propiedades, deve-se gerar seo feixo correspondente ********/
/*************************************************************************************************/
/*************************************************************************************************/
/***** Nome: Pedro Daniel Camargos Soares 					Matricula: 0020640	******************/
/*************************************************************************************************/
/***** Nome: Lucas Gabriel de Almeida		 				Matricula: 0035333	******************/
/*************************************************************************************************/
/*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int VerificaReflexiva = 0;
int VerificaSimetrica = 0;
int VerificaTransitiva = 0;

int i, j;
int **P_matriz; //Matriz

int entrada_de_dados(int argc, char** argv){
	
	//Define as variaveis
	int n, r1=0, r2 = 0; //n = dimensao da matriz / r1 e r2 sao os arcos
	char c; // letra
	
		
	FILE *P_entrada; //Ponteiro que aponta para o arquivo	
	P_entrada = fopen(argv[1],"r"); //Abre o arquivo
	
	if(P_entrada == NULL){ //verifica se o arquivo pode ser aberto
		printf("Arquivo nao pode ser aberto\n");		
		return 0;
	}
	
	fscanf(P_entrada, "%c %i", &c, &n); //Le a primeira linha do arquivo e recebe a dimensao da matriz

		
	/************************* GERA A MATRIZ **************************/
	P_matriz = malloc(n * sizeof(int*)); //Aloca dinamicamente uma matriz	
	//Define as linhas da matriz
	for(i=0; i<n; i++){
		//Define as colunas da matriz
		P_matriz[i] = malloc(n * sizeof(int));
		for(j=0; j<n; j++){
			P_matriz[i][j] = 0;
		}		
	}	
		
	do{ //Le todo o arquivo ate que a constante char seja igual a F (que simboliza o fim do arquivo)
		fscanf(P_entrada,"\n%c %i %i", &c, &r1, &r2);
		
		//Seta os arcos na matriz
		P_matriz[r1-1][r2-1] = 1; /* Os valores r1 e r2 necessitam ser subtraidos por 1, para assim, armazer os arcos nas posicoes corretas.(Pois em c, o vetor se inicia no 0) */
		
	} while(c != 'f');
	
	fclose(P_entrada); //Fecha o arquivo
		
		
	verifica_relacao_reflexiva(n, argv);
	
}

int verifica_relacao_reflexiva(int n, char** argv){ /* Funcao que verifica a propriedade reflexiva, recebe como parametro a dimencao da matriz */
	
	/* Define as variaveis */
	int i, verifica = 1; 
	
	
	for(i=0; i<n; i++){
		
		if (P_matriz[i][i] == 0){ /* Verifica a diagonal principal da matriz, se ouver algum 0 a relacao nao e reflexiva. Em seguida chama a funcao que adicionara os fechos reflexivos */	
			verifica = 0;			
			
		} 
		
	} 

	
	if (verifica == 0){ /* Caso a variavel flag for igual a 0, seta a variavel global como 1. A variavel global sera usada para calcular o fecho */
		VerificaReflexiva = 1;
	} 
	
	verifica_relacao_simetrica(n, argv); /* Chama a funcao que verifica se a relacao e simetrica */
	
}

int verifica_relacao_simetrica(int n, char** argv){ /* Funcao que verifica a propriedade simetrica, recebe como parametro a dimencao da matriz  */
	
	/* Define as variaveis */
	int i, j, verifica, soma;

	verifica = 1;
	soma = 0;

	for(i=0; i<n; i++){
		
		for(j=0; j<n; j++){
			
			if (P_matriz[i][j] == 1) { /* Verifica o arco de ida */
				
				if (P_matriz[j][i] == 0){ /* Verifica o arco de volta, se o arco de voltar for 0 a relacao nao e simetrica, em seguida chama a funcao que adicionara os fechos simetricos */
					
					verifica = 0;
					
				}
				
			}
			
			if (i != j){
				//verifica essa bagaÃ§a				
				soma = soma + P_matriz[i][j];
				
			}
			
		}
		
	}
	
	if (soma == 0){
		
		verifica = 0;
				
	}
	
	if (verifica == 0){ /* Caso a variavel flag for igual a 0, seta a variavel global como 1. A variavel global sera usada para calcular o fecho */
		VerificaSimetrica = 1;
				
	}
	
		verifica_relacao_transitiva(n, argv); /* Chama a funcao que verifica se a relacao e transitiva */
	
}

int verifica_relacao_transitiva(int n, char** argv){ /* Funcao que verifica a propriedade transitiva, recebe como parametro a dimencao da matriz  */
	
	/* Define as variaveis */
	int i, j, k, verifica=1, soma = 0;
	
	for(i=0; i<n; i++){
		
		for(j=0; j<n; j++){
			
			for(k=0; k<n; k++){
				
				if ((P_matriz[i][j] == 1) && (P_matriz[j][k] == 1)){ /* Verifica se existe um arco de ida de a para b e de b para c */					

					if (P_matriz[i][k] == 0){ /* Verifica se existe um arco de ida de a para c */	
										
					verifica=0;												
						
					}
				}				
			}			
		}		
	}
	
	if(verifica == 0){ /* Caso a variavel flag for igual a 0, seta a variavel global como 1. A variavel global sera usada para calcular o fecho */						
		VerificaTransitiva = 1;
				
	}
	
	fecho_reflexivo(n, argv); /* Chama a funcao que adiciona o fecho reflexivo */
	
}

int fecho_reflexivo(int n, char** argv){ /* Funcao que adiciona os fechos reflexivos, recebe como parametro a dimencao da matriz  */
	
	if (VerificaReflexiva == 1){
		
		/**********************************************************************************/
		/******************************* Define as variaveis ******************************/
		/**********************************************************************************/
		int **mat_fecho, i,j;
		
		/**********************************************************************************/	
		/******************* Abaixo, a matriz de entrada sera espelhada *******************/
		/**********************************************************************************/
		mat_fecho = malloc(n * sizeof(int *)); //Aloca dinamicamente uma matriz.
	
		//Define as linhas da matriz
		for(i=0; i<n; i++){
		
			//Define as colunas
			mat_fecho[i] = malloc(n * sizeof(int));
			for(j=0; j<n; j++){
				mat_fecho[i][j] = P_matriz[i][j]; //Espelha a matriz
			
			}		
		}
		
		/************************ ADICIONA O ARQUIVO DE SAIDA CONTENDO OS FECHOS REFLEXIVOS ***********************/
	
		//Abre o arquivo TXT
		char dot[9] = "-ref.dot"; 
		char saida[24];
	
		FILE *P_saida; //Ponteiro que aponta para o arquivo
		strcpy (saida,argv[2]); //Define o valor para a string
		strcat (saida,dot); //Junta as duas strings
		P_saida = fopen(saida,"w"); //Abre o arquivo
	
		fprintf(P_saida,"digraph fecho\n"); //Escreve a primeira linha do arquivo fecho
		fprintf(P_saida,"{\n"); //Escreve o caractere {
		
		for(i=0; i<n; i++){ //Escreve todos os componentes do grafo
			fprintf(P_saida,"\t%d;\n",i+1);
		}
	
		for(i=0; i<n; i++){ //Escreve os arcos da matriz no arquivo
			for(j=0; j<n; j++){
				if(P_matriz[i][j] == 1){
					fprintf(P_saida,"\t%d -> %d;\n",i+1,j+1);
				}
			}
		}
	
		/**********************************************************************************/	
		/*************************** Inicia a adicao dos fechos ***************************/
		/**********************************************************************************/
		
		for(i=0; i<n; i++){
			
				if(mat_fecho[i][i] == 0){ //Verifica a diagonal principal, se for 0 adiciona o novo valor.
				
					fprintf(P_saida,"\t%d -> %d [color=red];\n",i+1,i+1); //Adiciona o fecho no arquivo de saida
					mat_fecho[i][i] = 1;					
				}
			
		}
		
	fprintf(P_saida,"}");//Escreve o caractere }
	fclose(P_saida); // Fecha o arquivo	
		
	}
	fecho_simetrico(n, argv);
}

int fecho_simetrico(int n, char** argv){ /* Funcao que adiciona os fechos simetricos, recebe como parametro a dimencao da matriz  */
	
	if (VerificaSimetrica == 1){
		
		/**********************************************************************************/
		/******************************* Define as variaveis ******************************/
		/**********************************************************************************/
		int **mat_fecho, i,j;
	
		/**********************************************************************************/	
		/******************* Abaixo, a matriz de entrada sera espelhada *******************/
		/**********************************************************************************/
		mat_fecho = malloc(n * sizeof(int *)); //Aloca dinamicamente uma matriz.
		
		//Define as linhas da matriz
		for(i=0; i<n; i++){
		
			//Define as colunas
			mat_fecho[i] = malloc(n * sizeof(int));
			for(j=0; j<n; j++){
				mat_fecho[i][j] = P_matriz[i][j]; //Espelha a matriz
			
			}		
		}
		
		/************************ ADICIONA O ARQUIVO DE SAIDA CONTENDO OS FECHOS SIMETRICOS ***********************/
		
		//Abre o arquivo TXT
		char dot[9] = "-sim.dot"; 
		char saida[24];
		
		FILE *P_saida; //Ponteiro que aponta para o arquivo
		strcpy (saida,argv[2]); //Define o valor para a string
		strcat (saida,dot); //Junta as duas strings
		P_saida = fopen(saida,"w"); //Abre o arquivo
			
		fprintf(P_saida,"digraph fecho\n"); //Escreve a primeira linha do arquivo fecho
		fprintf(P_saida,"{\n"); //Escreve o caractere {
		
		for(i=0; i<n; i++){ //Escreve todos os componentes do grafo
			fprintf(P_saida,"\t%d;\n",i+1);
		}
	
		for(i=0; i<n; i++){ //Escreve os arcos da matriz no arquivo
			for(j=0; j<n; j++){
				if(P_matriz[i][j] == 1){
					fprintf(P_saida,"\t%d -> %d;\n",i+1,j+1);
				}
			}
		}
	
		
		/**********************************************************************************/	
		/*************************** Inicia a adicao dos fechos ***************************/
		/**********************************************************************************/
	
		for(i=0; i<n; i++){
		
			for(j=0; j<n; j++){
			
				if(P_matriz[i][j] == 1 && P_matriz[j][i] == 0){ //Verifica a existencia de um arco;	
				
						fprintf(P_saida,"\t%d -> %d [color=red];\n",j+1,i+1); //Adiciona o fecho no arquivo de saida
						mat_fecho[j][i] = 1;
						
				}
								
			}
		}
				
	fprintf(P_saida,"}");//Escreve o caractere }
	fclose(P_saida); // Fecha o arquivo	
		
	}
	
	fecho_transitivo(n, argv);
	
}

int fecho_transitivo(int n, char** argv){/* Funcao que adiciona os fechos transitivos, recebe como parametro a dimencao da matriz  */
	
	if (VerificaTransitiva == 1){
	
		/**********************************************************************************/
		/******************************* Define as variaveis ******************************/
		/**********************************************************************************/
		int **mat_fecho, i, j, k, houve_inclusao;
	
		/**********************************************************************************/	
		/******************* Abaixo, a matriz de entrada sera espelhada *******************/
		/**********************************************************************************/
		mat_fecho = malloc(n * sizeof(int *)); //Aloca dinamicamente uma matriz.
	
		//Define as linhas da matriz
		for(i=0; i<n; i++){
			
			//Define as colunas
			mat_fecho[i] = malloc(n * sizeof(int));
			for(j=0; j<n; j++){
				mat_fecho[i][j] = P_matriz[i][j]; //Espelha a matriz
				
			}		
		}
		
		/************************ ADICIONA O ARQUIVO DE SAIDA CONTENDO OS FECHOS REFLEXIVOS ***********************/
	
		//Abre o arquivo TXT
		char dot[9] = "-tra.dot"; 
		char saida[24];
	
		FILE *P_saida; //Ponteiro que aponta para o arquivo
		strcpy (saida,argv[2]); //Define o valor para a string
		strcat (saida,dot); //Junta as duas strings
		P_saida = fopen(saida,"w"); //Abre o arquivo
		
		fprintf(P_saida,"digraph fecho\n"); //Escreve a primeira linha do arquivo fecho
		fprintf(P_saida,"{\n"); //Escreve o caractere {
		
		for(i=0; i<n; i++){ //Escreve todos os componentes do grafo
			fprintf(P_saida,"\t%d;\n",i+1);
		}
	
		for(i=0; i<n; i++){ //Escreve os arcos da matriz no arquivo
			for(j=0; j<n; j++){
				if(P_matriz[i][j] == 1){
					fprintf(P_saida,"\t%d -> %d;\n",i+1,j+1);
				}
			}
		}
	
		/**********************************************************************************/	
		/*************************** Inicia a adicao dos fechos ***************************/
		/**********************************************************************************/
					
				
		do { //Estrutura que ira repetir a acao ate parar de haver adicao de fechos.
		
			houve_inclusao = 0; // Variavel flag que ira verificar a necessidade de repetir o laco de repeticao.
		
			for(i=0; i<n; i++){
				for(j=0; j<n; j++){
					for(k=0; k<n; k++){
						
						if(P_matriz[i][j] == 1 && P_matriz[j][k] == 1 && P_matriz[i][k] == 0){
							mat_fecho[i][k] = 2;//seta como 2 pra diferenciar o feixo das relacoes jÃ¡ existentes
							houve_inclusao = 1;						
						}
					}
				}
			}
		} while (houve_inclusao == 0);
		
			for(i=0; i<n; i++){
					for(k=0; k<n; k++){
											
						if(	mat_fecho[i][k] == 2){
							
								fprintf(P_saida,"\t%d -> %d [color=red];\n",i+1,k+1); //Adiciona o fecho no arquivo de saida
								
						}								
						
					}
				
			}		
			
		fprintf(P_saida,"}");//Escreve o caractere }
		fclose(P_saida); // Fecha o arquivo	
	}
	
}

	
	return (EXIT_SUCCESS);
}


