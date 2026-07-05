#pragma once

#include "Domain/Entities/Review.h"
#include "Domain/Structures/BST.h"
#include "Application/UseCaseRegistry.h"
#include "Infrastructure/Datasources/DatasetGenerator.h"
#include <string>
#include <vector>
#include <functional>

namespace Datamazon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Drawing::Text;
	using namespace std;

	inline void getReviewsForProductHelper(BST<Review*, int>* bst, int productId, SimpleList<Review*>* outList) {
		bst->inOrderTraversal([productId, outList](Review* r) {
			if (r->getProductId() == productId) {
				outList->addBack(r);
			}
		});
	}

	public ref class home_screen : public System::Windows::Forms::Form
	{
	private:
		UseCaseRegistry* registry;
		bool isCartOpen;
		int cartTargetWidth;
		String^ activeView;
		Product* selectedProduct;

		System::Windows::Forms::Panel^ hoveredCard;
		int hoveredCardButton;

		System::ComponentModel::IContainer^ components;

		System::Windows::Forms::Panel^ panelHeader;
		System::Windows::Forms::PictureBox^ picLogo;
		System::Windows::Forms::Panel^ panelSearchBox;
		System::Windows::Forms::TextBox^ txtSearch;
		System::Windows::Forms::Button^ btnCartToggle;
		System::Windows::Forms::Button^ btnAdminToggle;

		System::Windows::Forms::Panel^ panelFilters;
		System::Windows::Forms::Label^ lblFiltersTitle;
		System::Windows::Forms::ComboBox^ cbCategories;
		System::Windows::Forms::ComboBox^ cbSortCriteria;
		System::Windows::Forms::Panel^ panelMinPrice;
		System::Windows::Forms::TextBox^ txtMinPrice;
		System::Windows::Forms::Panel^ panelMaxPrice;
		System::Windows::Forms::TextBox^ txtMaxPrice;
		System::Windows::Forms::Button^ btnApplyFilters;
		System::Windows::Forms::Button^ btnClearFilters;

		System::Windows::Forms::Panel^ panelCart;
		System::Windows::Forms::Label^ lblCartTitle;
		System::Windows::Forms::ListBox^ listCartItems;
		System::Windows::Forms::Label^ lblCartTotal;
		System::Windows::Forms::Button^ btnCheckout;
		System::Windows::Forms::Button^ btnClearCart;
		System::Windows::Forms::Timer^ timerCart;

		System::Windows::Forms::Panel^ panelContent;
		System::Windows::Forms::FlowLayoutPanel^ flowProducts;

		System::Windows::Forms::Panel^ panelProductDetail;
		System::Windows::Forms::Label^ lblDetailName;
		System::Windows::Forms::Label^ lblDetailCategory;
		System::Windows::Forms::Label^ lblDetailPrice;
		System::Windows::Forms::Label^ lblDetailStock;
		System::Windows::Forms::PictureBox^ picDetailProduct;
		System::Windows::Forms::Panel^ panelReviewComment;
		System::Windows::Forms::TextBox^ txtReviewComment;
		System::Windows::Forms::NumericUpDown^ numReviewRating;
		System::Windows::Forms::Button^ btnAddReview;
		System::Windows::Forms::ListBox^ listReviews;
		System::Windows::Forms::Button^ btnBackToStore;
		System::Windows::Forms::Button^ btnAddDetailToCart;

		System::Windows::Forms::Panel^ panelAdmin;
		System::Windows::Forms::TabControl^ tabControlAdmin;
		System::Windows::Forms::TabPage^ tabCrud;
		System::Windows::Forms::TabPage^ tabBenchmarks;
		System::Windows::Forms::TabPage^ tabStructures;
		System::Windows::Forms::Panel^ panelCrudId;
		System::Windows::Forms::TextBox^ txtCrudId;
		System::Windows::Forms::Panel^ panelCrudName;
		System::Windows::Forms::TextBox^ txtCrudName;
		System::Windows::Forms::Panel^ panelCrudCategory;
		System::Windows::Forms::TextBox^ txtCrudCategory;
		System::Windows::Forms::Panel^ panelCrudPrice;
		System::Windows::Forms::TextBox^ txtCrudPrice;
		System::Windows::Forms::Panel^ panelCrudStock;
		System::Windows::Forms::TextBox^ txtCrudStock;
		System::Windows::Forms::Button^ btnCrudAdd;
		System::Windows::Forms::Button^ btnCrudDelete;
		System::Windows::Forms::Button^ btnCrudBrowseImage;
		System::Windows::Forms::Label^ lblCrudImagePath;
		System::Windows::Forms::PictureBox^ picCrudImagePreview;
		System::Windows::Forms::OpenFileDialog^ openFileDialog;
		System::Windows::Forms::DataGridView^ gridAdminProducts;
		System::Windows::Forms::Button^ btnRunBenchmarks;
		System::Windows::Forms::Label^ lblBenchmarkResults;
		System::Windows::Forms::Button^ btnGenerateDataset;
		System::Windows::Forms::Panel^ panelDatasetCount;
		System::Windows::Forms::TextBox^ txtDatasetCount;
		System::Windows::Forms::ComboBox^ cbStructureSelect;
		System::Windows::Forms::ComboBox^ cbBstProductSelect;
		System::Windows::Forms::Panel^ panelStructureDraw;
		System::Windows::Forms::Panel^ panelPagination;
		System::Windows::Forms::Button^ btnPrevPage;
		System::Windows::Forms::Button^ btnNextPage;
		System::Windows::Forms::Label^ lblPageInfo;
		System::Windows::Forms::Label^ lblJumpTo;
		System::Windows::Forms::Panel^ panelPageJump;
		System::Windows::Forms::TextBox^ txtPageJump;
		System::Windows::Forms::Button^ btnGoPage;

		System::Windows::Forms::Panel^ panelGPS;
		System::Windows::Forms::Panel^ panelGPSDraw;
		System::Windows::Forms::Label^ lblGPSTitle;
		System::Windows::Forms::Label^ lblGPSInfo;
		System::Windows::Forms::Button^ btnGPSConfirm;
		System::Windows::Forms::ComboBox^ cbDestinationCities;
		System::Windows::Forms::Timer^ timerGPS;

		System::Windows::Forms::Panel^ panelLogin;
		System::Windows::Forms::Panel^ panelLoginCard;
		System::Windows::Forms::TextBox^ txtLoginUser;
		System::Windows::Forms::TextBox^ txtLoginPass;
		System::Windows::Forms::Button^ btnLoginSubmit;
		System::Windows::Forms::Panel^ panelCoupon;
		System::Windows::Forms::TextBox^ txtCouponCode;
		System::Windows::Forms::Button^ btnApplyCoupon;
		System::Windows::Forms::Label^ lblCouponStatus;
		System::Windows::Forms::Panel^ panelInvoiceModal;
		System::Windows::Forms::Label^ lblInvoiceDetails;
		System::Windows::Forms::Button^ btnCloseInvoiceModal;
		System::Windows::Forms::TabPage^ tabAdminClients;
		System::Windows::Forms::TabPage^ tabAdminSuppliers;
		System::Windows::Forms::TabPage^ tabAdminWarehouses;
		System::Windows::Forms::DataGridView^ gridAdminClients;
		System::Windows::Forms::DataGridView^ gridAdminSuppliers;
		System::Windows::Forms::DataGridView^ gridAdminWarehouses;

		int* gpsPath;
		int gpsPathLength;
		int gpsCurrentStep;
		float truckX;
		float truckY;
		int gpsStartNode;
		int gpsEndNode;
		int gpsTotalDistance;
		BST<Review*, int>* globalReviewsBst;
		std::vector<Product*>* currentProductList;
		int currentPage;
		int totalPages;
		static const int PAGE_SIZE = 10;
		Client* activeClient;
		String^ currentUserRole;
		Coupon* activeCoupon;

	public:
		home_screen(void)
		{
			InitializeComponent();
			registry = UseCaseRegistry::getInstance();
			isCartOpen = false;
			cartTargetWidth = 0;
			activeView = "login";
			selectedProduct = nullptr;
			hoveredCard = nullptr;
			hoveredCardButton = 0;
			activeClient = nullptr;
			currentUserRole = "client";
			activeCoupon = nullptr;
			currentProductList = new std::vector<Product*>();
			currentPage = 1;
			totalPages = 1;
			gpsPath = new int[20];
			gpsPathLength = 0;
			gpsCurrentStep = 0;
			truckX = 0;
			truckY = 0;

			globalReviewsBst = new BST<Review*, int>();
			int reviewIdSeq = 1;
			for (int pId = 1; pId <= 10; ++pId) {
				globalReviewsBst->insert(reviewIdSeq++, new Review(reviewIdSeq, pId, 100 + pId, 5, "Excelente calidad del producto. Totalmente recomendado."));
				globalReviewsBst->insert(reviewIdSeq++, new Review(reviewIdSeq, pId, 200 + pId, 4, "Muy buen funcionamiento, llego a tiempo."));
				globalReviewsBst->insert(reviewIdSeq++, new Review(reviewIdSeq, pId, 300 + pId, 3, "Aceptable por el costo."));
			}

			loadCategories();
			refreshProductCatalog();
		}

	protected:
		~home_screen()
		{
			delete[] gpsPath;
			delete globalReviewsBst;
			if (components) delete components;
		}

	private:
		static string toStdString(System::String^ s) {
			using namespace System::Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			string os(chars);
			Marshal::FreeHGlobal(IntPtr((void*)chars));
			return os;
		}

		static System::String^ toSystemString(const string& s) {
			return gcnew System::String(s.c_str());
		}

		static GraphicsPath^ createRoundedRectPath(RectangleF rect, float radius) {
			GraphicsPath^ path = gcnew GraphicsPath();
			float d = radius * 2.0f;
			path->AddArc(rect.X, rect.Y, d, d, 180.0f, 90.0f);
			path->AddArc(rect.X + rect.Width - d, rect.Y, d, d, 270.0f, 90.0f);
			path->AddArc(rect.X + rect.Width - d, rect.Y + rect.Height - d, d, d, 0.0f, 90.0f);
			path->AddArc(rect.X, rect.Y + rect.Height - d, d, d, 90.0f, 90.0f);
			path->CloseAllFigures();
			return path;
		}

		static void fillRoundedRect(Graphics^ g, RectangleF rect, float radius, Brush^ brush) {
			GraphicsPath^ path = createRoundedRectPath(rect, radius);
			g->FillPath(brush, path);
			delete path;
		}

		static void drawRoundedRectOutline(Graphics^ g, RectangleF rect, float radius, Pen^ pen) {
			GraphicsPath^ path = createRoundedRectPath(rect, radius);
			g->DrawPath(pen, path);
			delete path;
		}

		static String^ resolveImagePath(String^ imageFile) {
			String^ p;
			p = L"Images\\" + imageFile; if (System::IO::File::Exists(p)) return p;
			p = System::Windows::Forms::Application::StartupPath + L"\\Images\\" + imageFile; if (System::IO::File::Exists(p)) return p;
			p = System::AppDomain::CurrentDomain->BaseDirectory + L"\\Images\\" + imageFile; if (System::IO::File::Exists(p)) return p;
			p = L"..\\Images\\" + imageFile; if (System::IO::File::Exists(p)) return p;
			p = L"..\\..\\Datamazon\\Images\\" + imageFile; if (System::IO::File::Exists(p)) return p;
			return nullptr;
		}

		static void setRegionRounded(Control^ ctrl, int radius) {
			GraphicsPath^ path = gcnew GraphicsPath();
			float d = (float)(radius * 2);
			float w = (float)ctrl->Width;
			float h = (float)ctrl->Height;
			path->AddArc(0.0f, 0.0f, d, d, 180.0f, 90.0f);
			path->AddArc(w - d, 0.0f, d, d, 270.0f, 90.0f);
			path->AddArc(w - d, h - d, d, d, 0.0f, 90.0f);
			path->AddArc(0.0f, h - d, d, d, 90.0f, 90.0f);
			path->CloseAllFigures();
			ctrl->Region = gcnew System::Drawing::Region(path);
		}

		static void styleButton(Button^ btn, Color bg, Color fg, Color hover, Color pressed, float fontSize) {
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->FlatAppearance->MouseOverBackColor = hover;
			btn->FlatAppearance->MouseDownBackColor = pressed;
			btn->BackColor = bg;
			btn->ForeColor = fg;
			btn->Font = gcnew System::Drawing::Font("Segoe UI", fontSize, FontStyle::Bold);
			btn->Cursor = Cursors::Hand;
		}

		void loadCategories() {
			cbCategories->Items->Clear();
			cbCategories->Items->Add("Todas las Categorias");
			cbCategories->Items->Add("Tecnologia");
			cbCategories->Items->Add("Ropa");
			cbCategories->Items->Add("Educacion");
			cbCategories->SelectedIndex = 0;

			cbDestinationCities->Items->Clear();
			cbDestinationCities->Items->Add("Lima Centro");
			cbDestinationCities->Items->Add("Lima Norte");
			cbDestinationCities->Items->Add("Arequipa");
			cbDestinationCities->Items->Add("Trujillo");
			cbDestinationCities->Items->Add("Cusco");
			cbDestinationCities->Items->Add("Chiclayo");
			cbDestinationCities->Items->Add("Piura");
			cbDestinationCities->Items->Add("Ica");
			cbDestinationCities->SelectedIndex = 0;
		}

		void refreshProductCatalog();

		void createProductCard(Product* p) {
			Panel^ card = gcnew Panel();
			card->Size = System::Drawing::Size(200, 350);
			card->BackColor = System::Drawing::Color::FromArgb(245, 245, 245);
			card->Margin = System::Windows::Forms::Padding(10);
			card->Tag = IntPtr(p);
			card->Cursor = Cursors::Default;

			card->Paint += gcnew PaintEventHandler(this, &home_screen::card_Paint);
			card->MouseEnter += gcnew EventHandler(this, &home_screen::card_MouseEnter);
			card->MouseLeave += gcnew EventHandler(this, &home_screen::card_MouseLeave);
			card->MouseMove += gcnew MouseEventHandler(this, &home_screen::card_MouseMove);
			card->MouseClick += gcnew MouseEventHandler(this, &home_screen::card_MouseClick);

			flowProducts->Controls->Add(card);
		}

		void refreshProductReviews(Product* p) {
			listReviews->Items->Clear();
			SimpleList<Review*>* productReviews = new SimpleList<Review*>();
			getReviewsForProductHelper(globalReviewsBst, p->getId(), productReviews);

			for (auto it = productReviews->begin(); it != productReviews->end(); ++it) {
				Review* r = *it;
				String^ stars = "";
				for (int i = 0; i < r->getRating(); ++i) stars += L"\u2605";
				for (int i = r->getRating(); i < 5; ++i) stars += L"\u2606";
				listReviews->Items->Add(stars + "  " + toSystemString(r->getComment()));
			}
			delete productReviews;
		}

		void updateCartUI() {
			listCartItems->Items->Clear();
			::Stack<Product*>* cart = registry->getManageCartUseCase()->getCart();
			Node<Product*>* current = cart->getTop();
			while (current != nullptr) {
				listCartItems->Items->Add(toSystemString(current->value->getName()) + "   S/. " + current->value->getPrice().ToString("F2"));
				current = current->next;
			}
			double total = registry->getManageCartUseCase()->getCartTotal();
			if (activeCoupon != nullptr) {
				double discount = total * (activeCoupon->getDiscountPercent() / 100.0);
				total -= discount;
				lblCartTotal->Text = "Total: S/. " + total.ToString("F2") + " (-" + activeCoupon->getDiscountPercent().ToString("F0") + "%)";
			} else {
				lblCartTotal->Text = "Total: S/. " + total.ToString("F2");
			}
			btnCartToggle->Text = L"\U0001F6D2 Carrito (" + cart->count().ToString() + ")";
			panelStructureDraw->Invalidate();
		}

		void triggerCartOpenAnimation() {
			isCartOpen = true;
			cartTargetWidth = 320;
			timerCart->Start();
		}

		void switchActiveView() {
			panelLogin->Visible = (activeView == "login");
			panelHeader->Visible = (activeView != "login");
			panelContent->Visible = (activeView == "store");
			panelFilters->Visible = (activeView == "store");
			panelProductDetail->Visible = (activeView == "detail");
			panelAdmin->Visible = (activeView == "admin");
			panelGPS->Visible = (activeView == "gps");
			if (activeView == "admin") {
				panelStructureDraw->Invalidate();
			}
		}

		void InitializeComponent(void);
		void panelHeader_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		void panelSearchBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		void card_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		void card_MouseEnter(System::Object^ sender, System::EventArgs^ e);
		void card_MouseLeave(System::Object^ sender, System::EventArgs^ e);
		void card_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		void card_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		void btnApplyFilters_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClearFilters_Click(System::Object^ sender, System::EventArgs^ e);
		void txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e);
		void btnCartToggle_Click(System::Object^ sender, System::EventArgs^ e);
		void btnAdminToggle_Click(System::Object^ sender, System::EventArgs^ e);
		void timerCart_Tick(System::Object^ sender, System::EventArgs^ e);
		void btnClearCart_Click(System::Object^ sender, System::EventArgs^ e);
		void btnCheckout_Click(System::Object^ sender, System::EventArgs^ e);
		void btnBackToStore_Click(System::Object^ sender, System::EventArgs^ e);
		void btnAddDetailToCart_Click(System::Object^ sender, System::EventArgs^ e);
		void btnAddReview_Click(System::Object^ sender, System::EventArgs^ e);
		void btnCrudAdd_Click(System::Object^ sender, System::EventArgs^ e);
		void btnCrudDelete_Click(System::Object^ sender, System::EventArgs^ e);
		void btnCrudBrowseImage_Click(System::Object^ sender, System::EventArgs^ e);
		void btnRunBenchmarks_Click(System::Object^ sender, System::EventArgs^ e);
		void btnGenerateDataset_Click(System::Object^ sender, System::EventArgs^ e);
		void cbStructureSelect_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		void panelStructureDraw_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		void btnGPSConfirm_Click(System::Object^ sender, System::EventArgs^ e);
		void timerGPS_Tick(System::Object^ sender, System::EventArgs^ e);
		void panelGPSDraw_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		void tabControl_DrawItem(System::Object^ sender, System::Windows::Forms::DrawItemEventArgs^ e);
		void listCartItems_DrawItem(System::Object^ sender, System::Windows::Forms::DrawItemEventArgs^ e);
		void listReviews_DrawItem(System::Object^ sender, System::Windows::Forms::DrawItemEventArgs^ e);
		void comboBox_DrawItem(System::Object^ sender, System::Windows::Forms::DrawItemEventArgs^ e);
		void panelFilters_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		void inputPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		void cbBstProductSelect_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		void populateBstProductSelect();
		void buildBalancedBSTHelper(BST<Review*, int>* tempBst, Review** arr, int start, int end);
		void btnPrevPage_Click(System::Object^ sender, System::EventArgs^ e);
		void btnNextPage_Click(System::Object^ sender, System::EventArgs^ e);
		void btnGoPage_Click(System::Object^ sender, System::EventArgs^ e);
		void renderCurrentPageProducts();
		void applySortingToCurrentList();
		void btnLoginSubmit_Click(System::Object^ sender, System::EventArgs^ e);
		void btnApplyCoupon_Click(System::Object^ sender, System::EventArgs^ e);
		void btnCloseInvoiceModal_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
