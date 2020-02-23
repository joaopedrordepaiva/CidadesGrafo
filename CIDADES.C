/****************************************************************************
*   $MCI Módulo de implementação: Módulo CIDADES
*
*   Arquivo gerado:              CIDADES.C
*   Letras identificadoras:      CID
*
*   Projeto: Projeto Cidade
*   Autores: jpp - João Pedro Paiva
*
*   $LIM Limites da implementação:
*       Número de vizinhos: 0 até 32.
*       Número de cidades: 0 até 255.
*       Número de casos: 0 até 4,294,967,295.
*       Tamanho dos nomes dos arquivos de input e output: 0 até 59
*           caracteres, excluindo a extensão (.txt).
*       Comprimento de cada linha do arquivo de input: 0 até 63 caracteres.
*
*   $HA Histórico de evolução:
*       Versão  Autor   Data        Observações
*       1.00    jpp     26/01/2020  Início do desenvolvimento
*       2.00    jpp     28/01/2020  stringCopia e ParseCidadesEQuantidades
*       3.00    jpp     29/01/2020  Tipo conteudo, função de criação da
*                                   lista, função de impressão da lista
*                                   função pow, função de destruição.
*                                   
*       4.00    jpp     30/01/2020  Função de armazenamento de quantidades
*                                   dos vizinhos de cada nó até a camada
*                                   desejada, função de ordenação.
*
****************************************************************************/

#include "LISTA.H"
#include "CIDADES.H"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/********************* Variáveis encapuladas no módulo *********************/

typedef struct CID_tagConteudoCidade
{
    char *pStringNomeCidade;

    unsigned long vConjuntoVizinhos;

    unsigned int vQuantidadeNucleo;
    unsigned int vQuantidadeCamadasDeVizinhos;

} * CID_tppConteudoCidade;

/************** Protótipos das funções encapuladas no módulo ***************/

CID_tpCondRet CID_stringParseCidadesEQuantidades(char pString[], char **ppStringNomeCidade, char **ppStringQuantidade);

CID_tpCondRet CID_stringParseVizinhos(char *pStringVizinhos, unsigned char *pCidadeAtual, unsigned long *pConjuntoVizinhos);

CID_tpCondRet CID_somaQuantidadeVizinhosPorConjunto(CID_tppCabecaCidade pListaDeCidades, unsigned char vNumTotalDeCidades, unsigned char vCidadeAtual, unsigned long vConjuntoVizinhos, unsigned int *pSomaQuantidadesVizinhos, unsigned long *pConjuntoVizinhosCamada, unsigned char vCamadas);

unsigned char CID_stringComprimento(char pString[]);

CID_tpCondRet CID_stringCopia(char pString1[], char pString2[]);

CID_tpCondRet CID_vaiPara(CID_tppCabecaCidade pLista, unsigned char vPos);

unsigned int CID_pow(unsigned int vBase, unsigned int vPower);

unsigned int CID_converteStringParaUInt(char *pString);

CID_tpCondRet CID_destruirConteudoDeCidade(CID_tppConteudoCidade pConteudoCidade);

/**************** Código das funções exportadas pelo módulo ****************/

