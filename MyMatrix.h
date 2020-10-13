/*
* Autor: Erick Lima Figueiredo
* MA: ES98898 Data: 09/10/2020
* UNIVERSIDADE FEDERAL DE VIÇOSA
* DISC: Estrutura de Dados
* Professor: Salles Vianna

==== TRABALHO 1 ====
*/

//Interface da Classe

#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <iostream>

template <class T>
class MyMatrix{
    public:
        //Construtor
        MyMatrix(int, int*, bool);
        MyMatrix(const MyMatrix<T>&);

        //Destrutor
        ~MyMatrix();

        //Setters
        void set(int, int, const T&);

        //Getters
        const T& get(int, int) const;
        int getNumRows() const {return rows;};
        int getNumCols(int) const;
        int getNumElems() const {return size;};
        
        //Flag
        bool isRagged() const {return (matriz == NULL && tam == NULL) && (start != NULL && ragged != NULL);};

        //Resize
        void resizeRow(int, int);
        void resizeNumRows(int);

        //Conversão
        void convertToRagged();
        void convertToTraditional();

        //Impressão
        void print() const;

        //Operador
        MyMatrix<T>& operator=(const MyMatrix&);

    protected:
        int rows = 0, size = 0;
        int *tam = NULL, *start = NULL;
        T *ragged = NULL;
        T **matriz = NULL;
    
    private:
        void create (int, int *, bool, bool);
        void destroy();
};

//Implementação da Classe

template <class T>
MyMatrix<T>::MyMatrix(int rows, int *array, bool isRagged){
    create(rows, array, isRagged, false);
}

template <class T>
MyMatrix<T>::MyMatrix(const MyMatrix<T> &other){
    //Chamaremos a sobrecarga do operador de atribuição
    *this = other;
}

template <class T>
MyMatrix<T>::~MyMatrix(){
    destroy();
}

template <class T>
void MyMatrix<T>::set(int row, int col, const T &val){
    if(isRagged())
        /*Como estão todos em "linha" no mesmo array, pegamos a posição inicial correspondente 
        a linha e somamos a ela o indice da coluna para obter o valor desejado*/
        ragged[start[row]+col] = val;
    else
        matriz[row][col] = val;
}

template <class T>
const T& MyMatrix<T>::get(int row, int col) const{
    if(isRagged())
        return ragged[start[row]+col];
    else
        return matriz[row][col];
}

template <class T>
int MyMatrix<T>::getNumCols(int i) const{
    if(!rows)
        return 0;
    if(isRagged())
        /*No vetor Start, do modo ragged, guardamos a posição inicial de cada linha, então basta a 
        diferença entre o próx. índice, pelo índice que estamos*/
        return start[i+1] - start[i];
    else
        return tam[i];
}

template <class T>
void MyMatrix<T>::resizeRow(int row, int newCols){
    //Verificamos se houve alguma alteração, caso a diferença dê ZERO apenas retornamos
    if(getNumCols(row) == newCols)
        return;

    if(isRagged()){

        int diferenca = newCols - getNumCols(row);

        //Fazemos a cópia do ragged para realizarmos a realocação, visto que não dispomos do realloc
        T *oldRagged = new T[size];

        for(int i = 0; i < size; i++)
            oldRagged[i] = ragged[i];
        
        //Pegamos a diferença para saber em quanto o vetor ragged vai aumentar ou diminuir
        
        delete []ragged;

        size += diferenca;
         //Alocamos o novo tamanho considerando o redimensionamento das colunas do row
        ragged = new T[size];

        //Vamos preencher o ragged até a parte realocada
        for(int i = 0; i < size; i++){
            if(i >= start[row+1] && i < start[row+1]+diferenca){
                //As colunas acrescidas vão receber o valor parão do tipo que pertencem
                ragged[i] = T();
            }else if(i >= start[row+1]+diferenca){
                //Continuamos a cópia apos adicionarmos ou retirarmos as colunas do row
                ragged[i] = oldRagged[i - diferenca];
            }else{
                //Iniciamos a cópia até encontrarmos a posição onde houve alteração
                ragged[i] = oldRagged[i];
            }
        }

        delete []oldRagged;

        /*Adequamos o mapeamento dos rows da matriz no Start somando a diferença em cada posição 
        acima do row modificado*/
        for(int i = row+1; i < rows+1; i++)
            start[i] += diferenca;

    }else{
        size += newCols - getNumCols(row);
        
        T *oldRow = new T[tam[row]];
        for(int i = 0; i < tam[row]; i++) oldRow[i] = matriz[row][i];

        delete []matriz[row];
        matriz[row] = new T[newCols];

        for(int i = 0; i < newCols; i++){
            if(i >= tam[row])
                matriz[row][i] = T();
            else
                matriz[row][i] = oldRow[i];
        }
        
        delete []oldRow;

        tam[row] = newCols;
    }
}

