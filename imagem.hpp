#ifndef _IMAGEM_HPP_
#define _IMAGEM_HPP_

#include <algorithm>
#include "objArq.hpp"

class Imagem{
public:
	Imagem(int, int);
	void renderizar(vector<Objeto*> *);
private:
	int altura, largura, dpi;
	vec projToPix(vec);
	vec pixToProj(vec);
};

#endif