/****************************************************************************
*
*	$FC Função:
*       CID Armazena várias cidades de um arquivo txt em uma lista.
*
****************************************************************************/
CID_tpCondRet CID_criarListaDeCidades(CID_tppCabecaCidade *ppListaDeCidades, char *pStringArquivoDeCidades, unsigned char *pNumTotalDeCidades)
{

    FILE *pArquivoDeCidades;
    CID_tppConteudoCidade pConteudoCidade;
    unsigned int vQuantidadeConvertida;
    char pStringCidade[64], *pStringNomeCidade, *pStringQuantidade;

    if (LIS_criarLista((void (*)(void *))CID_destruirConteudoDeCidade, ppListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetFaltouMemoria;

    pArquivoDeCidades = fopen(pStringArquivoDeCidades, "r");

    if (!pArquivoDeCidades)
        return CID_CondRetFaltouMemoria;

    *pNumTotalDeCidades = 0;

    while (fgets(pStringCidade, 64, pArquivoDeCidades))
    {

        if (CID_stringParseCidadesEQuantidades(pStringCidade, &pStringNomeCidade, &pStringQuantidade) != CID_CondRetOK)
            return CID_CondRetFaltouMemoria;

        vQuantidadeConvertida = CID_converteStringParaUInt(pStringQuantidade);

        free(pStringQuantidade);

        pConteudoCidade = (CID_tppConteudoCidade)malloc(sizeof(struct CID_tagConteudoCidade));

        pConteudoCidade->pStringNomeCidade = pStringNomeCidade;

        pConteudoCidade->vQuantidadeNucleo = vQuantidadeConvertida;

        pConteudoCidade->vQuantidadeCamadasDeVizinhos = 0;

        pConteudoCidade->vConjuntoVizinhos = 0;

        if (LIS_InserirNoApos(*ppListaDeCidades, (void *)pConteudoCidade) != LIS_CondRetOK)
            return CID_CondRetFaltouMemoria;

        ++*pNumTotalDeCidades;
    }

    fclose(pArquivoDeCidades);

    if (LIS_vaiParaPrimeiroNo(*ppListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    return CID_CondRetOK;
}

/****************************************************************************
*
*	$FC Função:
*       CID Armazena conjunto de vizinhos descritos no txt.
*
****************************************************************************/
CID_tpCondRet CID_armazenarConjuntosVizinhos(CID_tppCabecaCidade pListaDeCidades, char *pStringArquivoDeVizinhos)
{

    FILE *pArquivoDeVizinhos;
    CID_tppConteudoCidade pConteudoCidade;
    char pStringVizinhos[64];
    unsigned long vConjuntoVizinhos;
    unsigned char vCidadeAtual;

    if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    pArquivoDeVizinhos = fopen(pStringArquivoDeVizinhos, "r");

    if (!pArquivoDeVizinhos)
        return CID_CondRetFaltouMemoria;

    while (fgets(pStringVizinhos, 64, pArquivoDeVizinhos))
    {
        CID_stringParseVizinhos(pStringVizinhos, &vCidadeAtual, &vConjuntoVizinhos);
        CID_vaiPara(pListaDeCidades, vCidadeAtual);

        if (LIS_obterConteudo(pListaDeCidades, (void **)&pConteudoCidade) != LIS_CondRetOK)
            return CID_CondRetProblemaDeLista;

        pConteudoCidade->vConjuntoVizinhos = vConjuntoVizinhos;
    }

    fclose(pArquivoDeVizinhos);

    if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    return CID_CondRetOK;
}

/****************************************************************************
*
*	$FC Função:
*       CID Armazena a soma das quantidades dos vizinhos até a camada
*           desejada.
*
****************************************************************************/
CID_tpCondRet CID_armazenarSomasVizinhos(CID_tppCabecaCidade pListaDeCidades, unsigned char vNumTotalDeCidades, unsigned char vCamadas)
{

    CID_tppConteudoCidade pConteudoCidade;
    unsigned long vConjuntoVizinhosCamada;
    unsigned int vSomaQuantidadesVizinhos;
    unsigned char vCidadeAtual;

    if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    vCidadeAtual = 0;


    do
    {
        if (LIS_obterConteudo(pListaDeCidades, (void **)&pConteudoCidade) != LIS_CondRetOK)
            return CID_CondRetProblemaDeLista;

        if (!vCamadas)
        {
            pConteudoCidade->vQuantidadeCamadasDeVizinhos = pConteudoCidade->vQuantidadeNucleo;
            continue;
        }


        if (CID_somaQuantidadeVizinhosPorConjunto(pListaDeCidades, vNumTotalDeCidades, vCidadeAtual, pConteudoCidade->vConjuntoVizinhos, &vSomaQuantidadesVizinhos, &vConjuntoVizinhosCamada, vCamadas) != CID_CondRetOK)
            return CID_CondRetProblemaDeLista;

        pConteudoCidade->vQuantidadeCamadasDeVizinhos = vSomaQuantidadesVizinhos;

        vCidadeAtual++;

    } while (LIS_vaiParaProximoNo(pListaDeCidades) == LIS_CondRetOK);

    if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    return CID_CondRetOK;
}

/****************************************************************************
*
*	$FC Função:
*       CID Ordena lista de cidades da maior soma das quantidades dos
*           vizinhos para a menor soma das quantidades dos vizinhos
*           utilizando o método bubble sort.
*
****************************************************************************/
CID_tpCondRet CID_ordenarListaDeCidades(CID_tppCabecaCidade pListaDeCidades)
{

    CID_tppConteudoCidade pConteudoCidadeUm, pConteudoCidadeDois;

    struct CID_tagConteudoCidade pConteudoCidadeAux;

    unsigned char vHouveTroca;

    vHouveTroca = 0;

    if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    do
    {
        if (LIS_obterConteudo(pListaDeCidades, (void **)&pConteudoCidadeUm) != LIS_CondRetOK)
            return CID_CondRetProblemaDeLista;

        else if (LIS_vaiParaProximoNo(pListaDeCidades) != LIS_CondRetOK)

            if (!vHouveTroca)
                return CID_CondRetOK;

            else if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
                return CID_CondRetProblemaDeLista;

            else
                vHouveTroca = 0;

        else
        {
            if (LIS_obterConteudo(pListaDeCidades, (void **)&pConteudoCidadeDois) != LIS_CondRetOK)
                return CID_CondRetProblemaDeLista;


            else if (pConteudoCidadeUm->vQuantidadeCamadasDeVizinhos < pConteudoCidadeDois->vQuantidadeCamadasDeVizinhos)
            {
                pConteudoCidadeAux = *pConteudoCidadeUm;
                *pConteudoCidadeUm = *pConteudoCidadeDois;
                *pConteudoCidadeDois = pConteudoCidadeAux;
                vHouveTroca = 1;
            }

        }

    } while (1);

    if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    return CID_CondRetOK;
}

/****************************************************************************
*
*	$FC Função:
*       CID Imprime lista de cidades.
*
****************************************************************************/
CID_tpCondRet CID_imprimirListaDeCidades(CID_tppCabecaCidade pListaDeCidades)
{

    CID_tppConteudoCidade pConteudoCidade;

    if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    do
    {
        if (LIS_obterConteudo(pListaDeCidades, (void **)&pConteudoCidade) != LIS_CondRetOK)
            return CID_CondRetProblemaDeLista;

        printf("%s : %u\n", pConteudoCidade->pStringNomeCidade, pConteudoCidade->vQuantidadeCamadasDeVizinhos);

    } while (LIS_vaiParaProximoNo(pListaDeCidades) == LIS_CondRetOK);

    if (LIS_vaiParaPrimeiroNo(pListaDeCidades) != LIS_CondRetOK)
        return CID_CondRetProblemaDeLista;

    return CID_CondRetOK;
}

/****************************************************************************
*
*	$FC Função:
*       CID Destrói lista de cidades.
*
****************************************************************************/
CID_tpCondRet CID_destruirListaDeCidades(CID_tppCabecaCidade pListaDeCidades)
{
    LIS_DestruirLista(pListaDeCidades);

    return CID_CondRetOK;
}

/****************************************************************************
*
*	$FC Função:
*       CID Copia pString1 para pString2.
*
****************************************************************************/
CID_tpCondRet CID_stringCopia(char pString1[], char pString2[])
{

    int vCont;

    vCont = 0;

    do
        if (pString1[vCont] != '\n')
            pString2[vCont] = pString1[vCont];

    while (pString1[vCont++]);

    return CID_CondRetOK;
}

/**************** Código das funções encapsuladas no módulo ****************/

/****************************************************************************
*
*	$FC Função:
*       CID Quebra string do arquivo txt em uma string com o nome da cidade e
*       uma string com a quantidade.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais do vetor de caracteres.
*
*
*  $EP Parâmetros
*       $P pString - O parâmetro que receberá o endereço do primeiro caractere
*           da string que deseja-se quebrar.
*           Este parâmetro é passado por referência.
*       $P pStringNomeCidade - O parâmetro que receberá o ponteiro para o
*           endereço do primeiro caractere da string de nome.
*           Este parâmetro é passado por referência.
*       $P pStringQuantidades - O parâmetro que receberá o ponteiro para o
*           endereço do primeiro caractere da string de qunatidade.
*           Este parâmetro é passado por referência.
*
****************************************************************************/
CID_tpCondRet CID_stringParseCidadesEQuantidades(char pString[], char **ppStringNomeCidade, char **ppStringQuantidade)
{

    int vTamString;

    char *pPrimeiroCharStringQtd;

    for (vTamString = 0; pString[vTamString]; vTamString++)
        if (pString[vTamString] == ':')
        {
            pString[vTamString - 1] = '\0';
            *ppStringNomeCidade = (char *)malloc(vTamString - 1);
            if (!*ppStringNomeCidade)
                return CID_CondRetFaltouMemoria;
            CID_stringCopia(pString, *ppStringNomeCidade);
            pPrimeiroCharStringQtd = pString + vTamString + 2;
        }

    *ppStringQuantidade = (char *)malloc(pString + vTamString - pPrimeiroCharStringQtd);

    if (!*ppStringQuantidade)
        return CID_CondRetFaltouMemoria;

    CID_stringCopia(pPrimeiroCharStringQtd, *ppStringQuantidade);

    return CID_CondRetOK;
}
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       O nome da cidade e a quantidade foram retornados por referência.
*		Valem as assertivas estruturais do vetor de caracteres.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*       CID_CondRetFaltouMemoria - Malloc falhou.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Analiza string do arquivo txt para somar quantidades de vizinhos.
*
*
*   $AE Assertivas de entrada esperadas:
*       Lista pode estar em qualquer posição.
*		Valem as assertivas estruturais da lista duplamente encadeada com
*       cabeça.
*
*
*  $EP Parâmetros
*       $P pListaDeCidades - O parâmetro que receberá o endereço da cabeça da
*           lista de cidades.
*           Este parâmetro é passado por referência.
*       $P pStringVizinhos - O parâmetro que receberá o endereço do primeiro
*           caractere da string que deseja-se aalisar.
*           Este parâmetro é passado por referência.
*
****************************************************************************/
CID_tpCondRet CID_stringParseVizinhos(char *pStringVizinhos, unsigned char *pCidadeAtual, unsigned long *pConjuntoVizinhos)
{
    unsigned char vVizinhoAtual;

    int vTamString;

    char vTamStringNum;

    vTamString = 0;

    while (pStringVizinhos[vTamString] >= '0' && pStringVizinhos[vTamString] <= '9')
        vTamString++;

    pStringVizinhos[vTamString] = '\0';
    *pCidadeAtual = (unsigned char)CID_converteStringParaUInt(pStringVizinhos);

    *pConjuntoVizinhos = (unsigned long)0x1 << *pCidadeAtual;

    while (pStringVizinhos[vTamString] < '0' || pStringVizinhos[vTamString] > '9')
        vTamString++;

    vTamStringNum = 0;

    while (pStringVizinhos[vTamString])
    {
        vTamStringNum++;

        if (pStringVizinhos[vTamString] == ' ' || pStringVizinhos[vTamString] == '\n')
        {
            pStringVizinhos[vTamString] = '\0';

            vVizinhoAtual = (unsigned char)CID_converteStringParaUInt(pStringVizinhos + vTamString - vTamStringNum + 1);

            *pConjuntoVizinhos |= (unsigned long)0x1 << vVizinhoAtual;

            vTamStringNum = 0;
        }

        vTamString++;
    }

    return CID_CondRetOK;
}
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       A soma das quantidades dos vizinhos de uma cidade foi determinada.
*       Lista está na posição da cidade atual.
*		Valem as assertivas estruturais da lista duplamente encadeada com
*       cabeça.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Retorna a soma das quantidades dos vizinhos marcados no conjunto.
*
*
*   $AE Assertivas de entrada esperadas:
*       Lista está na posição da cidade atual.
*       Um dos vizinhos marcados no conjunto pode ser igual à cidade atual.
*		Valem as assertivas estruturais da lista duplamente encadeada com
*       cabeça.
*
*
*  $EP Parâmetros
*       $P pListaDeCidades - O parâmetro que receberá o endereço da cabeça da
*           lista de cidades.
*           Este parâmetro é passado por referência.
*       $P vCidadeAtual - O parâmetro que receberá o valor numérico da cidade
*           atual para que possamos navegar na lista e retornar à posição
*           inicial.
*           Este parâmetro é passado por valor.
*       $P vConjuntoVizinhos - O parâmetro que receberá o conjunto de vizinhos
*           cuja soma das quantidades deseja-se determinar.
*           Este parâmetro é passado por valor.
*       $P vSomaQuantidadesVizinhos - O parâmetro que receberá a soma das
*           quantidades dos vizinhos.
*           Este parâmetro é passado por referência.
*
****************************************************************************/
CID_tpCondRet CID_somaQuantidadeVizinhosPorConjunto(CID_tppCabecaCidade pListaDeCidades, unsigned char vNumTotalDeCidades, unsigned char vCidadeAtual, unsigned long vConjuntoVizinhos, unsigned int *pSomaQuantidadesVizinhos, unsigned long *pConjuntoVizinhosCamada, unsigned char vCamadas)
{

    CID_tppConteudoCidade pConteudoCidade;
    short vDirecaoEPassos;
    unsigned char vVizinhoAnterior, vVizinhoAtual;

    if (!vCamadas)
        return CID_CondRetOK;

    *pConjuntoVizinhosCamada = vConjuntoVizinhos;

    *pSomaQuantidadesVizinhos = 0;

    vVizinhoAnterior = vCidadeAtual;

    for (int i = 0; i < vNumTotalDeCidades; i++)
    {
        if (((vConjuntoVizinhos >> i) & (unsigned long)0x1) == (unsigned long)0x0)
            continue;

        vVizinhoAtual = i;

        vDirecaoEPassos = (short)(vVizinhoAtual - vVizinhoAnterior);

        if (vDirecaoEPassos > 0)
        {
            while (vDirecaoEPassos--)
                if (LIS_vaiParaProximoNo(pListaDeCidades) != LIS_CondRetOK)
                    return CID_CondRetProblemaDeLista;

            if (LIS_obterConteudo(pListaDeCidades, (void **)&pConteudoCidade) != LIS_CondRetOK)
                return CID_CondRetProblemaDeLista;

            *pSomaQuantidadesVizinhos += pConteudoCidade->vQuantidadeNucleo;

            *pConjuntoVizinhosCamada |= pConteudoCidade->vConjuntoVizinhos;
        }

        else
        {
            while (vDirecaoEPassos++)
                if (LIS_vaiParaNoAnterior(pListaDeCidades) != LIS_CondRetOK)
                    return CID_CondRetProblemaDeLista;

            if (LIS_obterConteudo(pListaDeCidades, (void **)&pConteudoCidade) != LIS_CondRetOK)
                return CID_CondRetProblemaDeLista;

            *pSomaQuantidadesVizinhos += pConteudoCidade->vQuantidadeNucleo;
            *pConjuntoVizinhosCamada |= pConteudoCidade->vConjuntoVizinhos;
        }

        vVizinhoAnterior = vVizinhoAtual;
    }

    vDirecaoEPassos = (short)(vVizinhoAnterior - vCidadeAtual);

    if (vDirecaoEPassos > 0)
    {
        while (vDirecaoEPassos--)
            if (LIS_vaiParaNoAnterior(pListaDeCidades) != LIS_CondRetOK)
                return CID_CondRetProblemaDeLista;
    }

    else
    {
        while (vDirecaoEPassos++)
            if (LIS_vaiParaProximoNo(pListaDeCidades) != LIS_CondRetOK)
                return CID_CondRetProblemaDeLista;
    }

    if (CID_somaQuantidadeVizinhosPorConjunto(pListaDeCidades, vNumTotalDeCidades, vCidadeAtual, *pConjuntoVizinhosCamada, pSomaQuantidadesVizinhos, pConjuntoVizinhosCamada, --vCamadas) != CID_CondRetOK)
            return CID_CondRetProblemaDeLista;

    return CID_CondRetOK;

}
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       Lista está na posição da cidade atual.
*       A soma das quantidades dos vizinhos demarcados no conjunto foi
*       determinada.
*		Valem as assertivas estruturais da lista duplamente encadeada com
*       cabeça.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*       CID_CondRetProblemaDeLista
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Anda um certo número de passos para frente ou para trás numa
*       lista.
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais da lista duplamente encadeada.
*
*
*  $EP Parâmetros
*       $P pLista - O parâmetro que receberá o ponteiro para a cabeça da
*           lista duplamente encadeada.
*           Este parâmetro é passado por referência.
*       $P vPos - O parâmetro que receberá a posição desejada da lista.
*           Este parâmetro é passado por valor.
*
****************************************************************************/
CID_tpCondRet CID_vaiPara(CID_tppCabecaCidade pLista, unsigned char vPos)
{

    LIS_vaiParaPrimeiroNo(pLista);

    while (vPos)
    {
        LIS_vaiParaProximoNo(pLista);
        vPos--;
    }

    return CID_CondRetOK;
}
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       Lista está na posição desejada.
*		Valem as assertivas estruturais da lista duplamente encadeada com
*       cabeça.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Determina o comprimento de uma string.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais do vetor de caracteres.
*
*
*  $EP Parâmetros
*       $P string - O parâmetro que receberá o endereço do primeiro caractere
*           da string cujo tamanho deseja-se determinar.
*           Este parâmetro é passado por referência.
*
****************************************************************************/
unsigned char CID_stringComprimento(char pString[])
{

    unsigned char vSoma;
    int vCont;

    vSoma = (unsigned char)0;
    vCont = 0;

    do
        if (pString[vCont] != '\n')
            vSoma++;
    while (pString[vCont++]);

    return vSoma;
}
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       O comprimento da string foi determinado.
*		Valem as assertivas estruturais da lista duplamente encadeada com
*       cabeça.
*
*
*   $FV Valor retornado
*       vSoma - o comprimento da string.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Determina vBase ^ vPower.
*
*
*   $AE Assertivas de entrada esperadas:
*		vBase e vPower são valores inteiros.
*
*
*  $EP Parâmetros
*       $P vBase - O parâmetro que receberá o valor que deseja-se elevar.
*           Este parâmetro é passado por valor.
*       $P vPower - O parâmetro que receberá o valor ao qual deseja-se
*           elevar a base.
*           Este parâmetro é passado por valor.
*
****************************************************************************/
unsigned int CID_pow(unsigned int vBase, unsigned int vPower)
{

    unsigned int vRes;

    vRes = 1;

    while (--vPower)
        vRes *= vBase;

    return vRes;
}
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       vBase ^ vPower foi retornado. 
*
*
*   $FV Valor retornado
*       vBase = vBase ^ vPower
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Converte uma string numérica para o UInt equivalente.
*
*
*   $AE Assertivas de entrada esperadas:
*		Todos os caracteres da string são números.
*       O valor equivalente à string está no intervalo 0..4,294,967,295
*
*
*  $EP Parâmetros
*       $P pString - O parâmetro que receberá o endereço do primeiro
*           caractere da string a ser convertida. 
*           Este parâmetro é passado por referência.
*
****************************************************************************/
unsigned int CID_converteStringParaUInt(char *pString)
{

    unsigned int vConvertido, vTamString;

    vTamString = (unsigned int)CID_stringComprimento(pString);

    vTamString--;

    vConvertido = (unsigned int)0;

    for (int i = 0; pString[i]; i++)
        vConvertido += (unsigned int)(pString[i] - '0') * CID_pow((unsigned int)10, vTamString - (unsigned int)i);

    return vConvertido;
}
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       O valor numérico equivalente à string foi determinado.
*
*
*   $FV Valor retornado
*       vConvertido - O valor numérico equivalente à string.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Destrói conteúdo de cada cidade.
*
*
*   $AE Assertivas de entrada esperadas:
*		Conteúdo não é nulo.
*
*
*  $EP Parâmetros
*       $P pConteudoCidade - O parâmetro que receberá o endereço do conteúdo
*           de um nó da lista de cidades. 
*           Este parâmetro é passado por referência.
*
****************************************************************************/
CID_tpCondRet CID_destruirConteudoDeCidade(CID_tppConteudoCidade pConteudoCidade)
{
    free(pConteudoCidade->pStringNomeCidade);

    free(pConteudoCidade);

    return CID_CondRetOK;
}
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       O conteúdo da cidade foi destruído.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*
****************************************************************************/