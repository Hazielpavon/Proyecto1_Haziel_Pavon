// Gestion.cpp
#include "Gestion.h"
#include "ListaContactos.h"
// Esta clase Gestiona las solicitudes 

void Gestion::EnviarSolicitud(Persona^ emisor, Persona^ receptor)
{
    if (emisor == nullptr || receptor == nullptr)
        return;

    //  No puedo mandarme solicitud a mi mismo 
    if (emisor->GetNombreUsuario()
        ->Equals(receptor->GetNombreUsuario(), StringComparison::OrdinalIgnoreCase))
    {
        MessageBox::Show(
            "No se puede enviar solicitud a uno mismo.",
            "Error",
            MessageBoxButtons::OK,
            MessageBoxIcon::Warning
        );
        return;
    }

    // 2) no puede enviarse solicitud a alguien queya es tu amigo 
    if (emisor->GetListaContactos()->buscar(receptor->GetNombreUsuario(), 1) != nullptr) {
        MessageBox::Show("Ya son amigos.", "Info",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }

    // No se puede enviar solicitud a alguien que ya le mandaste solicitud 
    if (emisor->GetSolicitudesEnviadas()->buscar(receptor->GetNombreUsuario(), 1) != nullptr) {
        MessageBox::Show("Ya enviaste una solicitud a este usuario.", "Info",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }

    // 4) No se puede mandar ambos solicitudes de amistad 
    if (emisor->GetSolicitudesRecibidas()->buscar(receptor->GetNombreUsuario(), 1) != nullptr) {
        MessageBox::Show("Este usuario ya te envió una solicitud. Ve a \"Solicitudes\" para aceptarla.",
            "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }


    emisor->GetSolicitudesEnviadas()->agregar(receptor);
    receptor->GetSolicitudesRecibidas()->agregar(emisor);

    MessageBox::Show("Solicitud enviada correctamente.", "Éxito",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
}

// aceptar la solicitud 
void Gestion::AceptarSolicitud(Persona^ receptor, Persona^ emisor)
{
    if (receptor == nullptr || emisor == nullptr)
        return;
        
    if (receptor->GetSolicitudesRecibidas()->buscar(emisor->GetNombreUsuario(), 1) == nullptr) {
        MessageBox::Show("No tienes ninguna solicitud de este usuario.", "Error",
            MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }
    // Si falla alguna de las otras valicaciones este metodo no permite aceptar solicitudes 
    if (receptor->GetListaContactos()->buscar(emisor->GetNombreUsuario(), 1) != nullptr) {
        receptor->GetSolicitudesRecibidas()->Eliminar(emisor->GetNombreUsuario());
        emisor->GetSolicitudesEnviadas()->Eliminar(receptor->GetNombreUsuario());

        MessageBox::Show("Ya eran amigos. Se ha eliminado la solicitud pendiente.", "Info",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }
    // se elimina de la lista la solicitud enviada y recibida y se hacen amigps 
    receptor->GetSolicitudesRecibidas()->Eliminar(emisor->GetNombreUsuario());
    emisor->GetSolicitudesEnviadas()->Eliminar(receptor->GetNombreUsuario());

    // se agregan mutuamente 
    receptor->GetListaContactos()->agregar(emisor);
    emisor->GetListaContactos()->agregar(receptor);

    MessageBox::Show("Solicitud aceptada.", "Éxito",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
}

// rechazar solicitud 
void Gestion::RechazarSolicitud(Persona^ receptor, Persona^ emisor)
{   
    if (receptor == nullptr || emisor == nullptr)
        return;

    if (receptor->GetSolicitudesRecibidas()->buscar(emisor->GetNombreUsuario(), 1) == nullptr) {
        MessageBox::Show("No tienes ninguna solicitud de este usuario.", "Error",
            MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    if (receptor->GetListaContactos()->buscar(emisor->GetNombreUsuario(), 1) != nullptr) {
        MessageBox::Show("Ya son amigos. No se puede rechazar una solicitud de un amigo.", "Info",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }

    receptor->GetSolicitudesRecibidas()->Eliminar(emisor->GetNombreUsuario());
    emisor->GetSolicitudesEnviadas()->Eliminar(receptor->GetNombreUsuario());

    MessageBox::Show("Solicitud rechazada.", "Info",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
}
