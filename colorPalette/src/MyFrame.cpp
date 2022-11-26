#include "MyFrame.h"


#define COLOR_Y_ID 6001
#define COLOR_U_ID 6002
#define COLOR_V_ID 6003

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
    : wxFrame(nullptr, wxID_ANY, title, pos, size), mY(0), mU(0), mV(0) {

    wxSizer* windowSizer = new wxBoxSizer(wxVERTICAL);
    wxSizer* yuvSizer = new wxBoxSizer(wxHORIZONTAL);

    wxPanel* yuvPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    this->mColorPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
    this->mColorPanel->SetBackgroundColour(wxColor(0, 0, 0));

    wxStaticText* yText = new wxStaticText(yuvPanel, wxID_ANY, "Y");
    wxStaticText* uText = new wxStaticText(yuvPanel, wxID_ANY, "U");
    wxStaticText* vText = new wxStaticText(yuvPanel, wxID_ANY, "V");

    this->mYValue = new wxTextCtrl(yuvPanel, COLOR_Y_ID);
    this->mUValue = new wxTextCtrl(yuvPanel, COLOR_U_ID);
    this->mVValue = new wxTextCtrl(yuvPanel, COLOR_V_ID);

    this->mYValue->Bind(wxEVT_TEXT, &MyFrame::onTextCtrlChanged, this);
    this->mUValue->Bind(wxEVT_TEXT, &MyFrame::onTextCtrlChanged, this);
    this->mVValue->Bind(wxEVT_TEXT, &MyFrame::onTextCtrlChanged, this);

    yuvSizer->Add(yText, 1, wxRIGHT, 0);
    yuvSizer->Add(this->mYValue, 1, wxALL);
    yuvSizer->Add(uText, 1, wxALL);
    yuvSizer->Add(this->mUValue, 1, wxALL);
    yuvSizer->Add(vText, 1, wxALL);
    yuvSizer->Add(this->mVValue, 1, wxALL);

    yuvPanel->SetSizer(yuvSizer);

    windowSizer->Add(yuvPanel, 0, wxBOTTOM | wxALIGN_CENTER, this->FromDIP(20));
    windowSizer->Add(this->mColorPanel, 0, wxALIGN_CENTER);

    this->SetSizerAndFit(windowSizer);
}


void MyFrame::onTextCtrlChanged(wxCommandEvent& evt) {
    int id = evt.GetId();
    std::string numStr;
    int stringLen = 0;

    switch (id)
    {
        case COLOR_Y_ID:
            numStr = this->mYValue->GetLineText(0).ToStdString();
            stringLen = this->mYValue->GetLineLength(0);
            this->setColorComponentValue(COLOR_COMPONENT::Y_COMPONENT, numStr, stringLen);
            break;
        case COLOR_U_ID:
            numStr = this->mUValue->GetLineText(0).ToStdString();
            stringLen = this->mUValue->GetLineLength(0);
            this->setColorComponentValue(COLOR_COMPONENT::U_COMPONENT, numStr, stringLen);
            break;
        case COLOR_V_ID:
            numStr = this->mVValue->GetLineText(0).ToStdString();
            stringLen = this->mVValue->GetLineLength(0);
            this->setColorComponentValue(COLOR_COMPONENT::V_COMPONENT, numStr, stringLen);
            break;
        default:
            break;
    }
}


void MyFrame::setColorComponentValue(COLOR_COMPONENT comp, const std::string& num, int len) {
    if (len <= 0 || len > 3) return;
    if (MyFrame::isDigital(num)) {
        int compValue = std::atoi(num.c_str());
        switch (comp)
        {
            case COLOR_COMPONENT::Y_COMPONENT :
                this->mY = (compValue >= 255 ? 255 : compValue);
                break;
            case COLOR_COMPONENT::U_COMPONENT :
                this->mU = (compValue >= 255 ? 255 : compValue);
                break;
            case COLOR_COMPONENT::V_COMPONENT :
                this->mV = (compValue >= 255 ? 255 : compValue);
                break;
            default:
                break;
        }

        // update panel color
        unsigned int rgbColor[3] = {0, 0, 0};
        MyFrame::yuv2rgb(this->mY, this->mU, this->mV, rgbColor);
        this->mColorPanel->SetBackgroundColour(wxColour(rgbColor[0], rgbColor[1], rgbColor[2]));
        printf("color [%u, %u, %u]\n", this->mY, this->mU, this->mV);
    }
}

bool MyFrame::isDigital(const std::string& numStr) {
    for (const char& ch : numStr) {
        if (ch > '9' || ch < '0') return false;
    }

    return true;
}

void MyFrame::yuv2rgb(unsigned int y, unsigned int cr, unsigned cb, unsigned int* rgb) {
    if (rgb == nullptr) return;

    rgb[0] = 1.402 * static_cast<double>(cr) + y; 
    rgb[2] = 1.772 * static_cast<double>(cb) + y;
    rgb[1] = static_cast<double>(y) - 0.713 * static_cast<double>(cr) - 0.344 * static_cast<double>(cb);

    return;
}