#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Analex.h"
#include "Anasint.h"

char escopo = 'g';
char categoria_simb ='v';
int topo = -1;
int tipos;


void DesempilhaVariaveis(){

int aux = topo;

    while (1){

          if (tabela_s[aux].categoria == 'v'){
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

void InsereTabela(){
    topo++;
    strcpy(tabela_s[topo].nome_var,t.lexema);
    tabela_s[topo].tipo = tipos;
    tabela_s[topo].categoria = categoria_simb;
    tabela_s[topo].escopo = escopo;
    tabela_s[topo].zombie = 0;
}
//proximo token apos abre parentese
void tipos_param(FILE *FD){

    Analex(FD);


  if((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
  	//proximo token apos palavra reservada
				    escopo = 'l';
				    categoria_simb = 'p';
				    tipos = t.codigo;
				    Analex(FD);
				    if(t.cat == IDENTIFICADOR){
				      //proximo token apos id
							InsereTabela();
				      Analex(FD);
				    }else{
				      printf("id esperado na linha %d",contLinha);
							system("pause");
							//printf("\n %d %d",t.cat,t.codigo);
							exit(-23);

						}

				    if (t.cat == SINAL && t.codigo == VIRGULA){
				      		Analex(FD);
						      while(1){
							        if((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
												Analex(FD);
                                                tipos = t.codigo;
														if(t.cat == IDENTIFICADOR){
																InsereTabela();
																Analex(FD);
																	if(t.cat == SINAL && t.codigo == VIRGULA){
																		Analex(FD);
																	}else if(t.cat == SINAL && t.codigo == FECHA_PAR){
																		categoria_simb = 'v';
																		return;
																	}else{
																		printf("Erro: Fecha parenteses esperado na linha %d ",contLinha);
																		system("pause");
																		exit(-27);
																	}


														}else{
															printf("id esperado na linha %d",contLinha);
															system("pause");
															printf("\n %d %d",t.cat,t.codigo);
															exit(-24);
														}
											}else{
												printf("palavra reservada esperada");
												system("pause");
												exit(-26);
											}
							    }

						}else if(t.cat == SINAL && t.codigo == FECHA_PAR){
							categoria_simb = 'v';
							return;
						}else{
							printf("Erro: Fecha parenteses esperado na linha %d ",contLinha);
							system("pause");
							exit(-25);
						}

  } else if(t.cat == PALAVRA_RES && t.codigo == semparam){

					Analex(FD);

					if(t.cat == SINAL && t.codigo == FECHA_PAR){
						categoria_simb = 'v';
						return;
					}else{
						printf("Erro: Fecha parenteses esperado na linha %d ",contLinha);
						system("pause");
						exit(-21);
					}

	} else{
    printf("parametro invalido. esperado palavra reservada na linha %d", contLinha);
		//printf("\n %d %d",t.cat,t.codigo);
		system("pause");
		exit(-1);
	}


}

void tipos_p_opc(FILE *FD){
//escopo = 'l';
Analex(FD);

	if((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
		Analex(FD);
			while(1){

							if(t.cat == IDENTIFICADOR){
								//InsereTabela(tipo)
									Analex(FD);
							}

							if(t.cat == SINAL && t.codigo == VIRGULA){
								Analex(FD);
									if((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano))){
											Analex(FD);
									}else{
										printf("Erro na linha %d", contLinha);
										system("pause");
										exit(-10);
									}

							}else if(t.cat == SINAL && t.codigo == FECHA_PAR){
								break;

							}else{
								printf("Erro na linha %d",contLinha);

								system("pause");
								//printf("\n %d %d",t.cat,t.codigo);
								exit(-11);
							}
			}

	}else if(t.cat == PALAVRA_RES && t.codigo == semparam){
		Analex(FD);
		if(t.cat == SINAL && t.codigo == FECHA_PAR){
			return;
		}else{
			printf("Erro: Fecha parenteses esperado na linha %d ",contLinha);
			system("pause");
			exit(-6);
		}

	}else{
		printf("Erro: Parametros esperados na linha %d ",contLinha);
		system("pause");
		exit(-12);
	}
}

void cmd(FILE*FD){


  if(t.cat == PALAVRA_RES && t.codigo == se){
    Analex(FD);
    if(t.cat == SINAL && t.codigo == ABRE_PAR){
        expr(FD);
        Analex(FD);
          if(t.cat == SINAL && t.codigo == FECHA_PAR){
                  Analex(FD);
                    cmd(FD);
                          if(t.cat == PALAVRA_RES && t.codigo == senao){
                            Analex(FD);
                            cmd(FD);
                          }
                          return;
          }else{
            printf("Erro: fecha parenteses esperado na linha %d ",contLinha);
            system("pause");
            exit(-72);
          }
    }else{
      printf("Erro: Abre parenteses esperado na linha %d ",contLinha);
      system("pause");
      exit(-71);
    }

  }else if(t.cat == PALAVRA_RES && t.codigo == enquanto){
    Analex(FD);
    if(t.cat == SINAL && t.codigo == ABRE_PAR){
        expr(FD);
        Analex(FD);
            if(t.cat == SINAL && t.codigo == FECHA_PAR){
              Analex(FD);
              cmd(FD);
              return;

            }else{
              printf("Erro: fecha parenteses esperado na linha %d ",contLinha);
              system("pause");
              exit(-74);
            }
    }else{
      printf("Erro: Abre parenteses esperado na linha %d ",contLinha);
      system("pause");
      exit(-73);
    }
  }else if(t.cat == PALAVRA_RES && t.codigo == para){
    Analex(FD);
    if(t.cat == SINAL && t.codigo == ABRE_PAR){

        if(!(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)){
          Analex(FD);
            if(t.cat == IDENTIFICADOR){
              atrib(FD);
            }else{
              printf("Identificador esperado na linha %d ",contLinha);
              system("pause");
              exit(-76);
            }

        }
            Analex(FD);
            if(t.cat == SINAL && t.codigo == PTO_VIRGULA){ // primeiro pto virg

                  if(!(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)){
                      expr(FD);
                  }
                        Analex(FD);

                        if(t.cat == SINAL && t.codigo == PTO_VIRGULA){// segundo pto virg

                                  if(!(tnext.cat == SINAL && tnext.codigo == FECHA_PAR)){
                                      Analex(FD);
                                            if(t.cat == IDENTIFICADOR){
                                              atrib(FD);
                                            }else{
                                              printf("Identificador esperado na linha %d ",contLinha);
                                              system("pause");
                                              exit(-77);
                                            }
                                  }
                                        Analex(FD);

                                            if(t.cat == SINAL && t.codigo == FECHA_PAR){
                                              Analex(FD);
                                              cmd(FD);
                                              //Analex(FD);
                                              return;
                                            }else{
                                              printf("Erro: fecha parenteses esperado na linha %d ",contLinha);
                                              system("pause");
                                              exit(-75);
                                            }
                      }else{
                        printf("Erro: ponto e virgula esperado na linha %d ",contLinha);
                        system("pause");
                        exit(-78);
                      }
              }else{
                printf("Erro: ponto e virgula esperado na linha %d ",contLinha);
                system("pause");
                exit(-77);
              }
    }else{
      printf("Erro: Abre parenteses esperado na linha %d ",contLinha);
      system("pause");
      exit(-76);
    }
  }else if(t.cat == PALAVRA_RES && t.codigo == retorne){

      if(!(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)){
          expr(FD);
      }
          Analex(FD);

      if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
        return;
      }else{
        printf("Erro: ponto e virgula esperado na linha %d ",contLinha);
        system("pause");
        exit(-79);
      }

  }else if(t.cat == SINAL && t.codigo == ABRE_CHAVE){

/*
      while(!(tnext.cat == SINAL && tnext.codigo == FECHA_CHAVE)){
          Analex(FD);
          cmd(FD);
      }
      Analex(FD);
      if(t.cat == SINAL && t.codigo == FECHA_CHAVE){
        Analex(FD);
        return;
*/


              Analex(FD);
              while(!(t.cat == SINAL && t.codigo == FECHA_CHAVE)){
                  cmd(FD);
              }
              Analex(FD);
              return;

/*
      }else{
        printf("Erro: fecha chave esperado na linha %d ",contLinha);
        //printf("%d %d ",t.cat, t.codigo);
        system("pause");
        exit(-80);
      }*/
  }else if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
    Analex(FD);
    return;
  }else if (t.cat == IDENTIFICADOR){

                  if(tnext.cat == SINAL && tnext.codigo == ABRE_PAR){
                        Analex(FD);
                          if(t.cat == SINAL && t.codigo == ABRE_PAR){
                            if(!(tnext.cat == SINAL && tnext.codigo == FECHA_PAR)){
                                expr(FD);
                            }

                              while(tnext.cat == SINAL && tnext.codigo == VIRGULA){
                                Analex(FD);
                                expr(FD);
                              }

                                Analex(FD);

                                    if(t.cat == SINAL && t.codigo == FECHA_PAR){
                                        Analex(FD);
                                        if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                            return;
                                        }else{
                                          printf("Erro: ponto e virgula esperado na linha %d ",contLinha);
                                          system("pause");
                                          exit(-84);
                                        }

                                    }else{
                                      printf("Erro: fecha parenteses esperado na linha %d ",contLinha);
                                      system("pause");
                                      exit(-83);
                                    }

                          }else{
                            printf("Erro: abre parenteses esperado na linha %d ",contLinha);
                            //printf("\n %d %d",t.cat,t.codigo);
                            system("pause");
                            exit(-82);
                          }
                    }else if(tnext.cat == SINAL && tnext.codigo == IGUAL){
                        atrib(FD);
                        Analex(FD);
                            if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
                              return;
                            }else{
                              printf("Erro: ponto e virgula esperado na linha %d ",contLinha);
                              system("pause");
                              exit(-81);
                            }
                    }else{
                      printf("Erro na linha %d ",contLinha);
                      system("pause");
                      exit(-85);
                    }
  }else{
    printf("Erro na linha %d ",contLinha);
    printf("%d %d ",tnext.cat, tnext.codigo);
    system("pause");
    exit(-86);
  }
}

void op_rel(FILE *FD){
  Analex(FD);
    if((t.cat == SINAL) && ((t.codigo == IGUAL_IGUAL) || (t.codigo == DIFERENTE) || (t.codigo == MENOR)  || (t.codigo == MENOR_IGUAL)  || (t.codigo == MAIOR) || (t.codigo == MAIOR_IGUAL ))){
        return;
    }else{
        printf("Erro na linha %d: Esperado sinal de op_rel",contLinha);
        system("pause");
        printf("%d %d ",t.cat, t.codigo);
        exit(-50);
    }

}

void atrib(FILE *FD){
Analex(FD);
    if(t.cat == SINAL && t.codigo == IGUAL)
        expr(FD);
    else{
        printf("Erro na linha %d: Esperado sinal igual",contLinha);
        system("pause");
        //printf("\n %d %d ",tnext.cat,tnext.codigo);
        exit(-6);
    }

}

void expr(FILE *FD){

  expr_simp(FD);

  if((!(tnext.cat == SINAL && tnext.codigo == VIRGULA)) && (!(tnext.cat == SINAL && tnext.codigo == PTO_VIRGULA)) && (!(tnext.cat == SINAL && tnext.codigo == FECHA_PAR))){
   	op_rel(FD);
    expr_simp(FD);
  }
}

void expr_simp(FILE *FD){

  //Analex(FD);

  if((tnext.cat == SINAL)  && ((tnext.codigo == MAIS) || (tnext.codigo == MENOS))){
    Analex(FD);
  }

  termo(FD);

  while((tnext.cat == SINAL) && ((tnext.codigo == MAIS) || (tnext.codigo == MENOS) || (tnext.codigo == OU))){
    Analex(FD);
    termo(FD);
  }

}

void termo(FILE *FD){
 fator(FD);

  while((tnext.cat == SINAL) && ((tnext.codigo == ASTERISCO) || (tnext.codigo == BARRA) || (tnext.codigo == E))){
    Analex(FD);
    fator(FD);
  }
}

void fator(FILE *FD){
  Analex(FD);

  if(t.cat == IDENTIFICADOR){

    if(tnext.cat == SINAL && tnext.codigo == ABRE_PAR){
      Analex(FD);
          if(tnext.cat == SINAL && tnext.codigo == FECHA_PAR){
							Analex(FD);
            	return;
          }else{
            expr(FD);
            Analex(FD);
          }

            while(t.cat == SINAL && t.codigo == VIRGULA){
              expr(FD);
          }
            //Analex(FD);
            if(t.cat == SINAL && t.codigo == FECHA_PAR){
              return;
            }else{
              printf("Fecha parenteses esperado");
              system("pause");
              exit(-30);
            }
    }

  }else if(t.cat == CT_INT){
    	return;
  }else if (t.cat == CT_REAL){
    return;
  }else if (t.cat == CT_C){
    	return;
  }else if (t.cat == CT_L){
    	return;
  }else if((t.cat == SINAL) && (t.codigo == ABRE_PAR)){
      expr(FD);
      Analex(FD);
      if((t.cat == SINAL) && (t.codigo == FECHA_PAR)){
        	return;
      }else{
        printf("Fecha parenteses esperado");
       system("pause");
       exit(-31);
      }

  }else if((t.cat == SINAL) && (t.codigo == NEGACAO)){
    fator(FD);
  }else{
    printf("Erro na linha %d ",contLinha);
    system("pause");
    exit(-29);
  }
}

void Prog (FILE *FD){

//inicio = NULL;
//indice = 0;

Analex(FD);
Analex(FD);

	do{

	  if ((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real)||  (t.codigo == booleano) || (t.codigo == semretorno))){
              tipos = t.codigo;
			  Analex(FD);
			  if(t.cat == IDENTIFICADOR){
                   if (!(tnext.cat == SINAL && tnext.codigo == ABRE_PAR) && tipos == semretorno){
                        printf("Erro na linha %d: Nao eh possivel declarar uma variavel semretorno\n",contLinha);
                        system("pause");
                        exit(-112);
                   }
                   if (tnext.cat == SINAL && tnext.codigo == ABRE_PAR){
                        categoria_simb = 'f';
                   }
                   InsereTabela();
			       Analex(FD);

						        if (t.cat == SINAL && t.codigo == VIRGULA){
			                        Analex(FD);
			                        do{
                                if(t.cat == IDENTIFICADOR){
                                    InsereTabela();
                                    Analex(FD);
                                    if (t.cat == SINAL && t.codigo == VIRGULA){
                                      Analex(FD);

                                    }else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                      Analex(FD);
                                      break;
                                    }else{
                                      printf("ponto e virgula esperado na linha %d ",contLinha);
                                      system("pause");
                                      exit(-20);
                                    }
                                    }
                                    else {
                                      printf("Erro na linha %d. identificador esperado\n",contLinha);
                                      system("pause");
                                      exit(-30);
                                    }

			                        }while(1);

										}else if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
												Analex(FD);
						        }else if (t.cat == SINAL && t.codigo == ABRE_PAR){ //funcao
						                    tipos_param(FD);
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
																																		Analex(FD);
																																		if (t.cat == SINAL && t.codigo == VIRGULA){
																																							 Analex(FD);
																																							 do{
																																											 if(t.cat == IDENTIFICADOR){
																																													 InsereTabela();
																																													 Analex(FD);
																																													 		if (t.cat == SINAL && t.codigo == VIRGULA){
																																														 			Analex(FD);
																																													 		}else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                                                                                break;
																																													 		}else{
																																														 			printf("ponto e virgula esperado na linha %d",contLinha);
																																																	system("pause");
																																																	exit(-13);
																																													 		}
																																								 				}
																																							 }while(1);
																																	}else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){

																																	}else{
																																		printf("Erro: Ponto e virgula esperado na linha %d",contLinha);
																																		system("pause");
																																		exit(-14);
																																	}

									                                          }else{
                                                              printf("ID esperado na linha %d ",contLinha);
                                                              system("pause");
                                                              exit(-90);
                                                            }

																											}else if(t.cat == SINAL && t.codigo == FECHA_CHAVE){
																													escopo = 'g';
																													DesempilhaVariaveis();
																													Analex(FD);
																													break;
																											}else{
    																											cmd(FD);
                                                    }
																								}
                                              /*  if(t.cat == SINAL && t.codigo == FECHA_CHAVE){
                                                    Analex(FD);
                                                }else{
                                                  printf("fecha chave esperado na linha %d",contLinha);
                                                  system("pause");
                                                  exit(-96);
                                                }*/

			                                  }else{
			                                   	printf("abre chave esperado na linha %d ",contLinha);
																					system("pause");
																					//printf("\n %d %d",t.cat,t.codigo);
																					exit(-15);
			                                  }

											}else{
													printf("ponto e virgula esperado na linha %d ", contLinha);
													system("pause");
													exit(-17);
											}
								}else{
									printf("ID esperado na linha %d ",contLinha);
									system("pause");
									exit(-2);
								}


					}else if(t.cat == PALAVRA_RES && t.codigo == prototipo){
                Analex(FD);
                  if ((t.cat == PALAVRA_RES) &&  ((t.codigo == caracter) ||  (t.codigo == inteiro) ||   (t.codigo == real) ||  (t.codigo == booleano) || (t.codigo == semretorno))){
                          Analex(FD);
                            if(t.cat == IDENTIFICADOR){
                               Analex(FD);
                                //InsereTabela(tipo);
                                    if (t.cat == SINAL && t.codigo == ABRE_PAR){
                                              tipos_p_opc(FD);
                                              Analex(FD);

                                                  if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
																										Analex(FD);
                                                  }
                                                  else if(t.cat == SINAL && t.codigo == VIRGULA){
                                                    while(1){
                                                        Analex(FD);
                                                        if(t.cat == IDENTIFICADOR){
                                                            Analex(FD);
                                                            //InsereTabela(tipo);
                                                            if (t.cat == SINAL && t.codigo == ABRE_PAR){
                                                                tipos_p_opc(FD);
                                                                Analex(FD);

                                                                if(t.cat == SINAL && t.codigo == PTO_VIRGULA){
                                                                    Analex(FD);
                                                                    break;
                                                                }else if (t.cat == SINAL && t.codigo == VIRGULA){
                                                                    Analex(FD);
                                                                }else{
                                                                    printf("ponto e virgula esperado na linha %d",contLinha);
                                                                    printf("\n %d %d\n",t.cat,t.codigo);
                                                                    printf("\n %d %d\n",tnext.cat,tnext.codigo);
                                                                    system("pause");
                                                                    exit(-3);
                                                                }
                                                            }else{
                                                                printf("abre parenteses esperado na linha %d",contLinha);
                                                                system("pause");
                                                                exit(-4);
                                                            }
                                                        }else if(t.cat == FIM_ARQ){
                                                            printf("Erro na linha %d. Falta ponto e virgula ",contLinha);
                                                            system("pause");
                                                            exit(-111);
                                                        }else{
                                                            printf("ID esperado na linha %d ",contLinha);
                                                            system("pause");
                                                            exit(-7);
                                                        }
                                                    }
                                                  }else{
                                                      printf("ponto e virgula esperado na linha %d",contLinha);
																											printf("\n %d %d\n",t.cat,t.codigo);
																											printf("\n %d %d\n",tnext.cat,tnext.codigo);
																											system("pause");
																											exit(-3);
                                                  }
                                    }else{
                                            printf("abre parenteses esperado na linha %d",contLinha);
																						system("pause");
																						exit(-4);
                                    }


                           }else{
                          		printf("ID esperado na linha %d ",contLinha);
															system("pause");
															exit(-7);
                          }

                }else{
									printf("Erro na linha %d ",contLinha);
									system("pause");
									exit(-8);
                }
          }else if(t.cat == SINAL && t.codigo == FECHA_CHAVE){
            Analex(FD);
            if(t.cat == SINAL && t.codigo == FECHA_CHAVE){
                printf("Erro na linha %d: Fecha chave solto\n",contLinha);
                printf("\n %d %d",t.cat,t.codigo);
                system("pause");
                exit(-110);
            }

					}else{
							printf("Erro na linha %d ",contLinha);
							printf("\n %d %d",t.cat,t.codigo);
							system("pause");
							exit(-9);
					}


	}while(t.cat != 6); //Fim Arquivo

	return;
}




