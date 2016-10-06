#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "tinyxml2.h"
#include "carro.h"
#define numSeg 50

using namespace tinyxml2;


Carro::Carro(){
  id = "";
  raio = 0;
  corR = 0;
  corG = 0;
  corB = 0;
  xcentro = 0;
  ycentro = 0;
}

std::string Carro::getId(){
  return id;
}

int Carro::getRaio(){
  return raio;
}

float Carro::getCorR(){
  return corR;
}

float Carro::getCorG(){
  return corG;
}

float Carro::getCorB(){
  return corB;
}

float Carro::getXcentro(){
  return xcentro;
}

float Carro::getYcentro(){
  return ycentro;
}

void Carro::setId(std::string i){
  id = i;
}

void Carro::setRaio(int t){
  raio = t;
}

void Carro::setCorR(float c){
  corR = c;
}

void Carro::setCorG(float c){
  corG = c;
}

void Carro::setCorB(float c){
  corB = c;
}

void Carro::setXcentro(float x){
  xcentro = x;
}

void Carro::setYcentro(float y){
  ycentro = y;
}

void Carro::leitura(XMLElement *carro){

  std::string cor;
  // Procurando atributos do circulo:
  circulo->QueryIntAttribute("r",&raio);
  circulo->QueryFloatAttribute("cx",&xcentro);
  circulo->QueryFloatAttribute("cy",&ycentro);
  cor = circulo->Attribute("fill");
  id = circulo->Attribute("id");

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
      this->setCorG(0.5);
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

// Função que verifica se houve colisão com os inimigos
unsigned short Carro::verificaBordas(Circulo c){
  float r = (this->getRaio() + c.getRaio());
  float dx = this->getXcentro() - c.getXcentro();
  float dy = this->getYcentro() - c.getYcentro();

  if (r > sqrt(dx*dx + dy*dy)){
    return 1;
  }else{
    return 0;
  }


}

// Função que verifica se o jogador está na pista
unsigned short Carro::dentroPista(std::vector<Circulo> Pista){
  float re,ri,xcentroInterno, ycentroInterno;

  for (unsigned int i = 0; i < Pista.size(); i++){
    if (Pista[i].getCorR() == 0 && Pista[i].getCorG() == 0 && Pista[i].getCorB() == 1){
      re = Pista[i].getRaio();
    }else if (Pista[i].getCorR() == 1 && Pista[i].getCorG() == 1 && Pista[i].getCorB() == 1){
      xcentroInterno = Pista[i].getXcentro();
      ycentroInterno = Pista[i].getYcentro();
      ri = Pista[i].getRaio();
    }
  }

  float dxi = this->getXcentro() - xcentroInterno;
	float dyi = this->getYcentro() - ycentroInterno;


	if ((sqrt(dxi*dxi + dyi*dyi) + this->getRaio()) > re){
			return 0;
		} else{
			if ((sqrt(dxi*dxi + dyi*dyi) - this->getRaio()) < ri){
					return 0;
				}else{
					return 1;
				}
		}
}

// Desenha o circulo na tela
void Carro::desenhaCarro(){
  glColor3f((GLfloat)this->getCorR(),(GLfloat)this->getCorG(),(GLfloat)this->getCorB());
  // Desenhar um poligono branco (circulo)
  glBegin(GL_POLYGON);
  	for(int i = 0; i < numSeg; i++)
  	{
  		float t = (2.0f * 3.1415926f * float(i)) / float(numSeg);

  		float x = this->getRaio() * cos(t);
  		float y = this->getRaio() * sin(t);

  		glVertex3f(x + this->getXcentro(), y + this->getYcentro(),0.0);

  	}
	glEnd();
}
