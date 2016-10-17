#ifndef _ALUMIADOR_HPP_
#define _ALUMIADOR_HPP_

#include <armadillo>

using namespace arma;

class Alumiador{
public:
	Alumiador(vec, vec);
	vec getPosition();
	vec getIntense();
private:
	vec ponto;
	vec intensidade;
};

#endif

