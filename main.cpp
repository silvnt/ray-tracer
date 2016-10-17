#include "imagem.hpp"

int main(int argc, char **argv){
	if(argc != 4){
		printf("Insira valores de largura e altura da imagem (pixels). Insira Arquivo .obj\n");
		return 1;
	}
	
	Imagem *img = new Imagem(atoi(argv[2]), atoi(argv[1]));
	
	// Objetos
	
	ObjArq *obj = new ObjArq(argv[3]);
	
	/*vec centroEsfera = {0.0, 0.0, 5.0};
	uvec corEsfera = {255,255,255};
	uvec corSpecEsfera = {255,255,255};
	Objeto *esfera = new Esfera(centroEsfera, 3.0, corEsfera, corSpecEsfera, 300);
	
	vec pTA3={1.0, -1.0, 1.0}, pTB3={1.0, 0.0, 1.0}, pTC3={-1.0, 0.0, 1.0};
	uvec corTriang3 = {255,255,255};
	uvec corSpecTriang3 = {255,255,255};
	Objeto *triangulo3 = new Triangulo(pTA3, pTB3, pTC3, corTriang3, corSpecTriang3, 50);*/
	
	vector<Objeto*> formas;
	obj->inserir(&formas);
	
	//formas.push_back(esfera);
	//formas.push_back(triangulo3);
	
	// Luminares
	
	vec positLuz= {0.0, 0.0, 0.0};
	vec iLuz = {0, 0, 1};
	Alumiador *luz1 = new Alumiador(positLuz, iLuz);
	
	/*vec positLuz2= {5.0, 5.0, 5.0};
	vec iLuz2 = {0, 0, 1};
	Alumiador *luz2 = new Alumiador(positLuz2, iLuz2);
	
	vec positLuz3= {-5.0, -5.0, 5.0};
	vec iLuz3 = {1, 0, 0};
	Alumiador *luz3 = new Alumiador(positLuz3, iLuz3);*/
	
	vector<Alumiador*> luminares;
	luminares.push_back(luz1);
	//luminares.push_back(luz2);
	//luminares.push_back(luz3);
	
	//Renderização
	
	img->renderizar(&formas, &luminares);
	
	return 0;
}


