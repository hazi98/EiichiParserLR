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
#define SIMBOLO_NO_TERMINAL_Instruccion     2
#define SIMBOLO_NO_TERMINAL_InstrVuelta     3
#define SIMBOLO_NO_TERMINAL_InstrAvanza     4
#define SIMBOLO_NO_TERMINAL_InstrSiChocas   5
#define SIMBOLO_NO_TERMINAL_InstrObjeto     6


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
int     bolPDRCError = FALSE;

int CurrentToken(int intSimboloT)
{
    if (!bolPDRCError)
    {
        if (ptrCurrentToken->intTokenCodigo == intSimboloT)
        {
            return TRUE;
        }//if
        else
        {
            return FALSE;
        }//else
    }//if
}//CurrentToken

void Expect(int intSimboloT)
{
    if (!bolPDRCError)
    {
        if (CurrentToken(intSimboloT))
        {//Token Actual está en la posición correcta de acuerdo a la gramática
            printf("Token Correcto=%s, Renglon=%d, Columna=%d\n",
                   ptrCurrentToken->strTokenTextoFuente,
                   ptrCurrentToken->intReglon,
                   ptrCurrentToken->intColumna);
            ptrCurrentToken = ptrCurrentToken->ptrSig;
        }//if
        else
        {//Hay un error sintáctico
            printf("Error Sintactico Token=%s, Renglon=%d, Columna=%d\n",
                   ptrCurrentToken->strTokenTextoFuente,
                   ptrCurrentToken->intReglon,
                   ptrCurrentToken->intColumna);
            bolPDRCError = TRUE;
        }//else
    }//if
}//Expect

int CurrentTokenInFirst(int intSimboloNT)
{            printf("Error Sintactico Token=%s, Renglon=%d, Columna=%d\n",
                   ptrCurrentToken->strTokenTextoFuente,
                   ptrCurrentToken->intReglon,
                   ptrCurrentToken->intColumna);

    int bolRes = FALSE;

    if (!bolPDRCError)
    {
        switch(intSimboloNT)
        {
            case SIMBOLO_NO_TERMINAL_Programa:
                if (CurrentToken(SIMBOLO_TERMINAL_VDER)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_VIZQ)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_AVANZA)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_SI_CHOCAS)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_RECOGE)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_DEJA)) {bolRes=TRUE; break;}
                break;
            case SIMBOLO_NO_TERMINAL_Instruccion:
                if (CurrentToken(SIMBOLO_TERMINAL_VDER)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_VIZQ)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_AVANZA)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_SI_CHOCAS)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_RECOGE)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_DEJA)) {bolRes=TRUE; break;}
                break;
            case SIMBOLO_NO_TERMINAL_InstrVuelta:
                if (CurrentToken(SIMBOLO_TERMINAL_VDER)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_VIZQ)) {bolRes=TRUE; break;}
                break;
            case SIMBOLO_NO_TERMINAL_InstrAvanza:
                if (CurrentToken(SIMBOLO_TERMINAL_AVANZA)) {bolRes=TRUE; break;}
                break;
            case SIMBOLO_NO_TERMINAL_InstrSiChocas:
                if (CurrentToken(SIMBOLO_TERMINAL_SI_CHOCAS)) {bolRes=TRUE; break;}
                break;
            case SIMBOLO_NO_TERMINAL_InstrObjeto:
                if (CurrentToken(SIMBOLO_TERMINAL_RECOGE)) {bolRes=TRUE; break;}
                if (CurrentToken(SIMBOLO_TERMINAL_DEJA)) {bolRes=TRUE; break;}
                break;
            default:
                break;
        }//switch
    }//if

    return bolRes;
}//CurrentTokenInFirst

void Instruccion();
void InstrVuelta();
void InstrAvanza();
void InstrSiChocas();
void InstrObjeto();

//Programa ::= Instruccion; {Instruccion ;}
void Programa()
{
    if (!bolPDRCError)
    {
        Instruccion();
        Expect(SIMBOLO_TERMINAL_PuntoyComa);
        while(CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_Instruccion))
        {
            Instruccion();
            Expect(SIMBOLO_TERMINAL_PuntoyComa);
        }//while
    }//if
}//Programa

//Instruccion ::= InstrVuelta | InstrAvanza | InstrSiChocas |
//                InstrObjeto
void Instruccion()
{
    if (!bolPDRCError)
    {
        if(CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstrVuelta))
        {
            InstrVuelta();
        }//if
        else if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstrAvanza))
        {
            InstrAvanza();
        }//else if
        else if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstrSiChocas))
        {
            InstrSiChocas();
        }//else if
        else //if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstrObjeto))
        {
            InstrObjeto();
        }//else
    }//if
}//Instruccion

//InstrVuelta ::= "VDER" | "VIZQ"
void InstrVuelta()
{
    if (!bolPDRCError)
    {
        if(CurrentToken(SIMBOLO_TERMINAL_VDER))
        {
            Expect(SIMBOLO_TERMINAL_VDER);
        }//if
        else //if(CurrentToken(SIMBOLO_TERMINAL_VIZQ))
        {
            Expect(SIMBOLO_TERMINAL_VIZQ);
        }//else
    }//if
}//InstrVuelta

//InstrAvanza ::= "AVANZA" "Num"
void InstrAvanza()
{
    if (!bolPDRCError)
    {
        Expect(SIMBOLO_TERMINAL_AVANZA);
        Expect(SIMBOLO_TERMINAL_Num);
    }//if
}//InstrAvanza

//InstrSiChocas ::= "SI_CHOCAS" Instruccion
void InstrSiChocas ()
{
    if (!bolPDRCError)
    {
        Expect(SIMBOLO_TERMINAL_SI_CHOCAS);
        Instruccion();
    }//if
}//InstrSiChocas

//InstrObjeto ::= "RECOGE" | "DEJA"
void InstrObjeto()
{
    if (!bolPDRCError)
    {
        if(CurrentToken(SIMBOLO_TERMINAL_RECOGE))
            Expect(SIMBOLO_TERMINAL_RECOGE);
        //if
        else
            Expect(SIMBOLO_TERMINAL_DEJA);
        //else
    }//if
}//InstrObjeto

int parser_PDRC()
{
    //int bolRes = TRUE;

    ptrCurrentToken = ptrTokenList;

    Programa(); //Símbolo Inicial de la Gramática

    if (bolPDRCError)
      return FALSE; //Reconocimiento Sintáctico Incorrecto
    else
      return TRUE;  //Reconocimiento SIntáctico Correcto
}//parser_PDRC()



