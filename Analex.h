#define NumeroPR 11 //Utilizado para percorrer o vetor de PR

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
	int valor_I; 	// valor inteiro
	double valor_R;	// valor real
}token;


//**************Tabela de Identificadores*******************


typedef struct Identificador{
	
	char lexema[30];	
	struct Identificador *prox;	
}ID;

ID *inicio = NULL;

//***********************************************************

//**************Tabela de Palavras Reservadas***************

typedef struct PalavraReservada{
	
	char lexema[30];
	
}PR;

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
	{.lexema = "retorne"}
};
		
//***********************************************************

//**************Tabela de Constantes Literais****************

/*
typedef struct ConstanteLiteral{
	
	char string[250];	
	struct ConstanteLiteral *prox;	
}CL;

CL *inicioCL = NULL;

*/


char CL[1000][30];
int indice = 0;
//***********************************************************

