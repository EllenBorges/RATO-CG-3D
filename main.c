/*------------------------DESCRICAO---------------------------------
Computacao Grafica
Nome: Ellen Priscila Borges Oliveira
RA: 69554

O programa desenha um ratinh tridimensional animado na tela,o qual persegue
pedaços de queijo que aparecem de acordo com o clique do mouse.
Quando o rato se aproxima do queijo, o queijo some da tela.

*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <GL/glut.h>

/*------------------------CONSTANTES-------------------------------*/
#define PI 3.141592654
#define DEFAULT_WINDOW_SIZE_W 800.0
#define DEFAULT_WINDOW_SIZE_H 600.0

/*------------------------VARIAVEIS--------------------------------*/


float x_novoQueijo, y_novoQueijo;

GLfloat angle = 45;
int flag1, flag2, gira, cor1, cor2, cor3;
int width, heigth;
float rX, rY, rZ, time;
float elbow1 = 0, elbow2 = 0;
GLfloat fAspect;
double tempo = 1.0;




/*------------------ESTRUTURA DA LISTA-----------------------------*/
typedef struct no_lista{
  float x, y;
  struct no_lista *prox;
}NO;

typedef struct Lista{
    NO* primeiro;
    NO* ultimo;
    int tamanho;
}LDE;

LDE *listaQueijo;
/*----------------- FUNCOES PARA A LISTA ENCADEADA-----------------*/


void InicializaLista(LDE *L){

  L->primeiro = NULL;
  L->ultimo = NULL;
  L->tamanho = 0;

}

/*insere um novo no no final da lista*/
void InsereNO(LDE *L, float x,float y){

    NO *novo = (NO*)malloc(sizeof(NO));
    novo->prox = NULL;
    novo->x = x;
    novo->y = y;


    if(L->primeiro==NULL && L->ultimo==NULL){
        L->primeiro = novo;
        L->ultimo = novo;
        L->tamanho++;
    }
    else{

        L->ultimo->prox = novo;
        L->ultimo = novo;
        L->ultimo->prox = NULL;
        L->tamanho++;
    }

}

void RemoveNO(){

    if(listaQueijo!=NULL){ /*se a lista nao esta vazia*/
	    NO* temp = listaQueijo->primeiro;
        free(listaQueijo->primeiro);
            /*remove começo*/
        listaQueijo->primeiro = temp->prox;
        listaQueijo->tamanho--;

         if (listaQueijo->primeiro == NULL)
            listaQueijo->ultimo = NULL;


    }


}



void lst_imprime (NO* lst){
    NO* p;

    for (p = lst; p != NULL; p = p->prox)
        printf("X_Queijo = [%.2f] \n Y_Queijo = [%.2f] \n", p->x, p->y);


}

void Imprime_ListaQueijo(){
    if(listaQueijo!=NULL && listaQueijo->tamanho>0)
        lst_imprime(listaQueijo->primeiro);
}








/*------------------------FUNÇÕES DE INICIALIZAÇÃO---------------------*/
void inicializa_Tela(char nome_janela[]){

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(DEFAULT_WINDOW_SIZE_W, DEFAULT_WINDOW_SIZE_H);

    glutCreateWindow(nome_janela);
   /* glClearColor(255,255,255,255);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);*/
    glFinish();

}

void inicializa_Variaveis(){
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  flag1 = 1;
  flag2 = 1;
  cor1 = 1;
  cor2 = 0;
  cor3 = 0;
  time = 1.0;
  rX = 0.0;
  rY = 0.0;
  rZ = 0.0;
  gira = 0;


}
void SetupRC(void) {
    GLfloat luzAmbiente[4]={0.5, 0.5, 0.5, 1.0};
    GLfloat luzDifusa[4]={0.7, 0.7, 0.7, 1.0};
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
    GLfloat posicaoLuz[4]={500.0, -50.0, 50.0, 0.0};
    GLfloat posicaoLuz2[4]={0.0, -5000.0, 0.0, 0.0};

    GLfloat light1_Direcao [4] = {0.0, 0.0, -1.0, 1.0};

    GLfloat objeto_ambiente[4] = {0.5, 0.0, 0.0, 1.0};
    GLfloat objeto_difusa[4] = {1.0, 0.0, 0.0, 1.0};

	/* Capacidade de brilho do material */
    GLfloat especularidade[4]={1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 20;


/* Especifica que a cor de fundo da janela será preta */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

/* Ativa o uso da luz ambiente */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

/* Define os parâmetros da luz de número 0 */
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

/*glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light1_Direcao);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 8.0);*/


/* define as propriedades do material */
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, objeto_ambiente);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, objeto_difusa);
/* Define a refletância do material */
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
/* Define a concentração do brilho */
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

