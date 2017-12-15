#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Analex.h"
#include "Anasint.h"
#include "GerenciadorTS.h"
#include "GerenciadorErros.h"

char escopo = 'g';
char categoria_simb ='v';
int topo = -1;
char func_retorno[30];
char label[6];
int Retorno = 0,SemRetorno = 0;
int qtdLabel = 0;
int m,n = 0;
int contParametro = 0;
int Amem=0;


void criaLabel(){
  qtdLabel++;
  char aux[6];
  sprintf(aux,"%d",qtdLabel);
  strcpy(label, "L");
  strncat(label,aux,6);
}

char * selecao_completa(){
  char lsalvo[6];
  if (t.cat == PALAVRA_RES && t.codigo == senao){ // GERAÇÃO DE CÓDIGO
     criaLabel();
     strcpy(lsalvo,label);
     fprintf(FD1, "GOTO %s\n", label);
     return lsalvo;
 }
 return "\0";
}

int verificaAnd(){
  if((tnext.cat == SINAL) && (tnext.codigo == E)){
    criaLabel();
    return 1;
  }
  return 0;
}

int verificaOr(){
  if((tnext.cat == SINAL) && (tnext.codigo == OU)){
    criaLabel();
    return 1;
  }
  return 0;
}

char * buscaLabelFunc(char nomeFuncBuscada[30], char cat){
  int Aux = topo;
    for(Aux;Aux>=0;Aux--){
      if((strcmp(tabela_s[Aux].nome_var,nomeFuncBuscada) == 0) && (tabela_s[Aux].categoria == cat)){
        return tabela_s[Aux].labelSimb;
      }
    }
    return "\0";
}

void InsereLabelFunc(char labelFunc[]){
  strcpy(tabela_s[topo].labelSimb,labelFunc);
}

void codigo_oprel(int codigo){
    char label_oprel[6],label_oprel1[6], label_oprel2[6];
    switch(codigo){
        case IGUAL_IGUAL:
            fprintf(FD1,"SUB\n");
            criaLabel();
            strcpy(label_oprel,label);
            fprintf(FD1,"GOFALSE %s\n",label);
            fprintf(FD1,"PUSH 0\n");
            criaLabel();
            strcpy(label_oprel1,label);
            fprintf(FD1,"GOTO %s\n",label);
            fprintf(FD1,"LABEL %s\n",label_oprel);
            fprintf(FD1,"PUSH 1\n");
            fprintf(FD1,"LABEL %s\n",label_oprel1);
            break;
        case DIFERENTE:
            fprintf(FD1,"SUB\n");
            criaLabel();
            strcpy(label_oprel,label);
            fprintf(FD1,"GOFALSE %s\n",label);
            fprintf(FD1,"PUSH 1\n");
            criaLabel();
            strcpy(label_oprel1,label);
            fprintf(FD1,"GOTO %s\n",label);
            fprintf(FD1,"LABEL %s\n",label_oprel);
            fprintf(FD1,"PUSH 0\n");
            fprintf(FD1,"LABEL %s\n",label_oprel1);
            break;
        case MAIOR:
            fprintf(FD1,"SUB\n");
            criaLabel();
            strcpy(label_oprel,label);
            fprintf(FD1,"GOTRUE %s\n",label);
            fprintf(FD1,"PUSH 0\n");
            criaLabel();
            strcpy(label_oprel1,label);
            fprintf(FD1,"GOTO %s\n",label);
            fprintf(FD1,"LABEL %s\n",label_oprel);
            fprintf(FD1,"PUSH 1\n");
            fprintf(FD1,"LABEL %s\n",label_oprel1);
            break;
        case MENOR_IGUAL:
            fprintf(FD1,"SUB\n");
            criaLabel();
            strcpy(label_oprel,label);
            fprintf(FD1,"GOTRUE %s\n",label);
            fprintf(FD1,"PUSH 1\n");
            criaLabel();
            strcpy(label_oprel1,label);
            fprintf(FD1,"GOTO %s\n",label);
            fprintf(FD1,"LABEL %s\n",label_oprel);
            fprintf(FD1,"PUSH 0\n");
            fprintf(FD1,"LABEL %s\n",label_oprel1);
            break;
        case MENOR:
            fprintf(FD1,"SUB\n");
            criaLabel();
            strcpy(label_oprel,label);
            fprintf(FD1,"COPY\n");
            fprintf(FD1,"GOFALSE %s\n",label);
            criaLabel();
            strcpy(label_oprel1,label);
            fprintf(FD1,"GOTRUE %s\n",label);
            fprintf(FD1,"PUSH 1\n");
            criaLabel();
            strcpy(label_oprel2,label);
            fprintf(FD1,"GOTO %s\n",label);
            fprintf(FD1,"LABEL %s\n",label_oprel);
            fprintf(FD1,"POP\n");
            fprintf(FD1,"LABEL %s\n",label_oprel1);
            fprintf(FD1,"PUSH 0\n");
            fprintf(FD1,"LABEL %s\n",label_oprel2);
            break;
        case MAIOR_IGUAL:
            fprintf(FD1,"SUB\n");
            criaLabel();
            strcpy(label_oprel,label);
            fprintf(FD1,"COPY\n");
            fprintf(FD1,"GOFALSE %s\n",label);
            criaLabel();
            strcpy(label_oprel1,label);
            fprintf(FD1,"GOTRUE %s\n",label);
            fprintf(FD1,"PUSH 0\n");
            criaLabel();
            strcpy(label_oprel2,label);
            fprintf(FD1,"GOTO %s\n",label);
            fprintf(FD1,"LABEL %s\n",label_oprel);
            fprintf(FD1,"POP\n");
            fprintf(FD1,"LABEL %s\n",label_oprel1);
            fprintf(FD1,"PUSH 1\n");
            fprintf(FD1,"LABEL %s\n",label_oprel2);
            break;

    }

}

