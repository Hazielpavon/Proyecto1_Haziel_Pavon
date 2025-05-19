#include "Persona.h"
#include "GestorMensajes.h"
#include "ListaContactos.h"
#include "Listausuarios.h"
using namespace System::IO;
// Constructor sobrecargado 
Persona::Persona(String^ nombreUsuario, String^ nombreCompleto, String^ correo,String^ contrasena, int edad, Image^ imagenPerfil,String^ preguntaSeguridad, String^ respuesta):
	NombreUsuario(nombreUsuario), 
	NombreCompleto(nombreCompleto),
	Correo(correo), 
	Contrasena(contrasena), 
	Edad(edad),
	ImagenPerfil(imagenPerfil), 
	PreguntaSeguridad(preguntaSeguridad),
	Respuesta(respuesta), 
	estado(false),
	listaContactos(gcnew ListaContactos()),
	solicitudesEnviadas(gcnew ListaContactos()),
	solicitudesRecibidas(gcnew ListaContactos()),
	listamensajesEnviados(gcnew ListaMensajes<String^>()),
	listamensajesRecibidos(gcnew ListaMensajes<String^>()) 
{}
// Constructor Vacio 
Persona::Persona()
{
	pilaDeshacer = gcnew Pila<GestorMensajes<String^>^>();
	colaNoLeidos = gcnew Cola<GestorMensajes<String^>^>();
	NombreUsuario = "";
	NombreCompleto = "";
	Correo = "";
	Contrasena = "";
	Edad = 0;
	ImagenPerfil = nullptr;
	ImagenBytes = nullptr;
	PreguntaSeguridad = "";
	Respuesta = "";
	estado = false;
	listaContactos = gcnew ListaContactos();
	solicitudesEnviadas = gcnew ListaContactos();
	solicitudesRecibidas = gcnew ListaContactos();
	nombresContactos = gcnew array<String^>(0);
	nombresSolicitudesEnviadas = gcnew array<String^>(0);
	nombresSolicitudesRecibidas = gcnew array<String^>(0);
	listamensajesEnviados = gcnew ListaMensajes<String^>();
	listamensajesRecibidos = gcnew ListaMensajes<String^>();
}
// Getters y setters 
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
void Persona::SetImagenPerfil(Image^ imagen) {
	this->ImagenPerfil = imagen;

	if (imagen != nullptr) {
		MemoryStream^ ms = gcnew MemoryStream();
		imagen->Save(ms, Imaging::ImageFormat::Png);
		ImagenBytes = ms->ToArray();
	}
}

String^ Persona::GetPreguntaSeguridad() { return PreguntaSeguridad; }
void Persona::SetPreguntaSeguridad(String^ v) { PreguntaSeguridad = v; }

String^ Persona::GetRespuesta() { return Respuesta; }
void Persona::SetRespuesta(String^ v) { Respuesta = v; }

bool Persona::GetEstado() { return estado; }
void Persona::SetEstado(bool e) { estado = e; }

ListaContactos^ Persona::GetListaContactos() { return listaContactos; }
ListaContactos^ Persona::GetSolicitudesEnviadas() { return solicitudesEnviadas; }
ListaContactos^ Persona::GetSolicitudesRecibidas() { return solicitudesRecibidas; }

ListaMensajes<String^>^ Persona::GetListaMensajesEnviados(){return listamensajesEnviados;}
void Persona::SetListaMensajesEnviados(ListaMensajes<String^>^ lista){listamensajesEnviados = lista;}

ListaMensajes<String^>^ Persona::GetListaMensajesRecibidos(){return listamensajesRecibidos;}
void Persona::SetListaMensajesRecibidos(ListaMensajes<String^>^ lista){listamensajesRecibidos = lista;}

String^ Persona::ToString(){return NombreUsuario;}


