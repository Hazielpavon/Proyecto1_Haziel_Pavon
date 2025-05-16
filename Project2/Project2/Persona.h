#pragma once

#include "ListaContactos.h"
using namespace System;
using namespace System::Drawing;
[Serializable]
ref class ListaContactos;
[Serializable]
public ref class Persona {
private:
private:
	String^ NombreUsuario;
	String^ NombreCompleto;
	String^ Correo;
	String^ Contrasena;
	int Edad;
	[NonSerialized]
	Image^ ImagenPerfil;
	array<Byte>^ ImagenBytes;
	String^ PreguntaSeguridad;
	String^ Respuesta;
	bool estado;
	[NonSerialized]
		ListaContactos^ listaContactos;
	[NonSerialized]
		ListaContactos^ solicitudesEnviadas;
	[NonSerialized]
		ListaContactos^ solicitudesRecibidas;

		array<String^>^ nombresContactos;
		array<String^>^ nombresSolicitudesEnviadas;
		array<String^>^ nombresSolicitudesRecibidas;

public:
	Persona(String^ nombreUsuario,
		String^ nombreCompleto,
		String^ correo,
		String^ contrasena,
		int edad,
		Image^ imagenPerfil,
		String^ preguntaSeguridad,
		String^ respuesta);

	// Getters y Setters
	String^ GetNombreUsuario();
	void SetNombreUsuario(String^ nombreUsuario);

	String^ GetNombreCompleto();
	void SetNombreCompleto(String^ nombreCompleto);

	String^ GetCorreo();
	void SetCorreo(String^ correo);

	String^ GetContrasena();
	void SetContrasena(String^ contrasena);

	int GetEdad();
	void SetEdad(int edad);

	Image^ GetImagenPerfil();
	void SetImagenPerfil(Image^ imagen);

	String^ GetPreguntaSeguridad();
	void SetPreguntaSeguridad(String^ pregunta);

	String^ GetRespuesta();
	void SetRespuesta(String^ respuesta);

	bool GetEstado();
	void SetEstado(bool e);

	ListaContactos^ GetListaContactos();
	ListaContactos^ GetSolicitudesEnviadas();
	ListaContactos^ GetSolicitudesRecibidas();

	virtual String^ ToString() override;
	void PrepararParaGuardar();
	void RestaurarDesdeCarga();
};
