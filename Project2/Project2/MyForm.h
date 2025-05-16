#pragma once
#include "Persona.h"
#include "Nodo.h"
#include "Listausuarios.h"
#include "Gestion.h"


namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		static Listausuarios^ lista = gcnew Listausuarios();
		static Nodo^ x = gcnew Nodo();

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
	private: System::Windows::Forms::PictureBox^ pictureBox5;
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


	private: System::Windows::Forms::Label^ label32;


	public:

		MyForm(void)
		{
			InitializeComponent();
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->listBox1->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox_DrawItem);
			this->listBox2->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox_DrawItem);
			this->listBox3->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox_DrawItem);
			this->listBox4->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox_DrawItem);
			this->listBox5->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::listBox_DrawItem);
			lista->CargarDesdeArchivo();
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

			listBox4->BackColor = myColor;
			listBox4->DrawMode = DrawMode::OwnerDrawFixed;
			listBox4->ItemHeight = 40;
			listBox4->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);

			listBox5->BackColor = myColor;
			listBox5->DrawMode = DrawMode::OwnerDrawFixed;
			listBox5->ItemHeight = 40;
			listBox5->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);

			textBox20->BackColor = myColor; 
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
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
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
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
			this->panelChats = (gcnew System::Windows::Forms::Panel());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->listBox5 = (gcnew System::Windows::Forms::ListBox());
			this->listBox4 = (gcnew System::Windows::Forms::ListBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
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
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
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
			this->SolicitudesPanel = (gcnew System::Windows::Forms::Panel());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
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
			this->panelChats->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panel6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			this->panel5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			this->PanelEliminarPErf->SuspendLayout();
			this->SolicitudesPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			this->EditarPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
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
			this->panel2->Margin = System::Windows::Forms::Padding(4);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1361, 705);
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
			this->OlvidastePanel->Name = L"OlvidastePanel";
			this->OlvidastePanel->Size = System::Drawing::Size(910, 698);
			this->OlvidastePanel->TabIndex = 14;
			this->OlvidastePanel->Visible = false;
			// 
			// button19
			// 
			this->button19->BackColor = System::Drawing::Color::AliceBlue;
			this->button19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button19->ForeColor = System::Drawing::Color::Gray;
			this->button19->Location = System::Drawing::Point(471, 450);
			this->button19->Margin = System::Windows::Forms::Padding(4);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(256, 64);
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
			this->button18->Location = System::Drawing::Point(167, 452);
			this->button18->Margin = System::Windows::Forms::Padding(4);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(256, 64);
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
			this->label34->Location = System::Drawing::Point(468, 282);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(75, 17);
			this->label34->TabIndex = 30;
			this->label34->Text = L"Respuesta: \r\n";
			// 
			// textBox16
			// 
			this->textBox16->Enabled = false;
			this->textBox16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox16->Location = System::Drawing::Point(578, 230);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(256, 25);
			this->textBox16->TabIndex = 29;
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label35->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label35->Location = System::Drawing::Point(490, 233);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(46, 17);
			this->label35->TabIndex = 28;
			this->label35->Text = L"Frase: \r\n";
			// 
			// textBox17
			// 
			this->textBox17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox17->Location = System::Drawing::Point(578, 279);
			this->textBox17->Multiline = true;
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(256, 84);
			this->textBox17->TabIndex = 27;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label36->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label36->Location = System::Drawing::Point(28, 297);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(139, 17);
			this->label36->TabIndex = 26;
			this->label36->Text = L"Confirmar Contraseña:\r\n";
			// 
			// textBox18
			// 
			this->textBox18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox18->Location = System::Drawing::Point(207, 295);
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(181, 25);
			this->textBox18->TabIndex = 25;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label37->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label37->Location = System::Drawing::Point(28, 233);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(115, 17);
			this->label37->TabIndex = 24;
			this->label37->Text = L"Contraseña Nueva";
			// 
			// textBox19
			// 
			this->textBox19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox19->Location = System::Drawing::Point(207, 234);
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(181, 25);
			this->textBox19->TabIndex = 23;
			// 
			// label33
			// 
			this->label33->BackColor = System::Drawing::Color::Transparent;
			this->label33->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label33->ForeColor = System::Drawing::SystemColors::Menu;
			this->label33->Location = System::Drawing::Point(279, 57);
			this->label33->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(555, 60);
			this->label33->TabIndex = 11;
			this->label33->Text = L"Recupera tu cuenta";
			// 
			// linkLabel2
			// 
			this->linkLabel2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linkLabel2->Location = System::Drawing::Point(1021, 467);
			this->linkLabel2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->linkLabel2->Name = L"linkLabel2";
			this->linkLabel2->Size = System::Drawing::Size(334, 34);
			this->linkLabel2->TabIndex = 13;
			this->linkLabel2->TabStop = true;
			this->linkLabel2->Text = L"Olvidaste tu contraseña\?";
			this->linkLabel2->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::linkLabel2_LinkClicked);
			this->linkLabel2->Click += gcnew System::EventHandler(this, &MyForm::linkLabel2_Click);
			// 
			// label31
			// 
			this->label31->BackColor = System::Drawing::Color::Transparent;
			this->label31->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label31->ForeColor = System::Drawing::SystemColors::Menu;
			this->label31->Location = System::Drawing::Point(138, 573);
			this->label31->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(672, 60);
			this->label31->TabIndex = 12;
			this->label31->Text = L"Conecta. Comparte. Chatee.";
			// 
			// pictureBox9
			// 
			this->pictureBox9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.Image")));
			this->pictureBox9->Location = System::Drawing::Point(249, 168);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(354, 358);
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
			this->label30->Location = System::Drawing::Point(197, 29);
			this->label30->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(486, 60);
			this->label30->TabIndex = 10;
			this->label30->Text = L"Bienvenido a Chatee";
			// 
			// panel7
			// 
			this->panel7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel7->Location = System::Drawing::Point(904, 3);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(26, 701);
			this->panel7->TabIndex = 9;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::Menu;
			this->label2->Location = System::Drawing::Point(1001, 511);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(360, 60);
			this->label2->TabIndex = 8;
			this->label2->Text = L"No tienes una cuenta\? ";
			// 
			// linkLabel1
			// 
			this->linkLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linkLabel1->Location = System::Drawing::Point(1103, 574);
			this->linkLabel1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(113, 34);
			this->linkLabel1->TabIndex = 7;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"Registrate";
			this->linkLabel1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::linkLabel1_MouseClick);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->Location = System::Drawing::Point(948, 271);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(54, 50);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 6;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->Location = System::Drawing::Point(948, 165);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(54, 47);
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
			this->button1->Location = System::Drawing::Point(1025, 377);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(256, 64);
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
			this->ContraText->Location = System::Drawing::Point(1025, 271);
			this->ContraText->Margin = System::Windows::Forms::Padding(4);
			this->ContraText->Multiline = true;
			this->ContraText->Name = L"ContraText";
			this->ContraText->Size = System::Drawing::Size(255, 63);
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
			this->UsuarioText->Location = System::Drawing::Point(1025, 162);
			this->UsuarioText->Margin = System::Windows::Forms::Padding(4);
			this->UsuarioText->Multiline = true;
			this->UsuarioText->Name = L"UsuarioText";
			this->UsuarioText->Size = System::Drawing::Size(255, 63);
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
			this->label1->Location = System::Drawing::Point(1067, 64);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(168, 60);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Login";
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panel4->Controls->Add(this->panelChats);
			this->panel4->Controls->Add(this->EditarPanel);
			this->panel4->Controls->Add(this->PanelEliminarPErf);
			this->panel4->Controls->Add(this->panel1);
			this->panel4->Controls->Add(this->SolicitudesPanel);
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
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(1754, 892);
			this->panel4->TabIndex = 28;
			this->panel4->Visible = false;
			// 
			// panelChats
			// 
			this->panelChats->Controls->Add(this->label39);
			this->panelChats->Controls->Add(this->button20);
			this->panelChats->Controls->Add(this->textBox20);
			this->panelChats->Controls->Add(this->listBox5);
			this->panelChats->Controls->Add(this->listBox4);
			this->panelChats->Controls->Add(this->label38);
			this->panelChats->Location = System::Drawing::Point(353, 132);
			this->panelChats->Name = L"panelChats";
			this->panelChats->Size = System::Drawing::Size(978, 543);
			this->panelChats->TabIndex = 28;
			this->panelChats->Visible = false;
			// 
			// label39
			// 
			this->label39->BackColor = System::Drawing::Color::Transparent;
			this->label39->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label39->ForeColor = System::Drawing::SystemColors::Menu;
			this->label39->Location = System::Drawing::Point(31, 12);
			this->label39->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(231, 61);
			this->label39->TabIndex = 15;
			this->label39->Text = L"Contactos";
			// 
			// button20
			// 
			this->button20->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button20->Location = System::Drawing::Point(805, 459);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(150, 72);
			this->button20->TabIndex = 14;
			this->button20->Text = L"Enviar";
			this->button20->UseVisualStyleBackColor = true;
			// 
			// textBox20
			// 
			this->textBox20->Location = System::Drawing::Point(464, 459);
			this->textBox20->Multiline = true;
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(282, 72);
			this->textBox20->TabIndex = 13;
			// 
			// listBox5
			// 
			this->listBox5->FormattingEnabled = true;
			this->listBox5->ItemHeight = 16;
			this->listBox5->Location = System::Drawing::Point(464, 83);
			this->listBox5->Name = L"listBox5";
			this->listBox5->Size = System::Drawing::Size(483, 356);
			this->listBox5->TabIndex = 12;
			// 
			// listBox4
			// 
			this->listBox4->FormattingEnabled = true;
			this->listBox4->ItemHeight = 16;
			this->listBox4->Location = System::Drawing::Point(35, 83);
			this->listBox4->Name = L"listBox4";
			this->listBox4->Size = System::Drawing::Size(295, 388);
			this->listBox4->TabIndex = 11;
			this->listBox4->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox4_SelectedIndexChanged);
			// 
			// label38
			// 
			this->label38->BackColor = System::Drawing::Color::Transparent;
			this->label38->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label38->ForeColor = System::Drawing::SystemColors::Menu;
			this->label38->Location = System::Drawing::Point(602, 6);
			this->label38->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(231, 61);
			this->label38->TabIndex = 10;
			this->label38->Text = L"Mensajes";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panel1->Controls->Add(this->panel6);
			this->panel1->Controls->Add(this->panel5);
			this->panel1->Controls->Add(this->pictureBox7);
			this->panel1->Controls->Add(this->label25);
			this->panel1->Controls->Add(this->button10);
			this->panel1->Controls->Add(this->button11);
			this->panel1->Location = System::Drawing::Point(353, 132);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(978, 543);
			this->panel1->TabIndex = 23;
			this->panel1->Visible = false;
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
			this->panel6->Location = System::Drawing::Point(242, 12);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(734, 525);
			this->panel6->TabIndex = 20;
			// 
			// label28
			// 
			this->label28->BackColor = System::Drawing::Color::Transparent;
			this->label28->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->ForeColor = System::Drawing::SystemColors::Menu;
			this->label28->Location = System::Drawing::Point(451, 25);
			this->label28->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(227, 34);
			this->label28->TabIndex = 19;
			this->label28->Text = L"Agregar Contactos";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label29->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label29->Location = System::Drawing::Point(11, 23);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(132, 17);
			this->label29->TabIndex = 18;
			this->label29->Text = L"Nombre de Usuario:\r\n";
			// 
			// button14
			// 
			this->button14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button14->Location = System::Drawing::Point(207, 54);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(129, 35);
			this->button14->TabIndex = 17;
			this->button14->Text = L"Buscar";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &MyForm::button14_Click);
			// 
			// textBox13
			// 
			this->textBox13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox13->Location = System::Drawing::Point(14, 59);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(144, 25);
			this->textBox13->TabIndex = 16;
			// 
			// button15
			// 
			this->button15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button15->Location = System::Drawing::Point(477, 374);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(144, 53);
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
			this->checkBox3->Location = System::Drawing::Point(472, 303);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(18, 17);
			this->checkBox3->TabIndex = 14;
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// textBox14
			// 
			this->textBox14->Enabled = false;
			this->textBox14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox14->Location = System::Drawing::Point(477, 238);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(144, 25);
			this->textBox14->TabIndex = 13;
			// 
			// pictureBox8
			// 
			this->pictureBox8->Location = System::Drawing::Point(477, 91);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(144, 113);
			this->pictureBox8->TabIndex = 12;
			this->pictureBox8->TabStop = false;
			// 
			// listBox2
			// 
			this->listBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 17;
			this->listBox2->Location = System::Drawing::Point(12, 116);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(368, 378);
			this->listBox2->TabIndex = 11;
			this->listBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox2_SelectedIndexChanged);
			// 
			// panel5
			// 
			this->panel5->Controls->Add(this->label27);
			this->panel5->Controls->Add(this->label26);
			this->panel5->Controls->Add(this->button13);
			this->panel5->Controls->Add(this->textBox12);
			this->panel5->Controls->Add(this->button12);
			this->panel5->Controls->Add(this->checkBox2);
			this->panel5->Controls->Add(this->textBox11);
			this->panel5->Controls->Add(this->pictureBox5);
			this->panel5->Controls->Add(this->listBox1);
			this->panel5->Location = System::Drawing::Point(242, 12);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(732, 531);
			this->panel5->TabIndex = 10;
			// 
			// label27
			// 
			this->label27->BackColor = System::Drawing::Color::Transparent;
			this->label27->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->ForeColor = System::Drawing::SystemColors::Menu;
			this->label27->Location = System::Drawing::Point(433, 33);
			this->label27->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(294, 34);
			this->label27->TabIndex = 19;
			this->label27->Text = L"Contactos Agregados";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label26->Location = System::Drawing::Point(11, 23);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(132, 17);
			this->label26->TabIndex = 18;
			this->label26->Text = L"Nombre de Usuario:\r\n";
			// 
			// button13
			// 
			this->button13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button13->Location = System::Drawing::Point(207, 54);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(129, 35);
			this->button13->TabIndex = 17;
			this->button13->Text = L"Buscar";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &MyForm::button13_Click);
			// 
			// textBox12
			// 
			this->textBox12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox12->Location = System::Drawing::Point(14, 59);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(144, 25);
			this->textBox12->TabIndex = 16;
			// 
			// button12
			// 
			this->button12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button12->Location = System::Drawing::Point(477, 374);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(144, 53);
			this->button12->TabIndex = 15;
			this->button12->Text = L"Eliminar";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Indeterminate;
			this->checkBox2->Enabled = false;
			this->checkBox2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->checkBox2->Location = System::Drawing::Point(472, 303);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(18, 17);
			this->checkBox2->TabIndex = 14;
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// textBox11
			// 
			this->textBox11->Enabled = false;
			this->textBox11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox11->Location = System::Drawing::Point(477, 238);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(144, 25);
			this->textBox11->TabIndex = 13;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Location = System::Drawing::Point(477, 91);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(144, 113);
			this->pictureBox5->TabIndex = 12;
			this->pictureBox5->TabStop = false;
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 17;
			this->listBox1->Location = System::Drawing::Point(12, 116);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(368, 378);
			this->listBox1->TabIndex = 11;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// pictureBox7
			// 
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(92, 400);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(51, 51);
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
			this->label25->Location = System::Drawing::Point(4, 9);
			this->label25->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(231, 61);
			this->label25->TabIndex = 9;
			this->label25->Text = L"Contactos";
			// 
			// button10
			// 
			this->button10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button10->Location = System::Drawing::Point(15, 295);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(197, 53);
			this->button10->TabIndex = 8;
			this->button10->Text = L"Agregar";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// button11
			// 
			this->button11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button11->Location = System::Drawing::Point(14, 184);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(197, 53);
			this->button11->TabIndex = 7;
			this->button11->Text = L"Ver Contactos";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click);
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
			this->PanelEliminarPErf->Location = System::Drawing::Point(354, 133);
			this->PanelEliminarPErf->Name = L"PanelEliminarPErf";
			this->PanelEliminarPErf->Size = System::Drawing::Size(976, 540);
			this->PanelEliminarPErf->TabIndex = 19;
			this->PanelEliminarPErf->Visible = false;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label24->Location = System::Drawing::Point(527, 192);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(75, 17);
			this->label24->TabIndex = 22;
			this->label24->Text = L"Respuesta: \r\n";
			// 
			// textBox10
			// 
			this->textBox10->Enabled = false;
			this->textBox10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox10->Location = System::Drawing::Point(624, 140);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(256, 25);
			this->textBox10->TabIndex = 21;
			// 
			// Eliminar
			// 
			this->Eliminar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Eliminar->Location = System::Drawing::Point(426, 357);
			this->Eliminar->Name = L"Eliminar";
			this->Eliminar->Size = System::Drawing::Size(129, 53);
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
			this->label23->Location = System::Drawing::Point(536, 142);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(46, 17);
			this->label23->TabIndex = 19;
			this->label23->Text = L"Frase: \r\n";
			// 
			// textBox9
			// 
			this->textBox9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox9->Location = System::Drawing::Point(624, 192);
			this->textBox9->Multiline = true;
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(256, 84);
			this->textBox9->TabIndex = 18;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label21->Location = System::Drawing::Point(73, 222);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(139, 17);
			this->label21->TabIndex = 17;
			this->label21->Text = L"Confirmar Contraseña:\r\n";
			// 
			// textBox7
			// 
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox7->Location = System::Drawing::Point(252, 220);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(181, 25);
			this->textBox7->TabIndex = 16;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label22->Location = System::Drawing::Point(73, 158);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(116, 17);
			this->label22->TabIndex = 15;
			this->label22->Text = L"Contraseña Actual:\r\n";
			// 
			// textBox8
			// 
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox8->Location = System::Drawing::Point(252, 159);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(181, 25);
			this->textBox8->TabIndex = 14;
			// 
			// label14
			// 
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::SystemColors::Menu;
			this->label14->Location = System::Drawing::Point(345, 31);
			this->label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(333, 60);
			this->label14->TabIndex = 3;
			this->label14->Text = L"Eliminar Perfil";
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
			this->SolicitudesPanel->Location = System::Drawing::Point(356, 138);
			this->SolicitudesPanel->Name = L"SolicitudesPanel";
			this->SolicitudesPanel->Size = System::Drawing::Size(971, 535);
			this->SolicitudesPanel->TabIndex = 23;
			this->SolicitudesPanel->Visible = false;
			// 
			// textBox15
			// 
			this->textBox15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox15->Location = System::Drawing::Point(632, 317);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(231, 25);
			this->textBox15->TabIndex = 9;
			// 
			// pictureBox10
			// 
			this->pictureBox10->Location = System::Drawing::Point(622, 138);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(228, 100);
			this->pictureBox10->TabIndex = 8;
			this->pictureBox10->TabStop = false;
			// 
			// button17
			// 
			this->button17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button17->Location = System::Drawing::Point(763, 422);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(97, 23);
			this->button17->TabIndex = 7;
			this->button17->Text = L"Rechazar";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &MyForm::button17_Click);
			// 
			// button16
			// 
			this->button16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button16->Location = System::Drawing::Point(632, 422);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(97, 23);
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
			this->listBox3->ItemHeight = 17;
			this->listBox3->Location = System::Drawing::Point(100, 131);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(391, 344);
			this->listBox3->TabIndex = 5;
			this->listBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox3_SelectedIndexChanged);
			// 
			// label32
			// 
			this->label32->BackColor = System::Drawing::Color::Transparent;
			this->label32->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label32->ForeColor = System::Drawing::SystemColors::Menu;
			this->label32->Location = System::Drawing::Point(387, 41);
			this->label32->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(295, 60);
			this->label32->TabIndex = 4;
			this->label32->Text = L"Solicitudes";
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
			this->EditarPanel->Location = System::Drawing::Point(354, 133);
			this->EditarPanel->Name = L"EditarPanel";
			this->EditarPanel->Size = System::Drawing::Size(975, 540);
			this->EditarPanel->TabIndex = 7;
			this->EditarPanel->Visible = false;
			// 
			// button9
			// 
			this->button9->ForeColor = System::Drawing::SystemColors::GrayText;
			this->button9->Location = System::Drawing::Point(426, 419);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(192, 45);
			this->button9->TabIndex = 18;
			this->button9->Text = L"Modificar\r\n";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// pictureBox6
			// 
			this->pictureBox6->Location = System::Drawing::Point(498, 116);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(149, 125);
			this->pictureBox6->TabIndex = 17;
			this->pictureBox6->TabStop = false;
			// 
			// button8
			// 
			this->button8->ForeColor = System::Drawing::SystemColors::GrayText;
			this->button8->Location = System::Drawing::Point(530, 258);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(88, 28);
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
			this->label20->Location = System::Drawing::Point(28, 409);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(41, 17);
			this->label20->TabIndex = 15;
			this->label20->Text = L"Edad:\r\n";
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox6->Location = System::Drawing::Point(188, 407);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(181, 25);
			this->textBox6->TabIndex = 14;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label19->Location = System::Drawing::Point(28, 347);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(118, 17);
			this->label19->TabIndex = 13;
			this->label19->Text = L"Contraseña Nueva:\r\n";
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(188, 342);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(181, 25);
			this->textBox5->TabIndex = 12;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label18->Location = System::Drawing::Point(28, 280);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(113, 17);
			this->label18->TabIndex = 11;
			this->label18->Text = L"Contraseña Actual";
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(188, 284);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(181, 25);
			this->textBox4->TabIndex = 10;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label17->Location = System::Drawing::Point(28, 225);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(120, 51);
			this->label17->TabIndex = 9;
			this->label17->Text = L"Correo Electronico:\r\n\r\n\r\n";
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(188, 223);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(181, 25);
			this->textBox3->TabIndex = 8;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label16->Location = System::Drawing::Point(28, 167);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(121, 17);
			this->label16->TabIndex = 7;
			this->label16->Text = L"Nombre Completo:\r\n";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(188, 165);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(181, 25);
			this->textBox2->TabIndex = 6;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label15->Location = System::Drawing::Point(28, 116);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(132, 17);
			this->label15->TabIndex = 5;
			this->label15->Text = L"Nombre de Usuario: ";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(188, 114);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(181, 25);
			this->textBox1->TabIndex = 4;
			// 
			// label13
			// 
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::SystemColors::Menu;
			this->label13->Location = System::Drawing::Point(396, 18);
			this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(292, 60);
			this->label13->TabIndex = 3;
			this->label13->Text = L"Editar Perfil";
			// 
			// panel11
			// 
			this->panel11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel11->Location = System::Drawing::Point(1327, 132);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(32, 543);
			this->panel11->TabIndex = 27;
			// 
			// panel10
			// 
			this->panel10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel10->Location = System::Drawing::Point(353, 674);
			this->panel10->Name = L"panel10";
			this->panel10->Size = System::Drawing::Size(1005, 31);
			this->panel10->TabIndex = 26;
			// 
			// panel9
			// 
			this->panel9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel9->Location = System::Drawing::Point(353, 101);
			this->panel9->Name = L"panel9";
			this->panel9->Size = System::Drawing::Size(1005, 37);
			this->panel9->TabIndex = 25;
			// 
			// panel8
			// 
			this->panel8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panel8->Location = System::Drawing::Point(321, 101);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(37, 604);
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
			this->checkBox1->Location = System::Drawing::Point(321, 45);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(67, 20);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"Online";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// button7
			// 
			this->button7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button7->Location = System::Drawing::Point(34, 479);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(250, 53);
			this->button7->TabIndex = 6;
			this->button7->Text = L"Solicitudes";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(34, 609);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(77, 66);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox4->TabIndex = 5;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &MyForm::pictureBox4_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button5->Location = System::Drawing::Point(34, 388);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(250, 53);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Contactos";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(34, 299);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(250, 53);
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
			this->LabelNombre->Location = System::Drawing::Point(602, 29);
			this->LabelNombre->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->LabelNombre->Name = L"LabelNombre";
			this->LabelNombre->Size = System::Drawing::Size(595, 60);
			this->LabelNombre->TabIndex = 2;
			this->LabelNombre->Text = L"Bienvenido ";
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(34, 38);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(250, 164);
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
			this->panel3->Margin = System::Windows::Forms::Padding(4);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(1361, 704);
			this->panel3->TabIndex = 11;
			this->panel3->Visible = false;
			// 
			// button6
			// 
			this->button6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button6->ForeColor = System::Drawing::SystemColors::ScrollBar;
			this->button6->Location = System::Drawing::Point(714, 529);
			this->button6->Margin = System::Windows::Forms::Padding(4);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(187, 57);
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
			this->button3->Location = System::Drawing::Point(580, 180);
			this->button3->Margin = System::Windows::Forms::Padding(4);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(113, 28);
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
			this->label12->Location = System::Drawing::Point(1119, 213);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(163, 28);
			this->label12->TabIndex = 26;
			this->label12->Text = L"Respuesta:";
			// 
			// Respuesta
			// 
			this->Respuesta->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Respuesta->Location = System::Drawing::Point(1051, 245);
			this->Respuesta->Margin = System::Windows::Forms::Padding(4);
			this->Respuesta->Multiline = true;
			this->Respuesta->Name = L"Respuesta";
			this->Respuesta->Size = System::Drawing::Size(281, 126);
			this->Respuesta->TabIndex = 25;
			// 
			// label11
			// 
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::SystemColors::Menu;
			this->label11->Location = System::Drawing::Point(1072, 92);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(232, 28);
			this->label11->TabIndex = 24;
			this->label11->Text = L"Pregunta de Seguridad:";
			// 
			// Edad
			// 
			this->Edad->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Edad->Location = System::Drawing::Point(259, 462);
			this->Edad->Margin = System::Windows::Forms::Padding(4);
			this->Edad->Name = L"Edad";
			this->Edad->Size = System::Drawing::Size(192, 29);
			this->Edad->TabIndex = 23;
			// 
			// Validarcontra
			// 
			this->Validarcontra->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Validarcontra->Location = System::Drawing::Point(259, 406);
			this->Validarcontra->Margin = System::Windows::Forms::Padding(4);
			this->Validarcontra->Name = L"Validarcontra";
			this->Validarcontra->Size = System::Drawing::Size(192, 29);
			this->Validarcontra->TabIndex = 22;
			// 
			// Contra
			// 
			this->Contra->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Contra->Location = System::Drawing::Point(259, 341);
			this->Contra->Margin = System::Windows::Forms::Padding(4);
			this->Contra->Name = L"Contra";
			this->Contra->Size = System::Drawing::Size(192, 29);
			this->Contra->TabIndex = 21;
			// 
			// Correo
			// 
			this->Correo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Correo->Location = System::Drawing::Point(259, 267);
			this->Correo->Margin = System::Windows::Forms::Padding(4);
			this->Correo->Name = L"Correo";
			this->Correo->Size = System::Drawing::Size(192, 29);
			this->Correo->TabIndex = 20;
			// 
			// NomCompleto
			// 
			this->NomCompleto->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NomCompleto->Location = System::Drawing::Point(259, 198);
			this->NomCompleto->Margin = System::Windows::Forms::Padding(4);
			this->NomCompleto->Name = L"NomCompleto";
			this->NomCompleto->Size = System::Drawing::Size(192, 29);
			this->NomCompleto->TabIndex = 19;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::SystemColors::ScrollBar;
			this->button2->Location = System::Drawing::Point(506, 529);
			this->button2->Margin = System::Windows::Forms::Padding(4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(187, 57);
			this->button2->TabIndex = 18;
			this->button2->Text = L"Guardar";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click_1);
			// 
			// NomUsuario
			// 
			this->NomUsuario->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NomUsuario->Location = System::Drawing::Point(259, 135);
			this->NomUsuario->Margin = System::Windows::Forms::Padding(4);
			this->NomUsuario->Name = L"NomUsuario";
			this->NomUsuario->Size = System::Drawing::Size(192, 29);
			this->NomUsuario->TabIndex = 11;
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::SystemColors::Menu;
			this->label10->Location = System::Drawing::Point(552, 133);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(163, 28);
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
			this->Combopregunta->Location = System::Drawing::Point(1051, 135);
			this->Combopregunta->Margin = System::Windows::Forms::Padding(4);
			this->Combopregunta->Name = L"Combopregunta";
			this->Combopregunta->Size = System::Drawing::Size(281, 24);
			this->Combopregunta->TabIndex = 9;
			// 
			// ImagenPerf
			// 
			this->ImagenPerf->Location = System::Drawing::Point(761, 132);
			this->ImagenPerf->Margin = System::Windows::Forms::Padding(4);
			this->ImagenPerf->Name = L"ImagenPerf";
			this->ImagenPerf->Size = System::Drawing::Size(140, 76);
			this->ImagenPerf->TabIndex = 8;
			this->ImagenPerf->TabStop = false;
			// 
			// label9
			// 
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::SystemColors::Menu;
			this->label9->Location = System::Drawing::Point(40, 462);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(135, 28);
			this->label9->TabIndex = 7;
			this->label9->Text = L"Edad: ";
			// 
			// label8
			// 
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::SystemColors::Menu;
			this->label8->Location = System::Drawing::Point(40, 406);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(211, 28);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Confirmar Contraseña: ";
			// 
			// label7
			// 
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::SystemColors::Menu;
			this->label7->Location = System::Drawing::Point(40, 343);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(181, 28);
			this->label7->TabIndex = 5;
			this->label7->Text = L"Contraseña: ";
			// 
			// label6
			// 
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::SystemColors::Menu;
			this->label6->Location = System::Drawing::Point(40, 271);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(181, 28);
			this->label6->TabIndex = 4;
			this->label6->Text = L"Correo Electronico:";
			// 
			// label5
			// 
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::SystemColors::Menu;
			this->label5->Location = System::Drawing::Point(40, 198);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(211, 28);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Nombre Completo:";
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::SystemColors::Menu;
			this->label4->Location = System::Drawing::Point(40, 132);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(211, 28);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Nombre: De Usuario: ";
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::Menu;
			this->label3->Location = System::Drawing::Point(524, 11);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(412, 60);
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
			this->Menu->Size = System::Drawing::Size(195, 76);
			// 
			// personalizarPerfilToolStripMenuItem
			// 
			this->personalizarPerfilToolStripMenuItem->Name = L"personalizarPerfilToolStripMenuItem";
			this->personalizarPerfilToolStripMenuItem->Size = System::Drawing::Size(194, 24);
			this->personalizarPerfilToolStripMenuItem->Text = L"Personalizar Perfil";
			this->personalizarPerfilToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::personalizarPerfilToolStripMenuItem_Click);
			// 
			// eliminarPerfilToolStripMenuItem
			// 
			this->eliminarPerfilToolStripMenuItem->Name = L"eliminarPerfilToolStripMenuItem";
			this->eliminarPerfilToolStripMenuItem->Size = System::Drawing::Size(194, 24);
			this->eliminarPerfilToolStripMenuItem->Text = L"Eliminar Perfil";
			this->eliminarPerfilToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::eliminarPerfilToolStripMenuItem_Click);
			// 
			// cerrarSesionToolStripMenuItem
			// 
			this->cerrarSesionToolStripMenuItem->Name = L"cerrarSesionToolStripMenuItem";
			this->cerrarSesionToolStripMenuItem->Size = System::Drawing::Size(194, 24);
			this->cerrarSesionToolStripMenuItem->Text = L"Cerrar Sesion";
			this->cerrarSesionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cerrarSesionToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1361, 702);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel3);
			this->Margin = System::Windows::Forms::Padding(4);
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
			this->panelChats->ResumeLayout(false);
			this->panelChats->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			this->PanelEliminarPErf->ResumeLayout(false);
			this->PanelEliminarPErf->PerformLayout();
			this->SolicitudesPanel->ResumeLayout(false);
			this->SolicitudesPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			this->EditarPanel->ResumeLayout(false);
			this->EditarPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImagenPerf))->EndInit();
			this->Menu->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		bool esPlaceholderUsuario = true;
		bool esPlaceholderContrasena = true;

	private: System::Void textBox1_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		if (UsuarioText->Text->Trim() == "") {
			UsuarioText->Text = "Usuario";
			UsuarioText->ForeColor = Color::Gray;
			esPlaceholderUsuario = true;
		}
	}

	private: System::Void textBox2_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		if (ContraText->Text->Trim() == "") {
			ContraText->Text = "Contraseña";
			ContraText->ForeColor = Color::Gray;
			ContraText->UseSystemPasswordChar = false;
			esPlaceholderContrasena = true;
		}
	}

	private: System::Void textBox2_MouseEnter(System::Object^ sender, System::EventArgs^ e) {

		if (esPlaceholderContrasena) {
			ContraText->Text = "";
			ContraText->ForeColor = Color::Black;
			ContraText->UseSystemPasswordChar = true;
			esPlaceholderContrasena = false;
		}
	}
	private: System::Void textBox1_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		if (esPlaceholderUsuario) {
			UsuarioText->Text = "";
			UsuarioText->ForeColor = Color::Black;
			esPlaceholderUsuario = false;
		}
	}
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

	private: System::Void listBox_DrawItem(System::Object^ sender, DrawItemEventArgs^ e)
	{
		if (e->Index < 0) return;

		ListBox^ lb = (ListBox^)sender;
		String^ text = lb->Items[e->Index]->ToString();

		Color bgColor = Color::FromArgb(173, 216, 230);
		Color textColor = Color::Black;

		// Si está seleccionado, cambia el color
		if ((e->State & DrawItemState::Selected) == DrawItemState::Selected)
		{
			bgColor = Color::FromArgb(100, 149, 237); // Azul más fuerte
			textColor = Color::White;
		}

		// Dibujar fondo
		e->Graphics->FillRectangle(gcnew SolidBrush(bgColor), e->Bounds);

		// Centrar texto vertical y horizontal
		StringFormat^ sf = gcnew StringFormat();
		sf->Alignment = StringAlignment::Near;
		sf->LineAlignment = StringAlignment::Center;

		Rectangle rect = e->Bounds;
		rect.X += 10; // margen izquierdo

		// Dibujar texto
		e->Graphics->DrawString(text, e->Font, gcnew SolidBrush(textColor), rect, sf);

		// Dibujar borde opcional
		e->Graphics->DrawRectangle(Pens::LightGray, e->Bounds);
	}



	private: System::Void linkLabel1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		panel4->Visible = false;
		panel2->Visible = false;
		panel3->Visible = true;
	}


	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ dialog = gcnew OpenFileDialog();

		dialog->Filter = "Archivos de imagen|*.jpg;*.jpeg;*.png;*.bmp";
		dialog->Title = "Selecciona una imagen de perfil";

		if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			ImagenPerf->Image = Image::FromFile(dialog->FileName);
			ImagenPerf->SizeMode = PictureBoxSizeMode::Zoom;
		}
	}

	private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		lista->GuardarEnArchivo();
		x->persona->SetEstado(false);
	}

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


		if (perfIm == nullptr) {
			perfIm = Image::FromFile("C:\\Users\\hapav\\Downloads\\Project2\\4powQ.jpg");
			ImagenPerf->Image = perfIm;
			ImagenPerf->SizeMode = PictureBoxSizeMode::Zoom;
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

		Persona^ personaNueva = gcnew Persona(NomUs, NomCom, corr, con, ed, perfIm, seleccion, Res);
		lista->OrdenarPorUsername();
		lista->Add(personaNueva);

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
		ImagenPerf->Image = Image::FromFile("C:\\Users\\hapav\\Downloads\\Project2\\4powQ.jpg");

	}



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

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ usuario = UsuarioText->Text;
		String^ contra = ContraText->Text->Trim();
		lista->OrdenarPorUsername();
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


	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		panel3->Visible = false;
		panel4->Visible = false;
		panel2->Visible = true;
	}
	private: System::Void button3_Click_1(System::Object^ sender, System::EventArgs^ e) {
		SeleccionarImagen(ImagenPerf);
	}

	private: System::Void pictureBox4_Click(System::Object^ sender, System::EventArgs^ e) {
		Menu->Show(pictureBox4, System::Drawing::Point(0, pictureBox4->Height));
	}

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

		MessageBox::Show("Perfil actualizado con éxito.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);


	}

	private: System::Void personalizarPerfilToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

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
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
		SeleccionarImagen(pictureBox6);
	}
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

	private: System::Void eliminarPerfilToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		panel2->Visible = false;
		panel3->Visible = false;
		EditarPanel->Visible = false;
		panel4->Visible = true;
		SolicitudesPanel->Visible = false;
		PanelEliminarPErf->BringToFront();
		PanelEliminarPErf->Visible = true;
		textBox10->Text = x->persona->GetPreguntaSeguridad();

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
				Logout();
			}
		}


	}
	private: System::Void Logout() {
		panel3->Visible = false;
		panel4->Visible = false;
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		panel2->Visible = true;
		panel1->Visible = false;
		panel5->Visible = false;
		panel6->Visible = false;

	}
	private: System::Void cerrarSesionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult resultado = MessageBox::Show(
			"¿Está seguro de que desea cerrar sesion de su cuenta?",
			"Confirmar",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Warning);
		if (resultado == System::Windows::Forms::DialogResult::Yes) {
			Logout();
			lista->GuardarEnArchivo();
			x->persona->SetEstado(false); 
		}
	}
	private: System::Void button13_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nombreusuario = textBox12->Text->Trim();
		x->persona->GetListaContactos()->OrdenarPorUsername();
		Nodo^ resultado = x->persona->GetListaContactos()->buscar(nombreusuario, 1);
		listBox1->Items->Clear();

		if (resultado != nullptr) {
			String^ usuario = resultado->persona->GetNombreUsuario();
			listBox1->Items->Add(usuario);
			MessageBox::Show("Usuario encontrado!");
		}
		else {
			MessageBox::Show("Usuario no encontrado");
		}
	}
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
	private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listBox1->SelectedItem != nullptr) {
			Persona^ persona = dynamic_cast<Persona^>(listBox1->SelectedItem);
			x->persona->GetListaContactos()->OrdenarPorUsername();
			x->persona->GetListaContactos()->Eliminar(persona->GetNombreUsuario());
			MessageBox::Show("Usuario Eliminado Exitosamente!");
		}
		else {
			MessageBox::Show("Tiene que eligir un usuario para eliminarlo");
		}

		textBox11->Text = "";
		pictureBox5->Image = nullptr;
		checkBox2->Checked = false;
		checkBox2->Text = "";
	}
	private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e) {
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		panel6->Visible = false;
		SolicitudesPanel->Visible = false;
		panel5->Visible = true;
		panel1->Visible = true;
		x->persona->GetListaContactos()->OrdenarPorUsername();
		x->persona->GetListaContactos()->agregarList(listBox1);
	}


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
	private: System::Void button14_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nombreusuario = textBox13->Text->Trim();
		lista->OrdenarPorUsername();
		Nodo^ resultado = lista->BuscarPersona(nombreusuario, 1);

		listBox2->Items->Clear();

		if (resultado != nullptr) {
			String^ usuario = resultado->persona->GetNombreUsuario();
			listBox2->Items->Add(usuario);
			MessageBox::Show("Usuario encontrado!");
		}
		else {
			MessageBox::Show("Usuario no encontrado");
		}
	}
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
	private: System::Void button15_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listBox2->SelectedItem != nullptr) {
			Persona^ destino = dynamic_cast<Persona^>(listBox2->SelectedItem);
			Gestion::EnviarSolicitud(x->persona, destino);
		}
		else {
			MessageBox::Show("Debe seleccionar una persona para mandar solicitud", "Error",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		textBox14->Text = "";
		pictureBox8->Image = nullptr;
		checkBox3->Checked = false;
		checkBox3->Text = "";
	}

	private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
		panel5->Visible = false;
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		SolicitudesPanel->Visible = false;
		panel1->Visible = true;
		panel6->Visible = true;
		// Validar que no se muestre el propio usuario 
		lista->agregarList(listBox2);
		lista->OrdenarPorUsername();
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		PanelEliminarPErf->Visible = false;
		EditarPanel->Visible = false;
		SolicitudesPanel->Visible = false;
		panel1->Visible = true;
		panel1->BringToFront();
		lista->OrdenarPorUsername();
		lista->agregarList(listBox2);
		x->persona->GetListaContactos()->OrdenarPorUsername();
		x->persona->GetListaContactos()->agregarList(listBox1);
	}
	private: System::Void listBox3_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (listBox3->SelectedItem != nullptr) {
			Persona^ persona = dynamic_cast<Persona^>(listBox3->SelectedItem);
			textBox15->Text = persona->GetNombreUsuario();
			pictureBox10->Image = persona->GetImagenPerfil();
			pictureBox10->SizeMode = PictureBoxSizeMode::Zoom;

		}
	}
	private: System::Void button16_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listBox3->SelectedItem != nullptr) {
			Persona^ persona = dynamic_cast<Persona^>(listBox3->SelectedItem);
			Gestion::AceptarSolicitud(x->persona, persona);
		}
		else {
			MessageBox::Show("No seleccionó ningún usuario");
		}
		textBox15->Text = "";
		pictureBox10->Image = nullptr;
	}
	private: System::Void button17_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listBox3->SelectedItem != nullptr) {
			Persona^ persona = dynamic_cast<Persona^>(listBox3->SelectedItem);
			Gestion::RechazarSolicitud(x->persona, persona);
		}
		else {
			MessageBox::Show("No seleccionó ningún usuario");
		}
		textBox15->Text = "";
		pictureBox10->Image = nullptr;

	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
		EditarPanel->Visible = false;
		PanelEliminarPErf->Visible = false;
		panel1->Visible = false;
		SolicitudesPanel->Visible = true;
		SolicitudesPanel->BringToFront();
		x->persona->GetSolicitudesRecibidas()->OrdenarPorUsername();
		x->persona->GetSolicitudesRecibidas()->agregarList(listBox3);


	}
	private: System::Void linkLabel2_Click(System::Object^ sender, System::EventArgs^ e) {




	}
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
	}
	private: System::Void button19_Click(System::Object^ sender, System::EventArgs^ e) {
		OlvidastePanel->Visible = false;
		textBox17->Text = "";
		textBox19->Text = "";
		textBox18->Text = "";
	}

		// Falta 

private: System::Void listBox4_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) { 
	panel1->Visible = false; 
	EditarPanel->Visible = false; 
	PanelEliminarPErf->Visible = false; 
	SolicitudesPanel->Visible = false; 
	panelChats->Visible = true; 
	x->persona->GetListaContactos()->OrdenarPorUsername(); 
	x->persona->GetListaContactos()->agregarList(listBox4);

}
};
}