void endRelativo(char nome[]){
  n = 0;
  int Aux = topo;
      for(Aux;Aux>=0;Aux--){
          if((strcmp(nome,tabela_s[Aux].nome_var) == 0)){
              if(tabela_s[Aux].escopo == 'g' && tabela_s[Aux].categoria == 'v'){
                  m = 0;
                  do{
                    Aux --;
                    if(tabela_s[Aux].escopo == 'g' && tabela_s[Aux].categoria == 'v')
                      n++;
                    }  while(Aux>= 0);
                    return;
              }else if(tabela_s[Aux].escopo == 'l' && tabela_s[Aux].categoria == 'v'){
                  m = 1;
                    do{
                      n++;
                      Aux --;
                    }while(tabela_s[Aux].categoria == 'v');
                  n--;
                  return;
              }else if (tabela_s[Aux].categoria == 'r' || tabela_s[Aux].categoria == 'p'){
                m = 1;
                do{
                    Aux++;
                    n++;
                  } while((tabela_s[Aux].categoria == 'r' || tabela_s[Aux].categoria == 'p') && Aux <= topo);
                n = n * -1;
                n = n -2;
                return;
              }
          }
      }
}

void procuraPrincipal(){ //procura a funcao principal na tabela de símbolos, e se não encontrar, acusa erro.
int Aux = topo;
    for(Aux;Aux>=0;Aux--){
        if((strcmp("principal",tabela_s[Aux].nome_var) == 0)){
            return;
          }
    }
    GerenciadorErros(ERROPRINCIPAL);
}

void ehFuncao(){ //Função que verifica se um ID é uma função. Se for, indica erro, senão, simplesmente retorna.
  int Aux = topo - 1;
    for(Aux;Aux>=0;Aux--){
        if((strcmp(t.lexema,tabela_s[Aux].nome_var) == 0)){
          if(tabela_s[Aux].categoria == 'f'){
            GerenciadorErros(ERRO_FUNC_ATRIB);
          }else{
            return;
          }
        }
    }
}

int verificaSemRetorno(){ //Verifica se uma função é sem retorno e retorna true ou false.

  int Aux = topo - 1;
    for(Aux;Aux>=0;Aux--){
        if((strcmp(t.lexema,tabela_s[Aux].nome_var) == 0)){
          if(tabela_s[Aux].tipo == 0){
            return 1;
          }else{
            return 0;
          }
        }
      }
      GerenciadorErros(FUNCAO_N_DECLARADA);
}

int tipoId(){
  int i=0;
  for (i=topo+1; i>=0; i--){
    if(strcmp(tabela_s[i].nome_var,t.lexema) == 0 && (tabela_s[i].zombie == 0)){
        return tabela_s[i].tipo;
    }
  }
  GerenciadorErros(VAR_N_DECLARADA);
}

void funcTopo(){
  int i=0;
  for (i=topo+1; i>=0; i--){
    if(tabela_s[i].categoria == 'f'){
        strcpy(func_retorno, tabela_s[i].nome_var);
        return;
    }
  }
    GerenciadorErros(FUNCAOTOPO);
}

int contaQtdParam(){
    int i =0, cont = 0, j =0;
    for(i=topo+1; i>=0; i--){
      if(strcmp(tabela_s[i].nome_var,t.lexema) == 0 &&
        (tabela_s[i].categoria == 'f'|| tabela_s[i].categoria == 'o')){
            j = i+1;
            break;
        }
    }
    if(!strcmp(tabela_s[j-1].nome_var,t.lexema) == 0){
      GerenciadorErros(FUNCAO_N_DECLARADA);
    }
    while(tabela_s[j].categoria == 'p' || tabela_s[j].categoria == 'r'){
        if(tabela_s[j].categoria == 'r' && tabela_s[j].tipo == 5){
            cont = 0;
            break;
        }
        cont++;
        j++;
    }
    return cont;
}

int contaQtdVarLocais(char nomeFunc[]){
    int i =0, cont = 0, j =0;
    for(i=topo+1; i>=0; i--){
      if(strcmp(tabela_s[i].nome_var,nomeFunc) == 0 &&
        (tabela_s[i].categoria == 'f')){
            j = i+1;
            break;
        }
    }
    if(!strcmp(tabela_s[j-1].nome_var,nomeFunc) == 0){
      GerenciadorErros(FUNCAO_N_DECLARADA);
    }
    while(tabela_s[j].categoria == 'p' ){
        j++;
    }

    while(tabela_s[j].categoria == 'v' && tabela_s[j].escopo == 'l'){
        cont++;
        j++;
    }

    return cont;
}


void verificaQtdParam(int paramFunc, int qtdPassada){
    if(!(paramFunc == qtdPassada)) {
      GerenciadorErros(QTDPARAM_INCOMPATIVEL);
    }
}

void verCompatibilidadeParam(int tipoParam, int saltos, char func_atual[]){
  int i =0;
  for(i=0;i<topo+1;i++){
      if(strcmp(tabela_s[i].nome_var,func_atual) == 0 &&
        tabela_s[i].categoria == 'f'){
          if ((!verCompatibilidade(tabela_s[i+saltos].tipo,tipoParam)) && tabela_s[i+saltos].categoria == 'p'){
            GerenciadorErros(TIPOPARAM_INCOMPATIVEL);
          }
          else
            break;
        }
  }
}

