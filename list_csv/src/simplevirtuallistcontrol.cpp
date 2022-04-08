#include "simplevirtuallistcontrol.h"
#include <wx/listctrl.h>
#include <algorithm>

SimpleVirtualListControl::SimpleVirtualListControl(wxWindow *parent, const wxWindowID id, const wxPoint &pos, const wxSize &size) :
    wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL) {
    this->AppendColumn("Date");
    this->AppendColumn("Low");
    this->AppendColumn("High");
    this->AppendColumn("Open");
    this->AppendColumn("Close");
    this->AppendColumn("Volume");
    this->AppendColumn("IVR");

    this->SetColumnWidth(0, 180);
    this->SetColumnWidth(5, 100);

    this->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent &evt) {
        auto selectedListIndex = getFirstSelectedIndex();
        std::cout << "GetNextItem() = " << selectedListIndex << std::endl;
        long selectedDataIndex;

        if (selectedListIndex != -1) {
            selectedDataIndex = this->orderedIndices[selectedListIndex];

            // deselecting old index
            this->SetItemState(selectedListIndex, 0, wxLIST_STATE_SELECTED);
        }

        this->sortByColumn(evt.GetColumn());
        this->RefreshAfterUpdate();

        if (selectedListIndex != -1) {
            auto listIndexToSelect = findIndexOfDataIndex(selectedDataIndex);
            this->SetItemState(listIndexToSelect, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
            this->EnsureVisible(listIndexToSelect);
        }

        this->sortAscending = !this->sortAscending;
    });
}

wxString SimpleVirtualListControl::OnGetItemText(long index, long column) const {
    ItemData item = items[orderedIndices[index]];

    switch (column) {
    case 0:
        return item.date;
    case 1:
        return wxString::Format("%.2f", item.low);
    case 2:
        return wxString::Format("%.2f", item.high);
    case 3:
        return wxString::Format("%.2f", item.open);
    case 4:
        return wxString::Format("%.2f", item.close);
    case 5:
        return wxString::Format("%.0f", item.volume);
    case 6:
        return wxString::Format("%d", item.ivr);
    default:
        return "";
    }
}

void SimpleVirtualListControl::RefreshAfterUpdate() {
    this->SetItemCount(orderedIndices.size());
    this->Refresh();
}

void SimpleVirtualListControl::setItems(std::vector<ItemData> itemsToSet) {
    this->items = itemsToSet;

    this->orderedIndices = std::vector<long>(items.size());
    /**
     * 将数组的中 begin() 开始的位置到 end()为止的位置用一组数据进行填充。第三个参数表示填充的起始值
     * 值的大小依次的增大。下面就是从 0 开始填充。
     */
    std::iota(orderedIndices.begin(), orderedIndices.end(), 0);
}

void SimpleVirtualListControl::sortByColumn(int column) {
    // C++14 generic lambda
    static auto genericCompare = [](auto i1, auto i2, bool ascending) {
        return ascending ? i1 < i2 : i1 > i2;
    };

    bool ascending = this->sortAscending;

    std::sort(orderedIndices.begin(), orderedIndices.end(), [this, column, ascending](long index1, long index2) {
        auto i1 = this->items[index1];
        auto i2 = this->items[index2];

        switch (column) {
        case 0:
            return genericCompare(i1.date, i2.date, ascending);
        case 1:
            return genericCompare(i1.low, i2.low, ascending);
        case 2:
            return genericCompare(i1.high, i2.high, ascending);
        case 3:
            return genericCompare(i1.open, i2.open, ascending);
        case 4:
            return genericCompare(i1.close, i2.close, ascending);
        case 5:
            return genericCompare(i1.volume, i2.volume, ascending);
        case 6:
            return genericCompare(i1.ivr, i2.ivr, ascending);
        default:
            return false;
        }
    });
}

long SimpleVirtualListControl::getFirstSelectedIndex() {
    return GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

long SimpleVirtualListControl::findIndexOfDataIndex(long dataIndex) {
    return std::find(orderedIndices.begin(), orderedIndices.end(), dataIndex) - orderedIndices.begin();
}