/* Habilita a definição da cor do material a partir da cor corrente */
    glEnable(GL_COLOR_MATERIAL);
/* Habilita o uso de iluminação*/
    glEnable(GL_LIGHTING);
/* Habilita a luz de número 0 */
    glEnable(GL_LIGHT0);
/* Habilita o depth-buffering */
    glEnable(GL_DEPTH_TEST);
/*glShadeModel(GL_FLAT);*/

}
/* Função usada para especificar o volume de visualização */
void Viewing(void)	{
	/* Especifica sistema de coordenadas de projeção */
	glMatrixMode(GL_PROJECTION);
	/* Inicializa sistema de coordenadas de projeção */
	glLoadIdentity();

	/* Especifica a projeção perspectiva */
	gluPerspective(angle, fAspect, 0.1, 1000);

	/* Especifica sistema de coordenadas do modelo */
	glMatrixMode(GL_MODELVIEW);
	/* Inicializa sistema de coordenadas de projeção */
	glLoadIdentity();

	/* Especifica posição do observador e do alvo */
	gluLookAt(0, 20, 200, 0, 0, 0, 0, 1, 0);
}
/*------------------------FUNÇÕES ADICIONAIS ---------------------*/
void cor_Corrente(char nome_cor[]){

    if(strcmp (nome_cor, "branco") == 0)
        glColor3f(1,1,1);
    else if(strcmp (nome_cor, "preto") == 0)
        glColor3f(0,0,0);
    else if(strcmp (nome_cor, "vermelho") == 0)
        glColor3f(1,0,0);
    else if(strcmp (nome_cor, "azul") == 0)
        glColor3f(0,0,1);
    else if(strcmp (nome_cor, "verde") == 0)
        glColor3f(0,1,0);
    else if(strcmp (nome_cor, "amarelo") == 0)
        glColor3f(1,1,0);
    else if(strcmp (nome_cor, "magenta") == 0)
        glColor3f(1,0,1);
    else if(strcmp (nome_cor, "ciano") == 0)
        glColor3f(0,1,1);
    else if(strcmp (nome_cor, "cinza") == 0)
        glColor3f(0.86,0.86,0.86);
     else if(strcmp (nome_cor, "rosa claro") == 0)
        glColor3f(1,0.71,0.76);
    else if(strcmp (nome_cor, "salmao claro") == 0)
        glColor3f(1,0.63,0.48);
    else if(strcmp (nome_cor, "salmao") == 0)
        glColor3f(0.98,0.5,0.45);
    else if(strcmp (nome_cor, "cinza ardosia escuro") == 0)
        glColor3f(0.18,0.31,0.31);
    else if(strcmp (nome_cor, "ouro") == 0)
        glColor3f(1,0.84,0);

}


/*---------------------- FUNCOES DE TRANSFORMAÇÃO---------------------------*/

void translada_Rato(){
}

void rotaciona_Rato(){
}

void escala_Rato(){

}


/*---------------------- FUNCOES DE DESENHO---------------------------*/
void desenha_Queijo(){
/*-----------------------Desenha Queijo-----------------------*/



}

void desenha_perna(){

}

