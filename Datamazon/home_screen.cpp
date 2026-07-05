#include "home_screen.h"
#include "Infrastructure/Sorting/Sorting.h"

using namespace Datamazon;

bool compareNameAsc(Product* a, Product* b) {
	return a->getName() < b->getName();
}
bool compareNameDesc(Product* a, Product* b) {
	return a->getName() > b->getName();
}
bool comparePriceAsc(Product* a, Product* b) {
	return a->getPrice() < b->getPrice();
}
bool comparePriceDesc(Product* a, Product* b) {
	return a->getPrice() > b->getPrice();
}
bool compareStockAsc(Product* a, Product* b) {
	return a->getStock() < b->getStock();
}
bool compareStockDesc(Product* a, Product* b) {
	return a->getStock() > b->getStock();
}

void home_screen::InitializeComponent(void)
{
	this->components = gcnew System::ComponentModel::Container();
	this->SetStyle(ControlStyles::AllPaintingInWmPaint | ControlStyles::OptimizedDoubleBuffer | ControlStyles::ResizeRedraw, true);
	this->Size = System::Drawing::Size(1100, 750);
	this->Text = L"Datamazon Store";
	this->StartPosition = FormStartPosition::CenterScreen;
	this->BackColor = Color::FromArgb(245, 245, 245);
	this->DoubleBuffered = true;
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->MaximizeBox = false;

	this->panelHeader = gcnew Panel();
	this->panelHeader->Size = System::Drawing::Size(1100, 70);
	this->panelHeader->Dock = DockStyle::Top;
	this->panelHeader->Paint += gcnew PaintEventHandler(this, &home_screen::panelHeader_Paint);

	this->picLogo = gcnew PictureBox();
	this->picLogo->Size = System::Drawing::Size(160, 48);
	this->picLogo->Location = Point(25, 10);
	this->picLogo->SizeMode = PictureBoxSizeMode::Zoom;
	this->picLogo->BackColor = Color::Transparent;
	String^ logoPath = "logo.png";
	if (!System::IO::File::Exists(logoPath)) {
		logoPath = System::IO::Path::Combine(System::AppDomain::CurrentDomain->BaseDirectory, "logo.png");
	}
	if (!System::IO::File::Exists(logoPath)) {
		logoPath = "../logo.png";
	}
	try {
		if (System::IO::File::Exists(logoPath)) {
			this->picLogo->Image = Image::FromFile(logoPath);
		}
	} catch (...) {}

	this->panelSearchBox = gcnew Panel();
	this->panelSearchBox->Size = System::Drawing::Size(420, 38);
	this->panelSearchBox->Location = Point(230, 16);
	this->panelSearchBox->BackColor = Color::Transparent;
	this->panelSearchBox->Paint += gcnew PaintEventHandler(this, &home_screen::panelSearchBox_Paint);

	this->txtSearch = gcnew TextBox();
	this->txtSearch->Size = System::Drawing::Size(390, 24);
	this->txtSearch->Location = Point(15, 7);
	this->txtSearch->BorderStyle = BorderStyle::None;
	this->txtSearch->BackColor = Color::White;
	this->txtSearch->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
	this->txtSearch->TextChanged += gcnew EventHandler(this, &home_screen::txtSearch_TextChanged);
	this->panelSearchBox->Controls->Add(this->txtSearch);

	this->btnCartToggle = gcnew Button();
	this->btnCartToggle->Text = L"\U0001F6D2 Carrito (0)";
	this->btnCartToggle->Size = System::Drawing::Size(145, 38);
	this->btnCartToggle->Location = Point(770, 16);
	styleButton(this->btnCartToggle, Color::FromArgb(255, 153, 0), Color::White, Color::FromArgb(230, 130, 0), Color::FromArgb(200, 110, 0), 9);
	this->btnCartToggle->Click += gcnew EventHandler(this, &home_screen::btnCartToggle_Click);
	setRegionRounded(this->btnCartToggle, 19);

	this->btnAdminToggle = gcnew Button();
	this->btnAdminToggle->Text = L"Admin Panel";
	this->btnAdminToggle->Size = System::Drawing::Size(120, 38);
	this->btnAdminToggle->Location = Point(935, 16);
	styleButton(this->btnAdminToggle, Color::FromArgb(55, 71, 90), Color::White, Color::FromArgb(71, 85, 105), Color::FromArgb(51, 65, 85), 9);
	this->btnAdminToggle->Click += gcnew EventHandler(this, &home_screen::btnAdminToggle_Click);
	setRegionRounded(this->btnAdminToggle, 19);

	this->panelHeader->Controls->Add(this->picLogo);
	this->panelHeader->Controls->Add(this->panelSearchBox);
	this->panelHeader->Controls->Add(this->btnCartToggle);
	this->panelHeader->Controls->Add(this->btnAdminToggle);

	this->panelFilters = gcnew Panel();
	this->panelFilters->Size = System::Drawing::Size(195, 630);
	this->panelFilters->Location = Point(10, 80);
	this->panelFilters->BackColor = Color::White;
	this->panelFilters->Paint += gcnew PaintEventHandler(this, &home_screen::panelFilters_Paint);
	setRegionRounded(this->panelFilters, 16);

	this->lblFiltersTitle = gcnew Label();
	this->lblFiltersTitle->Text = L"Filtros";
	this->lblFiltersTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 13, FontStyle::Bold);
	this->lblFiltersTitle->ForeColor = Color::FromArgb(15, 17, 17);
	this->lblFiltersTitle->Location = Point(20, 20);
	this->lblFiltersTitle->AutoSize = true;

	Label^ lblCatLabel = gcnew Label();
	lblCatLabel->Text = L"Categoria";
	lblCatLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
	lblCatLabel->ForeColor = Color::FromArgb(86, 89, 89);
	lblCatLabel->Location = Point(20, 65);
	lblCatLabel->AutoSize = true;

	this->cbCategories = gcnew ComboBox();
	this->cbCategories->Size = System::Drawing::Size(155, 28);
	this->cbCategories->Location = Point(20, 88);
	this->cbCategories->DropDownStyle = ComboBoxStyle::DropDownList;
	this->cbCategories->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
	this->cbCategories->FlatStyle = FlatStyle::Flat;
	this->cbCategories->BackColor = Color::FromArgb(248, 250, 252);
	this->cbCategories->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
	this->cbCategories->DrawItem += gcnew DrawItemEventHandler(this, &home_screen::comboBox_DrawItem);

	Label^ lblPriceLabel = gcnew Label();
	lblPriceLabel->Text = L"Rango de Precio";
	lblPriceLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
	lblPriceLabel->ForeColor = Color::FromArgb(86, 89, 89);
	lblPriceLabel->Location = Point(20, 135);
	lblPriceLabel->AutoSize = true;

	this->panelMinPrice = gcnew Panel();
	this->panelMinPrice->Size = System::Drawing::Size(65, 30);
	this->panelMinPrice->Location = Point(20, 160);
	this->panelMinPrice->BackColor = Color::Transparent;
	this->panelMinPrice->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);

	this->txtMinPrice = gcnew TextBox();
	this->txtMinPrice->Size = System::Drawing::Size(53, 18);
	this->txtMinPrice->Location = Point(6, 6);
	this->txtMinPrice->Text = L"0";
	this->txtMinPrice->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
	this->txtMinPrice->BorderStyle = BorderStyle::None;
	this->txtMinPrice->BackColor = Color::White;
	this->panelMinPrice->Controls->Add(this->txtMinPrice);

	Label^ lblDash = gcnew Label();
	lblDash->Text = L"-";
	lblDash->Location = Point(90, 163);
	lblDash->AutoSize = true;

	this->panelMaxPrice = gcnew Panel();
	this->panelMaxPrice->Size = System::Drawing::Size(65, 30);
	this->panelMaxPrice->Location = Point(107, 160);
	this->panelMaxPrice->BackColor = Color::Transparent;
	this->panelMaxPrice->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);

	this->txtMaxPrice = gcnew TextBox();
	this->txtMaxPrice->Size = System::Drawing::Size(53, 18);
	this->txtMaxPrice->Location = Point(6, 6);
	this->txtMaxPrice->Text = L"5000";
	this->txtMaxPrice->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
	this->txtMaxPrice->BorderStyle = BorderStyle::None;
	this->txtMaxPrice->BackColor = Color::White;
	this->panelMaxPrice->Controls->Add(this->txtMaxPrice);

	Label^ lblSortLabel = gcnew Label();
	lblSortLabel->Text = L"Ordenar por";
	lblSortLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
	lblSortLabel->ForeColor = Color::FromArgb(86, 89, 89);
	lblSortLabel->Location = Point(20, 205);
	lblSortLabel->AutoSize = true;

	this->cbSortCriteria = gcnew ComboBox();
	this->cbSortCriteria->Size = System::Drawing::Size(155, 28);
	this->cbSortCriteria->Location = Point(20, 228);
	this->cbSortCriteria->DropDownStyle = ComboBoxStyle::DropDownList;
	this->cbSortCriteria->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
	this->cbSortCriteria->FlatStyle = FlatStyle::Flat;
	this->cbSortCriteria->BackColor = Color::FromArgb(248, 250, 252);
	this->cbSortCriteria->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
	this->cbSortCriteria->DrawItem += gcnew DrawItemEventHandler(this, &home_screen::comboBox_DrawItem);
	this->cbSortCriteria->Items->Add("Sin ordenar");
	this->cbSortCriteria->Items->Add("Nombre: A - Z");
	this->cbSortCriteria->Items->Add("Nombre: Z - A");
	this->cbSortCriteria->Items->Add("Precio: Menor a Mayor");
	this->cbSortCriteria->Items->Add("Precio: Mayor a Menor");
	this->cbSortCriteria->Items->Add("Stock: Menor a Mayor");
	this->cbSortCriteria->Items->Add("Stock: Mayor a Menor");
	this->cbSortCriteria->SelectedIndex = 0;

	this->btnApplyFilters = gcnew Button();
	this->btnApplyFilters->Text = L"Aplicar Filtros";
	this->btnApplyFilters->Size = System::Drawing::Size(155, 36);
	this->btnApplyFilters->Location = Point(20, 280);
	styleButton(this->btnApplyFilters, Color::FromArgb(255, 153, 0), Color::White, Color::FromArgb(230, 130, 0), Color::FromArgb(200, 110, 0), 9);
	this->btnApplyFilters->Click += gcnew EventHandler(this, &home_screen::btnApplyFilters_Click);
	setRegionRounded(this->btnApplyFilters, 10);

	this->btnClearFilters = gcnew Button();
	this->btnClearFilters->Text = L"Limpiar";
	this->btnClearFilters->Size = System::Drawing::Size(155, 34);
	this->btnClearFilters->Location = Point(20, 328);
	styleButton(this->btnClearFilters, Color::FromArgb(241, 245, 249), Color::FromArgb(71, 85, 105), Color::FromArgb(226, 232, 240), Color::FromArgb(203, 213, 225), 9);
	this->btnClearFilters->Click += gcnew EventHandler(this, &home_screen::btnClearFilters_Click);
	setRegionRounded(this->btnClearFilters, 10);

	this->panelFilters->Controls->Add(this->lblFiltersTitle);
	this->panelFilters->Controls->Add(lblCatLabel);
	this->panelFilters->Controls->Add(this->cbCategories);
	this->panelFilters->Controls->Add(lblPriceLabel);
	this->panelFilters->Controls->Add(this->panelMinPrice);
	this->panelFilters->Controls->Add(lblDash);
	this->panelFilters->Controls->Add(this->panelMaxPrice);
	this->panelFilters->Controls->Add(lblSortLabel);
	this->panelFilters->Controls->Add(this->cbSortCriteria);
	this->panelFilters->Controls->Add(this->btnApplyFilters);
	this->panelFilters->Controls->Add(this->btnClearFilters);

	this->panelCart = gcnew Panel();
	this->panelCart->Size = System::Drawing::Size(0, 680);
	this->panelCart->Location = Point(1100, 70);
	this->panelCart->BackColor = Color::White;

	this->lblCartTitle = gcnew Label();
	this->lblCartTitle->Text = L"Tu Carrito";
	this->lblCartTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
	this->lblCartTitle->ForeColor = Color::FromArgb(15, 17, 17);
	this->lblCartTitle->Location = Point(20, 20);
	this->lblCartTitle->AutoSize = true;

	Label^ lblCartSubtitle = gcnew Label();
	lblCartSubtitle->Text = L"Estructura: Stack (LIFO)";
	lblCartSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 8, FontStyle::Italic);
	lblCartSubtitle->ForeColor = Color::FromArgb(130, 130, 130);
	lblCartSubtitle->Location = Point(20, 48);
	lblCartSubtitle->AutoSize = true;

	this->listCartItems = gcnew ListBox();
	this->listCartItems->Size = System::Drawing::Size(275, 430);
	this->listCartItems->Location = Point(20, 75);
	this->listCartItems->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->listCartItems->BorderStyle = BorderStyle::None;
	this->listCartItems->BackColor = Color::FromArgb(248, 250, 252);
	this->listCartItems->ItemHeight = 36;
	this->listCartItems->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
	this->listCartItems->DrawItem += gcnew DrawItemEventHandler(this, &home_screen::listCartItems_DrawItem);

	this->lblCartTotal = gcnew Label();
	this->lblCartTotal->Text = L"Total: S/. 0.00";
	this->lblCartTotal->Font = gcnew System::Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
	this->lblCartTotal->ForeColor = Color::FromArgb(177, 39, 4);
	this->lblCartTotal->Location = Point(20, 520);
	this->lblCartTotal->AutoSize = true;

	this->btnCheckout = gcnew Button();
	this->btnCheckout->Text = L"Proceder al Despacho";
	this->btnCheckout->Size = System::Drawing::Size(275, 40);
	this->btnCheckout->Location = Point(20, 555);
	styleButton(this->btnCheckout, Color::FromArgb(255, 153, 0), Color::White, Color::FromArgb(230, 130, 0), Color::FromArgb(200, 110, 0), 10);
	this->btnCheckout->Click += gcnew EventHandler(this, &home_screen::btnCheckout_Click);
	setRegionRounded(this->btnCheckout, 12);

	this->btnClearCart = gcnew Button();
	this->btnClearCart->Text = L"Eliminar Ultimo (Pop)";
	this->btnClearCart->Size = System::Drawing::Size(275, 36);
	this->btnClearCart->Location = Point(20, 605);
	styleButton(this->btnClearCart, Color::FromArgb(239, 68, 68), Color::White, Color::FromArgb(220, 50, 50), Color::FromArgb(200, 40, 40), 9);
	this->btnClearCart->Click += gcnew EventHandler(this, &home_screen::btnClearCart_Click);
	setRegionRounded(this->btnClearCart, 12);

	this->panelCart->Controls->Add(this->lblCartTitle);
	this->panelCart->Controls->Add(lblCartSubtitle);
	this->panelCart->Controls->Add(this->listCartItems);
	this->panelCart->Controls->Add(this->lblCartTotal);
	this->panelCart->Controls->Add(this->btnCheckout);
	this->panelCart->Controls->Add(this->btnClearCart);

	this->timerCart = gcnew Timer(this->components);
	this->timerCart->Interval = 10;
	this->timerCart->Tick += gcnew EventHandler(this, &home_screen::timerCart_Tick);

	this->panelContent = gcnew Panel();
	this->panelContent->Location = Point(215, 80);
	this->panelContent->Size = System::Drawing::Size(870, 630);
	this->panelContent->BackColor = Color::FromArgb(245, 245, 245);

	this->flowProducts = gcnew FlowLayoutPanel();
	this->flowProducts->Size = System::Drawing::Size(870, 555);
	this->flowProducts->Location = Point(0, 0);
	this->flowProducts->AutoScroll = true;
	this->flowProducts->Padding = System::Windows::Forms::Padding(5);
	this->flowProducts->BackColor = Color::FromArgb(245, 245, 245);
	this->panelContent->Controls->Add(this->flowProducts);

	this->panelPagination = gcnew Panel();
	this->panelPagination->Location = Point(0, 555);
	this->panelPagination->Size = System::Drawing::Size(870, 75);
	this->panelPagination->BackColor = Color::FromArgb(245, 245, 245);

	this->btnPrevPage = gcnew Button();
	this->btnPrevPage->Text = L"\u2190  Anterior";
	this->btnPrevPage->Size = System::Drawing::Size(100, 32);
	this->btnPrevPage->Location = Point(180, 20);
	styleButton(this->btnPrevPage, Color::FromArgb(241, 245, 249), Color::FromArgb(51, 65, 85), Color::FromArgb(226, 232, 240), Color::FromArgb(203, 213, 225), 9);
	this->btnPrevPage->Click += gcnew EventHandler(this, &home_screen::btnPrevPage_Click);
	setRegionRounded(this->btnPrevPage, 8);

	this->lblPageInfo = gcnew Label();
	this->lblPageInfo->Text = L"Pagina 1 de 1";
	this->lblPageInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f, FontStyle::Bold);
	this->lblPageInfo->ForeColor = Color::FromArgb(51, 65, 85);
	this->lblPageInfo->Location = Point(290, 24);
	this->lblPageInfo->Size = System::Drawing::Size(130, 25);
	this->lblPageInfo->TextAlign = ContentAlignment::MiddleCenter;

	this->btnNextPage = gcnew Button();
	this->btnNextPage->Text = L"Siguiente  \u2192";
	this->btnNextPage->Size = System::Drawing::Size(100, 32);
	this->btnNextPage->Location = Point(430, 20);
	styleButton(this->btnNextPage, Color::FromArgb(241, 245, 249), Color::FromArgb(51, 65, 85), Color::FromArgb(226, 232, 240), Color::FromArgb(203, 213, 225), 9);
	this->btnNextPage->Click += gcnew EventHandler(this, &home_screen::btnNextPage_Click);
	setRegionRounded(this->btnNextPage, 8);

	this->lblJumpTo = gcnew Label();
	this->lblJumpTo->Text = L"Ir a pagina:";
	this->lblJumpTo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
	this->lblJumpTo->ForeColor = Color::FromArgb(100, 116, 139);
	this->lblJumpTo->Location = Point(560, 24);
	this->lblJumpTo->Size = System::Drawing::Size(75, 25);
	this->lblJumpTo->TextAlign = ContentAlignment::MiddleRight;

	this->panelPageJump = gcnew Panel();
	this->panelPageJump->Size = System::Drawing::Size(50, 32);
	this->panelPageJump->Location = Point(640, 20);
	this->panelPageJump->BackColor = Color::Transparent;
	this->panelPageJump->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);

	this->txtPageJump = gcnew TextBox();
	this->txtPageJump->Location = Point(6, 6);
	this->txtPageJump->Size = System::Drawing::Size(38, 18);
	this->txtPageJump->Text = L"1";
	this->txtPageJump->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
	this->txtPageJump->BorderStyle = BorderStyle::None;
	this->txtPageJump->BackColor = Color::White;
	this->txtPageJump->TextAlign = HorizontalAlignment::Center;
	this->panelPageJump->Controls->Add(this->txtPageJump);

	this->btnGoPage = gcnew Button();
	this->btnGoPage->Text = L"Ir";
	this->btnGoPage->Size = System::Drawing::Size(40, 32);
	this->btnGoPage->Location = Point(700, 20);
	styleButton(this->btnGoPage, Color::FromArgb(255, 153, 0), Color::White, Color::FromArgb(230, 130, 0), Color::FromArgb(200, 110, 0), 9);
	this->btnGoPage->Click += gcnew EventHandler(this, &home_screen::btnGoPage_Click);
	setRegionRounded(this->btnGoPage, 8);

	this->panelPagination->Controls->Add(this->btnPrevPage);
	this->panelPagination->Controls->Add(this->lblPageInfo);
	this->panelPagination->Controls->Add(this->btnNextPage);
	this->panelPagination->Controls->Add(this->lblJumpTo);
	this->panelPagination->Controls->Add(this->panelPageJump);
	this->panelPagination->Controls->Add(this->btnGoPage);

	this->panelContent->Controls->Add(this->panelPagination);

	this->panelProductDetail = gcnew Panel();
	this->panelProductDetail->Location = Point(10, 80);
	this->panelProductDetail->Size = System::Drawing::Size(1075, 630);
	this->panelProductDetail->BackColor = Color::White;
	this->panelProductDetail->Visible = false;
	setRegionRounded(this->panelProductDetail, 16);

	this->btnBackToStore = gcnew Button();
	this->btnBackToStore->Text = L"\u2190  Volver al Catalogo";
	this->btnBackToStore->Size = System::Drawing::Size(180, 36);
	this->btnBackToStore->Location = Point(25, 20);
	styleButton(this->btnBackToStore, Color::FromArgb(241, 245, 249), Color::FromArgb(51, 65, 85), Color::FromArgb(226, 232, 240), Color::FromArgb(203, 213, 225), 9);
	this->btnBackToStore->Click += gcnew EventHandler(this, &home_screen::btnBackToStore_Click);
	setRegionRounded(this->btnBackToStore, 10);

	this->lblDetailName = gcnew Label();
	this->lblDetailName->Font = gcnew System::Drawing::Font(L"Segoe UI", 20, FontStyle::Bold);
	this->lblDetailName->ForeColor = Color::FromArgb(15, 17, 17);
	this->lblDetailName->Location = Point(30, 75);
	this->lblDetailName->Size = System::Drawing::Size(600, 45);

	this->lblDetailCategory = gcnew Label();
	this->lblDetailCategory->Font = gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Italic);
	this->lblDetailCategory->ForeColor = Color::FromArgb(86, 89, 89);
	this->lblDetailCategory->Location = Point(30, 130);
	this->lblDetailCategory->Size = System::Drawing::Size(400, 25);

	this->lblDetailPrice = gcnew Label();
	this->lblDetailPrice->Font = gcnew System::Drawing::Font(L"Segoe UI", 18, FontStyle::Bold);
	this->lblDetailPrice->ForeColor = Color::FromArgb(177, 39, 4);
	this->lblDetailPrice->Location = Point(30, 165);
	this->lblDetailPrice->Size = System::Drawing::Size(300, 40);

	this->lblDetailStock = gcnew Label();
	this->lblDetailStock->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
	this->lblDetailStock->ForeColor = Color::FromArgb(86, 89, 89);
	this->lblDetailStock->Location = Point(30, 215);
	this->lblDetailStock->Size = System::Drawing::Size(300, 25);

	this->picDetailProduct = gcnew PictureBox();
	this->picDetailProduct->Size = System::Drawing::Size(300, 300);
	this->picDetailProduct->Location = Point(680, 75);
	this->picDetailProduct->SizeMode = PictureBoxSizeMode::Zoom;
	this->picDetailProduct->BackColor = Color::FromArgb(248, 250, 252);

	this->btnAddDetailToCart = gcnew Button();
	this->btnAddDetailToCart->Text = L"Agregar a mi Compra";
	this->btnAddDetailToCart->Size = System::Drawing::Size(220, 44);
	this->btnAddDetailToCart->Location = Point(30, 260);
	styleButton(this->btnAddDetailToCart, Color::FromArgb(255, 153, 0), Color::White, Color::FromArgb(230, 130, 0), Color::FromArgb(200, 110, 0), 10);
	this->btnAddDetailToCart->Click += gcnew EventHandler(this, &home_screen::btnAddDetailToCart_Click);
	setRegionRounded(this->btnAddDetailToCart, 12);

	Label^ lblReviewsTitle = gcnew Label();
	lblReviewsTitle->Text = L"Resenas de Clientes (BST InOrder)";
	lblReviewsTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 13, FontStyle::Bold);
	lblReviewsTitle->ForeColor = Color::FromArgb(15, 17, 17);
	lblReviewsTitle->Location = Point(30, 330);
	lblReviewsTitle->AutoSize = true;

	this->listReviews = gcnew ListBox();
	this->listReviews->Size = System::Drawing::Size(700, 150);
	this->listReviews->Location = Point(30, 365);
	this->listReviews->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->listReviews->BorderStyle = BorderStyle::None;
	this->listReviews->BackColor = Color::FromArgb(248, 250, 252);
	this->listReviews->ItemHeight = 36;
	this->listReviews->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
	this->listReviews->DrawItem += gcnew DrawItemEventHandler(this, &home_screen::listReviews_DrawItem);

	Label^ lblWriteReview = gcnew Label();
	lblWriteReview->Text = L"Dejar Resena:";
	lblWriteReview->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
	lblWriteReview->ForeColor = Color::FromArgb(15, 17, 17);
	lblWriteReview->Location = Point(30, 530);
	lblWriteReview->AutoSize = true;

	this->panelReviewComment = gcnew Panel();
	this->panelReviewComment->Size = System::Drawing::Size(450, 32);
	this->panelReviewComment->Location = Point(30, 558);
	this->panelReviewComment->BackColor = Color::Transparent;
	this->panelReviewComment->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);

	this->txtReviewComment = gcnew TextBox();
	this->txtReviewComment->Size = System::Drawing::Size(434, 20);
	this->txtReviewComment->Location = Point(8, 6);
	this->txtReviewComment->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->txtReviewComment->BorderStyle = BorderStyle::None;
	this->txtReviewComment->BackColor = Color::White;
	this->panelReviewComment->Controls->Add(this->txtReviewComment);

	this->numReviewRating = gcnew NumericUpDown();
	this->numReviewRating->Location = Point(500, 558);
	this->numReviewRating->Minimum = 1;
	this->numReviewRating->Maximum = 5;
	this->numReviewRating->Value = 5;
	this->numReviewRating->Size = System::Drawing::Size(55, 28);
	this->numReviewRating->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);

	this->btnAddReview = gcnew Button();
	this->btnAddReview->Text = L"Publicar";
	this->btnAddReview->Size = System::Drawing::Size(110, 32);
	this->btnAddReview->Location = Point(575, 556);
	styleButton(this->btnAddReview, Color::FromArgb(55, 71, 90), Color::White, Color::FromArgb(71, 85, 105), Color::FromArgb(51, 65, 85), 9);
	this->btnAddReview->Click += gcnew EventHandler(this, &home_screen::btnAddReview_Click);
	setRegionRounded(this->btnAddReview, 10);

	this->panelProductDetail->Controls->Add(this->btnBackToStore);
	this->panelProductDetail->Controls->Add(this->lblDetailName);
	this->panelProductDetail->Controls->Add(this->lblDetailCategory);
	this->panelProductDetail->Controls->Add(this->lblDetailPrice);
	this->panelProductDetail->Controls->Add(this->lblDetailStock);
	this->panelProductDetail->Controls->Add(this->picDetailProduct);
	this->panelProductDetail->Controls->Add(this->btnAddDetailToCart);
	this->panelProductDetail->Controls->Add(lblReviewsTitle);
	this->panelProductDetail->Controls->Add(this->listReviews);
	this->panelProductDetail->Controls->Add(lblWriteReview);
	this->panelProductDetail->Controls->Add(this->panelReviewComment);
	this->panelProductDetail->Controls->Add(this->numReviewRating);
	this->panelProductDetail->Controls->Add(this->btnAddReview);

	this->panelAdmin = gcnew Panel();
	this->panelAdmin->Location = Point(10, 80);
	this->panelAdmin->Size = System::Drawing::Size(1075, 630);
	this->panelAdmin->BackColor = Color::White;
	this->panelAdmin->Visible = false;
	setRegionRounded(this->panelAdmin, 16);

	this->tabControlAdmin = gcnew TabControl();
	this->tabControlAdmin->Dock = DockStyle::Fill;
	this->tabControlAdmin->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->tabControlAdmin->DrawMode = TabDrawMode::OwnerDrawFixed;
	this->tabControlAdmin->SizeMode = TabSizeMode::Fixed;
	this->tabControlAdmin->ItemSize = System::Drawing::Size(190, 42);
	this->tabControlAdmin->DrawItem += gcnew DrawItemEventHandler(this, &home_screen::tabControl_DrawItem);

	this->tabCrud = gcnew TabPage();
	this->tabCrud->Text = L"Gestion Inventario";
	this->tabCrud->BackColor = Color::White;

	this->gridAdminProducts = gcnew DataGridView();
	this->gridAdminProducts->Size = System::Drawing::Size(700, 250);
	this->gridAdminProducts->Location = Point(20, 20);
	this->gridAdminProducts->ReadOnly = true;
	this->gridAdminProducts->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
	this->gridAdminProducts->BackgroundColor = Color::FromArgb(248, 250, 252);
	this->gridAdminProducts->BorderStyle = BorderStyle::None;
	this->gridAdminProducts->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
	this->gridAdminProducts->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(241, 245, 249);
	this->gridAdminProducts->EnableHeadersVisualStyles = false;

	Label^ lblId = gcnew Label(); lblId->Text = L"ID:"; lblId->Location = Point(20, 290); lblId->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); lblId->AutoSize = true;
	this->panelCrudId = gcnew Panel();
	this->panelCrudId->Size = System::Drawing::Size(60, 30);
	this->panelCrudId->Location = Point(20, 312);
	this->panelCrudId->BackColor = Color::Transparent;
	this->panelCrudId->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);
	this->txtCrudId = gcnew TextBox(); this->txtCrudId->Location = Point(6, 6); this->txtCrudId->Size = System::Drawing::Size(48, 18); this->txtCrudId->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); this->txtCrudId->BorderStyle = BorderStyle::None; this->txtCrudId->BackColor = Color::White;
	this->panelCrudId->Controls->Add(this->txtCrudId);

	Label^ lblNm = gcnew Label(); lblNm->Text = L"Nombre:"; lblNm->Location = Point(100, 290); lblNm->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); lblNm->AutoSize = true;
	this->panelCrudName = gcnew Panel();
	this->panelCrudName->Size = System::Drawing::Size(150, 30);
	this->panelCrudName->Location = Point(100, 312);
	this->panelCrudName->BackColor = Color::Transparent;
	this->panelCrudName->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);
	this->txtCrudName = gcnew TextBox(); this->txtCrudName->Location = Point(6, 6); this->txtCrudName->Size = System::Drawing::Size(138, 18); this->txtCrudName->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); this->txtCrudName->BorderStyle = BorderStyle::None; this->txtCrudName->BackColor = Color::White;
	this->panelCrudName->Controls->Add(this->txtCrudName);

	Label^ lblCt = gcnew Label(); lblCt->Text = L"Categoria:"; lblCt->Location = Point(270, 290); lblCt->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); lblCt->AutoSize = true;
	this->panelCrudCategory = gcnew Panel();
	this->panelCrudCategory->Size = System::Drawing::Size(120, 30);
	this->panelCrudCategory->Location = Point(270, 312);
	this->panelCrudCategory->BackColor = Color::Transparent;
	this->panelCrudCategory->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);
	this->txtCrudCategory = gcnew TextBox(); this->txtCrudCategory->Location = Point(6, 6); this->txtCrudCategory->Size = System::Drawing::Size(108, 18); this->txtCrudCategory->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); this->txtCrudCategory->BorderStyle = BorderStyle::None; this->txtCrudCategory->BackColor = Color::White;
	this->panelCrudCategory->Controls->Add(this->txtCrudCategory);

	Label^ lblPr = gcnew Label(); lblPr->Text = L"Precio:"; lblPr->Location = Point(410, 290); lblPr->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); lblPr->AutoSize = true;
	this->panelCrudPrice = gcnew Panel();
	this->panelCrudPrice->Size = System::Drawing::Size(80, 30);
	this->panelCrudPrice->Location = Point(410, 312);
	this->panelCrudPrice->BackColor = Color::Transparent;
	this->panelCrudPrice->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);
	this->txtCrudPrice = gcnew TextBox(); this->txtCrudPrice->Location = Point(6, 6); this->txtCrudPrice->Size = System::Drawing::Size(68, 18); this->txtCrudPrice->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); this->txtCrudPrice->BorderStyle = BorderStyle::None; this->txtCrudPrice->BackColor = Color::White;
	this->panelCrudPrice->Controls->Add(this->txtCrudPrice);

	Label^ lblSt = gcnew Label(); lblSt->Text = L"Stock:"; lblSt->Location = Point(510, 290); lblSt->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); lblSt->AutoSize = true;
	this->panelCrudStock = gcnew Panel();
	this->panelCrudStock->Size = System::Drawing::Size(60, 30);
	this->panelCrudStock->Location = Point(510, 312);
	this->panelCrudStock->BackColor = Color::Transparent;
	this->panelCrudStock->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);
	this->txtCrudStock = gcnew TextBox(); this->txtCrudStock->Location = Point(6, 6); this->txtCrudStock->Size = System::Drawing::Size(48, 18); this->txtCrudStock->Font = gcnew System::Drawing::Font(L"Segoe UI", 9); this->txtCrudStock->BorderStyle = BorderStyle::None; this->txtCrudStock->BackColor = Color::White;
	this->panelCrudStock->Controls->Add(this->txtCrudStock);

	this->btnCrudAdd = gcnew Button();
	this->btnCrudAdd->Text = L"Registrar Producto";
	this->btnCrudAdd->Size = System::Drawing::Size(180, 38);
	this->btnCrudAdd->Location = Point(20, 360);
	styleButton(this->btnCrudAdd, Color::FromArgb(255, 153, 0), Color::White, Color::FromArgb(230, 130, 0), Color::FromArgb(200, 110, 0), 9);
	this->btnCrudAdd->Click += gcnew EventHandler(this, &home_screen::btnCrudAdd_Click);
	setRegionRounded(this->btnCrudAdd, 10);

	this->btnCrudDelete = gcnew Button();
	this->btnCrudDelete->Text = L"Eliminar por ID";
	this->btnCrudDelete->Size = System::Drawing::Size(150, 38);
	this->btnCrudDelete->Location = Point(220, 360);
	styleButton(this->btnCrudDelete, Color::FromArgb(239, 68, 68), Color::White, Color::FromArgb(220, 50, 50), Color::FromArgb(200, 40, 40), 9);
	this->btnCrudDelete->Click += gcnew EventHandler(this, &home_screen::btnCrudDelete_Click);
	setRegionRounded(this->btnCrudDelete, 10);

	this->openFileDialog = gcnew OpenFileDialog();
	this->openFileDialog->Filter = L"Imagenes (*.jpg;*.jpeg;*.png)|*.jpg;*.jpeg;*.png";
	this->openFileDialog->Title = L"Seleccionar imagen del producto";

	this->btnCrudBrowseImage = gcnew Button();
	this->btnCrudBrowseImage->Text = L"Examinar...";
	this->btnCrudBrowseImage->Size = System::Drawing::Size(100, 38);
	this->btnCrudBrowseImage->Location = Point(610, 360);
	styleButton(this->btnCrudBrowseImage, Color::FromArgb(100, 116, 139), Color::White, Color::FromArgb(71, 85, 105), Color::FromArgb(51, 65, 85), 9);
	this->btnCrudBrowseImage->Click += gcnew EventHandler(this, &home_screen::btnCrudBrowseImage_Click);
	setRegionRounded(this->btnCrudBrowseImage, 10);

	this->lblCrudImagePath = gcnew Label();
	this->lblCrudImagePath->Text = L"Sin imagen";
	this->lblCrudImagePath->Font = gcnew System::Drawing::Font(L"Segoe UI", 8);
	this->lblCrudImagePath->ForeColor = Color::FromArgb(100, 116, 139);
	this->lblCrudImagePath->Location = Point(720, 360);
	this->lblCrudImagePath->AutoSize = true;

	this->picCrudImagePreview = gcnew PictureBox();
	this->picCrudImagePreview->Size = System::Drawing::Size(60, 60);
	this->picCrudImagePreview->Location = Point(720, 310);
	this->picCrudImagePreview->SizeMode = PictureBoxSizeMode::Zoom;
	this->picCrudImagePreview->BackColor = Color::FromArgb(241, 245, 249);

	this->tabCrud->Controls->Add(this->gridAdminProducts);
	this->tabCrud->Controls->Add(lblId); this->tabCrud->Controls->Add(this->panelCrudId);
	this->tabCrud->Controls->Add(lblNm); this->tabCrud->Controls->Add(this->panelCrudName);
	this->tabCrud->Controls->Add(lblCt); this->tabCrud->Controls->Add(this->panelCrudCategory);
	this->tabCrud->Controls->Add(lblPr); this->tabCrud->Controls->Add(this->panelCrudPrice);
	this->tabCrud->Controls->Add(lblSt); this->tabCrud->Controls->Add(this->panelCrudStock);
	this->tabCrud->Controls->Add(this->btnCrudAdd);
	this->tabCrud->Controls->Add(this->btnCrudDelete);
	this->tabCrud->Controls->Add(this->btnCrudBrowseImage);
	this->tabCrud->Controls->Add(this->lblCrudImagePath);
	this->tabCrud->Controls->Add(this->picCrudImagePreview);

	this->tabBenchmarks = gcnew TabPage();
	this->tabBenchmarks->Text = L"Performance Benchmarks";
	this->tabBenchmarks->BackColor = Color::White;

	this->btnRunBenchmarks = gcnew Button();
	this->btnRunBenchmarks->Text = L"Ejecutar Pruebas";
	this->btnRunBenchmarks->Size = System::Drawing::Size(200, 40);
	this->btnRunBenchmarks->Location = Point(30, 30);
	styleButton(this->btnRunBenchmarks, Color::FromArgb(19, 25, 33), Color::White, Color::FromArgb(30, 41, 59), Color::FromArgb(15, 23, 42), 9);
	this->btnRunBenchmarks->Click += gcnew EventHandler(this, &home_screen::btnRunBenchmarks_Click);
	setRegionRounded(this->btnRunBenchmarks, 10);

	this->lblBenchmarkResults = gcnew Label();
	this->lblBenchmarkResults->Text = L"Haga clic en Ejecutar para iniciar el test...";
	this->lblBenchmarkResults->Font = gcnew System::Drawing::Font(L"Consolas", 10);
	this->lblBenchmarkResults->ForeColor = Color::FromArgb(30, 41, 59);
	this->lblBenchmarkResults->Location = Point(30, 90);
	this->lblBenchmarkResults->Size = System::Drawing::Size(700, 300);

	Label^ lblDataset = gcnew Label();
	lblDataset->Text = L"Generar Dataset Masivo:";
	lblDataset->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
	lblDataset->Location = Point(30, 420);
	lblDataset->AutoSize = true;

	this->panelDatasetCount = gcnew Panel();
	this->panelDatasetCount->Size = System::Drawing::Size(100, 30);
	this->panelDatasetCount->Location = Point(30, 450);
	this->panelDatasetCount->BackColor = Color::Transparent;
	this->panelDatasetCount->Paint += gcnew PaintEventHandler(this, &home_screen::inputPanel_Paint);

	this->txtDatasetCount = gcnew TextBox();
	this->txtDatasetCount->Location = Point(6, 6);
	this->txtDatasetCount->Size = System::Drawing::Size(88, 18);
	this->txtDatasetCount->Text = L"2000";
	this->txtDatasetCount->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->txtDatasetCount->BorderStyle = BorderStyle::None;
	this->txtDatasetCount->BackColor = Color::White;
	this->panelDatasetCount->Controls->Add(this->txtDatasetCount);

	this->btnGenerateDataset = gcnew Button();
	this->btnGenerateDataset->Text = L"Generar e Indexar";
	this->btnGenerateDataset->Size = System::Drawing::Size(155, 32);
	this->btnGenerateDataset->Location = Point(150, 448);
	styleButton(this->btnGenerateDataset, Color::FromArgb(255, 153, 0), Color::White, Color::FromArgb(230, 130, 0), Color::FromArgb(200, 110, 0), 9);
	this->btnGenerateDataset->Click += gcnew EventHandler(this, &home_screen::btnGenerateDataset_Click);
	setRegionRounded(this->btnGenerateDataset, 10);

	this->tabBenchmarks->Controls->Add(this->btnRunBenchmarks);
	this->tabBenchmarks->Controls->Add(this->lblBenchmarkResults);
	this->tabBenchmarks->Controls->Add(lblDataset);
	this->tabBenchmarks->Controls->Add(this->panelDatasetCount);
	this->tabBenchmarks->Controls->Add(this->btnGenerateDataset);

	this->tabStructures = gcnew TabPage();
	this->tabStructures->Text = L"Visualizador TDA";
	this->tabStructures->BackColor = Color::White;

	this->cbStructureSelect = gcnew ComboBox();
	this->cbStructureSelect->Size = System::Drawing::Size(240, 28);
	this->cbStructureSelect->Location = Point(20, 20);
	this->cbStructureSelect->DropDownStyle = ComboBoxStyle::DropDownList;
	this->cbStructureSelect->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->cbStructureSelect->FlatStyle = FlatStyle::Flat;
	this->cbStructureSelect->BackColor = Color::FromArgb(248, 250, 252);
	this->cbStructureSelect->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
	this->cbStructureSelect->DrawItem += gcnew DrawItemEventHandler(this, &home_screen::comboBox_DrawItem);
	this->cbStructureSelect->Items->Add(L"DoubleList (Catalogo)");
	this->cbStructureSelect->Items->Add(L"Stack (Carrito)");
	this->cbStructureSelect->Items->Add(L"Queue (Pedidos)");
	this->cbStructureSelect->Items->Add(L"HashTable (IDs)");
	this->cbStructureSelect->Items->Add(L"AVL Tree (Precios)");
	this->cbStructureSelect->Items->Add(L"BST (Resenas)");
	this->cbStructureSelect->SelectedIndex = 0;
	this->cbStructureSelect->SelectedIndexChanged += gcnew EventHandler(this, &home_screen::cbStructureSelect_SelectedIndexChanged);

	this->cbBstProductSelect = gcnew ComboBox();
	this->cbBstProductSelect->Size = System::Drawing::Size(240, 28);
	this->cbBstProductSelect->Location = Point(280, 20);
	this->cbBstProductSelect->DropDownStyle = ComboBoxStyle::DropDownList;
	this->cbBstProductSelect->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->cbBstProductSelect->FlatStyle = FlatStyle::Flat;
	this->cbBstProductSelect->BackColor = Color::FromArgb(248, 250, 252);
	this->cbBstProductSelect->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
	this->cbBstProductSelect->DrawItem += gcnew DrawItemEventHandler(this, &home_screen::comboBox_DrawItem);
	this->cbBstProductSelect->SelectedIndexChanged += gcnew EventHandler(this, &home_screen::cbBstProductSelect_SelectedIndexChanged);
	this->cbBstProductSelect->Visible = false;

	this->panelStructureDraw = gcnew Panel();
	this->panelStructureDraw->Size = System::Drawing::Size(1020, 480);
	this->panelStructureDraw->Location = Point(20, 60);
	this->panelStructureDraw->BorderStyle = BorderStyle::None;
	this->panelStructureDraw->BackColor = Color::FromArgb(248, 250, 252);
	this->panelStructureDraw->AutoScroll = true;
	this->panelStructureDraw->Paint += gcnew PaintEventHandler(this, &home_screen::panelStructureDraw_Paint);

	this->tabStructures->Controls->Add(this->cbStructureSelect);
	this->tabStructures->Controls->Add(this->cbBstProductSelect);
	this->tabStructures->Controls->Add(this->panelStructureDraw);

	this->tabControlAdmin->TabPages->Add(this->tabCrud);
	this->tabControlAdmin->TabPages->Add(this->tabBenchmarks);
	this->tabControlAdmin->TabPages->Add(this->tabStructures);
	this->panelAdmin->Controls->Add(this->tabControlAdmin);

	this->panelGPS = gcnew Panel();
	this->panelGPS->Location = Point(10, 80);
	this->panelGPS->Size = System::Drawing::Size(1075, 630);
	this->panelGPS->BackColor = Color::White;
	this->panelGPS->Visible = false;
	setRegionRounded(this->panelGPS, 16);

	this->lblGPSTitle = gcnew Label();
	this->lblGPSTitle->Text = L"Despacho y Logistica (Dijkstra)";
	this->lblGPSTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
	this->lblGPSTitle->ForeColor = Color::FromArgb(15, 17, 17);
	this->lblGPSTitle->Location = Point(25, 20);
	this->lblGPSTitle->AutoSize = true;

	this->lblGPSInfo = gcnew Label();
	this->lblGPSInfo->Text = L"Ciudad de destino:";
	this->lblGPSInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->lblGPSInfo->ForeColor = Color::FromArgb(86, 89, 89);
	this->lblGPSInfo->Location = Point(25, 60);
	this->lblGPSInfo->AutoSize = true;

	this->cbDestinationCities = gcnew ComboBox();
	this->cbDestinationCities->Location = Point(25, 85);
	this->cbDestinationCities->Size = System::Drawing::Size(200, 28);
	this->cbDestinationCities->DropDownStyle = ComboBoxStyle::DropDownList;
	this->cbDestinationCities->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
	this->cbDestinationCities->FlatStyle = FlatStyle::Flat;
	this->cbDestinationCities->BackColor = Color::FromArgb(248, 250, 252);
	this->cbDestinationCities->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
	this->cbDestinationCities->DrawItem += gcnew DrawItemEventHandler(this, &home_screen::comboBox_DrawItem);

	this->btnGPSConfirm = gcnew Button();
	this->btnGPSConfirm->Text = L"Despachar Camion";
	this->btnGPSConfirm->Size = System::Drawing::Size(170, 36);
	this->btnGPSConfirm->Location = Point(245, 82);
	styleButton(this->btnGPSConfirm, Color::FromArgb(255, 153, 0), Color::White, Color::FromArgb(230, 130, 0), Color::FromArgb(200, 110, 0), 9);
	this->btnGPSConfirm->Click += gcnew EventHandler(this, &home_screen::btnGPSConfirm_Click);
	setRegionRounded(this->btnGPSConfirm, 10);

	this->panelGPSDraw = gcnew Panel();
	this->panelGPSDraw->Size = System::Drawing::Size(1020, 490);
	this->panelGPSDraw->Location = Point(25, 130);
	this->panelGPSDraw->BorderStyle = BorderStyle::None;
	this->panelGPSDraw->BackColor = Color::FromArgb(248, 250, 252);
	this->panelGPSDraw->Paint += gcnew PaintEventHandler(this, &home_screen::panelGPSDraw_Paint);

	this->timerGPS = gcnew Timer(this->components);
	this->timerGPS->Interval = 50;
	this->timerGPS->Tick += gcnew EventHandler(this, &home_screen::timerGPS_Tick);

	this->panelGPS->Controls->Add(this->lblGPSTitle);
	this->panelGPS->Controls->Add(this->lblGPSInfo);
	this->panelGPS->Controls->Add(this->cbDestinationCities);
	this->panelGPS->Controls->Add(this->btnGPSConfirm);
	this->panelGPS->Controls->Add(this->panelGPSDraw);

	this->Controls->Add(this->panelCart);
	this->Controls->Add(this->panelContent);
	this->Controls->Add(this->panelProductDetail);
	this->Controls->Add(this->panelAdmin);
	this->Controls->Add(this->panelGPS);
	this->Controls->Add(this->panelFilters);
	this->Controls->Add(this->panelHeader);

	this->gridAdminProducts->ColumnCount = 6;
	this->gridAdminProducts->Columns[0]->Name = L"ID";
	this->gridAdminProducts->Columns[1]->Name = L"Nombre";
	this->gridAdminProducts->Columns[2]->Name = L"Categoria";
	this->gridAdminProducts->Columns[3]->Name = L"Precio";
	this->gridAdminProducts->Columns[4]->Name = L"Stock";
	this->gridAdminProducts->Columns[5]->Name = L"Imagen";
}

