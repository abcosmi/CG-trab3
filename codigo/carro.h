#ifndef T_CARRO
  #define T_CARRO
#include <iostream>
#include <vector>
#include "tinyxml2.h"

class Carro {
  std::string id;
  int raio;
  float corR, corG, corB;
	float xcentro, ycentro;

public:
  Carro();
  std::string getId();
  int getRaio();
  float getCorR();
  float getCorG();
  float getCorB();
	float getXcentro();
	float getYcentro();
  void setId(std::string);
  void setRaio(int);
  void setCorR(float);
  void setCorG(float);
  void setCorB(float);
	void setXcentro(float);
	void setYcentro(float);
  void leitura(tinyxml2::XMLElement*);
	unsigned short verificaBordas(Circulo);
  unsigned short dentroPista(std::vector<Circulo>);
  void desenhaCirculo();

};

#endif
