#ifndef _CHART_CONTROL_H_
#define _CHART_CONTROL_H_

#include <wx/wx.h>
#include <vector>
#include <string>
#include <memory>

class ChartControl: public wxWindow {
public:
    ChartControl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

    std::vector<double> mValues;
    std::string         mTitle;

private:
    void OnPaint(wxPaintEvent& evt);
};

#endif /* _CHART_CONTROL_H_ */