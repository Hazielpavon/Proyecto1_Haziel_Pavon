#include "Gestion.h"
#include "Gestion.h"
#include "Persona.h"
#include "ListaContactos.h"
using namespace System::Windows::Forms;
void Gestion::EnviarSolicitud(Persona^ emisor, Persona^ receptor)
{
	if (receptor == nullptr || emisor == nullptr) return;

	if (receptor != emisor) {
		if (emisor->GetSolicitudesEnviadas()->buscar(receptor->GetNombreUsuario(), 1) != nullptr) {
			MessageBox::Show("Solicitud ya enviada.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}
		emisor->GetSolicitudesEnviadas()->agregar(receptor);
		receptor->GetSolicitudesRecibidas()->agregar(emisor);
		MessageBox::Show("Solicitud Enviada Correctamente");
	}
	else {
		MessageBox::Show("No se puede agregar a usted mismo");
		return;
	}
}

void Gestion::AceptarSolicitud(Persona^ receptor, Persona^ emisor)
{

	if (receptor->GetListaContactos()->buscar(emisor->GetNombreUsuario(), 1) != nullptr) {
		MessageBox::Show("Ya son amigos.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return;
	}

	receptor->GetSolicitudesRecibidas()->Eliminar(emisor->GetNombreUsuario());
	emisor->GetSolicitudesEnviadas()->Eliminar(receptor->GetNombreUsuario());

	receptor->GetListaContactos()->agregar(emisor);
	emisor->GetListaContactos()->agregar(receptor);

	MessageBox::Show("Solicitud aceptada.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
}


void Gestion::RechazarSolicitud(Persona^ receptor, Persona^ emisor)
{
	if (receptor == nullptr || emisor == nullptr) return;

	if (receptor->GetSolicitudesRecibidas()->buscar(emisor->GetNombreUsuario(), 1) == nullptr) {
		MessageBox::Show("No existe solicitud recibida.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	receptor->GetSolicitudesRecibidas()->Eliminar(emisor->GetNombreUsuario());
	emisor->GetSolicitudesEnviadas()->Eliminar(receptor->GetNombreUsuario());
	MessageBox::Show("Solicitud rechazada.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
