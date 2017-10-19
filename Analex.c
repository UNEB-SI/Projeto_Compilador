#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Analex.h"


int contLinha = 0;


token AnalisadorLexico(FILE *FD){

int estado = 0,cont = 0;
int c;
token t;
ID *aux;

	if(inicio == NULL){
		inicio = (ID *) malloc(sizeof(ID)); //Necessário para criar uma tabela de Identificadores (Lista encadeada)
		inicio->prox = NULL;
	}

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
					t.lexema[cont++] = c;

				}else if(isdigit(c)){ //Digito

					estado = 4;
					t.digito[cont++] = c;

				}else if(c == '<'){

					estado = 9;

				}else if(c == '>'){

					estado = 13;

				}else if(c == ';'){

					t.cat = SINAL;
					t.codigo = PTO_VIRGULA;
					return t;

				}else if(c == '+'){

					t.cat = SINAL;
					t.codigo = MAIS;
					return t;

				}else if(c == '-'){

					t.cat = SINAL;
					t.codigo = MENOS;
					return t;

				}else if(c == '*'){

					t.cat = SINAL;
					t.codigo = ASTERISCO;
					return t;

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

					t.cat = SINAL;
					t.codigo = ABRE_PAR;
					return t;

				}else if(c == ')'){

					t.cat = SINAL;
					t.codigo = FECHA_PAR;
					return t;

				}else if(c == '{'){

					t.cat = SINAL;
					t.codigo = ABRE_CHAVE;
					return t;

				}else if(c == '}'){

					t.cat = SINAL;
					t.codigo = FECHA_CHAVE;
					return t;

				}else if(c == ','){

					t.cat = SINAL;
					t.codigo = VIRGULA;
					return t;

				}else if(c == 39){

					estado = 41;

				}else if(c == '"'){

					estado = 44;
					t.cat = CT_L;
					t.codigo = indice;

				}else{

					printf("\n\nCaracter nao-valido na linha %d : %c\n",contLinha,c);
					system("pause");
					exit(-2);
				}
				break;

			case 1:

				t.cat = FIM_ARQ;
				t.codigo = 0;
				return t;

				break;

			case 2:

				if((isalpha(c)) || (c == '_') || (isdigit(c))){

					estado = 2;
					t.lexema[cont++] = c;

				}else{

					t.lexema[cont]='\0';
					ungetc(c,FD);
					int i;

					for(i=0;i<NumeroPR;i++){

						if(!(strcmp(t.lexema,TabelaPR[i].lexema))) {

							t.cat = PALAVRA_RES;
							t.codigo = i;

							return t;
						}
					}

					aux = inicio;


					while (aux->prox != NULL){

						if(strcmp(t.lexema,aux->lexema)==0){

							t.cat = IDENTIFICADOR;
							return t;
						}
						aux = aux->prox;
					}

					aux->prox = (ID *) malloc(sizeof(ID));
					aux = aux->prox;
					aux->prox = NULL;

					strcpy(aux->lexema,t.lexema);
					t.cat = IDENTIFICADOR;
					return t;
				}
				break;

			case 4:

				if(isdigit(c)){ //se for numero
					estado = 4;
					t.digito[cont++] = c;
				}else if (c == '.'){
					estado = 5;
					t.digito[cont++] = c;
				}else{
					ungetc(c,FD);
					t.digito[cont] = '\0';
					t.cat = CT_INT;
					t.valor_I = atoi(t.digito);
					return t;
				}

				break;

			case 5:

				if(isdigit(c)){
					estado = 6;
					t.digito[cont++] = c;
				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;

			case 6:

				if(isdigit(c)){
					estado = 6;
					t.digito[cont++] = c;
				}else{
					ungetc(c,FD);
					t.cat = CT_REAL;
					t.valor_R = atof(t.digito);
					return t;
				}

				break;

			case 9:

				if(c == '='){
					estado = 11;
					t.cat = SINAL;
					t.codigo = MENOR_IGUAL;
					return t;
				}else{
					ungetc(c,FD);
					t.cat = SINAL;
					t.codigo = MENOR;
					return t;
				}

				break;

			case 13:

				if(c == '='){
					estado = 11;
					t.cat = SINAL;
					t.codigo = MAIOR_IGUAL;
					return t;
				}else{
					ungetc(c,FD);
					t.cat = SINAL;
					t.codigo = MAIOR;
					return t;
				}

				break;

			case 21:

				if(c == '='){

					t.cat = SINAL;
					t.codigo = IGUAL_IGUAL;
					return t;

				}else{

					ungetc(c,FD);
					t.cat = SINAL;
					t.codigo = IGUAL;
					return t;
				}

				break;

			case 24:

				if(c == '*'){

					estado = 25;

				}else{

					ungetc(c,FD);
					t.cat = SINAL;
					t.codigo = BARRA;
					return t;

				}

				break;

			case 25:

				if(c == '*') estado = 26;
				if(c== '\n') contLinha++;

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

					t.cat = SINAL;
					t.codigo = OU;
					return t;
				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;


			case 31:

					if(c == '&'){

					t.cat = SINAL;
					t.codigo = E;
					return t;
				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;


			case 33:

				if(c == '='){

					t.cat = SINAL;
					t.codigo = DIFERENTE;
					return t;
				}else{

					ungetc(c,FD);
					t.cat = SINAL;
					t.codigo = NEGACAO;
					return t;
				}

				break;

			case 41:

				if((isprint(c)) && ((c != 39) && (c != 92))){ // 92 é barra invertida

					t.cat = CT_C;
					t.codigo = c;
					estado = 43;

				} else if((c == '\\')&& ((c != 39))){ //39 é apostrofo
				    estado = 47;
				}else{
					printf("erro na linha %d :[%c]",contLinha,c);
					system("pause");
					exit(-3);
				}

				break;

			case 43:

				if(c == 39){ //Apóstrofo

					return t;
				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;

			case 44:

				if((isprint(c)) && (c != '"') && (c != '\\')){

					//CL[indice++] = c;
					t.lexema[cont++] = c;

				}else if(c == '\\'){

					estado = 50;

				}else if(c == '"'){

					//CL[indice++] = '\0';
					t.lexema[cont++] = '\0';
					strcpy(CL[indice],t.lexema);
					indice++;
					return t;

				}else{
					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);
				}

				break;

			case 47:

                if(c == 'n'){

                    t.cat = CT_C;
					t.codigo = '\n';
					estado = 43;

				}else if(c == '0'){

					t.cat = CT_C;
					t.codigo = '\0';
					estado = 43;

                }else{

                    printf("erro na linha %d :[%c]",contLinha,c);
					system("pause");
					exit(-3);

                }

				break;

			case 50:

				if(c == 'n'){

				}else if((isprint(c)) && (c != '"') && (c != '\\')){

					//CL[indice++] = c;
					t.lexema[cont++] = c;
					estado = 44;
				}else{

					printf("erro na linha %d",contLinha);
					system("pause");
					exit(-3);

				}

				break;
		}
	}
}