int tipoFunc(char nomeFunc[]){
  int i =0;
  for(i=0;i<topo+1;i++){
      if(strcmp(tabela_s[i].nome_var,nomeFunc) == 0 &&
        (tabela_s[i].categoria == 'f' || tabela_s[i].categoria == 'o')){
          return tabela_s[i].tipo;
        }
  }
  GerenciadorErros(FUNCAO_N_DECLARADA);

}

int verCompatibilidade(int primTipo, int segTipo){
  switch(primTipo){
    case inteiro:
      if(segTipo == inteiro || segTipo == booleano || segTipo == caracter){
        return 1;
      }
      break;
    case caracter:
      if(segTipo == inteiro || segTipo == caracter || segTipo == booleano){
        return 1;
      }
      break;
    case booleano:
      if(segTipo == booleano || segTipo == inteiro || segTipo == caracter){
        return 1;
      }
      break;
    case real:
      if(segTipo == real){
        return 1;
      }
      break;
  }

  if(segTipo == 0){
    GerenciadorErros(FUNC_RET_VALOR);
  }
  GerenciadorErros(TIPO_INCOMPATIVEL);
}

void DesempilhaVariaveis(){

int aux = topo;

    while (1){

          if (tabela_s[aux].categoria == 'v'){
            strcpy(tabela_s[aux].nome_var,"\0");
            tabela_s[aux].tipo = 99;
            tabela_s[aux].categoria = '\0';
            tabela_s[aux].escopo = '\0';
            tabela_s[aux].zombie = 0;
            topo --;
            aux --;
          }else if(tabela_s[aux].categoria == 'p'){
            tabela_s[aux].zombie = 1;
            aux --;
          }else{
            return;
          }
    }
}

void verificaRedeclaracao(){
  int Aux = topo - 1;
    for(Aux;Aux>=0;Aux--){
        if((strcmp(t.lexema,tabela_s[Aux].nome_var) == 0) && (tabela_s[Aux].escopo == escopo) && (tabela_s[Aux].zombie == 0) && (tabela_s[Aux].free == 0) && (tabela_s[Aux].tipo != semparam) && (t.lexema[0] != '\0') && (tabela_s[Aux].categoria != 'r')){
            if(tabela_s[Aux].categoria != 'o'){
              GerenciadorErros(REDECLARACAO);
            }else if (categoria_simb == 'o'){
              GerenciadorErros(REDECLARACAO_PROTO);
            }else{
                if(tabela_s[Aux].tipo != tipos){
                  GerenciadorErros(TIPO_FUNC_DIF);
                }
              tabela_s[Aux].free = 1;
              return;
            }
        }
    }
}

void InsereTabela(){

    topo++;
    verificaRedeclaracao();
    strcpy(tabela_s[topo].nome_var,t.lexema);
    tabela_s[topo].tipo = tipos;
    tabela_s[topo].categoria = categoria_simb;
    tabela_s[topo].escopo = escopo;
    tabela_s[topo].zombie = 0;
    tabela_s[topo].free = 0;
}

//Funcao que retorna -1 ou a posição do prototipo na tabela
// -1 foi utilizado ao invés de 0 (false) pois a posição 0 da tabela também é válida,
//e se ele encontrasse um prototipo na posição 0, indicaria que não existe protótipo
int temPrototipo(){

  int aux = topo - 1;
    for(aux;aux>=0;aux--){
        if((strcmp(tabela_s[topo].nome_var,tabela_s[aux].nome_var) == 0) && (tabela_s[aux].categoria == 'o')){
          return aux;
        }
      }
    return -1;
}

void checaTipoPrototipo(int posicao){

  if(tabela_s[posicao].categoria == 'r'){
        if(tipos == tabela_s[posicao].tipo){
            if(tabela_s[posicao].nome_var[0] != '\0'){
                if(strcmp(t.lexema,tabela_s[posicao].nome_var) != 0){
                  GerenciadorErros(NOME_PAR_DIF);
                }
            }

        }else{
          GerenciadorErros(TIPO_DIF);
        }
  }else{
    GerenciadorErros(QTDPARAM_INCOMPATIVEL);
  }
}

