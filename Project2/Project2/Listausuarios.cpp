#include "Listausuarios.h"
using namespace System::IO;
using namespace System::Runtime::Serialization::Formatters::Binary;
using namespace System::Collections::Generic;
#using <System.Runtime.Serialization.Formatters.Soap.dll>

Listausuarios::Listausuarios()
{
	this->ListaPersonas = nullptr;
}


Listausuarios::Listausuarios(Nodo^ listapersonas)
{
	this->ListaPersonas = listapersonas;
}


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

void Listausuarios::Add(Persona^ usuarioNuevo)
{
	Nodo^ nuevo = gcnew Nodo(usuarioNuevo);
	nuevo->next = ListaPersonas;
	ListaPersonas = nuevo;
}

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
bool Listausuarios::Isempty()
{
	return ListaPersonas == nullptr;
}
void Listausuarios::GuardarEnArchivo() {
	FileStream^ fs = gcnew FileStream("usuarios.dat", FileMode::Create);
	BinaryFormatter^ bf = gcnew BinaryFormatter();

	List<Persona^>^ personas = gcnew List<Persona^>();
	Nodo^ actual = ListaPersonas;

	while (actual != nullptr) {
		actual->persona->PrepararParaGuardar();
		personas->Add(actual->persona);
		actual = actual->next;
	}

	bf->Serialize(fs, personas);
	fs->Close();
}


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

void Listausuarios::CargarDesdeArchivo() {
	if (!File::Exists("usuarios.dat")) return;

	FileStream^ fs = gcnew FileStream("usuarios.dat", FileMode::Open);
	BinaryFormatter^ bf = gcnew BinaryFormatter();

	List<Persona^>^ personas = dynamic_cast<List<Persona^>^>(bf->Deserialize(fs));
	fs->Close();

	ListaPersonas = nullptr;

	for each (Persona ^ p in personas) {
		p->RestaurarDesdeCarga(); // Importante
		Add(p);
	}
}

void Listausuarios::agregarList(ListBox^ lista)
{
	lista->Items->Clear();
	Nodo^ actual = ListaPersonas;
	while (actual != nullptr) {
		lista->Items->Add(actual->persona); 
		actual = actual->next;
	}
}


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

