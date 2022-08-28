#ifndef _DRAWING_CANVAS_H_
#define _DRAWING_CANVAS_H_

#include <wx/wx.h>
#include "graphicobject.h"
#include <list>

// 定义两个事件类型
wxDECLARE_EVENT(CANVAS_RECT_ADDED, wxCommandEvent);
wxDECLARE_EVENT(CANVAS_RECT_REMOVED, wxCommandEvent);

class DrawingCanvas : public wxWindow {
public:
    DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    virtual ~DrawingCanvas() {}

    void addRect(int width, int height, int centerX, int centerY, double angle, wxColor color, const std::string& text);

    // 移除当前画布当中，绘制在最上层的对象
    void removeTopRect();

    //  获取当前的画布上绘制的对象的总个数
    int getObjectCount();

private:
    void OnPaint(wxPaintEvent& evt);

    // 鼠标事件处理
    void onMouseDown(wxMouseEvent& evt);
    void onMouseUp(wxMouseEvent& evt);
    void onMouseMove(wxMouseEvent& evt);
    void onMouseLeave(wxMouseEvent& evt);

    void finishDrag();
    void finishRotation();

    // 对象被添加和对象被删除的两个事件处理函数
    void sendRectAddedEvent(const wxString& rectTitle);
    void sendRectRemovedEvent(const wxString& rectTitle);

private:
    std::list<GraphicObject>    objectList;

    // 当前正在被拖拽的对象
    GraphicObject*              draggedObj;
    // 当前的对象是否应该被旋转
    bool                        shouldBeRotated;

    // 在松开鼠标之后，对象最终被拖曳到的位置
    wxPoint2DDouble             lastDragOrigin;
};

#endif /* _DRAWING_CANVAS_H_ */