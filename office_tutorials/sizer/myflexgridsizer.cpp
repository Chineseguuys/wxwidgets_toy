#include "myflexgridsizer.h"

MyFlexGridSizer::MyFlexGridSizer(wxWindow *parent, wxWindowID id, const wxString &title)
    : wxDialog(parent, id, title)
{
    wxFlexGridSizer *flexgridsizer = new wxFlexGridSizer(2, 3, 0, 0);
    this->SetSizer(flexgridsizer);

    flexgridsizer->AddGrowableCol(0);

    wxButton *button1 = new wxButton(this, FLEX_ID_BUTTON1, wxT("One"));
    flexgridsizer->Add(
        button1, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
        5);

    wxButton *button2 = new wxButton(this, FLEX_ID_BUTTON2, wxT("Two"));
    flexgridsizer->Add(
        button2, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
        5);

    wxButton *button3 = new wxButton(this, FLEX_ID_BUTTON3, wxT("Three(Longer then other buttons)"));
    flexgridsizer->Add(
        button3, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
        5);
    
    wxButton *button4 = new wxButton(this, FLEX_ID_BUTTON4, wxT("Four(Longer then other buttons)"));
    flexgridsizer->Add(
        button4, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
        5);
    
    wxButton *button5 = new wxButton(this, FLEX_ID_BUTTON5, wxT("Five"));
    flexgridsizer->Add(
        button5, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
        5);
    
    wxButton *button6 = new wxButton(this, FLEX_ID_BUTTON6, wxT("Six"));
    flexgridsizer->Add(
        button6, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
        5);

    flexgridsizer->Fit(this);
    flexgridsizer->SetSizeHints(this);
}