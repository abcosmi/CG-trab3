#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "funcoes_opengl.h"
#include "circulo.h"
#include "janela.h"
#include "retangulo.h"
#include "tinyxml2.h"


using namespace tinyxml2;

Janela j;
std::vector<Circulo> Inimigos;
std::vector<Circulo> Pista;
Circulo Jogador;
Retangulo r;


int main(int argc,char **argv){
  if (argc < 2){
    std::cout << "Digite a localizacao do arquivo config.xml. Exemplo:\n\t ./trabalhocg ../teste/\n";
    std::exit(1);
  }

  std::string caminhoXML = argv[1];
  caminhoXML = caminhoXML + "config.xml";

  leituraXML(caminhoXML);

  // OpenGL:
  glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(j.getLargura(),j.getAltura());
	glutInitWindowPosition(100,100);
	glutCreateWindow(j.getTitulo().c_str());
	init();
	glutDisplayFunc(display);
  glutKeyboardFunc(keyPress);
  glutKeyboardUpFunc(keyUP);
	glutIdleFunc(idle);
	glutMainLoop();

  return 0;
}
