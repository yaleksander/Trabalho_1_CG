#include "Bspline.h"
#include <GL/glut.h>

void BSpline(float Points[4][2], int densidade){

    float ponto[2];
    float intervalo;
    float matrizintervalos[4];
    float matriztransforma[4][4] = {{ -1,  3, -3, 1},
                                    {  3, -6,  3, 0},
                                    { -3,  0,  3, 0},
                                    {  1,  4,  1, 0}};

	glBegin(GL_LINE_STRIP);

        for( int i = 0; i <= densidade; i++ ){

            // Cria os intervalos variando de 0 a 1
            intervalo = (float)i / densidade;

            // Monta a Matriz com os intervalos
            matrizintervalos[0] = intervalo*intervalo*intervalo;
            matrizintervalos[1] = intervalo*intervalo;
            matrizintervalos[2] = intervalo;
            matrizintervalos[3] = 1;

            // Equação para calculo da posição do ponto para um intervalo t
            // S(t) = T * 1/6 * M * P
            for(int j = 0; j < 4; j++){
                for(int k = 0; k < 4; k++ ){
                    ponto[0] += matrizintervalos[k] * (1.0/6) * matriztransforma[k][j] * Points[j][0];
                    ponto[1] += matrizintervalos[k] * (1.0/6) * matriztransforma[k][j] * Points[j][1];
                }
            }

            // Cria ponto do intervalo t
            glVertex2f( ponto[0], ponto[1] );

            // Zera os pontos para o proximo calculo
            for(int j = 0; j < 2; j++){
                ponto[j] = 0;
            }
        }

    glEnd();
}
