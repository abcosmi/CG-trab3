#ifndef T_JANELA
  #define T_JANELA
#include <iostream>

class Janela{
  int largura;
  int altura;
  float corR, corG, corB;
  std::string titulo;

public:
  Janela();
  int getLargura();
  int getAltura();
  float getCorR();
  float getCorG();
  float getCorB();
  std::string getTitulo();
  void setLargura(int);
  void setAltura(int);
  void setCorR(float);
  void setCorG(float);
  void setCorB(float);
  void setTitulo(std::string);
  void leitura(std::string);
};


#endif
