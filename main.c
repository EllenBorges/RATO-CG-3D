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

/*------------------------VARIAVEIS--------------------------------*/

GLfloat altura_Janela, largura_Janela ;
GLfloat x_Janela=100, y_Janela=100;





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

    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(500,500);
    largura_Janela = 500;
    altura_Janela = 500;
    glutInitWindowPosition(x_Janela,y_Janela);
    glutCreateWindow(nome_janela);
    glClearColor(255,255,255,255);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glFinish();

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


/*----------------------Variaveis locais-----------------------*/
  
/*------------------------Desenha Rato------------------------*/

    
    /*desenha corpo*/

    



    /*desenha cabeça*/
    

    /*desenha orelha esquerda*/
   

   

    /*desenha orelha direita*/
    
   
    /*desenha nariz*/
   
    /*desenha olho direito*/
    

    /*desenha olho esquerdoa*/
  

    /*desenha bigode*/
    
        /* bigode esquerdo*/
       


    /*desenha rabo */

   /*desenha perna*/
    



}

void desenha(){
    glClearColor(255,255,255,255);
    glClear(GL_COLOR_BUFFER_BIT);

    desenha_Queijo();
    desenha_Rato();

    glFlush();

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
            
            break;
	 case 'x':
            /*faz com que o rato rotacione no eixo x */
	    break;

        case 'Y':
            /*faz com que o rato rotacione no eixo y */
            
            break;
	 case 'y':
            /*faz com que o rato rotacione no eixo y */
	    break;

        case 'Z':
            /*faz com que o rato rotacione no eixo z */
            
            break;
	 case 'z':
            /*faz com que o rato rotacione no eixo z */
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
            cont++;
            x_novoQueijo = ((float)x/((float)largura_Janela/2.0))-1.0;

            y_novoQueijo = (float) 1 -(float) y/(altura_Janela/2.0);

            InsereNO(listaQueijo,x_novoQueijo,y_novoQueijo);
            controla_Rato();
            

        }
        break;
    }
    glutPostRedisplay();
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

    glutMainLoop();
    free(listaQueijo);

return 0;
}
