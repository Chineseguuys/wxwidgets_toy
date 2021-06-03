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

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(basicListView, 1, wxALL | wxEXPAND, 0);
    panel->SetSizerAndFit(sizer);

    this->populateListView();
}


void MyFrame::populateListView()
{
    this->addSingleItem(123, "Some Item", "This is a item");
    this->addSingleItem(456, "Other Item", "This is a different item");
    this->addSingleItem(789, "Another Item", "This is a most different item");
}

void MyFrame::addSingleItem(int id, const std::string& name, const std::string& destription)
{
    int index = this->basicListView->GetItemCount();

    this->basicListView->InsertItem(index, std::to_string(id));
    this->basicListView->SetItem(index, 1, name);
    this->basicListView->SetItem(index, 2, destription);

    this->basicListView->SetItemData(index, id);
}

void MyFrame::SortById(wxCommandEvent& e)
{
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
    this->sortDirection = -this->sortDirection;
}