#include "Persona.h"
#include "ListaContactos.h"
using namespace System::IO;

Persona::Persona(String^ nombreUsuario,
    String^ nombreCompleto,
    String^ correo,
    String^ contrasena,
    int edad,
    Image^ imagenPerfil,
    String^ preguntaSeguridad,
    String^ respuesta)
{
    NombreUsuario = nombreUsuario;
    NombreCompleto = nombreCompleto;
    Correo = correo;
    Contrasena = contrasena;
    Edad = edad;
    ImagenPerfil = imagenPerfil;
    PreguntaSeguridad = preguntaSeguridad;
    Respuesta = respuesta;
    estado = false;

    listaContactos = gcnew ListaContactos();
    solicitudesEnviadas = gcnew ListaContactos();
    solicitudesRecibidas = gcnew ListaContactos();
}

String^ Persona::GetNombreUsuario() { return NombreUsuario; }
void Persona::SetNombreUsuario(String^ v) { NombreUsuario = v; }

String^ Persona::GetNombreCompleto() { return NombreCompleto; }
void Persona::SetNombreCompleto(String^ v) { NombreCompleto = v; }

String^ Persona::GetCorreo() { return Correo; }
void Persona::SetCorreo(String^ v) { Correo = v; }

String^ Persona::GetContrasena() { return Contrasena; }
void Persona::SetContrasena(String^ v) { Contrasena = v; }

int Persona::GetEdad() { return Edad; }
void Persona::SetEdad(int v) { Edad = v; }

Image^ Persona::GetImagenPerfil() { return ImagenPerfil; }
void Persona::SetImagenPerfil(Image^ v) { ImagenPerfil = v; }

String^ Persona::GetPreguntaSeguridad() { return PreguntaSeguridad; }
void Persona::SetPreguntaSeguridad(String^ v) { PreguntaSeguridad = v; }

String^ Persona::GetRespuesta() { return Respuesta; }
void Persona::SetRespuesta(String^ v) { Respuesta = v; }

bool Persona::GetEstado() { return estado; }
void Persona::SetEstado(bool e) { estado = e; }

ListaContactos^ Persona::GetListaContactos() { return listaContactos; }
ListaContactos^ Persona::GetSolicitudesEnviadas() { return solicitudesEnviadas; }
ListaContactos^ Persona::GetSolicitudesRecibidas() { return solicitudesRecibidas; }



String^ Persona::ToString() 
{
    return NombreUsuario;
}

void Persona::PrepararParaGuardar() {
    if (ImagenPerfil != nullptr) {
        MemoryStream^ ms = gcnew MemoryStream();
        ImagenPerfil->Save(ms, System::Drawing::Imaging::ImageFormat::Png);
        ImagenBytes = ms->ToArray();
    }

    if (listaContactos != nullptr)
        nombresContactos = listaContactos->GetNombresUsuarios();

    if (solicitudesEnviadas != nullptr)
        nombresSolicitudesEnviadas = solicitudesEnviadas->GetNombresUsuarios();

    if (solicitudesRecibidas != nullptr)
        nombresSolicitudesRecibidas = solicitudesRecibidas->GetNombresUsuarios();
}

void Persona::RestaurarDesdeCarga() {
    if (ImagenBytes != nullptr) {
        MemoryStream^ ms = gcnew MemoryStream(ImagenBytes);
        ImagenPerfil = Image::FromStream(ms);
    }

    listaContactos = gcnew ListaContactos();
    solicitudesEnviadas = gcnew ListaContactos();
    solicitudesRecibidas = gcnew ListaContactos();

    if (nombresContactos != nullptr) {
        for each (String ^ nombre in nombresContactos)
            listaContactos->agregar(gcnew Persona(nombre, "", "", "", 0, nullptr, "", ""));
    }

    if (nombresSolicitudesEnviadas != nullptr) {
        for each (String ^ nombre in nombresSolicitudesEnviadas)
            solicitudesEnviadas->agregar(gcnew Persona(nombre, "", "", "", 0, nullptr, "", ""));
    }

    if (nombresSolicitudesRecibidas != nullptr) {
        for each (String ^ nombre in nombresSolicitudesRecibidas)
            solicitudesRecibidas->agregar(gcnew Persona(nombre, "", "", "", 0, nullptr, "", ""));
    }
}