void tipos_param(FILE *FD){

int contParam = 0,contAmem = 0;
int prototipo = 0;
prototipo = temPrototipo();

  if((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
  	//proximo token apos palavra reservada
				    escopo = 'l';
				    categoria_simb = 'p';
				    tipos = t.codigo;
				    Analex(FD);
				    if(t.cat == IDENTIFICADOR){
				      //proximo token apos id

              contParam++;
              if (prototipo != -1)
                checaTipoPrototipo(prototipo + contParam);
                contAmem++;
							InsereTabela();
				      Analex(FD);
				    }else{
              GerenciadorErros(ID_ESPERADO);
						}

				    if (t.cat == SINAL && t.codigo == VIRGULA){
				      		Analex(FD);
						      while(1){
							        if((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
												Analex(FD);
                        tipos = t.codigo;
														if(t.cat == IDENTIFICADOR){
                                contParam++;
                                if (prototipo != -1)
                                  checaTipoPrototipo(prototipo + contParam);
                                  contAmem++;
																InsereTabela();
																Analex(FD);
																	if(t.cat == SINAL && t.codigo == VIRGULA){
																		Analex(FD);
																	}else{
                                    contParametro = contParam;
                                    contParam = contParam + prototipo + 1;
                                      if(tabela_s[contParam].categoria == 'r'){
                                        GerenciadorErros(QTDPARAM_INCOMPATIVEL);
                                      }
                                      fprintf(FD1,"AMEM %d\n",contAmem);
                                      Amem = Amem + contAmem;
																		return;
																	}

														}else{
                              GerenciadorErros(ID_ESPERADO);
														}
											}else{
                        GerenciadorErros(PR_ESPERADO);
											}
							    }

						}else{
              fprintf(FD1,"AMEM %d\n",contAmem);
              contParametro = contParam;
              Amem = Amem + contAmem;
							return;
						}

  } else if(t.cat == PALAVRA_RES && t.codigo == semparam){
        contParam++;

        if(tnext.cat == SINAL && tnext.codigo == FECHA_PAR){
              escopo = 'l';
              categoria_simb = 'p';
              tipos = semparam;
              if(prototipo != -1)
                checaTipoPrototipo(prototipo + contParam);
      				Analex(FD);
      						return;
          }else{
                GerenciadorErros(FUNCAO_SEMPARAM_PAR);
          }
  }else{
        GerenciadorErros(PARAM_ESPERADO);
  }
}

void tipos_p_opc(FILE *FD){
escopo = 'l';
categoria_simb = 'r';
Analex(FD);

	if((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
    tipos = t.codigo;
		//Analex(FD);
			while(1){

							if(tnext.cat == IDENTIFICADOR){
                Analex(FD);
								InsereTabela();
								Analex(FD);
							}else{
                t.lexema[0] = '\0';
                InsereTabela();
                Analex(FD);
              }

							if(t.cat == SINAL && t.codigo == VIRGULA){
								Analex(FD);

									if((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
                      tipos = t.codigo;

									}else{
                    GerenciadorErros(ERRO_LINHA);
									}
							}else{
                break;
              }
			}

	}else if(t.cat == PALAVRA_RES && t.codigo == semparam){
    tipos = t.codigo;
    InsereTabela();
		Analex(FD);

	}else{
    GerenciadorErros(PARAM_ESPERADO);
	}
}
void cmd(FILE*FD){
  int tipoRetorno = 0;

  if(t.cat == PALAVRA_RES && t.codigo == se){
    Analex(FD);
    if(t.cat == SINAL && t.codigo == ABRE_PAR){
        int tipoExprSe;
        tipoExprSe = expr(FD);
        if (!verCompatibilidade(booleano,tipoExprSe)){
            GerenciadorErros(EXPR_BOOL);
        }
        Analex(FD);
          if(t.cat == SINAL && t.codigo == FECHA_PAR){
                  char labelsalvo[6], labelsalvo1[7];
                  Analex(FD);
                  criaLabel();
                  strcpy(labelsalvo,label);
                  fprintf(FD1,"GOFALSE %s\n", label);
                    cmd(FD);

                    strcpy(labelsalvo1,selecao_completa());
                    fprintf(FD1,"LABEL %s\n", labelsalvo);
                          if(t.cat == PALAVRA_RES && t.codigo == senao){
                            Analex(FD);
                            cmd(FD);
                            fprintf(FD1,"LABEL %s\n", labelsalvo1);
                          }
                          return;
          }else{
            GerenciadorErros(FECHAPAR_ESPERADO);
          }
    }else{
        GerenciadorErros(ABREPAR_ESPERADO);
    }

  }else if(t.cat == PALAVRA_RES && t.codigo == enquanto){
    char labelsalvo[6],labelsalvo1[6];
    Analex(FD);
    criaLabel();
    fprintf(FD1,"LABEL %s\n",label);
    strcpy(labelsalvo,label);
    if(t.cat == SINAL && t.codigo == ABRE_PAR){
        int tipoExprEnquanto;
        tipoExprEnquanto = expr(FD);
        if (!verCompatibilidade(booleano,tipoExprEnquanto)){
            GerenciadorErros(EXPR_BOOL);
        }
        Analex(FD);
            if(t.cat == SINAL && t.codigo == FECHA_PAR){
              Analex(FD);
              criaLabel();
              fprintf(FD1,"GOFALSE %s\n",label);
              strcpy(labelsalvo1,label);
              cmd(FD);
              fprintf(FD1,"GOTO %s\n",labelsalvo);
              fprintf(FD1,"LABEL %s\n",labelsalvo1);
              return;

            }else{
              GerenciadorErros(FECHAPAR_ESPERADO);
            }
    }else{
      GerenciadorErros(ABREPAR_ESPERADO);
    }

  }else if(t.cat == PALAVRA_RES && t.codigo == para){
    char labelsalvo1[6],labelsalvo2[6],labelsalvo3[6],labelsalvo4[6],nomeId[30],nomeId2[30];
    Analex(FD);
    if(t.cat == SINAL && t.codigo == ABRE_PAR){

        if(!(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)){
          Analex(FD);
            if(t.cat == IDENTIFICADOR){
              int tipoAtrib, idTipo;
              strcpy(nomeId,t.lexema);
              idTipo = tipoId();
              tipoAtrib = atrib(FD);
              verCompatibilidade(idTipo,tipoAtrib);
              endRelativo(nomeId);
              fprintf(FD1,"STOR %d,%d\n",m,n);
            }else{
              GerenciadorErros(ID_ESPERADO);
            }

        }

        criaLabel();
        fprintf(FD1,"LABEL %s\n",label);
        strcpy(labelsalvo1,label);

            Analex(FD);
            if(t.cat == SINAL && t.codigo == PTO_VIRGULA){ // primeiro pto virg

                  if(!(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)){
                    int tipoExprPara;
                    tipoExprPara = expr(FD);
                    if (!verCompatibilidade(booleano,tipoExprPara)){
                        GerenciadorErros(EXPR_BOOL);
                    }
                  }
                  else{
                    fprintf(FD1,"PUSH 1\n");
                  }

                        criaLabel();
                        fprintf(FD1,"GOFALSE %s\n",label);
                        strcpy(labelsalvo2,label);
                        criaLabel();
                        fprintf(FD1,"GOTO %s\n",label);
                        strcpy(labelsalvo3,label);
                        criaLabel();
                        fprintf(FD1,"LABEL %s\n",label);
                        strcpy(labelsalvo4,label);
                        Analex(FD);

                        if(t.cat == SINAL && t.codigo == PTO_VIRGULA){// segundo pto virg

                                  if(!(tnext.cat == SINAL && tnext.codigo == FECHA_PAR)){
                                      Analex(FD);
                                            if(t.cat == IDENTIFICADOR){
                                              int tipoAtrib, idTipo;
                                              strcpy(nomeId2,t.lexema);
                                              idTipo = tipoId();
                                              tipoAtrib = atrib(FD);
                                              verCompatibilidade(idTipo,tipoAtrib);
                                              endRelativo(nomeId2);
                                              fprintf(FD1,"STOR %d,%d\n",m,n);
                                            }else{
                                            GerenciadorErros(ID_ESPERADO);
                                            }
                                  }

                                        fprintf(FD1,"GOTO %s\n",labelsalvo1);
                                        fprintf(FD1,"LABEL %s\n",labelsalvo3);
                                        Analex(FD);

                                            if(t.cat == SINAL && t.codigo == FECHA_PAR){
                                              Analex(FD);
                                              cmd(FD);
                                              fprintf(FD1,"GOTO %s\n",labelsalvo4);
                                              fprintf(FD1,"LABEL %s\n",labelsalvo2);
                                              return;
                                            }else{
                                              GerenciadorErros(FECHAPAR_ESPERADO);
                                            }
                      }else{
                        GerenciadorErros(PTOVIRG_ESPERADO);
                      }
              }else{
                GerenciadorErros(PTOVIRG_ESPERADO);
              }
    }else{
      GerenciadorErros(ABREPAR_ESPERADO);
    }
  }else if(t.cat == PALAVRA_RES && t.codigo == retorne){
      Retorno = 1;
      if(SemRetorno == 1 && !(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)){
        GerenciadorErros(FUNCAO_SEMR_R);
      }

            if(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA){
              Analex(FD);
              Analex(FD);
              funcTopo();
              fprintf(FD1, "DMEM %d\n",contaQtdVarLocais(func_retorno));
              fprintf(FD1, "RET 1,%d\n",contParametro);
              return;
            }
      if(!(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)){
          tipoRetorno = expr(FD);
          funcTopo();
          int funcTipo = tipoFunc(func_retorno);
          verCompatibilidade(tipoRetorno,funcTipo);
      }else{
        GerenciadorErros(FUNCAO_RETORNO);
      }
          Analex(FD);

      if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
        Analex(FD);
        funcTopo();
        fprintf(FD1, "STOR 1,%d\n",-3-contParametro);
        fprintf(FD1, "DMEM %d\n",contaQtdVarLocais(func_retorno));
        fprintf(FD1, "RET 1,%d\n",contParametro);
        return;
      }else{
        GerenciadorErros(PTOVIRG_ESPERADO);
      }

  }else if(t.cat == SINAL && t.codigo == ABRE_CHAVE){

              Analex(FD);
              while(!(t.cat == SINAL && t.codigo == FECHA_CHAVE)){
                  cmd(FD);
              }
              Analex(FD);
              return;


  }else if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
    Analex(FD);
    return;
  }else if (t.cat == IDENTIFICADOR){

                  int param = 0, qtdParam = 0,contParam = 0;
                  char funcaoAt[30];
                  if(tnext.cat == SINAL && tnext.codigo == ABRE_PAR){
                        if(verificaSemRetorno() == 0){
                          GerenciadorErros(FUNCAO_SEMRETORNO);
                        }
                        strcpy(funcaoAt,t.lexema);
                        qtdParam = contaQtdParam();
                        Analex(FD);
                          if(t.cat == SINAL && t.codigo == ABRE_PAR){

                            if(!(tnext.cat == SINAL && tnext.codigo == FECHA_PAR)){
                                contParam++;
                                param = expr(FD);
                                verCompatibilidadeParam(param,contParam,funcaoAt);
                            }

                              while(tnext.cat == SINAL && tnext.codigo == VIRGULA){
                                Analex(FD);
                                contParam++;
                                param = expr(FD);
                                verCompatibilidadeParam(param,contParam,funcaoAt);
                              }

                                Analex(FD);

                                    if(t.cat == SINAL && t.codigo == FECHA_PAR){
                                        verificaQtdParam(qtdParam,contParam);
                                        if(strcmp(buscaLabelFunc(funcaoAt,'f'),"\0") == 0){
                                            fprintf(FD1,"CALL %s\n", buscaLabelFunc(funcaoAt,'o'));
                                        }
                                        else{
                                            fprintf(FD1,"CALL %s\n", buscaLabelFunc(funcaoAt,'f'));
                                        }
                                        Analex(FD);
                                        if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                          Analex(FD);
                                            return;
                                        }else{
                                          GerenciadorErros(PTOVIRG_ESPERADO);
                                        }

                                    }else{
                                    GerenciadorErros(FECHAPAR_ESPERADO);
                                    }

                          }else{
                            GerenciadorErros(ABREPAR_ESPERADO);
                            exit(-82);
                          }
                    }else if(tnext.cat == SINAL && tnext.codigo == IGUAL){

                        char nome1[30];
                        strcpy(nome1,t.lexema);

                        int tipoAtrib, idTipo;
                        idTipo = tipoId();
                        tipoAtrib = atrib(FD);
                        verCompatibilidade(idTipo,tipoAtrib);
                        Analex(FD);
                            if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
                              endRelativo(nome1);
                              fprintf(FD1,"STOR %d,%d\n",m,n);
                              Analex(FD);
                              return;
                            }else{
                              GerenciadorErros(PTOVIRG_ESPERADO);
                            }
                    }else{
                    GerenciadorErros(ERRO_LINHA);
                    }
  }else{
    GerenciadorErros(ERRO_LINHA);
  }
}

