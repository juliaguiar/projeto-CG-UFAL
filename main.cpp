#include "main.h"

#include <fstream>
#include <SFML/Graphics.hpp>

#define PI 3.1415926535898

// direção da câmera
float lx = 0, ly = 0,lz = -1;
float angleXZ = 0, angleY = 0;

// posição da câmera
float x = 0,y = 1, z =10;

int mouseX;
int mouseY;

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {0.0, 1.0, 1.0, 1.0};

float angle = 0.0f;

float glass_alpha = 0.5f;

float right_door_angle = 0.0f;
float left_door_angle = 0.0f;

GLuint texture_id[20];

void middle_circle (GLfloat radius) {
	
	GLfloat circle_points = 50;
	GLfloat angle;
	glBegin(GL_POLYGON);
		
		for (int i = 0; i < circle_points+1; i++) 
		{
			angle = PI*i/circle_points;
			glVertex2f(radius*cos(angle), radius*sin(angle));
		}
		
	glEnd();
	
}

void drawCube(GLdouble size, int *tex) {
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    if(tex[i] >= 0) {
      glBindTexture(GL_TEXTURE_2D, texture_id[tex[i]]);
    }
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    if(i==1)
      glTexCoord2f(1.0f, 0.0f);
    else
      glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(&v[faces[i][0]][0]);
    if(i==1)
      glTexCoord2f(0.0f, 0.0f);
    else
      glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(&v[faces[i][1]][0]);
    if(i==1)
      glTexCoord2f(0.0f, 1.0f);
    else
      glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(&v[faces[i][2]][0]);
    if(i==1)
      glTexCoord2f(1.0f, 1.0f);
    else
      glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
    if(tex[i] >= 0) {
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
}

void drawOfficeDesk(float x, float y, float z) {
    glColor3f(0.1f, 0.1f, 0.1f);
	
	int office_desk_texture[] = {8, 8, 8, 8, 8, 8};
    
    //base esquerda
    glPushMatrix();
    glTranslatef(x, 0.125f+y, z);
    glScalef(0.2, 0.1, 0.7);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();

	//lateral esquerda
	glPushMatrix();
    glTranslatef(x, 0.4f+y, z);
    glScalef(0.1, 0.5f, 0.4);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
     
    //base direita
    glPushMatrix();
    glTranslatef(x+1, 0.125f+y, z);
    glScalef(0.2, 0.1, 0.7);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();    
    
    //lateral direita
	glPushMatrix();
    glTranslatef(x+1, 0.4f+y, z);
    glScalef(0.1, 0.5f, 0.4);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
    
    //parte superior da mesa 
    glPushMatrix();
    glTranslatef(x+0.5, 0.7f+y, z);
    glScalef(1.5, 0.1, 1.0);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
}

void drawProjector() {
	int projector_texture[] = {-1, -1, -1, 4, -1, -1};
	
    //Projector 1

	glColor3f(1.0f, 1.0f, 1.0f);
	//suporte projetor
    glPushMatrix();
    glTranslatef(4.0f, 5.075f, -29.0);
    glScalef(0.05, 1.1, 0.05);
    glutSolidCube(1.0f);
    glPopMatrix();
    
	//projetor
    glPushMatrix();
    glTranslatef(4.0f, 4.4625f, -29.0f);
    glScalef(0.5, 0.125, 0.5);
    drawCube(1.0f, projector_texture);
    glPopMatrix();
    
    //Projector 2

    glColor3f(1.0f, 1.0f, 1.0f);
    //suporte projetor
    glPushMatrix();
    glTranslatef(-4.0f, 5.075f, -29.0);
    glScalef(0.05, 1.1, 0.05);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //projetor
    glPushMatrix();
    glTranslatef(-4.0f, 4.4625f, -29.0f);
    glScalef(0.5, 0.125, 0.5);
    drawCube(1.0f, projector_texture);
    glPopMatrix();
}

void drawPainting() {
    //bordas quadro
    int pulpit_texture[] = {-1, -1, -1, -1, 6, -1};
    glColor3f(0.0,0.72,0.44);
    glPushMatrix();
    //glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 3.5f, -31.0f);
    glScalef(1.5, 2.0, 0.1);
    drawCube(1.0f, pulpit_texture);
    // glutSolidCube(1.0f);
    glPopMatrix();
}


void drawPulpit() {

    int pulpit_texture[] = {2, 2, 2, 2, 2, 2};
    
    //Base
    glColor3f(0.0,0.72,0.44); 
    glPushMatrix();
    glTranslatef(-0.0f, 0.8f, -29.0); 
    glScalef(1.0, 1.3, 0.4);
    drawCube(1.0f, pulpit_texture);
    glPopMatrix();
    
    //Baixo
   	
    glPushMatrix();
    glTranslatef(-0.0f, 0.1f, -28.5);
    glScalef(1.5, 0.2, 1.2);
    drawCube(1.0f, pulpit_texture);
    glPopMatrix();

}

void drawAirConditioning(float x, float z, char side) {
	//area de projeção
	int air_texture[] = {3, -1, -1, -1, -1, -1};
	
	if(side == 'r') {
		air_texture[0] = 3;
	} else if(side == 'l') {
		air_texture[2] = 3;
	}
	
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(x, 3.25f, z);
    glScalef(0.25, 0.5, 1.5);
    drawCube(1.0f, air_texture);
    glPopMatrix();
}

void drawProjectionQuad() {
	
    //Projetor 1

    //bordas quadro
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(4.1f, 4.1f, -31.0f);
    glScalef(2.5, 2.0, 0.1);
    glutSolidCube(1.0f);
    glPopMatrix();

	//area de projeção
	glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(4.1f, 4.0f, -30.5f);
    glScalef(2.0, 1.5, 0.1);
    glutSolidCube(1.0f);
    glPopMatrix();

    //Projector 2

    //bordas quadro
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-4.1f, 4.1f, -31.0f);
    glScalef(2.5, 2.0, 0.1);
    glutSolidCube(1.0f);
    glPopMatrix();

    //area de projeção
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-4.1f, 4.0f, -30.5f);
    glScalef(2.0, 1.5, 0.1);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawChair(float x, float z) {
    glColor3f(0.5f, 0.2f, 0.0f);
    
    int chair_texture[] = {2, 2, 2, 2, 2, 2};
    
    //base esquerda
    glPushMatrix();
    glTranslatef(x, 0.125f, z); 
    glScalef(0.25, 0.25, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();

	//lateral esquerda
	glPushMatrix();
    glTranslatef(x, 0.5f, z);
    glScalef(0.125, 0.5f, 0.8);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte esquerdo do apoio traseiro
    glPushMatrix();
    glTranslatef(x, 0.875f, z+0.45);
    glScalef(0.1, 1.25f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //base direita
    glPushMatrix();
    glTranslatef(x+2, 0.125f, z);
    glScalef(0.25, 0.25, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();    
    
    //lateral direita
	glPushMatrix();
    glTranslatef(x+2, 0.5f, z);
    glScalef(0.125, 0.5f, 0.8);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //assento 
    glPushMatrix();
    glTranslatef(x+1, 0.6f, z);
    glScalef(2.0, 0.1, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte direito do apoio traseiro
    glPushMatrix();
    glTranslatef(x+2, 0.875f, z+0.45);
    glScalef(0.1, 1.25f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte das costas
    glPushMatrix();
    glTranslatef(x+1.0f, 1.125f, z+0.45);
    glScalef(2.25f, 0.75f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
}

void drawTemple() {

    int chair_texture[] = {2, 2, 2, 2, 2, 2};
    int wall_texture[] = {5, 5, 5, 5, 5, 5};
    
    //Desenha linha horizontal
    glPushMatrix();
    glTranslatef(-0.5f, 8.5f, -2.0f); 
    glScalef(1.5, 0.3, 0.3);  
    glColor3f(0.745,0.423,0.188);
    drawCube(0.5f, chair_texture);
    glPopMatrix();
    
    //Desenha linha vertical
    glPushMatrix();
    glTranslatef(-0.5f, 8.3f, -2.0f); 
    glScalef(0.3, 3.0, 0.3);  
    glColor3f(0.745,0.423,0.188);
    drawCube(0.5f, chair_texture);
    glPopMatrix();
	
    //Desenha parede frontal da entrada a direita 1/2
    glPushMatrix();
    glTranslatef(5.0f, 1.65f, -2.25f); 
    glScalef(10.0, 8.8, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    drawCube(0.5f, wall_texture);
    glPopMatrix();
    
    //Desenha parede frontal da entrada a direita 2/2
    glBegin(GL_TRIANGLES);  
    glColor3f(1.0,1.0,0.74);
    glVertex3f(2.5f,3.75f,-1.75f);
    glVertex3f(7.5f,3.75f,-1.75f); 
    glVertex3f(2.5f,6.0f,-1.75f);
    glEnd();
    
    //Desenha parede lateral direita da entrada principal  
    glPushMatrix();
    glTranslatef(2.5f, 3.0f, -5.5f); 
    glScalef(0.5, 6.0, 7.0);  
    glColor3f(0.917,0.8431,0.7372);
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //Desenha parede frontal da entrada a esquerda 1/2
    glPushMatrix();
    glTranslatef(-5.5f, 1.65f, -2.25f); 
    glScalef(8.0, 8.8, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    drawCube(0.5f, wall_texture); 
    glPopMatrix();
    
    //Desenha parede frontal da entrada a esquerda 2/2
    glBegin(GL_TRIANGLES);  
    glColor3f(1.0,1.0,0.74);
    glVertex3f(-3.5f,3.75f,-1.75f); 
    glVertex3f(-7.5f,3.75f,-1.75f);
    glVertex3f(-3.5f,6.0f,-1.75f);
    glEnd();
    
    //Desenha parede lateral esquerda da entrada principal 
    glPushMatrix();
    glTranslatef(-3.5f, 3.0f, -5.5f); 
    glScalef(0.5, 6.0, 7.0);  
    glColor3f(0.917,0.8431,0.7372);
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //Desenha parede da porta de entrada da igreja 1/4 (parte maior)
    glPushMatrix();
    glTranslatef(-0.5f, 3.95f, -2.25f); 
    glScalef(12.9, 7.0, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    drawCube(0.5f, wall_texture);
    glPopMatrix();
    
    //Desenha parede da porta de entrada da igreja 2/4
    glPushMatrix();
    glTranslatef(-2.225f, 1.1f, -2.25f); 
    glScalef(5.0, 4.4, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    drawCube(0.5f, wall_texture);
    glPopMatrix();
    
    //Desenha parede da porta de entrada da igreja 4/4
    glPushMatrix();
    glTranslatef(1.5f,1.1f, -2.25f); 
    glScalef(5.0,4.4, 1.0); 
    glColor3f(0.917,0.8431,0.7372);
    drawCube(0.5f, wall_texture);
    glPopMatrix();
    
    //Desenha triângulo da ponta da igreja
    glBegin(GL_TRIANGLES);  
    glColor3f(0.917,0.8431,0.7372);
    glVertex3f(-3.3f,5.75f,-1.7f);
    glVertex3f(2.3f,5.75f,-1.7f);
    glVertex3f(-0.5f,7.35f,-1.7f); 
    glEnd();
    
    //Desenha 1° linha horizontal da entrada principal da igreja
    glPushMatrix();
    glTranslatef(-0.5f, 5.70, -1.9); 
    glScalef(13.0, 0.3, 0.8);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();

    //Desenha 1° linha vertical da entrada principal da igreja
    glPushMatrix();
    glTranslatef(-3.52f, 3.0f, -1.9); 
    glScalef(1.0, 12.0, 0.8);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
    
    //Desenha 2° linha vertical da entrada principal da igreja
    glPushMatrix();
    glTranslatef(2.52f, 3.0f, -1.9); 
    glScalef(1.0, 12.0, 0.8);  
    glRotatef(-90.0f, 0,0 , 1);
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
	
    //Parede lateral direita
	glPushMatrix();
    glColor3f(0.917,0.8431,0.7372);
    glTranslatef(7.25f, 1.65f, -16.95f); 
    glScalef(0.5, 4.4, 29.75);
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //Parede lateral esquerda
	glPushMatrix();
    glColor3f(0.917,0.8431,0.7372);
    glTranslatef(-7.25f, 1.65f, -16.95f);
    glScalef(0.5, 4.4, 29.75);
    drawCube(1.0f, wall_texture);
    glPopMatrix();
	
    //parede do fundo do templo 1/2
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(0.0f, 1.8f, -31.75f);
    glScalef(14.5, 4.5, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //parede do fundo do templo 2/2
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(-0.5f, 4.5f, -31.75f);
    glScalef(6.0, 2.5, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //Desenha triângulo da parede de fundo 1/2
    glBegin(GL_TRIANGLES);  
    glColor3f(1.0,1.0,0.74);
    glVertex3f(2.5f,3.75f,-31.75f);
    glVertex3f(7.5f,3.75f,-31.75f); 
    glVertex3f(2.5f,6.0f,-31.75f);
    glEnd();
    
    //Desenha triângulo da parede de fundo 2/2
    glBegin(GL_TRIANGLES);  
    glColor3f(1.0,1.0,0.74);
    glVertex3f(-3.5f,3.75f,-31.75f); 
    glVertex3f(-7.5f,3.75f,-31.75f);
    glVertex3f(-3.5f,6.0f,-31.75f);
    glEnd();
    
    //teto do templo 1/3
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(-0.5f, 5.75f, -20.75f); 
    glScalef(6.5, 0.5, 22.5);
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //teto do templo 2/3
    glPushMatrix();
    glColor3f(1.0f,0.66f,1.0f); 
    glTranslatef(-5.6f, 4.65f, -16.95f); 
    glRotatef(30.0f, 0, 0, 1);
    glScalef(4.38, 0.5, 29.75);
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //teto do templo 3/3
    glPushMatrix();
    glColor3f(1.0f,0.66f,1.0f);
    glTranslatef(5.13f, 4.7f, -16.95f); 
    glRotatef(-25.0f, 0, 0, 1);
    glScalef(5.35, 0.5, 29.75); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
	
    //teto interno entrada do templo (DIREITA)
    glPushMatrix();
    glColor3f(0.745,0.423,0.188);
    glTranslatef(1.0f, 6.75f, -5.5f);
    glRotatef(60.15f, 0, 0, 1);
    glScalef(0.5, 3.8, 7.0);
    glutSolidCube(1.0);
    glPopMatrix();
	
    //teto interno entrada do templo (ESQUERDA)
    glPushMatrix();
    glColor3f(0.745,0.423,0.188);
    glTranslatef(-2.0f, 6.75f, -5.5f);
    glRotatef(-60.0f, 0, 0, 1);
    glScalef(0.5, 3.8, 7.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    //Desenha 1° linha do teto da igreja (DIREITA)
    glPushMatrix();
    glTranslatef(1.0f, 6.8f, -1.9f);
    glRotatef(59.15f, 0, 0, 1); 
    glScalef(0.8, 7.5, 0.8);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
    
    //Desenha 2° linha do teto da igreja (ESQUERDA)
    glPushMatrix();
    glTranslatef(-2.0f, 6.8f, -1.9f);
    glRotatef(-60.0f, 0, 0, 1);
    glScalef(0.8, 7.6, 0.8);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();

	int pulpito_texture[] = {8, 8, 8, 8, 8, 8};
    
    //PAREDE INTERNA 
    
    //triangulo 1/2 ESQUERDA
    glBegin(GL_TRIANGLES);  
    glColor3f(1.0,1.0,0.74);
    glVertex3f(-3.6f,3.55f,-25.65f); 
    glVertex3f(-7.6f,3.55f,-25.65f);
    glVertex3f(-3.6f,5.8f,-25.65f);
    glEnd();
    
    //triangulo 2/2 DIREITA
    glBegin(GL_TRIANGLES);  
    glColor3f(1.0,1.0,0.74);
    glVertex3f(2.75f,3.55f,-25.65f);
    glVertex3f(7.75f,3.55f,-25.65f); 
    glVertex3f(2.75f,5.8f,-25.65f);
    glEnd();
    
    //quadrado 
    glBegin(GL_QUADS);
    glVertex3f(-3.6f,3.55f,-25.65f); 
    glVertex3f(-3.6f,5.8f,-25.65f);
    glVertex3f(2.75f,5.8f,-25.65f);
    glVertex3f(2.75f,3.55f,-25.65f);
    glEnd();
    
    //parede 1/7 lado direito principal
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(2.5f, 1.6f,-26.0f);
    glScalef(2.5, 4.0, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //parede 2/7 lado esquerdo principal
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(-2.5f, 1.6f,-26.0f);
    glScalef(2.5, 4.0, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix(); 
	
	//meio círculo da passagem principal
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, -25.7f);
    middle_circle(1.25);
    glPopMatrix(); 
    
    //parede 3/7 de cima principal
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(0.0f, 3.1f,-26.0f);
    glScalef(2.5, 1.0, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //parede 4/7 lado esquerdo da entrada esquerda
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(-6.0f, 1.6f,-26.0f);
    glScalef(1.5, 4.0, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //meio círculo da passagem esquerda
    glPushMatrix();
    glTranslatef(-4.5f, 2.0f, -25.7f);
    middle_circle(0.75);
    glPopMatrix(); 
    
    //parede 5/7 de cima passagem esquerda
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(-4.5f, 2.85f,-26.0f);
    glScalef(1.5, 1.5, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //parede 6/7 lado direito da entrada direita
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(6.15f, 1.6f,-26.0f);
    glScalef(1.8, 4.0, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
    
    //meio círculo da passagem esquerda
    glPushMatrix();
    glTranslatef(4.5f, 2.0f, -25.7f);
    middle_circle(0.75);
    glPopMatrix();
    
    //parede 7/7 de cima passagem direita
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(4.5f, 2.85f,-26.0f);
    glScalef(1.5, 1.5, 0.5); 
    drawCube(1.0f, wall_texture);
    glPopMatrix();
}

void drawDoor() {
    
    int chair_texture[] = {2, 2, 2, 2, 2, 2};
    
    //porta esquerda principal
    glPushMatrix();
    glColor3f(0.0,0.05,0.0); 
    glTranslatef(-0.675f, 1.05f, -1.8f);
    glRotatef(left_door_angle, 0, 1, 0);
    if(left_door_angle > 0)	
		glTranslatef(-0.1f, 0.0f, -0.25f);
    glScalef(0.6, 2.3, 0.1f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();       
    
    //Desenha borda esquerda da porta esquerda 
    glPushMatrix();
    glTranslatef(-1.05f, 1.07f, -1.9f);
    glScalef(0.3, 4.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
    
    //porta direita principal
    glPushMatrix();
    glColor3f(0.0,0.05,0.0); 
    glTranslatef(-0.05f, 1.05f, -1.8f); 
    glRotatef(right_door_angle, 0, 1, 0);
    if(right_door_angle > 0)	
		glTranslatef(-0.1f, 0.0f, 0.25f);
    glScalef(0.6, 2.3, 0.1f);
    drawCube(1.0f, chair_texture);
    glPopMatrix(); 
    
    //Desenha borda direita da porta direita
    glPushMatrix();
    glTranslatef(0.3f, 1.07f, -1.9f); 
    glScalef(0.3, 4.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
    
    //meio círculo menor da porta
    glPushMatrix();
    glTranslatef(-0.35f, 2.2f, -1.8f);
    glColor3f(0.0,0.05,0.0); 
    middle_circle(0.625);
    glPopMatrix();
    
    //meio círculo maior da porta
    glPushMatrix();
    glTranslatef(-0.35f, 2.2f, -1.8f);
    middle_circle(0.75);
    glPopMatrix();
    
    //PORTA ESQUERDA
    
    //parte esquerda
    glPushMatrix();
    glColor3f(0.0,0.05,0.0); 
    glTranslatef(-6.0f, 0.8f, -1.8f); 
    glScalef(0.6, 1.8, 0.1f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //borda parte esquerda  
    glPushMatrix();
    glTranslatef(-6.375f, 0.82f, -1.9f); 
    glScalef(0.3, 3.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
    
    //parte direita 
    glPushMatrix();
    glColor3f(0.0,0.05,0.0); 
    glTranslatef(-5.35f, 0.8f, -1.8f); 
    glScalef(0.6, 1.8, 0.1f);
    drawCube(1.0f, chair_texture);
    glPopMatrix(); 
    
    //borda parte direita 
	//Desenha borda direita da porta direita
    glPushMatrix();
    glTranslatef(-5.0f, 0.82f, -1.9f);
    glScalef(0.3, 3.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix(); 
    
    //meio círculo maior da porta
    glPushMatrix();
    glTranslatef(-5.7f, 1.7f, -1.8f);
    middle_circle(0.75);
    glPopMatrix();
    
	
	//PORTA DIREITA 
	
	//parte esquerda
    glPushMatrix();
    glColor3f(0.0,0.05,0.0); 
    glTranslatef(4.775f, 0.8f, -1.8f); 
    glScalef(0.6, 1.8, 0.1f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //borda parte esquerda  
    glPushMatrix();
    glTranslatef(4.4f, 0.82f, -1.9f); 
    glScalef(0.3, 3.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
	
	//parte direita 
    glPushMatrix();
    glColor3f(0.0,0.05,0.0); 
    glTranslatef(5.425f, 0.8f, -1.8f); 
    glScalef(0.6, 1.8, 0.1f);
    drawCube(1.0f, chair_texture);
    glPopMatrix(); 
    
    //borda parte direita 
	//Desenha borda direita da porta direita
    glPushMatrix();
    glTranslatef(5.775f, 0.82f, -1.9f); 
    glScalef(0.3, 3.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix(); 
    
    //meio círculo maior da porta
    glPushMatrix();
    glTranslatef(5.1f, 1.7f, -1.8f);
    middle_circle(0.75);
    glPopMatrix();
}

void drawWindows() {
    int chair_texture[] = {2, 2, 2, 2, 2, 2};
	
    //Janela Esquerda
    glPushMatrix();
    glColor3f(0.0,0.05,0.0); 
    glTranslatef(-2.05f, 4.35f, -2.0f);
    glScalef(1.0, 1.75, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();      
	
	//Desenha segunda borda superior da janela
    glPushMatrix();
    glTranslatef(-2.05f, 5.3f, -1.9f);
    glScalef(2.6, 0.3, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();  
    
	//Desenha borda esquerda da janela a esquerda
    glPushMatrix();
    glTranslatef(-2.64f, 4.35f, -1.9f);
    glScalef(0.3, 3.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
    
	//Desenha borda direita da janela a esquerda
    glPushMatrix();
    glTranslatef(-1.47f, 4.35f, -1.9f);
    glScalef(0.3, 3.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
    
    //borda inferior
    glPushMatrix();
    glTranslatef(-2.05f, 3.4f, -1.9f);
    glScalef(2.6, 0.3, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();
	
	
    //Janela Direita
    glPushMatrix();
    glColor3f(0.0,0.05,0.0); 
    glTranslatef(1.2f, 4.35f, -2.0f);
    glScalef(1.0, 1.75, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();  
	           
    //Desenha segunda borda superior da janela
    glPushMatrix();
    glTranslatef(1.2f, 5.3f, -1.9f);
    glScalef(2.6, 0.3, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();  
    
	//Desenha borda esquerda da janela esquerda
    glPushMatrix();
    glTranslatef(0.63f, 4.35f, -1.9f);
    glScalef(0.3, 3.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix(); 
    
	//Desenha borda direita da janela direita
    glPushMatrix();
    glTranslatef(1.77f, 4.35f, -1.9f);
    glScalef(0.3, 3.5, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix(); 
	
	//borda inferior
    glPushMatrix();
    glTranslatef(1.2f, 3.4f, -1.9f);
    glScalef(2.6, 0.3, 0.6);  
    glColor3f(0.0,0.72,0.44); 
    glutSolidCube(0.5);
    glPopMatrix();   
	
}

void drawFloor() {

  //piso-templo
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[7]);	 
  glTranslatef(0.0f, 0.0f, -13.0f);
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f); 
  glVertex3f(-7.5f, 0.0f, -19.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-7.5f, 0.0f, 7.5f);
  glTexCoord2f(1.0f, 0.0f); 
  glVertex3f( 7.5f, 0.0f, 7.5f);
  glTexCoord2f(1.0f, 1.0f); 
  glVertex3f( 7.5f, 0.0f, -19.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);	 
  glPopMatrix();
  
  //gramado lado esquerdo
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glTranslatef(-5.0f, 0.0f, 6.25f);
  glBegin(GL_QUADS);
  //glColor3f(0.0f, 0.3f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-2.5f, 0.0f, -11.75f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-2.5f, 0.0f, 2.5f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f( 2.5f, 0.0f, 2.5f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f( 2.5f, 0.0f, -11.75f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  
  //gramado lado direito
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glTranslatef(3.25f, 0.0f, 4.5f);
  glBegin(GL_QUADS);
  //glColor3f(0.0f, 0.3f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-4.25f, 0.0f, -10.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-4.25f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f( 4.25f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f( 4.25f, 0.0f, -10.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  
  //piso entrada
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[7]);	 
  glTranslatef(-1.75f, 0.0f, 4.5f);
  glBegin(GL_QUADS);
  //glColor3f(0.0f, 0.3f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f); 
  glVertex3f(-0.75f, 0.0f, -10.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-0.75f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 0.0f); 
  glVertex3f( 0.75f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 1.0f); 
  glVertex3f( 0.75f, 0.0f, -10.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);	 
  glPopMatrix();
}

//função DESENHO
void display()
{
  // "limpa" um buffer particular ou combinações de buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // To operate on model-view matrix
  glMatrixMode(GL_MODELVIEW);     
  // Reset transformations
  glLoadIdentity();
  // Set the camera
  gluLookAt(  x, y, z,
  x+lx, y, z+lz,
  0.0f, 1.0f, 0.0f);


  drawChair(1.0f, -16.0f);
  drawChair(1.0f, -18.0f);
  drawChair(1.0f, -20.0f);
  drawChair(1.0f, -22.0f);
  
  drawChair(-3.0f, -22.0f);
  drawChair(-3.0f, -20.0f);
  drawChair(-3.0f, -18.0f);
  drawChair(-3.0f, -16.0f);
  
  drawFloor();
  drawTemple();
  drawDoor();
  drawWindows();
  drawOfficeDesk(-5.5f, -0.1f, -10.0f);
  drawOfficeDesk(4.0f, -0.1f, -10.0f);
  drawAirConditioning(6.85, -22.0, 'r');
  drawAirConditioning(6.85, -18.0, 'r');
  drawAirConditioning(6.85, -14.0, 'r');  
  drawAirConditioning(-6.85, -28.0, 'l');
  drawAirConditioning(-6.85, -25.0, 'l');
  drawAirConditioning(-6.85, -22.0, 'l');
  drawPulpit();
  drawPainting();
  
  glFlush(); 
  glutSwapBuffers(); 
}

void cameraViewUpdate(void){
   	ly = sin(angleY);
    lx = sin(angleXZ);
    lz = -cos(angleXZ);
}

void processNormalKeys(unsigned char key, int x2, int y2) {

	switch(key){
        case 'p':
        if(right_door_angle < 90.0f) right_door_angle=90.0f;
        glutPostRedisplay();
        break;
        
        case 'o':
        if(left_door_angle < 90.0f) left_door_angle=90.0f;
        glutPostRedisplay();
        break;

        case 'v':
        if(right_door_angle >= 90.0f) right_door_angle=0.0f;
        glutPostRedisplay();
        break;

        case 'c':
        if(left_door_angle >= 90.0f) left_door_angle=0.0f;
        glutPostRedisplay();
        break;

        case 'a':
        	angle -= 0.05f;
    		lx = sin(angle);
    		lz = -cos(angle);
    		break;
        case 'd':
        	angle += 0.05f;
    		lx = sin(angle);
    		lz = -cos(angle);
        	break;
        case 'r':
        	y += 0.1;
        	break;
        case 'f':
        	y -= 0.1;
        	if(y<0)
        		y=0.1;
        	break;
        	
        case 27:
            exit(0);
        break;
    }
}

void processSpecialKeys(int key, int xx, int yy) {

    float fraction = 0.9f;

    switch (key) {
        case GLUT_KEY_LEFT :
        	x += lz * fraction;
        	z -= lx * fraction;
        break;

        case GLUT_KEY_RIGHT :
        	x -= lz * fraction;
        	z += lx * fraction;
        break;

        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
        break;

        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
        break;
    }
}

void mousePassive(int x, int y){
    mouseX = x;
    mouseY = y;
}

void mouseMotion(int x, int y){
    const float SPEED = 100;

    angleXZ += (mouseX-x)/SPEED;
    angleY -= (mouseY-y)/SPEED;
    mousePassive(x, y);
    glutPostRedisplay();
}

void mouseFunc(int button, int state, int xx, int yy){
    float limiter = 0.2;

    if(button == 3){
        x += lx*limiter;
        z += lz*limiter;
    } else if (button == 4){
        x -= lx*limiter;
        z -= lz*limiter;
    }

}

/*
//
//
CÓDIGO REFERENTE A IMPLEMENTAÇÃO DE TEXTURA
//
*/

/*
void loadTextureFromFile(char const *filename,int index) {
    int width, height, c;
    c = 3;
    std::ifstream file(filename);

    if(! file.good())
    throw "file not found";
    file.close();

    sf::Image image;
    image.loadFromFile(filename);

    printf("%d %d\n", width, height);

    glGenTextures(1, &texture_id[index]);
    glBindTexture(GL_TEXTURE_2D, texture_id[index]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glBindTexture(GL_TEXTURE_2D, 0);
}
*/


/*
void applyTextures(){
	loadTextureFromFile("texture/grass.jpg", 1);
	loadTextureFromFile("texture/tabaco.jpg", 2);
	loadTextureFromFile("texture/airc.jpg", 3);
	loadTextureFromFile("texture/projetor.jpg", 4);
	loadTextureFromFile("texture/parede-interna.jpg", 5);
	loadTextureFromFile("texture/jesus.jpg", 6);
	loadTextureFromFile("texture/piso-entrada.jpg", 7);
	loadTextureFromFile("texture/mesa.jpg", 8);
}
*/
	
void init() {
  glClearColor(0.7, 1.0, 1.0, 0.0); //função que determina a cor utilizada para limpar a janela (0 a 1)

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING); //ativa luz
	
  glEnable(GL_COLOR_MATERIAL); //ter um ou mais parâmetros de material rastreiam a cor atual
  glShadeModel(GL_SMOOTH); //selecione sombreamento suave
  glEnable(GL_DEPTH_TEST); //faz comparações de profundidade e atualiza o buffer de profundidade
  
  glEnable(GL_BLEND); //mistura os valores de cores de fragmentos calculados com os valores na cor buffers
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //mescla os valores RGBA de entrada (origem) com os valores RGBA que já estão no buffer de quadros (os valores de destino)
 
  glEnable(GL_TEXTURE_2D); // texturização bidimensional é realizada
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);

  //applyTextures();
}

//altera tamanho da janela
void reshape(GLsizei width, GLsizei height)
{
  if (height == 0) {
      height = 1;
  }

  glViewport(0, 0, width, height); //define como a viewport é especificada

  float ratio = width * 1.0 / height;

  glMatrixMode(GL_PROJECTION); //avisa a OpenGL que todas as futuras alterações irão afetar a "câmera"
  glLoadIdentity(); //a matriz corrente é inicializada com a matriz identidade (nenhuma transformação é acumulada)

  gluPerspective(45.0f, ratio, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW); //avisa a OpenGL que todas as futuras alterações irão afetar o que é desenhado
}

int main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE); //modo de exibição deve ser usado (single-buffered ou double-buffered)
  glutInitWindowSize(WIDTH,HEIGHT); //especifica o tamanho em pixels da janela GLUT
  glutInitWindowPosition(10, 10); //especifica a localização inicial da janela GLUT

  if(!glutCreateWindow("Capela de São Benedito")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init(); //inicializações OpenGL que devem ser executadas antes do rendering
  
  glutMotionFunc(mouseMotion);
  glutPassiveMotionFunc(mousePassive);
  glutMouseFunc(mouseFunc);
  glutDisplayFunc(display); //função callback de exibição
  glutReshapeFunc(reshape); //função callback de alteração do tamanho da janela
  glutIdleFunc(display); //define o retorno de chamada ocioso global
  glutSpecialFunc(processSpecialKeys);
  glutKeyboardFunc(processNormalKeys);

  glutMainLoop(); //começa a execução da “máquina de estados”

  return 0;
}