/*
if (t.cat == SINAL && t.codigo == VIRGULA){
			                                  Analex(FD);
			                                   do{
			                                        if(t.cat == IDENTIFICADOR){
			                                         Analex(FD);

			                                                  if (t.cat == SINAL && t.codigo == ABRE_PAR){
			                                                              tipos_param();
			                                                              Analex(FD);

			                                                          if(t.cat == SINAL && t.codigo == FECHA_PAR){
																	  }else{
			                                                              printf("fecha par esperado");
			                                                          }
			                                                  }else{
			                                                          printf("abre par esperado");
																}

			                                        }else if (t.cat == SINAL && t.codigo == VIRGULA){
			                                    	}else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){
			                                              break;
			                                        }else{
			                                              printf("pto virg esperado");
			                                          }

			                                  }while(1);

			                        }else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){
			                                break;
			                        }else{
			                          printf("pto virg esperado");
			                      }



			        }else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){

			        }else{
			               printf("pto virg esperado");
					}


			}else{
					printf("Erro na linha");
			}




			***************************************


			if(t.cat == SINAL && t.codigo == ABRE_CHAVE){

								 do{
													if(t.cat == IDENTIFICADOR){
														//InsereTabela(tipo);
														Analex(FD);

																		if (t.cat == SINAL && t.codigo == ABRE_PAR){
																								tipos_p_opc(FD);
																								Analex(FD);

																						if(t.cat == SINAL && t.codigo == FECHA_PAR){
																						}else{
																								printf("fecha par esperado na linha %d",contLinha);
																								system("pause");
																								exit(-3);
																						}
																		}else{
																						printf("abre parent esperado na linha %d",contLinha);
																						system("pause");
																						exit(-4);
																		}

												}else if (t.cat == SINAL && t.codigo == VIRGULA){
														Analex(FD);
												}else if (t.cat == SINAL && t.codigo == PTO_VIRGULA){
																break;
												 }else{
																printf("pto virg esperado na linha %d ",contLinha);
													}

										}while(1);

			 }else{
					printf("abre chave esperado na linha %d ",contLinha);
					system("pause");
					exit(-5);
			 }

*/
