#include <wx/wx.h>
#include <wx/listctrl.h>

#ifndef __MYFRAME__
#define __MYFRAME__

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    wxListView *basicListView;
    int sortDirection = 1;

    void populateListView();
    void addSingleItem(int id, const std::string& name, const std::string& destription);
    void SortById(wxCommandEvent& e);
};

#endif
