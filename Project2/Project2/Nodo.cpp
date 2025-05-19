#include "Nodo.h"
// utilizada para manejar todos los contactos y usuarios en la aplicacion 
Nodo::Nodo(Persona^ nuevaPersona) :
	persona(nuevaPersona),
	next(nullptr)
{}

Nodo::Nodo()
{
}
