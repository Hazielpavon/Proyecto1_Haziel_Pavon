#pragma once
#include "Persona.h"
#include "Nodo.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::Serialization;

ref class Persona;
ref class Nodo;
[System::Serializable]
public ref class ListaContactos
{
private:
	Nodo^ listaContactos;

public:
	array<String^>^ GetNombresUsuarios();
	ListaContactos();
	Nodo^ buscar(String^ dato, int critero);
	void OrdenarPorUsername();
	void Eliminar(String^ usuario);
	Nodo^ obtenerMitad(Nodo^ inicio, Nodo^ final);
	void agregarList(ListBox^ lista);
	void agregar(Persona^ usuario);

	
};
