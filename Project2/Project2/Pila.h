#pragma once

using namespace System;

// Pila LIFO
generic<typename T>
public ref class Pila
{
private:
    ref class Nodo
    {
    public:
        T Valor;
        Nodo^ Siguiente;
        Nodo(T v) : Valor(v), Siguiente(nullptr) {}
    };

    Nodo^ cima;
    int conteo;

public:
    Pila() : cima(nullptr), conteo(0) {}

    // Añade un elemento
    void Push(T v)
    {
        Nodo^ n = gcnew Nodo(v);
        n->Siguiente = cima;
        cima = n;
        ++conteo;
    }

    // Extrae el elemento superior
    T Pop()
    {
        if (IsEmpty())
            throw gcnew InvalidOperationException("La pila está vacía.");
        T v = cima->Valor;
        cima = cima->Siguiente;
        --conteo;
        return v;
    }

    // Consulta el elemento superior sin extraerlo
    T Peek()
    {
        if (IsEmpty())
            throw gcnew InvalidOperationException("La pila está vacía.");
        return cima->Valor;
    }

    // ¿Vacía?
    bool IsEmpty()
    {
        return cima == nullptr;
    }

    // Vacía la pila
    void Clear()
    {
        cima = nullptr;
        conteo = 0;
    }

    // Número de elementos
    property int Count
    {
        int get() { return conteo; }
    }
};