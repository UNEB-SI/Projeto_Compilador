#ifndef ANASINT
#define ANASINT

/* Variaveis globais  */
extern token t, tnext;
extern char escopo;
extern int contLinha;
extern int topo;
int tipoFuncao;

/* Assinaturas de funcoes  */
void Prog(FILE *);
void tipos_param(FILE *);
void tipos_p_opc(FILE *);
void cmd(FILE *);
void atrib(FILE *);
void expr(FILE *);
void expr_simp(FILE *);
void termo(FILE *);
void fator(FILE *);
void op_rel(FILE *);

/*Tabela de símbolos */

typedef struct TabelaSimbolos{
	char nome_var[30];
	int tipo;
	char categoria;
	char escopo;
	int zombie;
}TS;

TS tabela_s[1000];


#endif // ANASINT