int op_rel(FILE *FD){
  int codigo;
  Analex(FD);
    if((t.cat == SINAL) && ((t.codigo == IGUAL_IGUAL) || (t.codigo == DIFERENTE) || (t.codigo == MENOR)  || (t.codigo == MENOR_IGUAL)  || (t.codigo == MAIOR) || (t.codigo == MAIOR_IGUAL ))){
        codigo = t.codigo;
        return codigo;
    }else{
      GerenciadorErros(OPREL_ESPERADO);
    }

}

int atrib(FILE *FD){
int tipo;
ehFuncao();
Analex(FD);
    if(t.cat == SINAL && t.codigo == IGUAL){

        tipo = expr(FD);
        if(tipo != caracter && tipo != inteiro && tipo != booleano && tipo != real){
          GerenciadorErros(TIPOVAR_ATRIB);
        }
        return tipo;
    }else{
        GerenciadorErros(IGUAL_ESPERADO);
    }

}

int expr(FILE *FD){
  int primTipo = 0,segTipo = 0, operacao = 0;
  primTipo = expr_simp(FD);
  if((!(tnext.cat == SINAL && tnext.codigo == VIRGULA)) && (!(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)) && (!(tnext.cat == SINAL && tnext.codigo == FECHA_PAR))){
   	operacao = op_rel(FD);
    segTipo = expr_simp(FD);
    verCompatibilidade(primTipo,segTipo);
    codigo_oprel(operacao);
    primTipo = segTipo;
    return booleano;
  }
  return primTipo;
}

