#include "drawingcanvas.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#define COMBINATION2
#define REDUCE_FACTORY 100.0f


// define of self defined commend event
wxDEFINE_EVENT(CANVAS_RECT_ADDED, wxCommandEvent);
wxDEFINE_EVENT(CANVAS_RECT_REMOVED, wxCommandEvent);

// public
DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size) 
    : wxWindow(parent, id, pos, size)
{
    // 如果要使用 wxAutoBufferedPaintDC, 那么就需要设置下面的属性
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    // 绑定鼠标操作的事件到其对应的处理函数上
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::onMouseDown, this);
    this->Bind(wxEVT_MOTION,    &DrawingCanvas::onMouseMove, this);
    this->Bind(wxEVT_LEFT_UP,   &DrawingCanvas::onMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::onMouseLeave, this);

    // 我们在这里添加一些绘制的长方形
    // 颜色的 alpha 通道默认值是 255, 即颜色是完全不透明的，后绘制的图像会覆盖前面绘制的图形
    this->addRect(this->FromDIP(100), this->FromDIP(80), this->FromDIP(210), this->FromDIP(140), 0, *wxRED, "Rect #1");
    this->addRect(this->FromDIP(130), this->FromDIP(110), this->FromDIP(280), this->FromDIP(210), M_PI / 3.0, *wxBLUE, "Rect #2");
    this->addRect(this->FromDIP(110), this->FromDIP(110), this->FromDIP(300), this->FromDIP(120), M_PI / 4.0, wxColor(255, 0, 255, 255), "Rect #3");

    // 初始化
    this->draggedObj = nullptr;
    this->shouldBeRotated = false;
}


/**
 * @brief 添加需要绘制的长方形
 * 
 * @param width     长方形的宽度
 * @param height    长方形的高度
 * @param centerX   长方形中心点在窗口的显示位置 x 坐标
 * @param centerY   长方形中心点在窗口的显示位置 y 坐标
 * @param angle     长方形需要旋转的角度
 * @param color     长方形绘制的颜色
 * @param text      长方形中显示的字符串
 */
void DrawingCanvas::addRect(int width, int height, int centerX, int centerY, double angle, wxColor color, const std::string& text) {
    GraphicObject obj {
        // 绘制的所有的长方体在做所有的变换之前，均是以 windows 的原点作为它们的本地坐标
        // 即所有的图像先绘制在原点的位置，之后在做放缩，旋转，移动等操作
        .rect = {-width / 2.0, -height / 2.0, static_cast<double>(width), static_cast<double>(height)},
        .color = color,
        .text = text,
        .transform = {} // 初始化为一个单位矩阵
    };

    obj.transform.Translate(static_cast<double>(centerX), static_cast<double>(centerY));
    obj.transform.Rotate(angle);

    this->objectList.push_back(obj);
    this->sendRectAddedEvent(text);
    this->Refresh();
}

/**
 * @brief 返回当前的画布中绘制的对象的个数
 * 
 * @return int 画布中包含的对象的个数
 */
int DrawingCanvas::getObjectCount() {
    return this->objectList.size();
}

/**
 * @brief 移除画布当中，当前绘制在最上层的对象
 * 
 */
void DrawingCanvas::removeTopRect() {
    // 移除最上层的对象，那么首先画布当中需要有对象，另外最上层的对象当前不能处在被鼠标选中的状态
    if (!this->objectList.empty() && this->draggedObj == nullptr) {
        auto text = this->objectList.back().text;
        this->objectList.pop_back();

        this->sendRectRemovedEvent(text);
        this->Refresh();    // 刷新画布，重新进行对象的绘制
    }
}


// private
void DrawingCanvas::OnPaint(wxPaintEvent& evt) {
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

#ifdef BANDED   // 废弃的旧代码
    if (gc) {
        wxSize rectSize = this->FromDIP(wxSize(100, 80));
        // 绘制一个中心点在 window 原点(左上角) 的一个长方形
        wxPoint rectOrigin = {-rectSize.GetWidth() / 2, -rectSize.GetHeight() / 2};

        wxAffineMatrix2D transform {};  // 这里初始化是一个单位矩阵

#ifdef COMBINATION1
        transform.Translate(100, 130);  // 平移
        transform.Rotate(M_PI / 3.0);   // 旋转
        transform.Scale(3, 3);          // 放缩
        // 整个变换的应用是从下到上进行的，即先进行放缩，再进行旋转，最后进行平移
#endif /* COMBINATION1 */

#ifdef COMBINATION2
        transform.Scale(3, 3);          // 放缩
        transform.Translate(100, 130);  // 平移
        transform.Rotate(M_PI / 3.0);   // 旋转
        // 这里我们先进行旋转操作，之后再进行放缩
#endif /* COMBINATION2 */

        gc->SetTransform(gc->CreateMatrix(transform));

        gc->SetBrush(*wxGREEN_BRUSH);
        gc->DrawRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight());

        // 希望可以在长方形的正中心来绘制字体，那么我们必须考虑字体的长度和宽度
        gc->SetFont(*wxNORMAL_FONT, *wxWHITE);
        wxString text = "Text";
        double textWidth, textHeight;
        gc->GetTextExtent(text, &textWidth, &textHeight);
        gc->DrawText(text, rectOrigin.x + rectSize.GetWidth() / 2.0 - textWidth / 2.0, rectOrigin.y + rectSize.GetHeight() / 2.0 - textHeight / 2.0);

        delete gc;
    }
