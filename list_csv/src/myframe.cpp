#include "myframe.h"
#include <fstream>

#ifndef CSV_DIR
#define CSV_DIR "./data/"
#endif

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size),
    useVirtual(true),
    virtualListView(nullptr),
    plainListView(nullptr),
    switchButton(nullptr) {
    this->items = readItemsFromCsv();
    this->setupLayout();
}

std::vector<ItemData> MyFrame::readItemsFromCsv() {
    /**
     * 从文件读取所有数据
     */
    std::ifstream the_stream{std::string(CSV_DIR) + "apple_1d.csv", std::ios::in};

    the_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<ItemData> items;

    while (the_stream) {
        /**
         * 一次读取一行的数据，存储在 数据结构 ItemData
         */
        auto item = ItemData::fromCsvLine(the_stream);
        if (!item.date.empty()) {
            items.push_back(item);
        }
    }

    return items;
}

void MyFrame::populateVirtualListView() {
    virtualListView->setItems(items);
    virtualListView->RefreshAfterUpdate();
}

void MyFrame::populatePlainListView() {
    for (int i = 0; i < items.size(); i++) {
        const auto &item = items[i];
        int         insertionPoint = plainListView->GetItemCount();

        plainListView->InsertItem(insertionPoint, item.date);
        plainListView->SetItem(insertionPoint, 1, wxString::Format("%.2f", item.low));
        plainListView->SetItem(insertionPoint, 2, wxString::Format("%.2f", item.high));
        plainListView->SetItem(insertionPoint, 3, wxString::Format("%.2f", item.open));
        plainListView->SetItem(insertionPoint, 4, wxString::Format("%.2f", item.close));
        plainListView->SetItem(insertionPoint, 5, wxString::Format("%.0f", item.volume));
        plainListView->SetItem(insertionPoint, 6, wxString::Format("%d", item.ivr));
    }
}

void MyFrame::setupLayout() {
    std::string buttonLabel = "Re-create as a plain ListView";

    if (switchButton != nullptr) {
        switchButton->Destroy();
        switchButton = nullptr;
    }
    if (useVirtual) {
        if (plainListView != nullptr) {
            plainListView->Destroy();
            plainListView = nullptr;
        }
        addVirtualList();

        wxStopWatch sw;
        populateVirtualListView();
        std::cout << "Populating virtual list view took " << sw.Time() << "ms." << std::endl;
    } else {
        if (virtualListView != nullptr) {
            virtualListView->Destroy();
            virtualListView = nullptr;
        }
        buttonLabel = "Re-create as a virtual ListView";
        addPlainList();

        wxStopWatch sw;
        populatePlainListView();
        std::cout << "Populating plain list view took " << sw.Time() << "ms." << std::endl;
    }

    switchButton = new wxButton(this, wxID_ANY, buttonLabel);
    switchButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent &e) {
        this->useVirtual = !this->useVirtual;
        setupLayout();
    });

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(useVirtual ? virtualListView : plainListView, 1, wxALL | wxEXPAND, 0);
    sizer->Add(switchButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);

    this->SetSizer(sizer);
    this->Layout();
}

void MyFrame::addPlainList() {
    plainListView = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(800, 500), wxLC_REPORT);

    plainListView->AppendColumn("Date");
    plainListView->AppendColumn("Low");
    plainListView->AppendColumn("High");
    plainListView->AppendColumn("Open");
    plainListView->AppendColumn("Close");
    plainListView->AppendColumn("Volume");
    plainListView->AppendColumn("IVR");

    plainListView->SetColumnWidth(0, 180);
    plainListView->SetColumnWidth(5, 100);
}

void MyFrame::addVirtualList() {
    virtualListView = new SimpleVirtualListControl(this, wxID_ANY, wxDefaultPosition, wxSize(800, 500));
}