#pragma once
ref class Persona;

ref class Gestion
{
public:
    static void EnviarSolicitud(Persona^ emisor, Persona^ receptor);
    static void AceptarSolicitud(Persona^ receptor, Persona^ emisor);
    static void RechazarSolicitud(Persona^ receptor, Persona^ emisor);
};