template <class T>
void MyMatrix<T>::resizeNumRows(int newRows){
    if(rows == newRows)
        return;

    if(isRagged()){
        //Como não dispomos dos recursos de realloc, vamos fazer uma cópia de start e ragged
        int *oldStart = new int[rows+1];

        for(int i = 0; i < rows+1; i++)
            oldStart[i] = start[i];

        delete []start;
        start = new int[newRows+1];

        /*Zeramos a posição que receberá o size para que o incremento não seja feito com lixo 
        de memória*/
        start[newRows] = 0;

        //Vai garantir colocar as posições vazias
        int ult = 0;

        for(int i = 0; i < newRows; i++){
            if(i >= rows){
                /*Caso estejamos aumentando o row, repetimos o valor a frente da ultima posição da 
                linha, para indicar que está vazia*/
                start[i] = ult;
            }else{
                start[i] = oldStart[i];
                start[newRows] += oldStart[i+1] - oldStart[i];          
                ult = oldStart[i+1];      
            }
        }

        delete []oldStart;

        T *oldRagged = new T[size];

        for(int i = 0; i < size; i++)
            oldRagged[i] = ragged[i];

        delete []ragged;
        ragged = new T[start[newRows]];
        
        if(size >= start[newRows])
            for(int i = 0; i < start[newRows]; i++)
                ragged[i] = oldRagged[i];
        else
            for(int i = 0; i < size; i++)
                ragged[i] = oldRagged[i];

        delete []oldRagged;

        rows = newRows;
        size = start[rows];
    }else{
        //Como não dispomos dos recursos de realloc, vamos fazer uma cópia de tam e oldMatriz
        T **oldMatriz = new T*[rows];

        for(int i = 0; i< rows; i++){
            oldMatriz[i] = new T[tam[i]];
            
            for(int j = 0; j < getNumCols(i); j++)
                oldMatriz[i][j] = matriz[i][j];
            
            delete []matriz[i];
        }

        delete []matriz;
        
        int *oldTam = new int[rows];

        for(int i = 0; i < rows; i++)
            oldTam[i] = tam[i];

        delete []tam;
        tam = new int[newRows];

        for(int i = 0; i < newRows; i++){
            if(i < rows)
                tam[i] = oldTam[i];
            else
                tam[i] = 0;
        }

        delete []oldTam;

        matriz = new T*[newRows];

        for(int i = 0; i < newRows; i++)
            matriz[i] = new T[tam[i]];

        //Como não sabemos se a matriz vai aumentar o diminuir
        size = 0;

        //Feitos os redimensionamentos, copiamos os dados de volta para a matriz
        for(int i = 0; i < newRows; i++){
            if(i >= rows)
                break;

            for(int j = 0; j < getNumCols(i); j++){
                matriz[i][j] = oldMatriz[i][j];
                size++;
            }
        }

         //Deletamos a matriz de cópia
        for(int i = 0; i < rows; i++)
            delete []oldMatriz[i];
        
        delete []oldMatriz;

        rows = newRows;
    }
}

template <class T>
void MyMatrix<T>::convertToRagged(){
    // Só vamos fazer a operação se o formato for o tradicional
    if(!isRagged()){
        ragged = new T[size];
        int cursor = 0;

        //Passamos os dados do formato tradicional para o ragged
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < getNumCols(i); j++)
                ragged[cursor++] = matriz[i][j];
            
            delete []matriz[i];
        }

        delete []matriz;
        matriz = NULL;

        start = new int[rows+1];

        //Vamos gravar em start as posições que não são dependentes de tam, a primeira e a última
        start[0] = 0;
        start[rows] = size;

        for(int i = 1; i < rows; i++)
            start[i] = start[i-1]+tam[i-1];

        delete[]tam;
        tam = NULL;
    }
}

template <class T>
void MyMatrix<T>::convertToTraditional(){
    // Só vamos fazer a operação se o formato for o Ragged
    if(isRagged()){
        tam = new int[rows];

        //Vamos converter o array start para tam
        for(int i = 0; i < rows; i++)
            tam[i] = start[i+1] - start[i];

        delete []start;
        start = NULL;

        matriz = new T*[rows];

        for(int i = 0; i < rows; i++)
            matriz[i] = new T[tam[i]];
        
        /*Utilizaremos um cursor para andar na matriz ragged, enquanto percorremos as linhas 
        e as colunas da matriz*/
        int cursor = 0;

        for(int i = 0; i < rows; i++)
            for(int j = 0; j < getNumCols(i); j++)
                matriz[i][j] = ragged[cursor++];

        delete []ragged;
        ragged = NULL;
    }
}

