#include "mygridsizer.h"

MyGridSizer::MyGridSizer(wxWindow *parent, wxWindowID id, const wxString &title)
    : wxDialog(parent, id, title) {
    // 创建顶层的 sizer
    wxGridSizer *gridSizer = new wxGridSizer(2, 3, 0, 0);
    SetSizer(gridSizer);

    wxButton *button1 = new wxButton(this, ID_BUTTON1, wxT("One"));
    gridSizer->Add(button1, 0,
                   wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL,
                   5);
    
    wxButton *button2 = new wxButton(this, ID_BUTTON2, wxT("Two(the second button)"));
    gridSizer->Add(button2, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
                   5);
    
    wxButton *button3 = new wxButton(this, ID_BUTTON3, wxT("Three"));
    gridSizer->Add(button3, 0,
                   wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL,
                   5);
    
    wxButton *button4 = new wxButton(this, ID_BUTTON4, wxT("Four"));
    gridSizer->Add(button4, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
                   5);
    
    wxButton *button5 = new wxButton(this, ID_BUTTON5, wxT("Five"));
    gridSizer->Add(button5, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
                   5);
    
    wxButton *button6 = new wxButton(this, ID_BUTTON6, wxT("Six"));
    gridSizer->Add(button6, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
                   5);

    gridSizer->Fit(this);
    gridSizer->SetSizeHints(this);
}