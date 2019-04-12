//parser_LL.c
#include <stdlib.h>
#include <stdio.h>

#define FALSE (0)
#define TRUE (-1)

#define SIMBOLO_TERMINAL_VDER 1
#define SIMBOLO_TERMINAL_VIZQ 2
#define SIMBOLO_TERMINAL_AVANZA 3
#define SIMBOLO_TERMINAL_SI_CHOCAS 4
#define SIMBOLO_TERMINAL_RECOGE 5
#define SIMBOLO_TERMINAL_DEJA 6
#define SIMBOLO_TERMINAL_Num 7
#define SIMBOLO_TERMINAL_PuntoyComa 8
#define SIMBOLO_TERMINAL_Espacio 9
#define SIMBOLO_TERMINAL_Tabulador 10
#define SIMBOLO_TERMINAL_Salto_linea 11
#define SIMBOLO_TERMINAL_EOF 12

#define SIMBOLO_NO_TERMINAL_Programa        1
#define SIMBOLO_NO_TERMINAL_Programa2       2
#define SIMBOLO_NO_TERMINAL_Instruccion     3
#define SIMBOLO_NO_TERMINAL_InstrVuelta     4
#define SIMBOLO_NO_TERMINAL_InstrAvanza     5
#define SIMBOLO_NO_TERMINAL_InstrSiChocas   6
#define SIMBOLO_NO_TERMINAL_InstrObjeto     7

#define TIPO_SIMBOLO_NO_TERMINAL    1
#define TIPO_SIMBOLO_TERMINAL       2

#define SIMBOLOS_NO_TERMINALES_NUMMAX 7
#define SIMBOLOS_TERMINALES_NUMMAX 12

