#ifndef _OBJETO_HPP_
#define _OBJETO_HPP_

#include <armadillo>
#include <math.h>

using namespace arma;

class Objeto{
public:
	virtual double tVal(vec) = 0;
	virtual vec getNormal(vec, double) = 0;
	virtual uvec getColor() = 0;
};

class Esfera : public Objeto{
public:
	Esfera(vec, double, uvec={0,0,0});
	double tVal(vec);
	vec getNormal(vec, double);
	uvec getColor();
private:
	vec centro;
	double raio;
	uvec cor;
};

class Triangulo : public Objeto{
public:
	Triangulo(vec, vec, vec, uvec={0,0,0});
	double tVal(vec);
	vec getNormal(vec, double);
	uvec getColor();
private:
	double getBeta(vec);
	double getGama(vec);
	double getA(vec);
	vec a, b, c;
	uvec cor;
};

#endif
