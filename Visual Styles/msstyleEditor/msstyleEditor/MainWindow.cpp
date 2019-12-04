﻿#include "MainWindow.h"
#include "AboutDialog.h"
#include "HelpDialog.h"
#include "AddPropertyDialog.h"
#include "StringResourceDialog.h"

#include "CustomFileDropTarget.h"
#include "CustomTreeItemData.h"
#include "SearchDialog.h"
#include "UiHelper.h"
#include "Exporter.h"

#include "wxPropertyCategoryToolbar.h"

#include "libmsstyle\VisualStyle.h"
#include "libmsstyle\StylePart.h"

#include <wx\mstream.h>
#include <wx\wfstream.h>
#include <wx\wupdlock.h>

#include <algorithm>
#include <string>
#include <cctype>	// std::isspace

#include <shlobj.h> // SHGetKnownFolderPath()

using namespace libmsstyle;

#define TEXT_PLAY "&Test \u25B6"
#define TEXT_STOP "&Stop Test \u25A0"

// for identifying panes inside AUI manager
#define PANE_NAME_CLASSES "paneClasses"
#define PANE_NAME_IMAGE "paneImage"
#define PANE_NAME_PROPERTIES "paneProps"

// the caption text
#define PANE_CAPTION_CLASSES "Class View"
#define PANE_CAPTION_IMAGE "Image View"
#define PANE_CAPTION_PROPERTIES "Property View"

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
	, currentStyle(nullptr)
	, selectedImageProp(nullptr)
	, searchDlg(nullptr)
{
	this->SetSizeHints(wxSize(900, 600), wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_LISTBOX));

	m_auiManager = new wxAuiManager(this);

	classView = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT | wxHSCROLL | wxNO_BORDER | wxVSCROLL | wxTAB_TRAVERSAL);
	imageView = new ImageViewCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), 0);
	propView = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxSize(300, -1), wxPG_DEFAULT_STYLE | wxTAB_TRAVERSAL | wxNO_BORDER);

	m_paneInfoClassView.Left()
		.Name(wxT(PANE_NAME_CLASSES))
		.CaptionVisible(true)
		.DestroyOnClose(false)
		.Caption(wxT(PANE_CAPTION_CLASSES))
		.MinSize(300, 100);

	m_paneInfoImageView.Center()
		.Name(wxT(PANE_NAME_IMAGE))
		.CaptionVisible(true)
		.DestroyOnClose(false)
		.Caption(wxT(PANE_CAPTION_IMAGE))
		.MinSize(300, 100);

	m_paneInfoPropView.Right()
		.Name(wxT(PANE_NAME_PROPERTIES))
		.CaptionVisible(true)
		.DestroyOnClose(false)
		.Caption(wxT(PANE_CAPTION_PROPERTIES))
		.MinSize(300, 100);

	m_auiManager->AddPane(classView, m_paneInfoClassView);
	m_auiManager->AddPane(imageView, m_paneInfoImageView);
	m_auiManager->AddPane(propView, m_paneInfoPropView);

	m_auiManager->Update();

	mainmenu = new wxMenuBar();
	fileMenu = new wxMenu();
	editMenu = new wxMenu();
	viewMenu = new wxMenu();
	themeMenu = new wxMenu();
	aboutMenu = new wxMenu();

	wxMenu* exportSubMenu = new wxMenu();
	exportSubMenu->Append(ID_EXPORT_TREE, wxT("Style Info"));

	fileMenu->Append(ID_FOPEN, wxT("&Open\tCtrl+O"));
	fileMenu->Append(ID_FSAVE, wxT("&Save\tCtrl+S"));
	fileMenu->AppendSubMenu(exportSubMenu, wxT("&Export ..."));
	fileMenu->Enable(ID_FSAVE, false);

	themeMenu->Append(ID_THEME_APPLY, wxT(TEXT_PLAY));

	editMenu->Append(ID_IEXPORT, wxT("Image &Export"));
	editMenu->Append(ID_IREPLACE, wxT("Image &Replace"));
	editMenu->Enable(ID_IEXPORT, false);
	editMenu->Enable(ID_IREPLACE, false);
	// Not useful yet because saving string tables doesn't work atm
	//editMenu->AppendSeparator();
	//editMenu->Append(ID_STRING_RESOURCES, wxT("&String Resources"));
	//editMenu->Enable(ID_STRING_RESOURCES, false);
	editMenu->AppendSeparator();
	editMenu->Append(ID_FIND, wxT("&Find\tCtrl+F"));

	aboutMenu->Append(ID_HELP, wxT("&License"));
	aboutMenu->Append(ID_ABOUT, wxT("&About"));

	//
	// Image View  & Context Menu
	//
	imageViewMenu = new wxMenu();
	imageViewMenu->AppendRadioItem(ID_BG_WHITE, wxT("White"));
	imageViewMenu->AppendRadioItem(ID_BG_GREY, wxT("Light Grey"))->Check();
	imageViewMenu->AppendRadioItem(ID_BG_BLACK, wxT("Black"));
	imageViewMenu->AppendRadioItem(ID_BG_CHESS, wxT("Chessboard"));

	windowMgmtMenu = new wxMenu();
	windowMgmtMenu->Append(ID_PANE_CLASSVIEW, wxT(PANE_CAPTION_CLASSES));
	windowMgmtMenu->Append(ID_PANE_IMAGEVIEW, wxT(PANE_CAPTION_IMAGE));
	windowMgmtMenu->Append(ID_PANE_PROPVIEW, wxT(PANE_CAPTION_PROPERTIES));

	viewMenu->Append(ID_EXPAND_TREE, wxT("&Expand All"));
	viewMenu->Append(ID_COLLAPSE_TREE, wxT("&Collapse All"));
	viewMenu->AppendSubMenu(imageViewMenu, wxT("&Background"));
	viewMenu->AppendSubMenu(windowMgmtMenu, wxT("&Windows"));
	viewMenu->AppendSeparator();
	viewMenu->Append(ID_THEMEFOLDER, wxT("&Theme Folder"));
	viewMenu->Enable(ID_RESOURCEDLG, false);

	mainmenu->Append(fileMenu, wxT("&File"));
	mainmenu->Append(editMenu, wxT("&Edit"));
	mainmenu->Append(viewMenu, wxT("&View"));
	mainmenu->Append(themeMenu, wxT("&Theme"));
	mainmenu->Append(aboutMenu, wxT("&Info"));
	this->SetMenuBar(mainmenu);

	statusBar = this->CreateStatusBar(1);

	// Main Menu Event Handler
	Connect(ID_FOPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnFileOpenMenuClicked));
	Connect(ID_FSAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnFileSaveMenuClicked));
	Connect(ID_EXPORT_TREE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnExportLogicalStructure));
	Connect(ID_THEME_APPLY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnThemeApply));

	Connect(ID_IEXPORT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnImageExportClicked));
	Connect(ID_IREPLACE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnImageReplaceClicked));
	Connect(ID_STRING_RESOURCES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnEditStringResources));
	Connect(ID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnAboutClicked));
	Connect(ID_HELP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnHelpClicked));
	Connect(ID_COLLAPSE_TREE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnCollapseClicked));
	Connect(ID_EXPAND_TREE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnExpandClicked));
	Connect(ID_THEMEFOLDER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnOpenThemeFolder));
	Connect(ID_FIND, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnOpenSearchDlg));


	imageView->Connect(wxEVT_CONTEXT_MENU, wxContextMenuEventHandler(MainWindow::OnImageViewContextMenuTriggered), NULL, this);
	Connect(ID_BG_FIRST, ID_BG_LAST, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnImageViewBgSelect));
	Connect(ID_PANE_FIRST, ID_PANE_LAST, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnTogglePane));

	//
	// Treeview & Property Grid
	//
	Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(MainWindow::OnClassViewTreeSelChanged), NULL, this);

	propView->Connect(wxEVT_PG_CHANGING, wxPropertyGridEventHandler(MainWindow::OnPropertyGridChanging), NULL, this);
	propView->Connect(wxPropertyCategoryToolbar::ID_ADD_PROP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnPropertyGridItemCreate), NULL, this);
	propView->Connect(wxPropertyCategoryToolbar::ID_REMOVE_PROP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnPropertyGridItemDelete), NULL, this);
	propView->SetCaptionBackgroundColour(wxColour(0xE0E0E0));
	propView->SetCaptionTextColour(wxColour(0x202020)); // BGR
	propView->SetBackgroundColour(*wxWHITE);
	propView->SetMarginColour(*wxWHITE);
	propView->EnableScrolling(true, true);

	// Looks like the resource has to be on top alphabetically or it wont be used as caption image..
	wxFrame::SetIcon(wxICON(APPICON));

	this->SetDropTarget(new CustomFileDropTarget(*this));

	wxAcceleratorEntry entries[3];
	entries[0].Set(wxAcceleratorEntryFlags::wxACCEL_CTRL, wxKeyCode::WXK_CONTROL_F, ID_FIND);
	entries[1].Set(wxAcceleratorEntryFlags::wxACCEL_CTRL, wxKeyCode::WXK_CONTROL_S, ID_FSAVE);
	entries[2].Set(wxAcceleratorEntryFlags::wxACCEL_CTRL, wxKeyCode::WXK_CONTROL_O, ID_FOPEN);
	wxAcceleratorTable table(3, entries);
	SetAcceleratorTable(table);
}