// Preparamos la clase persona para guardar 
void Persona::PrepararParaGuardar() {
	// Convertimos la imagen a bytes 
	// Investigado en : https://stackoverflow.com/questions/7629887/difficulty-saving-image-to-memorystream
	if (ImagenPerfil != nullptr) {
		try {
			MemoryStream^ ms = gcnew MemoryStream();
			ImagenPerfil->Save(ms, Imaging::ImageFormat::Png);
			ImagenBytes = ms->ToArray();
			ms->Close();
		}
		catch (Exception^) {
			ImagenBytes = nullptr;
		}
	}
	else {
		ImagenBytes = nullptr;
	}

	// guardamos los nombres de los contactos en un array para que sea mas facil de almacenar 
	if (listaContactos != nullptr) {
		auto arr = listaContactos->GetNombresUsuarios();
		nombresContactos = (arr != nullptr) ? arr : gcnew array<String^>(0);
	}
	else {
		nombresContactos = gcnew array<String^>(0);
	}

	// lo mismo pero con las solicitudes enviadas 
	if (solicitudesEnviadas != nullptr) {
		auto arr = solicitudesEnviadas->GetNombresUsuarios();
		nombresSolicitudesEnviadas = (arr != nullptr) ? arr : gcnew array<String^>(0);
	}
	else {
		nombresSolicitudesEnviadas = gcnew array<String^>(0);
	}

	//  Solicitudes recibidas
	if (solicitudesRecibidas != nullptr) {
		auto arr = solicitudesRecibidas->GetNombresUsuarios();
		nombresSolicitudesRecibidas = (arr != nullptr) ? arr : gcnew array<String^>(0);
	}
	else {
		nombresSolicitudesRecibidas = gcnew array<String^>(0);
	}

	//  Mensajes enviados
	if (listamensajesEnviados != nullptr) {
		auto arr = listamensajesEnviados->PrepararParaGuardar();
		mensajesEnviadosGuardados = (arr != nullptr) ? arr : gcnew array<GestorMensajes<String^>^>(0);
	}
	else {
		mensajesEnviadosGuardados = gcnew array<GestorMensajes<String^>^>(0);
	}

	//  Mensajes recibidos
	if (listamensajesRecibidos != nullptr) {
		auto arr = listamensajesRecibidos->PrepararParaGuardar();
		mensajesRecibidosGuardados = (arr != nullptr) ? arr : gcnew array<GestorMensajes<String^>^>(0);
	}
	else {
		mensajesRecibidosGuardados = gcnew array<GestorMensajes<String^>^>(0);
	}
}
// Preparamos para restaurar la persona 
void Persona::RestaurarDesdeCarga(Listausuarios^ todosUsuarios) {
	// 1) Restaurar imagen
	if (ImagenBytes != nullptr && ImagenBytes->Length > 0) {
		try {
			MemoryStream^ ms = gcnew MemoryStream(ImagenBytes);
			ImagenPerfil = Image::FromStream(ms);
			ms->Close();
		}
		catch (...) {
			ImagenPerfil = nullptr;
		}
	}
	else {
		ImagenPerfil = nullptr;
	}

	// inicializamos la lista vacia y se carga con la lista de mensajes enviados guardados 
	listamensajesEnviados = gcnew ListaMensajes<String^>();
	listamensajesEnviados->RestaurarDesdeCarga(mensajesEnviadosGuardados);

	// inicializamos la lista vacia y se carga con la lista de mensajes recibidps guardados 
	listamensajesRecibidos = gcnew ListaMensajes<String^>();
	listamensajesRecibidos->RestaurarDesdeCarga(mensajesRecibidosGuardados);

	// para agregar los contactos recorremos la lista de nombre de contacto, se busca el usuario y se agrega 
	listaContactos = gcnew ListaContactos();
	for each (String ^ nom in nombresContactos) {
		if (!String::IsNullOrWhiteSpace(nom)) {
			if (Nodo^ n = todosUsuarios->BuscarPersona(nom, 1))
				listaContactos->agregar(n->persona);
		}
	}
	// Lo mismo pero con solicitudes de amistad enviadas 
	solicitudesEnviadas = gcnew ListaContactos();
	for each (String ^ nom in nombresSolicitudesEnviadas) {
		if (!String::IsNullOrWhiteSpace(nom)) {
			if (Nodo^ n = todosUsuarios->BuscarPersona(nom, 1))
				solicitudesEnviadas->agregar(n->persona);
		}
	}
	// Lo mismo pero con solicitudes de amistad Recibidas 
	solicitudesRecibidas = gcnew ListaContactos();
	for each (String ^ nom in nombresSolicitudesRecibidas) {
		if (!String::IsNullOrWhiteSpace(nom)) {
			if (Nodo^ n = todosUsuarios->BuscarPersona(nom, 1))
				solicitudesRecibidas->agregar(n->persona);
		}
	}
}

