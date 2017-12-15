#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"
#include "Anasint.h"
#include "GerenciadorErros.h"

void GerenciadorErros(int erro){

         switch(erro){

            case ERROPRINCIPAL:
                printf("Erro na linha %d. Funcao principal nao encontrada\n",contLinha);
		     break;

            case ERRO_FUNC_ATRIB:
			      printf("Erro na linha %d. Funcao nao pode receber atribuicao\n",contLinha);
		     break;

            case FUNCAO_N_DECLARADA:
		          printf("Erro na linha %d. Funcao nao declarada\n",contLinha);
		     break;

            case VAR_N_DECLARADA:
		          printf("Erro na linha %d. Variavel nao declarada\n",contLinha);
		     break;

            case FUNCAOTOPO:
		       printf("Erro na linha %d. Nao ha funcao no topo\n",contLinha);
		     break;

            case QTDPARAM_INCOMPATIVEL:
			   printf("Erro na linha %d. Quantidade de parametros incompativel.\n",contLinha);
		     break;

            case TIPOPARAM_INCOMPATIVEL:
		       printf("Erro na linha %d. Tipo do parametro incompativel\n",contLinha);
		     break;

            case FUNC_RET_VALOR:
		         printf("Erro na linha %d. a funcao deveria retornar um valor\n",contLinha);
		     break;

            case TIPO_INCOMPATIVEL:
			    printf("Erro na linha %d. Tipos incompativeis\n",contLinha);
		     break;

            case REDECLARACAO:
		        printf("Erro: Redeclaracao na linha %d\n",contLinha);
		     break;

            case REDECLARACAO_PROTO:
		        printf("Erro: Redeclaracao de prototipo na linha %d\n",contLinha);
		     break;

            case TIPO_FUNC_DIF:
		       printf("Erro: Tipo de funcao diferente do esperado na linha %d\n",contLinha);
		     break;

            case NOME_PAR_DIF:
			     printf("Erro: Nome de parametro diferente do prototipo na linha %d\n",contLinha);
		     break;

            case TIPO_DIF:
		       printf("Erro: Tipo diferente do esperado na linha %d\n",contLinha);
		     break;

            case ID_ESPERADO:
		         printf("Identificador esperado na linha %d\n",contLinha);
		     break;

            case PR_ESPERADO:
			    printf("palavra reservada esperada na linha %d\n",contLinha);
		     break;

            case FUNCAO_SEMPARAM_PAR:
		          printf("Erro: Funcao semparam contem parametros na linha %d\n",contLinha);
		     break;

            case PARAM_ESPERADO:
		        printf("Erro: parametros esperados na linha %d\n",contLinha);
		     break;

            case ERRO_LINHA:
		       printf("Erro na linha %d\n", contLinha);
		     break;

            case EXPR_BOOL:
			   printf("Erro na linha %d. A expressao deve ser do tipo booleano ou compativel\n",contLinha);
		     break;

            case FECHAPAR_ESPERADO:
		       printf("Erro: fecha parenteses esperado na linha %d\n",contLinha);
		     break;

            case ABREPAR_ESPERADO:
		         printf("Erro: Abre parenteses esperado na linha %d\n",contLinha);
		     break;

            case PTOVIRG_ESPERADO:
			    printf("Erro: ponto e virgula esperado na linha %d\n",contLinha);
		     break;

            case FUNCAO_SEMR_R:
		        printf("Erro: funcao declarada como semretorno. Retorne encontrado na linha %d\n",contLinha);
		     break;

            case FUNCAO_RETORNO:
		        printf("Erro na linha %d: A funcao deve possuir um valor de retorno.\n",contLinha);
		     break;

            case FUNCAO_SEMRETORNO:
		       printf("Erro na linha %d: a funcao deve ser do tipo semretorno. \n",contLinha);
		     break;

            case OPREL_ESPERADO:
                printf("Erro na linha %d: Esperado sinal de op_rel",contLinha);
		     break;

            case TIPOVAR_ATRIB :
                printf("Erro na linha %d: Apenas variaveis dos tipos basicos podem receber atribuicoes",contLinha);
		     break;

            case IGUAL_ESPERADO:
                printf("Erro na linha %d: Esperado sinal igual\n",contLinha);
		     break;

            case FUNCAO_DECL_SEMRETORNO:
                printf("Erro: a funcao foi declarada como semretorno na linha %d\n",contLinha);
		     break;

            case VAR_SEMRETORNO:
                printf("Erro na linha %d: Nao eh possivel declarar uma variavel semretorno\n",contLinha);
		     break;

            case ABRECHAVE_ESPERADO:
                printf("abre chave esperado na linha %d\n",contLinha);
		     break;

            case FECHACHAVE_SOLTO:
                printf("Erro na linha %d: Fecha chave solto\n",contLinha);
		     break;
		 }

	system("pause");
    exit(-erro);
}
