#include <wx/wx.h>
#include <wx/listctrl.h>
#include "itemdata.h"
#include "simplevirtuallistcontrol.h"


#ifndef __MYFRAME__
#define __MYFRAME__

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    SimpleVirtualListControl *virtualListView;
    wxListCtrl *plainListView;

    wxButton *switchButton;

    std::vector<ItemData> readItemsFromCsv();
    std::vector<ItemData> items;

    void populateVirtualListView();
    void populatePlainListView();
    void setupLayout();
    void addPlainList();
    void addVirtualList();

    bool useVirtual;
};

#endif