// Estos dos metodos son escenciales para que cuando se lea se entienda lo que esta leyendo y como interpretar la informacion en el codigo 
Persona::Persona(SerializationInfo^ info, StreamingContext context) {
	NombreUsuario = info->GetString("NombreUsuario");
	Contrasena = info->GetString("Contrasena");     
	NombreCompleto = info->GetString("NombreCompleto");
	Correo = info->GetString("Correo");
	Edad = info->GetInt32("Edad");

	ImagenBytes = safe_cast<array<Byte>^>(info->GetValue("ImagenBytes", array<Byte>::typeid));
	if (ImagenBytes != nullptr) {
		MemoryStream^ ms = gcnew MemoryStream(ImagenBytes);
		ImagenPerfil = Image::FromStream(ms);
	}

	PreguntaSeguridad = info->GetString("PreguntaSeguridad");
	Respuesta = info->GetString("Respuesta");
	estado = info->GetBoolean("Estado");
	nombresContactos = (array<String^>^) info->GetValue("nombresContactos", array<String^>::typeid);
	nombresSolicitudesEnviadas = (array<String^>^) info->GetValue("nombresSolicitudesEnviadas", array<String^>::typeid);
	nombresSolicitudesRecibidas = (array<String^>^) info->GetValue("nombresSolicitudesRecibidas", array<String^>::typeid);
	mensajesEnviadosGuardados =safe_cast<array<GestorMensajes<String^>^>^>(info->GetValue("mensajesEnviadosGuardados",array<GestorMensajes<String^>^>::typeid));
	mensajesRecibidosGuardados =safe_cast<array<GestorMensajes<String^>^>^>(info->GetValue("mensajesRecibidosGuardados",array<GestorMensajes<String^>^>::typeid));

	listaContactos = gcnew ListaContactos();
	solicitudesEnviadas = gcnew ListaContactos();
	solicitudesRecibidas = gcnew ListaContactos();
	listamensajesEnviados = gcnew ListaMensajes<String^>();
	listamensajesRecibidos = gcnew ListaMensajes<String^>();

}
// SIrve para serializar un objeto y guardar de forma correcta sus datos 

void Persona::GetObjectData(SerializationInfo^ info, StreamingContext context) {
	info->AddValue("NombreUsuario", NombreUsuario);
	info->AddValue("Contrasena", Contrasena);       
	info->AddValue("NombreCompleto", NombreCompleto);
	info->AddValue("Correo", Correo);
	info->AddValue("Edad", Edad);

	if (ImagenPerfil != nullptr) {
		MemoryStream^ ms = gcnew MemoryStream();
		ImagenPerfil->Save(ms, Imaging::ImageFormat::Png);
		array<Byte>^ bytes = ms->ToArray();
		info->AddValue("ImagenBytes", bytes);
	}
	else {
		info->AddValue("ImagenBytes", nullptr);
	}

	info->AddValue("PreguntaSeguridad", PreguntaSeguridad);
	info->AddValue("Respuesta", Respuesta);
	info->AddValue("Estado", estado);
	info->AddValue("nombresContactos", nombresContactos);
	info->AddValue("nombresSolicitudesEnviadas", nombresSolicitudesEnviadas);
	info->AddValue("nombresSolicitudesRecibidas", nombresSolicitudesRecibidas);
	info->AddValue("mensajesEnviadosGuardados", mensajesEnviadosGuardados);
	info->AddValue("mensajesRecibidosGuardados", mensajesRecibidosGuardados);
}



