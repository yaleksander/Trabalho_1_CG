#include <GL/glut.h>
#include <stdio.h>
#include "EditaVetor.h"
#include "DesenhaCurva.h"

int alturajanela = 600, largurajanela = 600;
int quantidadepontos = 0;
float vetorpontos[100][2];
bool verpoligono = false, verpontos = true;
int posicaoelemento = -1;
int densidade = 200;

void display(void);
void init(void);
void mouse(int button, int state, int x, int y);
void keyboardPress(unsigned char key, int x, int y);
void motion(int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(alturajanela, largurajanela);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Curvas interativas");
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardPress);
	glutDisplayFunc(display);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	desenhacurva(vetorpontos, quantidadepontos, densidade);
	if (verpoligono)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
			for (int i = 0; i < quantidadepontos; i++)
				glVertex3f(vetorpontos[i][0], vetorpontos[i][1], 0.0);
		glEnd();
	}
	if (verpontos)
	{
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(10);
		glBegin(GL_POINTS);
			for (int i = 0; i < quantidadepontos; i++)
				glVertex3f(vetorpontos[i][0], vetorpontos[i][1], 0.0);
		glEnd();
		glColor3ub(0, 255, 255);
		for (int k = 0; k < quantidadepontos; k++)
		{
			glRasterPos2f(vetorpontos[k][0] + 0.1, vetorpontos[k][1] + 0.1);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
			if (k > 9)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (char) (48 + ((int) (k / 10))));
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (char) (48 + ((int) (k % 10))));
		}
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	y = alturajanela - y;
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			posicaoelemento = ProcuraElemento(vetorpontos, quantidadepontos, x * (10.0 / largurajanela), y * (10.0 / alturajanela), 0.9);
			if (quantidadepontos < 100 && posicaoelemento == -1)
			{
				vetorpontos[quantidadepontos][0] = x * (10.0 / largurajanela);
				vetorpontos[quantidadepontos][1] = y * (10.0 / alturajanela);
				quantidadepontos++;
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && quantidadepontos != 0)
	{
		posicaoelemento = ProcuraElemento(vetorpontos, quantidadepontos, x * (10.0 / largurajanela), y * (10.0 / alturajanela), 0.9);
		if (posicaoelemento >= 0)
		{
			quantidadepontos = ApagaElemento(vetorpontos, quantidadepontos, posicaoelemento);
			posicaoelemento = -1;
		}
	}
}

void keyboardPress(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case 'p':
			verpoligono = !verpoligono;
			break;
		case 'b':
			verpontos = !verpontos;
	}
}

void motion(int x, int y)
{
	if (x > 0 && x < largurajanela && y > 0 && y < alturajanela && posicaoelemento >= 0)
	{
		y = alturajanela - y;
		vetorpontos[posicaoelemento][0] = x * (10.0 / largurajanela);
		vetorpontos[posicaoelemento][1] = y * (10.0 / alturajanela);
	}
}
