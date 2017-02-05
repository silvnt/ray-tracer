#ifndef _OBJETO_HPP_
#define _OBJETO_HPP_

#include "alumiador.hpp"
#include <math.h>

class Objeto{
public:
	virtual double tVal(vec, vec) = 0;
	virtual vec getNormal(vec, vec, double) = 0;
	virtual uvec getDifuseColor() = 0;
	virtual uvec getSpecColor() = 0;
	virtual double getShineness() = 0;
};

class Esfera : public Objeto{
public:
	Esfera(vec, double, uvec={255,255,255}, uvec={255,255,255}, double = 1.0);
	double tVal(vec, vec);
	vec getNormal(vec, vec, double);
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
	Triangulo(vec, vec, vec, uvec={200,200,200}, uvec={200,200,200}, double = 20.0, vec={0.0, 0.0, 0.0}, vec={0.0, 0.0, 0.0}, vec={0.0, 0.0, 0.0});
	double tVal(vec, vec);
	vec getNormal(vec, vec, double);
	uvec getDifuseColor();
	uvec getSpecColor();
	double getShineness();
private:
	double getBeta(vec, vec);
	double getGama(vec, vec);
	double getA(vec);
	vec a, b, c;
	vec nA, nB, nC;
	uvec cor;
	uvec specCor;
	double shineness;
};

#endif
