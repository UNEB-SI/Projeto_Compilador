#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Analex.h"
#include "Anasint.h"
#include "GerenciadorTS.h"

void imprimir(){
    int i;
	printf("\n============================TABELA=DE=SIMBOLOS========================\n");
	for(i=0;i<topo+1;i++){
        printf("Lexema: %s, Tipo: %d, Categoria: %c, Escopo: %c, Zombie?: %d\n",tabela_s[i].nome_var,tabela_s[i].tipo,tabela_s[i].categoria,tabela_s[i].escopo,tabela_s[i].zombie);
	}
	printf("\n A tabela de simbolos possui %d simbolos\n",topo+1);
	system("pause");
}
