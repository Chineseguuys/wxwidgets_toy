#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Grid layers", wxPoint(30, 30), wxSize(800, 600)) {
    btn = new wxButton*[nFieldWidth * nFieldHeight];
    wxGridSizer *grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

    for (int x = 0; x < nFieldWidth; ++x) {
        for (int y = 0; y < nFieldHeight; ++y)  {
            btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
            grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

            btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, 
                            &cMain::OnButtonClicked, 
                            this);
        }
    }

    this->SetSizer(grid);
    grid->Layout();
}

cMain::~cMain() {
    delete[] btn;
}

void cMain::OnButtonClicked(wxCommandEvent &evt) {
    int x = (evt.GetId() - 10000) % nFieldWidth;
    int y = (evt.GetId() - 10000) / nFieldHeight;
    printf("(%d, %d)\n", x, y);
    evt.Skip();
}