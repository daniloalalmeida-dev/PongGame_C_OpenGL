// Anima.c - Utilizado como base para o programa completo abaixo.
// Jogo Semelhante ao videojogo Pong, criado em 1972.
// Para melhor compreensão do programa, veja o arquivo READ ME.

#include <windows.h>
#include <gl/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define QUADRADO 1
#define TRIANGULO 2
#define RETANGULO 3

//variáveis globais
GLint primitiva = 1;
GLfloat r, g, b;

//atualização de frames
int interval = 1000 / 60;

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

//variável para ter a pontuação na tela
int score_left = 0;
int score_right = 0;

// Tamanho e posição inicial do quadrado
GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei rsize = 15;

// Tamanho do incremento nas direções x e y
// (número de pixels para se mover a cada intervalo de tempo)
GLfloat xstep = 3.0f;
GLfloat ystep = 3.0f;

//variáveis do placar
static char score_1[10], score_2[10];
static GLint player1_score = 0, player2_score = 0;

// tamanho e dados gerais da raquete
int racket_width = 10;
int racket_height = 80;
int racket_speed = 8;

// posição inicial da raquete esquerda
float racket_left_x = 2.0f;
float racket_left_y = 100.0f;

// posição inicial da raquete direita
float racket_right_x = racket_left_x;
float racket_right_y = racket_left_y;

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
        //Iluminação 1
        GLfloat luzAmbiente[4]={0.8,0.8,0.8,1.0};
        GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor"
        GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
        GLfloat posicaoLuz1[4]={100.0, 150.0, 100.0, 1.0};

        // Capacidade de brilho do material
        GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
        GLint especMaterial = 60;

        // Define a refletância do material
        glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

        // Define a concentração do brilho
        glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

        // Ativa o uso da luz ambiente
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

        // Define os parâmetros da luz de número 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz1 );

        //Iluminação 2
        GLfloat luzAmbiente1[4]={0.8,0.8,0.8,1.0};
        GLfloat luzDifusa1[4]={0.7,0.7,0.7,1.0}; // "cor"
        GLfloat luzEspecular1[4]={0.0, 0.0, 1.0, 1.0};// "brilho"
        GLfloat posicaoLuz2[4]={100.0, 70.0, 100.0, 1.0};

        // Capacidade de brilho do material
        GLfloat especularidade1[4]={1.0,1.0,1.0,1.0};
        GLint especMaterial1 = 60;

        // Define a refletância do material
        glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade1);

        // Define a concentração do brilho
        glMateriali(GL_FRONT,GL_SHININESS,especMaterial1);

        // Ativa o uso da luz ambiente
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente1);

        // Define os parâmetros da luz de número 0
        glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular1);
        glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz2);

}

//Desenhar e localizar o placar na tela
void DesenhaPlacar(char*string, int x, int y, int z)
{
    char *c;
    glPushMatrix();
    glTranslatef(x, y+8,z);
     glScalef(0.09f, 0.08f,z);
      glColor3f(1.0f, 1.0f, 1.0f);
    for (c=string; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
    }
    glPopMatrix();
}

//função de desenho, neste caso utilizada apenas para as raquetes
void DesenhaRaquete(float x, float y, float width, float height) {

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(x + width, y + height);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(x, y + height);
    glEnd();

}

// Desenha um quadrado preenchido com a cor corrente
void DesenhaQuadrado(void){

      glBegin (GL_QUADS);
               glVertex2i(x1,y1+rsize);
               glColor3f(1.0f, 0.0f, 0.0f);
               glVertex2i(x1,y1);
                glColor3f(0.0f, 1.0f, 0.0f);
               glVertex2i(x1+rsize,y1);
               glColor3f(0.0f, 0.0f, 1.0f);
               glVertex2i(x1+rsize,y1+rsize);
     glEnd();
}

void DesenhaTriangulo(void){ //desenho do triangulo

      glBegin (GL_TRIANGLES);
                glVertex2i(x1,y1+rsize);
                glColor3f(1.0f, 0.0f, 0.0f);
               glVertex2i(x1,y1);
               glColor3f(0.0f, 1.0f, 0.0f);
               glVertex2i(x1+rsize,y1);
               glColor3f(0.0f, 0.0f, 1.0f);
               glVertex2i(x1+rsize,y1+rsize);

     glEnd();

     glBegin (GL_TRIANGLES);
                glVertex2i(x1,y1+rsize);
                glColor3f(1.0f, 0.0f, 0.0f);
               glVertex2i(x1,y1);
               glColor3f(0.0f, 1.0f, 0.0f);
               glVertex2i(x1-rsize,y1);
               glColor3f(0.0f, 1.0f, 1.0f);
               glVertex2i(x1+rsize,y1+rsize);
     glEnd();
}

void DesenhaRetangulo(void){ //desenho do retangulo

     glBegin (GL_POLYGON);
                glVertex2f(x1,y1+rsize);
                glColor3f(1.0f, 0.0f, 0.0f);
               glVertex2f(x1,y1);
               glColor3f(0.0f, 1.0f, 0.0f);
               glVertex2f(x1+rsize*2,y1);
               glColor3f(0.0f, 0.0f, 1.0f);
               glVertex2f(x1+rsize*2,y1+rsize);
     glEnd();
}

