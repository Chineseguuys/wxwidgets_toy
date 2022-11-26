#ifndef __VISUALGRID_H__
#define __VISUALGRID_H__

#include <vector>
#include <wx/wx.h>
#include <mutex>


class VisualGrid : public wxWindow {
public:
    VisualGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int xSquaresCount, 
        std::vector<float>& v, std::mutex& m);

public:
#ifdef  DEBUG_COMPILER
    int dbgRefReqs = 0;
    int dbgOnPaintExecutions = 0;
#endif /* DEBUG_COMPILER */

private:
    void OnPaint(wxPaintEvent& evt);

private:
    int                 mSquaresCounts;
    std::vector<float>& mValues;
    std::mutex&         mValuesMutex;
};

#endif /* __VISUALGRID_H__ */