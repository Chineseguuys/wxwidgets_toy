#ifndef __SIMPLEVIRTUALLISTCONTROL__
#define __SIMPLEVIRTUALLISTCONTROL__

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "itemdata.h"

#include <vector>
#include <numeric>



class SimpleVirtualListControl : public wxListCtrl
{
private:
    bool sortAscending = true;
    std::vector<ItemData> items;
    std::vector<long> orderedIndices;

public:
    SimpleVirtualListControl(wxWindow *parent, const wxWindowID id, const wxPoint &pos, const wxSize &size);
    virtual wxString OnGetItemText(long index, long column) const wxOVERRIDE;
    void RefreshAfterUpdate();
    void setItems(std::vector<ItemData> itemsToSet);

private:
    void sortByColumn(int column);
    long getFirstSelectedIndex();
    long findIndexOfDataIndex(long dataIndex);
};



#endif
