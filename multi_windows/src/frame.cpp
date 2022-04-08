#include <wx/wx.h>
#include <wx/notebook.h>
#include "frame.h"
#include "android.xpm"
#include "binary-code.xpm"

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(MyFrame::DEVICE_FLUSH_BOTTON_ID, MyFrame::onDeviceFlush)
EVT_LIST_ITEM_SELECTED(MyFrame::DEVICE_LIST_VIEW_ID, MyFrame::onDeviceListSelect)
EVT_TOGGLEBUTTON(MyFrame::DEVICE_MONITOR_DEVICE_BUTTON_ID, MyFrame::onDeviceMonitor)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size) {
    wxNotebook *notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, size);

    this->mImageList.reset(new wxImageList(32, 32, true, 3));
    notebook->SetImageList(this->mImageList.get());
    this->mImageList->Add(wxIcon(a56847603c05465bc7b67168a6b4b4fcdj5qJWCqVbSMbfPQ));
    this->mImageList->Add(wxIcon(_daefd171c60499e9320caab891f50bcuk7q9LWx1hIEZ4pG));
    wxPanel *windows1 = new wxPanel(notebook, wxID_ANY);
    wxPanel *windows2 = new wxPanel(notebook, wxID_ANY);

    // 设置 Sizer ，分配布局
    wxPanel *windows1_top_left = new wxPanel(windows1, wxID_ANY);
    wxPanel *windows1_top_right = new wxPanel(windows1, wxID_ANY, wxDefaultPosition, wxSize(200, 100));

    wxBoxSizer *top_left_sizer = new wxBoxSizer(wxVERTICAL);          // 竖直方向
    wxBoxSizer *top_left_bottom_sizer = new wxBoxSizer(wxHORIZONTAL); // 水平方向

    this->mDeviceListVew = new wxListCtrl(windows1_top_left, DEVICE_LIST_VIEW_ID, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    this->mDevicePackagesListView = new wxListCtrl(windows1, DEVICE_PACKAGE_LIST_VIEW_ID, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    this->mDeviceFlushButton = new wxButton(windows1_top_left, DEVICE_FLUSH_BOTTON_ID, "flush");
    this->mDeviceMonitorButton = new wxToggleButton(windows1_top_left, DEVICE_MONITOR_DEVICE_BUTTON_ID, "unmonitored");

    top_left_sizer->Add(this->mDeviceListVew, 1, wxEXPAND | wxALL, 2);
    top_left_sizer->Add(top_left_bottom_sizer, 0, wxEXPAND | wxALL, 2);
    top_left_bottom_sizer->Add(this->mDeviceFlushButton, 0, wxALL, 2);
    top_left_bottom_sizer->Add(this->mDeviceMonitorButton, 0, wxALL, 2);

    this->mDeviceListVew->InsertColumn(0, "device");
    this->mDeviceListVew->InsertColumn(1, "state");
    this->mDeviceListVew->SetColumnWidth(0, 300);
    this->mDeviceListVew->SetColumnWidth(1, 300);
    this->mDevicePackagesListView->InsertColumn(0, "package");
    this->mDevicePackagesListView->InsertColumn(1, "full path");
    this->mDevicePackagesListView->SetColumnWidth(0, 300);
    this->mDevicePackagesListView->SetColumnWidth(1, 300);

    windows1_top_left->SetSizerAndFit(top_left_sizer);

    windows1_top_left->SetBackgroundColour(wxColour(200, 100, 100));
    windows1_top_right->SetBackgroundColour(wxColour(100, 200, 100));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL); // 垂直方向的 sizer
    // 组件加入到 sizer 当中的时候，按照从上到下的顺序进行排列
    wxBoxSizer *sizer_top = new wxBoxSizer(wxHORIZONTAL); // 水平方向的 sizer
    // 组件加入到 sizer 当中的时候，按照从左到右的顺序进行排列

    sizer_top->Add(windows1_top_left, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 4);
    sizer_top->Add(windows1_top_right, 1, wxEXPAND | wxRIGHT | wxTOP, 4);

    sizer->Add(sizer_top, 1, wxEXPAND);
    sizer->Add(this->mDevicePackagesListView, 1, wxEXPAND | wxLEFT | wxBOTTOM | wxRIGHT | wxTOP, 4);

    windows1->SetSizerAndFit(sizer);

    this->mPanelArray.push_back(windows1);
    this->mPanelArray.push_back(windows2);

    notebook->AddPage(windows1, wxT("拉取和安装apk"), true, 0);
    notebook->AddPage(windows2, wxT("进制转换"), false, 1);
}

