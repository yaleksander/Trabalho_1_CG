#include "EditaVetor.h"
#include <stdio.h>

int ProcuraElemento(float vetorpontos[][2], int quantidadepontos, int x, int y, float tolerancia){
    for(int i = 0; i < quantidadepontos; i++){
        if(/*(vetorpontos[i][0]-tolerancia)<=x &&
           x<=(vetorpontos[i][0]+tolerancia) &&
           (vetorpontos[i][1]-tolerancia)<=y &&
           y<=(vetorpontos[i][1]+tolerancia)*/
           x==(int)vetorpontos[i][0] && y==(int)vetorpontos[i][1]
            //concertar erro de distancia do ponto aqui, não funciona se aumentar a tela e as vezes falha
        ){

            return i;
        }
    }
    return -1;
}

int ApagaElemento(float vetorpontos[][2], int quantidadepontos, int posicaoponto){
    for(int k = posicaoponto; k < quantidadepontos-1; k++){
        vetorpontos[k][0]=vetorpontos[k+1][0];
        vetorpontos[k][1]=vetorpontos[k+1][1];
    }
    return quantidadepontos-1;
}