void home_screen::panelHeader_Paint(System::Object^ sender, PaintEventArgs^ e)
{
	Graphics^ g = e->Graphics;
	LinearGradientBrush^ gradient = gcnew LinearGradientBrush(
		Point(0, 0), Point(panelHeader->Width, 0),
		Color::FromArgb(19, 25, 33), Color::FromArgb(35, 47, 62));
	g->FillRectangle(gradient, 0, 0, panelHeader->Width, panelHeader->Height);
	delete gradient;
}

void home_screen::panelSearchBox_Paint(System::Object^ sender, PaintEventArgs^ e)
{
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;
	RectangleF rect(0.0f, 0.0f, (float)panelSearchBox->Width - 1.0f, (float)panelSearchBox->Height - 1.0f);
	fillRoundedRect(g, rect, 19.0f, gcnew SolidBrush(Color::White));
	drawRoundedRectOutline(g, rect, 19.0f, gcnew Pen(Color::FromArgb(210, 210, 210), 1.0f));
}

void home_screen::card_Paint(System::Object^ sender, PaintEventArgs^ e)
{
	Panel^ card = safe_cast<Panel^>(sender);
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;
	g->TextRenderingHint = TextRenderingHint::ClearTypeGridFit;

	float w = (float)card->Width;
	float h = (float)card->Height;
	bool isHovered = (card == hoveredCard);

	RectangleF shadowRect(3.0f, 3.0f, w - 4.0f, h - 4.0f);
	int shadowAlpha = isHovered ? 35 : 12;
	fillRoundedRect(g, shadowRect, 12.0f, gcnew SolidBrush(Color::FromArgb(shadowAlpha, 0, 0, 0)));

	RectangleF cardRect(0.0f, 0.0f, w - 4.0f, h - 4.0f);
	fillRoundedRect(g, cardRect, 12.0f, gcnew SolidBrush(Color::White));
	drawRoundedRectOutline(g, cardRect, 12.0f, gcnew Pen(Color::FromArgb(isHovered ? 200 : 230, isHovered ? 200 : 230, isHovered ? 200 : 230), 1.0f));

	IntPtr ptr = (IntPtr)card->Tag;
	Product* p = (Product*)ptr.ToPointer();

	// Draw product image
	String^ imageFullPath = resolveImagePath(toSystemString(p->getImagePath()));
	if (imageFullPath == nullptr) {
		imageFullPath = resolveImagePath(L"default.jpg");
	}
	if (imageFullPath != nullptr) {
		try {
			Image^ prodImg = Image::FromFile(imageFullPath);
			RectangleF imgRect(15.0f, 15.0f, 166.0f, 110.0f);
			g->DrawImage(prodImg, imgRect);
			delete prodImg;
		} catch (...) {}
	} else {
		fillRoundedRect(g, RectangleF(15.0f, 15.0f, 166.0f, 110.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(241, 245, 249)));
		System::Drawing::Font^ noImgFont = gcnew System::Drawing::Font(L"Segoe UI", 8, FontStyle::Italic);
		g->DrawString(L"Sin imagen", noImgFont, gcnew SolidBrush(Color::FromArgb(156, 163, 175)), RectangleF(15.0f, 15.0f, 166.0f, 110.0f), gcnew StringFormat());
	}

	System::Drawing::Font^ nameFont = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
	g->DrawString(toSystemString(p->getName()), nameFont, gcnew SolidBrush(Color::FromArgb(15, 17, 17)),
		RectangleF(15.0f, 135.0f, 165.0f, 42.0f));

	System::Drawing::Font^ catFont = gcnew System::Drawing::Font(L"Segoe UI", 8, FontStyle::Italic);
	g->DrawString(toSystemString(p->getCategory()), catFont, gcnew SolidBrush(Color::FromArgb(86, 89, 89)), 15.0f, 175.0f);

	System::Drawing::Font^ priceFont = gcnew System::Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
	g->DrawString("S/. " + p->getPrice().ToString("F2"), priceFont, gcnew SolidBrush(Color::FromArgb(177, 39, 4)), 15.0f, 195.0f);

	System::Drawing::Font^ stockFont = gcnew System::Drawing::Font(L"Segoe UI", 8);
	String^ stockText = (p->getStock() > 0) ? "En stock (" + p->getStock().ToString() + ")" : "Sin stock";
	Color stockColor = (p->getStock() > 0) ? Color::FromArgb(0, 120, 55) : Color::FromArgb(200, 40, 40);
	g->DrawString(stockText, stockFont, gcnew SolidBrush(stockColor), 15.0f, 225.0f);

	StringFormat^ sf = gcnew StringFormat();
	sf->Alignment = StringAlignment::Center;
	sf->LineAlignment = StringAlignment::Center;

	RectangleF btnAddRect(15.0f, 260.0f, 166.0f, 36.0f);
	Color addBg = (isHovered && hoveredCardButton == 1) ? Color::FromArgb(230, 130, 0) : Color::FromArgb(255, 153, 0);
	fillRoundedRect(g, btnAddRect, 8.0f, gcnew SolidBrush(addBg));
	System::Drawing::Font^ btnFont = gcnew System::Drawing::Font(L"Segoe UI", 8.5f, FontStyle::Bold);
	g->DrawString(L"Agregar al Carrito", btnFont, gcnew SolidBrush(Color::White), btnAddRect, sf);

	RectangleF btnDetailRect(15.0f, 307.0f, 166.0f, 36.0f);
	Color detBg = (isHovered && hoveredCardButton == 2) ? Color::FromArgb(226, 232, 240) : Color::FromArgb(241, 245, 249);
	fillRoundedRect(g, btnDetailRect, 8.0f, gcnew SolidBrush(detBg));
	System::Drawing::Font^ detFont = gcnew System::Drawing::Font(L"Segoe UI", 8.5f);
	g->DrawString(L"Ver Detalle", detFont, gcnew SolidBrush(Color::FromArgb(51, 65, 85)), btnDetailRect, sf);
}

