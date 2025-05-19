#pragma once
// Nodos que manejan los mensajes 
generic <typename T>
public ref class NodoMensaje {
public:
    T dato;
    NodoMensaje<T>^ siguiente;

    NodoMensaje(T d) {
        dato = d;
        siguiente = nullptr;
    }
};

