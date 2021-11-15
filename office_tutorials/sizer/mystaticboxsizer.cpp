#include "mystaticboxsizer.h"

MyStaticBoxSizer::MyStaticBoxSizer(wxWindow *parent, wxWindowID id, const wxString &title)
    : wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{
    wxBoxSizer* topLevel = new wxBoxSizer(wxVERTICAL);
    // Create static box and static box sizer
    wxStaticBox* staticBox = new wxStaticBox(this,
        wxID_ANY, wxT("General settings"));
    wxStaticBoxSizer *staticSizer = new wxStaticBoxSizer(staticBox, wxVERTICAL);
    topLevel->Add(staticSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    // Create a check box inside the static box sizer
    wxCheckBox *checkBox =
        new wxCheckBox(this, ID_CHECKBOX, wxT("& Show splash screen"),
                       wxDefaultPosition, wxDefaultSize);
    staticSizer->Add(checkBox, 0, wxALIGN_LEFT | wxALL, 5);
    SetSizer(topLevel);
    topLevel->Fit(this);
    topLevel->SetSizeHints(this);
}