//função especial do teclado para mover as raquetes
void teclado(int key, int x, int y) {
    // racket esquerda
    switch(key){
    case GLUT_KEY_UP:
        racket_left_y += racket_speed;
        break;
    case GLUT_KEY_DOWN:
        racket_left_y -= racket_speed;
        break;

    // racket direita
    case GLUT_KEY_F1:
        racket_right_y += racket_speed;
        break;
    case GLUT_KEY_F2:
        racket_right_y -= racket_speed;
        break;
    }
}

// Função callback chamada para fazer o desenho
void Desenha(void){
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     // Limpa a janela de visualização com a cor de fundo especificada
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //DefineIluminacao();

     // Especifica que a cor corrente
     //         R     G     B
     glColor3f(r,g,b);

     // Desenha uma primitiva
     switch (primitiva) {
            case QUADRADO:  DesenhaQuadrado();
                            break;
            case TRIANGULO: DesenhaTriangulo();
                            break;
            case RETANGULO: DesenhaRetangulo();
                            break;
     }

    // coordenadas do desenho das raquetes na tela
    DesenhaRaquete(racket_left_x, racket_left_y, racket_width, racket_height);
    DesenhaRaquete(racket_right_x, racket_right_y, racket_width, racket_height);

    // desenha o placar do player 1
    snprintf (score_1, sizeof(score_1), "%d", player1_score);
    DesenhaPlacar(score_1, 100, 200, 0);

    // desenha o placar do player 2
    snprintf (score_2, sizeof(score_2), "%d", player2_score);
    DesenhaPlacar(score_2, 150, 200, 0);

    if(player1_score == 10){
        DesenhaPlacar("Player 1 Ganhou!!", 80, 125, 0);
    };

     if(player2_score == 10){
        DesenhaPlacar("Player 2 Ganhou!!", 80, 125, 0);
    };

     // Executa os comandos OpenGL
     glutSwapBuffers();
}

void update(int value){

     //chama update() novamente no intervalo milisegundos
    glutTimerFunc(interval, update, 0);

    //reapresenta o frame
    glutPostRedisplay();
}

// Função callback chamada pela GLUT a cada intervalo de tempo
// (a window não está sendo redimensionada ou movida)
void Timer(int value)
{

 // quando acertar a raquete esquerda
 if(    x1-5 < racket_left_x + racket_width &&
        x1-5 > racket_left_x &&
        y1 < racket_left_y + racket_height &&
        y1 > racket_left_y) {
                      xstep = -xstep*1.05, racket_speed++;
                                };

// quando acertar a raquete direta
if (    x1+rsize > racket_right_x &&
        x1+rsize < racket_right_x + racket_width &&
        y1+2+rsize < racket_right_y + racket_height &&
        y1+2+rsize > racket_right_y) {
                      xstep = -xstep*1.05, racket_speed++;
                                };

// Muda a direção quando chega na borda esquerda ou direita && muda a primitiva e a cor
if(player1_score <= 9 ){
   if(x1 > windowWidth-rsize){
         xstep = -xstep,
            primitiva = RETANGULO,
                player1_score++;
                    glColor3b(1.0f, 1.0f, 0.0f);
         };
};

if(player2_score <= 9){
         if(x1 < 0){
            xstep = -xstep,
                primitiva = RETANGULO,
                    player2_score++;
                        glColor3b(1.0f, 0.0f, 1.0f);
         };
};

// Muda a direção quando chega na borda superior ou inferior  && muda a primitiva e a cor
    if(y1 > windowHeight-rsize || y1 < 0)
          ystep = -ystep,
            primitiva = TRIANGULO,
                glColor3b(0.0f, 1.0f, 1.0f);

// Verifica as bordas.  Se a window for menor e o
    // quadrado sair do volume de visualização
   if(x1 > windowWidth-rsize)
         x1 = windowWidth-rsize-1;

   if(y1 > windowHeight-rsize)
         y1 = windowHeight-rsize-1;

    // Move o quadrado
    x1 += xstep;
    y1 += ystep;

//testa o tamanho da janela para que a raquete direita se mova junto com a janela
    if (windowWidth >= 250)
            racket_right_x = windowWidth - 12;

    // Redesenha o quadrado com as novas coordenadas
    glutPostRedisplay();
    glutTimerFunc(33,Timer, 1);
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    DefineIluminacao();
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    primitiva = 3;

    // Habilita a definição da cor do material a partir da cor corrente
        glEnable(GL_COLOR_MATERIAL);

        //Habilita o uso de iluminação
        glEnable(GL_LIGHTING);

        // Habilita a luz de número 0
        glEnable(GL_LIGHT0);

         // Habilita a luz de número 1
        glEnable(GL_LIGHT1);

        // Habilita o depth-buffering
        glEnable(GL_DEPTH_TEST);

        // Habilita o modelo de colorização de Gouraud
        glShadeModel(GL_SMOOTH);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
     // Evita a divisao por zero
     if(h == 0) h = 1;

     // Especifica as dimensões da Viewport
     glViewport(0, 0, w, h);

     // Inicializa o sistema de coordenadas
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     // Estabelece a janela de seleção (left, right, bottom, top)
     if (w <= h)  {
		windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
     }
     else  {
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
     }

     gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

// Programa Principal
int main(void)
{
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(800,800);
     glutInitWindowPosition(0,0);
     glutCreateWindow("Trabalho Prático– DaniloAlmeida - MilenaMiyoshi - ReynoldPereira");
     glutDisplayFunc(Desenha);
     glutReshapeFunc(AlteraTamanhoJanela);
     glutTimerFunc(33, Timer, 1);
     Inicializa();
     glutSpecialFunc(teclado);

     //inicia tudo
     glutMainLoop();

}
