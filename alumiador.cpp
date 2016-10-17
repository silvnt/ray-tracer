#include "alumiador.hpp"

Alumiador::Alumiador(vec pPosition, vec pIntense){
	ponto = pPosition;
	intensidade = pIntense;
}

vec Alumiador::getPosition(){ return ponto; }
vec Alumiador::getIntense(){ return intensidade; }
