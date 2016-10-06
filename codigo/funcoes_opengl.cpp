#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "funcoes_opengl.h"
#include "janela.h"
#include "circulo.h"
#include "retangulo.h"

extern Janela j;
extern std::vector<Circulo> Inimigos;
extern std::vector<Circulo> Pista;
extern Circulo Jogador;
extern Retangulo r;

float velCarro = 0, velTiro = 0;
int keyStatus[256];  // Possui a informação de qual tecla doi apertada

using namespace tinyxml2;

void leituraXML(std::string caminhoXML){

	std::string nome,tipo,caminhoSVG;

  // Carregando arquivo xml:
  XMLDocument xmlConfig;
  xmlConfig.LoadFile(caminhoXML.c_str());

  // Criando um elemento raiz (no caso, seria a tag aplicação):
  XMLNode *aplicacao = xmlConfig.FirstChild();
  if (aplicacao == NULL){
    std::cout << "Não foi possível ler o arquivo xml" << std::endl;
    std::exit(0);
  }

  // Obtendo informacao do arquivo svg:
  XMLElement* arquivoDaArena = aplicacao->FirstChildElement("arquivoDaArena");
  nome = arquivoDaArena->Attribute("nome");
  tipo = arquivoDaArena->Attribute("tipo");
  caminhoSVG = arquivoDaArena->Attribute("caminho");
	XMLElement* carro = aplicacao->FirstChildElement("carro");
	carro->QueryFloatAttribute("velTiro",&velTiro);
	carro->QueryFloatAttribute("velTiro",&velCarro);


	// Carregando arquivo xml:
	XMLDocument svgConfig;
	svgConfig.LoadFile((caminhoSVG+nome+"."+tipo).c_str());

	// Criando um elemento raiz (no caso, seria a tag aplicação):
	XMLNode *svg = svgConfig.FirstChild();
	if (svg == NULL){
		std::cout << "Não foi possível ler o arquivo svg" << std::endl;
		std::exit(0);
	}

// Informações dos circulos (Pista, jogador e inimigos):
	XMLElement* elemento = svg->FirstChildElement("circle");
	while (elemento != NULL){
		if (strcmp(elemento->Value(), "circle") == 0){
			Circulo c;
			c.leitura(elemento);
			c.setYcentro(j.getAltura() - c.getYcentro());
			if (c.getId() == "Inimigo")
				Inimigos.push_back(c);
			else if (c.getId() == "Pista")
				Pista.push_back(c);
			else if (c.getId() == "Jogador")
				Jogador = c;
		}
		elemento = elemento->NextSiblingElement();
	}

// Informações do retangulo:
	XMLElement* retangulo = svg->FirstChildElement("rect");
	r.leitura(retangulo);
	r.setYcentro(j.getAltura() - r.getYcentro());

// Informações da janela:
	for (unsigned int i = 0; i < Pista.size();i++){
		if (Pista[i].getCorR() == 0 && Pista[i].getCorG() == 0 && Pista[i].getCorB() == 1){
			j.setLargura(2*(Pista[i].getRaio()));
			j.setAltura(2*(Pista[i].getRaio()));
		}
	}
	j.setTitulo(nome);
	j.setCorR(1);
	j.setCorG(1);
	j.setCorB(1);
}

// Função printa na tela:
void display(void) {
	// limpar todos os pixels
	glClear(GL_COLOR_BUFFER_BIT);

// Desenha pista
	for (unsigned int i = 0; i < Pista.size(); i++)
			Pista[i].desenhaCirculo();

// Desenha retangulo
	r.desenhaRetangulo();

// Desenha inimigos
	for (unsigned int i = 0; i < Inimigos.size(); i++)
			Inimigos[i].desenhaCirculo();

// Desenha Jogador
	Jogador.desenhaCirculo();

	glutSwapBuffers();
}

void keyUP(unsigned char key,int x, int y){
	switch(key){
		case 'w':
		case 'W':
			keyStatus[key] = 0;
			break;
		case 's':
		case 'S':
			keyStatus[key] = 0;
			break;
		case 'a':
		case 'A':
			keyStatus[key] = 0;
			break;
		case 'd':
		case 'D':
			keyStatus[key] = 0;
			break;
	}

}

void keyPress(unsigned char key,int x, int y){
	switch(key){
		case 'w':
		case 'W':
			keyStatus[key] = 1;
			break;
		case 's':
		case 'S':
			keyStatus[key] = 1;
			break;
		case 'a':
		case 'A':
			keyStatus[key] = 1;
			break;
		case 'd':
		case 'D':
			keyStatus[key] = 1;
			break;
	}

}

// Função para estabelecer a camera e as coisas inicias da janela:
void init(void) {
	// selecionar cor de fundo (preto)
	glClearColor((GLfloat)j.getCorR(),(GLfloat)j.getCorG(),(GLfloat)j.getCorB(),0.0);

	// inicializar sistema de viz
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float xcentro = 0,ycentro = 0,raio = 0;
	// Captura informações da pista azul para acertar a camera:
	for (unsigned int i = 0; i < Pista.size(); i++){
		if (Pista[i].getCorR() == 0 && Pista[i].getCorG() == 0 && Pista[i].getCorB() == 1){
			xcentro = Pista[i].getXcentro();
			ycentro = Pista[i].getYcentro();
			raio = Pista[i].getRaio();
		}
	}
	glOrtho((GLfloat)(xcentro - raio),(GLfloat)(xcentro + raio),(GLfloat)(ycentro - raio),(GLfloat)(ycentro + raio),-1.0,1.0);
}

void idle(void){
	float xantigo = 0,yantigo = 0;

	if (keyStatus['w'] || keyStatus['W']){
		yantigo = Jogador.getYcentro();
		Jogador.setYcentro(Jogador.getYcentro() + velCarro);
		for (unsigned int i = 0; i < Inimigos.size(); i++) {
			if (Jogador.dentroPista(Pista)){
				if (Jogador.verificaBordas(Inimigos[i]))
					Jogador.setYcentro(yantigo);
			}else{
				Jogador.setYcentro(yantigo);
			}
		}
	}if (keyStatus['s'] || keyStatus['S']){
		yantigo = Jogador.getYcentro();
		Jogador.setYcentro(Jogador.getYcentro() - velCarro);
		for (unsigned int i = 0; i < Inimigos.size(); i++) {
			if (Jogador.dentroPista(Pista)){
				if (Jogador.verificaBordas(Inimigos[i]))
					Jogador.setYcentro(yantigo);
			}else{
				Jogador.setYcentro(yantigo);
			}
		}
	}if (keyStatus['a'] || keyStatus['A']){
		xantigo = Jogador.getXcentro();
		Jogador.setXcentro(Jogador.getXcentro() - velCarro);
		for (unsigned int i = 0; i < Inimigos.size(); i++) {
			if (Jogador.dentroPista(Pista)){
				if (Jogador.verificaBordas(Inimigos[i]))
					Jogador.setXcentro(xantigo);
			}else{
				Jogador.setXcentro(xantigo);
			}
		}
	}if (keyStatus['d'] || keyStatus['D']){
		xantigo = Jogador.getXcentro();
		Jogador.setXcentro(Jogador.getXcentro() + velCarro);
		for (unsigned int i = 0; i < Inimigos.size(); i++) {
			if (Jogador.dentroPista(Pista)){
				if (Jogador.verificaBordas(Inimigos[i]))
					Jogador.setXcentro(xantigo);
			}else{
				Jogador.setXcentro(xantigo);
			}
		}
	}

	glutPostRedisplay();
}