//////////////////////////////////////////////////////////////////////////
// EVENT HANDLER
//////////////////////////////////////////////////////////////////////////

void MainWindow::OnFileOpenMenuClicked(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Visual Style"), "", "", "Visual Style (*.msstyles)|*.msstyles|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	CloseStyle();
	OpenStyle(openFileDialog.GetPath());
}

void MainWindow::OnFileSaveMenuClicked(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save Visual Style"), "", "", "Visual Style (*.msstyles)|*.msstyles", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	try
	{
		wxString wxpath = saveFileDialog.GetPath();
		const wxScopedCharBuffer buf = wxpath.ToUTF8();
		std::string utf8Path(buf.data(), buf.length());

		currentStyle->Save(utf8Path);
		statusBar->SetStatusText("Style saved successfully!");
	}
	catch (std::runtime_error err)
	{
		wxMessageBox(err.what(), "Error saving file!", wxICON_ERROR);
	}
}

void MainWindow::OnExportLogicalStructure(wxCommandEvent& event)
{
	if (currentStyle == nullptr)
		return;

	try
	{
		wxFileDialog saveFileDialog(this, _("Export Style Info"), "", "", "Style Info (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL)
			return;

		Exporter::ExportLogicalStructure(saveFileDialog.GetPath().ToStdWstring(), *currentStyle);
	}
	catch (std::runtime_error ex)
	{
		wxMessageBox(ex.what(), wxT("Error exporting"), wxICON_ERROR);
	}
}

void MainWindow::OnThemeApply(wxCommandEvent& event)
{
	if (currentStyle == nullptr)
		return;

	if (themeManager.IsThemeInUse())
	{
		try
		{
			themeManager.Rollback();
			themeMenu->SetLabel(ID_THEME_APPLY, wxT(TEXT_PLAY));
			Sleep(300); // prevent doubleclicks
			return;
		}
		catch (...)
		{
		}
	}

	bool needConfirmation = false;
	OSVERSIONINFO version;
	ZeroMemory(&version, sizeof(OSVERSIONINFO));
	version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

#pragma warning( disable : 4996 )
	GetVersionEx(&version);

	libmsstyle::Platform styleplatform = currentStyle->GetCompatiblePlatform();

	if (version.dwMajorVersion == 6 &&
		version.dwMinorVersion == 1 &&
		styleplatform != libmsstyle::Platform::WIN7)
	{
		needConfirmation = true;
	}

	if (version.dwMajorVersion == 6 &&
		version.dwMinorVersion >= 2 &&
		styleplatform != libmsstyle::Platform::WIN8 &&
		styleplatform != libmsstyle::Platform::WIN81)
	{
		needConfirmation = true;
	}

	if (version.dwMajorVersion == 10 &&
		version.dwMinorVersion >= 0 &&
		styleplatform != libmsstyle::Platform::WIN10)
	{
		needConfirmation = true;
	}

	if (needConfirmation)
	{
		if (wxMessageBox(wxT("It looks like the style was not made for this windows version. Try to apply it anyways?"), wxT("msstyleEditor"), wxYES_NO | wxICON_WARNING) == wxNO)
			return;
	}

	try
	{
		themeManager.ApplyTheme(*currentStyle);
		themeMenu->SetLabel(ID_THEME_APPLY, wxT(TEXT_STOP));
		Sleep(300); // prevent doubleclicks
	}
	catch (std::runtime_error& err)
	{
		wxMessageBox(err.what(), "Error applying style!", wxICON_ERROR);
	}
	catch (std::exception& ex)
	{
		wxMessageBox(ex.what(), "Error applying style!", wxICON_ERROR);
	}
	catch (...)
	{
		wxMessageBox("Unknown exception!", "Error applying style!", wxICON_ERROR);
	}
}

void MainWindow::OnClassViewTreeSelChanged(wxTreeEvent& event)
{
	auto treeItemID = event.GetItem();
	auto treeItemData = classView->GetItemData(treeItemID);

	selectedImageProp = nullptr;
	imageView->RemoveImage();
	statusBar->SetStatusText(wxEmptyString);

	// Class Node
	ClassTreeItemData* classData = dynamic_cast<ClassTreeItemData*>(treeItemData);
	if (classData != nullptr)
	{
		// Track selection
		selection.ClassId = classData->GetClass()->classID;
		selection.PartId = -1;
		selection.StateId = -1;

		statusBar->SetStatusText(wxString::Format("C: %d", selection.ClassId));

		// Update UI
		propView->Clear();
		return;
	}

	// Part Node
	PartTreeItemData* partData = dynamic_cast<PartTreeItemData*>(treeItemData);
	if (partData != nullptr)
	{
		StylePart* part = partData->GetPart();

		// Track selection
		classData = dynamic_cast<ClassTreeItemData*>(
			classView->GetItemData(
			classView->GetItemParent(treeItemID)));

		selection.ClassId = classData->GetClass()->classID;
		selection.PartId = part->partID;
		selection.StateId = -1;

		// Update UI
		statusBar->SetStatusText(wxString::Format("C: %d, P: %d", selection.ClassId, part->partID));
		FillPropertyView(*part);
		return;
	}

	// Image Node
	PropTreeItemData* propData = dynamic_cast<PropTreeItemData*>(treeItemData);
	if (propData != nullptr)
	{
		selectedImageProp = propData->GetProperty();

		// Track selection
		partData = dynamic_cast<PartTreeItemData*>(
			classView->GetItemData(
			classView->GetItemParent(treeItemID)));

		classData = dynamic_cast<ClassTreeItemData*>(
			classView->GetItemData(
			classView->GetItemParent(
			classView->GetItemParent(treeItemID))));

		selection.ClassId = classData->GetClass()->classID;
		selection.PartId = partData->GetPart()->partID;
		selection.StateId = -1;

		// Update UI
		StyleResourceType type;
		if (selectedImageProp->GetTypeID() == IDENTIFIER::FILENAME ||
			selectedImageProp->GetTypeID() == IDENTIFIER::FILENAME_LITE)
			type = StyleResourceType::rtImage;
		else if (selectedImageProp->GetTypeID() == IDENTIFIER::DISKSTREAM)
			type = StyleResourceType::rtAtlas;
		else type = StyleResourceType::rtNone;

		std::string file = currentStyle->GetQueuedResourceUpdate(selectedImageProp->GetResourceID(), type);
		if (!file.empty())
		{
			ShowImageFromFile(wxString::FromUTF8(file.c_str()));

			statusBar->SetStatusText(wxString::Format("C: %d, P: %d, Img: %d*", selection.ClassId, selection.PartId, selectedImageProp->GetResourceID()));
		}
		else
		{
			ShowImageFromResource(selectedImageProp);
			statusBar->SetStatusText(wxString::Format("C: %d, P: %d, Img: %d", selection.ClassId, selection.PartId, selectedImageProp->GetResourceID()));
		}

		return;
	}

	return;
}

void MainWindow::OnPropertyGridChanging(wxPropertyGridEvent& event)
{
	wxPGProperty* tmpProp = event.GetProperty();
	StyleProperty* styleProp = (StyleProperty*)tmpProp->GetClientData();

	if (!styleProp)
		return;

	// COLORIZATIONCOLOR is internally an integer...
	if (styleProp->GetNameID() == IDENTIFIER::COLORIZATIONCOLOR)
	{
		wxAny value = event.GetValidationInfo().GetValue();
		wxColor color = value.As<wxColour>();

		int colargb = color.Alpha() << 24 | color.Red() << 16 | color.Green() << 8 | color.Blue();
		styleProp->UpdateIntegerUnchecked(colargb);
		return;
	}

	switch (styleProp->header.typeID)
	{
	case IDENTIFIER::FILENAME:
		styleProp->UpdateImageLink(event.GetValidationInfo().GetValue().GetInteger()); break;
	case IDENTIFIER::INT:
		styleProp->UpdateInteger(event.GetValidationInfo().GetValue().GetInteger()); break;
	case IDENTIFIER::SIZE:
		styleProp->UpdateSize(event.GetValidationInfo().GetValue().GetInteger()); break;
	case IDENTIFIER::ENUM:
		styleProp->UpdateEnum(event.GetValidationInfo().GetValue().GetInteger()); break;
	case IDENTIFIER::BOOLTYPE:
		styleProp->UpdateBoolean(event.GetValidationInfo().GetValue().GetBool()); break;
	case IDENTIFIER::COLOR:
	{
		wxAny value = event.GetValidationInfo().GetValue();
		wxColor color = value.As<wxColour>();
		styleProp->UpdateColor(color.Red(), color.Green(), color.Blue());
	} break;
	case IDENTIFIER::RECTTYPE:
	case IDENTIFIER::MARGINS:
	{
		int l, t, r, b;
		if (sscanf(event.GetValidationInfo().GetValue().GetString().mb_str(), "%d, %d, %d, %d", &l, &t, &r, &b) != 4)
		{
			event.Veto();
			wxMessageBox("Invalid format! expected: a, b, c, d", "format error", wxICON_ERROR);
			return;
		}
		else
		{
			if (styleProp->header.typeID == IDENTIFIER::RECTTYPE)
				styleProp->UpdateRectangle(l, t, r, b);
			if (styleProp->header.typeID == IDENTIFIER::MARGINS)
				styleProp->UpdateMargin(l, t, r, b);
		}
	} break;
	case IDENTIFIER::POSITION:
	{
		int x, y;
		if (sscanf(event.GetValidationInfo().GetValue().GetString().mb_str(), "%d, %d", &x, &y) != 2)
		{
			event.Veto();
			wxMessageBox("Invalid format! expected: a, b", "format error", wxICON_ERROR);
			return;
		}
		else
		{
			styleProp->UpdatePosition(x, y);
		}
	} break;
	case IDENTIFIER::FONT:
		styleProp->UpdateFont(event.GetValidationInfo().GetValue().GetInteger()); break;
	case IDENTIFIER::HIGHCONTRASTCOLORTYPE:
		styleProp->UpdateHCC(event.GetValidationInfo().GetValue().GetInteger()); break;
	default:
	{
		char msg[100];
		sprintf(msg, "Changing properties of type '%s' is not supported yet!", lookup::FindTypeName(styleProp->GetTypeID()));
		wxMessageBox(msg, "Unsupported", wxICON_INFORMATION);

		event.Veto();
	} break;
	}

}

void MainWindow::OnPropertyGridItemCreate(wxCommandEvent& event)
{
	if (selection.ClassId < 0 ||
		selection.PartId < 0)
	{
		wxMessageBox("Internal error. lost track of state.");
		return;
	}

	wxPropertyCategoryToolbar* category = dynamic_cast<wxPropertyCategoryToolbar*>(event.GetEventObject());

	libmsstyle::StyleProperty* prop = new StyleProperty();
	prop->header.classID = selection.ClassId;
	prop->header.partID = selection.PartId;
	prop->header.stateID = ((StyleState*)category->GetClientData())->stateID;

	AddPropertyDialog propDlg(this);
	if (propDlg.ShowModal(*prop) == wxID_OK)
	{
		StylePart* part = currentStyle->FindClass(selection.ClassId)
			->FindPart(selection.PartId);

		part->FindState(prop->header.stateID)->AddProperty(prop);

		FillPropertyView(*part);
	}
	else delete prop;
}

void MainWindow::OnPropertyGridItemDelete(wxCommandEvent& event)
{
	wxPGProperty* wxprop = propView->GetSelection();
	if (wxprop == nullptr || wxprop->IsCategory())
	{
		wxMessageBox("No item selected!");
		return;
	}

	if (selection.ClassId < 0 ||
		selection.PartId < 0)
	{
		wxMessageBox("Internal error. Lost track of selection.", "Remove Property", wxICON_ERROR);
		return;
	}

	StyleProperty* prop = static_cast<StyleProperty*>(wxprop->GetClientData());
	if (/*prop->GetTypeID() == IDENTIFIER::FILENAME ||*/
		prop->GetTypeID() == IDENTIFIER::FILENAME_LITE ||
		prop->GetTypeID() == IDENTIFIER::DISKSTREAM)
	{
		wxMessageBox("Cannot remove image properties yet!", "Remove Property", wxICON_INFORMATION);
		return;
	}

	wxString msgText = wxString::Format("Remove property \"%s\" with value: \"%s\"?", prop->LookupName(), prop->GetValueAsString());
	if (wxMessageBox(msgText, "Remove Property", wxYES_NO) == wxYES)
	{
		StylePart* part = currentStyle->FindClass(selection.ClassId)
			->FindPart(selection.PartId);

		// todo: cannot just remove any prop. image props are still used in the classview..
		part->FindState(prop->header.stateID)->RemoveProperty(prop);
		FillPropertyView(*part);
	}
}

void MainWindow::OnImageExportClicked(wxCommandEvent& event)
{
	if (selectedImage.GetSize() == 0 || selectedImage.GetData() == 0 || selectedImageProp == nullptr)
	{
		wxMessageBox("Select an image first!", "Export Image", wxICON_ERROR);
		return;
	}

	wxFileDialog saveFileDialog(this, "Export Image", "", "", "PNG Image (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxFileOutputStream outputStream(saveFileDialog.GetPath());
	if (!outputStream.IsOk())
	{
		wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
		return;
	}

	if (!outputStream.WriteAll(selectedImage.GetData(), selectedImage.GetSize()))
	{
		wxLogError("Error while writing to the file!");
		return;
	}

	statusBar->SetStatusText("Image exported successfully!");
}

void MainWindow::OnImageReplaceClicked(wxCommandEvent& event)
{
	if (selectedImageProp == nullptr)
	{
		wxMessageBox("Select an image resource first!", "Replace Image", wxICON_ERROR);
		return;
	}

	wxFileDialog openFileDialog(this, "Replace Image", "", "", "PNG Image (*.png)|*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	StyleResourceType tp;
	switch (selectedImageProp->GetTypeID())
	{
	case IDENTIFIER::FILENAME:
	case IDENTIFIER::FILENAME_LITE:
		tp = StyleResourceType::rtImage; break;
	case IDENTIFIER::DISKSTREAM:
		tp = StyleResourceType::rtAtlas; break;
	default:
		tp = StyleResourceType::rtNone; break;
	}

	wxString path = openFileDialog.GetPath();
	const wxScopedCharBuffer buf = path.ToUTF8();
	std::string utf8Path(buf.data(), buf.length());
	currentStyle->QueueResourceUpdate(selectedImageProp->GetResourceID(), tp, utf8Path);
}

void MainWindow::OnEditStringResources(wxCommandEvent& event)
{
	StringResourceDialog dlg(this, currentStyle->GetStringTable());
	dlg.ShowModal();
}

void MainWindow::OnImageViewContextMenuTriggered(wxContextMenuEvent& event)
{
	imageView->PopupMenu(imageViewMenu, imageView->ScreenToClient(event.GetPosition()));
}

void MainWindow::OnImageViewBgSelect(wxCommandEvent& event)
{
	switch (event.GetId())
	{
	case ID_BG_WHITE:
		imageView->SetBackgroundStyle(ImageViewCtrl::BackgroundStyle::White);
		break;
	case ID_BG_GREY:
		imageView->SetBackgroundStyle(ImageViewCtrl::BackgroundStyle::LightGrey);
		break;
	case ID_BG_BLACK:
		imageView->SetBackgroundStyle(ImageViewCtrl::BackgroundStyle::Black);
		break;
	case ID_BG_CHESS:
		imageView->SetBackgroundStyle(ImageViewCtrl::BackgroundStyle::Chessboard);
		break;
	default:
		break;
	}
}

void MainWindow::OnTogglePane(wxCommandEvent& event)
{
	const char* paneName = nullptr;

	switch (event.GetId())
	{
	case ID_PANE_CLASSVIEW:
		paneName = PANE_NAME_CLASSES; break;
	case ID_PANE_IMAGEVIEW:
		paneName = PANE_NAME_IMAGE; break;
	case ID_PANE_PROPVIEW:
		paneName = PANE_NAME_PROPERTIES; break;
	default: break;
	}

	wxAuiPaneInfo& pane = m_auiManager->GetPane(paneName);
	if (pane.IsOk())
	{
		pane.Show(!pane.IsShown());
		m_auiManager->Update();
	}
}

void MainWindow::OnHelpClicked(wxCommandEvent& event)
{
	HelpDialog helpDlg(this, wxID_ANY, wxT("License"));
	helpDlg.ShowModal();
}

void MainWindow::OnAboutClicked(wxCommandEvent& event)
{
	AboutDialog aboutDlg(this, wxID_ANY, wxT("About"));
	aboutDlg.ShowModal();
}

void MainWindow::OnCollapseClicked(wxCommandEvent& event)
{
	// Hide temporarily so collapsing goes faster (no unnecessary redraws)
	classView->HideWithEffect(wxShowEffect::wxSHOW_EFFECT_BLEND);
	classView->CollapseAll();
	classView->ShowWithEffect(wxShowEffect::wxSHOW_EFFECT_BLEND);

	// collapse centered around the currently selected item
	// also focus the treeview again, as the menu took the focus
	wxTreeItemIdValue cookie;
	wxTreeItemId selectedItem = classView->GetSelection();
	if (selectedItem != nullptr)
		classView->ScrollTo(selectedItem);
	else
	{
		wxTreeItemId root = classView->GetRootItem();
		if (root.IsOk())
		{
			wxTreeItemId first = classView->GetFirstChild(root, cookie);
			if (first.IsOk())
			{
				classView->ScrollTo(first);
			}
		}
	}

	classView->SetFocus();
}

void MainWindow::OnExpandClicked(wxCommandEvent& event)
{
	// Hide temporarily so expansion goes faster (no unnecessary redraws)
	classView->HideWithEffect(wxShowEffect::wxSHOW_EFFECT_BLEND);
	classView->ExpandAll();
	classView->ShowWithEffect(wxShowEffect::wxSHOW_EFFECT_BLEND);

	// expand centered around the currently selected item
	// also focus the treeview again, as the menu took the focus
	wxTreeItemIdValue cookie;
	wxTreeItemId selectedItem = classView->GetSelection();
	if (selectedItem != nullptr)
		classView->ScrollTo(selectedItem);
	else
	{
		wxTreeItemId root = classView->GetRootItem();
		if (root.IsOk())
		{
			wxTreeItemId first = classView->GetFirstChild(root, cookie);
			if (first.IsOk())
			{
				classView->ScrollTo(first);
			}
		}
	}

	classView->SetFocus();
}

void MainWindow::OnOpenThemeFolder(wxCommandEvent& event)
{
	wchar_t* windowsFolder = nullptr;
	if (SHGetKnownFolderPath(FOLDERID_Windows, KF_FLAG_DEFAULT, NULL, &windowsFolder) == S_OK)
	{
		wxString cmd = wxString::Format("explorer %s\\Resources\\Themes\\", windowsFolder);
		CoTaskMemFree(windowsFolder);
		wxExecute(cmd, wxEXEC_ASYNC, NULL);
	}
	else wxExecute("explorer C:\\Windows\\Resources\\Themes\\", wxEXEC_ASYNC, NULL);
}

void MainWindow::OnOpenSearchDlg(wxCommandEvent& event)
{
	if (searchDlg == nullptr)
	{
		searchDlg = new SearchDialog(this);
		searchDlg->SetSearchHandler((ISearchDialogListener*)this);
	}

	if (!searchDlg->IsShown())
		searchDlg->Show();
}

bool endReached = false;
void MainWindow::OnFindNext(const SearchProperties& search)
{
	if (currentStyle == nullptr)
		return;

	if (search.value.length() == 0)
		return;

	wxTreeItemId startItem = classView->GetSelection();
	if (!startItem.IsOk() || endReached)
	{
		endReached = false;
		startItem = classView->GetRootItem();
		if (!startItem.IsOk())
			return;
	}

	wxTreeItemId item = FindNext(search, startItem);
	if (item.IsOk())
	{
		classView->SelectItem(item);
	}
	else
	{
		wxMessageBox(wxT("No further match for \"")
			+ search.value
			+ wxT("\" !\n")
			+ wxT("Search will begin from top again."));
		endReached = true;
	}
}


bool ContainsStringInvariant(const std::string& text, const std::string& toFind)
{
	auto it = std::search(text.begin(), text.end(),
		toFind.begin(), toFind.end(),
		[](char c1, char c2) -> bool
	{
		return std::toupper(c1) == std::toupper(c2);
	});

	return (it != text.end());
}

bool ContainsProperty(const SearchProperties& search, wxTreeItemData* treeItemData)
{
	if (treeItemData == nullptr)
		return false;

	// If its a part node, check its properties
	PartTreeItemData* partData = dynamic_cast<PartTreeItemData*>(treeItemData);
	if (partData == nullptr)
		return false;

	StylePart* part = partData->GetPart();

	for (auto& state : *part)
	{
		for (auto& prop : state.second)
		{
			// if its a property of the desired type, do a comparison
			if (prop->header.typeID != search.type)
				continue;

			// comparison
			switch (prop->header.typeID)
			{
			case IDENTIFIER::POSITION:
			{
				char propPos[32];
				sprintf(propPos, "%d,%d",
					prop->data.positiontype.x,
					prop->data.positiontype.y);

				std::string tmp = search.value;
				tmp.erase(std::remove_if(tmp.begin(), tmp.end(), std::isspace), tmp.end());

				if (ContainsStringInvariant(std::string(propPos), tmp))
					return true;
			} break;
			case IDENTIFIER::COLOR:
			{
				char propColor[32];
				sprintf(propColor, "%d,%d,%d",
					prop->data.colortype.r,
					prop->data.colortype.g,
					prop->data.colortype.b);

				std::string tmp = search.value;
				tmp.erase(std::remove_if(tmp.begin(), tmp.end(), std::isspace), tmp.end());

				if (ContainsStringInvariant(std::string(propColor), tmp))
					return true;
			} break;
			case IDENTIFIER::MARGINS:
			{
				char propMargin[32];
				sprintf(propMargin, "%d,%d,%d,%d",
					prop->data.margintype.left,
					prop->data.margintype.top,
					prop->data.margintype.right,
					prop->data.margintype.bottom);

				std::string tmp = search.value;
				tmp.erase(std::remove_if(tmp.begin(), tmp.end(), std::isspace), tmp.end());

				if (ContainsStringInvariant(std::string(propMargin), tmp))
					return true;
			} break;
			case IDENTIFIER::RECTTYPE:
			{
				char propRect[32];
				sprintf(propRect, "%d,%d,%d,%d",
					prop->data.recttype.left,
					prop->data.recttype.top,
					prop->data.recttype.right,
					prop->data.recttype.bottom);

				std::string tmp = search.value;
				tmp.erase(std::remove_if(tmp.begin(), tmp.end(), std::isspace), tmp.end());

				if (ContainsStringInvariant(std::string(propRect), tmp))
					return true;
			} break;
			case IDENTIFIER::SIZE:
			{
				try
				{
					int size = std::stoi(search.value);
					if (size == prop->data.sizetype.size)
						return true;
				}
				catch (...) {}
			} break;
			}
		}
	}

	return false;
}

bool ContainsName(const std::string& str, wxTreeItemData* treeItemData)
{
	if (treeItemData == nullptr)
		return false;

	// Class Node
	ClassTreeItemData* classData = dynamic_cast<ClassTreeItemData*>(treeItemData);
	if (classData != nullptr)
	{
		return ContainsStringInvariant(classData->GetClass()->className, str);
	}

	// Part Node
	PartTreeItemData* partData = dynamic_cast<PartTreeItemData*>(treeItemData);
	if (partData != nullptr)
	{
		return ContainsStringInvariant(partData->GetPart()->partName, str);
	}

	// Image Node
	PropTreeItemData* propData = dynamic_cast<PropTreeItemData*>(treeItemData);
	if (propData != nullptr)
	{
		const char* name = propData->GetProperty()->LookupName();
		if (name == nullptr)
			return false;
		else return ContainsStringInvariant(std::string(name), str);
	}

	return false;
}

wxTreeItemId MainWindow::FindNext(const SearchProperties& search, wxTreeItemId node)
{
	wxTreeItemIdValue cookie;
	wxTreeItemId originalNode = node;
	while (node.IsOk())
	{
		// see whether the node contains "search.value" somewhere.
		// skip the first node to not get stuck.
		if (node != originalNode)
		{
			wxTreeItemData* data = classView->GetItemData(node);
			switch (search.mode)
			{
			case SearchProperties::MODE_NAME:
			{
				if (ContainsName(search.value, data))
					return node;
			} break;
			case SearchProperties::MODE_PROPERTY:
			{
				if (ContainsProperty(search, data))
					return node;
			} break;
			default:
				break;
			}
		}


		// find nodes: depth
		wxTreeItemId nextNode = classView->GetFirstChild(node, cookie);
		if (!nextNode.IsOk())
		{
			// find nodes: breadth
			nextNode = classView->GetNextSibling(node);
			if (!nextNode.IsOk())
			{
				// back out and try finding a node in the breadth
				wxTreeItemId previous = node;
				nextNode = classView->GetItemParent(node);
				while (nextNode.IsOk() && nextNode != classView->GetRootItem() && !classView->GetNextSibling(nextNode).IsOk())
				{
					nextNode = classView->GetItemParent(nextNode);
				}

				if (nextNode == classView->GetRootItem())
					return wxTreeItemId();

				if (nextNode.IsOk()) // parent ok, so we have a sibling
					nextNode = classView->GetNextSibling(nextNode);
				//else: parent was not ok because we reached the root node -> no nodes left anymore -> search done
			}
		}

		node = nextNode;
	}

	return wxTreeItemId();
}


//////////////////////////////////////////////////////////////////////////
// OTHER LOGIC
//////////////////////////////////////////////////////////////////////////

void MainWindow::OpenStyle(const wxString& file)
{
	currentStyle = new VisualStyle();

	try
	{
		const wxScopedCharBuffer buf = file.ToUTF8();
		std::string utf8Path(buf.data(), buf.length());
		currentStyle->Load(utf8Path);
	}
	catch (std::exception& ex)
	{
		wxString message("Are you sure this is a Windows Vista, 7, 8 or 10 visual style?\r\n\r\nDetails: ");
		message += ex.what();
		wxMessageBox(message, "Error loading style!", wxICON_ERROR, this);
		delete currentStyle;
		currentStyle = nullptr;
		return;
	}

	FillClassView();

	editMenu->Enable(ID_IEXPORT, true);
	editMenu->Enable(ID_IREPLACE, true);
	editMenu->Enable(ID_STRING_RESOURCES, true);
	fileMenu->Enable(ID_FSAVE, true);
	themeMenu->Enable(ID_THEME_APPLY, true);
	viewMenu->Enable(ID_RESOURCEDLG, true);


	this->SetTitle(wxString("msstyleEditor - ") + wxString::FromUTF8(currentStyle->GetPath().c_str()));
}

void MainWindow::CloseStyle()
{
	if (currentStyle != nullptr)
	{
		try {
			themeManager.Rollback();
			themeMenu->SetLabel(ID_THEME_APPLY, wxT(TEXT_PLAY));
		}
		catch (...)
		{
		}

		// remove everything that could still point to the style data
		propView->Clear();
		imageView->RemoveImage();
		classView->Freeze();
		classView->DeleteAllItems();
		classView->Thaw();

		delete currentStyle;
		currentStyle = nullptr;
	}
}


void MainWindow::FillClassView()
{
	classView->Freeze();
	classView->DeleteAllItems();
	wxTreeItemId rootNode = classView->AddRoot(wxT("[StyleName]"));

	// Add classes
	for (auto& cls : *currentStyle)
	{
		wxTreeItemId classNode = classView->AppendItem(rootNode, cls.second.className, -1, -1, static_cast<wxTreeItemData*>(new ClassTreeItemData(&cls.second)));

		// Add parts
		for (auto& part : cls.second)
		{
			wxTreeItemId partNode = classView->AppendItem(classNode, part.second.partName, -1, -1, static_cast<wxTreeItemData*>(new PartTreeItemData(&part.second)));

			// Add images
			for (auto& state : part.second)
			{
				// Add properties
				for (auto& prop : state.second)
				{
					// Add images
					if (prop->header.typeID == IDENTIFIER::FILENAME ||
						prop->header.typeID == IDENTIFIER::FILENAME_LITE ||
						prop->header.typeID == IDENTIFIER::DISKSTREAM)
					{
						const char* propName = prop->LookupName(); // propnames have to be looked up, but thats fast
						classView->AppendItem(partNode, propName, -1, -1, static_cast<wxTreeItemData*>(new PropTreeItemData(prop)));
					}
				}
			}
		}

	}

	classView->SortChildren(rootNode);
	classView->Thaw();
}

void MainWindow::FillPropertyView(StylePart& part)
{
	propView->Clear();
	for (auto& state : part)
	{
		wxPropertyCategoryToolbar* category = new wxPropertyCategoryToolbar(propView->GetPanel(), state.second.stateName);
		category->SetClientData(&state);
		for (auto& prop : state.second)
		{
			category->AppendChild(GetWXPropertyFromMsStyleProperty(*currentStyle, *prop));
		}
		propView->Append(category);
	}
}


void MainWindow::ShowImageFromResource(const StyleProperty* prop)
{
	StyleResource res = currentStyle->GetResourceFromProperty(*prop);
	if (res.GetData() != nullptr && res.GetSize() != 0)
	{
		selectedImage = res;
		wxMemoryInputStream stream(selectedImage.GetData(), selectedImage.GetSize());
		wxImage img(stream, wxBITMAP_TYPE_PNG);
		imageView->SetImage(img);
	}
}

void MainWindow::ShowImageFromFile(wxString& imgPath)
{
	wxFileInputStream stream(imgPath);
	if (stream.IsOk())
	{
		wxImage img(stream, wxBITMAP_TYPE_PNG);
		imageView->SetImage(img);
	}
	else
	{
		wxMessageBox("Replacement image '" + imgPath.ToStdString() + "' is not accessible or missing!", "Error loading image!", wxICON_ERROR, this);
	}
}


MainWindow::~MainWindow()
{
	propView->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(MainWindow::OnPropertyGridChanging), NULL, this);
	if (currentStyle != nullptr)
	{
		delete currentStyle;
		currentStyle = nullptr;
	}
}