// ListaMensajes.h
#pragma once
#include "GestorMensajes.h"
#include "NodoMensaje.h"
#include "Pila.h"
#include "Cola.h"
#include <fstream>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Runtime::Serialization::Formatters::Binary;

generic<typename T>
public ref class ListaMensajes {
private:

	// pila de deshacer, rehacer y cola de no leidos, son nodos con una lista(vector de tipo template)
	Pila<NodoMensaje<GestorMensajes<T>^>^>^ pilaDeshacer;
	Pila<NodoMensaje<GestorMensajes<T>^>^>^ pilaRehacer;
	Cola<GestorMensajes<T>^>^ colaNoLeidos;

	NodoMensaje<GestorMensajes<T>^>^ cabeza;
	NodoMensaje<GestorMensajes<T>^>^ cola;


public:
	ListaMensajes() {
		cabeza = nullptr;
		cola = nullptr;
		pilaDeshacer = gcnew Pila<NodoMensaje<GestorMensajes<T>^>^>();
		pilaRehacer = gcnew Pila<NodoMensaje<GestorMensajes<T>^>^>();
		colaNoLeidos = gcnew Cola<GestorMensajes<T>^>();
	}
	// Mismos comparados dentro del Myform.h donde se compara por tabla ascii ignorando las mayusculas y minusculas 
	static int CompareByFecha(GestorMensajes<T>^ a, GestorMensajes<T>^ b) {
		return DateTime::Compare(a->Fecha, b->Fecha);
	}
	static int CompareByContacto(GestorMensajes<T>^ a, GestorMensajes<T>^ b) {
		return String::Compare(a->OtroUsuario, b->OtroUsuario, StringComparison::OrdinalIgnoreCase);
	}
	static int CompareByLongitud(GestorMensajes<T>^ a, GestorMensajes<T>^ b) {
		return a->Contenido->ToString()->Length
			- b->Contenido->ToString()->Length;
	}
	// Devuelve Solo los mensajes con un contacto dado
	List<GestorMensajes<T>^>^ GetMensajesCon(String^ otroUsuario) {
		// vector de mensajes con un solo usuario 
		auto resultado = gcnew List<GestorMensajes<T>^>();
		for (auto cur = cabeza; cur != nullptr; cur = cur->siguiente) {
			auto m = cur->dato;
			if (m->OtroUsuario != nullptr &&
				m->OtroUsuario->Equals(otroUsuario, StringComparison::OrdinalIgnoreCase))
			{
				resultado->Add(m);
			}
		}
		return resultado;
	}


	// agregar un mensaje , Template de contenido, tipo de mensaje, si esta leido y el usuario 
	void AgregarMensaje(T contenido, TipoMensaje tipo, bool leido, String^ otroUsuario) {
		auto msg = gcnew GestorMensajes<T>(contenido, tipo, otroUsuario);
		auto nodo = gcnew NodoMensaje<GestorMensajes<T>^>(msg);

		if (cabeza == nullptr) {
			cabeza = cola = nodo;
		}
		else {
			cola->siguiente = nodo;
			cola = nodo;
		}

		// pila de undo/redo trabaja con Nodos
		// Se guarda por si se quiere eliminar 
		pilaDeshacer->Push(nodo);
		pilaRehacer->Clear();    // invalidamos el redo porque no se esta rehaciendo uaun 

		if (!leido)
			colaNoLeidos->Enqueue(msg);
	}

	// 2) Deshacer mensaje (pop de undo, lo quita de la lista y lo guarda en redo)
	void DeshacerUltimoMensaje() {
		if (pilaDeshacer->IsEmpty()) return;
		auto nodo = pilaDeshacer->Pop();

		// lo eliminamos de la lista enlazada
		if (cabeza == nodo) {
			// si es el primero
			cabeza = cabeza->siguiente;
			if (cola == nodo)
				cola = nullptr;
		}
		else {
			// buscamos al anterior
			auto prev = cabeza;
			while (prev != nullptr && prev->siguiente != nodo)
				prev = prev->siguiente;
			if (prev != nullptr) {
				prev->siguiente = nodo->siguiente;
				if (cola == nodo)
					cola = prev;
			}
		}
		// desconecto completamente el nodo
		nodo->siguiente = nullptr;

		// lo ponemos en la pila de redo
		pilaRehacer->Push(nodo);
	}

	//  Rehacer (pop de redo, lo vuelve a insertar al final y lo devuelve al undo)
	void RehacerUltimoMensaje() {
		if (pilaRehacer->IsEmpty()) return;
		auto nodo = pilaRehacer->Pop();

		// lo volvemos a anexar al final
		nodo->siguiente = nullptr;
		if (cola == nullptr) {
			cabeza = cola = nodo;
		}
		else {
			cola->siguiente = nodo;
			cola = nodo;
		}

		// lo devolvemos a undo
		pilaDeshacer->Push(nodo);
	}

	//  Mensajes pendientes de leer
	int CantidadNoLeidos() {
		return colaNoLeidos->Count;
	}
	// retorna una lista de mensajes no leidos con un dequeue
	// Todos estos metodos son una mezcla de lista enlazadas y vectores 
	List<GestorMensajes<T>^>^ GetMensajesNoLeidos() {
		auto lista = gcnew List<GestorMensajes<T>^>();
		while (!colaNoLeidos->IsEmpty())
			lista->Add(colaNoLeidos->Dequeue());
		return lista;
	}

	void MarcarLeidosCon(String^ otroUsuario) {
		// Recorro la lista y marco todos los leidos 
		for (auto cur = cabeza; cur != nullptr; cur = cur->siguiente) {
			auto m = cur->dato;
			if (!m->Leido && m->OtroUsuario != nullptr && m->OtroUsuario->Equals(otroUsuario, StringComparison::OrdinalIgnoreCase))
			{
				m->Leido = true;
			}
		}
		// Rebuild de la cola de no leídos sin los de este usuario
		auto nueva = gcnew Cola<GestorMensajes<T>^>();
		while (!colaNoLeidos->IsEmpty()) {
			auto m = colaNoLeidos->Dequeue();
			if (!m->OtroUsuario->Equals(otroUsuario, StringComparison::OrdinalIgnoreCase))
				nueva->Enqueue(m);
		}
		colaNoLeidos = nueva;
	}

	// 5) Serialización / deserialización de toda la lista enlazada
	// Se ocupa este metodo para preparar todo los mensajes para guardar 
	array<GestorMensajes<T>^>^ PrepararParaGuardar() {
		auto tmp = gcnew List<GestorMensajes<T>^>();
		for (auto cur = cabeza; cur != nullptr; cur = cur->siguiente)
			tmp->Add(cur->dato);
		return tmp->ToArray();
	}
	// aca se deserializan y se almacenan 
	void RestaurarDesdeCarga(array<GestorMensajes<T>^>^ arr) {
		cabeza = cola = nullptr;
		pilaDeshacer->Clear();
		colaNoLeidos->Clear();
		pilaRehacer->Clear();
		if (arr == nullptr) return;
		for each (auto m in arr) {
			auto nodo = gcnew NodoMensaje<GestorMensajes<T>^>(m);
			if (cabeza == nullptr) cabeza = cola = nodo;
			else { cola->siguiente = nodo; cola = nodo; }
			pilaDeshacer->Push(nodo);
			if (!m->Leido) colaNoLeidos->Enqueue(m);
		}
	}

	// 6) Guardar/Cargar conversación individual
	void GuardarConversacion(String^ otroUsuario) {
		auto msgs = GetMensajesCon(otroUsuario);
		String^ fn = String::Format("conversacion_{0}.dat", otroUsuario);
		FileStream^ fs = gcnew FileStream(fn, FileMode::Create, FileAccess::Write);
		BinaryFormatter^ bf = gcnew BinaryFormatter();
		bf->Serialize(fs, msgs);
		fs->Close();
	}
	List<GestorMensajes<T>^>^ CargarConversacion(String^ otroUsuario) {
		String^ fn = String::Format("conversacion_{0}.dat", otroUsuario);
		if (!File::Exists(fn)) return nullptr;
		FileStream^ fs = gcnew FileStream(fn, FileMode::Open, FileAccess::Read);
		BinaryFormatter^ bf = gcnew BinaryFormatter();
		auto msgs = safe_cast<List<GestorMensajes<T>^>^>(bf->Deserialize(fs));
		fs->Close();
		return msgs;
	}

	// 7) Algoritmos de ordenamiento para los botones especificos 
	void OrdenarPorFecha_Burbuja()
	{
		if (!cabeza) return;
		bool swapped;
		do {
			swapped = false;
			auto cur = cabeza;
			while (cur->siguiente) {
				auto nxt = cur->siguiente;
				if (CompareByFecha(cur->dato, nxt->dato) > 0) {
					// swap datos
					auto tmp = cur->dato;
					cur->dato = nxt->dato;
					nxt->dato = tmp;
					swapped = true;
				}
				cur = nxt;
			}
		} while (swapped);
	}

	//  Insertion‐sort por nombre de contacto
	void OrdenarPorContacto_Insercion()
	{
		if (!cabeza) return;
		NodoMensaje<GestorMensajes<T>^>^ sorted = nullptr;
		auto cur = cabeza;
		while (cur) {
			auto next = cur->siguiente;
			if (!sorted ||
				CompareByContacto(cur->dato, sorted->dato) < 0)
			{
				cur->siguiente = sorted;
				sorted = cur;
			}
			else {
				auto p = sorted;
				while (p->siguiente &&
					CompareByContacto(p->siguiente->dato, cur->dato) < 0)
					p = p->siguiente;
				cur->siguiente = p->siguiente;
				p->siguiente = cur;
			}
			cur = next;
		}
		cabeza = sorted;
		cola = cabeza;
		while (cola->siguiente) cola = cola->siguiente;
	}

	void OrdenarPorLongitud_QuickSort()
	{
		cabeza = QuickSortList(cabeza);

		// Recalcular “cola”
		cola = cabeza;
		if (cola) {
			while (cola->siguiente)
				cola = cola->siguiente;
		}

		// Reconstruir undo/redo y cola de no leídos
		pilaDeshacer->Clear();
		pilaRehacer->Clear();
		colaNoLeidos->Clear();
		for (auto cur = cabeza; cur != nullptr; cur = cur->siguiente) {
			pilaDeshacer->Push(cur);
			if (!cur->dato->Leido)
				colaNoLeidos->Enqueue(cur->dato);
		}
	}

private:

	NodoMensaje<GestorMensajes<T>^>^ QuickSortList(NodoMensaje<GestorMensajes<T>^>^ head)
	{
		if (!head || !head->siguiente)
			return head;

		// Elegimos el primer elemento como pivote
		int pivotLen = head->dato->Contenido->ToString()->Length;

		// Cabeceras y colas de las 3 sub-listas
		NodoMensaje<GestorMensajes<T>^>^ lessH = nullptr, ^ lessT = nullptr;
		NodoMensaje<GestorMensajes<T>^>^ equalH = nullptr, ^ equalT = nullptr;
		NodoMensaje<GestorMensajes<T>^>^ greatH = nullptr, ^ greatT = nullptr;

		// Partición
		for (auto cur = head; cur != nullptr; ) {
			auto next = cur->siguiente;
			cur->siguiente = nullptr;

			int len = cur->dato->Contenido->ToString()->Length;
			if (len < pivotLen) {
				if (!lessH) lessH = lessT = cur;
				else { lessT->siguiente = cur; lessT = cur; }
			}
			else if (len == pivotLen) {
				if (!equalH) equalH = equalT = cur;
				else { equalT->siguiente = cur; equalT = cur; }
			}
			else {
				if (!greatH) greatH = greatT = cur;
				else { greatT->siguiente = cur; greatT = cur; }
			}

			cur = next;
		}

		// Recursión
		lessH = QuickSortList(lessH);
		greatH = QuickSortList(greatH);

		NodoMensaje<GestorMensajes<T>^>^ newHead = nullptr, ^ newTail = nullptr;

		// 1) less
		if (lessH) {
			newHead = lessH;
			newTail = lessH;
			while (newTail->siguiente)
				newTail = newTail->siguiente;
		}

		// 2) equal
		if (equalH) {
			if (!newHead) {
				newHead = equalH;
				newTail = equalT;
			}
			else {
				newTail->siguiente = equalH;
				newTail = equalT;
			}
		}

		// 3) greater
		if (greatH) {
			if (!newHead) {
				newHead = greatH;
				// no necesitamos tail más allá de aquí
			}
			else {
				newTail->siguiente = greatH;
			}
		}

		return newHead;
	}
};