#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"
#include "Anasint.h"
#include "GerenciadorTS.h"

int main(){
    int i=0;
	char nome[25];
   	FILE *fp;

	printf("Digite o nome do arquivo a ser lido\n");
   	gets(nome);

   fp = fopen(nome,"r");
   FD1 = fopen ("codigoObjeto.obj","w");
   if(fp == NULL){
	   	printf("erro: arquivo inexistente");
	   	exit(-5);
   }

	Prog(fp);

	fclose(fp);
  fclose(FD1);

	printf("\n Codigo sintatica e semanticamente correto! \n\n");

	char resultado;
	printf("Deseja verificar a tabela de simbolos? (S/N) \n\n> ");
	resultado = getchar();

	if(resultado == 's' || resultado == 'S')
            imprimir();


	return 0;
}
