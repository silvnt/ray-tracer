#ifndef _OBJETO_HPP_
#define _OBJETO_HPP_

#include "alumiador.hpp"
#include <math.h>

class Objeto{
public:
	virtual double tVal(vec) = 0;
	virtual vec getNormal(vec, double) = 0;
	virtual uvec getDifuseColor() = 0;
	virtual uvec getSpecColor() = 0;
	virtual double getShineness() = 0;
};

class Esfera : public Objeto{
public:
	Esfera(vec, double, uvec={255,255,255}, uvec={255,255,255}, double = 1.1);
	double tVal(vec);
	vec getNormal(vec, double);
	uvec getDifuseColor();
	uvec getSpecColor();
	double getShineness();
private:
	vec centro;
	double raio;
	uvec cor;
	uvec specCor;
	double shineness;
};

class Triangulo : public Objeto{
public:
	Triangulo(vec, vec, vec, uvec={255,255,255}, uvec={255,255,255}, double = 1.1);
	double tVal(vec);
	vec getNormal(vec, double);
	uvec getDifuseColor();
	uvec getSpecColor();
	double getShineness();
private:
	double getBeta(vec);
	double getGama(vec);
	double getA(vec);
	vec a, b, c;
	uvec cor;
	uvec specCor;
	double shineness;
};

#endif
