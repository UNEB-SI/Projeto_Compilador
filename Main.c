#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"
#include "Anasint.h"

int main(){
    int i=0;
	char nome[25];
   	FILE *fp;

	printf("Digite o nome do arquivo a ser lido\n");
   	gets(nome);

   fp = fopen(nome,"r");

   if(fp == NULL){
	   	printf("erro: arquivo inexistente");
	   	exit(-5);
   }

	Prog(fp);

	fclose(fp);

	printf("\n Codigo sintaticamente correto! \n\n");
	printf("============================TABELA=DE=SIMBOLOS========================\n");
	for(i=0;i<topo+1;i++){
        printf("Lexema: %s, Tipo: %d, Categoria: %c, Escopo: %c, Zombie?: %d\n",tabela_s[i].nome_var,tabela_s[i].tipo,tabela_s[i].categoria,tabela_s[i].escopo,tabela_s[i].zombie);
	}
	printf("A tabela de simbolos possui %d simbolos\n",topo+1);
	system("pause");
	return 0;
}
