#ifndef CIDADES_H
#define CIDADES_H
/****************************************************************************
*   $MCI Módulo de definição: Módulo CIDADES
*
*   Arquivo gerado:              CIDADES.H
*   Letras identificadoras:      CID
*
*   Projeto: Projeto Cidade
*   Autores: jpp - João Pedro Paiva
*
*   $HA Histórico de evolução:
*       Versão  Autor   Data        Observações
*       1.00    jpp     26/01/2020  Início do desenvolvimento
*       2.00    jpp     23/02/2020  Descriçõesdas funções de armazenamento de
*                                   conjuntos, armazenamento de quantidades,
*                                   ordenação, impressão e destruição.
*
*
*   $ED Descrição do módulo
*       Este módulo implementa um conjunto de funções para armazenar cidades
*       em listas duplamente encadeadas.
*
****************************************************************************/

/******************* Declarações exportadas pelo módulo ********************/

/* Tipo referência para uma lista de cidades */
typedef struct LIS_tagLista *CID_tppCabecaCidade;

/****************************************************************************
*
*  $TC Tipo de dados: CID Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de cidades
*
****************************************************************************/
typedef enum
{

    CID_CondRetOK, /* Concluiu corretamente */

    CID_CondRetFaltouMemoria, /* Faltou memória para allocar */

    CID_CondRetProblemaDeLista /* Função de LIS não retornou condição de
    teste bem sucedido quando deveria */

} CID_tpCondRet;