//MATRIZ DE RECONOCIMIENTO LL
int MR[SIMBOLOS_NO_TERMINALES_NUMMAX][SIMBOLOS_TERMINALES_NUMMAX] = {
   {1,1,1,1,1,1,-1,-1,-1,-1,-1,-1},
   {2,2,2,2,2,2,-1,-1,-1,-1,-1,3},
   {4,4,5,6,7,7,-1,-1,-1,-1,-1,-1},
   {8,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
   {-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1},
   {-1,-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1},
   {-1,-1,-1,-1,12,13,-1,-1,-1,-1,-1,-1}
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
t_token *ptrCurrentToken;

//STACK DE RECONOCIMIENTO LL
struct t_StackLL
{
    int intSimboloTipo; //Si es Terminal o No Terminal
    int intSimboloCodigo; //Código Numérico (#define) de T o NT

    struct t_StackLL *ptrSig;
};
typedef struct t_StackLL t_StackLL;
t_StackLL *ptrStackLLTop = NULL;

void pushLL(int intSimboloTipo, int intSimboloCodigo)
{
    t_StackLL *nuevo = (t_StackLL *)malloc(sizeof(t_StackLL));
    nuevo->intSimboloTipo = intSimboloTipo;
    nuevo->intSimboloCodigo = intSimboloCodigo;
    nuevo->ptrSig = NULL;

    if (ptrStackLLTop != NULL) //Hay elementos en el Stack
    {
        nuevo->ptrSig = ptrStackLLTop;
    }//if
    ptrStackLLTop = nuevo;
}//pushLL

void pushLL_T(int intSimboloCodigo)
{
    pushLL(TIPO_SIMBOLO_TERMINAL, intSimboloCodigo);
}//pushLL_T

void pushLL_NT(int intSimboloCodigo)
{
    pushLL(TIPO_SIMBOLO_NO_TERMINAL, intSimboloCodigo);
}//pushLL_NT

void popLL()
{
    t_StackLL *aux;

    if (ptrStackLLTop != NULL) //Hay elementos en el Stack
    {
        aux = ptrStackLLTop;
        ptrStackLLTop = ptrStackLLTop->ptrSig;
        free(aux);
    }//if
}//popLL

void vaciar_StackLL()
{
    while(ptrStackLLTop != NULL)
        popLL();

}//vaciar_StackLL

int stack_top_es_NT()
{
    int bolRes = FALSE;

    if (ptrStackLLTop != NULL)
    {
        if(ptrStackLLTop->intSimboloTipo == TIPO_SIMBOLO_NO_TERMINAL)
            bolRes = TRUE;
    }//if

    return bolRes;
}//stack_top_es_NT

void imprimeT(int intSimboloCodigo)
{
    switch(intSimboloCodigo)
    {
        case SIMBOLO_TERMINAL_VDER: printf("T_VDER"); break;
        case SIMBOLO_TERMINAL_VIZQ: printf("T_VIZQ"); break;
        case SIMBOLO_TERMINAL_AVANZA: printf("T_AVANZA"); break;
        case SIMBOLO_TERMINAL_SI_CHOCAS : printf("T_SI_CHOCAS"); break;
        case SIMBOLO_TERMINAL_RECOGE: printf("T_RECOGE"); break;
        case SIMBOLO_TERMINAL_DEJA: printf("T_DEJA"); break;
        case SIMBOLO_TERMINAL_Num: printf("T_Num"); break;
        case SIMBOLO_TERMINAL_PuntoyComa: printf("T_PuntoyComa"); break;
        case SIMBOLO_TERMINAL_Espacio: printf("T_Espacio"); break;
        case SIMBOLO_TERMINAL_Tabulador: printf("T_Tabulador"); break;
        case SIMBOLO_TERMINAL_Salto_linea : printf("T_Salto_linea"); break;
        case SIMBOLO_TERMINAL_EOF: printf("T_EOF"); break;
        default:pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            printf("ERROR");
            break;
    }//switch
}//imprimeT

void imprimeNT(int intSimboloCodigo)
{
    switch(intSimboloCodigo)
    {
        case SIMBOLO_NO_TERMINAL_Programa: printf("NT_Programa"); break;
        case SIMBOLO_NO_TERMINAL_Programa2: printf("NT_Programa2"); break;
        case SIMBOLO_NO_TERMINAL_Instruccion: printf("NT_Instruccion"); break;
        case SIMBOLO_NO_TERMINAL_InstrVuelta: printf("NT_InstrVuelta"); break;
        case SIMBOLO_NO_TERMINAL_InstrAvanza: printf("NT_InstrAvanza"); break;
        case SIMBOLO_NO_TERMINAL_InstrSiChocas: printf("NT_InstrSiChocas"); break;
        case SIMBOLO_NO_TERMINAL_InstrObjeto: printf("NT_InstrObjeto"); break;
        default:
            printf("ERROR");
            break;
    }//switch
}//imprimeNT

void imprime_entrada()
{
    t_token *aux = ptrCurrentToken;

    printf("Entrada: ");
    while(aux != NULL)
    {
        imprimeT(aux->intTokenCodigo);
        printf("   ");
        aux = aux->ptrSig;
    }//while
    printf("\n");
}//imprime_entrada

void stack_imprime2(t_StackLL *nodoStack)
{
    if (nodoStack != NULL)
    {
        stack_imprime2(nodoStack->ptrSig);
        switch(nodoStack->intSimboloTipo)
        {
            case TIPO_SIMBOLO_TERMINAL:
                imprimeT(nodoStack->intSimboloCodigo);
                break;
            case TIPO_SIMBOLO_NO_TERMINAL:
                imprimeNT(nodoStack->intSimboloCodigo);
                break;
            default:
                printf("Error");
                break;
        }//switch
        printf("   ");
    }//if
}//stack_imprime2

void stack_imprime()
{
    printf("Stack: ");
    stack_imprime2(ptrStackLLTop);
    printf("\n");
}//stack_imprime

void imprime_regla(int intNumReglaObtenidaDeMR)
{
    switch(intNumReglaObtenidaDeMR)
    {
        case 1: printf("1. Programa -> Instruccion ; Programa2"); break;
        case 2: printf("2. Programa2 -> Instruccion ; Programa2"); break;
        case 3: printf("3. Programa2 -> epsilon"); break;
        case 4: printf("4. Instruccion -> InstrVuelta"); break;
        case 5: printf("5. Instruccion -> InstrAvanza"); break;
        case 6: printf("6. Instruccion -> InstrSiChocas"); break;
        case 7: printf("7. Instruccion -> InstrObjeto"); break;
        case 8: printf("8. InstrVuelta -> VDER"); break;
        case 9: printf("9. InstrVuelta -> VIZQ"); break;
        case 10: printf("10. InstrAvanza -> AVANZA Num"); break;
        case 11: printf("11. InstrSiChocas -> SI_CHOCAS Instruccion"); break;
        case 12: printf("12. InstrObjeto -> RECOGE"); break;
        case 13: printf("13. InstrObjeto -> DEJA"); break;
        default: break;
    }//switch
    printf("\n");
}//imprime_regla

void SustituyeNTenStackPorParteDerechaDeLaRegla(int intNumReglaObtenidaDeMR)
{
    //Sacar el NT arriba del Stack
    popLL();
    //Insertar los símbolos de la parte derecha de la regla (RHS) en orden inverso en el Stack
    switch(intNumReglaObtenidaDeMR)
    {
        case 1: //1. Programa -> Instrucción ; Programa2
            pushLL_NT(SIMBOLO_NO_TERMINAL_Programa2);
            pushLL_T(SIMBOLO_TERMINAL_PuntoyComa);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            break;
        case 2: //2. Programa2 -> Instruccion ; Programa2
            pushLL_NT(SIMBOLO_NO_TERMINAL_Programa2);
            pushLL_T(SIMBOLO_TERMINAL_PuntoyComa);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            break;
        case 3: //3. Programa2 -> epsilon
            break;
        case 4: //4. Instruccion -> InstrVuelta
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstrVuelta);
            break;
        case 5: //5. Instruccion -> InstrAvanza
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstrAvanza);
            break;
        case 6: //6. Instruccion -> InstrSiChocas
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstrSiChocas);
            break;
        case 7: //7. Instruccion -> InstrObjeto
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstrObjeto);
            break;
        case 8: //8. InstrVuelta -> VDER
            pushLL_T(SIMBOLO_TERMINAL_VDER);
            break;
        case 9: //9. InstrVuelta -> VIZQ
            pushLL_T(SIMBOLO_TERMINAL_VIZQ);
            break;
        case 10: //10. InstrAvanza -> AVANZA Num
            pushLL_T(SIMBOLO_TERMINAL_Num);
            pushLL_T(SIMBOLO_TERMINAL_AVANZA);
            break;
        case 11: //11. InstrSiChocas -> SI_CHOCAS Instruccion
            pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            pushLL_T(SIMBOLO_TERMINAL_SI_CHOCAS);
            break;
        case 12: //12. InstrObjeto -> RECOGE
            pushLL_T(SIMBOLO_TERMINAL_RECOGE);
            break;
        case 13: //13. InstrObjeto -> DEJA
            pushLL_T(SIMBOLO_TERMINAL_DEJA);
            break;
    }//switch
}//SustituyeNTenStackPorParteDerechaDeLaRegla

