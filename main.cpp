#include "imagem.hpp"

int main(int argc, char **argv){
	if(argc != 4){
		printf("Insira valores de largura e altura da imagem (pixels). Insira Arquivo .obj\n");
		return 1;
	}
	
	Imagem *img = new Imagem(atoi(argv[2]), atoi(argv[1]));
	FILE *arq = fopen(argv[3], "r");
	
	ObjArq *obj = new ObjArq(arq);
	
	vec centroEsfera = {-3.0, 3.0, 5.0};
	uvec corEsfera = {0,255,0};
	Objeto *esfera = new Esfera(centroEsfera, 3.0, corEsfera);
	
	vec pTA3={3.0, -3.0, 1.0}, pTB3={3.0, 0.0, 2.0}, pTC3={-3.0, 0.0, 3.0};
	uvec corTriang3 = {0,0,0};
	Objeto *triangulo3 = new Triangulo(pTA3, pTB3, pTC3, corTriang3);
	
	vector<Objeto*> formas;
	obj->inserir(&formas);
	formas.push_back(esfera);
	formas.push_back(triangulo3);
	
	img->renderizar(&formas);
	
	return 0;
}


