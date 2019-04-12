#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FALSE (0)
#define TRUE (-1)

#define TIPO_NODO_Intermedio        1
#define TIPO_NODO_IntermedioFinal   2
#define TIPO_NODO_Final             3

#define SCANNER_ERROR   -1
#define TOKEN_RECONOCIDO -1

#define ESPACIOS_POR_TAB 8

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

#define AUTOMATA_ESTADOS_NUM 39
#define AUTOMATA_SIMBOLOS_ENTRADA_Y_CONTROL 33

#define AUTOMATA_TIPO_NODO (AUTOMATA_SIMBOLOS_ENTRADA_Y_CONTROL - 2)
#define AUTOMATA_CODIGO_SALIDA (AUTOMATA_SIMBOLOS_ENTRADA_Y_CONTROL - 1)

int MT[AUTOMATA_ESTADOS_NUM][AUTOMATA_SIMBOLOS_ENTRADA_Y_CONTROL] = {
   {8,-1,29,-1,-1,-1,-1,-1,-1,-1,-1,23,14,1,-1,33,33,33,33,33,33,33,33,33,33,-1,34,35,36,37,38,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,2,-1,-1,-1,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_VDER},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_VIZQ},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_AVANZA},
   {-1,-1,-1,-1,-1,-1,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_SI_CHOCAS},
   {-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,25,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_RECOGE},
   {-1,-1,-1,30,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,31,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {32,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Intermedio,SCANNER_ERROR},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_DEJA},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,33,33,33,33,33,33,33,33,33,33,-1,-1,-1,-1,-1,-1,TIPO_NODO_IntermedioFinal,SIMBOLO_TERMINAL_Num},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_PuntoyComa},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_Espacio},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_Tabulador},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_Salto_linea},
   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,TIPO_NODO_Final,SIMBOLO_TERMINAL_EOF}
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

void InsertarEnTokenList(int intTokenCodigo, char *strTokenTextoFuente,
    int intReglon, int intColumna)
{
    t_token *ptrTmp = ptrTokenList;

    t_token *ptrTokenNuevo = (t_token *)malloc(sizeof(t_token));
    ptrTokenNuevo->intTokenCodigo = intTokenCodigo;
    ptrTokenNuevo->strTokenTextoFuente =
        (char *)malloc(strlen(strTokenTextoFuente)+1);
    ptrTokenNuevo->strTokenTextoFuente[0] = '\0';
    strcpy(ptrTokenNuevo->strTokenTextoFuente,strTokenTextoFuente);
    ptrTokenNuevo->intReglon = intReglon;
    ptrTokenNuevo->intColumna = intColumna;
    ptrTokenNuevo->ptrSig = NULL;

    if (ptrTmp == NULL) //La lista está vacía
    {
        ptrTokenList = ptrTokenNuevo;
    }//if
    else
    {
        while(ptrTmp->ptrSig != NULL)
        {
            ptrTmp = ptrTmp->ptrSig;
        }//while
        ptrTmp->ptrSig = ptrTokenNuevo;
    }//else

}//InsertarEnTokenList

void ListaToken_Libera()
{
    t_token *ptrAux = ptrTokenList;
    t_token *ptrAnt;

    while(ptrAux != NULL) //Mientras no sea igual a nulo se libera el nodo
    {
        ptrAnt = ptrAux;
        ptrAux = ptrAux->ptrSig;

        if(ptrAnt->strTokenTextoFuente != NULL)
            free(ptrAnt->strTokenTextoFuente);
        free(ptrAnt);
    }//while

}//ListaToken_Libera

void ListaTokens_Imprime()
{
    t_token *ptrAux = ptrTokenList;

    printf("\nImpresion de Lista\n");

    while(ptrAux != NULL)
    {
        printf("Token Reconocido r[%d],c[%d] - [%d] - Codigo:[%s]\n",
               ptrAux->intReglon,
               ptrAux->intColumna,
               ptrAux->intTokenCodigo,
               ptrAux->strTokenTextoFuente
               );
        ptrAux = ptrAux->ptrSig;
    }//while
}//ListaTokens_Imprime

