#using <mscorlib.dll>
#include "Listausuarios.h"  
#include "Nodo.h"
#include "Persona.h"
using namespace System;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Runtime::Serialization::Formatters::Binary;
using namespace System::Collections::Generic;
// Constructor vacio 
Listausuarios::Listausuarios()
{
	this->ListaPersonas = nullptr;
	
}
// Cargado 
Listausuarios::Listausuarios(Nodo^ listapersonas)
{
	this->ListaPersonas = listapersonas;
}
// Se mandan todos los usuarios donde se necesite 
List<Persona^>^ Listausuarios::GetAllUsuarios() {
	auto resultado = gcnew List<Persona^>();
	for (Nodo^ cur = ListaPersonas; cur != nullptr; cur = cur->next) {
		if (cur->persona != nullptr)
			resultado->Add(cur->persona);
	}
	return resultado;
}
// Busqueda binaria 
Nodo^ Listausuarios::BuscarPersona(String^ Dato, int criterio)
{
	if (ListaPersonas == nullptr) return nullptr;
	Nodo^ inicio = ListaPersonas;
	Nodo^ fin = nullptr;
	Dato = Dato->Trim();
	while (inicio != fin) {
		Nodo^ medio = obtenerMitad(inicio, fin);
		if (medio == nullptr) break;
		String^ keyValue;
		if (criterio == 1) {
			keyValue = medio->persona->GetNombreUsuario()->Trim();
		}
		else {
			keyValue = medio->persona->GetCorreo()->Trim();
		}
		int comparacion = keyValue->CompareTo(Dato);
		if (comparacion == 0) {
			return medio; 
		}
		else if (comparacion < 0) {
			inicio = medio->next; 
		}
		else {
			fin = medio; 
		}
	}
	return nullptr; 
}
// Agregar un usuario en una lista enlazada (Al frente)
void Listausuarios::Add(Persona^ usuarioNuevo)
{
	Nodo^ nuevo = gcnew Nodo(usuarioNuevo);
	nuevo->next = ListaPersonas;
	ListaPersonas = nuevo;
}
// Metodo para la busqueda binaria precisamente encontrar la mitad de la lista 
Nodo^ Listausuarios::obtenerMitad(Nodo^ inicio, Nodo^ fin)
{
	if (inicio == nullptr) return nullptr;
	Nodo^ lento = inicio;
	Nodo^ rapido = inicio;
	while (rapido != nullptr && rapido != fin && rapido->next != nullptr && rapido->next != fin) {
		rapido = rapido->next->next;
		if (rapido != nullptr && rapido != fin)
			lento = lento->next;
	}
	return lento;

}
// validar si la lista esta vacia o no 
bool Listausuarios::Isempty()
{
	return ListaPersonas == nullptr;
}


void Listausuarios::GuardarEnArchivo() {
	Monitor::Enter(fileLock);
	try {
		// Invocamos el metodo en persona para prepara cada usuario y si prepara 
		auto personas = gcnew List<Persona^>();
		for (Nodo^ cur = ListaPersonas; cur != nullptr; cur = cur->next)
			if (cur->persona != nullptr) {
				cur->persona->PrepararParaGuardar();
				personas->Add(cur->persona);
			}

		// Abrimos el stream y se vacia, todo lo que estaba dentro se vacia antes de volver a escribir 
		FileStream^ fs = gcnew FileStream(DATA_FILE,FileMode::OpenOrCreate,FileAccess::ReadWrite,FileShare::ReadWrite | FileShare::Delete);
		fs->SetLength(0);

		// Serializamos, convierte las personas a bytes y lo escribe en el archivo 
		auto bf = gcnew BinaryFormatter();
		bf->Serialize(fs, personas);
		fs->Flush();
		fs->Close();
	}
	catch (Exception^ ex) {
		MessageBox::Show("Error guardando usuarios.dat:\n" + ex->Message,
			"Error",
			MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	finally {
		Monitor::Exit(fileLock);
	}
}
void Listausuarios::CargarDesdeArchivo() {
	// 1) Si no existe el fichero(usuarios.dat), o existe pero esta vacio, 
	//    arrancamos con lista vacia.
	FileInfo^ fi = gcnew FileInfo(DATA_FILE);
	if (!fi->Exists || fi->Length == 0) {
		ListaPersonas = nullptr;
		return;
	}

	Monitor::Enter(fileLock);
	try {
		// Deserializamos 
		FileStream^ fs = gcnew FileStream(DATA_FILE,FileMode::Open,FileAccess::Read,FileShare::ReadWrite | FileShare::Delete);
		auto bf = gcnew BinaryFormatter();
		auto loaded = safe_cast<List<Persona^>^>(bf->Deserialize(fs));
		fs->Close();

		// Reconstruimos la lista en memoria
		ListaPersonas = nullptr;
		for each (Persona ^ p in loaded) {
			Nodo^ nodo = gcnew Nodo(p);
			nodo->next = ListaPersonas;
			ListaPersonas = nodo;
		}

		// 4) Ordenamos y restauramos
		OrdenarPorUsername();
		for (Nodo^ cur = ListaPersonas; cur != nullptr; cur = cur->next)
			cur->persona->RestaurarDesdeCarga(this);
	}
	catch (SerializationException^ sx) {
		// si el stream esta corrupto o vacio
		// descartamos y arrancamos limpio
		ListaPersonas = nullptr;
	}
	catch (Exception^ ex) {
		MessageBox::Show("Error cargando usuarios.dat:\n" + ex->Message,
			"Error",
			MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	finally {
		Monitor::Exit(fileLock);
	}
}
// Metodo sencillo de eliminar un usuario 
void Listausuarios::eliminar(String^ usuario)
{
	usuario = usuario->Trim()->ToLower();
	Nodo^ actual = ListaPersonas;
	Nodo^ anterior = nullptr;

	while (actual != nullptr) {
		String^ nombreUsuario = actual->persona->GetNombreUsuario()->Trim()->ToLower();

		if (nombreUsuario == usuario) {
			if (anterior == nullptr) {
				ListaPersonas = actual->next;
			}
			else {
				anterior->next = actual->next;
			}

			delete actual;
			return;
		}

		anterior = actual;
		actual = actual->next;
	}
}

// Agregar usuarios a una listbox (mas facil hacerlo en la clase)
void Listausuarios::agregarList(ListBox^ lista)
{
	lista->Items->Clear();
	Nodo^ actual = ListaPersonas;
	while (actual != nullptr) {
		lista->Items->Add(actual->persona); 
		actual = actual->next;
	}
}

// Implemente este ordenar usuario por bubble sort 
void Listausuarios::OrdenarPorUsername()
{
	if (ListaPersonas == nullptr) return;

	bool intercambiado;

	do {
		intercambiado = false;
		Nodo^ actual = ListaPersonas;

		while (actual->next != nullptr)
		{
			String^ a = actual->persona->GetNombreUsuario();
			String^ b = actual->next->persona->GetNombreUsuario();

			if (String::Compare(a, b, StringComparison::OrdinalIgnoreCase) > 0)
			{
				Persona^ temp = actual->persona;
				actual->persona = actual->next->persona;
				actual->next->persona = temp;
				intercambiado = true;
			}

			actual = actual->next;
		}

	} while (intercambiado);
}

