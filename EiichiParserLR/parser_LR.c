//parser_LR.c
#include <stdlib.h>
#include <stdio.h>

#define FALSE (0)
#define TRUE (-1)

#define TIPO_SIMBOLO_NO_DEFINIDO	0
#define TIPO_SIMBOLO_NO_TERMINAL    1
#define TIPO_SIMBOLO_TERMINAL       2

#define SIMBOLO_TERMINAL_VDER			1
#define SIMBOLO_TERMINAL_VIZQ			2
#define SIMBOLO_TERMINAL_AVANZA			3
#define SIMBOLO_TERMINAL_SI_CHOCAS		4
#define SIMBOLO_TERMINAL_RECOGE			5
#define SIMBOLO_TERMINAL_DEJA			6
#define SIMBOLO_TERMINAL_Num			7
#define SIMBOLO_TERMINAL_PuntoyComa		8
#define SIMBOLO_TERMINAL_Espacio		9
#define SIMBOLO_TERMINAL_Tabulador		10
#define SIMBOLO_TERMINAL_Salto_linea	11
#define SIMBOLO_TERMINAL_EOF			12

#define SIMBOLO_NO_TERMINAL_Programa        1
// #define SIMBOLO_NO_TERMINAL_Programa2       2  <-- Ya no se usa en LR
#define SIMBOLO_NO_TERMINAL_Instruccion     2
#define SIMBOLO_NO_TERMINAL_InstrVuelta     3
#define SIMBOLO_NO_TERMINAL_InstrAvanza     4
#define SIMBOLO_NO_TERMINAL_InstrSiChocas   5
#define SIMBOLO_NO_TERMINAL_InstrObjeto     6

#define LR_ACTION_ERROR		-1
#define LR_ACTION_SHIFT		1
#define LR_ACTION_REDUCE	2
#define LR_ACTION_ACCEPT	3
#define LR_ACTION_GOTO		4

#define LR_STRING_ACTION_SHIFT		'S'
#define LR_STRING_ACTION_REDUCE		'R'
#define LR_STRING_ACTION_ACCEPT		'A'
#define LR_STRING_ACTION_ERROR		'\0'

#define LR_ERROR		-1

#define LR_ESTADOS_NUMMAX 17
#define LR_TABLA_COLUMNAS_NUMMAX (SIMBOLO_TERMINAL_EOF + SIMBOLO_NO_TERMINAL_InstrObjeto)
#define LR_GOTO_OFFSET (SIMBOLO_TERMINAL_EOF)

void pushLR(int intSimboloTipo, int intSimboloCodigo);

void pushLR_T(int intSimboloCodigo);

void pushLR_NT(int intSimboloCodigo);

void pushLR_T_cEdo(int intSimboloCodigo, int intEstado);

void pushLR_NT_cEdo(int intSimboloCodigo, int intEstado);

void popLR();

void vaciar_StackLR();

void imprimteT_LR(int intSimboloCodigo);

void imprimteNT_LR(int intSimboloCodigo);


char *MR_LR[LR_ESTADOS_NUMMAX][LR_TABLA_COLUMNAS_NUMMAX] = {
	{"S7","S8","S9","S10","S11","S12","","","","","","","1","2","3","4","5","6"},
	{"","","","","","","","","","","","A","","","","","",""},
	{"","","","","","","","S13","","","","","","","","","",""},
	{"","","","","","","","R3","","","","","","","","","",""},
	{"","","","","","","","R4","","","","","","","","","",""},
	{"","","","","","","","R5","","","","","","","","","",""},
	{"","","","","","","","R6","","","","","","","","","",""},
	{"","","","","","","","R7","","","","","","","","","",""},
	{"","","","","","","","R8","","","","","","","","","",""},
	{"","","","","","","S14","","","","","","","","","","",""},
	{"S7","S8","S9","S10","S11","S12","","","","","","","","15","3","4","5","6"},
	{"","","","","","","","R11","","","","","","","","","",""},
	{"","","","","","","","R12","","","","","","","","","",""},
	{"S7","S8","S9","S10","S11","S12","","","","","","R2","16","2","3","4","5","6"},
	{"","","","","","","","R9","","","","","","","","","",""},
	{"","","","","","","","R10","","","","","","","","","",""},
	{"","","","","","","","","","","","R1","","","","","",""}
};