int ObtenerCodigoSimboloEntrada(char c)
{
    int intCodigoSimboloEntrada = -1;

    switch(c)
    {
        case 'A': intCodigoSimboloEntrada = 0; break;
        case 'C': intCodigoSimboloEntrada = 1; break;
        case 'D': intCodigoSimboloEntrada = 2; break;
        case 'E': intCodigoSimboloEntrada = 3; break;
        case 'G': intCodigoSimboloEntrada = 4; break;
        case 'H': intCodigoSimboloEntrada = 5; break;
        case 'I': intCodigoSimboloEntrada = 6; break;
        case 'J': intCodigoSimboloEntrada = 7; break;
        case 'N': intCodigoSimboloEntrada = 8; break;
        case 'O': intCodigoSimboloEntrada = 9; break;
        case 'Q': intCodigoSimboloEntrada = 10; break;
        case 'R': intCodigoSimboloEntrada = 11; break;
        case 'S': intCodigoSimboloEntrada = 12; break;
        case 'V': intCodigoSimboloEntrada = 13; break;
        case 'Z': intCodigoSimboloEntrada = 14; break;
        case '0': intCodigoSimboloEntrada = 15; break;
        case '1': intCodigoSimboloEntrada = 16; break;
        case '2': intCodigoSimboloEntrada = 17; break;
        case '3': intCodigoSimboloEntrada = 18; break;
        case '4': intCodigoSimboloEntrada = 19; break;
        case '5': intCodigoSimboloEntrada = 20; break;
        case '6': intCodigoSimboloEntrada = 21; break;
        case '7': intCodigoSimboloEntrada = 22; break;
        case '8': intCodigoSimboloEntrada = 23; break;
        case '9': intCodigoSimboloEntrada = 24; break;
        case '_': intCodigoSimboloEntrada = 25; break;
        case ';': intCodigoSimboloEntrada = 26; break;
        case ' ': intCodigoSimboloEntrada = 27; break;
        case '\t': intCodigoSimboloEntrada = 28; break;
        case '\n': intCodigoSimboloEntrada = 29; break;
        case -1: intCodigoSimboloEntrada = 30; break;
    }//switch

    return intCodigoSimboloEntrada;
}//ObtenerCodigoSimboloEntrada

char *ObtenerEtiquetaDelSimboloTerminal(int intCodigoSimboloTerminal)
{
    char *strTokenSimboloTerminal = (char *) malloc (255);
    strTokenSimboloTerminal[0] = '\0';

    switch(intCodigoSimboloTerminal)
    {
        case SIMBOLO_TERMINAL_VDER:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_VDER");
            break;
        case SIMBOLO_TERMINAL_VIZQ:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_VIZQ");
            break;
        case SIMBOLO_TERMINAL_AVANZA:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_AVANZA");
            break;
        case SIMBOLO_TERMINAL_SI_CHOCAS:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_SI_CHOCAS");
            break;
        case SIMBOLO_TERMINAL_RECOGE:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_RECOGE");
            break;
        case SIMBOLO_TERMINAL_DEJA:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_DEJA");
            break;
        case SIMBOLO_TERMINAL_Num:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_Num");
            break;
        case SIMBOLO_TERMINAL_PuntoyComa:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_PuntoyComa");
            break;
        case SIMBOLO_TERMINAL_Espacio:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_Espacio");
            break;
        case SIMBOLO_TERMINAL_Tabulador:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_Tabulador");
            break;
        case SIMBOLO_TERMINAL_Salto_linea:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_Salto_linea");
            break;
        case SIMBOLO_TERMINAL_EOF:
            strcpy(strTokenSimboloTerminal,"SIMBOLO_TERMINAL_EOF");
            break;
        default:
            strcpy(strTokenSimboloTerminal,"ERROR");
            break;
    }//switch

    return strTokenSimboloTerminal;
}//ObtenerEtiquetaDelSimboloTerminal

int EsTokenSeparador(int intCodigoSimboloTerminal)
{
    int boolRespuesta = FALSE;

    switch(intCodigoSimboloTerminal)
    {
        case SIMBOLO_TERMINAL_Espacio:
            boolRespuesta = TRUE;
            break;
        case SIMBOLO_TERMINAL_Tabulador:
            boolRespuesta = TRUE;
            break;
        case SIMBOLO_TERMINAL_Salto_linea:
            boolRespuesta = TRUE;
            break;
        default:
            break;
    }//switch

    return boolRespuesta;
}//EsTokenSeparador