void home_screen::card_MouseEnter(System::Object^ sender, System::EventArgs^ e)
{
	Panel^ card = safe_cast<Panel^>(sender);
	hoveredCard = card;
	card->Invalidate();
}

void home_screen::card_MouseLeave(System::Object^ sender, System::EventArgs^ e)
{
	Panel^ card = safe_cast<Panel^>(sender);
	if (hoveredCard == card) {
		hoveredCard = nullptr;
		hoveredCardButton = 0;
	}
	card->Cursor = Cursors::Default;
	card->Invalidate();
}

void home_screen::card_MouseMove(System::Object^ sender, MouseEventArgs^ e)
{
	Panel^ card = safe_cast<Panel^>(sender);
	int oldBtn = hoveredCardButton;

	if (e->X >= 15 && e->X <= 181) {
		if (e->Y >= 260 && e->Y <= 296) {
			hoveredCardButton = 1;
			card->Cursor = Cursors::Hand;
		} else if (e->Y >= 307 && e->Y <= 343) {
			hoveredCardButton = 2;
			card->Cursor = Cursors::Hand;
		} else {
			hoveredCardButton = 0;
			card->Cursor = Cursors::Default;
		}
	} else {
		hoveredCardButton = 0;
		card->Cursor = Cursors::Default;
	}

	if (oldBtn != hoveredCardButton) {
		card->Invalidate();
	}
}

