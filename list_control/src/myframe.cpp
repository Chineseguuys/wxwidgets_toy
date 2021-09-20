#include "myframe.h"


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxPanel *panel = new wxPanel(this);
    basicListView = new wxListView(panel);
    basicListView->AppendColumn("ID");
    basicListView->AppendColumn("Name");
    basicListView->AppendColumn("Description");

    basicListView->SetColumnWidth(0, 80);
    basicListView->SetColumnWidth(1, 120);
    basicListView->SetColumnWidth(2, 600);

    /**
     * 使用一个 button 来查看这个排序的效果
    */
    auto button = new wxButton(panel, wxID_ANY, "Sort by ID");
    /**
     * Bind() 绑定事件更加的灵活
    */
    button->Bind(wxEVT_BUTTON, &MyFrame::SortById, this);
    
    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(basicListView, 1, wxALL | wxEXPAND, 0);
    sizer->Add(button, 0, wxALIGN_LEFT | wxTOP | wxBOTTOM | wxLEFT, 5);
    panel->SetSizerAndFit(sizer);

    this->populateListView();
}


void MyFrame::populateListView()
{
    this->addSingleItem(123, "Some Item", "This is a item");
    this->addSingleItem(456, "Other Item", "This is a different item");
    this->addSingleItem(789, "Another Item", "This is a most different item");
    this->addSingleItem(1213, "AAnother Item", "This is a most most different item");
}

void MyFrame::addSingleItem(int id, const std::string& name, const std::string& destription)
{
    int index = this->basicListView->GetItemCount();

    this->basicListView->InsertItem(index, std::to_string(id));
    this->basicListView->SetItem(index, 1, name);
    this->basicListView->SetItem(index, 2, destription);

    /**
     * 这里设置的值是每一行的数据的一个属性值，这个属性值非常的重要
     * list 在进行排序的时候依赖的就是这个属性值
    */
    this->basicListView->SetItemData(index, id);
}

void MyFrame::SortById(wxCommandEvent& e)
{
    /**
     * 默认的排序算法会根据 SetItemData() 中设置的值的大小来进行排序。
     * 下面的这个函数中第一个参数是一个函数句柄，这里直接使用 lambda 表达式。
     * item1 和 item2 就是每一个 item 存储的值（即在 this->basicListView->SetItemData(index, id); 当中设置的 id 值）
     * 
     * typedef ssize_t wxIntPtr
     * Signed and unsigned integral types big enough to contain all of long, size_t and void*.
     * (The mapping is more complex than a simple typedef and is not shown here).
    */
    this->basicListView->SortItems(
        [](wxIntPtr item1, wxIntPtr item2, wxIntPtr direction) {
            if (item1 == item2) 
                return 0;
            else if (item1 < item2) 
                return -static_cast<int>(direction);
            else 
                return static_cast<int>(direction);
        },
        this->sortDirection
    );

    this->basicListView->Refresh();
    /**
     * sortDirection 控制排序的方向，从大到小或者从小到达。
     * 上一次排序是从大到小，那么这一次就要从小到达
    */
    this->sortDirection = -this->sortDirection;
}