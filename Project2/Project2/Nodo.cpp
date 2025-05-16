#include "Nodo.h"
Nodo::Nodo(Persona^ nuevaPersona) :
	persona(nuevaPersona),
	next(nullptr)
{}

Nodo::Nodo()
{
}
