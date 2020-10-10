#include <iostream>
#include "MyMatrix.h"
using namespace std;


int main() {
	int tams[] = {1,3,0,2};

	//Cria uma matriz de inteiros com numero de colunas em cada linha: 1,3,0,2
	//O primeiro argumento do construtor é o número de linhas da matriz
	//O segundo argumento é um apontador para um array (com tamanho igual ao número de linhas) indicando o número de colunas em cada linha
	//O terceiro argumento deve ser true se a matriz for criada no modo ragged ou false se for criada no modo tradicional
	MyMatrix<int> m(4, tams, false);	

	//Inicializa a matriz com os elementos: [ [1], [2,3,4], [], [5,6] ]
	//getNumRows retorna o número de linhas da matriz (4 nesse caso)
	//getNumCols retorna quantas colunas tem na linha passada como argumento
	//a função "set" armazena, na linha passada como primeiro argumento e coluna passada como segundo, o terceiro argumento da função
	//Neste trabalho, funcoes do tipo "get" e "set" devem ter complexidade maxima O(1). Alem disso, elas nao devem fazer tratamento de erros (ou seja, voce pode supor que o usuario ira sempre se referir a uma posicao valida)
	for(int i=0,ct=1;i<m.getNumRows();i++) {
		for(int j=0;j<m.getNumCols(i);j++,ct++) {
			m.set(i,j,ct); 
		}
	}
	//cout << m.get(1,2) << "\n"; //retorna o elemento da linha 1, coluna 2 da matriz (deve ser o numero 4 nesse exemplo...)
	cout << m.getNumElems() << "\n"; //retorna quantos elementos (mesmo se nao inicializados) há na matriz... nesse caso, há 6. Deve ter complexidade máxima O(1)

	//imprime "Rows: rows", onde rows é o numero de linhas da matriz. 
	//Na proxima linha, imprime "Elems: elems", onde elems é o número total de elementos na matriz.
	//A seguir, imprime o conteúdo de cada linha (separado por um espaco em branco os elementos e criando uma nova linha para cada linha). 
	//Antes de cada linha essa funcao tambem deve imprimir o numero de elementos nela, seguido por um ":"
	//Para o exemplo acima, a saída seria: 
	/*
	Rows: 4
	Elems: 6
	1: 1
	3: 2 3 4
	0:
	2: 5 6
	*/
	cout << "Imprimindo a matriz original..." << "\n";
	m.print();
    cout << "É ragged? " << m.isRagged() << endl;

    cout << "Passando para ragged" << "\n";
    m.convertToRagged();
	m.print();
    cout << "É ragged? " << m.isRagged() << endl;

    cout << "voltando para tradicional" << "\n";
    m.convertToTraditional();
	m.print();
    cout << "É ragged? " << m.isRagged() << endl;

}