int expr_simp(FILE *FD){
  int primTipo = 0,segTipo = 0, codigo = 0;
  char labelOr[6];


  if((tnext.cat == SINAL)  && ((tnext.codigo == MAIS) || (tnext.codigo == MENOS))){
    Analex(FD);
  }

  primTipo = termo(FD);
  if(verificaOr()){
    strcpy(labelOr,label);
  }

  while((tnext.cat == SINAL) && ((tnext.codigo == MAIS) || (tnext.codigo == MENOS) || (tnext.codigo == OU))){
    Analex(FD);
    codigo = t.codigo;
    if(codigo == OU){
        fprintf(FD1,"COPY\n");
        fprintf(FD1,"GOTRUE %s\n",labelOr);
        fprintf(FD1,"POP\n");
    }
    segTipo = termo(FD);
    verCompatibilidade(primTipo,segTipo);
    if(codigo != OU){
        if(primTipo == CT_REAL){
          fprintf(FD1,"%s\n", ((codigo==MAIS) ? "ADDF" : "SUBF"));
        }
        else{
          fprintf(FD1,"%s\n", ((codigo==MAIS) ? "ADD" : "SUB"));
        }
    }
    primTipo = segTipo;
  }
  if (codigo == OU){
    fprintf(FD1,"LABEL %s\n", labelOr);
  }
  return primTipo;
}

int termo(FILE *FD){
 int primTipo = 0,segTipo = 0, codigo = 0;
 char labelAnd[6];
 primTipo = fator(FD);

  if(verificaAnd()){
    strcpy(labelAnd,label);
  }
  while((tnext.cat == SINAL) && ((tnext.codigo == ASTERISCO) || (tnext.codigo == BARRA) || (tnext.codigo == E))){
    Analex(FD);
    codigo = t.codigo;
    if(codigo == E){
        fprintf(FD1,"COPY\n");
        fprintf(FD1,"GOFALSE %s\n",labelAnd);
        fprintf(FD1,"POP\n");
    }
    segTipo = fator(FD);
    verCompatibilidade(primTipo,segTipo);
    if(codigo != E){
        if(primTipo == CT_REAL){
          fprintf(FD1,"%s\n", ((codigo==ASTERISCO) ? "MULF" : "DIVF"));
        }
        else{
          fprintf(FD1,"%s\n", ((codigo==ASTERISCO) ? "MUL" : "DIV"));
        }
    }
    primTipo = segTipo;
  }
  if (codigo == E){
    fprintf(FD1,"LABEL %s\n", labelAnd);
  }
  return primTipo;
}

