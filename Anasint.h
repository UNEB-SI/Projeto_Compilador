#ifndef ANASINT
#define ANASINT

/* Variaveis globais  */
extern token t, tnext;
extern char escopo;
extern int contLinha;
extern int topo;
extern int Retorno;
extern int SemRetorno;
int tipoFuncao;
FILE *FD1;

/* Assinaturas de funcoes  */
void Prog(FILE *);
void tipos_param(FILE *);
void tipos_p_opc(FILE *);
void cmd(FILE *);
int atrib(FILE *);
int expr(FILE *);
int expr_simp(FILE *);
int termo(FILE *);
int fator(FILE *);
int op_rel(FILE *);
char * selecao_completa();
void criaLabel();
int verificaAnd();
int verificaOr();
char * buscaLabelFunc(char []);
void InsereLabelFunc(char[]);
void codigo_oprel(int );
void endRelativo(char []);
void procuraPrincipal();
void ehFuncao();
int verificaSemRetorno();
int tipoId();
void funcTopo();
int contaQtdParam();
void verificaQtdParam(int , int );
void verCompatibilidadeParam(int , int , char[]);
int tipoFunc(char []);
int verCompatibilidade(int , int );
void DesempilhaVariaveis();
void verificaRedeclaracao();
void InsereTabela();
int temPrototipo();
void checaTipoPrototipo(int );

/*Tabela de símbolos */

typedef struct TabelaSimbolos{
	char nome_var[30];
	int tipo;
	char categoria;
	char escopo;
	int zombie;
	int free;
	char labelSimb[7];
}TS;

TS tabela_s[1000];

#endif // ANASINT
