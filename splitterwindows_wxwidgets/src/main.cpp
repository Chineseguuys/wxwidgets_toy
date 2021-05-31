#include <wx/wx.h>
#include <wx/splitter.h>

#define _SPLITTER_SENCE_3_

class MyApp : public wxApp {
public:
	virtual bool OnInit();
};


wxIMPLEMENT_APP(MyApp); // 在这里构建 main() 

class MyFrame : public wxFrame {
public:
	MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};


bool MyApp::OnInit() {
	MyFrame *frame = new MyFrame("Layout Example", wxDefaultPosition, wxDefaultSize);
	frame->Show(true);
	return  true;
}

#ifdef _SPLITTER_SENCE_1_

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size) 
{
	wxSplitterWindow *splitter = new wxSplitterWindow(this);

	wxPanel *left = new wxPanel(splitter);
	wxPanel *right = new wxPanel(splitter);

	left->SetBackgroundColour(wxColour(200, 100, 100));
	right->SetBackgroundColour(wxColour(100, 200, 100));

	splitter->SplitVertically(left, right);
}

#endif

#ifdef _SPLITTER_SENCE_2_

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size) 
{
	wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, 
			wxDefaultPosition, wxDefaultSize, 
			wxSP_LIVE_UPDATE | wxSP_BORDER);

	wxPanel *left = new wxPanel(splitter);
	wxPanel *right = new wxPanel(splitter);

	left->SetBackgroundColour(wxColour(200, 100, 100));
	right->SetBackgroundColour(wxColour(100, 200, 100));

	splitter->SetMinimumPaneSize(200); //规定了窗口的最小的宽度，滑动条不能让其中的窗口宽度小于这个数值

	splitter->SplitVertically(left, right);
}

#endif

#ifdef _SPLITTER_SENCE_3_

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size) 
{
	wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, 
			wxDefaultPosition, wxDefaultSize, 
			wxSP_LIVE_UPDATE | wxSP_BORDER
	);

	wxSplitterWindow *right_splitter = new wxSplitterWindow(splitter, wxID_ANY,
			wxDefaultPosition, wxDefaultSize,
			wxSP_LIVE_UPDATE | wxSP_BORDER
	);

	wxPanel *left = new wxPanel(splitter);
	wxPanel *right = new wxPanel(right_splitter);
	wxPanel *bottom = new wxPanel(right_splitter);


	left->SetBackgroundColour(wxColour(200, 100, 100));
	right->SetBackgroundColour(wxColour(100, 200, 100));
	bottom->SetBackgroundColour(wxColour(100, 100, 200));

	splitter->SetMinimumPaneSize(200); //规定了窗口的最小的宽度，滑动条不能让其中的窗口宽度小于这个数值
	right_splitter->SetMinimumPaneSize(100);

	splitter->SplitVertically(left, right_splitter);
	right_splitter->SplitHorizontally(right, bottom);
}

#endif