//main.c
#pragma warning(disable:4996)
#include <stdlib.h>
#define FALSE (0)
#define TRUE (-1)

struct t_token
{
    int intTokenCodigo;
    char *strTokenTextoFuente;
    int intReglon;
    int intColumna;
    struct t_token *ptrSig;
};
typedef struct t_token t_token;

t_token *ptrTokenList = NULL;

void scanner(char *strArchivoNombre);
int parser_PDRC();
int parser_LL();
int ObtenerAccion(int intEstado, int intSimboloT);
int parser_LR(); // <--
int ListaTokens_Imprime();
int ListaToken_Libera();

int main()
{
    int bolRes = FALSE;

    scanner("fuente.txt");
    //La lista que genera el Scanner, la envía al Parser
    ListaTokens_Imprime();
    //bolRes = parser_PDRC(); //Llamada al Parser PDRC
    //bolRes = parser_LL(); //Llamada al Parser LL
	bolRes = parser_LR(); //<-- Llamada al Parser LR
	ListaToken_Libera();

    return bolRes;
}
