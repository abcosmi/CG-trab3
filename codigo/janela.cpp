#include <iostream>
#include <string>
#include "janela.h"
#include "tinyxml2.h"

using namespace tinyxml2;

Janela::Janela(){
  largura = 0;
  altura = 0;
  corR = 0;
  corG = 0;
  corB = 0;
  titulo = "";
}

int Janela::getAltura(){
  return altura;
}

int Janela::getLargura(){
  return largura;
}

float Janela::getCorR(){
  return corR;
}

float Janela::getCorG(){
  return corG;
}

float Janela::getCorB(){
  return corB;
}

std::string Janela::getTitulo(){
  return titulo;
}

void Janela::setAltura(int a){
  altura = a;
}

void Janela::setLargura(int l){
  largura = l;
}

void Janela::setCorR(float c){
  corR = c;
}

void Janela::setCorG(float c){
  corG = c;
}

void Janela::setCorB(float c){
  corB = c;
}

void Janela::setTitulo(std::string t){
  titulo = t;
}

void Janela::leitura(std::string caminhoXML){

  // Carregando arquivo xml:
  XMLDocument xmlConfig;
  xmlConfig.LoadFile(caminhoXML.c_str());

  // Criando um elemento raiz (no caso, seria a tag aplicação):
  XMLNode *aplicacao = xmlConfig.FirstChild();
  if (aplicacao == NULL){
    std::cout << "Não foi possível ler o arquivo xml2" << std::endl;
    std::exit(1);
  }
  int raio = 0;
  float cx = 0,cy = 0;
  // Procurando pelos atribudos da janela:
  XMLElement* circulo = aplicacao->FirstChildElement("circle");
  circulo->QueryIntAttribute("r",&raio);
  circulo->QueryFloatAttribute("cx",&cx);
  circulo->QueryFloatAttribute("cy",&cy);

  this->setLargura(raio+cx);
  this->setAltura(raio+cy);
  this->setCorR(1);
  this->setCorG(1);
  this->setCorB(1);



}