void desenha_Rato(){
    glPushMatrix();

    /*desenha corpo*/
    glPushMatrix();

			//cima

			glTranslatef(0,-14, -14);
			glRotatef(60, 1, 0, 0);
			glPushMatrix();
				glScalef(1.1, 1.3, 1.1);
				glColor3f(0.18,0.31,0.31);
				glutSolidSphere(13, 200.0, 200);
			glPopMatrix();

            //baixo

             glTranslatef(0,-20,-20);
			glPushMatrix();

				glScalef(1.7, 1.8, 1.8);
				glColor3f(0.18,0.31,0.31);
				glutSolidSphere(15, 200, 200);
			glPopMatrix();


		glPopMatrix();
    /*desenha cabeça*/

    // Cabeça
		glPushMatrix();
            //baixo

            glRotatef(-60, 1, 0, 0);
            glTranslatef(0.0, -3, -1);
			glPushMatrix();
                glScalef(1.2, 1.5, 1.2);
                glColor3f(0.18,0.31,0.31);
				glutSolidSphere(13, 200.0, 200);
			glPopMatrix();
			//cima

			glTranslatef(0.0, -8.0, 0.0);
			glRotatef(-15, 1, 0, 0);
			glPushMatrix();
				glScalef(1.0, 1.5, 1.0);
				glColor3f(0.18,0.31,0.31);
				glutSolidSphere(13, 200.0, 200);
			glPopMatrix();
		glPopMatrix();

    /*desenha orelha esquerda*/

    glPushMatrix();
        glPushMatrix();
            glRotatef(-45,0, 1 ,0);
            glTranslatef(-15, 8, 0);
            glScalef(2.5, 2.5 , 2.5);
            glColor3f(0.18,0.31,0.31);
            glutSolidTorus(2, 2, 50, 50);
        glPopMatrix();
        /*
         glPushMatrix();
            glRotatef(-45,0, 1 ,0);
            glTranslatef(-18, 8, 0);
            glScalef(2.5, 2.5 , 2.5);
            glColor3f(0.98,0.5,0.45);
            glutSolidSphere(2, 50, 50);
        glPopMatrix();*/

     glPopMatrix();



    /*desenha orelha direita*/
    glPushMatrix();
        glPushMatrix();
            glRotatef(45,0, 1 ,0);
            glTranslatef(15, 8, 0);
            glScalef(2.5, 2.5, 2.5);
            glColor3f(0.18,0.31,0.31);
            glutSolidTorus(2, 2, 50, 50);
        glPopMatrix();
     glPopMatrix();



    /*desenha nariz*/

    glPushMatrix();
        glPushMatrix();
            glTranslatef(0, -8, 30);
            glScalef(2, 2 , 2);
            glColor3f(0.0, 0.0, 0.0);
            glutSolidSphere(2.0, 100.0, 20);
        glPopMatrix();
     glPopMatrix();



    /*desenha olho direito*/
    glPushMatrix();
			glTranslatef(0.0, 0.5, 13.0);
			glPushMatrix();
				glTranslatef(-7.0, 3, 0);
				//glRotatef(45, 0, 0, 1);
				glPushMatrix();
					glScalef(0.9, 0.9, 1.0);
					glColor3f(0.0, 0.0, 0.0);
					glutSolidSphere(3.0, 100.0, 20);
				glPopMatrix();
				//iris
				glPushMatrix();
					//glTranslatef(-0.5, 0.0, 0.0);
					glScalef(0.2, 0.2, 0.2);
                    glColor3f(0.86,0.86,0.86);
					glutSolidSphere(3.0, 100.0, 20);
				glPopMatrix();
			glPopMatrix();

			/*desenha olho esquerdoa*/

			glPushMatrix();
				glTranslatef(7.0, 3, 0.0);
				//glRotatef(-45, 0, 0, 1);
				glPushMatrix();
					glScalef(0.9, 0.9, 1.0);
					glColor3f(0.0, 0.0, 0.0);
					glutSolidSphere(3.0, 100.0, 20);
				glPopMatrix();
				//iris
				glPushMatrix();
					//glTranslatef(0.5, 0.0, 0.0);
					glScalef(0.2, 0.2, 0.2);
					glColor3f(0.86,0.86,0.86);
					glutSolidSphere(3.0, 100.0, 20);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();




    /*desenha bigode*/

        /* bigode direito*/

     glPushMatrix();
            glTranslatef(5, -2, 20);
            glRotatef(90,0,1,0);
            glColor3f(0.0, 0.0, 0.0);
             glutSolidCone(0.5,25,100,100);
    glPopMatrix();

    glPushMatrix();
            glTranslatef(5, -4, 20);
            glRotatef(90,0,1,0);
            glColor3f(0.0, 0.0, 0.0);
             glutSolidCone(0.5,30,100,100);
    glPopMatrix();

     glPushMatrix();
            glTranslatef(5, -6, 20);
            glRotatef(90,0,1,0);
            glRotatef(-90,0,0,1);
            glColor3f(0.0, 0.0, 0.0);
             glutSolidCone(0.5,25,100,100);
    glPopMatrix();


        /* bigode esquerdo*/

     glPushMatrix();
            glTranslatef(-5, -2, 20);
            glRotatef(-90,0,1,0);
            glColor3f(0.0, 0.0, 0.0);
            glutSolidCone(0.5,25,100,100);
    glPopMatrix();

    glPushMatrix();
            glTranslatef(-5, -4, 20);
            glRotatef(-90,0,1,0);
           glColor3f(0.0, 0.0, 0.0);
            glutSolidCone(0.5,30,100,100);
    glPopMatrix();

     glPushMatrix();
            glTranslatef(-5, -6, 20);
            glRotatef(-90,0,1,0);
            glRotatef(90,0,0,1);
            glColor3f(0.0, 0.0, 0.0);
            glutSolidCone(0.5,25,100,100);
    glPopMatrix();

    /*desenha rabo */

    glPushMatrix();
            glTranslatef(0, -22, -40);
            glRotatef(180,0,1,0);
            glColor3f(0.18,0.31,0.31);
            glutSolidCone(2,80,100,100);

    glPopMatrix();

   /*desenha perna*/


    glPopMatrix();

}

