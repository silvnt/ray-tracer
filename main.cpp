#include "imagem.hpp"

int main(int argc, char **argv){
	if(argc != 2){
		printf("Insira apenas um arquivo .ray para renderizar\n");
		return 1;
	}
	
	FILE *arqRay = fopen(argv[1], "r");
	char testLine[128];
	int res = fscanf(arqRay, "%s", testLine);
	
	if(strcmp(testLine, "_CONF_RAY_") != 0){
		printf("Este não é um arquivo válido.\n");
		return 2;
	}
	
	vec centroProj = {0.0, 0.0, 0.0};
	int resLargura = 800;
	int resAltura = 600;
	char imgNome[128];

	
	vector<Objeto*> formas;
	vector<Alumiador*> luminares;

	
	while(1){
		char line[128];
		
		res = fscanf(arqRay, "%s", line);
		
		if(res == EOF){ break; }
		
		if(strcmp(line, "_nomeImg") == 0){
			res = fscanf(arqRay, "%s", imgNome);
			
		}else if(strcmp(line, "_resolucao") == 0){
			res = fscanf(arqRay, "%d %d", &resLargura, &resAltura);
			
		}else if(strcmp(line, "_centroProjetivo") == 0){
			double x, y, z;
			res = fscanf(arqRay, "%lf %lf %lf", &x, &y, &z);
			centroProj = {x, y, z};
			
		}else if(strcmp(line, "_inserir") == 0){
			char line2[128];
			res = fscanf(arqRay, "%s", line2);
			
			if(strcmp(line2, "esfera") == 0){
				vec centroEsfera = {0.0, 0.0, 3.0};
				uvec corEsfera = {128,128,128};
				uvec corSpecEsfera = {128,128,128};
				double raio = 1.0;
				double shineness = 2.0;
				
				
				while(1){
					char line3[128];
					res = fscanf(arqRay, "%s", line3);
					
					if(strcmp(line3, ".centro") == 0){
						double x, y, z;
						res = fscanf(arqRay, "%lf %lf %lf", &x, &y, &z);
						centroEsfera = {x, y, z};
			
					}else if(strcmp(line3, ".raio") == 0){
						res = fscanf(arqRay, "%lf", &raio);
						
					}else if(strcmp(line3, ".corDifusa") == 0){
						unsigned int x, y, z;
						res = fscanf(arqRay, "%d %d %d", &x, &y, &z);
						corEsfera = {x, y, z};
						
					}else if(strcmp(line3, ".corEspecular") == 0){
						unsigned int x, y, z;
						res = fscanf(arqRay, "%d %d %d", &x, &y, &z);
						corSpecEsfera = {x, y, z};
						
					}else if(strcmp(line3, ".shineness") == 0){
						res = fscanf(arqRay, "%lf", &shineness);
						
					}else if(strcmp(line3, "_") == 0){ break; }
					
				}
				
				Objeto *esfera = new Esfera(centroEsfera, raio, corEsfera, corSpecEsfera, shineness);
				formas.push_back(esfera);
				
			}else if(strcmp(line2, "triangulo") == 0){
				vec pTA3={1.0, -1.0, 1.0}, pTB3={0.0, 1.0, 1.0}, pTC3={-1.0, 0.0, 1.0};
				uvec corTriang3 = {128,128,128};
				uvec corSpecTriang3 = {128,128,128};
				double shineness = 2.0;
				
				while(1){
					char line3[128];
					res = fscanf(arqRay, "%s", line3);
					
					if(strcmp(line3, ".vertice1") == 0){
						double x, y, z;
						res = fscanf(arqRay, "%lf %lf %lf", &x, &y, &z);
						
						pTA3 = {x, y, z};
						
					}else if(strcmp(line3, ".vertice2") == 0){
						double x, y, z;
						res = fscanf(arqRay, "%lf %lf %lf", &x, &y, &z);
						
						pTB3 = {x, y, z};
					
					}else if(strcmp(line3, ".vertice3") == 0){
						double x, y, z;
						res = fscanf(arqRay, "%lf %lf %lf", &x, &y, &z);
						
						pTC3 = {x, y, z};
						
					}else if(strcmp(line3, ".corDifusa") == 0){
						unsigned int x, y, z;
						res = fscanf(arqRay, "%d %d %d", &x, &y, &z);
						
						corTriang3 = {x, y, z};
						
					}else if(strcmp(line3, ".corEspecular") == 0){
						unsigned int x, y, z;
						res = fscanf(arqRay, "%d %d %d", &x, &y, &z);
						
						corSpecTriang3 = {x, y, z};
						
					}else if(strcmp(line3, ".shineness") == 0){
						res = fscanf(arqRay, "%lf", &shineness);
						
						
					}else if(strcmp(line3, "_") == 0){ break; }
					
				}
				
				Objeto *triangulo3 = new Triangulo(pTA3, pTB3, pTC3, corTriang3, corSpecTriang3, shineness);
				formas.push_back(triangulo3);
				
			}else if(strcmp(line2, "obj") == 0){
				char line3[128];
				res = fscanf(arqRay, "%s", line3);
				
				ObjArq *obj = new ObjArq(line3);
				obj->inserir(&formas);
				
			
			}else if(strcmp(line2, "luz") == 0){
				vec positLuz= {5.0, 5.0, 0.0};
				vec iLuz = {0.5, 0.5, 0.5};
				
				
				while(1){
					char line3[128];
					res = fscanf(arqRay, "%s", line3);
					
					if(strcmp(line3, ".posicao") == 0){
						double x, y, z;
						res = fscanf(arqRay, "%lf %lf %lf", &x, &y, &z);
						positLuz = {x, y, z};
						
					}else if(strcmp(line3, ".intensidade") == 0){
						double x, y, z;
						res = fscanf(arqRay, "%lf %lf %lf", &x, &y, &z);
						iLuz = {x, y, z};
						
					}else if(strcmp(line3, "_") == 0){ break; }
				
				}
				
				Alumiador *luz = new Alumiador(positLuz, iLuz);
				luminares.push_back(luz);
			
			}else{
				printf("Inserção inválida.\n");
				return 3;
			}
		}
	}
	
	fclose(arqRay);
	
	//Renderização
	
	Imagem *img = new Imagem(resAltura, resLargura, centroProj);
	img->renderizar(&formas, &luminares, imgNome);
	printf("Renderizado com Sucesso!\n");
	
	return 0;
}


