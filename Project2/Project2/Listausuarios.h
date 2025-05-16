#pragma once
#include "Nodo.h"
#include "Persona.h"
public ref class Listausuarios
{
private: 
	Nodo^ ListaPersonas = nullptr; 

public: 
	Listausuarios(); 
	Listausuarios(Nodo^listapersonas); 
	Nodo^ BuscarPersona(String^ Dato, int criterio); 
	void Add(Persona^ usuarioNuevo); 
	Nodo^ obtenerMitad(Nodo^ inicio, Nodo^ final);
	bool Isempty(); 
	void GuardarEnArchivo();
	void eliminar(String^ usuario); 
	void CargarDesdeArchivo();
	void agregarList(ListBox^ lista);
	void OrdenarPorUsername();
};

