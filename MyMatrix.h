/*

Autor: Erick Lima Figueiredo
MA: ES98898 Data: 09/10/2020

DISC: Estrutura de Dados
Professor: Salles Vianna

====Trabalho1====

*/

#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <iostream>

template <class T>
class MyMatrix{
    public:
        //Construtor
        MyMatrix(int, int *, bool);

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
        bool isRagged() const {return matriz == NULL && tam == NULL;};

        //Resize
        void resizeRow(int, int);
        void resizeNumRows(int);

        //Conversão
        void convertToRagged();
        void convertToTraditional();

        void print() const;

    protected:
        int rows = 0, size = 0;
        int *tam = NULL, *start = NULL, *ragged = NULL;
        T **matriz = NULL; 
};

template <class T>
MyMatrix<T>::MyMatrix(int rows, int *array, bool isRagged){
    this->rows = rows;
    if(isRagged){

        //Colocamos +1 porque a ultima posição guarda o size (ou o limite de ragged)
        start = new int[rows+1];

        for(int i = 0; i < rows; i++)    
            size += array[i];

        ragged = new T[size];
        int cursor = 0;

        for(int i = 0; i < rows; i++){
            if(array[i] != 0){
                start[i] = cursor;
                cursor += tam[i];
            }else{
                //Se o tamanho da linha for 0, não movemos o cursor
                start[i] = cursor;
            }
        }

        //A última linha do start vai receber o size, para sabermos a primeira posição fora da alocação
        start[rows] = size;
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
MyMatrix<T>::~MyMatrix(){
    if(isRagged()){
        delete []start;
        delete []ragged;
    }else{
        delete []tam;

        for(int i = 0; i < rows; i++)
            delete matriz[i];

        delete []matriz;
    }

    size = rows = 0;
}

template <class T>
void MyMatrix<T>::set(int row, int col, const T &val){
    if(isRagged()){
        ragged[start[row]+col] = val;
    }else{
        matriz[row][col] = val;
    }
}

template <class T>
const T& MyMatrix<T>::get(int row, int col) const{
    if(isRagged()){
        return ragged[start[row]+col];
    }else{
        return matriz[row][col];
    }
}

template <class T>
int MyMatrix<T>::getNumCols(int i) const{
    if(isRagged()){
        return start[i+1] - start[i];
    }else{
        return tam[i];
    }
}

template <class T>
void MyMatrix<T>::resizeRow(int row, int newCols){
    
    if(isRagged()){
        //Fazemos a cópia do ragged para realizarmos a realocação, visto que não dispomos do realloc
        T *oldRagged = new T[size];

        for(int i = 0; i < size; i++)
            oldRagged[i] = ragged[i];
        
        int diferenca = newCols - getNumCols(row);
        
        delete[] ragged;
        size += diferenca;
         //Alocamos o novo tamanho considerando o redimensionamento das colunas do row
        ragged = new T[size];

        //Vamos preencher o ragged até a parte realocada
        for(int i = 0; i < size; i++){
            if(i >= start[row+1] && i < start[row+1]+diferenca){
                ragged[i] = T();
            }else if(i >= start[row+1]+diferenca){
                ragged[i] = oldRagged[i - diferenca];
            }else{
                ragged[i] = oldRagged[i];
            }
        }

        delete []oldRagged;

        //Adequamos o mateamento dos rows da matriz no Start somando a diferença em cada posição acima do row modificado
        for(int i = row; i < rows+1; i++)
            start[i] += diferenca;

    }else{
        size += newCols - getNumCols(row);
        
        int *oldRow = new T[tam[row]];
        for(int i = 0; i < tam[row]; i++) oldRow[i] = matriz[row][i];

        delete matriz[row];
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
    if(isRagged()){

    }else{

    }
}

template <class T>
void MyMatrix<T>::convertToRagged(){
    if(!isRagged()){

    }
}

template <class T>
void MyMatrix<T>::convertToTraditional(){
    if(isRagged()){

    }
}

template <class T>
void MyMatrix<T>::print() const{
    std::cout << "Rows: " << rows << "\nElems: " << size << "\n";
    if(isRagged()){
        int cursor = 0;
        for(int i = 0; i < rows; i++){
            std::cout << start[i+1] - start[i] << ": ";
            for(int j = start[i]; j < start[i+1]; j++){
                if(j == start[i+1]-1){
                    std::cout << ragged[j] << "\n";
                }else{
                    std::cout << ragged[j] << " ";
                }
            }
        }
    
    }else{
        for(int i = 0; i < rows; i++){
            std::cout << tam[i] << ": ";
            if(!tam[i])
                std::cout << "\n";
            for(int j = 0; j < tam[i]; j++){
                if(j == tam[i]-1)
                    std::cout << matriz[i][j] << "\n";
                else
                    std::cout << matriz[i][j] << " ";
            }
        }
    }
}

#endif //MY_MATRIX_H