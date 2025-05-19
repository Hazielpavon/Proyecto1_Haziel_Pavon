#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <rpc.h>

#include "MyForm.h"
#include "Persona.h"
#include "Nodo.h"
#include "Listausuarios.h"
#include "Gestion.h"
// CODIGO HECHO POR HAZIEL AARON PAVON VILLEDA 
namespace Project2 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::IO;
	using namespace System::Drawing;


	public ref class MyForm : public System::Windows::Forms::Form
	{
		// Clase Que me ayuda a manejar el tipo de texto, si se envio o no, la hora(Fecha en la que fue enviada)
		ref class HiloItem {
		public:
			String^ Texto;
			DateTime Fecha;
			bool   Enviado;
			TipoMensaje Tipo;
			// Una clase especifica para ver el tipo de mensajes utilizando templates 
			String^ Contenido;

			HiloItem(String^ texto, DateTime fecha, bool enviado, TipoMensaje tipo, String^ contenido) : Texto(texto), Fecha(fecha), Enviado(enviado), Tipo(tipo), Contenido(contenido)
			{
			}

			virtual String^ ToString() override {
				return Texto;
			}
		};
		// Lo que hace buildHistorial es construir en el listbox 6 es mostrar el historial de TODOS los mensajes enviados y recbidos en el orden especificado por el usuario 
		// la sintaxis List<Dato ^>^ es el equivalente en el cli de Vector 
	private: List<HiloItem^>^ BuildHistorial() {
		// va a recorrer y mostrar todos los mensajes enviados 
		auto arrEnv = x->persona->GetListaMensajesEnviados()->PrepararParaGuardar();
		auto arrRec = x->persona->GetListaMensajesRecibidos()->PrepararParaGuardar();
		// "auto" en cli es basicamente la variable se asigna el tipo de dato que sea, si getlistademensajes recibidos es un string, arrrec almacena un string
		auto hilo = gcnew List<HiloItem^>();
		for each (auto m in arrEnv) {
			String^ contenidoBruto = m->Contenido->ToString();
			// Si la condicion es cierta el tipo de mensaje basicamente es un sticker si no se pone otro formato un if mas simplificado en una sola linea 
			// El format es basicamente texto = contenidoBruto->ToString(); pero usando el formato de .NET
			String^ texto = (m->Tipo == TipoMensaje::Sticker) ? "[Sticker]" : String::Format("{0}", contenidoBruto);
			// Va por marcadores [0] selecciona la fecha en el formato, Tu-> [1] Selecciona el otro usuario y por ultimo el texto 
			String^ linea = String::Format("[{0:yyyy-MM-dd HH:mm}] Tú → {1}: {2}", m->Fecha, m->OtroUsuario, texto);

			// Por ultimo todo se agrega al hilo de mensajes 
			hilo->Add(gcnew HiloItem(linea, m->Fecha, true, m->Tipo, contenidoBruto));
		}
		// Se repite el mismo proceso pero para cada mensaje Recibido 
		for each (auto m in arrRec) {
			String^ contenidoBruto = m->Contenido->ToString();
			String^ texto = (m->Tipo == TipoMensaje::Sticker) ? "[Sticker]" : String::Format("{0}", contenidoBruto);

			String^ linea = String::Format("[{0:yyyy-MM-dd HH:mm}] {1} → Tú: {2}", m->Fecha, m->OtroUsuario, texto);

			hilo->Add(gcnew HiloItem(linea, m->Fecha, false, m->Tipo, contenidoBruto));
		}
		return hilo;
	}
		   // Comparacion simple entre mensajes expecificamente su fecha para ordenarlos 
		   static int CompareByFechaHiloItem(HiloItem^ a, HiloItem^ b) {
			   return DateTime::Compare(a->Fecha, b->Fecha);
		   }
		   //significa que se hara una comparacion ordinal (es decir, basada en el valor numerico de los caracteres) pero ignorando mayusculas y minusculas. Con la tabla ascii 
		   //a-> otrousuario, b->otrousuario, basicamente esttoy comparando el mensaje que mando una persona a a una persona b
		   static int CompareGestoresPorContacto(GestorMensajes<String^>^ a, GestorMensajes<String^>^ b) {
			   return String::Compare(a->OtroUsuario, b->OtroUsuario, StringComparison::OrdinalIgnoreCase);
		   }

		   // Si el resultado es negativo es porque b es mayor que a, y si es positivo es porque a es mayor, si es 0 ambas son igual de largas 
		   // Ordena tus mensajes internos por la longitud de su Contenido.
		   static int CompareGestoresPorLongitud(GestorMensajes<String^>^ a, GestorMensajes<String^>^ b) {
			   return a->Contenido->ToString()->Length - b->Contenido->ToString()->Length;
		   }
		   // Ordena tus elementos de UI (HiloItem) por la longitud de la cadena que mostrara el usuario.
		   static int CompareByLongitudHiloItem(HiloItem^ a, HiloItem^ b) {
			   return a->Texto->Length - b->Texto->Length;
		   }

		   // Ordena por orden alfabetico de la misma forma que el de contacto, con la tabla ascii ignorando las mayusculas y minusculas 
		   static int CompareByAlfabeticoHiloItem(HiloItem^ a, HiloItem^ b) {
			   return String::Compare(a->Texto, b->Texto, StringComparison::OrdinalIgnoreCase);
		   }


	public:
		// Aca declaro todos los metodos necesarios para iniciar el programa 

		// Listausuarios controla la mayoria de acciones, guardar, cargar, agregar, etc. 
		static Listausuarios^ lista = gcnew Listausuarios();
		// Cada nodo tendra una persona, a partir de la lista, en el nodo se almacena la persona que esta actualmente LOGGED IN
		static Nodo^ x;

		// Sticker path funciona agarrado el path de la computadora, para poder mandar un sticker (Imagen)
	private: String^ stickerPath = nullptr;
		   // Bandera para validar si se ha mandado un sticker 
	private: bool validarSticker = false;
		   // La parte mas escencial del codigo, el Watcher. Lo que hace el watcher es leer los cambios en el archivo asi poder 
		   // Mantener conversaciones en tiempo "real" entre dos o mas usuarios, cada cosa nueva que haga un usuario se refleja en el otro usuario 

	private:System::IO::FileSystemWatcher^ watcher;
	private:
		// Metodos que actualizan la interfaz 
		void PopulateListBox6(List<HiloItem^>^ hilo)
		{
			listBox6->BeginUpdate();
			listBox6->Items->Clear();
			for each (auto hi in hilo)
				listBox6->Items->Add(hi);
			listBox6->EndUpdate();
		}
		void RefreshChatContacts()
		{
			listBox4->BeginUpdate();
			listBox4->Items->Clear();
			x->persona->GetListaContactos()->OrdenarPorUsername();
			x->persona->GetListaContactos()->agregarList(listBox4);
			listBox4->EndUpdate();
		}

		void RefreshChatMessages()
		{
			listBox5->BeginUpdate();
			listBox5->Items->Clear();
			if (listBox4->SelectedItem != nullptr)
			{
				Persona^ sel = safe_cast<Persona^>(listBox4->SelectedItem);
				MostrarHilo(sel);
			}
			listBox5->EndUpdate();
		}
		void RefreshAllDisplays() {
			if (x == nullptr || x->persona == nullptr) return;
			RefreshAllUsuarios();         // listBox2
			RefreshContactos();           // listBox1
			RefreshSolicitudesRecibidas();// listBox3
			RefreshChatContacts();        // listBox4
			RefreshChatMessages();        // listBox5
		}


		void RefreshAllUsuarios() {
			listBox2->BeginUpdate();
			listBox2->Items->Clear();
			for each (Persona ^ p in lista->GetAllUsuarios()) {
				// solo usuarios distintos al actual para no exista la posibilidad de agregarse a si mismo en la lista de usuarios existente 
				if (x && p->GetNombreUsuario() == x->persona->GetNombreUsuario())
					continue;
				listBox2->Items->Add(p);
			}
			listBox2->EndUpdate();
		}
		void RefreshContactos()
		{
			if (x == nullptr || x->persona == nullptr) return;
			listBox1->BeginUpdate();
			listBox1->Items->Clear();
			x->persona->GetListaContactos()->OrdenarPorUsername();
			x->persona->GetListaContactos()->agregarList(listBox1);
			listBox1->EndUpdate();
		}

		void RefreshSolicitudesRecibidas()
		{
			if (x == nullptr || x->persona == nullptr) return;
			listBox3->BeginUpdate();
			listBox3->Items->Clear();
			x->persona->GetSolicitudesRecibidas()->OrdenarPorUsername();
			x->persona->GetSolicitudesRecibidas()->agregarList(listBox3);
			listBox3->EndUpdate();
		}
		void SaveAndRefreshAll()
		{
			// Guardar en disco SIN disparar el watcher
			if (watcher) watcher->EnableRaisingEvents = false;
			lista->GuardarEnArchivo();
			if (watcher) watcher->EnableRaisingEvents = true;

			// Refrescar Toda la interfaz y guardar cambios 
			RefreshAllDisplays();
		}
	private: System::Windows::Forms::Panel^ PanelEliminarPErf;
	public:


	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ Eliminar;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::CheckBox^ checkBox2;

	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::Button^ button13;
	private: System::Windows::Forms::TextBox^ textBox12;
	private: System::Windows::Forms::PictureBox^ pictureBox7;
	private: System::Windows::Forms::Panel^ panel6;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Button^ button14;
	private: System::Windows::Forms::TextBox^ textBox13;
	private: System::Windows::Forms::Button^ button15;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::TextBox^ textBox14;
	private: System::Windows::Forms::PictureBox^ pictureBox8;
	private: System::Windows::Forms::ListBox^ listBox2;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label30;
	private: System::Windows::Forms::Panel^ panel7;
	private: System::Windows::Forms::PictureBox^ pictureBox9;
	private: System::Windows::Forms::Label^ label31;
	private: System::Windows::Forms::Panel^ panel9;
	private: System::Windows::Forms::Panel^ panel8;
	private: System::Windows::Forms::Panel^ panel11;
	private: System::Windows::Forms::Panel^ panel10;
	private: System::Windows::Forms::Panel^ SolicitudesPanel;
	private: System::Windows::Forms::TextBox^ textBox15;
	private: System::Windows::Forms::PictureBox^ pictureBox10;
	private: System::Windows::Forms::Button^ button17;
	private: System::Windows::Forms::Button^ button16;
	private: System::Windows::Forms::ListBox^ listBox3;
	private: System::Windows::Forms::LinkLabel^ linkLabel2;
	private: System::Windows::Forms::Panel^ OlvidastePanel;

	private: System::Windows::Forms::Label^ label33;
	private: System::Windows::Forms::Label^ label34;
	private: System::Windows::Forms::TextBox^ textBox16;
	private: System::Windows::Forms::Label^ label35;
	private: System::Windows::Forms::TextBox^ textBox17;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::TextBox^ textBox18;
	private: System::Windows::Forms::Button^ button18;
	private: System::Windows::Forms::Label^ label37;
	private: System::Windows::Forms::TextBox^ textBox19;
	private: System::Windows::Forms::Button^ button19;
	private: System::Windows::Forms::Panel^ panelChats;
	private: System::Windows::Forms::ListBox^ listBox5;
	private: System::Windows::Forms::ListBox^ listBox4;
	private: System::Windows::Forms::Label^ label38;
	private: System::Windows::Forms::Button^ button20;
	private: System::Windows::Forms::TextBox^ textBox20;
	private: System::Windows::Forms::Label^ label39;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::PictureBox^ pictureBox11;
	private: System::Windows::Forms::PictureBox^ pictureBox12;
	private: System::Windows::Forms::Button^ button21;
	private: System::Windows::Forms::Panel^ PanelHistorial;
	private: System::Windows::Forms::Label^ label40;
	private: System::Windows::Forms::Label^ label41;
	private: System::Windows::Forms::Button^ button25;
	private: System::Windows::Forms::Button^ button24;
	private: System::Windows::Forms::Label^ label42;
	private: System::Windows::Forms::Button^ button23;
	private: System::Windows::Forms::Button^ button22;
	private: System::Windows::Forms::TextBox^ textBox21;
	private: System::Windows::Forms::ListBox^ listBox6;
	private: System::Windows::Forms::PictureBox^ pictureBox13;
	private: System::Windows::Forms::Label^ label32;
	public:

		MyForm(void)
		{

			InitializeComponent();
			// se crea un nuevo objeto FileSystemWatcher que vigilará cambios en el sistema de archivos.
			watcher = gcnew FileSystemWatcher();
			// Le decimos que ruta vigilar que es en la que se esta ejectuando la aplicacion 
			watcher->Path = Application::StartupPath;
			// Solo va a reaccionar a cambios en este archivo 
			watcher->Filter = "usuarios.dat";
			// Va a notificar solo estos datos especificado  modificaciones del contenido renombrados y creacion de archivo 
			watcher->NotifyFilter = NotifyFilters::LastWrite | NotifyFilters::FileName | NotifyFilters::CreationTime;

			// Si ocurre uno de los eventos mencionados se llaman a los metodos mas adelante creados, 
			watcher->Changed += gcnew FileSystemEventHandler(this, &MyForm::OnUsuariosFileChanged);
			watcher->Created += gcnew FileSystemEventHandler(this, &MyForm::OnUsuariosFileChanged);
			watcher->Renamed += gcnew RenamedEventHandler(this, &MyForm::OnUsuariosFileRenamed);
			// Sincroniza todos los cambios en la interfaz 
			watcher->SynchronizingObject = this;
			// Finalmente se dispara luego de estar bien configurada 
			watcher->EnableRaisingEvents = true;

			lista = gcnew Listausuarios();
			lista->CargarDesdeArchivo();
			// Esta linea esta en varios lados del codigo para asegurarme que no se pierdan los datos del usuario actual 
			if (!String::IsNullOrEmpty(currentU)) {
				x = lista->BuscarPersona(currentU, 1);
			}
			// Se refrescan todos los listboxes 
			RefreshAllDisplays();
			// Evento para manejar el formclosing solamente utilizado para guardar los datos si el usuario cierra el programa presionando la x 
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);


			// Todas estas asignaciones son puramente esteticas para los listboxes y Color de los paneles 
			this->listBox1->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox_DrawItem);
			this->listBox2->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox_DrawItem);
			this->listBox3->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox_DrawItem);

			listBox5->DrawMode = DrawMode::OwnerDrawFixed;
			listBox5->ItemHeight = 30;
			listBox5->Font = gcnew System::Drawing::Font("Segoe UI", 10);
			listBox5->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox5_DrawItem);



			listBox6->DrawMode = DrawMode::OwnerDrawFixed;
			listBox6->ItemHeight = 30;
			listBox6->Font = gcnew System::Drawing::Font("Segoe UI", 10);
			listBox6->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox5_DrawItem);


			Color myColor = Color::FromArgb(0x07, 0x9d, 0xa7);

			panel2->BackColor = myColor;
			panel3->BackColor = myColor;
			panel4->BackColor = myColor;

			System::Drawing::Color myColor2 = System::Drawing::Color::FromArgb(0x01, 0x52, 0x58);

			EditarPanel->BackColor = myColor2;
			PanelEliminarPErf->BackColor = myColor2;
			panel1->BackColor = myColor2;
			panel5->BackColor = myColor2;
			panel6->BackColor = myColor2;
			SolicitudesPanel->BackColor = myColor2;
			OlvidastePanel->BackColor = myColor2;
			panelChats->BackColor = myColor2;

			listBox1->BackColor = myColor;
			listBox1->DrawMode = DrawMode::OwnerDrawFixed;
			listBox1->ItemHeight = 40;
			listBox1->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);

			listBox2->BackColor = myColor;
			listBox2->DrawMode = DrawMode::OwnerDrawFixed;
			listBox2->ItemHeight = 40;
			listBox2->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);

			listBox3->BackColor = myColor;
			listBox3->DrawMode = DrawMode::OwnerDrawFixed;
			listBox3->ItemHeight = 40;
			listBox3->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);

			this->listBox4->DrawMode = DrawMode::OwnerDrawFixed;
			this->listBox4->ItemHeight = 40;
			this->listBox4->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			this->listBox4->BackColor = myColor;
			this->listBox4->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox4_DrawItem);

			listBox5->Items->Clear();
			listBox4->Items->Clear();
			listBox6->Items->Clear();
			textBox20->BackColor = myColor;
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel2;
	protected:

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::LinkLabel^ linkLabel1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ ContraText;
	private: System::Windows::Forms::TextBox^ UsuarioText;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ Respuesta;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ Edad;
	private: System::Windows::Forms::TextBox^ Validarcontra;
	private: System::Windows::Forms::TextBox^ Contra;
	private: System::Windows::Forms::TextBox^ Correo;
	private: System::Windows::Forms::TextBox^ NomCompleto;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ NomUsuario;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::ComboBox^ Combopregunta;
	private: System::Windows::Forms::PictureBox^ ImagenPerf;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ LabelNombre;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::ContextMenuStrip^ Menu;
	private: System::Windows::Forms::ToolStripMenuItem^ personalizarPerfilToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ eliminarPerfilToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ cerrarSesionToolStripMenuItem;
	private: System::Windows::Forms::Panel^ EditarPanel;

	private: System::Windows::Forms::Label^ label13;


	private: System::Windows::Forms::PictureBox^ pictureBox6;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button9;
	private: System::ComponentModel::IContainer^ components;


	protected:



	private:

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->OlvidastePanel = (gcnew System::Windows::Forms::Panel());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->linkLabel2 = (gcnew System::Windows::Forms::LinkLabel());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->ContraText = (gcnew System::Windows::Forms::TextBox());
			this->UsuarioText = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->PanelHistorial = (gcnew System::Windows::Forms::Panel());
			this->button25 = (gcnew System::Windows::Forms::Button());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->listBox6 = (gcnew System::Windows::Forms::ListBox());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->panelChats = (gcnew System::Windows::Forms::Panel());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->listBox5 = (gcnew System::Windows::Forms::ListBox());
			this->listBox4 = (gcnew System::Windows::Forms::ListBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->SolicitudesPanel = (gcnew System::Windows::Forms::Panel());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->EditarPanel = (gcnew System::Windows::Forms::Panel());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->PanelEliminarPErf = (gcnew System::Windows::Forms::Panel());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->Eliminar = (gcnew System::Windows::Forms::Button());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->panel10 = (gcnew System::Windows::Forms::Panel());
			this->panel9 = (gcnew System::Windows::Forms::Panel());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->LabelNombre = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->Respuesta = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->Edad = (gcnew System::Windows::Forms::TextBox());
			this->Validarcontra = (gcnew System::Windows::Forms::TextBox());
			this->Contra = (gcnew System::Windows::Forms::TextBox());
			this->Correo = (gcnew System::Windows::Forms::TextBox());
			this->NomCompleto = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->NomUsuario = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->Combopregunta = (gcnew System::Windows::Forms::ComboBox());
			this->ImagenPerf = (gcnew System::Windows::Forms::PictureBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->Menu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->personalizarPerfilToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eliminarPerfilToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cerrarSesionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel2->SuspendLayout();
			this->OlvidastePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->panel4->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panel5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			this->panel6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			this->PanelHistorial->SuspendLayout();
			this->panelChats->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			this->SolicitudesPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			this->EditarPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			this->PanelEliminarPErf->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->panel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImagenPerf))->BeginInit();
			this->Menu->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panel2->Controls->Add(this->OlvidastePanel);
			this->panel2->Controls->Add(this->linkLabel2);
			this->panel2->Controls->Add(this->label31);
			this->panel2->Controls->Add(this->pictureBox9);
			this->panel2->Controls->Add(this->label30);
			this->panel2->Controls->Add(this->panel7);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->linkLabel1);
			this->panel2->Controls->Add(this->pictureBox2);
			this->panel2->Controls->Add(this->pictureBox1);
			this->panel2->Controls->Add(this->button1);
			this->panel2->Controls->Add(this->ContraText);
			this->panel2->Controls->Add(this->UsuarioText);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1021, 573);
			this->panel2->TabIndex = 1;
			// 
			// OlvidastePanel
			// 
			this->OlvidastePanel->Controls->Add(this->button19);
			this->OlvidastePanel->Controls->Add(this->button18);
			this->OlvidastePanel->Controls->Add(this->label34);
			this->OlvidastePanel->Controls->Add(this->textBox16);
			this->OlvidastePanel->Controls->Add(this->label35);
			this->OlvidastePanel->Controls->Add(this->textBox17);
			this->OlvidastePanel->Controls->Add(this->label36);
			this->OlvidastePanel->Controls->Add(this->textBox18);
			this->OlvidastePanel->Controls->Add(this->label37);
			this->OlvidastePanel->Controls->Add(this->textBox19);
			this->OlvidastePanel->Controls->Add(this->label33);
			this->OlvidastePanel->Location = System::Drawing::Point(0, 1);
			this->OlvidastePanel->Margin = System::Windows::Forms::Padding(2);
			this->OlvidastePanel->Name = L"OlvidastePanel";
			this->OlvidastePanel->Size = System::Drawing::Size(682, 567);
			this->OlvidastePanel->TabIndex = 14;
			this->OlvidastePanel->Visible = false;
			// 
			// button19
			// 
			this->button19->BackColor = System::Drawing::Color::AliceBlue;
			this->button19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button19->ForeColor = System::Drawing::Color::Gray;
			this->button19->Location = System::Drawing::Point(353, 366);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(192, 52);
			this->button19->TabIndex = 32;
			this->button19->Text = L"Cancelar";
			this->button19->UseVisualStyleBackColor = false;
			this->button19->Click += gcnew System::EventHandler(this, &MyForm::button19_Click);
			// 
			// button18
			// 
			this->button18->BackColor = System::Drawing::Color::AliceBlue;
			this->button18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button18->ForeColor = System::Drawing::Color::Gray;
			this->button18->Location = System::Drawing::Point(125, 367);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(192, 52);
			this->button18->TabIndex = 31;
			this->button18->Text = L"Restaurar Contraseña";
			this->button18->UseVisualStyleBackColor = false;
			this->button18->Click += gcnew System::EventHandler(this, &MyForm::button18_Click);
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label34->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label34->Location = System::Drawing::Point(351, 229);
			this->label34->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(66, 13);
			this->label34->TabIndex = 30;
			this->label34->Text = L"Respuesta: \r\n";
			// 
			// textBox16
			// 
			this->textBox16->Enabled = false;
			this->textBox16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox16->Location = System::Drawing::Point(434, 187);
			this->textBox16->Margin = System::Windows::Forms::Padding(2);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(193, 21);
			this->textBox16->TabIndex = 29;
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label35->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label35->Location = System::Drawing::Point(368, 189);
			this->label35->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(40, 13);
			this->label35->TabIndex = 28;
			this->label35->Text = L"Frase: \r\n";
			// 
			// textBox17
			// 
			this->textBox17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox17->Location = System::Drawing::Point(434, 227);
			this->textBox17->Margin = System::Windows::Forms::Padding(2);
			this->textBox17->Multiline = true;
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(193, 69);
			this->textBox17->TabIndex = 27;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label36->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label36->Location = System::Drawing::Point(21, 241);
			this->label36->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(123, 13);
			this->label36->TabIndex = 26;
			this->label36->Text = L"Confirmar Contraseña:\r\n";
			// 
			// textBox18
			// 
			this->textBox18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox18->Location = System::Drawing::Point(155, 240);
			this->textBox18->Margin = System::Windows::Forms::Padding(2);
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(137, 21);
			this->textBox18->TabIndex = 25;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label37->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label37->Location = System::Drawing::Point(21, 189);
			this->label37->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(101, 13);
			this->label37->TabIndex = 24;
			this->label37->Text = L"Contraseña Nueva";
			// 
			// textBox19
			// 
			this->textBox19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox19->Location = System::Drawing::Point(155, 190);
			this->textBox19->Margin = System::Windows::Forms::Padding(2);
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(137, 21);
			this->textBox19->TabIndex = 23;
			// 
			// label33
			// 
			this->label33->BackColor = System::Drawing::Color::Transparent;
			this->label33->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label33->ForeColor = System::Drawing::SystemColors::Menu;
			this->label33->Location = System::Drawing::Point(209, 46);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(416, 49);
			this->label33->TabIndex = 11;
			this->label33->Text = L"Recupera tu cuenta";
			// 
			// linkLabel2
			// 
			this->linkLabel2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linkLabel2->Location = System::Drawing::Point(766, 379);
			this->linkLabel2->Name = L"linkLabel2";
			this->linkLabel2->Size = System::Drawing::Size(250, 28);
			this->linkLabel2->TabIndex = 13;
			this->linkLabel2->TabStop = true;
			this->linkLabel2->Text = L"Olvidaste tu contraseña\?";
			this->linkLabel2->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::linkLabel2_LinkClicked);
			// 
			// label31
			// 
			this->label31->BackColor = System::Drawing::Color::Transparent;
			this->label31->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label31->ForeColor = System::Drawing::SystemColors::Menu;
			this->label31->Location = System::Drawing::Point(104, 466);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(504, 49);
			this->label31->TabIndex = 12;
			this->label31->Text = L"Conecta. Comparte. Chatee.";
			// 
			// pictureBox9
			// 
			this->pictureBox9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.Image")));
			this->pictureBox9->Location = System::Drawing::Point(187, 136);
			this->pictureBox9->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(266, 291);
			this->pictureBox9->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox9->TabIndex = 11;
			this->pictureBox9->TabStop = false;
			// 
			// label30
			// 
			this->label30->BackColor = System::Drawing::Color::Transparent;
			this->label30->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label30->ForeColor = System::Drawing::SystemColors::Menu;
			this->label30->Location = System::Drawing::Point(148, 24);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(364, 49);
			this->label30->TabIndex = 10;
			this->label30->Text = L"Bienvenido a Chatee";
			// 
			// panel7
			// 
			this->panel7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel7->Location = System::Drawing::Point(678, 2);
			this->panel7->Margin = System::Windows::Forms::Padding(2);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(20, 570);
			this->panel7->TabIndex = 9;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::Menu;
			this->label2->Location = System::Drawing::Point(751, 415);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(270, 49);
			this->label2->TabIndex = 8;
			this->label2->Text = L"No tienes una cuenta\? ";
			// 
			// linkLabel1
			// 
			this->linkLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linkLabel1->Location = System::Drawing::Point(827, 466);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(85, 28);
			this->linkLabel1->TabIndex = 7;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"Registrate";
			this->linkLabel1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::linkLabel1_MouseClick);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->Location = System::Drawing::Point(711, 220);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(40, 41);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 6;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->Location = System::Drawing::Point(711, 134);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(40, 38);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::AliceBlue;
			this->button1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::Gray;
			this->button1->Location = System::Drawing::Point(769, 306);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(192, 52);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Log in";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// ContraText
			// 
			this->ContraText->AcceptsTab = true;
			this->ContraText->BackColor = System::Drawing::Color::AliceBlue;
			this->ContraText->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ContraText->ForeColor = System::Drawing::Color::Gray;
			this->ContraText->Location = System::Drawing::Point(769, 220);
			this->ContraText->Multiline = true;
			this->ContraText->Name = L"ContraText";
			this->ContraText->Size = System::Drawing::Size(192, 52);
			this->ContraText->TabIndex = 2;
			this->ContraText->Text = L"Contraseña";
			this->ContraText->MouseEnter += gcnew System::EventHandler(this, &MyForm::textBox2_MouseEnter);
			this->ContraText->MouseLeave += gcnew System::EventHandler(this, &MyForm::textBox2_MouseLeave);
			// 
			// UsuarioText
			// 
			this->UsuarioText->AcceptsTab = true;
			this->UsuarioText->BackColor = System::Drawing::Color::AliceBlue;
			this->UsuarioText->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->UsuarioText->ForeColor = System::Drawing::Color::Gray;
			this->UsuarioText->Location = System::Drawing::Point(769, 132);
			this->UsuarioText->Multiline = true;
			this->UsuarioText->Name = L"UsuarioText";
			this->UsuarioText->Size = System::Drawing::Size(192, 52);
			this->UsuarioText->TabIndex = 1;
			this->UsuarioText->Text = L"Usuario";
			this->UsuarioText->MouseEnter += gcnew System::EventHandler(this, &MyForm::textBox1_MouseEnter);
			this->UsuarioText->MouseLeave += gcnew System::EventHandler(this, &MyForm::textBox1_MouseLeave);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::Menu;
			this->label1->Location = System::Drawing::Point(800, 52);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(126, 49);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Login";
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panel4->Controls->Add(this->panel1);
			this->panel4->Controls->Add(this->PanelHistorial);
			this->panel4->Controls->Add(this->panelChats);
			this->panel4->Controls->Add(this->SolicitudesPanel);
			this->panel4->Controls->Add(this->button21);
			this->panel4->Controls->Add(this->EditarPanel);
			this->panel4->Controls->Add(this->PanelEliminarPErf);
			this->panel4->Controls->Add(this->panel11);
			this->panel4->Controls->Add(this->panel10);
			this->panel4->Controls->Add(this->panel9);
			this->panel4->Controls->Add(this->panel8);
			this->panel4->Controls->Add(this->checkBox1);
			this->panel4->Controls->Add(this->button7);
			this->panel4->Controls->Add(this->pictureBox4);
			this->panel4->Controls->Add(this->button5);
			this->panel4->Controls->Add(this->button4);
			this->panel4->Controls->Add(this->LabelNombre);
			this->panel4->Controls->Add(this->pictureBox3);
			this->panel4->Location = System::Drawing::Point(0, 0);
			this->panel4->Margin = System::Windows::Forms::Padding(2);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(1021, 573);
			this->panel4->TabIndex = 28;
			this->panel4->Visible = false;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panel1->Controls->Add(this->panel5);
			this->panel1->Controls->Add(this->panel6);
			this->panel1->Controls->Add(this->pictureBox7);
			this->panel1->Controls->Add(this->label25);
			this->panel1->Controls->Add(this->button10);
			this->panel1->Controls->Add(this->button11);
			this->panel1->Location = System::Drawing::Point(265, 107);
			this->panel1->Margin = System::Windows::Forms::Padding(2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(734, 441);
			this->panel1->TabIndex = 23;
			this->panel1->Visible = false;
			// 
			// panel5
			// 
			this->panel5->Controls->Add(this->pictureBox5);
			this->panel5->Controls->Add(this->label27);
			this->panel5->Controls->Add(this->label26);
			this->panel5->Controls->Add(this->button13);
			this->panel5->Controls->Add(this->textBox12);
			this->panel5->Controls->Add(this->button12);
			this->panel5->Controls->Add(this->checkBox2);
			this->panel5->Controls->Add(this->textBox11);
			this->panel5->Controls->Add(this->listBox1);
			this->panel5->Location = System::Drawing::Point(185, 9);
			this->panel5->Margin = System::Windows::Forms::Padding(2);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(549, 422);
			this->panel5->TabIndex = 10;
			this->panel5->Visible = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Enabled = false;
			this->pictureBox5->Location = System::Drawing::Point(357, 67);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(108, 92);
			this->pictureBox5->TabIndex = 20;
			this->pictureBox5->TabStop = false;
			// 
			// label27
			// 
			this->label27->BackColor = System::Drawing::Color::Transparent;
			this->label27->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->ForeColor = System::Drawing::SystemColors::Menu;
			this->label27->Location = System::Drawing::Point(325, 27);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(220, 28);
			this->label27->TabIndex = 19;
			this->label27->Text = L"Contactos Agregados";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label26->Location = System::Drawing::Point(8, 19);
			this->label26->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(112, 13);
			this->label26->TabIndex = 18;
			this->label26->Text = L"Nombre de Usuario:\r\n";
			// 
			// button13
			// 
			this->button13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button13->Location = System::Drawing::Point(155, 44);
			this->button13->Margin = System::Windows::Forms::Padding(2);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(97, 28);
			this->button13->TabIndex = 17;
			this->button13->Text = L"Buscar";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &MyForm::button13_Click);
			// 
			// textBox12
			// 
			this->textBox12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox12->Location = System::Drawing::Point(10, 48);
			this->textBox12->Margin = System::Windows::Forms::Padding(2);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(109, 21);
			this->textBox12->TabIndex = 16;
			// 
			// button12
			// 
			this->button12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button12->Location = System::Drawing::Point(358, 304);
			this->button12->Margin = System::Windows::Forms::Padding(2);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(108, 43);
			this->button12->TabIndex = 15;
			this->button12->Text = L"Eliminar";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->checkBox2->Enabled = false;
			this->checkBox2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->checkBox2->Location = System::Drawing::Point(354, 246);
			this->checkBox2->Margin = System::Windows::Forms::Padding(2);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(15, 14);
			this->checkBox2->TabIndex = 14;
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// textBox11
			// 
			this->textBox11->Enabled = false;
			this->textBox11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox11->Location = System::Drawing::Point(358, 193);
			this->textBox11->Margin = System::Windows::Forms::Padding(2);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(109, 21);
			this->textBox11->TabIndex = 13;
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Location = System::Drawing::Point(9, 94);
			this->listBox1->Margin = System::Windows::Forms::Padding(2);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(277, 304);
			this->listBox1->TabIndex = 11;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// panel6
			// 
			this->panel6->Controls->Add(this->label28);
			this->panel6->Controls->Add(this->label29);
			this->panel6->Controls->Add(this->button14);
			this->panel6->Controls->Add(this->textBox13);
			this->panel6->Controls->Add(this->button15);
			this->panel6->Controls->Add(this->checkBox3);
			this->panel6->Controls->Add(this->textBox14);
			this->panel6->Controls->Add(this->pictureBox8);
			this->panel6->Controls->Add(this->listBox2);
			this->panel6->Location = System::Drawing::Point(185, 10);
			this->panel6->Margin = System::Windows::Forms::Padding(2);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(549, 421);
			this->panel6->TabIndex = 20;
			// 
			// label28
			// 
			this->label28->BackColor = System::Drawing::Color::Transparent;
			this->label28->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->ForeColor = System::Drawing::SystemColors::Menu;
			this->label28->Location = System::Drawing::Point(338, 20);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(170, 28);
			this->label28->TabIndex = 19;
			this->label28->Text = L"Agregar Contactos";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label29->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label29->Location = System::Drawing::Point(8, 19);
			this->label29->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(112, 13);
			this->label29->TabIndex = 18;
			this->label29->Text = L"Nombre de Usuario:\r\n";
			// 
			// button14
			// 
			this->button14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button14->Location = System::Drawing::Point(155, 44);
			this->button14->Margin = System::Windows::Forms::Padding(2);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(97, 28);
			this->button14->TabIndex = 17;
			this->button14->Text = L"Buscar";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &MyForm::button14_Click);
			// 
			// textBox13
			// 
			this->textBox13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox13->Location = System::Drawing::Point(10, 48);
			this->textBox13->Margin = System::Windows::Forms::Padding(2);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(109, 21);
			this->textBox13->TabIndex = 16;
			// 
			// button15
			// 
			this->button15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button15->Location = System::Drawing::Point(358, 304);
			this->button15->Margin = System::Windows::Forms::Padding(2);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(108, 43);
			this->button15->TabIndex = 15;
			this->button15->Text = L"Mandar Solicitud";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &MyForm::button15_Click);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->checkBox3->Enabled = false;
			this->checkBox3->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->checkBox3->Location = System::Drawing::Point(354, 246);
			this->checkBox3->Margin = System::Windows::Forms::Padding(2);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(15, 14);
			this->checkBox3->TabIndex = 14;
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// textBox14
			// 
			this->textBox14->Enabled = false;
			this->textBox14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox14->Location = System::Drawing::Point(358, 193);
			this->textBox14->Margin = System::Windows::Forms::Padding(2);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(109, 21);
			this->textBox14->TabIndex = 13;
			// 
			// pictureBox8
			// 
			this->pictureBox8->Location = System::Drawing::Point(358, 74);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(108, 92);
			this->pictureBox8->TabIndex = 12;
			this->pictureBox8->TabStop = false;
			// 
			// listBox2
			// 
			this->listBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 12;
			this->listBox2->Location = System::Drawing::Point(9, 94);
			this->listBox2->Margin = System::Windows::Forms::Padding(2);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(277, 304);
			this->listBox2->TabIndex = 11;
			this->listBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox2_SelectedIndexChanged);
			// 
			// pictureBox7
			// 
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(69, 325);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(38, 41);
			this->pictureBox7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox7->TabIndex = 11;
			this->pictureBox7->TabStop = false;
			this->pictureBox7->Click += gcnew System::EventHandler(this, &MyForm::pictureBox7_Click);
			// 
			// label25
			// 
			this->label25->BackColor = System::Drawing::Color::Transparent;
			this->label25->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label25->ForeColor = System::Drawing::SystemColors::Menu;
			this->label25->Location = System::Drawing::Point(3, 7);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(173, 50);
			this->label25->TabIndex = 9;
			this->label25->Text = L"Contactos";
			// 
			// button10
			// 
			this->button10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button10->Location = System::Drawing::Point(11, 240);
			this->button10->Margin = System::Windows::Forms::Padding(2);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(148, 43);
			this->button10->TabIndex = 8;
			this->button10->Text = L"Agregar";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// button11
			// 
			this->button11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button11->Location = System::Drawing::Point(10, 150);
			this->button11->Margin = System::Windows::Forms::Padding(2);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(148, 43);
			this->button11->TabIndex = 7;
			this->button11->Text = L"Ver Contactos";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click);
			// 
			// PanelHistorial
			// 
			this->PanelHistorial->Controls->Add(this->button25);
			this->PanelHistorial->Controls->Add(this->button24);
			this->PanelHistorial->Controls->Add(this->label42);
			this->PanelHistorial->Controls->Add(this->button23);
			this->PanelHistorial->Controls->Add(this->button22);
			this->PanelHistorial->Controls->Add(this->textBox21);
			this->PanelHistorial->Controls->Add(this->listBox6);
			this->PanelHistorial->Controls->Add(this->label41);
			this->PanelHistorial->Controls->Add(this->label40);
			this->PanelHistorial->Location = System::Drawing::Point(265, 106);
			this->PanelHistorial->Name = L"PanelHistorial";
			this->PanelHistorial->Size = System::Drawing::Size(734, 443);
			this->PanelHistorial->TabIndex = 30;
			this->PanelHistorial->Visible = false;
			// 
			// button25
			// 
			this->button25->Location = System::Drawing::Point(58, 374);
			this->button25->Name = L"button25";
			this->button25->Size = System::Drawing::Size(137, 38);
			this->button25->TabIndex = 24;
			this->button25->Text = L"Longitud";
			this->button25->UseVisualStyleBackColor = true;
			this->button25->Click += gcnew System::EventHandler(this, &MyForm::button25_Click);
			// 
			// button24
			// 
			this->button24->Location = System::Drawing::Point(58, 309);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(137, 38);
			this->button24->TabIndex = 23;
			this->button24->Text = L"Alfabetico";
			this->button24->UseVisualStyleBackColor = true;
			this->button24->Click += gcnew System::EventHandler(this, &MyForm::button24_Click);
			// 
			// label42
			// 
			this->label42->BackColor = System::Drawing::Color::Transparent;
			this->label42->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label42->ForeColor = System::Drawing::SystemColors::MenuBar;
			this->label42->Location = System::Drawing::Point(17, 171);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(277, 50);
			this->label42->TabIndex = 22;
			this->label42->Text = L"Ordenar Por:";
			// 
			// button23
			// 
			this->button23->Location = System::Drawing::Point(58, 252);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(137, 38);
			this->button23->TabIndex = 21;
			this->button23->Text = L"Fecha";
			this->button23->UseVisualStyleBackColor = true;
			this->button23->Click += gcnew System::EventHandler(this, &MyForm::button23_Click);
			// 
			// button22
			// 
			this->button22->Location = System::Drawing::Point(9, 99);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(101, 20);
			this->button22->TabIndex = 20;
			this->button22->Text = L"Buscar Palabra";
			this->button22->UseVisualStyleBackColor = true;
			this->button22->Click += gcnew System::EventHandler(this, &MyForm::button22_Click);
			// 
			// textBox21
			// 
			this->textBox21->Location = System::Drawing::Point(122, 100);
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(147, 20);
			this->textBox21->TabIndex = 19;
			// 
			// listBox6
			// 
			this->listBox6->FormattingEnabled = true;
			this->listBox6->Location = System::Drawing::Point(304, 82);
			this->listBox6->Name = L"listBox6";
			this->listBox6->Size = System::Drawing::Size(416, 329);
			this->listBox6->TabIndex = 18;
			// 
			// label41
			// 
			this->label41->BackColor = System::Drawing::Color::Transparent;
			this->label41->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label41->ForeColor = System::Drawing::SystemColors::MenuBar;
			this->label41->Location = System::Drawing::Point(315, 8);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(419, 50);
			this->label41->TabIndex = 17;
			this->label41->Text = L"Todos Los Mensajes";
			// 
			// label40
			// 
			this->label40->BackColor = System::Drawing::Color::Transparent;
			this->label40->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label40->ForeColor = System::Drawing::SystemColors::MenuBar;
			this->label40->Location = System::Drawing::Point(50, 7);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(173, 50);
			this->label40->TabIndex = 16;
			this->label40->Text = L"Historial";
			// 
			// panelChats
			// 
			this->panelChats->Controls->Add(this->pictureBox13);
			this->panelChats->Controls->Add(this->pictureBox12);
			this->panelChats->Controls->Add(this->pictureBox11);
			this->panelChats->Controls->Add(this->label39);
			this->panelChats->Controls->Add(this->button20);
			this->panelChats->Controls->Add(this->textBox20);
			this->panelChats->Controls->Add(this->listBox5);
			this->panelChats->Controls->Add(this->listBox4);
			this->panelChats->Controls->Add(this->label38);
			this->panelChats->Location = System::Drawing::Point(265, 107);
			this->panelChats->Margin = System::Windows::Forms::Padding(2);
			this->panelChats->Name = L"panelChats";
			this->panelChats->Size = System::Drawing::Size(734, 441);
			this->panelChats->TabIndex = 28;
			this->panelChats->Visible = false;
			// 
			// pictureBox13
			// 
			this->pictureBox13->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox13.Image")));
			this->pictureBox13->Location = System::Drawing::Point(537, 384);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(56, 46);
			this->pictureBox13->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox13->TabIndex = 18;
			this->pictureBox13->TabStop = false;
			this->pictureBox13->Click += gcnew System::EventHandler(this, &MyForm::pictureBox13_Click);
			// 
			// pictureBox12
			// 
			this->pictureBox12->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox12.Image")));
			this->pictureBox12->Location = System::Drawing::Point(638, 27);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(41, 34);
			this->pictureBox12->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox12->TabIndex = 17;
			this->pictureBox12->TabStop = false;
			this->pictureBox12->Click += gcnew System::EventHandler(this, &MyForm::pictureBox12_Click);
			// 
			// pictureBox11
			// 
			this->pictureBox11->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox11.Image")));
			this->pictureBox11->Location = System::Drawing::Point(685, 26);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(41, 34);
			this->pictureBox11->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox11->TabIndex = 16;
			this->pictureBox11->TabStop = false;
			this->pictureBox11->Click += gcnew System::EventHandler(this, &MyForm::pictureBox11_Click);
			// 
			// label39
			// 
			this->label39->BackColor = System::Drawing::Color::Transparent;
			this->label39->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label39->ForeColor = System::Drawing::SystemColors::Menu;
			this->label39->Location = System::Drawing::Point(23, 10);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(173, 50);
			this->label39->TabIndex = 15;
			this->label39->Text = L"Contactos";
			// 
			// button20
			// 
			this->button20->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button20->Location = System::Drawing::Point(604, 373);
			this->button20->Margin = System::Windows::Forms::Padding(2);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(112, 58);
			this->button20->TabIndex = 14;
			this->button20->Text = L"Enviar";
			this->button20->UseVisualStyleBackColor = true;
			this->button20->Click += gcnew System::EventHandler(this, &MyForm::button20_Click);
			// 
			// textBox20
			// 
			this->textBox20->Location = System::Drawing::Point(306, 371);
			this->textBox20->Margin = System::Windows::Forms::Padding(2);
			this->textBox20->Multiline = true;
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(212, 59);
			this->textBox20->TabIndex = 13;
			// 
			// listBox5
			// 
			this->listBox5->FormattingEnabled = true;
			this->listBox5->Location = System::Drawing::Point(299, 67);
			this->listBox5->Margin = System::Windows::Forms::Padding(2);
			this->listBox5->Name = L"listBox5";
			this->listBox5->Size = System::Drawing::Size(427, 290);
			this->listBox5->TabIndex = 12;
			// 
			// listBox4
			// 
			this->listBox4->FormattingEnabled = true;
			this->listBox4->Location = System::Drawing::Point(26, 67);
			this->listBox4->Margin = System::Windows::Forms::Padding(2);
			this->listBox4->Name = L"listBox4";
			this->listBox4->Size = System::Drawing::Size(222, 316);
			this->listBox4->TabIndex = 11;
			this->listBox4->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox4_SelectedIndexChanged);
			// 
			// label38
			// 
			this->label38->BackColor = System::Drawing::Color::Transparent;
			this->label38->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label38->ForeColor = System::Drawing::SystemColors::Menu;
			this->label38->Location = System::Drawing::Point(422, 5);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(173, 50);
			this->label38->TabIndex = 10;
			this->label38->Text = L"Mensajes";
			// 
			// SolicitudesPanel
			// 
			this->SolicitudesPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->SolicitudesPanel->Controls->Add(this->textBox15);
			this->SolicitudesPanel->Controls->Add(this->pictureBox10);
			this->SolicitudesPanel->Controls->Add(this->button17);
			this->SolicitudesPanel->Controls->Add(this->button16);
			this->SolicitudesPanel->Controls->Add(this->listBox3);
			this->SolicitudesPanel->Controls->Add(this->label32);
			this->SolicitudesPanel->Location = System::Drawing::Point(267, 112);
			this->SolicitudesPanel->Margin = System::Windows::Forms::Padding(2);
			this->SolicitudesPanel->Name = L"SolicitudesPanel";
			this->SolicitudesPanel->Size = System::Drawing::Size(728, 435);
			this->SolicitudesPanel->TabIndex = 23;
			this->SolicitudesPanel->Visible = false;
			// 
			// textBox15
			// 
			this->textBox15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox15->Location = System::Drawing::Point(474, 258);
			this->textBox15->Margin = System::Windows::Forms::Padding(2);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(174, 21);
			this->textBox15->TabIndex = 9;
			// 
			// pictureBox10
			// 
			this->pictureBox10->Location = System::Drawing::Point(466, 112);
			this->pictureBox10->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(171, 81);
			this->pictureBox10->TabIndex = 8;
			this->pictureBox10->TabStop = false;
			// 
			// button17
			// 
			this->button17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button17->Location = System::Drawing::Point(572, 343);
			this->button17->Margin = System::Windows::Forms::Padding(2);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(73, 19);
			this->button17->TabIndex = 7;
			this->button17->Text = L"Rechazar";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &MyForm::button17_Click);
			// 
			// button16
			// 
			this->button16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button16->Location = System::Drawing::Point(474, 343);
			this->button16->Margin = System::Windows::Forms::Padding(2);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(73, 19);
			this->button16->TabIndex = 6;
			this->button16->Text = L"Aceptar";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &MyForm::button16_Click);
			// 
			// listBox3
			// 
			this->listBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox3->FormattingEnabled = true;
			this->listBox3->ItemHeight = 12;
			this->listBox3->Location = System::Drawing::Point(75, 106);
			this->listBox3->Margin = System::Windows::Forms::Padding(2);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(294, 280);
			this->listBox3->TabIndex = 5;
			this->listBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox3_SelectedIndexChanged);
			// 
			// label32
			// 
			this->label32->BackColor = System::Drawing::Color::Transparent;
			this->label32->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label32->ForeColor = System::Drawing::SystemColors::Menu;
			this->label32->Location = System::Drawing::Point(290, 33);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(221, 49);
			this->label32->TabIndex = 4;
			this->label32->Text = L"Solicitudes";
			// 
			// button21
			// 
			this->button21->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button21->Location = System::Drawing::Point(22, 213);
			this->button21->Margin = System::Windows::Forms::Padding(2);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(188, 43);
			this->button21->TabIndex = 29;
			this->button21->Text = L"Historial";
			this->button21->UseVisualStyleBackColor = true;
			this->button21->Click += gcnew System::EventHandler(this, &MyForm::button21_Click);
			// 
			// EditarPanel
			// 
			this->EditarPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->EditarPanel->Controls->Add(this->button9);
			this->EditarPanel->Controls->Add(this->pictureBox6);
			this->EditarPanel->Controls->Add(this->button8);
			this->EditarPanel->Controls->Add(this->label20);
			this->EditarPanel->Controls->Add(this->textBox6);
			this->EditarPanel->Controls->Add(this->label19);
			this->EditarPanel->Controls->Add(this->textBox5);
			this->EditarPanel->Controls->Add(this->label18);
			this->EditarPanel->Controls->Add(this->textBox4);
			this->EditarPanel->Controls->Add(this->label17);
			this->EditarPanel->Controls->Add(this->textBox3);
			this->EditarPanel->Controls->Add(this->label16);
			this->EditarPanel->Controls->Add(this->textBox2);
			this->EditarPanel->Controls->Add(this->label15);
			this->EditarPanel->Controls->Add(this->textBox1);
			this->EditarPanel->Controls->Add(this->label13);
			this->EditarPanel->Location = System::Drawing::Point(266, 108);
			this->EditarPanel->Margin = System::Windows::Forms::Padding(2);
			this->EditarPanel->Name = L"EditarPanel";
			this->EditarPanel->Size = System::Drawing::Size(731, 439);
			this->EditarPanel->TabIndex = 7;
			this->EditarPanel->Visible = false;
			// 
			// button9
			// 
			this->button9->ForeColor = System::Drawing::SystemColors::GrayText;
			this->button9->Location = System::Drawing::Point(320, 340);
			this->button9->Margin = System::Windows::Forms::Padding(2);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(144, 37);
			this->button9->TabIndex = 18;
			this->button9->Text = L"Modificar\r\n";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// pictureBox6
			// 
			this->pictureBox6->Location = System::Drawing::Point(374, 94);
			this->pictureBox6->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(112, 102);
			this->pictureBox6->TabIndex = 17;
			this->pictureBox6->TabStop = false;
			// 
			// button8
			// 
			this->button8->ForeColor = System::Drawing::SystemColors::GrayText;
			this->button8->Location = System::Drawing::Point(398, 210);
			this->button8->Margin = System::Windows::Forms::Padding(2);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(66, 23);
			this->button8->TabIndex = 16;
			this->button8->Text = L"Seleccionar";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label20->Location = System::Drawing::Point(21, 332);
			this->label20->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(36, 13);
			this->label20->TabIndex = 15;
			this->label20->Text = L"Edad:\r\n";
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox6->Location = System::Drawing::Point(141, 331);
			this->textBox6->Margin = System::Windows::Forms::Padding(2);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(137, 21);
			this->textBox6->TabIndex = 14;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label19->Location = System::Drawing::Point(21, 282);
			this->label19->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(104, 13);
			this->label19->TabIndex = 13;
			this->label19->Text = L"Contraseña Nueva:\r\n";
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(141, 278);
			this->textBox5->Margin = System::Windows::Forms::Padding(2);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(137, 21);
			this->textBox5->TabIndex = 12;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label18->Location = System::Drawing::Point(21, 228);
			this->label18->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(101, 13);
			this->label18->TabIndex = 11;
			this->label18->Text = L"Contraseña Actual";
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(141, 231);
			this->textBox4->Margin = System::Windows::Forms::Padding(2);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(137, 21);
			this->textBox4->TabIndex = 10;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label17->Location = System::Drawing::Point(21, 183);
			this->label17->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(105, 39);
			this->label17->TabIndex = 9;
			this->label17->Text = L"Correo Electronico:\r\n\r\n\r\n";
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(141, 181);
			this->textBox3->Margin = System::Windows::Forms::Padding(2);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(137, 21);
			this->textBox3->TabIndex = 8;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label16->Location = System::Drawing::Point(21, 136);
			this->label16->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(104, 13);
			this->label16->TabIndex = 7;
			this->label16->Text = L"Nombre Completo:\r\n";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(141, 134);
			this->textBox2->Margin = System::Windows::Forms::Padding(2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(137, 21);
			this->textBox2->TabIndex = 6;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label15->Location = System::Drawing::Point(21, 94);
			this->label15->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(113, 13);
			this->label15->TabIndex = 5;
			this->label15->Text = L"Nombre de Usuario: ";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(141, 93);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(137, 21);
			this->textBox1->TabIndex = 4;
			// 
			// label13
			// 
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::SystemColors::Menu;
			this->label13->Location = System::Drawing::Point(297, 15);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(219, 49);
			this->label13->TabIndex = 3;
			this->label13->Text = L"Editar Perfil";
			// 
			// PanelEliminarPErf
			// 
			this->PanelEliminarPErf->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->PanelEliminarPErf->Controls->Add(this->label24);
			this->PanelEliminarPErf->Controls->Add(this->textBox10);
			this->PanelEliminarPErf->Controls->Add(this->Eliminar);
			this->PanelEliminarPErf->Controls->Add(this->label23);
			this->PanelEliminarPErf->Controls->Add(this->textBox9);
			this->PanelEliminarPErf->Controls->Add(this->label21);
			this->PanelEliminarPErf->Controls->Add(this->textBox7);
			this->PanelEliminarPErf->Controls->Add(this->label22);
			this->PanelEliminarPErf->Controls->Add(this->textBox8);
			this->PanelEliminarPErf->Controls->Add(this->label14);
			this->PanelEliminarPErf->Location = System::Drawing::Point(266, 108);
			this->PanelEliminarPErf->Margin = System::Windows::Forms::Padding(2);
			this->PanelEliminarPErf->Name = L"PanelEliminarPErf";
			this->PanelEliminarPErf->Size = System::Drawing::Size(732, 439);
			this->PanelEliminarPErf->TabIndex = 19;
			this->PanelEliminarPErf->Visible = false;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label24->Location = System::Drawing::Point(395, 156);
			this->label24->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(66, 13);
			this->label24->TabIndex = 22;
			this->label24->Text = L"Respuesta: \r\n";
			// 
			// textBox10
			// 
			this->textBox10->Enabled = false;
			this->textBox10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox10->Location = System::Drawing::Point(468, 114);
			this->textBox10->Margin = System::Windows::Forms::Padding(2);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(193, 21);
			this->textBox10->TabIndex = 21;
			// 
			// Eliminar
			// 
			this->Eliminar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Eliminar->Location = System::Drawing::Point(320, 290);
			this->Eliminar->Margin = System::Windows::Forms::Padding(2);
			this->Eliminar->Name = L"Eliminar";
			this->Eliminar->Size = System::Drawing::Size(97, 43);
			this->Eliminar->TabIndex = 20;
			this->Eliminar->Text = L"Eliminar";
			this->Eliminar->UseVisualStyleBackColor = true;
			this->Eliminar->Click += gcnew System::EventHandler(this, &MyForm::Eliminar_Click);
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label23->Location = System::Drawing::Point(402, 115);
			this->label23->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(40, 13);
			this->label23->TabIndex = 19;
			this->label23->Text = L"Frase: \r\n";
			// 
			// textBox9
			// 
			this->textBox9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox9->Location = System::Drawing::Point(468, 156);
			this->textBox9->Margin = System::Windows::Forms::Padding(2);
			this->textBox9->Multiline = true;
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(193, 69);
			this->textBox9->TabIndex = 18;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label21->Location = System::Drawing::Point(55, 180);
			this->label21->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(123, 13);
			this->label21->TabIndex = 17;
			this->label21->Text = L"Confirmar Contraseña:\r\n";
			// 
			// textBox7
			// 
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox7->Location = System::Drawing::Point(189, 179);
			this->textBox7->Margin = System::Windows::Forms::Padding(2);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(137, 21);
			this->textBox7->TabIndex = 16;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label22->Location = System::Drawing::Point(55, 128);
			this->label22->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(104, 13);
			this->label22->TabIndex = 15;
			this->label22->Text = L"Contraseña Actual:\r\n";
			// 
			// textBox8
			// 
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox8->Location = System::Drawing::Point(189, 129);
			this->textBox8->Margin = System::Windows::Forms::Padding(2);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(137, 21);
			this->textBox8->TabIndex = 14;
			// 
			// label14
			// 
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::SystemColors::Menu;
			this->label14->Location = System::Drawing::Point(259, 25);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(250, 49);
			this->label14->TabIndex = 3;
			this->label14->Text = L"Eliminar Perfil";
			// 
			// panel11
			// 
			this->panel11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel11->Location = System::Drawing::Point(995, 107);
			this->panel11->Margin = System::Windows::Forms::Padding(2);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(24, 441);
			this->panel11->TabIndex = 27;
			// 
			// panel10
			// 
			this->panel10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel10->Location = System::Drawing::Point(265, 548);
			this->panel10->Margin = System::Windows::Forms::Padding(2);
			this->panel10->Name = L"panel10";
			this->panel10->Size = System::Drawing::Size(754, 25);
			this->panel10->TabIndex = 26;
			// 
			// panel9
			// 
			this->panel9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel9->Location = System::Drawing::Point(265, 82);
			this->panel9->Margin = System::Windows::Forms::Padding(2);
			this->panel9->Name = L"panel9";
			this->panel9->Size = System::Drawing::Size(754, 30);
			this->panel9->TabIndex = 25;
			// 
			// panel8
			// 
			this->panel8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel8->Location = System::Drawing::Point(241, 82);
			this->panel8->Margin = System::Windows::Forms::Padding(2);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(28, 491);
			this->panel8->TabIndex = 24;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Enabled = false;
			this->checkBox1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->checkBox1->Location = System::Drawing::Point(241, 37);
			this->checkBox1->Margin = System::Windows::Forms::Padding(2);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(56, 17);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"Online";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// button7
			// 
			this->button7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button7->Location = System::Drawing::Point(24, 423);
			this->button7->Margin = System::Windows::Forms::Padding(2);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(188, 43);
			this->button7->TabIndex = 6;
			this->button7->Text = L"Solicitudes";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(26, 495);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(58, 54);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox4->TabIndex = 5;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &MyForm::pictureBox4_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button5->Location = System::Drawing::Point(24, 349);
			this->button5->Margin = System::Windows::Forms::Padding(2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(188, 43);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Contactos";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(24, 277);
			this->button4->Margin = System::Windows::Forms::Padding(2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(188, 43);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Mensajes";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// LabelNombre
			// 
			this->LabelNombre->BackColor = System::Drawing::Color::Transparent;
			this->LabelNombre->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LabelNombre->ForeColor = System::Drawing::SystemColors::Menu;
			this->LabelNombre->Location = System::Drawing::Point(452, 24);
			this->LabelNombre->Name = L"LabelNombre";
			this->LabelNombre->Size = System::Drawing::Size(446, 49);
			this->LabelNombre->TabIndex = 2;
			this->LabelNombre->Text = L"Bienvenido ";
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(26, 31);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(188, 133);
			this->pictureBox3->TabIndex = 0;
			this->pictureBox3->TabStop = false;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->button6);
			this->panel3->Controls->Add(this->button3);
			this->panel3->Controls->Add(this->label12);
			this->panel3->Controls->Add(this->Respuesta);
			this->panel3->Controls->Add(this->label11);
			this->panel3->Controls->Add(this->Edad);
			this->panel3->Controls->Add(this->Validarcontra);
			this->panel3->Controls->Add(this->Contra);
			this->panel3->Controls->Add(this->Correo);
			this->panel3->Controls->Add(this->NomCompleto);
			this->panel3->Controls->Add(this->button2);
			this->panel3->Controls->Add(this->NomUsuario);
			this->panel3->Controls->Add(this->label10);
			this->panel3->Controls->Add(this->Combopregunta);
			this->panel3->Controls->Add(this->ImagenPerf);
			this->panel3->Controls->Add(this->label9);
			this->panel3->Controls->Add(this->label8);
			this->panel3->Controls->Add(this->label7);
			this->panel3->Controls->Add(this->label6);
			this->panel3->Controls->Add(this->label5);
			this->panel3->Controls->Add(this->label4);
			this->panel3->Controls->Add(this->label3);
			this->panel3->Location = System::Drawing::Point(-2, -2);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(1021, 572);
			this->panel3->TabIndex = 11;
			this->panel3->Visible = false;
			// 
			// button6
			// 
			this->button6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button6->ForeColor = System::Drawing::SystemColors::ScrollBar;
			this->button6->Location = System::Drawing::Point(536, 430);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(140, 46);
			this->button6->TabIndex = 28;
			this->button6->Text = L"Cancelar";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->ForeColor = System::Drawing::SystemColors::ScrollBar;
			this->button3->Location = System::Drawing::Point(435, 146);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(85, 23);
			this->button3->TabIndex = 27;
			this->button3->Text = L"Seleccionar";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click_1);
			// 
			// label12
			// 
			this->label12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->ForeColor = System::Drawing::SystemColors::Menu;
			this->label12->Location = System::Drawing::Point(839, 173);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(122, 23);
			this->label12->TabIndex = 26;
			this->label12->Text = L"Respuesta:";
			// 
			// Respuesta
			// 
			this->Respuesta->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Respuesta->Location = System::Drawing::Point(788, 199);
			this->Respuesta->Multiline = true;
			this->Respuesta->Name = L"Respuesta";
			this->Respuesta->Size = System::Drawing::Size(212, 103);
			this->Respuesta->TabIndex = 25;
			// 
			// label11
			// 
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::SystemColors::Menu;
			this->label11->Location = System::Drawing::Point(804, 75);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(174, 23);
			this->label11->TabIndex = 24;
			this->label11->Text = L"Pregunta de Seguridad:";
			// 
			// Edad
			// 
			this->Edad->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Edad->Location = System::Drawing::Point(194, 375);
			this->Edad->Name = L"Edad";
			this->Edad->Size = System::Drawing::Size(145, 25);
			this->Edad->TabIndex = 23;
			// 
			// Validarcontra
			// 
			this->Validarcontra->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Validarcontra->Location = System::Drawing::Point(194, 330);
			this->Validarcontra->Name = L"Validarcontra";
			this->Validarcontra->Size = System::Drawing::Size(145, 25);
			this->Validarcontra->TabIndex = 22;
			// 
			// Contra
			// 
			this->Contra->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Contra->Location = System::Drawing::Point(194, 277);
			this->Contra->Name = L"Contra";
			this->Contra->Size = System::Drawing::Size(145, 25);
			this->Contra->TabIndex = 21;
			// 
			// Correo
			// 
			this->Correo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Correo->Location = System::Drawing::Point(194, 217);
			this->Correo->Name = L"Correo";
			this->Correo->Size = System::Drawing::Size(145, 25);
			this->Correo->TabIndex = 20;
			// 
			// NomCompleto
			// 
			this->NomCompleto->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NomCompleto->Location = System::Drawing::Point(194, 161);
			this->NomCompleto->Name = L"NomCompleto";
			this->NomCompleto->Size = System::Drawing::Size(145, 25);
			this->NomCompleto->TabIndex = 19;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::SystemColors::ScrollBar;
			this->button2->Location = System::Drawing::Point(380, 430);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(140, 46);
			this->button2->TabIndex = 18;
			this->button2->Text = L"Guardar";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click_1);
			// 
			// NomUsuario
			// 
			this->NomUsuario->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NomUsuario->Location = System::Drawing::Point(194, 110);
			this->NomUsuario->Name = L"NomUsuario";
			this->NomUsuario->Size = System::Drawing::Size(145, 25);
			this->NomUsuario->TabIndex = 11;
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::SystemColors::Menu;
			this->label10->Location = System::Drawing::Point(414, 108);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(122, 23);
			this->label10->TabIndex = 10;
			this->label10->Text = L"Imagen de Perfil:";
			// 
			// Combopregunta
			// 
			this->Combopregunta->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->Combopregunta->FormattingEnabled = true;
			this->Combopregunta->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"¿Cuál es el nombre de tu primera mascota\?",
					L"¿Cuál es el nombre de tu escuela primaria\?", L"¿Cuál es el segundo nombre de tu madre\?", L"¿Cuál es el nombre de tu mejor amigo de la infancia\?",
					L"¿Cuál es la ciudad donde naciste\?", L"¿Cuál fue tu primer trabajo\?", L"¿Cuál es tu comida favorita\?", L"¿Cuál fue el modelo de tu primer coche\?",
					L"¿Cuál era el nombre de tu profesor favorito\?", L"¿Cuál es el nombre de tu película favorita\?"
			});
			this->Combopregunta->Location = System::Drawing::Point(788, 110);
			this->Combopregunta->Name = L"Combopregunta";
			this->Combopregunta->Size = System::Drawing::Size(212, 21);
			this->Combopregunta->TabIndex = 9;
			// 
			// ImagenPerf
			// 
			this->ImagenPerf->Location = System::Drawing::Point(571, 107);
			this->ImagenPerf->Name = L"ImagenPerf";
			this->ImagenPerf->Size = System::Drawing::Size(105, 62);
			this->ImagenPerf->TabIndex = 8;
			this->ImagenPerf->TabStop = false;
			// 
			// label9
			// 
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::SystemColors::Menu;
			this->label9->Location = System::Drawing::Point(30, 375);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(101, 23);
			this->label9->TabIndex = 7;
			this->label9->Text = L"Edad: ";
			// 
			// label8
			// 
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::SystemColors::Menu;
			this->label8->Location = System::Drawing::Point(30, 330);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(158, 23);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Confirmar Contraseña: ";
			// 
			// label7
			// 
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::SystemColors::Menu;
			this->label7->Location = System::Drawing::Point(30, 279);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(136, 23);
			this->label7->TabIndex = 5;
			this->label7->Text = L"Contraseña: ";
			// 
			// label6
			// 
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::SystemColors::Menu;
			this->label6->Location = System::Drawing::Point(30, 220);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(136, 23);
			this->label6->TabIndex = 4;
			this->label6->Text = L"Correo Electronico:";
			// 
			// label5
			// 
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::SystemColors::Menu;
			this->label5->Location = System::Drawing::Point(30, 161);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(158, 23);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Nombre Completo:";
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::SystemColors::Menu;
			this->label4->Location = System::Drawing::Point(30, 107);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(158, 23);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Nombre: De Usuario: ";
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::Menu;
			this->label3->Location = System::Drawing::Point(393, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(309, 49);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Ingresa tus Datos";
			// 
			// Menu
			// 
			this->Menu->ImageScalingSize = System::Drawing::Size(20, 20);
			this->Menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->personalizarPerfilToolStripMenuItem,
					this->eliminarPerfilToolStripMenuItem, this->cerrarSesionToolStripMenuItem
			});
			this->Menu->Name = L"Menu";
			this->Menu->Size = System::Drawing::Size(168, 70);
			// 
			// personalizarPerfilToolStripMenuItem
			// 
			this->personalizarPerfilToolStripMenuItem->Name = L"personalizarPerfilToolStripMenuItem";
			this->personalizarPerfilToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->personalizarPerfilToolStripMenuItem->Text = L"Personalizar Perfil";
			this->personalizarPerfilToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::personalizarPerfilToolStripMenuItem_Click);
			// 
			// eliminarPerfilToolStripMenuItem
			// 
			this->eliminarPerfilToolStripMenuItem->Name = L"eliminarPerfilToolStripMenuItem";
			this->eliminarPerfilToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->eliminarPerfilToolStripMenuItem->Text = L"Eliminar Perfil";
			this->eliminarPerfilToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::eliminarPerfilToolStripMenuItem_Click);
			// 
			// cerrarSesionToolStripMenuItem
			// 
			this->cerrarSesionToolStripMenuItem->Name = L"cerrarSesionToolStripMenuItem";
			this->cerrarSesionToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->cerrarSesionToolStripMenuItem->Text = L"Cerrar Sesion";
			this->cerrarSesionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cerrarSesionToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1021, 570);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel3);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load_1);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->OlvidastePanel->ResumeLayout(false);
			this->OlvidastePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			this->PanelHistorial->ResumeLayout(false);
			this->PanelHistorial->PerformLayout();
			this->panelChats->ResumeLayout(false);
			this->panelChats->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			this->SolicitudesPanel->ResumeLayout(false);
			this->SolicitudesPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			this->EditarPanel->ResumeLayout(false);
			this->EditarPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			this->PanelEliminarPErf->ResumeLayout(false);
			this->PanelEliminarPErf->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImagenPerf))->EndInit();
			this->Menu->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		// Metodo para seleccionar imagenes Busca en los archivos, filtra por imagenes y se seleciona la imagen que se quiera de perfil 
	private: System::Void SeleccionarImagen(PictureBox^ imagen) {
		OpenFileDialog^ dialogo = gcnew OpenFileDialog();
		dialogo->Title = "Seleccionar imagen";
		dialogo->Filter = "Archivos de imagen|*.jpg;*.jpeg;*.png;*.bmp;*.gif";
		dialogo->InitialDirectory = Environment::GetFolderPath(Environment::SpecialFolder::MyPictures);

		if (dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			try {
				imagen->Image = Image::FromFile(dialogo->FileName);
				imagen->SizeMode = PictureBoxSizeMode::Zoom;
			}
			catch (Exception^ ex) {
				MessageBox::Show(
					"Error al cargar la imagen:\n" + ex->Message,
					"Error al seleccionar imagen",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error
				);
			}
		}
	}
		   // variables "Globales" para manejar situaciones especificas 
		   bool esPlaceholderUsuario = true;
		   bool esPlaceholderContrasena = true;
		   String^ currentU = "";
		   // Metodo escencial para el funcionamiento del watcher 
	private: System::Void OnUsuariosFileChanged(System::Object^ sender, FileSystemEventArgs^ e) {
		// Se guarda la persona que haya hecho el login 
		if (x != nullptr && x->persona != nullptr)
			currentU = x->persona->GetNombreUsuario();

		// Este thread sleep es escencial para darle tiempo al archivo de actualizarse 
		System::Threading::Thread::Sleep(50);

		// Se lee todo dentro del archivo 
		lista->CargarDesdeArchivo();

		// Se vuelve a buscar el mismo usuario para no perder la informacion 
		if (!String::IsNullOrEmpty(currentU))
			x = lista->BuscarPersona(currentU, 1);

		// Se actualizan los paneles 
		RefreshAllDisplays();
	}

		   // Este metodo es por seguridad si por error el archivo cambia de nombre 
	private: System::Void OnUsuariosFileRenamed(System::Object^ sender, RenamedEventArgs^ e) {
		// Sigue los mismos pasos que arriba 
		OnUsuariosFileChanged(sender, safe_cast<FileSystemEventArgs^>(e));
	}

		   // textBox1 es donde se escribe el nombre de usuario y le puse un diseno 
	private: System::Void textBox1_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		if (UsuarioText->Text->Trim() == "") {
			UsuarioText->Text = "Usuario";
			UsuarioText->ForeColor = Color::Gray;
			esPlaceholderUsuario = true;
		}
	}
		   // Mismo que el textbox1 
	private: System::Void textBox2_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		if (ContraText->Text->Trim() == "") {
			ContraText->Text = "Contraseña";
			ContraText->ForeColor = Color::Gray;
			ContraText->UseSystemPasswordChar = false;
			esPlaceholderContrasena = true;
		}
	}
		   // Cuando entra el mouse se elimina el texto que estaba antes 
	private: System::Void textBox2_MouseEnter(System::Object^ sender, System::EventArgs^ e) {

		if (esPlaceholderContrasena) {
			ContraText->Text = "";
			ContraText->ForeColor = Color::Black;
			ContraText->UseSystemPasswordChar = true;
			esPlaceholderContrasena = false;
		}
	}
		   // lo mismo que el anterior 
	private: System::Void textBox1_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		if (esPlaceholderUsuario) {
			UsuarioText->Text = "";
			UsuarioText->ForeColor = Color::Black;
			esPlaceholderUsuario = false;
		}
	}
		   // Metodo muy interesante, cada vez que el usuario ponga el cursor sobre un boton el cursor se convierte en mano, etc. 
	private: System::Void MyForm_Load_1(System::Object^ sender, System::EventArgs^ e) {
		SetCustomCursors(this);
	}
		   void SetCustomCursors(Control^ parent) {
			   for each (Control ^ control in parent->Controls) {
				   if (dynamic_cast<Button^>(control)) {
					   control->Cursor = Cursors::Hand;
				   }

				   if (dynamic_cast<TextBox^>(control)) {
					   control->Cursor = Cursors::IBeam;
				   }

				   if (control->HasChildren) {
					   SetCustomCursors(control);
				   }
			   }
		   }
		   // Diseno de listboxes en general, idea sacada de https://www.youtube.com/watch?v=OMHttb-N1JQ 
	private: System::Void listBox_DrawItem(System::Object^ sender, DrawItemEventArgs^ e)
	{
		if (e->Index < 0) return;
		ListBox^ lb = (ListBox^)sender;
		String^ text = lb->Items[e->Index]->ToString();
		Color bgColor = Color::FromArgb(173, 216, 230);
		Color textColor = Color::Black;
		if ((e->State & DrawItemState::Selected) == DrawItemState::Selected)
		{
			bgColor = Color::FromArgb(100, 149, 237);
			textColor = Color::White;
		}
		e->Graphics->FillRectangle(gcnew SolidBrush(bgColor), e->Bounds);
		StringFormat^ sf = gcnew StringFormat();
		sf->Alignment = StringAlignment::Near;
		sf->LineAlignment = StringAlignment::Center;
		System::Drawing::Rectangle rect = e->Bounds;
		rect.X += 10;
		e->Graphics->DrawString(text, e->Font, gcnew SolidBrush(textColor), rect, sf);
		e->Graphics->DrawRectangle(Pens::LightGray, e->Bounds);
	}
		   // Diseno preciso para unicamente el listbox de los contactos para seleccionar y mandar mensajes, para que muestre cuantos mensajes nuevos hay. 
	private: System::Void listBox4_DrawItem(Object^ sender, DrawItemEventArgs^ e) {
		if (e->Index < 0) return;
		ListBox^ lb = safe_cast<ListBox^>(sender);
		Persona^ p = safe_cast<Persona^>(lb->Items[e->Index]);
		auto recibidos = x->persona->GetListaMensajesRecibidos()->GetMensajesCon(p->GetNombreUsuario());
		int noLeidos = 0;
		for each (auto m in recibidos)
			if (!m->Leido) ++noLeidos;
		// se escribe el numero de mensajes no leidos y el usuario que los mando 
		String^ texto = p->GetNombreUsuario() + (noLeidos > 0 ? String::Format(" ({0} nuevos)", noLeidos) : "");
		bool seleccionado = (e->State & DrawItemState::Selected) != DrawItemState::None;
		// pinta de colores el usuario seleccionado 
		Color bg = seleccionado ? Color::CornflowerBlue : Color::FromArgb(7, 157, 167);
		e->Graphics->FillRectangle(gcnew SolidBrush(bg), e->Bounds);
		System::Drawing::Rectangle rect = e->Bounds;
		rect.X += 10;
		StringFormat^ sf = gcnew StringFormat();
		sf->Alignment = StringAlignment::Near;
		sf->LineAlignment = StringAlignment::Center;
		e->Graphics->DrawString(texto, e->Font, Brushes::White, rect, sf);
		e->DrawFocusRectangle();
	}
		   // Panel para registro 
	private: System::Void linkLabel1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		panel4->Visible = false;
		panel2->Visible = false;
		panel3->Visible = true;
		// Imagen por defecto 
		ImagenPerf->Image = Image::FromFile("4powQ.jpg");
		ImagenPerf->SizeMode = PictureBoxSizeMode::Zoom;
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		SeleccionarImagen(ImagenPerf);
	}
		   // Lo que mencionaba antes, si se cierra el form no se pierden los datos 
	private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

		if (lista != nullptr) {
			if (watcher != nullptr) watcher->EnableRaisingEvents = false;
			lista->GuardarEnArchivo();
			if (watcher != nullptr) watcher->EnableRaisingEvents = true;
		}
		if (x != nullptr && x->persona != nullptr) {
			x->persona->SetEstado(false);
		}
		if (listBox5 != nullptr && listBox5->Items != nullptr) {
			listBox5->Items->Clear();
		}
		if (listBox6 != nullptr && listBox6->Items != nullptr) {
			listBox6->Items->Clear();
		}
	}

		   // Menu de registro, validaciones y creacion de usuario 
	private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {
		String^ NomUs = NomUsuario->Text->Trim();
		String^ NomCom = NomCompleto->Text->Trim();
		String^ corr = Correo->Text->Trim();
		String^ con = Contra->Text;
		String^ Valicon = Validarcontra->Text;
		String^ Res = Respuesta->Text->Trim();
		Image^ perfIm = ImagenPerf->Image;
		String^ seleccion = Combopregunta->SelectedItem != nullptr ? Combopregunta->SelectedItem->ToString() : "";

		if (NomUs == "" || NomCom == "" || corr == "" || con == "" || Valicon == "" || Res == "" || Edad->Text->Trim() == "")
		{
			MessageBox::Show("Debe llenar todos los campos obligatorios.", "Falta informacion", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int ed;
		if (!Int32::TryParse(Edad->Text, ed)) {
			MessageBox::Show("Edad no valida. Ingrese solo numeros.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			Edad->Clear();
			return;
		}


		if (ed < 13) {
			MessageBox::Show("La edad debe ser mayor a 12 años.", "Edad invalida", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			Edad->Clear();
			return;
		}


		if (con != Valicon) {
			MessageBox::Show("Las contraseñas no coinciden.", "Error de Contraseña", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			Contra->Clear();
			Validarcontra->Clear();
			return;
		}


		if (con->Length < 6) {
			MessageBox::Show("La contraseña debe tener al menos 6 caracteres.", "Contraseña insegura", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}



		if (ContieneNumero(NomCom)) {
			MessageBox::Show("El nombre completo solo debe contener letras.", "Nombre invalido", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}



		if (!GmailValido(corr)) {
			MessageBox::Show("Ingrese un correo valido (ej: nombre@gmail.com).", "Correo invalido", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}


		if (seleccion == "") {
			MessageBox::Show("Debe seleccionar una pregunta de seguridad.", "Falta informacion", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}


		if (Res == "") {
			MessageBox::Show("Debe proporcionar una respuesta para la pregunta de seguridad.", "Falta información", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		if (Existe(NomUs, 1) != nullptr) {
			MessageBox::Show("El nombre de usuario ya esta en uso.", "Usuario duplicado", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (Existe(corr, 2) != nullptr) {
			MessageBox::Show("Este correo electrónico ya esta registrado.", "Correo duplicado", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		MessageBox::Show("¡Registro exitoso!", "Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);

		if (!String::IsNullOrEmpty(currentU)) {
			x = lista->BuscarPersona(currentU, 1);
		}
		// Se refresca todo 
		RefreshAllDisplays();
		Persona^ personaNueva = gcnew Persona(NomUs, NomCom, corr, con, ed, perfIm, seleccion, Res);
		// se ordena antes de ingresar 
		lista->OrdenarPorUsername();
		lista->Add(personaNueva);
		// se guarda en el archivo el cambio sin alertar al watcher para evitar errores coo bucle de recargas infinitas ya que el refresh all es el que 
		// Trabaja con el watcher 
		if (watcher != nullptr) watcher->EnableRaisingEvents = false;
		lista->GuardarEnArchivo();
		if (watcher != nullptr) watcher->EnableRaisingEvents = true;

		panel2->Visible = true;
		panel3->Visible = false;
		panel4->Visible = false;
		NomUsuario->Clear();
		NomCompleto->Clear();
		Correo->Clear();
		Contra->Clear();
		Validarcontra->Clear();
		Respuesta->Clear();
		Edad->Clear();
		Combopregunta->SelectedIndex = -1;


	}
		   // Metodos para hacer las validaciones 
		   bool ContieneNumero(String^ texto) {
			   int i = 0;
			   while (i < texto->Length) {
				   if (Char::IsDigit(texto[i])) {
					   return true;
				   }
				   i++;
			   }
			   return false;
		   }
		   bool GmailValido(String^ correo) {
			   bool encontroat = false;
			   String^ usuario = "";
			   String^ dominio = "";

			   for (int i = 0; i < correo->Length; i++) {
				   char x = correo[i];
				   if (x == '@') {
					   encontroat = true;
					   usuario = correo->Substring(0, i);
					   dominio = correo->Substring(i + 1, correo->Length - (i + 1));
					   break;
				   }
			   }

			   if (encontroat && dominio == "gmail.com") {
				   return true;
			   }
			   else {
				   return false;
			   }
		   }
		   Nodo^ Existe(String^ dato, int criterio) {
			   lista->OrdenarPorUsername();
			   return lista->BuscarPersona(dato, criterio);
		   }

		   // Login 
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		lista->OrdenarPorUsername();
		String^ usuario = UsuarioText->Text;
		String^ contra = ContraText->Text->Trim();
		x = lista->BuscarPersona(usuario, 1);

		if (x == nullptr) {
			MessageBox::Show("Usuario no encontrado.");
			return;
		}
		if (x->persona == nullptr) {
			MessageBox::Show("Error: El nodo tiene una persona nula.");
			return;
		}
		if (x->persona->GetContrasena() == nullptr) {
			MessageBox::Show("Error: La contraseña es nula.");
			return;
		}

		if (x == nullptr || x->persona == nullptr) {
			MessageBox::Show("El nombre de usuario no existe o está mal registrado.", "Usuario Equivocado", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (!x->persona->GetContrasena()->Equals(contra)) {
			MessageBox::Show("Contraseña Incorrecta.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		MessageBox::Show("Bienvenido.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);


		panel2->Visible = false;
		panel3->Visible = false;
		panel4->Visible = true;


		UsuarioText->Text = "";
		ContraText->Text = "";

		LabelNombre->Text = "Hola " + x->persona->GetNombreUsuario() + "!";
		pictureBox3->Image = x->persona->GetImagenPerfil();
		pictureBox3->SizeMode = PictureBoxSizeMode::Zoom;
		x->persona->SetEstado(true);
		if (watcher != nullptr) watcher->EnableRaisingEvents = false;
		lista->GuardarEnArchivo();
		if (watcher != nullptr) watcher->EnableRaisingEvents = true;

		RefreshAllDisplays();

	}
		   // Panel para recuperar tu cuenta 
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		panel3->Visible = false;
		panel4->Visible = false;
		panel2->Visible = true;
	}
		   // Seleccionar imagen nueva, decidi hacer un metodo 
	private: System::Void button3_Click_1(System::Object^ sender, System::EventArgs^ e) {
		SeleccionarImagen(ImagenPerf);
	}
		   // Muestra un menu donde hay varias opciones si cerrar sesion, eliminar cuenta o modificar 
	private: System::Void pictureBox4_Click(System::Object^ sender, System::EventArgs^ e) {
		Menu->Show(pictureBox4, System::Drawing::Point(0, pictureBox4->Height));
	}
		   // Modificar usuario 
	private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
		if (x == nullptr || x->persona == nullptr) {
			MessageBox::Show("Error interno: usuario no encontrado.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}


		String^ origUsuario = x->persona->GetNombreUsuario();
		String^ origNombre = x->persona->GetNombreCompleto();
		String^ origCorreo = x->persona->GetCorreo();
		String^ origEdadStr = x->persona->GetEdad().ToString();
		Image^ origImagen = x->persona->GetImagenPerfil();


		String^ nuevoUsuario = textBox1->Text->Trim();
		String^ nuevoNombre = textBox2->Text->Trim();
		String^ nuevoCorreo = textBox3->Text->Trim();
		String^ edadTexto = textBox6->Text->Trim();
		String^ contraActual = textBox4->Text;
		String^ contraNueva = textBox5->Text;
		Image^ nuevaImagen = pictureBox6->Image;


		if (nuevoUsuario != "" && nuevoUsuario != origUsuario) {

			if (Existe(nuevoUsuario, 1) != nullptr) {
				MessageBox::Show("El nombre de usuario ya está en uso.", "Usuario duplicado", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			x->persona->SetNombreUsuario(nuevoUsuario);
		}

		if (nuevoNombre != "" && nuevoNombre != origNombre) {
			if (ContieneNumero(nuevoNombre)) {
				MessageBox::Show("El nombre completo solo debe contener letras.", "Nombre inválido", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			x->persona->SetNombreCompleto(nuevoNombre);
		}


		if (nuevoCorreo != "" && nuevoCorreo != origCorreo) {
			if (!GmailValido(nuevoCorreo)) {
				MessageBox::Show("Ingrese un correo válido (ej: usuario@gmail.com).", "Correo inválido", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			if (Existe(nuevoCorreo, 2) != nullptr) {
				MessageBox::Show("Este correo electrónico ya está registrado.", "Correo duplicado", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			x->persona->SetCorreo(nuevoCorreo);
		}

		if (edadTexto != "" && edadTexto != origEdadStr) {
			int ed;
			if (!Int32::TryParse(edadTexto, ed)) {
				MessageBox::Show("Edad no válida. Ingrese solo números.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				textBox6->Clear();
				return;
			}
			if (ed < 13) {
				MessageBox::Show("La edad debe ser mayor o igual a 13 años.", "Edad inválida", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				textBox6->Clear();
				return;
			}
			x->persona->SetEdad(ed);
		}


		if (nuevaImagen != nullptr && nuevaImagen != origImagen) {
			x->persona->SetImagenPerfil(nuevaImagen);
			pictureBox3->Image = nuevaImagen;
			pictureBox3->SizeMode = PictureBoxSizeMode::Zoom;
		}

		if (contraActual != "" || contraNueva != "") {
			if (contraActual == "" || contraNueva == "") {
				MessageBox::Show("Para cambiar la contraseña, llene ambos campos.", "Error de contraseña", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			if (contraActual != x->persona->GetContrasena()) {
				MessageBox::Show("Contraseña actual incorrecta.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			if (contraNueva->Length < 6) {
				MessageBox::Show("La nueva contraseña debe tener al menos 6 caracteres.", "Contraseña insegura", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			x->persona->SetContrasena(contraNueva);
		}
		// Se modifica el usuario en base los campos modificados 
		MessageBox::Show("Perfil actualizado con éxito.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
		SaveAndRefreshAll();

	}

	private: System::Void personalizarPerfilToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		listBox5->Items->Clear();
		panel2->Visible = false;
		panel3->Visible = false;
		SolicitudesPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		EditarPanel->BringToFront();

		EditarPanel->Visible = true;


		textBox1->Text = x->persona->GetNombreUsuario();
		textBox2->Text = x->persona->GetNombreCompleto();
		textBox3->Text = x->persona->GetCorreo();
		textBox6->Text = x->persona->GetEdad().ToString();
		pictureBox6->Image = x->persona->GetImagenPerfil();
		pictureBox6->SizeMode = PictureBoxSizeMode::Zoom;

	}
		   // al momento de tocar la picture box se busca una imagen nueva 
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
		SeleccionarImagen(pictureBox6);
	}
		   // Aca elimino el usuario con la contrasena y pregunta de seguridad 
	private: System::Void eliminarPerfilToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		panel2->Visible = false;
		panel3->Visible = false;
		EditarPanel->Visible = false;
		panel4->Visible = true;
		SolicitudesPanel->Visible = false;
		PanelEliminarPErf->BringToFront();
		PanelEliminarPErf->Visible = true;
		textBox10->Text = x->persona->GetPreguntaSeguridad();
		listBox5->Items->Clear();
	}
	private: System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ contra = textBox8->Text;
		String^ Valicon = textBox7->Text;
		String^ frase = textBox9->Text;
		bool eliminar = true;

		if (contra != Valicon) {
			MessageBox::Show("Error: las contraseñas no son iguales", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			eliminar = false;
		}
		else if (contra != x->persona->GetContrasena()) {
			MessageBox::Show("Error: las contraseñas coinciden pero no es la contraseña de este perfil", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			eliminar = false;
		}

		if (frase != x->persona->GetRespuesta()) {
			MessageBox::Show("Respuesta incorrecta", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			eliminar = false;
		}

		if (eliminar) {
			System::Windows::Forms::DialogResult resultado = MessageBox::Show(
				"¿Está seguro de que desea eliminar su cuenta? Esta acción no se puede deshacer.",
				"Confirmar eliminación",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Warning);

			if (resultado == System::Windows::Forms::DialogResult::Yes) {
				lista->eliminar(x->persona->GetNombreUsuario());

				if (watcher != nullptr) watcher->EnableRaisingEvents = false;
				lista->GuardarEnArchivo();
				if (watcher != nullptr) watcher->EnableRaisingEvents = true;


				Logout();
				listBox5->Items->Clear();
			}
		}
		SaveAndRefreshAll();

	}
		   // se llama a logout cuando se selecciona la opcion de salir 
	private: System::Void Logout() {
		if (x != nullptr && x->persona != nullptr) {
			x->persona->SetEstado(false);
			if (watcher != nullptr) watcher->EnableRaisingEvents = false;
			lista->GuardarEnArchivo();
			if (watcher != nullptr) watcher->EnableRaisingEvents = true;
		}

		// ocultar panele
		panel3->Visible = false;
		panel4->Visible = false;
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		panel2->Visible = true;
	}
		   // Se le pregunta al usuario si cerrar o no sesion 
	private: System::Void cerrarSesionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult resultado = MessageBox::Show("¿Está seguro de que desea cerrar sesion de su cuenta?", "Confirmar", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (resultado == System::Windows::Forms::DialogResult::Yes) {
			listBox5->Items->Clear();
			listBox4->Items->Clear();
			Logout();
			if (watcher != nullptr) watcher->EnableRaisingEvents = false;
			lista->GuardarEnArchivo();
			if (watcher != nullptr) watcher->EnableRaisingEvents = true;
			x->persona->SetEstado(false);
		}
		RefreshAllDisplays();
	}
		   // Buscar usuario y refresca todo 
	private: System::Void button13_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nombreusuario = textBox12->Text->Trim();
		x->persona->GetListaContactos()->OrdenarPorUsername();
		Nodo^ resultado = x->persona->GetListaContactos()->buscar(nombreusuario, 1);
		listBox1->Items->Clear();

		if (resultado != nullptr) {
			listBox1->Items->Add(resultado);
			MessageBox::Show("Usuario encontrado!");
		}
		else {
			MessageBox::Show("Usuario no encontrado");
		}
		RefreshAllDisplays();
	}
		   // Se selecciona un usuario y se nuestran sus datos con la posibilidad de mandar una solicitud de amistad 
	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (listBox1->SelectedItem != nullptr) {

			Persona^ persona = dynamic_cast<Persona^>(listBox1->SelectedItem);
			textBox11->Text = persona->GetNombreUsuario();
			pictureBox5->Image = persona->GetImagenPerfil();
			pictureBox5->SizeMode = PictureBoxSizeMode::Zoom;
			if (persona->GetEstado() == false) {
				checkBox2->Checked = false;
				checkBox2->Text = "Ofline";
			}
			else {
				checkBox2->Checked = true;
				checkBox2->Text = "Online";
			}
		}
	}
		   // Eliminar un contacto guardando el cambio y luego refrescando la informacion 
	private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listBox1->SelectedItem != nullptr) {
			Persona^ persona = dynamic_cast<Persona^>(listBox1->SelectedItem);
			x->persona->GetListaContactos()->OrdenarPorUsername();
			x->persona->GetListaContactos()->Eliminar(persona->GetNombreUsuario());
			persona->GetListaContactos()->Eliminar(x->persona->GetNombreUsuario());
			if (watcher != nullptr) watcher->EnableRaisingEvents = false;
			lista->GuardarEnArchivo();
			if (watcher != nullptr) watcher->EnableRaisingEvents = true;
			MessageBox::Show("Usuario Eliminado Exitosamente!");
		}
		else {
			MessageBox::Show("Tiene que eligir un usuario para eliminarlo");
		}
		RefreshContactos();
		textBox11->Text = "";
		pictureBox5->Image = nullptr;
		checkBox2->Checked = false;
		checkBox2->Text = "";
	}
		   // Se muestran los contactos en la listbox 1 
	private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e) {
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		panel6->Visible = false;
		SolicitudesPanel->Visible = false;
		panel5->Visible = true;
		panel1->Visible = true;

		x->persona->GetListaContactos()->OrdenarPorUsername();
		x->persona->GetListaContactos()->agregarList(listBox1);
		RefreshContactos();
	}
		   // Refrescar la informacion dentro de las listboxes 
	private: System::Void pictureBox7_Click(System::Object^ sender, System::EventArgs^ e) {
		if (panel6->Visible == true) {
			lista->agregarList(listBox2);
		}
		else {
			x->persona->GetListaContactos()->OrdenarPorUsername();
			x->persona->GetListaContactos()->agregarList(listBox1);
		}
		x->persona->GetListaContactos()->OrdenarPorUsername();
		x->persona->GetListaContactos()->OrdenarPorUsername();
	}
		   // se busca un contacto y se muestra en la listbox 
	private: System::Void button14_Click(System::Object^ sender, System::EventArgs^ e) {

		if (!String::IsNullOrEmpty(currentU)) {
			x = lista->BuscarPersona(currentU, 1);
		}
		String^ nombreusuario = textBox13->Text->Trim();
		lista->OrdenarPorUsername();
		Nodo^ resultado = lista->BuscarPersona(nombreusuario, 1);

		listBox2->Items->Clear();

		if (resultado != nullptr) {
			listBox2->Items->Add(resultado->persona);
			MessageBox::Show("Usuario encontrado!");
		}
		else {
			MessageBox::Show("Usuario no encontrado");
		}
		RefreshAllDisplays();

	}
		   // Mostrar datos de un contacto 
	private: System::Void listBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (listBox2->SelectedItem != nullptr) {
			Persona^ persona = dynamic_cast<Persona^>(listBox2->SelectedItem);
			textBox14->Text = persona->GetNombreUsuario();
			pictureBox8->Image = persona->GetImagenPerfil();
			pictureBox8->SizeMode = PictureBoxSizeMode::Zoom;
			if (persona->GetEstado() == false) {
				checkBox3->Checked = false;
				checkBox3->Text = "Ofline";
			}
			else {
				checkBox3->Checked = true;
				checkBox3->Text = "Online";
			}
		}
	}
		   // Mandar solicitud de amistad auxiliada por la clase Gestion
	private: System::Void button15_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listBox2->SelectedItem == nullptr) {
			MessageBox::Show("Debe seleccionar una persona para mandar solicitud", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		Persona^ destino = safe_cast<Persona^>(listBox2->SelectedItem);
		if (x->persona->GetSolicitudesEnviadas()->buscar(destino->GetNombreUsuario(), 1) == nullptr
			&& x->persona->GetListaContactos()->buscar(destino->GetNombreUsuario(), 1) == nullptr)
		{
			Gestion::EnviarSolicitud(x->persona, destino);
			SaveAndRefreshAll();
		}
		else {
			MessageBox::Show("Ya existe una solicitud (o son ya amigos).");
		}
	}
		   // Muestra el menu de agregar 
	private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
		panel5->Visible = false;
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		SolicitudesPanel->Visible = false;
		panel1->Visible = true;
		panel6->Visible = true;
		if (!String::IsNullOrEmpty(currentU)) {
			x = lista->BuscarPersona(currentU, 1);
		}
		listBox2->Items->Clear();
		for each (Persona ^ p in lista->GetAllUsuarios()) {
			if (p->GetNombreUsuario() != x->persona->GetNombreUsuario()) {
				listBox2->Items->Add(p);
			}
		}
		RefreshAllDisplays();
	}
		   // se muestra el menu de los contactos 
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		PanelEliminarPErf->Visible = false;
		EditarPanel->Visible = false;
		SolicitudesPanel->Visible = false;
		PanelHistorial->Visible = false;
		panel1->Visible = true;
		panel1->BringToFront();

		if (!String::IsNullOrEmpty(currentU)) {
			x = lista->BuscarPersona(currentU, 1);
		}


		listBox2->Items->Clear();
		for each (Persona ^ p in lista->GetAllUsuarios()) {
			if (p->GetNombreUsuario() != x->persona->GetNombreUsuario()) {
				listBox2->Items->Add(p);
			}
		}
		RefreshAllDisplays();
	}
		   // Listbox dentro de solicitudes 
	private: System::Void listBox3_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (listBox3->SelectedItem != nullptr) {
			Persona^ persona = dynamic_cast<Persona^>(listBox3->SelectedItem);
			textBox15->Text = persona->GetNombreUsuario();
			pictureBox10->Image = persona->GetImagenPerfil();
			pictureBox10->SizeMode = PictureBoxSizeMode::Zoom;

		}
	}
		   // Boton de aceptar solicitud 
	private: System::Void button16_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listBox3->SelectedItem != nullptr) {

			if (!String::IsNullOrEmpty(currentU)) {
				x = lista->BuscarPersona(currentU, 1);
			}
			Persona^ persona = dynamic_cast<Persona^>(listBox3->SelectedItem);
			Gestion::AceptarSolicitud(x->persona, persona);
			SaveAndRefreshAll();

			listBox3->Items->Clear();
			x->persona->GetSolicitudesRecibidas()->OrdenarPorUsername();
			x->persona->GetSolicitudesRecibidas()->agregarList(listBox3);
		}
		else {
			MessageBox::Show("No seleccionó ningún usuario");
		}
		RefreshAllDisplays();
		textBox15->Text = "";
		pictureBox10->Image = nullptr;
	}
		   // Boton de rechazar solicitud 
	private: System::Void button17_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listBox3->SelectedItem != nullptr) {
			Persona^ persona = safe_cast<Persona^>(listBox3->SelectedItem);
			Gestion::RechazarSolicitud(x->persona, persona);
			SaveAndRefreshAll();

			x->persona->GetSolicitudesRecibidas()->OrdenarPorUsername();
			x->persona->GetSolicitudesRecibidas()->agregarList(listBox3);
		}
		else {
			MessageBox::Show("No seleccionó ningún usuario");
		}
		RefreshSolicitudesRecibidas();
	}
		   // Boton para mostrar solicitudes 
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		panel1->Visible = false;
		PanelHistorial->Visible = false;
		SolicitudesPanel->Visible = true;
		SolicitudesPanel->BringToFront();

		RefreshAllDisplays();
		x->persona->GetSolicitudesRecibidas()->OrdenarPorUsername();
		x->persona->GetSolicitudesRecibidas()->agregarList(listBox3);
		listBox5->Items->Clear();

	}
		   // Olvidaste tu contra? se restaura la contra con una clave nueva y la pregunta de segurdad 
	private: System::Void linkLabel2_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		String^ usuarioaVali = UsuarioText->Text;
		lista->OrdenarPorUsername();
		x = lista->BuscarPersona(usuarioaVali, 1);

		if (String::IsNullOrEmpty(usuarioaVali) || usuarioaVali == "Usuario") {

			MessageBox::Show("No hay usuario para restaurar la contraseña");

		}
		else if (x == nullptr) {
			MessageBox::Show("El usuario con ese noombre no existe");
		}
		else {
			OlvidastePanel->Visible = true;
			textBox16->Text = x->persona->GetPreguntaSeguridad();
		}


	}
		   // Boton para cambiar la contrasena 
	private: System::Void button18_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ usuarioaVali = UsuarioText->Text;
		lista->OrdenarPorUsername();
		x = lista->BuscarPersona(usuarioaVali, 1);
		String^ resp = textBox17->Text;
		String^ contraN = textBox19->Text;
		String^ valicontra = textBox18->Text;

		if (resp != x->persona->GetPreguntaSeguridad()) {
			MessageBox::Show("Error, respuesta incorrecta");
		}
		else {
			if (contraN != valicontra) {
				MessageBox::Show("Error, Las contraseñas no son iguales");
				return;
			}
			else {
				x->persona->SetContrasena(contraN);
				OlvidastePanel->Visible = false;
			}

		}
		SaveAndRefreshAll();
	}
		   // Cancelar accion de restaurar lacontra 
	private: System::Void button19_Click(System::Object^ sender, System::EventArgs^ e) {
		OlvidastePanel->Visible = false;
		textBox17->Text = "";
		textBox19->Text = "";
		textBox18->Text = "";
	}

		   // se selecciona un usuario dentro de la listbox y se muestra toda la conversacion con el metodo mostrar hilo 
	private: System::Void listBox4_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		Persona^ p = safe_cast<Persona^>(listBox4->SelectedItem);
		if (p != nullptr) {
			x->persona->GetListaMensajesRecibidos()->MarcarLeidosCon(p->GetNombreUsuario());
			MostrarHilo(p);
			RefreshChatMessages();
		}
	}
		   // Metodo escencial para las conversaciones 
	private: System::Void MostrarHilo(Persona^ contacto) {
		listBox5->Items->Clear(); // en este se muestran todos los datos 
		// Se consiguen los mensajes enviados y recibidos 
		auto enviados = x->persona->GetListaMensajesEnviados()->GetMensajesCon(contacto->GetNombreUsuario());
		auto recibidos = x->persona->GetListaMensajesRecibidos()->GetMensajesCon(contacto->GetNombreUsuario());
		//  construyo la lista de HiloItem con tipo y contenido original con la lista de mensajes enviados al usuario que lo mande 
		auto hilo = gcnew List<HiloItem^>();
		for each (auto m in x->persona->GetListaMensajesEnviados()->GetMensajesCon(contacto->GetNombreUsuario())) {
			// si es texto, mostramos el texto; si es sticker, ponemos un placeholder que diga que es un sticker 
			String^ txt = (m->Tipo == TipoMensaje::Texto) ? m->Contenido : (m->Tipo == TipoMensaje::Sticker) ? "[Sticker]" : "[Archivo]";
			hilo->Add(gcnew HiloItem(txt, m->Fecha, true, m->Tipo, m->Contenido));
		}

		// Se hace exactamente lo mismo pero con mensajes recibidos 
		for each (auto m in x->persona->GetListaMensajesRecibidos()->GetMensajesCon(contacto->GetNombreUsuario())) {
			String^ txt = (m->Tipo == TipoMensaje::Texto) ? m->Contenido : (m->Tipo == TipoMensaje::Sticker) ? "[Sticker]" : "[Archivo]";
			hilo->Add(gcnew HiloItem(txt, m->Fecha, false, m->Tipo, m->Contenido));
		}

		// Se ordena con un metodo generico como hiloItem tiene lista de tipo vector, vector ya tiene su metodo de ordenar pero llamo mi metodo de comparar por fecha para que ordene 
		// con ese criterio 
		hilo->Sort(gcnew Comparison<HiloItem^>(&MyForm::CompareByFechaHiloItem));

		listBox5->Items->Clear();
		for each (auto hi in hilo)
			listBox5->Items->Add(hi);
	}
		   // Boton para mostrar los mensajes 
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {

		panel1->Visible = false;
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		SolicitudesPanel->Visible = false;
		PanelHistorial->Visible = false;
		panelChats->Visible = true;
		x->persona->GetListaContactos()->OrdenarPorUsername();
		listBox4->Items->Clear();

		Nodo^ actual = x->persona->GetListaContactos()->GetHead();
		while (actual != nullptr) {
			listBox4->Items->Add(actual->persona);
			actual = actual->next;
		}

		listBox5->Items->Clear();
		RefreshAllDisplays();
	}

		   // boton para enviar mensaje 
	private: System::Void button20_Click(System::Object^ sender, System::EventArgs^ e) {

		Image^ temp = pictureBox13->Image;
		String^ texto = textBox20->Text->Trim();
		bool tieneTexto = !String::IsNullOrEmpty(texto);
		bool tieneSticker = (pictureBox13->Image != nullptr && !String::IsNullOrEmpty(stickerPath));
		Persona^ p = dynamic_cast<Persona^>(listBox4->SelectedItem);
		if (p == nullptr) return;               // ningun contacto seleccionado
		if (!tieneTexto && !tieneSticker) return; // nada que enviar

		// Se envia mensaje si hay 
		if (tieneTexto) {
			x->persona->GetListaMensajesEnviados()->AgregarMensaje(texto, TipoMensaje::Texto, true, p->GetNombreUsuario());
			p->GetListaMensajesRecibidos()->AgregarMensaje(texto, TipoMensaje::Texto, false, x->persona->GetNombreUsuario());
		}

		// se envia sticker si hay 
		if (tieneSticker && validarSticker == true) {
			x->persona->GetListaMensajesEnviados()->AgregarMensaje(stickerPath, TipoMensaje::Sticker, true, p->GetNombreUsuario());
			p->GetListaMensajesRecibidos()->AgregarMensaje(stickerPath, TipoMensaje::Sticker, false, x->persona->GetNombreUsuario());
			validarSticker = false;
		}

		SaveAndRefreshAll();

		// Se acualizan los mensajes enviados y recibidos de forma simultanea 
		MostrarHilo(p);


		textBox20->Clear();
		pictureBox13->Image = temp;
		stickerPath = nullptr;
	}
		// ACA es el diseno para la listbox de los mensajes, el que manda un mensaje tendra un color y el que lo reciba otro 
		   // Sacado de: https://stackoverflow.com/questions/9931420/why-does-listbox-drawitem-get-called-many-times
	private: System::Void listBox5_DrawItem(Object^ sender, DrawItemEventArgs^ e) {
		if (e->Index < 0) return;
		ListBox^ lb = safe_cast<ListBox^>(sender);
		HiloItem^ hi = safe_cast<HiloItem^>(lb->Items[e->Index]);

		Color bg = hi->Enviado ? Color::WhiteSmoke : Color::LightCyan;
		if ((e->State & DrawItemState::Selected) != DrawItemState::None)
			bg = Color::DarkSlateGray;
		e->Graphics->FillRectangle(gcnew SolidBrush(bg), e->Bounds);

		if (hi->Tipo == TipoMensaje::Sticker) {
			try {
				Image^ img = Image::FromFile(hi->Contenido);
				int size = e->Bounds.Height - 4;
				e->Graphics->DrawImage(img,e->Bounds.X + 2,e->Bounds.Y + 2,size, size);
			}
			catch (...) {
				e->Graphics->DrawString("[sticker missing]",e->Font, Brushes::Red,e->Bounds.Location);
			}
		}
		else {
			System::Drawing::Rectangle rect = e->Bounds;
			rect.X += 5;
			e->Graphics->DrawString(hi->Texto,e->Font,Brushes::Black,rect);
		}

		e->Graphics->DrawRectangle(Pens::LightGray, e->Bounds);

	}
		   // Deshacer mensaje se llama un metodo de la clase ListaMensaje 
	private: System::Void pictureBox11_Click(System::Object^ sender, System::EventArgs^ e) {
		Persona^ p = dynamic_cast<Persona^>(listBox4->SelectedItem);
		if (p != nullptr) {
			x->persona->GetListaMensajesEnviados()->DeshacerUltimoMensaje();
			p->GetListaMensajesRecibidos()->DeshacerUltimoMensaje();
			SaveAndRefreshAll();
			MostrarHilo(p);
		}
	}
		   // Rehacer el ultimo mensaje eliminado de la clase ListaMensaje 
	private: System::Void pictureBox12_Click(System::Object^ sender, System::EventArgs^ e) {
		Persona^ p = dynamic_cast<Persona^>(listBox4->SelectedItem);
		if (p == nullptr) return;

		x->persona->GetListaMensajesEnviados()->RehacerUltimoMensaje();
		p->GetListaMensajesRecibidos()->RehacerUltimoMensaje();
		SaveAndRefreshAll();
		MostrarHilo(p);
	}

		// mostrar historial 
	private: System::Void button21_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = false;
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		SolicitudesPanel->Visible = false;
		panelChats->Visible = false;
		PanelHistorial->BringToFront();
		PanelHistorial->Visible = true;
		PopulateListBox6(BuildHistorial());
		RefreshAllDisplays();
	}
		   // Aca si hago burbuja porque es con TODOS los mensajes si ninguna particulidad en hilo no lo hago de esta forma 
		   // por que se mete a cada mensaje enviado de usuario a, a b y el ordenamiento ahi llevaria a errores 
	private: System::Void button23_Click(System::Object^ sender, System::EventArgs^ e) {
		x->persona->GetListaMensajesEnviados()->OrdenarPorFecha_Burbuja();
		x->persona->GetListaMensajesRecibidos()->OrdenarPorFecha_Burbuja();
		auto hilo = BuildHistorial();
		PopulateListBox6(hilo);
	}
		   // Ordenamos por Insercion (Orden alfabetico)
	private: System::Void button24_Click(System::Object^ sender, System::EventArgs^ e) {
		x->persona->GetListaMensajesEnviados()->OrdenarPorContacto_Insercion();
		x->persona->GetListaMensajesRecibidos()->OrdenarPorContacto_Insercion();
		auto hilo = BuildHistorial();
		PopulateListBox6(hilo);
	}

		   // Ordenamos por Quicksort (Longitud del mensaje)
	private: System::Void button25_Click(System::Object^ sender, System::EventArgs^ e) {
		x->persona->GetListaMensajesEnviados()->OrdenarPorLongitud_QuickSort();
		x->persona->GetListaMensajesRecibidos()->OrdenarPorLongitud_QuickSort();
		auto hilo = BuildHistorial();
		PopulateListBox6(hilo);
	}
	private: System::Void pictureBox13_Click(System::Object^ sender, System::EventArgs^ e) {
		// Abrimos un OpenFileDialog para que el usuario seleccione su sticker
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Filter = "Imágenes|*.png;*.jpg;*.jpeg;*.bmp;*.gif";
		ofd->Title = "Selecciona un sticker";
		ofd->InitialDirectory = Environment::GetFolderPath(Environment::SpecialFolder::MyPictures);

		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			stickerPath = ofd->FileName;
			try {
				pictureBox13->Image = Image::FromFile(stickerPath);
				pictureBox13->SizeMode = PictureBoxSizeMode::Zoom;
				validarSticker = true;  
			}
			catch (Exception^ ex) {
				MessageBox::Show("No se pudo cargar la imagen:\n" + ex->Message,
					"Error al cargar sticker",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
				stickerPath = nullptr;
				validarSticker = false;
			}
		}
	}
		   // Buscar palabra enviada 
	private: System::Void button22_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ term = textBox21->Text->Trim();
		auto hilo = BuildHistorial();
		auto filtrado = gcnew List<HiloItem^>();
		for each (auto hi in hilo) {
			if (hi->Texto->IndexOf(term, StringComparison::OrdinalIgnoreCase) >= 0)
				filtrado->Add(hi);
		}
		PopulateListBox6(filtrado);
	}

	};

}

