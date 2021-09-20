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
    /**
     * 这个存储 csv 文件当中的所有的数据
    */
    std::vector<ItemData> items;
    bool useVirtual;

    std::vector<ItemData> readItemsFromCsv();

    void populateVirtualListView();
    void populatePlainListView();
    void setupLayout();
    void addPlainList();
    void addVirtualList();
};

#endif
