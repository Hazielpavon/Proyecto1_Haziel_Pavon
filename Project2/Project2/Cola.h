#pragma once
using namespace System;
generic<typename T>
public ref class Cola
{
private:
    ref class Nodo
    {
    public:
        T Valor;
        Nodo^ Siguiente;
        Nodo(T v) : Valor(v), Siguiente(nullptr) {}
    };

    Nodo^ head;
    Nodo^ tail;
    int conteo;

public:
    Cola() : head(nullptr), tail(nullptr), conteo(0) {}

    // Añade al final
    void Enqueue(T v)
    {
        Nodo^ n = gcnew Nodo(v);
        if (tail != nullptr)
            tail->Siguiente = n;
        tail = n;
        if (head == nullptr)
            head = n;
        ++conteo;
    }

    // Extrae del frente
    T Dequeue()
    {
        if (IsEmpty())
            throw gcnew InvalidOperationException("La cola está vacía.");
        T v = head->Valor;
        head = head->Siguiente;
        if (head == nullptr)
            tail = nullptr;
        --conteo;
        return v;
    }

    // Consulta el frente sin extraer
    T Peek()
    {
        if (IsEmpty())
            throw gcnew InvalidOperationException("La cola está vacía.");
        return head->Valor;
    }

    // ¿Vacía?
    bool IsEmpty()
    {
        return head == nullptr;
    }

    // Vacía la cola
    void Clear()
    {
        head = nullptr;
        tail = nullptr;
        conteo = 0;
    }

    // Número de elementos
    property int Count
    {
        int get() { return conteo; }
    }
};