#endif

    if (gc) {
        for (GraphicObject& object : this->objectList) {
            gc->SetTransform(gc->CreateMatrix(object.transform));
            gc->SetBrush(wxBrush(object.color));

            gc->DrawRectangle(object.rect.m_x, object.rect.m_y, object.rect.m_width, object.rect.m_height);

            gc->SetFont(*wxNORMAL_FONT, *wxWHITE);  // 颜色和字形
            double textWidth, textHeight;
            gc->GetTextExtent(object.text, &textWidth, &textHeight);    // 获取到这个字符串在屏幕显示的宽高
            gc->DrawText(   object.text, 
                            object.rect.m_x + object.rect.m_width / 2.0 - textWidth / 2.0,
                            object.rect.m_y + object.rect.m_height / 2.0 - textHeight / 2.0);
        }

        delete gc;
    }

}


// on mouse event
void DrawingCanvas::onMouseDown(wxMouseEvent& evt) {
    // 我们绘制对象的顺序是从前往后的，后面的对象如果和前面的对象有重叠的部分，那么后面的对象会覆盖前面的对象
    // 因此，我们判断一个点是否在一个对象的内部自然需要从最上层的对象开始进行判断，所以迭代器从反向进行判断
    std::list<GraphicObject>::reverse_iterator clickedObjectIter = std::find_if(
        this->objectList.rbegin(), this->objectList.rend(),
        [evt](const GraphicObject& obj) {
            wxPoint2DDouble clickPos = evt.GetPosition();   // 通过 event 来获取到点击的实际位置

            auto inv = obj.transform;
            inv.Invert();   // 获取到针对对象的变化矩阵，需要我们点击的点变换回到以 windows 坐标原点的位置来判断点击的点是否在对象的内部
            clickPos = inv.TransformPoint(clickPos);    // 针对点击的点执行对象变换的逆变换。
            return obj.rect.Contains(clickPos);
        }
    );

    if (clickedObjectIter != objectList.rend()) {
        std::list<GraphicObject>::iterator forwardIt = std::prev(clickedObjectIter.base());
        this->objectList.push_back(*forwardIt);
        // erase 函数必须使用正向的 iterator 迭代器，所以这里需要做一些转换
        this->objectList.erase(forwardIt);

        this->draggedObj = &(*std::prev(this->objectList.end()));
        this->lastDragOrigin =  evt.GetPosition();
        this->shouldBeRotated = wxGetKeyState(WXK_ALT);

        // 在 refresh() 之后会重新进行绘制，此时，被点击的对象将会最后进行绘制，那么其会绘制在所有的图像的上层
        this->Refresh();
    }
}

void DrawingCanvas::onMouseMove(wxMouseEvent& evt) {
    if (this->draggedObj != nullptr) {
        // 此时的鼠标点住了一个对象
        if (this->shouldBeRotated) {
            // 并且此时按下了 alt 键，那么在移动鼠标的时候，需要旋转图像
            double absoluteYDiff = evt.GetPosition().y - lastDragOrigin.m_y;
            // 控制移动鼠标时对象的旋转的速度
            this->draggedObj->transform.Rotate(absoluteYDiff / REDUCE_FACTORY * M_PI);
        }
        else {
            // 没有按下 Alt 键，此时移动鼠标的时候，应该是拖曳图像
            wxPoint2DDouble dragVector  = evt.GetPosition() - lastDragOrigin;

            auto inv = this->draggedObj->transform;
            inv.Invert();
            dragVector = inv.TransformDistance(dragVector);

            this->draggedObj->transform.Translate(dragVector.m_x, dragVector.m_y);
        }

        this->lastDragOrigin = evt.GetPosition();
        this->Refresh();
    }
}


void DrawingCanvas::onMouseUp(wxMouseEvent& evt) {
    this->finishDrag();
    this->finishRotation();
}

void DrawingCanvas::onMouseLeave(wxMouseEvent& evt) {
    this->finishDrag();
    this->finishRotation();
}

void DrawingCanvas::finishDrag() {
    this->draggedObj = nullptr;
}

void DrawingCanvas::finishRotation() {
    this->shouldBeRotated = false;
}


void DrawingCanvas::sendRectAddedEvent(const wxString& rectTitle) {
    wxCommandEvent event(CANVAS_RECT_ADDED, GetId());
    event.SetEventObject(this);
    event.SetString(rectTitle);

    ProcessWindowEvent(event);
}

void DrawingCanvas::sendRectRemovedEvent(const wxString& rectTitle) {
    wxCommandEvent event(CANVAS_RECT_REMOVED, GetId());
    event.SetEventObject(this);
    event.SetString(rectTitle);

    ProcessWindowEvent(event);
}