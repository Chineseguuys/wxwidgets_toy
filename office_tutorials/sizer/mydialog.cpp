#include "mydialog.h"

MyDialog::MyDialog(wxWindow *parent, wxWindowID id, const wxString &title)
    : wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);

    topSizer->Add(new wxTextCtrl(this, wxID_ANY, "My text.", wxDefaultPosition,
                                 wxSize(100, 60), wxTE_MULTILINE),
                1, wxEXPAND | wxALL, 10);
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL, 10);
    buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL, 10);

    topSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    SetSizer(topSizer);
    topSizer->Fit(this);
    topSizer->SetSizeHints(this);
}