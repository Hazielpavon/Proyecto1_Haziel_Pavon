#include "ListaContactos.h"
using namespace System::Collections::Generic;

array<String^>^ ListaContactos::GetNombresUsuarios() {
	List<String^>^ nombres = gcnew List<String^>();
	Nodo^ actual = listaContactos;
	while (actual != nullptr) {
		if (actual->persona != nullptr)
			nombres->Add(actual->persona->GetNombreUsuario());
		actual = actual->next;
	}
	return nombres->ToArray();
}


ListaContactos::ListaContactos()
{
	this->listaContactos = nullptr;
}

Nodo^ ListaContactos::buscar(String^ Dato, int criterio)
{
	if (listaContactos == nullptr) return nullptr;

	Nodo^ inicio = listaContactos;
	Nodo^ fin = nullptr;
	Dato = Dato->Trim()->ToLower();

	while (inicio != fin) {
		Nodo^ medio = obtenerMitad(inicio, fin);
		if (medio == nullptr) break;

		String^ keyValue;

		if (criterio == 1) {
			keyValue = medio->persona->GetNombreUsuario()->Trim()->ToLower();
		}
		else {
			keyValue = medio->persona->GetCorreo()->Trim()->ToLower();
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
void ListaContactos::OrdenarPorUsername()
{
	if (listaContactos == nullptr) return;

	bool intercambiado;

	do {
		intercambiado = false;
		Nodo^ actual = listaContactos;

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


void ListaContactos::Eliminar(String^ usuario)
{
	if (listaContactos == nullptr) return;
	Nodo^ actual = listaContactos;
	Nodo^ anterior = nullptr;
	while (actual != nullptr) {
		if (actual->persona->GetNombreUsuario()
			->Equals(usuario, StringComparison::OrdinalIgnoreCase))
		{
			if (anterior == nullptr) {
				listaContactos = actual->next;
			}
			else {
				anterior->next = actual->next;
			}
			actual->next = nullptr;
			return;
		}
		anterior = actual;
		actual = actual->next;
	}
}


Nodo^ ListaContactos::obtenerMitad(Nodo^ inicio, Nodo^ fin)
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
void ListaContactos::agregarList(ListBox^ lista)
{
	lista->Items->Clear();
	Nodo^ actual = listaContactos;
	while (actual != nullptr) {
		lista->Items->Add(actual->persona);
		actual = actual->next;
	}

}

void ListaContactos::agregar(Persona^ usuario)
{
	if (buscar(usuario->GetNombreUsuario(), 1) != nullptr)
		return;

	Nodo^ nuevo = gcnew Nodo(usuario);
	if (listaContactos == nullptr) {
		listaContactos = nuevo;
	}
	else {
		Nodo^ actual = listaContactos;
		while (actual->next != nullptr) {
			actual = actual->next;
		}
		actual->next = nuevo;
	}
}