struct t_token
{
	int intTokenCodigo;
	char *strTokenTextoFuente;
	int intReglon;
	int intColumna;
	struct t_token *ptrSig;
};
typedef struct t_token t_token;

t_token *ptrTokenList;
t_token *ptrCurrentTokenLR;

//STACK DE RECONOCIMIENTO LR
struct t_StackLR
{
	int intSimboloTipo; //Si es Terminal o No Terminal
	int intSimboloCodigo; //Código Numérico (#define) de T o NT
	int intEstado; //<-- Estado del automata
	struct t_StackLR *ptrSig;
};
typedef struct t_StackLR t_StackLR;
t_StackLR *ptrStackLRTop = NULL;

void pushLR(int intSimboloTipo, int intSimboloCodigo, int intEstado)
{
	t_StackLR *nuevo = (t_StackLR *)maLRoc(sizeof(t_StackLR));
	nuevo->intSimboloTipo = intSimboloTipo;
	nuevo->intSimboloCodigo = intSimboloCodigo;
	nuevo->intEstado = intEstado; //<--
	nuevo->ptrSig = NULL;

	if (ptrStackLRTop != NULL) //Hay elementos en el Stack
	{
		nuevo->ptrSig = ptrStackLRTop;
	}//if
	ptrStackLRTop = nuevo;
}//pushLR

void pushLR_T(int intSimboloCodigo)
{
	pushLR(TIPO_SIMBOLO_TERMINAL, intSimboloCodigo, 0); //<--
}//pushLR_T

void pushLR_NT(int intSimboloCodigo)
{
	pushLR(TIPO_SIMBOLO_NO_TERMINAL, intSimboloCodigo, 0); //<--
}//pushLR_NT

void pushLR_T_cEdo(int intSimboloCodigo, int intEstado)
{
	pushLR(TIPO_SIMBOLO_TERMINAL, intSimboloCodigo, intEstado); //<--
}//pushLR_T_cEdo

void pushLR_NT_cEdo(int intSimboloCodigo, int intEstado)
{
	pushLR(TIPO_SIMBOLO_NO_TERMINAL, intSimboloCodigo, intEstado); //<--
}//pushLR_NT_cEdo

void popLR()
{
	t_StackLR *aux;

	if (ptrStackLRTop != NULL) //Hay elementos en el Stack
	{
		aux = ptrStackLRTop;
		ptrStackLRTop = ptrStackLRTop->ptrSig;
		free(aux);
	}//if
}//popLR

void vaciar_StackLR()
{
	while (ptrStackLRTop != NULL)
		popLR();

}//vaciar_StackLR



void imprimteT_LR(int intSimboloCodigo)
{
	switch (intSimboloCodigo)
	{
	case SIMBOLO_TERMINAL_VDER: printf("T_VDER"); break;
	case SIMBOLO_TERMINAL_VIZQ: printf("T_VIZQ"); break;
	case SIMBOLO_TERMINAL_AVANZA: printf("T_AVANZA"); break;
	case SIMBOLO_TERMINAL_SI_CHOCAS: printf("T_SI_CHOCAS"); break;
	case SIMBOLO_TERMINAL_RECOGE: printf("T_RECOGE"); break;
	case SIMBOLO_TERMINAL_DEJA: printf("T_DEJA"); break;
	case SIMBOLO_TERMINAL_Num: printf("T_Num"); break;
	case SIMBOLO_TERMINAL_PuntoyComa: printf("T_PuntoyComa"); break;
	case SIMBOLO_TERMINAL_Espacio: printf("T_Espacio"); break;
	case SIMBOLO_TERMINAL_Tabulador: printf("T_Tabulador"); break;
	case SIMBOLO_TERMINAL_Salto_linea: printf("T_Salto_linea"); break;
	case SIMBOLO_TERMINAL_EOF: printf("T_EOF"); break;
	default:pushLR_NT(SIMBOLO_NO_TERMINAL_Instruccion);
		printf("ERROR");
		break;
	}//switch
}//imprimteT_LR

