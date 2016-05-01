#include "Bspline.h"
#include <GL/glut.h>
#include <stdio.h>

void BSpline(float Points[4][2], int densidade){

    float x, y;
    float intervalo;
    float b[4] = {0,0,0,0};
    float matrizintervalos[4];
    float matriztransforma[4][4] = {{ -1,  3, -3, 1},
                                    {  3, -6,  3, 0},
                                    { -3,  0,  3, 0},
                                    {  1,  4,  1, 0}};

	glColor3f(1,1,0);
	glBegin(GL_LINE_STRIP);

	for(int i=0;i!=densidade;++i){
		intervalo = (float)i/(densidade-1);

		matrizintervalos[0] = intervalo*intervalo*intervalo;
		matrizintervalos[1] = intervalo*intervalo;
		matrizintervalos[2] = intervalo;
		matrizintervalos[3] = 1;

        for(int j = 0; j < 4; j++){
/*
            for(int k = 0; k < 4; k++ ){
                b[j] += matriztransforma[k][j]*matrizintervalos[k];
            }b[j] /=6;
/////////////////////////////////////////////////////////////////////////////////// esse for tem que substituir as linhas abaixo
*/

		b[0] = (-1*matrizintervalos[0] +3*matrizintervalos[1] - 3*matrizintervalos[2] + matrizintervalos[3])/6.0f;
		b[1] = (3*matrizintervalos[0] - 6*matrizintervalos[1] +4*matrizintervalos[3])/6.0f;
		b[2] = (-3*matrizintervalos[0] +3*matrizintervalos[1] + 3*matrizintervalos[2] + 1*matrizintervalos[3])/6.0f;
		b[3] =  matrizintervalos[0]/6.0f;

////////////////////////////////////////////////////////////////////////////////// essa parte deve ser tirada
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            x += b[j]*Points[j][0];
            y += b[j]*Points[j][1];
        }
        glVertex2f( x, y );
        x=0; y=0;
	}
	glEnd();
}