int ParserLL_AplicarRegla()
{
    int intNumReglaObtenidaDeMR;

    //Se obtiene una regla de la Matriz de Reconocimiento
    intNumReglaObtenidaDeMR =
        MR[ptrStackLLTop->intSimboloCodigo - 1][ptrCurrentToken->intTokenCodigo - 1];

    if (intNumReglaObtenidaDeMR > 0) //Regla Gramatical Válida
    {
        imprime_regla(intNumReglaObtenidaDeMR);
        SustituyeNTenStackPorParteDerechaDeLaRegla(intNumReglaObtenidaDeMR);
    }//if
    else
    {
        return TRUE; //Hay Error Sintáctico
    }//else

    return FALSE; //No hay Error SIntáctico
}//ParserLL_AplicarRegla

int parser_LL()
{
    int bolBanderaErrorSintactico = FALSE;
    int bolBanderaEntradaReconocida = FALSE;

    //Inicializa el apuntador de recorrido de la cadena de entrada
    ptrCurrentToken = ptrTokenList;

    //Condiciones Iniciales del Stack
    pushLL_T(SIMBOLO_TERMINAL_EOF);
    pushLL_NT(SIMBOLO_NO_TERMINAL_Programa);

    do
    {
        printf("==========================================================\n");
        stack_imprime();
        printf("----------------------------------------------\n");
        imprime_entrada();
        printf("----------------------------------------------\n");

        //Si lo que está arriba del Stack es un No Terminal
        if (stack_top_es_NT())
        {
            //Aplicar Regla Gramatical
            bolBanderaErrorSintactico = ParserLL_AplicarRegla();

            if (bolBanderaErrorSintactico == TRUE)
            {
                printf("Error Sintactico Token=%s, Renglon=%d, Columna=%d\n",
                       ptrCurrentToken->strTokenTextoFuente,
                       ptrCurrentToken->intReglon,
                       ptrCurrentToken->intColumna);
            }//if
        }//if
        else //Si lo que está arriba del Stack es un Terminal
        {
            //Si el stack no está vacío y la entrada no está vacía
            if ((ptrStackLLTop != NULL) && (ptrCurrentToken != NULL))
            {
                //Si el Top del Stack y la Entrada son los mismos terminales
                if ((ptrStackLLTop->intSimboloCodigo == ptrCurrentToken->intTokenCodigo))
                {
                    //Entrada Reconocida = $ arriba stack y $ en la entrada
                    if (ptrStackLLTop->intSimboloCodigo == SIMBOLO_TERMINAL_EOF)
                    {
                        printf("ACEPTAR\n");
                        bolBanderaEntradaReconocida = TRUE;
                        printf("Entrada Reconocida. Analisis Sintactico Correcto.");
                    }//if
                    else //Expect: Terminal arriba del Stack = Terminal enviado por Scanner
                    {
                        printf("EXPECT\n");
                        popLL();
                        ptrCurrentToken = ptrCurrentToken->ptrSig;
                    }//else
                }//if
                else //El Top del Stack y la Entrada son Diferentes Terminales
                {    // => Error sintáctico
                    bolBanderaErrorSintactico = TRUE;
                    printf("Error Sintactico Token=%s, Renglon=%d, Columna=%d\n",
                           ptrCurrentToken->strTokenTextoFuente,
                           ptrCurrentToken->intReglon,
                           ptrCurrentToken->intColumna);
                }//else
            }//if
            else //El stack o la entrada está vacía
            {
                bolBanderaErrorSintactico = TRUE;
                if (ptrStackLLTop == NULL)
                {
                    printf("La Pila de Reconocimiento esta vacia\n");
                }//if
                else if (ptrCurrentToken == NULL)
                {
                    printf("Ya no existen tokens de entrada desde el Scanner\n");
                }//else if
            }//else
        }//else

    } while ((!bolBanderaErrorSintactico) && (!bolBanderaEntradaReconocida));

    vaciar_StackLL();

    return bolBanderaErrorSintactico;
}//paser_LL