void imprimteNT_LR(int intSimboloCodigo)
{
	switch (intSimboloCodigo)
	{
	case SIMBOLO_NO_TERMINAL_Programa: printf("NT_Programa"); break;
		// case SIMBOLO_NO_TERMINAL_Programa2: printf("NT_Programa2"); break; <-- Ya no se usa
	case SIMBOLO_NO_TERMINAL_Instruccion: printf("NT_Instruccion"); break;
	case SIMBOLO_NO_TERMINAL_InstrVuelta: printf("NT_InstrVuelta"); break;
	case SIMBOLO_NO_TERMINAL_InstrAvanza: printf("NT_InstrAvanza"); break;
	case SIMBOLO_NO_TERMINAL_InstrSiChocas: printf("NT_InstrSiChocas"); break;
	case SIMBOLO_NO_TERMINAL_InstrObjeto: printf("NT_InstrObjeto"); break;
	default:
		printf("ERROR");
		break;
	}//switch
}//imprimteNT_LR

void imprime_entrada_LR()
{
	t_token *aux = ptrCurrentTokenLR;

	printf("Entrada: ");
	while (aux != NULL)
	{
		imprimteT_LR(aux->intTokenCodigo);
		printf("   ");
		aux = aux->ptrSig;
	}//while
	printf("\n");
}//imprime_entrada_LR

void stack_imprime2_LR(t_StackLR *nodoStack)
{
	if (nodoStack != NULL)
	{
		stack_imprime2_LR(nodoStack->ptrSig);
		switch (nodoStack->intSimboloTipo)
		{
		case TIPO_SIMBOLO_TERMINAL:
			imprimteT_LR(nodoStack->intSimboloCodigo);
			printf(" %d ", nodoStack->intEstado);
			break;
		case TIPO_SIMBOLO_NO_TERMINAL:
			imprimteNT_LR(nodoStack->intSimboloCodigo);
			break;
		case TIPO_SIMBOLO_NO_DEFINIDO:		//<--
			printf(" 0 ");					//<--
			break;							//<--
		default:
			printf("Error");
			break;
		}//switch
		printf("   ");
	}//if
}//stack_imprime2_LR

void stack_imprime_LR() //<--
{
	printf("Stack: ");
	stack_imprime2_LR(ptrStackLRTop);
	printf("\n");
}//stack_imprime_LR

int ObtenerAccion(int intEstado, int intSimboloT)
{
	int intActionRes;

	switch (MR_LR[intEstado][intSimboloT][0])
	{
	case LR_STRING_ACTION_SHIFT:	// S
		intActionRes = LR_ACTION_SHIFT;
		break;
	case LR_STRING_ACTION_REDUCE:	// R
		intActionRes = LR_ACTION_REDUCE;
		break;
	case LR_STRING_ACTION_ACCEPT:	// A
		intActionRes = LR_ACTION_ACCEPT;
		break;
	case LR_STRING_ACTION_ERROR:	// \0
		intActionRes = LR_ACTION_ERROR;
		break;
	default:
		break;
	}//switch
}//ObtenerAccion

int ObtenerEstadoDeShift(int intEstado, int intSimboloT)
{
	int intRes = LR_ACTION_ERROR;

	if (MR_LR[intEstado][intSimboloT][0] == LR_ACTION_SHIFT)
	{
		int res = atoi(MR_LR[intEstado][intSimboloT] + 1);
	}//if
	
	return intRes;
}//ObtenerEstadoDeShift

int ObtenerNumReglaDeReduce(int intEstado, int intSimboloT)
{
	int intRes = LR_ACTION_ERROR;

	if (MR_LR[intEstado][intSimboloT][0] == LR_ACTION_REDUCE)
	{
		int res = atoi(MR_LR[intEstado][intSimboloT] + 1);
	}//if

	return intRes;
}//ObtenerNumReglaDeReduce