int fator(FILE *FD){
  int tipo = 0, param =0, qtdParam = 0,contParam = 0;
  char funcAtl[30],labelneg[7], labelneg1[7];
  Analex(FD);

  if(t.cat == IDENTIFICADOR){

    if(tnext.cat == SINAL && tnext.codigo == ABRE_PAR){
      strcpy(funcAtl,t.lexema);
      tipo = tipoFunc(t.lexema);
      if(tipo == semretorno){
        GerenciadorErros(FUNCAO_DECL_SEMRETORNO);
      }
      fprintf(FD1, "AMEM 1\n");
      Amem++;
      qtdParam = contaQtdParam();
      Analex(FD);
          if(tnext.cat == SINAL && tnext.codigo == FECHA_PAR){
              Analex(FD);
              verificaQtdParam(qtdParam,contParam);
                if(strcmp(buscaLabelFunc(funcAtl,'f'),"\0") == 0){
                    fprintf(FD1,"CALL %s\n", buscaLabelFunc(funcAtl,'o'));
                }
                else{
                    fprintf(FD1,"CALL %s\n", buscaLabelFunc(funcAtl,'f'));
                }
            	return tipo;
          }else{
            param = expr(FD);
            contParam++;
            if(tnext.cat == SINAL && tnext.codigo == FECHA_PAR){
              verCompatibilidadeParam(param,contParam,funcAtl);
            }
            Analex(FD);
          }

            while(t.cat == SINAL && t.codigo == VIRGULA){
              param =expr(FD);
              contParam++;
              if (tnext.cat == SINAL && tnext.codigo == FECHA_PAR){
                verCompatibilidadeParam(param,contParam,funcAtl);
              }
              Analex(FD);
            }
            if(t.cat == SINAL && t.codigo == FECHA_PAR){
              verificaQtdParam(qtdParam,contParam);
                if(strcmp(buscaLabelFunc(funcAtl,'f'),"\0") == 0){
                    fprintf(FD1,"CALL %s\n", buscaLabelFunc(funcAtl,'o'));
                }
                else{
                    fprintf(FD1,"CALL %s\n", buscaLabelFunc(funcAtl,'f'));
                }
              return tipo;
            }else{
              GerenciadorErros(FECHAPAR_ESPERADO);
            }
    }
    else{
        endRelativo(t.lexema);
        fprintf(FD1,"LOAD %d,%d\n",m,n);
        tipo = tipoId();
        return tipo;
    }

  }else if(t.cat == CT_INT){
      fprintf(FD1,"PUSH %d\n",t.valor_I);
      return inteiro;
  }else if (t.cat == CT_REAL){
    fprintf(FD1,"PUSH %.2f\n",t.valor_R);
    return real;
  }else if (t.cat == CT_C){
      fprintf(FD1,"PUSH %d\n",(int)t.codigo);
    	return caracter;
  }else if (t.cat == CT_L){
    	return caracter;
  }else if((t.cat == SINAL) && (t.codigo == ABRE_PAR)){
      tipo = expr(FD);
      Analex(FD);
      if((t.cat == SINAL) && (t.codigo == FECHA_PAR)){
        	return tipo;
      }else{
       GerenciadorErros(FECHAPAR_ESPERADO);
      }

  }else if((t.cat == SINAL) && (t.codigo == NEGACAO)){
    tipo = fator(FD);
    criaLabel();
    strcpy(labelneg,label);
    fprintf(FD1,"GOFALSE %s\n",label);
    fprintf(FD1,"PUSH 0\n");
    criaLabel();
    strcpy(labelneg1,label);
    fprintf(FD1,"GOTO %s\n",label);
    fprintf(FD1,"LABEL %s\n",labelneg);
    fprintf(FD1,"PUSH 1\n");
    fprintf(FD1,"LABEL %s\n",labelneg1);
    return tipo;
  }else{
  GerenciadorErros(ERRO_LINHA);
  }
  return tipo;
}

