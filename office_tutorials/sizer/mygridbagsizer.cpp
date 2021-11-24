#include "mygridbagsizer.h"

MyGridBagSizer::MyGridBagSizer(wxWindow *parent, wxWindowID id, const wxString &title)
    : wxDialog(parent, id, title)
{
    wxGridBagSizer *gridBagSizer = new wxGridBagSizer();
    SetSizer(gridBagSizer);

    wxButton *button1 = new wxButton(this, wxID_ANY, wxT("One(0,0)"));
    gridBagSizer->Add(button1, wxGBPosition(0, 0), wxGBSpan(1, 2), wxEXPAND);

    wxButton *button2 = new wxButton(this, wxID_ANY, wxT("Two (1, 2)"));
    gridBagSizer->Add(button2, wxGBPosition(1, 2), wxGBSpan(1, 2), wxEXPAND);

    wxButton *button3 = new wxButton(this, wxID_ANY, wxT("Three (3, 0)"));
    gridBagSizer->Add(button3, wxGBPosition(3, 0));

    wxButton *button4 = new wxButton(this, wxID_ANY, wxT("Three (3, 3)"));
    gridBagSizer->Add(button4, wxGBPosition(3, 3));

    //gridBagSizer->AddGrowableRow(0);
    //gridBagSizer->AddGrowableRow(1);
    //gridBagSizer->AddGrowableCol(2);

    gridBagSizer->Fit(this);
    gridBagSizer->SetSizeHints(this);
}