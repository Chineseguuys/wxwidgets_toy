#ifndef _MYFRAME_H_
#define _MYFRAME_H_

#include <wx/wx.h>
#include <random>
#include "drawingcanvas.h"

class MyFrame: public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& point, const wxSize& size);

private:
    // 两个按钮的事件相应，一个是添加一个绘制对象, 另一个是移除最顶端的绘制对象
    void OnAddButtonClick(wxCommandEvent& evt);
    void onRemoveButtonClick(wxCommandEvent& evt);

    void onRectAdded(wxCommandEvent& evt);
    void onRectRemoved(wxCommandEvent& evt);

    // 两个按钮放在一个 panel 当中
    wxPanel* createButtonPanel(wxWindow* parent);

private:
    DrawingCanvas* mCanvas;

    // 获取当前的画布当中包含的对象的个数
    int rectCount = 0;
    // 随机数发生器
    std::mt19937 randomGen;
};

#endif /* _MYFRAME_H_ */