void Prog (FILE *FD){
char labelFunc[6], pulaFunc[6];
Analex(FD);
Analex(FD);
int temProt = 0;

int contAmem = 0,AmemVarGlobal = 0;

fprintf(FD1,"INIP\n");
	do{

	  if ((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano) || (t.codigo == semretorno))){
              if(t.codigo == semretorno) SemRetorno = 1;
              tipos = t.codigo;
			           Analex(FD);
			  if(t.cat == IDENTIFICADOR){
                   categoria_simb = 'v';
                   if (!(tnext.cat == SINAL && tnext.codigo == ABRE_PAR) && tipos == semretorno){
                        GerenciadorErros(VAR_SEMRETORNO);
                   }
                   if (tnext.cat == SINAL && tnext.codigo == ABRE_PAR){
                        categoria_simb = 'f';
                        criaLabel();
                        fprintf(FD1, "GOTO %s\n", label);
                        strcpy(pulaFunc,label);
                   }else{
                     contAmem++;
                   }

                   InsereTabela();
                   if(categoria_simb == 'f'){
                        temProt = temPrototipo();
                        if(temProt == -1){
                            criaLabel();
                            strcpy(labelFunc,label);
                            InsereLabelFunc(labelFunc);
                        }
                        else{
                            strcpy(labelFunc,buscaLabelFunc(t.lexema,'o'));
                            InsereLabelFunc(labelFunc);
                        }
                        fprintf(FD1,"LABEL %s\n",labelFunc);
                   }
			       Analex(FD);

						        if (t.cat == SINAL && t.codigo == VIRGULA){
			                        Analex(FD);
			                        do{
                                if(t.cat == IDENTIFICADOR){
                                    contAmem++;
                                    InsereTabela();
                                    Analex(FD);
                                    if (t.cat == SINAL && t.codigo == VIRGULA){
                                      Analex(FD);

                                    }else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                      fprintf(FD1,"AMEM %d\n",contAmem);
                                        AmemVarGlobal = AmemVarGlobal + contAmem;
                                        contAmem = 0;
                                      Analex(FD);
                                      break;
                                    }else{
                                      GerenciadorErros(PTOVIRG_ESPERADO);
                                    }
                                }
                                    else {
                                      GerenciadorErros(ID_ESPERADO);
                                    }

			                        }while(1);

										}else if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
                      fprintf(FD1,"AMEM %d\n",contAmem);
                      AmemVarGlobal = AmemVarGlobal + contAmem;
                      contAmem = 0;
												Analex(FD);
						        }else if (t.cat == SINAL && t.codigo == ABRE_PAR){ //funcao
                            Analex(FD);
                            fprintf(FD1,"INIPR 1\n");
                            tipos_param(FD);

                                if(t.cat == SINAL && t.codigo == FECHA_PAR){
                                  if(!SemRetorno){
                                    fprintf(FD1, "AMEM 1\n");
                                    Amem++;
                                  }
                                  categoria_simb = 'v';
                                  Analex(FD);

			                                  if(t.cat == SINAL && t.codigo == ABRE_CHAVE){
																						Analex(FD);
																					escopo = 'l';
																							while(1){

						                                    			if ((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
																														tipos = t.codigo;
																														Analex(FD);
																																	if (t.cat == IDENTIFICADOR) {
																																		InsereTabela();
                                                                    contAmem++;
																																		Analex(FD);
																																		if (t.cat == SINAL && t.codigo == VIRGULA){
																																							 Analex(FD);
																																							 do{
																																											 if(t.cat == IDENTIFICADOR){
																																													 InsereTabela();
                                                                                           contAmem++;
																																													 Analex(FD);
																																													 		if (t.cat == SINAL && t.codigo == VIRGULA){
                                                                                                contAmem++;
																																														 			Analex(FD);
																																													 		}else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                                                                                fprintf(FD1,"AMEM %d\n",contAmem);
                                                                                                Amem = Amem + contAmem;
                                                                                                contAmem = 0;
                                                                                                break;
																																													 		}else{
                                                                                                  GerenciadorErros(PTOVIRG_ESPERADO);
																																													 		}
																																								 				}
																																							 }while(1);
																																	}else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                                                    fprintf(FD1,"AMEM %d\n",contAmem);
                                                                    Amem = Amem + contAmem;
                                                                    contAmem = 0;
																																	}else{
                                                                      GerenciadorErros(PTOVIRG_ESPERADO);
																																	}

									                                          }else{
                                                                GerenciadorErros(ID_ESPERADO);
                                                            }

																											}else if(t.cat == SINAL && t.codigo == FECHA_CHAVE){
																													escopo = 'g';
                                                        funcTopo();
                                                        fprintf(FD1,"DMEM %d\n",contaQtdVarLocais(func_retorno));
                                                        Amem = 0;
                                                              fprintf(FD1, "RET 1,%d\n",contParametro);
                                                          contParametro = 0;
                                                          Retorno = 0;

                                                          fprintf(FD1, "LABEL %s\n",pulaFunc);
                                                          DesempilhaVariaveis();
																													Analex(FD);
																													break;
																											}else{
    																											cmd(FD);
                                                    }
																								}

			                                  }else{
                                        GerenciadorErros(ABRECHAVE_ESPERADO);
			                                  }
                          }else{
                            GerenciadorErros(FECHAPAR_ESPERADO);
                          }

											}else{
                          GerenciadorErros(PTOVIRG_ESPERADO);
											}
								}else{
                  GerenciadorErros(ID_ESPERADO);
								}

                SemRetorno = 0;
					}else if(t.cat == PALAVRA_RES && t.codigo == prototipo){
                Analex(FD);
                  if ((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real) ||  (t.codigo == booleano) || (t.codigo == semretorno))){
                    tipos = t.codigo;
                          Analex(FD);
                            if(t.cat == IDENTIFICADOR){
                                categoria_simb = 'o';
                                  InsereTabela();
                                  criaLabel();
                                  InsereLabelFunc(label);
                                   Analex(FD);
                                    if (t.cat == SINAL && t.codigo == ABRE_PAR){
                                              tipos_p_opc(FD);
                                              escopo = 'g';
                                              categoria_simb = 'o';
                                            if(t.cat == SINAL && t.codigo == FECHA_PAR){
                                                Analex(FD);

                                                  if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
																										Analex(FD);
                                                  }
                                                  else if(t.cat == SINAL && t.codigo == VIRGULA){
                                                    while(1){
                                                        Analex(FD);
                                                        if(t.cat == IDENTIFICADOR){
                                                          InsereTabela();
                                                            Analex(FD);
                                                            if (t.cat == SINAL && t.codigo == ABRE_PAR){
                                                                tipos_p_opc(FD);
                                                                escopo = 'g';
                                                                categoria_simb = 'o';
                                                                  if(t.cat == SINAL && t.codigo == FECHA_PAR){
                                                                          Analex(FD);

                                                                          if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                                                              Analex(FD);
                                                                              break;
                                                                          }else if (t.cat == SINAL && t.codigo == VIRGULA){

                                                                          }else{
                                                                              GerenciadorErros(PTOVIRG_ESPERADO);
                                                                          }
                                                                    }else{
                                                                      GerenciadorErros(FECHAPAR_ESPERADO);
                                                                    }
                                                            }else{
                                                                GerenciadorErros(ABREPAR_ESPERADO);
                                                            }
                                                        }else if(t.cat == FIM_ARQ){
                                                            GerenciadorErros(PTOVIRG_ESPERADO);
                                                        }else{
                                                            GerenciadorErros(ID_ESPERADO);
                                                        }
                                                    }
                                                  }else{
                                                      GerenciadorErros(PTOVIRG_ESPERADO);
                                                  }

                                    }else{
                                      GerenciadorErros(FECHAPAR_ESPERADO);
                                    }
                                }else{
                                        GerenciadorErros(ABREPAR_ESPERADO);
                                }


                           }else{
                              GerenciadorErros(ID_ESPERADO);
                          }

                }else{
                  GerenciadorErros(ERRO_LINHA);
                }
          }else if(t.cat == SINAL && t.codigo == FECHA_CHAVE){
            Analex(FD);
            //TERMINO DA FUNCAO
            if(t.cat == SINAL && t.codigo == FECHA_CHAVE){
                GerenciadorErros(FECHACHAVE_SOLTO);
            }
					}else{
              GerenciadorErros(ERRO_LINHA);
					}

	}while(t.cat != 6); //Fim Arquivo

  procuraPrincipal();
  fprintf(FD1,"CALL %s\n", buscaLabelFunc("principal",'f'));
  fprintf(FD1,"DMEM %d\n",AmemVarGlobal);
  fprintf(FD1,"HALT\n");
	return;
}
