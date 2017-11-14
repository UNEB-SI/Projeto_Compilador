#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Analex.h"

PR TabelaPR[]={

	{.lexema = "semretorno"},
	{.lexema = "caracter"},
	{.lexema = "inteiro"},
	{.lexema = "real"},
	{.lexema = "booleano"},
	{.lexema = "semparam"},
	{.lexema = "se"},
	{.lexema = "senao"},
	{.lexema = "enquanto"},
	{.lexema = "para"},
	{.lexema = "retorne"},
	{.lexema = "prototipo"}
};

int contLinha = 1;
int indice = 0;

void Analex(FILE *FD){



int estado = 0,cont = 0;
int c,comentario;
//ID *aux;

t=tnext;

	while(1){

		c = fgetc(FD);

		switch(estado){

			case 0:

				if(feof(FD)){

					estado = 1;

				}else if(c == ' '){

					estado = 0;

				}else if(c== isspace(c)){

					estado = 0;

				}else if(c== '\t'){

					estado = 0;

				}else if (c == '\n'){ //Enter

					estado = 0;
					contLinha++;

				}else if(isalpha(c)){ //Letra

					estado = 2;
					tnext.lexema[cont++] = c;

				}else if(isdigit(c)){ //Digito

					estado = 4;
					tnext.digito[cont++] = c;

				}else if(c == '<'){

					estado = 9;

				}else if(c == '>'){

					estado = 13;

				}else if(c == ';'){

					tnext.cat = SINAL;
					tnext.codigo = PTO_VIRGULA;
					return;

				}else if(c == '+'){

					tnext.cat = SINAL;
					tnext.codigo = MAIS;
					return;

				}else if(c == '-'){

					tnext.cat = SINAL;
					tnext.codigo = MENOS;
					return;

				}else if(c == '*'){

					tnext.cat = SINAL;
					tnext.codigo = ASTERISCO;
					return;

				}else if(c == '='){

					estado = 21;

				}else if(c == '/'){

					estado = 24;

				}else if(c == '|'){

					estado = 29;

				}else if(c == '&'){

					estado = 31;

				}else if(c == '!'){

					estado = 33;

				}else if(c == '('){

					tnext.cat = SINAL;
					tnext.codigo = ABRE_PAR;
					return;

				}else if(c == ')'){

					tnext.cat = SINAL;
					tnext.codigo = FECHA_PAR;
					return;

				}else if(c == '{'){

					tnext.cat = SINAL;
					tnext.codigo = ABRE_CHAVE;
					return;

				}else if(c == '}'){

					tnext.cat = SINAL;
					tnext.codigo = FECHA_CHAVE;
					return;

				}else if(c == ','){

					tnext.cat = SINAL;
					tnext.codigo = VIRGULA;
					return;

				}else if(c == 39){

					estado = 41;

				}else if(c == '"'){

					estado = 44;
					tnext.cat = CT_L;
					tnext.codigo = indice;

				}else{

					printf("\n\nCaracter nao-valido na linha %d : %c\n",contLinha,c);
					system("pause");
					exit(-2);
				}
				break;

			case 1:

				tnext.cat = FIM_ARQ;
				tnext.codigo = 0;
				return;

				break;

			case 2:

				if((isalpha(c)) || (c == '_') || (isdigit(c))){

					estado = 2;
					tnext.lexema[cont++] = c;

				}else{

					tnext.lexema[cont]='\0';
					ungetc(c,FD);
					int i;

					for(i=0;i<NumeroPR;i++){

						if(!(strcmp(tnext.lexema,TabelaPR[i].lexema))) {

							tnext.cat = PALAVRA_RES;
							tnext.codigo = i;

							return;
						}
					}

						/*
					aux = inicio;


					while (aux->prox != NULL){

						if(strcmp(tnext.lexema,aux->lexema)==0){

							tnext.cat = IDENTIFICADOR;
							return;
						}
						aux = aux->prox;
					}

					aux->prox = (ID *) malloc(sizeof(ID));
					aux = aux->prox;
					aux->prox = NULL;

					strcpy(aux->lexema,tnext.lexema);
					tnext.cat = IDENTIFICADOR;
					return;*/

					tnext.cat = IDENTIFICADOR;
					return;
				}
				break;

			case 4:

				if(isdigit(c)){ //se for numero
					estado = 4;
					tnext.digito[cont++] = c;
				}else if (c == '.'){
					estado = 5;
					tnext.digito[cont++] = c;
				}else{
					ungetc(c,FD);
					tnext.digito[cont] = '\0';
					tnext.cat = CT_INT;
					tnext.valor_I = atoi(tnext.digito);
					return;
				}

				break;

			case 5:

				if(isdigit(c)){
					estado = 6;
					tnext.digito[cont++] = c;
				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;

			case 6:

				if(isdigit(c)){
					estado = 6;
					tnext.digito[cont++] = c;
				}else{
					ungetc(c,FD);
					tnext.cat = CT_REAL;
					tnext.valor_R = atof(tnext.digito);
					return;
				}

				break;

			case 9:

				if(c == '='){
					estado = 11;
					tnext.cat = SINAL;
					tnext.codigo = MENOR_IGUAL;
					return;
				}else{
					ungetc(c,FD);
					tnext.cat = SINAL;
					tnext.codigo = MENOR;
					return;
				}

				break;

			case 13:

				if(c == '='){
					estado = 11;
					tnext.cat = SINAL;
					tnext.codigo = MAIOR_IGUAL;
					return;
				}else{
					ungetc(c,FD);
					tnext.cat = SINAL;
					tnext.codigo = MAIOR;
					return;
				}

				break;

			case 21:

				if(c == '='){

					tnext.cat = SINAL;
					tnext.codigo = IGUAL_IGUAL;
					return;

				}else{

					ungetc(c,FD);
					tnext.cat = SINAL;
					tnext.codigo = IGUAL;
					return;
				}

				break;

			case 24:

				if(c == '*'){

					estado = 25;
					comentario = contLinha;
				}else{

					ungetc(c,FD);
					tnext.cat = SINAL;
					tnext.codigo = BARRA;
					return;

				}

				break;

			case 25:

				if(c == '*') estado = 26;
				if(c== '\n') contLinha++;
				if (feof(FD)){
					printf("Erro na linha %d \n",comentario);
					system("pause");
					exit(-10);
				}

				break;

			case 26:

				if(c == '/'){

					estado = 0;
				}else{
					estado = 25;
				}
				break;

			case 29:

				if(c == '|'){

					tnext.cat = SINAL;
					tnext.codigo = OU;
					return;
				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;


			case 31:

					if(c == '&'){

					tnext.cat = SINAL;
					tnext.codigo = E;
					return;
				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;


			case 33:

				if(c == '='){

					tnext.cat = SINAL;
					tnext.codigo = DIFERENTE;
					return;
				}else{

					ungetc(c,FD);
					tnext.cat = SINAL;
					tnext.codigo = NEGACAO;
					return;
				}

				break;

			case 41:

				if((isprint(c)) && ((c != 39) && (c != 92))){ // 92 � barra invertida

					tnext.cat = CT_C;
					tnext.codigo = c;
					estado = 43;

				} else if((c == '\\')&& ((c != 39))){ //39 � apostrofo
				    estado = 47;
				}else{
					printf("erro na linha %d :[%c]",contLinha,c);
					system("pause");
					exit(-3);
				}

				break;

			case 43:

				if(c == 39){ //Ap�strofo

					return;
				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;

			case 44:

				if((isprint(c)) && (c != '"') && (c != '\n')){

					//CL[indice++] = c;
					tnext.lexema[cont++] = c;

				}else if(c == '"'){

					//CL[indice++] = '\0';
					tnext.lexema[cont++] = '\0';
					strcpy(CL[indice],tnext.lexema);
					indice++;
					return;

				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;

			case 47:

                if(c == 'n'){

                    tnext.cat = CT_C;
					tnext.codigo = '\n';
					estado = 43;

				}else if(c == '0'){

					tnext.cat = CT_C;
					tnext.codigo = '\0';
					estado = 43;

                }else{

                    printf("erro na linha %d :[%c]",contLinha,c);
					system("pause");
					exit(-3);

                }

				break;

		}
	}
}
