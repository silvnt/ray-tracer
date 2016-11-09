#include "imagem.hpp"

int mdc(int n1, int n2);

Imagem::Imagem(int pAltura, int pLargura){
	altura = pAltura;
	largura = pLargura;
	dpi = mdc(pAltura, pLargura);
}

vec Imagem::projToPix(vec ponto){
	mat K;

	K << dpi*1.0 << 0.0 << largura/2.0 << endr
		<< 0.0 << (-1.0)*dpi << altura/2.0 << endr
		<< 0.0 << 0.0 << 1.0;

	return K*ponto;
}

vec Imagem::pixToProj(vec pixel){
	mat K;

	K << 1.0/dpi << 0.0 << largura/(-2.0*dpi) << endr
		<< 0.0 << (-1.0)/dpi << altura/(2.0*dpi) << endr
		<< 0.0 << 0.0 << 1.0;

	return K*pixel;
}

void Imagem::renderizar(vector<Objeto*> *objetos, vector<Alumiador*> *luminares){
	FILE *img = fopen("imagem.ppm", "w");
	fprintf(img, "P3\n%d %d\n%d\n", largura, altura, 255);
	
	for(int h = 0; h < altura; h++){
		for(int w = 0; w < largura; w++){
			vec pix = { w*1.0, h*1.0, 1.0 };
			vec v = pixToProj(pix);
			
			double tAtual = -1.0;
			Objeto *objetoAtual;
			int size = objetos->size();
			
			for(int i = 0; i < size; i++){
				double t = (*objetos)[i]->tVal(v);
				
				if(t >= 0 && ((t < tAtual) || (tAtual == -1.0))){
					tAtual = t;
					objetoAtual = (*objetos)[i];
				}
			}
				
			if(tAtual == -1.0){
				fprintf(img, "%d %d %d ", 0, 0, 0);
			}else{
				vec normal = normalise(objetoAtual->getNormal(v, tAtual));
				uvec corDifusa = objetoAtual->getDifuseColor();
				uvec corEspecular = objetoAtual->getSpecColor();
				double shineness = objetoAtual->getShineness();
				vec pontoForma = v + v*tAtual;
				
				int lumSize = luminares->size();
				vec realColor = {0, 0, 0};
				
				for(int j = 0; j < lumSize; j++){
					vec l = normalise((*luminares)[j]->getPosition() - pontoForma);
					vec intesLuz = (*luminares)[j]->getIntense();
					vec h = normalise(v + l);
					vec difInt = { corDifusa[0]*intesLuz[0], corDifusa[1]*intesLuz[1], corDifusa[2]*intesLuz[2] };
					vec speInt = { corEspecular[0]*intesLuz[0], corEspecular[1]*intesLuz[1], corEspecular[2]*intesLuz[2] };
					
					//printf("---------------------\n");
					//pontoForma.print();
					//normal.print();
					//l.print();
					//h.print();
					
					realColor += difInt*abs(dot(normal, l)) + speInt*pow(abs(dot(normal, h)), shineness);
					//realColor.print();
				}
				
				if(realColor[0]>255){ realColor[0] = 255; }
				if(realColor[1]>255){ realColor[1] = 255; }
				if(realColor[2]>255){ realColor[2] = 255; }
				
				
				fprintf(img, "%d %d %d ", (int)realColor[0], (int)realColor[1], (int)realColor[2]);
			}
		}
		
		fprintf(img, "\n");
		
	}
	
	fclose(img);
	
}

int mdc(int n1, int n2){
	int z = 1;
	
	while ( z !=0 )
	{
		z = n1 % n2;
		n1 = n2;
		n2 = z;
	}
	
	return n1;
}