/****************************************************************************
*
*	$FC Função:
*       CID Armazenar várias ciades de um arquivo txt em uma lista.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*
*
*  $EP Parâmetros
*       $P ppListaDeCidades - O parâmetro que receberá o endereço do ponteiro
*           para a cabeça da lista de cidades.
*           Este parâmetro é passado por referência.
*       $P pStringArquivoDeCidades - O parâmetro que receberá o endereço do
*           primeiro caractere da string com o nome do arquivo de texto com
*           as cidades.
*           Este parâmetro é passado por referência.
*       $P pNumTotalDeCidades - O parâmetro que retornará o número total de
*           cidades do do txt.
*           Este parâmetro é passado por referência.
*
****************************************************************************/
CID_tpCondRet CID_criarListaDeCidades(CID_tppCabecaCidade *ppListaDeCidades, char *pStringArquivoDeCidades, unsigned char *pNumTotalDeCidades);
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       Os cidades que estavam no arquivo txt foram armazenados em uma lista.
*       Nó corrente da lista é o primeiro nó.
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*       CID_CondRetFaltouMemoria - Malloc falhou
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Armazena conjunto de vizinhos descritos no txt.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*       Nó corrente da lista pode ser o primeiro nó ou não.
*		Valem as assertivas estruturais do vetor de caracteres.
*
*
*  $EP Parâmetros
*       $P pListaDeCidades - O parâmetro que receberá o ponteiro para a
*           cabeça da lista de cidades.
*           Este parâmetro é passado por referência.
*       $P pStringArquivoDeVizinhos - O parâmetro que receberá o endereço do
*           primeiro caractere da string com o nome do arquivo de texto com
*           as cidades e seus vizinhos.
*           Este parâmetro é passado por referência.
*
****************************************************************************/
CID_tpCondRet CID_armazenarConjuntosVizinhos(CID_tppCabecaCidade pListaDeCidades, char *pStringArquivoDeVizinhos);
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       Os viznhos das cidades listadas no arquivo txt foram armazenados em
*       conjuntos nos nós de suas respectivas cidades.
*       Nó corrente da lista é o primeiro nó.
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*		Valem as assertivas estruturais do vetor de caracteres.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*       CID_CondRetFaltouMemoria - Malloc falhou.
*       CID_CondRetProblemaDeLista - Alguma função de lista não retornou
*           condição de teste bem sucedido.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Armazena a soma das quantidades dos vizinhos até a camada
*           desejada.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*       Nó corrente da lista pode ser o primeiro nó ou não.
*
*
*  $EP Parâmetros
*       $P pListaDeCidades - O parâmetro que receberá o ponteiro para a
*           cabeça da lista de cidades.
*           Este parâmetro é passado por referência.
*       $P vNumTotalDeCidades - O parâmetro que receberá o número total de
*           cidades na lista.
*           Este parâmetro é passado por valor.
*       $P vCamadas - O parâmetro que receberá o número de camadas de
*           vizinhos cuja soma deseja-se armazenar.
*           Este parâmetro é passado por valor.
*
****************************************************************************/
CID_tpCondRet CID_armazenarSomasVizinhos(CID_tppCabecaCidade pListaDeCidades, unsigned char vNumTotalDeCidades, unsigned char vCamadas);
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       As somas dos vizinhos até a camada desejada de cada cidade foram
*       armazenadas nos nós de cada cidade.
*       Nó corrente da lista é o primeiro nó.
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*       CID_CondRetProblemaDeLista - Alguma função de lista não retornou
*           condição de teste bem sucedido.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Ordena lista de cidades da maior soma das quantidades dos
*           vizinhos para a menor soma das quantidades dos vizinhos
*           utilizando o método bubble sort.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*       Nó corrente da lista pode ser o primeiro nó ou não.
*       Lista de cidades pode estar ordenada ou não.
*
*
*  $EP Parâmetros
*       $P pListaDeCidades - O parâmetro que receberá o ponteiro para a
*           cabeça da lista de cidades.
*           Este parâmetro é passado por referência.
*
****************************************************************************/
CID_tpCondRet CID_ordenarListaDeCidades(CID_tppCabecaCidade pListaDeCidades);
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       A lista de cidades foi ordenada decrescentemente pelas somas das
*       quantidades dos vizinhos.
*       Nó corrente da lista é o primeiro nó.
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*       CID_CondRetProblemaDeLista - Alguma função de lista não retornou
*           condição de teste bem sucedido.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Imprime lista de cidades.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*       Nó corrente da lista pode ser o primeiro nó ou não.
*       Lista de cidades pode estar ordenada ou não.
*
*
*  $EP Parâmetros
*       $P pListaDeCidades - O parâmetro que receberá o ponteiro para a
*           cabeça da lista de cidades.
*           Este parâmetro é passado por referência.
*
****************************************************************************/
CID_tpCondRet CID_imprimirListaDeCidades(CID_tppCabecaCidade pListaDeCidades);
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       A lista de cidades foi impressa.
*       Nó corrente da lista é o primeiro nó.
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*       CID_CondRetProblemaDeLista - Alguma função de lista não retornou
*           condição de teste bem sucedido.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Destrói lista de cidades.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*       Nó corrente da lista pode ser o primeiro nó ou não.
*       Lista de cidades pode estar ordenada ou não.
*
*
*  $EP Parâmetros
*       $P pListaDeCidades - O parâmetro que receberá o ponteiro para a
*           cabeça da lista de cidades.
*           Este parâmetro é passado por referência.
*
*
****************************************************************************/
CID_tpCondRet CID_destruirListaDeCidades(CID_tppCabecaCidade pListaDeCidades);
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       A lista de cidades foi destruída.
*       Conteúdo de cada nó, nós e cabeça foram liberados.
*		Valem as assertivas estruturais da lista de cidades duplamente
*       encadeada com cabeça.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*       CID_CondRetProblemaDeLista - Alguma função de lista não retornou
*           condição de teste bem sucedido.
*
****************************************************************************/

/****************************************************************************
*
*	$FC Função:
*       CID Copia pString1 para pString2.
*
*
*   $AE Assertivas de entrada esperadas:
*		Valem as assertivas estruturais do vetor de caracteres.
*
*
*  $EP Parâmetros
*       $P string1 - O parâmetro que receberá o endereço do primeiro caractere
*           da string receptora.
*           Este parâmetro é passado por valor.
*       $P string2 - O parâmetro que receberá o endereço do primeiro caractere
*           da string emissora.
*           Este parâmetro é passado por valor.
*
****************************************************************************/
CID_tpCondRet CID_stringCopia(char pString1[], char pString2[]);
/****************************************************************************
*
*	$AS Assertivas de saída esperadas:
*       string1 recebeu cada caractere da string2.
*		Valem as assertivas estruturais do vetor de caracteres.
*
*
*   $FV Valor retornado
*       CID_CondRetOK - Condição de retorno de teste bem sucedido.
*
****************************************************************************/

#endif /* CIDADES_H */