void MyFrame::onDeviceFlush(wxCommandEvent &evt) {
    this->mDevices = ADBPiple::getAllDevices();
    this->mID2DeviceMap.clear();
    int device_num = this->mDevices.nDevices;
    this->mDeviceListVew->DeleteAllItems();
    for (int idx = 0; idx < device_num; ++idx) {
        const ADBPiple::device_list::Device &device = this->mDevices.mAllDevices[idx];
        this->mDeviceListVew->InsertItem(idx, "");
        this->mDeviceListVew->SetItem(idx, 0, device.mDeviceName);
        this->mDeviceListVew->SetItem(idx, 1, device.mDeviceState);
        this->mID2DeviceMap.insert(std::pair<int, ADBPiple::device_list::Device>(idx, device));
    }
}

// 点击列表中的一行，会触发该函数
void MyFrame::onDeviceListSelect(wxListEvent &evt) {
    long int    item_index = evt.GetIndex();
    std::string device_name_selected;

    log_info("selected item index is %ld", item_index);
    this->mDevice_Selected = this->mID2DeviceMap[item_index];
    log_info("device %s has been selected", this->mDevice_Selected.mDeviceName.c_str());
}

void MyFrame::onDeviceMonitor(wxCommandEvent &evt) {
    log_info("togger button");
    bool isChecked = evt.IsChecked();
    log_info("button is %s", isChecked ? "checked" : "not checked");
    if (isChecked) {
        // 开始进行 monitor adb -s device am monitor
        // 在子进程当中打开管道，frame 开启子线程进行读写，以及将结果送入 list 进行显示
        this->mADBPiple.reset(new ADBPiple(this->mDevice_Selected));
        if (this->mADBPiple->onMonitorDevices(&this->mMonitorDescriptor) != 0 || this->mMonitorDescriptor == nullptr) {
            log_error("create piple for monitor error");
            return;
        }
        log_info("open sub process for device monitor, read from fd[%d]", fileno(this->mMonitorDescriptor));
        // 打开线程 进行读写
        this->mThread.reset(new std::thread(&MyFrame::onMonitorThreadEntry, this));
    } else {
        // 结束监控 结束子进程和结束子线程
        log_info("stop and over the device monitor");
        this->mThreadDone = true;
        this->mThread->join();
        log_info("sub thread over");
        this->mADBPiple->onMonitorOver();
        log_info("close piple fd success");
    }
}

// 执行线程读数据
void MyFrame::onMonitorThreadEntry() {
    if (this->mMonitorDescriptor == nullptr) {
        log_error("Monitor file descriptor is null");
        return;
    }
    log_info("start device monitor");
    this->mMonitorPackages.clear();
    this->mDevicePackagesListView->DeleteAllItems();

    char *buffer = new char[128];
    this->mThreadDone = false;
    int index = 2;
    log_info("start while");
    while (!this->mThreadDone) {
        index = 2;
        if (fgets(buffer, 128 - 1, this->mMonitorDescriptor) != nullptr) {
            log_info("%s", buffer);
            const char *raw_buffer = buffer;
            int         str_len = strlen(raw_buffer);
            log_info("strlen[%d] with start %c%c", str_len, raw_buffer[0], raw_buffer[1]);
            if (str_len > 2 && raw_buffer[0] == '*' && raw_buffer[1] == '*') {
                while (raw_buffer[index] != ':') { ++index; }
                raw_buffer += (index + 1);
                std::string package = raw_buffer;
                log_info("get package: %s", package.c_str());
                if (this->mMonitorPackages.find(package) == this->mMonitorPackages.end()) {
                    this->mMonitorPackages.insert(package);
                    int insertPosition = this->mDevicePackagesListView->GetColumnCount();
                    this->mDevicePackagesListView->InsertItem(insertPosition, "");
                    this->mDevicePackagesListView->SetItem(insertPosition, 0, package);
                }
            }
        }
    } // 线程结束，退出线程函数就会自动退出线程
    if (buffer != nullptr) {
        delete[] buffer;
        log_info("delete[] buffer");
    }
    log_info("thread over");
}