int ReducePorRegla(int intRegla)
{
	int intEstadoAnterior;
	int intEstadoNuevo;
	switch (intRegla)
	{
	case 1: // 1. Programa -> Instruccion ; Programa
		// Se sacan del stack el # de elementos de la parte derecha RMS
		// Pero cada nodo del stack ya tiene un par de elementos (simbolo,estado)
		pops_LR(3);
		// Se obtiene el estado del simbolo arriba del stack antes de insertar el NT
		intEstadoAnterior = (ptrStackLRTop != NULL) ? ptrStackLRTop->intEstado : LR_ERROR;
		// Se inserta el NT del lado Izquierdo LHS de la regla
		pushLR_NT(SIMBOLO_NO_TERMINAL_Programa);
		intEstadoNuevo = (intEstadoAnterior != LR_ERROR) ? ObtenerGoto(intEstadoAnterior, SIMBOLO_NO_TERMINAL_Programa) : LR_ERROR;
		if(intEstadoNuevo) //TODO
		break;
	case 2: // 2. Programa -> Instruccion ;
		break;
	case 3: // 3. Instruccion -> InstrVuelta 
		break;
	case 4: // 4. Instruccion -> InstrAvanza
		break;
	case 5: // 5. Instruccion -> InstrSiChocas
		break;
	case 6: // 6. Instruccion -> InstrObjeto
		break;
	case 7: // 7. Instruccion -> Instr
		break;
	case 8: // 8. Programa -> Instruccion ; Programa
		break;
	case 9: // 9. Programa -> Instruccion ; Programa
		break;
	case 10: // 10. Programa -> Instruccion ; Programa
		break;
	case 11: // 11. Programa -> Instruccion ; Programa
		break;
	case 12:
		break;
	default:
		break;
	}//switch
}//ReducePorRegla

int parser_LR()
{
	int intBanderaErrorSintactico = FALSE;
	int intBanderaEntradaReconocida = FALSE;
	int intAction;
	int intEstado;
	int intTokenCodigo;

	// Inicializa el apuntador de recorrido de la cadena de entrada
	ptrCurrentTokenLR = ptrTokenList;

	// Condición inicial, se inserta el estado cero
	pushLR(TIPO_SIMBOLO_NO_DEFINIDO, TIPO_SIMBOLO_NO_DEFINIDO, 0);

	do
	{
		printf("==========================================================\n");
		stack_imprime_LR();
		printf("----------------------------------------------\n");
		imprime_entrada_LR();
		printf("----------------------------------------------\n");

		// Si stack sintáctico está vacío es un error
		if (ptrStackLRTop != NULL)
		{
			// Hay elementos en el stack sintáctico

			//Debe haber elementos en la entrada enviada por el scanner
			if (ptrCurrentTokenLR != NULL)
			{
				// Se obtiene la accion de la matriz de reconocimiento (ACTION)
				intAction = ObtenerAccion(ptrStackLRTop->intEstado, (ptrCurrentTokenLR->intTokenCodigo) - 1);

				switch (intAction)
				{
				case LR_ACTION_SHIFT:
					// Se obtiene el estado del shift
					intEstado = ObtenerEstadoDeShift(ptrStackLRTop->intEstado, (ptrCurrentTokenLR->intTokenCodigo) - 1);
					// Se obtiene el codigo del token de la lista de entrada enviada por el scanner
					intTokenCodigo = ptrCurrentTokenLR->intTokenCodigo;
					// Se hace el push al stack sintactico del token de la lista de entrada
					// Se hace el push del estado indicado por el shift
					pushLR_T_cEdo(intTokenCodigo, intEstado);
					// Se avanza el apuntador de entrada al siguiente token enviado por el scanner
					ptrCurrentTokenLR = ptrCurrentTokenLR->ptrSig;
					break;
				case LR_ACTION_REDUCE:
					// Se obtiene el numero de regla del Reduce
					intRegla = ObtenerNumReglaDeReduce(ptrStackLRTop->intEstado, (ptrCurrentTokenLR->intTokenCodigo) - 1);
					// Se reduce por la regla indicada
					intReduceRes = ReducePorRegla(intRegla);
					// Si no se puede reducir, se marca error
					break;
				case LR_ACTION_ACCEPT:
					break;
				case LR_ACTION_ERROR:
					break;
				default:
					break;
				}//switch

			}//if
			else
			{
				// No hay elementos en la entrada
				printf("Error Sintactico Token=%s, Renglon=%d, Columna=%d\n - No hay elementos en la entrada\n",
					ptrCurrentTokenLR->strTokenTextoFuente,
					ptrCurrentTokenLR->intReglon,
					ptrCurrentTokenLR->intColumna);

			}//else

		}//if
		else
		{
			printf("Error Sintactico Token=%s, Renglon=%d, Columna=%d\n - Stack sintactico vacio\n",
				ptrCurrentTokenLR->strTokenTextoFuente,
				ptrCurrentTokenLR->intReglon,
				ptrCurrentTokenLR->intColumna);
			intBanderaErrorSintactico = TRUE;
		}//else

		// Mientras no haya error sintactico ni entrada reconocida
	} while ((!intBanderaErrorSintactico) && (!intBanderaEntradaReconocida));

}