void scanner(char *strArchivoNombre)
{
    FILE *ptrArchivoFuente;
    //s := s0;
      int intEstadoActual = 0;
    int intEstadoSiguiente;
    char c;
    int intCodigoSimboloEntrada;
    int intTipoNodo;
    int intCodigoSimboloTerminal;
    char *strTokenSimboloTerminal;
    int boolBanderaLee = TRUE;
    char *strBuffer;
    int intLenAux;
    int intRenglon = 1;
    int intColumna = 0;
    int intRenglonToken;
    int intColumnaToken;

    strBuffer = (char *)malloc(1024);
    strBuffer[0]='\0';

    ptrArchivoFuente = fopen(strArchivoNombre, "r");

    if (ptrArchivoFuente == NULL)
    {
        perror("Error en archivo fuente.\n");
    }
    else
    {
        do
        {
            if (boolBanderaLee)
            {
                //c := siguientecaracter; //    c := siguientecaracter
                c = getc(ptrArchivoFuente);

                if (c == '\n')
                {
                    intRenglon++;
                    intColumna=0;
                }//else
                else
                {
                    if (c == '\t')
                    {
                        intColumna = intColumna
                            + (ESPACIOS_POR_TAB - (intColumna % ESPACIOS_POR_TAB));
                    }
                    else
                        intColumna++;
                }//else

            }//if

            if (intEstadoActual == 0)
            {
                intRenglonToken = intRenglon;
                intColumnaToken = intColumna;
            }//if

            if (!boolBanderaLee)
                boolBanderaLee = TRUE;

            intCodigoSimboloEntrada = ObtenerCodigoSimboloEntrada(c);

            //printf("Car=%c - ColMT=%d Edo=%d\n",c,intCodigoSimboloEntrada,intEstadoActual);
            //    s := mov[s,c];
            intEstadoSiguiente = MT[intEstadoActual][intCodigoSimboloEntrada];
            intTipoNodo =  MT[intEstadoActual][AUTOMATA_TIPO_NODO];

            //if s está en F then
            //    return "si"
            //else return "no";
            if((intEstadoSiguiente == TOKEN_RECONOCIDO)
                 && ((intTipoNodo == TIPO_NODO_Final)
                          || (intTipoNodo == TIPO_NODO_IntermedioFinal)
                        )
               )
            {//Token Reconocido
                intCodigoSimboloTerminal = MT[intEstadoActual][AUTOMATA_CODIGO_SALIDA];

                if (!EsTokenSeparador(intCodigoSimboloTerminal))
                {
                    strTokenSimboloTerminal =
                        ObtenerEtiquetaDelSimboloTerminal(intCodigoSimboloTerminal);

                    printf("Token Reconocido r[%d],c[%d] - [%d]:[%s] - Codigo:[%s]\n",
                           intRenglonToken,
                           intColumnaToken,
                           intCodigoSimboloTerminal,
                           strTokenSimboloTerminal,
                           strBuffer);

                    InsertarEnTokenList(intCodigoSimboloTerminal,strBuffer,
                            intRenglonToken, intColumnaToken);

                    free(strTokenSimboloTerminal);
                }//if

                intEstadoActual = 0;
                boolBanderaLee = FALSE;
                strBuffer[0] = '\0';
            }
            else if (intEstadoSiguiente == SCANNER_ERROR)
            {
                printf("Error Lexico r[%d],c[%d]\n",
                            intRenglonToken,
                            intColumnaToken);
                intEstadoActual = 0;
                strBuffer[0] = '\0';
            }
            else
            {
                intEstadoActual = intEstadoSiguiente;

                //Se concatena el caracter al buffer
                intLenAux = strlen(strBuffer);
                strBuffer[intLenAux] = c;
                strBuffer[intLenAux+1] = '\0';

            }//else

        } while (c != EOF);
        //while c <> eof do

        InsertarEnTokenList(SIMBOLO_TERMINAL_EOF,"SIMBOLO_TERMINAL_EOF",
            intRenglonToken, intColumnaToken);

    }
}//scanner
