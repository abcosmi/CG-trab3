#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "tinyxml2.h"
#include "retangulo.h"

using namespace tinyxml2;

Retangulo::Retangulo(){
  id = "";
  largura = 0;
  altura = 0;
  corR = 0;
  corG = 0;
  corB = 0;
  xcentro = 0;
  ycentro = 0;
}

std::string Retangulo::getId(){
  return id;
}

int Retangulo::getLargura(){
  return largura;
}

int Retangulo::getAltura(){
  return altura;
}

float Retangulo::getCorR(){
  return corR;
}

float Retangulo::getCorG(){
  return corG;
}

float Retangulo::getCorB(){
  return corB;
}

float Retangulo::getXcentro(){
  return xcentro;
}

float Retangulo::getYcentro(){
  return ycentro;
}

void Retangulo::setId(std::string i){
  id = i;
}

void Retangulo::setLargura(int t){
  largura = t;
}

void Retangulo::setAltura(int a){
  altura = a;
}

void Retangulo::setCorR(float c){
  corR = c;
}

void Retangulo::setCorG(float c){
  corG = c;
}

void Retangulo::setCorB(float c){
  corB = c;
}

void Retangulo::setXcentro(float x){
  xcentro = x;
}

void Retangulo::setYcentro(float y){
  ycentro = y;
}

void Retangulo::leitura(XMLElement* retangulo){

  std::string cor;

  // Procurando atributos do retangulo:
  retangulo->QueryFloatAttribute("x",&xcentro);
  retangulo->QueryFloatAttribute("y",&ycentro);
  retangulo->QueryIntAttribute("width",&largura);
  retangulo->QueryIntAttribute("height",&altura);
  cor = retangulo->Attribute("fill");
  id = retangulo->Attribute("id");


  if (cor == "white"){
    this->setCorR(1);
    this->setCorG(1);
    this->setCorB(1);
  }else if (cor == "blue"){
    this->setCorR(0);
    this->setCorG(0);
    this->setCorB(1);
  }else if (cor == "green"){
    this->setCorR(0);
    this->setCorG(1);
    this->setCorB(0);
  }else if (cor == "red"){
    this->setCorR(1);
    this->setCorG(0);
    this->setCorB(0);
  }else{
    this->setCorR(0);
    this->setCorG(0);
    this->setCorB(0);
 }


}

// Função que verifica se a coordenada passada esta dentro do retangulo
int Retangulo::verificaBordas(int x,int y){
	// return ((x > this->getXcentro()-this->getTamanho()/2) && (x < this->getXcentro()+this->getTamanho()/2) && (y > this->getYcentro()-this->getTamanho()/2) && (y < this->getYcentro()+this->getTamanho()/2));
  return 0;
}

// Desenha o retangulo na tela
void Retangulo::desenhaRetangulo(){
  // Desenhar um poligono branco (retangulo)
  glColor3f((GLfloat)this->getCorR(),(GLfloat)this->getCorG(),(GLfloat)this->getCorB());
  glBegin(GL_POLYGON);
    glVertex3f(this->getXcentro(),this->getYcentro(),0.0);
    glVertex3f(this->getXcentro()+this->getLargura(),this->getYcentro(),0.0);
    glVertex3f(this->getXcentro()+this->getLargura(),this->getYcentro()-this->getAltura(),0.0);
    glVertex3f(this->getXcentro(),this->getYcentro()-this->getAltura(),0.0);
  glEnd();
}
