# CidadesGrafo
O programa aborda o problema de facility location.
A aplicação determina qual nó de um grafo acumula o maior peso quando somamos ao peso deste nó os pesos de nós de camadas de nós vizinhos.
Para executar o programa basta compilar:
$gcc -Wall -o PRINCIPAL LISTA.C CIDADES.C PRINCIPAL.C
e executar:
$./PRINCIPAL
Pode-se modificar os nomes e pesos dos nós no arquivo MunicipiosQtdCasos.txt.
Os vizinhos de cada nó podem ser modificados no arquivo MunicipiosVizinhos.txt. A enumeração dos nós deve ser como está (começando em zero e incrementando por um). A enumeração no arquivo MunicipiosVizinhos.txt corresponde com os nomes listados no arquivo MunicipiosQtdCasos.txt, por exemplo o Rio de Janeiro descrito em MunicipiosQtdCasos.txt é o nó zero em MunicipiosVizinhos.txt e Tangua descrito em MunicipiosQtdCasos.txt é o nó 39 de MunicipiosVizinhos.txt.