int main(){

	char nome[25];
   	FILE *fp;
   	token t;


	printf("Digite o nome do arquivo a ser lido\n");
   	gets(nome);

   fp = fopen(nome,"r");

   if(fp == NULL){
	   	printf("erro: arquivo inexistente");
	   	exit(-5);
   }


 	do{

		t = AnalisadorLexico(fp);

			if(t.cat == IDENTIFICADOR) printf("<ID,%s> ",t.lexema);
			if(t.cat == PALAVRA_RES) printf("<PR,%s> ",TabelaPR[t.codigo].lexema);
			if(t.cat == CT_INT) printf("<CT_I,%d> ",t.valor_I);
			if(t.cat == CT_REAL) printf("<CT_R,%f> ",t.valor_R);
			if(t.cat == SINAL){
				
				switch(t.codigo){
					
					case 11:
						printf("<SN, ; > ");
						break;
					case 12:
						printf("<SN, > > ");
						break;
					case 13:
						printf("<SN, >= > ");
						break;
					case 14:
						printf("<SN, < >");
						break;
					case 15:
						printf("<SN, <= > ");
						break;
					case 16:
						printf("<SN, = > ");
						break;
					case 17:
						printf("<SN, == > ");
						break;
					case 18:
						printf("<SN, + > ");
						break;
					case 19:
						printf("<SN, - > ");
						break;
					case 20:
						printf("<SN, * > ");
						break;
					case 21:
						printf("<SN, / > ");
						break;
					case 22:
						printf("<SN, ( > ");
						break;
					case 23:
						printf("<SN, ) > ");
						break;
					case 24:
						printf("<SN, { > ");
						break;
					case 25:
						printf("<SN, } > ");
						break;
					case 26:
						printf("<SN, || > ");
						break;
					case 27:
						printf("<SN, && > ");
						break;
					case 28:
						printf("<SN, != > ");
						break;
					case 29:
						printf("<SN, , > ");
						break;
					case 30:
						printf("<SN, ! > ");
						break;
				}
			}
			
			if(t.cat == CT_C){

				if(t.codigo == 0) printf("<CT_C,\\0> ");					
				else if (t.codigo ==10) printf("<CT_C,\\n> ");					
				else printf("<CT_C,%c>",t.codigo);
				
			}
			if(t.cat == CT_L) printf("<CT_L,%s> ",CL[t.codigo]);



	}while(t.cat != 6);	//Chama o Analisador léxico até que ele retorne o código de EOF

	fclose(fp);

		return 0;
}


