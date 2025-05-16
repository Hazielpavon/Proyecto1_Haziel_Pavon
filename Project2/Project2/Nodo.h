#pragma once
#include "Persona.h"

ref class Persona;

public ref class Nodo
{
public:
	Persona^ persona;
	Nodo^ next = nullptr;
	Nodo(Persona^ nuevaPersona);
	Nodo();

};

