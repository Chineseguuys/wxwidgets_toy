#include "cEditorFrame.h"

wxBEGIN_EVENT_TABLE(cEditorFrame, wxMDIChildFrame)
    // EVT_SLIDER(20001, cEditorFrame::OnZoomChange)
wxEND_EVENT_TABLE()

// 此处不知道为何，GTK 在绘制子窗口的时候，会出错
cEditorFrame::cEditorFrame(wxMDIParentFrame *parent, wxString sName) :
    wxMDIChildFrame(parent, wxID_ANY, sName, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE) {
    this->m_Canvas = new cCanvas(this);

    //this->m_StatusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY, "");
    //wxCHECK2(this->m_StatusBar != nullptr, return);
    //this->m_ZoomSlider = new wxSlider(m_StatusBar, 20001, 8, 1, 32);
}

cEditorFrame::~cEditorFrame() {
}

void cEditorFrame::OnZoomChange(wxCommandEvent &evt) {
    this->m_StatusBar->SetStatusText(wxString("Zoom: ") << m_ZoomSlider->GetValue(), 1);
    this->m_Canvas->SetPixelSize(this->m_ZoomSlider->GetValue());
    evt.Skip();
}