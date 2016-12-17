#include <iostream>
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

class ObjRend{

	private:
		vector <int> vertexInd, uvInd, normalInd; //caracteristicas das faces
		vector <mat> vertices; // pontos dos vertices
		vector <mat> textures; // texturas (????)
		vector <mat> normals; // normais
	public:
		void setVert(mat a){
			this->vertices.push_back(a);
		}

		void setText(mat b){
			this->textures.push_back(b);
		}
		
		void setNormals(mat c){
			this->normals.push_back(c);
		}

		void setVertex(int a, int b, int c){
			this->vertexInd.push_back(a);
			this->uvInd.push_back(b);
			this->normalInd.push_back(c);
		}

		int getSize(){
			return this->vertexInd.size();
		}
		
};

int main(int argc, char **argv){

	FILE *arq;
	arq = fopen(argv[1],"r");

	mat vert;
	mat text;
	mat normal;
	int res;

	if(arq == NULL){
		cout << "passe o arquivo como parâmetro" << endl;
		return 1;
	}

	ObjRend *obj = new ObjRend;

	while(1){
		
	char line[128];

	res = fscanf(arq, "%s",line);

	if(res == EOF){break; }

	if(strcmp(line,"v") == 0){
		float vNew1,vNew2,vNew3;
		
		fscanf(arq,"%f %f %f\n",&vNew1,&vNew2,&vNew3);

		vert << vNew1 << endr << vNew2 << endr << vNew3 << endr;

		obj->setVert(vert);
			
	
	} else if(strcmp(line,"vt") == 0){
		
		float vtNew1, vtNew2;

		fscanf(arq,"%f %f\n",&vtNew1,&vtNew2);

		text << vtNew1 << endr << vtNew2 << endr << 1 << endr;

		obj->setText(text);

	}else if(strcmp(line,"vn") == 0){

		float vnNew1,vnNew2,vnNew3;
		
		fscanf(arq,"%f %f %f\n",&vnNew1,&vnNew2,&vnNew3);

		normal << vnNew1 << endr << vnNew2 << endr << vnNew3 << endr;

		obj->setNormals(normal);

	}else if(strcmp(line,"f") == 0){
		
		string vertex1, vertex2, vertex3;
		
		int vertexIndex[3], uvIndex[3], normalIndex[3];

		fscanf(arq, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], 			&normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

		obj->setVertex(vertexIndex[0], uvIndex[0], normalIndex[0]);
		obj->setVertex(vertexIndex[1], uvIndex[1], normalIndex[1]);
		obj->setVertex(vertexIndex[2], uvIndex[2], normalIndex[2]);

	}
	/*
	for(int i = 0; vertexind < obj.getSize(); i++){
	
	}
	*/			
}





























	
}
