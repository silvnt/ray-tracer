#include "objArq.hpp"

ObjArq::ObjArq(char *arqName){
	
	FILE *arq;
	arq = fopen(arqName,"r");
	int res;
	
	while(1){
		char line[128];
		
		res = fscanf(arq, "%s",line);
		
		if(res == EOF){ break; }
		
		if(strcmp(line,"v") == 0){
			double vNew1,vNew2,vNew3;
		
			res = fscanf(arq,"%lf %lf %lf\n",&vNew1,&vNew2,&vNew3);
			
			vertices.push_back(vNew1);
			vertices.push_back(vNew2);
			vertices.push_back(vNew3);
			
		}else if(strcmp(line,"vn") == 0){
			double vnNew1,vnNew2,vnNew3;
		
			res = fscanf(arq,"%lf %lf %lf\n",&vnNew1,&vnNew2,&vnNew3);
			
			normais.push_back(vnNew1);
			normais.push_back(vnNew2);
			normais.push_back(vnNew3);
			
		}else if(strcmp(line, "f") == 0){
			int vertexIndex[3], normalIndex[3];
			
			res = fscanf(arq, "%d//%d %d//%d %d//%d\n", 
					&vertexIndex[0], &normalIndex[0], &vertexIndex[1], 
					&normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			
			ligacoesVert.push_back(vertexIndex[0]);
			ligacoesVert.push_back(vertexIndex[1]);
			ligacoesVert.push_back(vertexIndex[2]);
			
			ligacoesNorm.push_back(normalIndex[0]);
			ligacoesNorm.push_back(normalIndex[1]);
			ligacoesNorm.push_back(normalIndex[2]);
			
			positObjVert.back() += 3;
			
		}else if(strcmp(line, "mtllib") == 0){
			res = fscanf(arq, "%s", mtlArqName);
			
		}else if(strcmp(line, "o") == 0){
			
			positObjVert.push_back(0);
			
		}
	}
	
	fclose(arq);
}

void ObjArq::readMtl(){
	FILE *mtlArq;
	mtlArq = fopen(mtlArqName, "r");
	
	int res;
			
		while(1){
			char line[128];
			res = fscanf(mtlArq, "%s", line);

			if(res == EOF){ break; }
			
			if(strcmp(line, "Ns") == 0){
				double sNew;
		
				res = fscanf(mtlArq,"%lf\n",&sNew);
				
				shinenessIntensidades.push_back(sNew);
				
			}else if(strcmp(line, "Kd") == 0){
				double dNew1,dNew2,dNew3;
		
				res = fscanf(mtlArq,"%lf %lf %lf\n",&dNew1,&dNew2,&dNew3);
				
				uvec newDifuseColor = {(unsigned int)(dNew1 * 255.0), (unsigned int)(dNew2 * 255.0), (unsigned int)(dNew3 * 255.0)};
				
				difusaCores.push_back(newDifuseColor);
				
			}else if(strcmp(line, "Ks") == 0){
				double sNew1,sNew2,sNew3;
		
				res = fscanf(mtlArq,"%lf %lf %lf\n",&sNew1,&sNew2,&sNew3);
				
				uvec newSpecularColor = {(unsigned int)(sNew1 * 255.0), (unsigned int)(sNew2 * 255.0), (unsigned int)(sNew3 * 255.0)};
				
				especularCores.push_back(newSpecularColor);
				
			}	
		}
		
	fclose(mtlArq);
}

void ObjArq::inserir(vector<Objeto*> *v){
	int i = -1, size = ligacoesVert.size();
	int colorIndex = -1;
	
	if(mtlArqName != NULL){ readMtl(); colorIndex = 0; }
	
	if(!normais.empty()){
		while(i < size-1){
			Objeto *novo;
		
			int posicV;
			int posicN;
			
			i++;
			posicV = (ligacoesVert[i]-1) * 3;
			posicN = (ligacoesNorm[i]-1) * 3;
			vec p1 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
			vec n1 = { normais[posicN], normais[posicN+1], normais[posicN+2] };
				
			i++;
			posicV = (ligacoesVert[i]-1) * 3;
			posicN = (ligacoesNorm[i]-1) * 3;
			vec p2 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
			vec n2 = { normais[posicN], normais[posicN+1], normais[posicN+2] };
					
			i++;
			posicV = (ligacoesVert[i]-1) * 3;
			posicN = (ligacoesNorm[i]-1) * 3;
			vec p3 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
			vec n3 = { normais[posicN], normais[posicN+1], normais[posicN+2] };
								
			if(colorIndex != -1){				
				novo = new Triangulo(p1, p2, p3, difusaCores[colorIndex], especularCores[colorIndex], shinenessIntensidades[colorIndex], n1, n2, n3);
			}else{
				uvec color = {200, 200, 200};
				uvec specColor = {200, 200, 200};
				double shineness = 20.0;
				novo = new Triangulo(p1, p2, p3, color, specColor, shineness, n1, n2, n3);
			}
					
			v->push_back(novo);
			
			if(i+1 == positObjVert[colorIndex]){ colorIndex++; }
		}
		
	}else{
		while(i < size-1){
			Objeto *novo;
			int posicV;
			
			i++; posicV = (ligacoesVert[i]-1) * 3;
			vec p1 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
		
			i++; posicV = (ligacoesVert[i]-1) * 3;
			vec p2 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
		
			i++; posicV = (ligacoesVert[i]-1) * 3;
			vec p3 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
		
			if(colorIndex != -1){
				novo = new Triangulo(p1, p2, p3, difusaCores[colorIndex], especularCores[colorIndex], shinenessIntensidades[colorIndex]);
					
			}else{
				uvec color = {200, 200, 200};
				uvec specColor = {200, 200, 200};
				double shineness = 20.0;
				novo = new Triangulo(p1, p2, p3, color, specColor, shineness);
					
			}
		
			v->push_back(novo);
			
			if(i+1 == positObjVert[colorIndex]){ colorIndex++; }
		}
	}
	
	
}
