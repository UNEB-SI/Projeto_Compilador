#ifndef ANALEX
#define ANALEX
#define NumeroPR 12 //Utilizado para percorrer o vetor de PR

extern int contLinha;

typedef enum {
	IDENTIFICADOR = 0,
	PALAVRA_RES = 1,
	CT_INT = 2,
	CT_REAL = 3,
	SINAL = 4,
	CT_C = 5,
	FIM_ARQ = 6,
	CT_L = 7

}categoria;


typedef enum {

	PTO_VIRGULA = 11,
	MAIOR = 12,
	MAIOR_IGUAL = 13,
	MENOR = 14,
	MENOR_IGUAL = 15,
	IGUAL = 16,
	IGUAL_IGUAL = 17,
	MAIS = 18,
	MENOS = 19,
	ASTERISCO = 20,
	BARRA = 21,
	ABRE_PAR = 22,
	FECHA_PAR = 23,
	ABRE_CHAVE = 24,
	FECHA_CHAVE = 25,
	OU = 26,
	E = 27,
	DIFERENTE = 28,
	VIRGULA = 29,
	NEGACAO = 30

}codigo;

/*
typedef enum{

	BARRA_N = 50,
	BARRA_ZERO	= 51
}caracter;*/


typedef struct Token{

	categoria cat;
	int codigo;		// ; + - * /
	char digito[30]; // <= >=
	char lexema[30]; //ID , PR
	 union {
	int valor_I; 	// valor inteiro
	double valor_R;	// valor real
	};
}token;

token t,tnext;

//**************Tabela de Identificadores*******************



//***********************************************************

//**************Tabela de Palavras Reservadas***************

typedef struct PalavraReservada{

	char lexema[30];

}PR;


typedef enum {
	semretorno,//0
	caracter,//1
	inteiro,//2
	real,//3
	booleano,//4
	semparam,//5
	se,//6
	senao,//7
	enquanto,//8
	para,//9
	retorne,//10
	prototipo//11

}palavraReserv;

//***********************************************************

//**************Tabela de Constantes Literais****************

char CL[1000][30];
extern int indice;
//***********************************************************


//**************Declaracao de Funcoes************************

void Analex(FILE *);
//***********************************************************
#endif