void desenha(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	  glRotatef(rX, 1.0, 0.0, 0.0);
	  glRotatef(rY, 0.0, 1.0, 0.0);
	  glRotatef(rZ, 0.0, 0.0, 1.0);
	  	  desenha_Rato(elbow1);

	glPopMatrix();
	//chamar a desenha queijo
    glutSwapBuffers();


}

void timer(int i){
	glutPostRedisplay();
	glutTimerFunc(time, timer, 1);
}

/*------------------FUNÇÕES DE MOVIMENTACAO DO RATO----------------------*/



void controla_Rato(){
/*rotação*/
/*translação*/



}



/*---------------------- FUNCOES DE INTERACAO---------------------------*/

void SpecialKeys (int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:

            break;
        case GLUT_KEY_DOWN:

            break;

        case GLUT_KEY_LEFT :

            break ;
        case GLUT_KEY_RIGHT :

            break ;
        default :
            break ;
        }
        glutPostRedisplay() ;
}

void keyboard (unsigned char key, int x, int y){
    switch(key){
        case 'E':
            /*faz com que o rato aumente seu tamanho*/


            break;
        case 'e':
            /*faz com que o rato diminua seu tamanho*/

            break;
        case 'X':
            /*faz com que o rato rotacione no eixo x */
            rX -= 5; break;

            break;
	 case 'x':
            /*faz com que o rato rotacione no eixo x */
            rX += 5; break;
	    break;

        case 'Y':
            /*faz com que o rato rotacione no eixo y */
            rY -= 5; break;

            break;
	 case 'y':
            /*faz com que o rato rotacione no eixo y */
             rY += 5; break;
	    break;

        case 'Z':
            /*faz com que o rato rotacione no eixo z */
            rZ -= 5; break;
            break;
	 case 'z':
            /*faz com que o rato rotacione no eixo z */
            rZ += 5; break;
	    break;

        case 27:
            exit(0);
            break;
        default:
            break;

    }
    glutPostRedisplay();
}

void MouseInt (int botao, int estado, int x, int y){
    switch(botao){
    case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN){

//            x_novoQueijo = ((float)x/((float)largura_Janela/2.0))-1.0;

        //    y_novoQueijo = (float) 1 -(float) y/(altura_Janela/2.0);

            InsereNO(listaQueijo,x_novoQueijo,y_novoQueijo);
            controla_Rato();


        }
        break;
    }
    glutPostRedisplay();
}

void reshape (int w, int h)
{
    /* Para previnir uma divisão por zero */
	if(h == 0) h = 1;

	if(w <= h){
		heigth = 80.0 * h / w;
		width = 80.0;
	}
	if(h <= w){
		width = 80.0 * w / h;
		heigth = 80.0;
	}

	/* Especifica o tamanho da viewport */
	glViewport(0, 0, w, h);

	/* Calcula a correção de aspecto */
	fAspect = (GLfloat)w / (GLfloat)h;

	Viewing();

}

int main(int argc, char *argv[]){

    glutInit (&argc,argv);

    listaQueijo = (LDE*) malloc(sizeof(LDE));
    InicializaLista(listaQueijo);

    inicializa_Tela("RUN MOUSE");
    glutDisplayFunc(desenha);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMouseFunc(MouseInt);

//glutIdleFunc(controla_Rato);
	//glutTimerFunc(time, timer, 1);
    glutReshapeFunc(reshape);
    SetupRC();

    glutMainLoop();
    free(listaQueijo);


return 0;
}

