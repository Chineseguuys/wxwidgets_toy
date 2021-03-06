#ifndef __C_CANVAS_H__
#define __C_CANVAS_H__

#include <wx/wx.h>
#include <wx/vscroll.h>

class cCanvas : public wxHVScrolledWindow {
public:
    cCanvas(wxWindow *parent);
    ~cCanvas();

private:
    int m_nPixelSize = 8;   
    // 软件的界面可以用矩阵方格来进行分割，而这个变量表示每一个方格所占用的像素的数量
public:
    void SetPixelSize(int n);

private:
    // 这两个方法是继承 wxHVScrolledWindow 必须要实现的两个方法
    virtual wxCoord OnGetRowHeight(size_t row) const;
    virtual wxCoord OnGetColumnWidth(size_t col) const;

    void OnDraw(wxDC &dc);
    void OnPaint(wxPaintEvent &evt);

    wxDECLARE_EVENT_TABLE();
};

#endif