void home_screen::card_MouseClick(System::Object^ sender, MouseEventArgs^ e)
{
	Panel^ card = safe_cast<Panel^>(sender);
	IntPtr ptr = (IntPtr)card->Tag;
	Product* p = (Product*)ptr.ToPointer();

	if (e->X >= 15 && e->X <= 181) {
		if (e->Y >= 260 && e->Y <= 296) {
			if (p->getStock() <= 0) {
				MessageBox::Show("Producto sin stock disponible", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			registry->getManageCartUseCase()->addToCart(p);
			updateCartUI();
			triggerCartOpenAnimation();
		} else if (e->Y >= 307 && e->Y <= 343) {
			selectedProduct = p;
			activeView = "detail";
			switchActiveView();
			lblDetailName->Text = toSystemString(p->getName());
			lblDetailCategory->Text = "Categoria: " + toSystemString(p->getCategory());
			lblDetailPrice->Text = "S/. " + p->getPrice().ToString("F2");
			lblDetailStock->Text = "Stock Disponible: " + p->getStock().ToString();
			String^ detailImgPath = resolveImagePath(toSystemString(p->getImagePath()));
			if (detailImgPath != nullptr) {
				try { picDetailProduct->Image = Image::FromFile(detailImgPath); } catch (...) { picDetailProduct->Image = nullptr; }
			} else {
				picDetailProduct->Image = nullptr;
			}
			refreshProductReviews(p);
		}
	}
}

void home_screen::btnApplyFilters_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ cat = cbCategories->SelectedItem->ToString();
	double minVal = 0; double maxVal = 99999;
	try { minVal = Double::Parse(txtMinPrice->Text); maxVal = Double::Parse(txtMaxPrice->Text); } catch (...) {}

	currentProductList->clear();
	DoubleList<Product*>* allProducts = registry->getProductRepository()->getAllProducts();
	for (auto it = allProducts->begin(); it != allProducts->end(); ++it) {
		Product* p = *it;
		bool matchCat = (cat == "Todas las Categorias" || toSystemString(p->getCategory()) == cat);
		bool matchPrice = (p->getPrice() >= minVal && p->getPrice() <= maxVal);
		if (matchCat && matchPrice) {
			currentProductList->push_back(p);
		}
	}
	applySortingToCurrentList();
	currentPage = 1;
	renderCurrentPageProducts();
}

void home_screen::btnClearFilters_Click(System::Object^ sender, System::EventArgs^ e)
{
	cbCategories->SelectedIndex = 0;
	txtMinPrice->Text = L"0";
	txtMaxPrice->Text = L"5000";
	txtSearch->Text = L"";
	cbSortCriteria->SelectedIndex = 0;
	refreshProductCatalog();
}

void home_screen::txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (activeView != "store") return;
	string query = toStdString(txtSearch->Text);
	DoubleList<Product*>* filtered = registry->getSearchProductUseCase()->searchFuzzy(query);
	currentProductList->clear();
	for (auto it = filtered->begin(); it != filtered->end(); ++it) {
		currentProductList->push_back(*it);
	}
	delete filtered;
	applySortingToCurrentList();
	currentPage = 1;
	renderCurrentPageProducts();
}

