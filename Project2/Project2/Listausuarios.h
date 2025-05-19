#pragma once
#include "Nodo.h"
#include "Persona.h"

using namespace System::Windows::Forms;
using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Threading;
using namespace System::Runtime::Serialization::Formatters::Binary;
using namespace System::Threading;
public ref class Listausuarios
{
private: 
	// Se declara la lista de personas, todos los usuarios existentes 
	Nodo^ ListaPersonas = nullptr;
	// Estos dos objetos sirven para sincronizar el acceso a recursos compartidos (por ejemplo, lectura/escritura de un archivo) en entornos multihilo. 
	//https://stackoverflow.com/search?q=C%2B%2B%2FCLI+initonly&s=5983a748-ebb2-421a-b8fb-599318934c2f 
	static Object^ fileLock = gcnew Object();
	static initonly String^ DATA_FILE;

	
public: 
	static Listausuarios()
	{
		DATA_FILE = Path::Combine(Application::StartupPath, "usuarios.dat");
	}
	// Metodos para agregar, buscar y eliminar una persona (Busqueda binaria)
	Listausuarios(); 
	Listausuarios(Nodo^listapersonas); 
	List<Persona^>^ GetAllUsuarios();
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