template <class T>
void MyMatrix<T>::print() const{
    std::cout << "Rows: " << rows << "\nElems: " << size << "\n";
    if(isRagged()){

        for(int i = 0; i < rows; i++){
            //Verificamos se a linha tem alguma coluna
            if(start[i+1] - start[i] == 0)
                std::cout << start[i+1] - start[i] << ":\n";
            else
                //Se tiver, fazemos a subtração do proximo index pelo que estamos para obter o número de colunas
                std::cout << start[i+1] - start[i] << ":";
                for(int j = start[i]; j < start[i+1]; j++){
                    if(j == start[i+1]-1)
                        std::cout << " " << ragged[j] << "\n";
                    else
                        std::cout << " " << ragged[j];
                }
        }
    
    }else{
        for(int i = 0; i < rows; i++){
            std::cout << tam[i] << ":";
            if(!tam[i])
                std::cout << "\n";
            for(int j = 0; j < tam[i]; j++){
                if(j == tam[i]-1)
                    std::cout << " " << matriz[i][j] << "\n";
                else
                    std::cout << " " << matriz[i][j];
            }
        }
    }
}

template <class T>
MyMatrix<T>& MyMatrix<T>::operator=(const MyMatrix<T> &other){
    //Comparamos o endereço para verificarmos se são o mesmo objeto
    if(this == &other)
        return *this;

    //Destruimos o objeto, para que não haja vazamentos de memória
    destroy();

    //Alocamos a memoria necessária de acordo com as especificidades de cada um
    if(other.isRagged()){
        /*O último parametro da função create recebe true se a construção será uma cópia de
        ragged, assim não precisaremos remodelar o array recebido*/
        create(other.getNumRows(), other.start, true, true);

        for(int i = 0; i < other.getNumElems(); i++)
            this->ragged[i] = other.ragged[i];
    }else{
        create(other.rows, other.tam, false, false);

        for(int i = 0; i < other.getNumRows(); i++)
            for(int j = 0; j < other.getNumCols(i); j++)
                this->matriz[i][j] = other.matriz[i][j];
    }

    return *this;
}

template <class T>
void MyMatrix<T>::create (int rows, int *array, bool isRagged, bool isRaggedCopy){
    this->rows = rows;
    if(isRagged){

        //Colocamos +1 porque a ultima posição guarda o size (ou o limite de ragged)
        start = new int[rows+1];
        
        if(!isRaggedCopy)
            for(int i = 0; i < rows; i++)    
                size += array[i];
        else
            size = array[rows];

        ragged = new T[size];

        /*Se não for uma cópia de ragged e precisamos construir um objeto no formato ragged,
        "remodelamos" o array recebido  dentro de start*/
        if(!isRaggedCopy){
            int cursor = 0;

            for(int i = 0; i < rows; i++){
                if(array[i] != 0){
                    start[i] = cursor;
                    cursor += array[i];
                }else{
                    //Se o tamanho da linha for 0, não movemos o cursor
                    start[i] = cursor;
                }
            }

            start[rows] = size;
        }else
        {
            //Se for uma cópia não precisamos fazer a conversão de array, basta copiá-lo
            for(int i = 0; i < rows+1; i++)
                start[i] = array[i];
        }

        //A última linha do start vai receber o size, para sabermos a primeira posição fora da alocação
    }else{
        matriz = new T*[rows];
        tam = new int[rows];

        for(int i = 0; i < rows; i++){
            size += tam[i] = array[i];
            matriz[i] = new T[tam[i]];
        }
    }
}

template <class T>
void MyMatrix<T>::destroy(){
    if(isRagged()){
        delete []start;
        delete []ragged;

        /*Atribuimos NULL novamente aos ponteiros para que não apontem para nenhuma posição usada por 
        outro programa e para que não comprometa nossa função membro isRagged()*/
        start = NULL;
        ragged = NULL;
    }else{
        delete []tam;

        for(int i = 0; i < rows; i++)
            delete []matriz[i];

        delete []matriz;

        tam = NULL;
        matriz = NULL;
    }

    size = rows = 0;
}

#endif //FIM MY_MATRIX_H