void home_screen::btnCartToggle_Click(System::Object^ sender, System::EventArgs^ e)
{
	isCartOpen = !isCartOpen;
	cartTargetWidth = isCartOpen ? 320 : 0;
	timerCart->Start();
}

void home_screen::btnAdminToggle_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (activeView == "admin") {
		activeView = "store";
		btnAdminToggle->Text = L"Admin Panel";
	} else {
		activeView = "admin";
		btnAdminToggle->Text = L"Volver Tienda";
		populateBstProductSelect();
		gridAdminProducts->Rows->Clear();
		DoubleList<Product*>* allProducts = registry->getProductRepository()->getAllProducts();
		for (auto it = allProducts->begin(); it != allProducts->end(); ++it) {
			Product* p = *it;
			gridAdminProducts->Rows->Add(p->getId().ToString(), toSystemString(p->getName()), toSystemString(p->getCategory()), p->getPrice().ToString("F2"), p->getStock().ToString(), toSystemString(p->getImagePath()));
		}
	}
	switchActiveView();
}

void home_screen::timerCart_Tick(System::Object^ sender, System::EventArgs^ e)
{
	int currentWidth = panelCart->Width;
	int step = 25;
	if (currentWidth < cartTargetWidth) {
		currentWidth += step;
		if (currentWidth >= cartTargetWidth) { currentWidth = cartTargetWidth; timerCart->Stop(); }
	} else {
		currentWidth -= step;
		if (currentWidth <= cartTargetWidth) { currentWidth = cartTargetWidth; timerCart->Stop(); }
	}
	panelCart->Width = currentWidth;
	panelCart->Location = Point(1100 - currentWidth, 70);
}

void home_screen::btnClearCart_Click(System::Object^ sender, System::EventArgs^ e)
{
	registry->getManageCartUseCase()->removeFromCart();
	updateCartUI();
}

