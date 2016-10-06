#ifndef T_RETANGULO
  #define T_RETANGULO
#include <iostream>
#include "tinyxml2.h"

class Retangulo {
  std::string id;
  int altura,largura;
  float corR, corG, corB;
	float xcentro, ycentro;

public:
  Retangulo();
  std::string getId();
  int getAltura();
  int getLargura();
  float getCorR();
  float getCorG();
  float getCorB();
	float getXcentro();
	float getYcentro();
  void setId(std::string);
  void setAltura(int);
  void setLargura(int);
  void setCorR(float);
  void setCorG(float);
  void setCorB(float);
	void setXcentro(float);
	void setYcentro(float);
  void leitura(tinyxml2::XMLElement*);
	int verificaBordas(int,int);
  void desenhaRetangulo();

};

#endif
