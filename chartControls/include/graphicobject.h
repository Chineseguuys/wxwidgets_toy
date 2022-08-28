#ifndef _GRAPHIC_OBJECT_H_
#define _GRAPHIC_OBJECT_H_

#include <wx/wx.h>

struct GraphicObject {
    wxRect2DDouble      rect;
    wxColor             color;
    wxString            text;
    wxAffineMatrix2D    transform;
};

#endif /* _GRAPHIC_OBJECT_H_ */