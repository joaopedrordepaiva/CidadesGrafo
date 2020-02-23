#include "CIDADES.H"
#include <stdio.h>

#define SYS_IS_LINUX

#ifdef SYS_IS_LINUX
#include <termios.h>

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old);         /* grab old terminal i/o settings */
    current = old;              /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo)
    {
        current.c_lflag |= ECHO; /* set echo mode */
    }
    else
    {
        current.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch(void)
{
    char ch;
    initTermios(0);
    ch = getchar();
    resetTermios();
    return ch;
}
#endif

#ifdef SYS_IS_WIN
#include <conio.h>
#endif

int main(int argc, char **argv)
{

    CID_tppCabecaCidade pListaDeCidades;

    unsigned char vNumTotalDeCidades;

    char pStringNomeArquivo[64], pStringNomeOutputDeCidades[64], vRespostaUsuario;

    if (argc > 1)
        CID_stringCopia(argv[1], pStringNomeArquivo);

    else
        CID_stringCopia("MunicipiosQtdCasos.txt", pStringNomeArquivo);

    if (argc > 2)
        CID_stringCopia(argv[2], pStringNomeOutputDeCidades);

    else
        CID_stringCopia("outputCidades.txt", pStringNomeOutputDeCidades);

    printf("%s -> %s\n", "MunicipiosQtdCasos.txt", "outputCidades.txt");

    if (CID_criarListaDeCidades(&pListaDeCidades, pStringNomeArquivo, &vNumTotalDeCidades) != CID_CondRetOK)
    {
        printf("Erro na criação da lista\n");
        return 1;
    }

    printf("Criação bem sucedida\n");

    if (CID_armazenarConjuntosVizinhos(pListaDeCidades, "MunicipiosVizinhos.txt") != CID_CondRetOK)
    {
        printf("Erro na armazenação dos conjuntos de vizinhos\n");
        return 1;
    }

    printf("Armazenação dos conjuntos bem sucedida\n");

    printf("Digite o número de camadas de vizinhos desejado:");

    do
        vRespostaUsuario = getch();
    while (vRespostaUsuario < '0' || vRespostaUsuario > '9');

    printf("\n");

    if (CID_armazenarSomasVizinhos(pListaDeCidades, vNumTotalDeCidades, (unsigned char)vRespostaUsuario - '0') != CID_CondRetOK)
    {
        printf("Erro na armazenação das somas de vizinhos\n");
        return 1;
    }

    printf("Armazenação de somas bem sucedida\n");

    if (CID_ordenarListaDeCidades(pListaDeCidades) != CID_CondRetOK)
    {
        printf("Erro na armazenação das somas de vizinhos\n");
        return 1;
    }

    printf("Ordenação de cidades bem sucedida\n");

    printf("\nImpressão iniciada\n\n");

    if (CID_imprimirListaDeCidades(pListaDeCidades) != CID_CondRetOK)
    {
        printf("Erro na impressão da lista\n");
        return 1;
    }

    printf("\nImpressão finalizada\n\n");

    if (CID_destruirListaDeCidades(pListaDeCidades) != CID_CondRetOK)
    {
        printf("Erro na destruição da lista\n");
        return 1;
    }

    printf("Destruição de dados bem sucedida\n");

    return 0;
}