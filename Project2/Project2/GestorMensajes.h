// GestorMensajes.h
#pragma once
using namespace System;
// clase para poder manejar los tipos de mensaje 
[Serializable]
enum class TipoMensaje {
    Texto,
    Sticker,
    Archivo
};

generic <typename T>
[Serializable]
public ref class GestorMensajes
{
private:
    T contenido;
    DateTime fechaHora;
    TipoMensaje tipo;
    String^ interlocutor;
    bool leido;
public:
    GestorMensajes(T c, TipoMensaje t, String^ otroUsuario): contenido(c), tipo(t), interlocutor(otroUsuario)
    {
        fechaHora = DateTime::Now;
    }

    property T Contenido {
        T get() { return contenido; }
    }
    property TipoMensaje Tipo {
        TipoMensaje get() { return tipo; }
    }
    property DateTime Fecha {
        DateTime get() { return fechaHora; }
    }
    property String^ OtroUsuario {
        String^ get() { return interlocutor; }
    }

    virtual String^ ToString() override {
        return String::Format("[{0}] {1}",
            fechaHora.ToString("HH:mm"), contenido->ToString());
    }
    property bool Leido { bool get() { return leido; } void set(bool v) { leido = v; } }

};