void home_screen::btnCheckout_Click(System::Object^ sender, System::EventArgs^ e)
{
	::Stack<Product*>* cart = registry->getManageCartUseCase()->getCart();
	if (cart->isEmpty()) {
		MessageBox::Show("Tu carrito esta vacio.", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}
	Order* order = registry->getManageCartUseCase()->checkout(1, 456);
	registry->getProcessOrderUseCase()->addOrder(order);
	gpsStartNode = 0; gpsCurrentStep = 0; gpsPathLength = 0;
	isCartOpen = false; cartTargetWidth = 0; timerCart->Start();
	activeView = "gps";
	switchActiveView();
}

void home_screen::btnBackToStore_Click(System::Object^ sender, System::EventArgs^ e)
{
	activeView = "store";
	selectedProduct = nullptr;
	switchActiveView();
}

void home_screen::btnAddDetailToCart_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (selectedProduct != nullptr) {
		if (selectedProduct->getStock() <= 0) {
			MessageBox::Show("Producto sin stock", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		registry->getManageCartUseCase()->addToCart(selectedProduct);
		updateCartUI();
		triggerCartOpenAnimation();
	}
}

void home_screen::btnAddReview_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (selectedProduct == nullptr || txtReviewComment->Text == L"") return;
	int newReviewId = rand() % 10000 + 1000;
	int rating = (int)numReviewRating->Value;
	string comment = toStdString(txtReviewComment->Text);
	globalReviewsBst->insert(newReviewId, new Review(newReviewId, selectedProduct->getId(), 999, rating, comment));
	refreshProductReviews(selectedProduct);
	txtReviewComment->Text = L"";
	MessageBox::Show("Resena agregada en el BST.", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

void home_screen::btnCrudAdd_Click(System::Object^ sender, System::EventArgs^ e)
{
	try {
		int id = Int32::Parse(txtCrudId->Text);
		string name = toStdString(txtCrudName->Text);
		string cat = toStdString(txtCrudCategory->Text);
		double price = Double::Parse(txtCrudPrice->Text);
		int stock = Int32::Parse(txtCrudStock->Text);
		string imagePath = toStdString(lblCrudImagePath->Text);
		if (imagePath == "Sin imagen" || imagePath.empty()) {
			imagePath = "default.jpg";
		}
		Product* p = new Product(id, name, cat, price, stock, imagePath);
		registry->getProductRepository()->addProduct(p);
		registry->getProductRepository()->saveProducts();
		gridAdminProducts->Rows->Add(id.ToString(), toSystemString(name), toSystemString(cat), price.ToString("F2"), stock.ToString(), toSystemString(imagePath));
		txtCrudId->Text = L""; txtCrudName->Text = L""; txtCrudCategory->Text = L""; txtCrudPrice->Text = L""; txtCrudStock->Text = L"";
		lblCrudImagePath->Text = L"Sin imagen";
		picCrudImagePreview->Image = nullptr;
		refreshProductCatalog();
		MessageBox::Show("Producto indexado en Hash y AVL.", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Information);
	} catch (...) {
		MessageBox::Show("Error en los datos.", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void home_screen::btnCrudDelete_Click(System::Object^ sender, System::EventArgs^ e)
{
	try {
		int id = Int32::Parse(txtCrudId->Text);
		registry->getProductRepository()->deleteProduct(id);
		registry->getProductRepository()->saveProducts();
		for (int i = 0; i < gridAdminProducts->Rows->Count; ++i) {
			if (gridAdminProducts->Rows[i]->Cells[0]->Value != nullptr && Int32::Parse(gridAdminProducts->Rows[i]->Cells[0]->Value->ToString()) == id) {
				gridAdminProducts->Rows->RemoveAt(i); break;
			}
		}
		refreshProductCatalog();
		txtCrudId->Text = L"";
		MessageBox::Show("Producto eliminado.", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Information);
	} catch (...) {
		MessageBox::Show("ID invalido.", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void home_screen::btnCrudBrowseImage_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		String^ srcPath = openFileDialog->FileName;
		String^ imagesDir = nullptr;
		String^ d;
		d = L"Images"; if (System::IO::Directory::Exists(d)) imagesDir = d;
		if (imagesDir == nullptr) { d = System::Windows::Forms::Application::StartupPath + L"\\Images"; if (System::IO::Directory::Exists(d)) imagesDir = d; }
		if (imagesDir == nullptr) { d = System::AppDomain::CurrentDomain->BaseDirectory + L"\\Images"; if (System::IO::Directory::Exists(d)) imagesDir = d; }
		if (imagesDir == nullptr) { d = L"..\\Images"; if (System::IO::Directory::Exists(d)) imagesDir = d; }
		if (imagesDir == nullptr) { d = L"..\\..\\Datamazon\\Images"; if (System::IO::Directory::Exists(d)) imagesDir = d; }
		if (imagesDir == nullptr) {
			imagesDir = L"Images";
			System::IO::Directory::CreateDirectory(imagesDir);
		}
		String^ destName = L"manual_" + System::IO::Path::GetFileName(srcPath);
		String^ destPath = System::IO::Path::Combine(imagesDir, destName);
		int counter = 1;
		while (System::IO::File::Exists(destPath)) {
			destName = L"manual_" + counter.ToString() + L"_" + System::IO::Path::GetFileName(srcPath);
			destPath = System::IO::Path::Combine(imagesDir, destName);
			counter++;
		}
		System::IO::File::Copy(srcPath, destPath);
		lblCrudImagePath->Text = destName;
		try {
			picCrudImagePreview->Image = Image::FromFile(destPath);
		} catch (...) {}
	}
}

void home_screen::btnRunBenchmarks_Click(System::Object^ sender, System::EventArgs^ e)
{
	BenchmarkResults res = registry->getRunBenchmarksUseCase()->execute();
	System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
	sb->AppendLine("========== BENCHMARKS ==========");
	sb->AppendLine("Productos: " + res.dataCount.ToString());
	sb->AppendLine();
	sb->AppendLine("-- BUSQUEDA --");
	sb->AppendLine("Lineal (DoubleList):  " + res.linearSearchNs.ToString() + " ns");
	sb->AppendLine("AVL Tree:             " + res.avlSearchNs.ToString() + " ns");
	sb->AppendLine("Hash Table:           " + res.hashSearchNs.ToString() + " ns");
	sb->AppendLine();
	sb->AppendLine("-- ORDENAMIENTO --");
	sb->AppendLine("Merge Sort:  " + res.mergeSortMs.ToString() + " ms");
	sb->AppendLine("Quick Sort:  " + res.quickSortMs.ToString() + " ms");
	sb->AppendLine("Heap Sort:   " + res.heapSortMs.ToString() + " ms");
	lblBenchmarkResults->Text = sb->ToString();
}

void home_screen::btnGenerateDataset_Click(System::Object^ sender, System::EventArgs^ e)
{
	try {
		int count = Int32::Parse(txtDatasetCount->Text);
		DatasetGenerator::generateAndSave(count, 50, 10);
		registry->getProductRepository()->loadProducts();
		refreshProductCatalog();
		MessageBox::Show("Dataset generado e indexado.", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Information);
	} catch (...) {
		MessageBox::Show("Cantidad invalida.", "Datamazon", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void home_screen::cbStructureSelect_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	int sel = cbStructureSelect->SelectedIndex;
	cbBstProductSelect->Visible = (sel == 5);
	panelStructureDraw->Invalidate();
}

void home_screen::panelStructureDraw_Paint(System::Object^ sender, PaintEventArgs^ e)
{
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;
	g->TextRenderingHint = TextRenderingHint::ClearTypeGridFit;
	int sel = cbStructureSelect->SelectedIndex;

	System::Drawing::Font^ titleFont = gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
	System::Drawing::Font^ nodeFont = gcnew System::Drawing::Font(L"Segoe UI", 9);
	Brush^ titleBrush = gcnew SolidBrush(Color::FromArgb(15, 17, 17));
	Pen^ linePen = gcnew Pen(Color::FromArgb(100, 116, 139), 2);
	Color nodeColor = Color::FromArgb(219, 234, 254);
	Color nodeBorder = Color::FromArgb(59, 130, 246);

	if (sel == 0) {
		DoubleList<Product*>* list = registry->getProductRepository()->getAllProducts();
		int itemCount = 0;
		Node<Product*>* countCurr = list->head;
		while (countCurr != nullptr) { itemCount++; countCurr = countCurr->next; }
		int totalWidth = itemCount * 130 + 50;
		panelStructureDraw->AutoScrollMinSize = System::Drawing::Size(totalWidth, 200);
		g->TranslateTransform((float)panelStructureDraw->AutoScrollPosition.X, (float)panelStructureDraw->AutoScrollPosition.Y);

		g->DrawString(L"DoubleList - Catalogo de Productos (" + itemCount.ToString() + L" items)", titleFont, titleBrush, 15.0f, 15.0f);
		Node<Product*>* curr = list->head;
		int x = 30;
		while (curr != nullptr) {
			fillRoundedRect(g, RectangleF((float)x, 80.0f, 100.0f, 50.0f), 8.0f, gcnew SolidBrush(nodeColor));
			drawRoundedRectOutline(g, RectangleF((float)x, 80.0f, 100.0f, 50.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
			g->DrawString(toSystemString(curr->value->getName()), nodeFont, titleBrush, (float)(x + 5), 97.0f);
			if (curr->next != nullptr) {
				g->DrawLine(linePen, (float)(x + 100), 98.0f, (float)(x + 130), 98.0f);
				g->DrawLine(linePen, (float)(x + 130), 112.0f, (float)(x + 100), 112.0f);
			}
			x += 130; curr = curr->next;
		}
	} else if (sel == 1) {
		::Stack<Product*>* cart = registry->getManageCartUseCase()->getCart();
		int itemCount = cart->count();
		int totalHeight = itemCount * 55 + 80;
		panelStructureDraw->AutoScrollMinSize = System::Drawing::Size(panelStructureDraw->Width, Math::Max(totalHeight, panelStructureDraw->Height));
		g->TranslateTransform((float)panelStructureDraw->AutoScrollPosition.X, (float)panelStructureDraw->AutoScrollPosition.Y);

		g->DrawString(L"Stack - Carrito del Cliente (LIFO)", titleFont, titleBrush, 15.0f, 15.0f);
		Node<Product*>* curr = cart->getTop();
		int y = 55; int count = 0;
		while (curr != nullptr) {
			fillRoundedRect(g, RectangleF(300.0f, (float)y, 170.0f, 45.0f), 8.0f, gcnew SolidBrush(nodeColor));
			drawRoundedRectOutline(g, RectangleF(300.0f, (float)y, 170.0f, 45.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
			g->DrawString(toSystemString(curr->value->getName()), nodeFont, titleBrush, 312.0f, (float)(y + 14));
			if (count == 0) g->DrawString(L"\u25B6 TOP", gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold), gcnew SolidBrush(Color::FromArgb(239, 68, 68)), 235.0f, (float)(y + 14));
			y += 55; curr = curr->next; count++;
		}
	} else if (sel == 2) {
		::Queue<Order*>* queue = registry->getProcessOrderUseCase()->getOrderQueue();
		int itemCount = 0;
		Node<Order*>* countCurr = queue->getFront();
		while (countCurr != nullptr) { itemCount++; countCurr = countCurr->next; }
		int totalWidth = itemCount * 155 + 50;
		panelStructureDraw->AutoScrollMinSize = System::Drawing::Size(Math::Max(totalWidth, panelStructureDraw->Width), 250);
		g->TranslateTransform((float)panelStructureDraw->AutoScrollPosition.X, (float)panelStructureDraw->AutoScrollPosition.Y);

		g->DrawString(L"Queue - Pedidos Pendientes (FIFO)", titleFont, titleBrush, 15.0f, 15.0f);
		Node<Order*>* curr = queue->getFront();
		int x = 50;
		while (curr != nullptr) {
			fillRoundedRect(g, RectangleF((float)x, 100.0f, 120.0f, 50.0f), 8.0f, gcnew SolidBrush(nodeColor));
			drawRoundedRectOutline(g, RectangleF((float)x, 100.0f, 120.0f, 50.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
			g->DrawString("Pedido #" + curr->value->getId().ToString(), nodeFont, titleBrush, (float)(x + 12), 117.0f);
			if (curr->next != nullptr) g->DrawLine(linePen, (float)(x + 120), 125.0f, (float)(x + 155), 125.0f);
			x += 155; curr = curr->next;
		}
	} else if (sel == 3) {
		auto hashTbl = registry->getProductRepository()->getProductsHash();
		size_t cap = hashTbl->getCapacity();
		auto tbl = hashTbl->getTable();
		int cols = 2;
		int rowsPerCol = (int)((cap + cols - 1) / cols);
		int slotH = 52;
		int chainW = 155;

		// Calculate max chain lengths per column for scroll size
		int maxChain[2] = { 0, 0 };
		for (size_t i = 0; i < cap; ++i) {
			int colIdx = (int)(i / rowsPerCol);
			if (colIdx > 1) colIdx = 1;
			int chainLen = 0;
			auto node = tbl[i];
			while (node != nullptr) { chainLen++; node = node->next; }
			if (chainLen > maxChain[colIdx]) maxChain[colIdx] = chainLen;
		}
		int totalW = 530 + 85 + chainW * maxChain[1] + 170;
		int totalH = rowsPerCol * slotH + 60;
		if (totalH < panelStructureDraw->Height) totalH = panelStructureDraw->Height;
		panelStructureDraw->AutoScrollMinSize = System::Drawing::Size(totalW, totalH);
		g->TranslateTransform((float)panelStructureDraw->AutoScrollPosition.X, (float)panelStructureDraw->AutoScrollPosition.Y);

		g->DrawString(L"HashTable - Indexacion O(1) por ID", titleFont, titleBrush, 15.0f, 15.0f);
		for (size_t i = 0; i < cap; ++i) {
			int col = (int)(i / rowsPerCol);
			int row = (int)(i % rowsPerCol);
			int colX = (col == 0) ? 30 : 530;
			int y = 60 + row * slotH;

			fillRoundedRect(g, RectangleF((float)colX, (float)y, 50.0f, 40.0f), 6.0f, gcnew SolidBrush(Color::FromArgb(241, 245, 249)));
			drawRoundedRectOutline(g, RectangleF((float)colX, (float)y, 50.0f, 40.0f), 6.0f, gcnew Pen(Color::FromArgb(148, 163, 184), 1.0f));
			g->DrawString("[" + i.ToString() + "]", nodeFont, titleBrush, (float)(colX + 12), (float)(y + 12));

			int nodeX = colX + 85;
			auto node = tbl[i];
			while (node != nullptr) {
				g->DrawLine(linePen, (float)(nodeX - 35), (float)(y + 20), (float)nodeX, (float)(y + 20));
				fillRoundedRect(g, RectangleF((float)nodeX, (float)(y + 2), 140.0f, 36.0f), 18.0f, gcnew SolidBrush(nodeColor));
				drawRoundedRectOutline(g, RectangleF((float)nodeX, (float)(y + 2), 140.0f, 36.0f), 18.0f, gcnew Pen(nodeBorder, 1.0f));
				g->DrawString("ID " + node->key.ToString() + ": " + toSystemString(node->value->getName()), gcnew System::Drawing::Font(L"Segoe UI", 7.5f), titleBrush, (float)(nodeX + 10), (float)(y + 11));
				nodeX += chainW;
				node = node->next;
			}
			if (tbl[i] == nullptr) {
				g->DrawLine(linePen, (float)(colX + 50), (float)(y + 20), (float)(colX + 85), (float)(y + 20));
				fillRoundedRect(g, RectangleF((float)(colX + 85), (float)(y + 2), 140.0f, 36.0f), 18.0f, gcnew SolidBrush(Color::FromArgb(241, 245, 249)));
				drawRoundedRectOutline(g, RectangleF((float)(colX + 85), (float)(y + 2), 140.0f, 36.0f), 18.0f, gcnew Pen(Color::FromArgb(200, 200, 200), 1.0f));
				g->DrawString(L"Vacio", nodeFont, gcnew SolidBrush(Color::FromArgb(150, 150, 150)), (float)(colX + 100), (float)(y + 10));
			}
		}
	} else if (sel == 4) {
		panelStructureDraw->AutoScrollMinSize = System::Drawing::Size(panelStructureDraw->Width, panelStructureDraw->Height);
		g->DrawString(L"AVL Tree - Indexacion Balanceada O(log N)", titleFont, titleBrush, 15.0f, 15.0f);
		auto avlTree = registry->getProductRepository()->getProductsAvlPrice();
		auto root = avlTree->getRoot();
		if (root == nullptr) {
			g->DrawString(L"Arbol AVL Vacio", titleFont, gcnew SolidBrush(Color::FromArgb(150, 150, 150)), 350.0f, 200.0f);
			return;
		}

		if (root->left != nullptr) g->DrawLine(linePen, 355.0f, 105.0f, 240.0f, 165.0f);
		if (root->right != nullptr) g->DrawLine(linePen, 400.0f, 105.0f, 520.0f, 165.0f);
		if (root->left != nullptr) {
			if (root->left->left != nullptr) g->DrawLine(linePen, 220.0f, 200.0f, 160.0f, 260.0f);
			if (root->left->right != nullptr) g->DrawLine(linePen, 265.0f, 200.0f, 310.0f, 260.0f);
		}
		if (root->right != nullptr) {
			if (root->right->left != nullptr) g->DrawLine(linePen, 500.0f, 200.0f, 440.0f, 260.0f);
			if (root->right->right != nullptr) g->DrawLine(linePen, 545.0f, 200.0f, 590.0f, 260.0f);
		}

		fillRoundedRect(g, RectangleF(320.0f, 55.0f, 115.0f, 45.0f), 8.0f, gcnew SolidBrush(nodeColor));
		drawRoundedRectOutline(g, RectangleF(320.0f, 55.0f, 115.0f, 45.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
		g->DrawString("S/. " + root->key.ToString("F2"), gcnew System::Drawing::Font(L"Segoe UI", 7.5f, FontStyle::Bold), titleBrush, 325.0f, 62.0f);
		g->DrawString(toSystemString(root->value->getName()), gcnew System::Drawing::Font(L"Segoe UI", 6.8f), titleBrush, 325.0f, 78.0f);

		if (root->left != nullptr) {
			fillRoundedRect(g, RectangleF(185.0f, 150.0f, 115.0f, 45.0f), 8.0f, gcnew SolidBrush(nodeColor));
			drawRoundedRectOutline(g, RectangleF(185.0f, 150.0f, 115.0f, 45.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
			g->DrawString("S/. " + root->left->key.ToString("F2"), gcnew System::Drawing::Font(L"Segoe UI", 7.5f, FontStyle::Bold), titleBrush, 190.0f, 157.0f);
			g->DrawString(toSystemString(root->left->value->getName()), gcnew System::Drawing::Font(L"Segoe UI", 6.8f), titleBrush, 190.0f, 173.0f);
		}

		if (root->right != nullptr) {
			fillRoundedRect(g, RectangleF(465.0f, 150.0f, 115.0f, 45.0f), 8.0f, gcnew SolidBrush(nodeColor));
			drawRoundedRectOutline(g, RectangleF(465.0f, 150.0f, 115.0f, 45.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
			g->DrawString("S/. " + root->right->key.ToString("F2"), gcnew System::Drawing::Font(L"Segoe UI", 7.5f, FontStyle::Bold), titleBrush, 470.0f, 157.0f);
			g->DrawString(toSystemString(root->right->value->getName()), gcnew System::Drawing::Font(L"Segoe UI", 6.8f), titleBrush, 470.0f, 173.0f);
		}

		if (root->left != nullptr && root->left->left != nullptr) {
			fillRoundedRect(g, RectangleF(110.0f, 245.0f, 95.0f, 38.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(254, 243, 199)));
			drawRoundedRectOutline(g, RectangleF(110.0f, 245.0f, 95.0f, 38.0f), 8.0f, gcnew Pen(Color::FromArgb(245, 158, 11), 1.2f));
			g->DrawString("S/. " + root->left->left->key.ToString("F2"), gcnew System::Drawing::Font(L"Segoe UI", 7.0f, FontStyle::Bold), titleBrush, 115.0f, 250.0f);
			g->DrawString(toSystemString(root->left->left->value->getName()), gcnew System::Drawing::Font(L"Segoe UI", 6.2f), titleBrush, 115.0f, 265.0f);
		}

		if (root->left != nullptr && root->left->right != nullptr) {
			fillRoundedRect(g, RectangleF(260.0f, 245.0f, 95.0f, 38.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(254, 243, 199)));
			drawRoundedRectOutline(g, RectangleF(260.0f, 245.0f, 95.0f, 38.0f), 8.0f, gcnew Pen(Color::FromArgb(245, 158, 11), 1.2f));
			g->DrawString("S/. " + root->left->right->key.ToString("F2"), gcnew System::Drawing::Font(L"Segoe UI", 7.0f, FontStyle::Bold), titleBrush, 265.0f, 250.0f);
			g->DrawString(toSystemString(root->left->right->value->getName()), gcnew System::Drawing::Font(L"Segoe UI", 6.2f), titleBrush, 265.0f, 265.0f);
		}

		if (root->right != nullptr && root->right->left != nullptr) {
			fillRoundedRect(g, RectangleF(390.0f, 245.0f, 95.0f, 38.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(254, 243, 199)));
			drawRoundedRectOutline(g, RectangleF(390.0f, 245.0f, 95.0f, 38.0f), 8.0f, gcnew Pen(Color::FromArgb(245, 158, 11), 1.2f));
			g->DrawString("S/. " + root->right->left->key.ToString("F2"), gcnew System::Drawing::Font(L"Segoe UI", 7.0f, FontStyle::Bold), titleBrush, 395.0f, 250.0f);
			g->DrawString(toSystemString(root->right->left->value->getName()), gcnew System::Drawing::Font(L"Segoe UI", 6.2f), titleBrush, 395.0f, 265.0f);
		}

		if (root->right != nullptr && root->right->right != nullptr) {
			fillRoundedRect(g, RectangleF(540.0f, 245.0f, 95.0f, 38.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(254, 243, 199)));
			drawRoundedRectOutline(g, RectangleF(540.0f, 245.0f, 95.0f, 38.0f), 8.0f, gcnew Pen(Color::FromArgb(245, 158, 11), 1.2f));
			g->DrawString("S/. " + root->right->right->key.ToString("F2"), gcnew System::Drawing::Font(L"Segoe UI", 7.0f, FontStyle::Bold), titleBrush, 545.0f, 250.0f);
			g->DrawString(toSystemString(root->right->right->value->getName()), gcnew System::Drawing::Font(L"Segoe UI", 6.2f), titleBrush, 545.0f, 265.0f);
		}
	} else if (sel == 5) {
		panelStructureDraw->AutoScrollMinSize = System::Drawing::Size(panelStructureDraw->Width, panelStructureDraw->Height);
		int pId = 1;
		if (cbBstProductSelect->SelectedIndex >= 0) {
			String^ selItem = cbBstProductSelect->SelectedItem->ToString();
			int spaceIdx = selItem->IndexOf(" ");
			int colonIdx = selItem->IndexOf(":");
			if (spaceIdx >= 0 && colonIdx > spaceIdx) {
				String^ idStr = selItem->Substring(spaceIdx + 1, colonIdx - spaceIdx - 1);
				pId = Int32::Parse(idStr);
			}
		}
		g->DrawString("BST - Resenas de Clientes para el Producto (ID: " + pId.ToString() + ")", titleFont, titleBrush, 15.0f, 15.0f);

		SimpleList<Review*>* productReviews = new SimpleList<Review*>();
		getReviewsForProductHelper(globalReviewsBst, pId, productReviews);

		if (productReviews->count() == 0) {
			g->DrawString(L"No hay resenas registradas en el BST para este producto.", nodeFont, titleBrush, 30.0f, 60.0f);
			delete productReviews;
			return;
		}

		BST<Review*, int>* tempBst = new BST<Review*, int>();
		int reviewCount = productReviews->count();
		Review** arr = new Review*[reviewCount];
		int idx = 0;
		for (auto it = productReviews->begin(); it != productReviews->end(); ++it) {
			arr[idx++] = *it;
		}

		for (int i = 1; i < reviewCount; i++) {
			Review* keyVal = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j]->getId() > keyVal->getId()) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = keyVal;
		}

		buildBalancedBSTHelper(tempBst, arr, 0, reviewCount - 1);
		delete[] arr;

		auto root = tempBst->getRoot();
		if (root != nullptr) {
			if (root->left != nullptr) g->DrawLine(linePen, 355.0f, 105.0f, 240.0f, 165.0f);
			if (root->right != nullptr) g->DrawLine(linePen, 400.0f, 105.0f, 520.0f, 165.0f);
			if (root->left != nullptr) {
				if (root->left->left != nullptr) g->DrawLine(linePen, 220.0f, 200.0f, 160.0f, 260.0f);
				if (root->left->right != nullptr) g->DrawLine(linePen, 265.0f, 200.0f, 310.0f, 260.0f);
			}
			if (root->right != nullptr) {
				if (root->right->left != nullptr) g->DrawLine(linePen, 500.0f, 200.0f, 440.0f, 260.0f);
				if (root->right->right != nullptr) g->DrawLine(linePen, 545.0f, 200.0f, 590.0f, 260.0f);
			}

			fillRoundedRect(g, RectangleF(310.0f, 55.0f, 135.0f, 45.0f), 8.0f, gcnew SolidBrush(nodeColor));
			drawRoundedRectOutline(g, RectangleF(310.0f, 55.0f, 135.0f, 45.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
			String^ stars1 = ""; for(int i=0; i<root->value->getRating(); ++i) stars1 += L"\u2605";
			g->DrawString(stars1, gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold), gcnew SolidBrush(Color::FromArgb(245, 158, 11)), 320.0f, 60.0f);
			g->DrawString("ID: " + root->key.ToString() + " - " + toSystemString(root->value->getComment()), gcnew System::Drawing::Font(L"Segoe UI", 6.0f), titleBrush, RectangleF(315.0f, 74.0f, 125.0f, 24.0f));

			if (root->left != nullptr) {
				fillRoundedRect(g, RectangleF(175.0f, 150.0f, 135.0f, 45.0f), 8.0f, gcnew SolidBrush(nodeColor));
				drawRoundedRectOutline(g, RectangleF(175.0f, 150.0f, 135.0f, 45.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
				String^ stars2 = ""; for(int i=0; i<root->left->value->getRating(); ++i) stars2 += L"\u2605";
				g->DrawString(stars2, gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold), gcnew SolidBrush(Color::FromArgb(245, 158, 11)), 185.0f, 155.0f);
				g->DrawString("ID: " + root->left->key.ToString() + " - " + toSystemString(root->left->value->getComment()), gcnew System::Drawing::Font(L"Segoe UI", 6.0f), titleBrush, RectangleF(180.0f, 169.0f, 125.0f, 24.0f));
			}

			if (root->right != nullptr) {
				fillRoundedRect(g, RectangleF(455.0f, 150.0f, 135.0f, 45.0f), 8.0f, gcnew SolidBrush(nodeColor));
				drawRoundedRectOutline(g, RectangleF(455.0f, 150.0f, 135.0f, 45.0f), 8.0f, gcnew Pen(nodeBorder, 1.5f));
				String^ stars3 = ""; for(int i=0; i<root->right->value->getRating(); ++i) stars3 += L"\u2605";
				g->DrawString(stars3, gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold), gcnew SolidBrush(Color::FromArgb(245, 158, 11)), 465.0f, 155.0f);
				g->DrawString("ID: " + root->right->key.ToString() + " - " + toSystemString(root->right->value->getComment()), gcnew System::Drawing::Font(L"Segoe UI", 6.0f), titleBrush, RectangleF(460.0f, 169.0f, 125.0f, 24.0f));
			}

			if (root->left != nullptr && root->left->left != nullptr) {
				fillRoundedRect(g, RectangleF(100.0f, 245.0f, 115.0f, 38.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(254, 243, 199)));
				drawRoundedRectOutline(g, RectangleF(100.0f, 245.0f, 115.0f, 38.0f), 8.0f, gcnew Pen(Color::FromArgb(245, 158, 11), 1.2f));
				String^ stars4 = ""; for(int i=0; i<root->left->left->value->getRating(); ++i) stars4 += L"\u2605";
				g->DrawString(stars4, gcnew System::Drawing::Font(L"Segoe UI", 7.5f, FontStyle::Bold), gcnew SolidBrush(Color::FromArgb(245, 158, 11)), 105.0f, 248.0f);
				g->DrawString("ID: " + root->left->left->key.ToString() + " - " + toSystemString(root->left->left->value->getComment()), gcnew System::Drawing::Font(L"Segoe UI", 5.8f), titleBrush, RectangleF(105.0f, 260.0f, 105.0f, 20.0f));
			}

			if (root->left != nullptr && root->left->right != nullptr) {
				fillRoundedRect(g, RectangleF(250.0f, 245.0f, 115.0f, 38.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(254, 243, 199)));
				drawRoundedRectOutline(g, RectangleF(250.0f, 245.0f, 115.0f, 38.0f), 8.0f, gcnew Pen(Color::FromArgb(245, 158, 11), 1.2f));
				String^ stars5 = ""; for(int i=0; i<root->left->right->value->getRating(); ++i) stars5 += L"\u2605";
				g->DrawString(stars5, gcnew System::Drawing::Font(L"Segoe UI", 7.5f, FontStyle::Bold), gcnew SolidBrush(Color::FromArgb(245, 158, 11)), 255.0f, 248.0f);
				g->DrawString("ID: " + root->left->right->key.ToString() + " - " + toSystemString(root->left->right->value->getComment()), gcnew System::Drawing::Font(L"Segoe UI", 5.8f), titleBrush, RectangleF(255.0f, 260.0f, 105.0f, 20.0f));
			}

			if (root->right != nullptr && root->right->left != nullptr) {
				fillRoundedRect(g, RectangleF(380.0f, 245.0f, 115.0f, 38.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(254, 243, 199)));
				drawRoundedRectOutline(g, RectangleF(380.0f, 245.0f, 115.0f, 38.0f), 8.0f, gcnew Pen(Color::FromArgb(245, 158, 11), 1.2f));
				String^ stars6 = ""; for(int i=0; i<root->right->left->value->getRating(); ++i) stars6 += L"\u2605";
				g->DrawString(stars6, gcnew System::Drawing::Font(L"Segoe UI", 7.5f, FontStyle::Bold), gcnew SolidBrush(Color::FromArgb(245, 158, 11)), 385.0f, 248.0f);
				g->DrawString("ID: " + root->right->left->key.ToString() + " - " + toSystemString(root->right->left->value->getComment()), gcnew System::Drawing::Font(L"Segoe UI", 5.8f), titleBrush, RectangleF(385.0f, 260.0f, 105.0f, 20.0f));
			}

			if (root->right != nullptr && root->right->right != nullptr) {
				fillRoundedRect(g, RectangleF(530.0f, 245.0f, 115.0f, 38.0f), 8.0f, gcnew SolidBrush(Color::FromArgb(254, 243, 199)));
				drawRoundedRectOutline(g, RectangleF(530.0f, 245.0f, 115.0f, 38.0f), 8.0f, gcnew Pen(Color::FromArgb(245, 158, 11), 1.2f));
				String^ stars7 = ""; for(int i=0; i<root->right->right->value->getRating(); ++i) stars7 += L"\u2605";
				g->DrawString(stars7, gcnew System::Drawing::Font(L"Segoe UI", 7.5f, FontStyle::Bold), gcnew SolidBrush(Color::FromArgb(245, 158, 11)), 535.0f, 248.0f);
				g->DrawString("ID: " + root->right->right->key.ToString() + " - " + toSystemString(root->right->right->value->getComment()), gcnew System::Drawing::Font(L"Segoe UI", 5.8f), titleBrush, RectangleF(535.0f, 260.0f, 105.0f, 20.0f));
			}
		}

		delete tempBst;
		delete productReviews;
	}
}

void home_screen::btnGPSConfirm_Click(System::Object^ sender, System::EventArgs^ e)
{
	gpsEndNode = cbDestinationCities->SelectedIndex;
	gpsStartNode = 0; gpsCurrentStep = 0;
	int pathLength = 0;
	gpsTotalDistance = registry->getProcessOrderUseCase()->calculateDeliveryRoute(gpsStartNode, gpsEndNode, gpsPath, pathLength);
	gpsPathLength = pathLength;
	if (gpsTotalDistance == -1 || gpsPathLength == 0) {
		MessageBox::Show("No hay ruta disponible", "GPS", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	timerGPS->Start();
}

void home_screen::timerGPS_Tick(System::Object^ sender, System::EventArgs^ e)
{
	if (gpsCurrentStep >= gpsPathLength - 1) {
		timerGPS->Stop();
		registry->getProcessOrderUseCase()->processNextOrder();
		registry->getManageCartUseCase()->clearCart();
		updateCartUI();
		MessageBox::Show("Pedido entregado exitosamente.", "Datamazon Logistics", MessageBoxButtons::OK, MessageBoxIcon::Information);
		activeView = "store"; switchActiveView();
		return;
	}
	gpsCurrentStep++;
	panelGPSDraw->Invalidate();
}

void home_screen::panelGPSDraw_Paint(System::Object^ sender, PaintEventArgs^ e)
{
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;
	g->TextRenderingHint = TextRenderingHint::ClearTypeGridFit;

	Graph<string>* graph = registry->getProcessOrderUseCase()->getDeliveryGraph();
	Pen^ edgePen = gcnew Pen(Color::FromArgb(203, 213, 225), 2);
	Pen^ activePen = gcnew Pen(Color::FromArgb(255, 153, 0), 4);
	System::Drawing::Font^ cityFont = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
	System::Drawing::Font^ distFont = gcnew System::Drawing::Font(L"Segoe UI", 8);

	for (int i = 0; i < graph->getV(); ++i) {
		SimpleList<typename Graph<string>::Edge>& adj = graph->getAdj(i);
		float x1 = (float)graph->getVertexX(i);
		float y1 = (float)graph->getVertexY(i);
		for (typename SimpleList<typename Graph<string>::Edge>::Iterator it = adj.begin(); it != adj.end(); ++it) {
			float x2 = (float)graph->getVertexX((*it).dest);
			float y2 = (float)graph->getVertexY((*it).dest);
			g->DrawLine(edgePen, x1, y1, x2, y2);
			g->DrawString((*it).weight.ToString() + " km", distFont, gcnew SolidBrush(Color::FromArgb(148, 163, 184)), (x1 + x2) / 2.0f, (y1 + y2) / 2.0f);
		}
	}

	if (gpsPathLength > 0) {
		for (int i = 0; i < gpsPathLength - 1; ++i) {
			g->DrawLine(activePen, (float)graph->getVertexX(gpsPath[i]), (float)graph->getVertexY(gpsPath[i]),
				(float)graph->getVertexX(gpsPath[i + 1]), (float)graph->getVertexY(gpsPath[i + 1]));
		}
	}

	for (int i = 0; i < graph->getV(); ++i) {
		float x = (float)graph->getVertexX(i);
		float y = (float)graph->getVertexY(i);
		bool active = false;
		for (int p = 0; p < gpsPathLength; ++p) { if (gpsPath[p] == i) active = true; }
		Color cityCol = active ? Color::FromArgb(34, 197, 94) : Color::FromArgb(30, 58, 138);
		g->FillEllipse(gcnew SolidBrush(cityCol), x - 16.0f, y - 16.0f, 32.0f, 32.0f);
		g->DrawEllipse(gcnew Pen(Color::White, 2.5f), x - 16.0f, y - 16.0f, 32.0f, 32.0f);
		g->DrawString(toSystemString(graph->getVertex(i)), cityFont, gcnew SolidBrush(Color::FromArgb(15, 17, 17)), x - 30.0f, y + 20.0f);
	}

	if (gpsPathLength > 0 && gpsCurrentStep < gpsPathLength) {
		float cx = (float)graph->getVertexX(gpsPath[gpsCurrentStep]);
		float cy = (float)graph->getVertexY(gpsPath[gpsCurrentStep]);
		g->FillEllipse(gcnew SolidBrush(Color::FromArgb(250, 204, 21)), cx - 10.0f, cy - 10.0f, 20.0f, 20.0f);
		g->DrawEllipse(gcnew Pen(Color::FromArgb(161, 98, 7), 2.0f), cx - 10.0f, cy - 10.0f, 20.0f, 20.0f);
		g->DrawString(L"\U0001F69A", gcnew System::Drawing::Font(L"Segoe UI", 12), gcnew SolidBrush(Color::FromArgb(161, 98, 7)), cx - 30.0f, cy - 35.0f);
	}
}

void home_screen::tabControl_DrawItem(System::Object^ sender, DrawItemEventArgs^ e)
{
	TabControl^ tc = safe_cast<TabControl^>(sender);
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;
	g->TextRenderingHint = TextRenderingHint::ClearTypeGridFit;

	TabPage^ page = tc->TabPages[e->Index];
	RectangleF tabRect((float)e->Bounds.X + 4.0f, (float)e->Bounds.Y + 6.0f, (float)e->Bounds.Width - 8.0f, (float)e->Bounds.Height - 10.0f);
	bool selected = (tc->SelectedIndex == e->Index);

	Color bg = selected ? Color::FromArgb(255, 153, 0) : Color::FromArgb(241, 245, 249);
	Color fg = selected ? Color::White : Color::FromArgb(71, 85, 105);

	fillRoundedRect(g, tabRect, 12.0f, gcnew SolidBrush(bg));

	StringFormat^ sf = gcnew StringFormat();
	sf->Alignment = StringAlignment::Center;
	sf->LineAlignment = StringAlignment::Center;
	g->DrawString(page->Text, gcnew System::Drawing::Font(L"Segoe UI", 9.5f, FontStyle::Bold), gcnew SolidBrush(fg), tabRect, sf);
}

void home_screen::listCartItems_DrawItem(System::Object^ sender, DrawItemEventArgs^ e)
{
	ListBox^ lb = safe_cast<ListBox^>(sender);
	if (e->Index < 0) return;
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;
	g->TextRenderingHint = TextRenderingHint::ClearTypeGridFit;

	bool selected = ((int)e->State & (int)DrawItemState::Selected) != 0;
	Color bg = selected ? Color::FromArgb(255, 237, 213) : (e->Index % 2 == 0 ? Color::FromArgb(248, 250, 252) : Color::White);

	g->FillRectangle(gcnew SolidBrush(bg), e->Bounds);

	if (selected) {
		RectangleF selBar((float)e->Bounds.X, (float)e->Bounds.Y, 4.0f, (float)e->Bounds.Height);
		g->FillRectangle(gcnew SolidBrush(Color::FromArgb(255, 153, 0)), selBar);
	}

	RectangleF textRect((float)e->Bounds.X + 14.0f, (float)e->Bounds.Y + 2.0f, (float)e->Bounds.Width - 20.0f, (float)e->Bounds.Height - 4.0f);
	StringFormat^ sf = gcnew StringFormat();
	sf->LineAlignment = StringAlignment::Center;
	g->DrawString(lb->Items[e->Index]->ToString(), gcnew System::Drawing::Font(L"Segoe UI", 9.5f), gcnew SolidBrush(Color::FromArgb(15, 17, 17)), textRect, sf);
}

void home_screen::listReviews_DrawItem(System::Object^ sender, DrawItemEventArgs^ e)
{
	ListBox^ lb = safe_cast<ListBox^>(sender);
	if (e->Index < 0) return;
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;
	g->TextRenderingHint = TextRenderingHint::ClearTypeGridFit;

	bool selected = ((int)e->State & (int)DrawItemState::Selected) != 0;
	Color bg = selected ? Color::FromArgb(254, 243, 199) : (e->Index % 2 == 0 ? Color::FromArgb(248, 250, 252) : Color::White);

	g->FillRectangle(gcnew SolidBrush(bg), e->Bounds);

	if (selected) {
		RectangleF selBar((float)e->Bounds.X, (float)e->Bounds.Y, 4.0f, (float)e->Bounds.Height);
		g->FillRectangle(gcnew SolidBrush(Color::FromArgb(245, 158, 11)), selBar);
	}

	RectangleF textRect((float)e->Bounds.X + 14.0f, (float)e->Bounds.Y + 2.0f, (float)e->Bounds.Width - 20.0f, (float)e->Bounds.Height - 4.0f);
	StringFormat^ sf = gcnew StringFormat();
	sf->LineAlignment = StringAlignment::Center;
	g->DrawString(lb->Items[e->Index]->ToString(), gcnew System::Drawing::Font(L"Segoe UI", 9.5f), gcnew SolidBrush(Color::FromArgb(15, 17, 17)), textRect, sf);
}

void home_screen::comboBox_DrawItem(System::Object^ sender, DrawItemEventArgs^ e)
{
	ComboBox^ cb = safe_cast<ComboBox^>(sender);
	if (e->Index < 0) return;
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;
	g->TextRenderingHint = TextRenderingHint::ClearTypeGridFit;

	bool selected = ((int)e->State & (int)DrawItemState::Selected) != 0;
	Color bg = selected ? Color::FromArgb(255, 237, 213) : Color::FromArgb(248, 250, 252);
	Color fg = selected ? Color::FromArgb(177, 39, 4) : Color::FromArgb(15, 17, 17);

	g->FillRectangle(gcnew SolidBrush(bg), e->Bounds);

	RectangleF textRect((float)e->Bounds.X + 8.0f, (float)e->Bounds.Y + 1.0f, (float)e->Bounds.Width - 12.0f, (float)e->Bounds.Height - 2.0f);
	StringFormat^ sf = gcnew StringFormat();
	sf->LineAlignment = StringAlignment::Center;
	g->DrawString(cb->Items[e->Index]->ToString(), gcnew System::Drawing::Font(L"Segoe UI", 9.5f), gcnew SolidBrush(fg), textRect, sf);
}

void home_screen::inputPanel_Paint(System::Object^ sender, PaintEventArgs^ e)
{
	Panel^ p = safe_cast<Panel^>(sender);
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;

	RectangleF mainRect(0.0f, 0.0f, (float)p->Width - 1.0f, (float)p->Height - 1.0f);
	fillRoundedRect(g, mainRect, 6.0f, gcnew SolidBrush(Color::White));
	drawRoundedRectOutline(g, mainRect, 6.0f, gcnew Pen(Color::FromArgb(213, 217, 217), 1.5f));
}

void home_screen::panelFilters_Paint(System::Object^ sender, PaintEventArgs^ e)
{
	Graphics^ g = e->Graphics;
	g->SmoothingMode = SmoothingMode::AntiAlias;

	RectangleF shadowRect(2.0f, 2.0f, (float)panelFilters->Width - 1.0f, (float)panelFilters->Height - 1.0f);
	fillRoundedRect(g, shadowRect, 16.0f, gcnew SolidBrush(Color::FromArgb(8, 0, 0, 0)));

	RectangleF mainRect(0.0f, 0.0f, (float)panelFilters->Width - 3.0f, (float)panelFilters->Height - 3.0f);
	fillRoundedRect(g, mainRect, 16.0f, gcnew SolidBrush(Color::White));
	drawRoundedRectOutline(g, mainRect, 16.0f, gcnew Pen(Color::FromArgb(230, 230, 230), 1.0f));
}

void home_screen::cbBstProductSelect_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	panelStructureDraw->Invalidate();
}

void home_screen::populateBstProductSelect()
{
	this->cbBstProductSelect->Items->Clear();
	DoubleList<Product*>* allProducts = registry->getProductRepository()->getAllProducts();
	for (auto it = allProducts->begin(); it != allProducts->end(); ++it) {
		this->cbBstProductSelect->Items->Add("ID " + (*it)->getId().ToString() + ": " + toSystemString((*it)->getName()));
	}
	if (this->cbBstProductSelect->Items->Count > 0) {
		this->cbBstProductSelect->SelectedIndex = 0;
	}
}

void home_screen::buildBalancedBSTHelper(BST<Review*, int>* tempBst, Review** arr, int start, int end)
{
	if (start > end) return;
	int mid = start + (end - start) / 2;
	tempBst->insert(arr[mid]->getId(), arr[mid]);
	buildBalancedBSTHelper(tempBst, arr, start, mid - 1);
	buildBalancedBSTHelper(tempBst, arr, mid + 1, end);
}

void home_screen::btnPrevPage_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (currentPage > 1) {
		currentPage--;
		renderCurrentPageProducts();
	}
}

void home_screen::btnNextPage_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (currentPage < totalPages) {
		currentPage++;
		renderCurrentPageProducts();
	}
}

void home_screen::btnGoPage_Click(System::Object^ sender, System::EventArgs^ e)
{
	try {
		int target = Int32::Parse(txtPageJump->Text);
		if (target >= 1 && target <= totalPages) {
			currentPage = target;
			renderCurrentPageProducts();
		} else {
			MessageBox::Show("Pagina fuera de rango (1 - " + totalPages.ToString() + ").", "Paginacion", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	} catch (...) {
		MessageBox::Show("Por favor, ingrese un numero de pagina valido.", "Paginacion", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void home_screen::renderCurrentPageProducts()
{
	flowProducts->Controls->Clear();
	hoveredCard = nullptr;
	hoveredCardButton = 0;

	int totalCount = (int)currentProductList->size();
	totalPages = (totalCount + PAGE_SIZE - 1) / PAGE_SIZE;
	if (totalPages < 1) totalPages = 1;
	if (currentPage > totalPages) currentPage = totalPages;
	if (currentPage < 1) currentPage = 1;

	lblPageInfo->Text = "Pagina " + currentPage.ToString() + " de " + totalPages.ToString();
	txtPageJump->Text = currentPage.ToString();

	int startIdx = (currentPage - 1) * PAGE_SIZE;
	int endIdx = startIdx + PAGE_SIZE;
	if (endIdx > totalCount) endIdx = totalCount;

	for (int i = startIdx; i < endIdx; ++i) {
		createProductCard((*currentProductList)[i]);
	}
}

void home_screen::applySortingToCurrentList()
{
	int n = (int)currentProductList->size();
	if (n <= 1) return;

	Product** arr = &(*currentProductList)[0];
	int sel = cbSortCriteria->SelectedIndex;

	if (sel == 1) {
		quickSort(arr, 0, n - 1, compareNameAsc);
	} else if (sel == 2) {
		quickSort(arr, 0, n - 1, compareNameDesc);
	} else if (sel == 3) {
		mergeSort(arr, 0, n - 1, comparePriceAsc);
	} else if (sel == 4) {
		mergeSort(arr, 0, n - 1, comparePriceDesc);
	} else if (sel == 5) {
		heapSort(arr, n, compareStockAsc);
	} else if (sel == 6) {
		heapSort(arr, n, compareStockDesc);
	}
}

void home_screen::refreshProductCatalog()
{
	currentProductList->clear();
	DoubleList<Product*>* allProducts = registry->getProductRepository()->getAllProducts();
	for (auto it = allProducts->begin(); it != allProducts->end(); ++it) {
		currentProductList->push_back(*it);
	}
	applySortingToCurrentList();
	currentPage = 1;
	populateBstProductSelect();
	renderCurrentPageProducts();
	panelStructureDraw->Invalidate();
}

[System::STAThreadAttribute]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew home_screen());
}

