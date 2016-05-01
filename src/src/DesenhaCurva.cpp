#include "DesenhaCurva.h"
#include "Bspline.h"

void desenhacurva(float Points[][2],int quantidadepontos, int densidade){
    float vet[4][2];
    if(quantidadepontos > 3){
        for(int k = 0; k < quantidadepontos -3; k++){
            for(int j = 0; j < 4; j++){
                vet[j][0] = Points[k+j][0];
                vet[j][1] = Points[k+j][1];
            }
            BSpline(vet, densidade);
        }
    }
}
