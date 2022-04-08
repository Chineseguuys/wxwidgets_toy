#ifndef _FRAME_H_
#define _FRAME_H_

#include <wx/wx.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/tglbtn.h>
#include <vector>
#include <set>
#include <memory>
#include <map>
#include "adbpiple.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    enum {
        DEVICE_LIST_VIEW_ID = 7001,
        DEVICE_PACKAGE_LIST_VIEW_ID,
        DEVICE_FLUSH_BOTTON_ID,
        DEVICE_MONITOR_DEVICE_BUTTON_ID
    };

private:
    std::shared_ptr<wxImageList> mImageList;
    std::vector<wxPanel *>       mPanelArray;

    wxListCtrl     *mDeviceListVew;
    wxButton       *mDeviceFlushButton;
    wxToggleButton *mDeviceMonitorButton;
    wxListCtrl     *mDevicePackagesListView;

    ADBPiple::device_list                        mDevices;
    std::map<int, ADBPiple::device_list::Device> mID2DeviceMap;

    ADBPiple::device_list::Device mDevice_Selected; // 记录当前被选中的设备

    FILE                     *mMonitorDescriptor; // 控制权不在这里，可能会失效，及时设置为 null
    std::shared_ptr<ADBPiple> mADBPiple;          // 长期有效

    std::mutex                   mMutex;
    bool                         mThreadDone;      // 结束线程
    std::shared_ptr<std::thread> mThread;          // 线程
    std::set<std::string>        mMonitorPackages; // 用来存储所有的监控中的 packages

private:
    void onDeviceFlush(wxCommandEvent &evt);
    void onDeviceListSelect(wxListEvent &evt);
    void onDeviceMonitor(wxCommandEvent &evt);
    void onMonitorThreadEntry();

private:
    DECLARE_EVENT_TABLE()
};
#endif /* _FRAME_H_ */