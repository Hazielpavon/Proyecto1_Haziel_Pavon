#pragma once
#using <System.dll>
#include "Pila.h"    
#include "Cola.h"
#using <System.Drawing.dll>
#using <System.Runtime.Serialization.dll>
#using <mscorlib.dll>
#include "ListaContactos.h"
#include "GestorMensajes.h"
#include "ListaMensajes.h"
#include "Listausuarios.h"
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Runtime::Serialization;
using namespace System::Collections::Generic;
ref class Listausuarios;
[Serializable]
ref class ListaContactos;
[Serializable]
ref class Persona : public ISerializable
{
private:
	// cada usuario tiene, colas para eliminar mensaje, pilas para deshacer mensajes, sus atributos, una lista de contacos, mensajes enviados y recibidos y solicitudes enviadas
	Pila<GestorMensajes<String^>^>^ pilaDeshacer;
	Cola<GestorMensajes<String^>^>^ colaNoLeidos;
	String^ NombreUsuario;
	String^ NombreCompleto;
	String^ Correo;
	String^ Contrasena;
	int Edad;
	array<Byte>^ ImagenBytes;
	String^ PreguntaSeguridad;
	String^ Respuesta;
	bool estado;

	[NonSerialized]
	Image^ ImagenPerfil;
	[NonSerialized]
	ListaContactos^ listaContactos;
	[NonSerialized]
	ListaContactos^ solicitudesEnviadas;
	[NonSerialized]
	ListaContactos^ solicitudesRecibidas;
	[NonSerialized]
	ListaMensajes<String^>^ listamensajesEnviados;
	[NonSerialized]
	ListaMensajes<String^>^ listamensajesRecibidos;

	array<String^>^ nombresContactos;
	array<String^>^ nombresSolicitudesEnviadas;
	array<String^>^ nombresSolicitudesRecibidas;
	array<GestorMensajes<String^>^>^ mensajesEnviadosGuardados;
	array<GestorMensajes<String^>^>^ mensajesRecibidosGuardados;
public:
	Persona(SerializationInfo^ info, StreamingContext context);
	Persona(String^ nombreUsuario,
		String^ nombreCompleto,
		String^ correo,
		String^ contrasena,
		int edad,
		Image^ imagenPerfil,
		String^ preguntaSeguridad,
		String^ respuesta);

	Persona();
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

	ListaMensajes<String^>^ GetListaMensajesEnviados();
	void SetListaMensajesEnviados(ListaMensajes<String^>^ lista);

	ListaMensajes<String^>^ GetListaMensajesRecibidos();
	void SetListaMensajesRecibidos(ListaMensajes<String^>^ lista);

	// guardado y srializar 
	void PrepararParaGuardar();
	void RestaurarDesdeCarga(Listausuarios^ todosUsuarios);
	virtual void GetObjectData(SerializationInfo^ info, StreamingContext context);
	virtual String^ ToString() override;
};
