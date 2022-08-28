#include "chartControl.h"

#include <wx/settings.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

ChartControl::ChartControl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE) {

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &ChartControl::OnPaint, this);
}

void ChartControl::OnPaint(wxPaintEvent& evt) {
    wxAutoBufferedPaintDC dc(this);

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc) {
        wxFont titleFont = wxFont(wxNORMAL_FONT->GetPointSize() * 2.0, 
                wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD
        );
        // 在我的电脑上这里的执行有点问题，子窗口是黑色的，但是并不是夜间模式， 所以这里采用直接显示白色
        //gc->SetFont(titleFont, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);
        gc->SetFont(titleFont, *wxWHITE);

        double tw, th;
        gc->GetTextExtent(this->mTitle, &tw, &th);  // 我们获取显示的文字的长度和宽度
        const double titleTopBottomMinimumMargin = this->FromDIP(10);
        wxRect2DDouble fullArea{0, 0, static_cast<double>(GetSize().GetWidth()), static_cast<double>(GetSize().GetHeight())};

        const double marginX = fullArea.GetSize().GetWidth() / 8.0;
        const double marginTop = std::max(fullArea.GetSize().GetHeight() / 8.0, titleTopBottomMinimumMargin * 2.0 + th);
        const double marginBottom = fullArea.GetSize().GetHeight() / 8.0;
        double labelsToChartAreaMargin = this->FromDIP(10);

        wxRect2DDouble chartArea = fullArea;
        chartArea.Inset(marginX, marginTop, marginX, marginBottom);

        gc->DrawText(this->mTitle, (fullArea.GetSize().GetWidth() - tw) / 2.0, (marginTop - th) / 2.0);
        
        //gc->SetBrush(*wxRED_BRUSH); // 设置毛刷的颜色，绘制的图像将会被填充为该颜色
        //gc->DrawRectangle(chartArea.m_x, chartArea.m_y, chartArea.m_width, chartArea.m_height);

        wxAffineMatrix2D normalizedToChartArea {};
        // 使用这个变换矩阵，将 [0, 1] 范围内的坐标映射到 chartArea 的范围内
        normalizedToChartArea.Translate(chartArea.GetLeft(), chartArea.GetTop());
        normalizedToChartArea.Scale(chartArea.m_width, chartArea.m_height);
        
        // printf("[%f, %f, %f, %f]\n", chartArea.GetLeft(), chartArea.GetTop(), chartArea.m_width, chartArea.m_height);

        double lowValue = *std::min_element(this->mValues.begin(), this->mValues.end());
        double highValue = *std::max_element(this->mValues.begin(), this->mValues.end());
        double yValueSpan = highValue - lowValue;

        wxAffineMatrix2D normalizedToValue {};
        normalizedToValue.Translate(0, highValue);
        normalizedToValue.Scale(1, -1);
        // y*(highValue - lowValue) *(-1) + highvalue;
        // 0 ------> highValue
        // 1 ------> lowValue
        // 0.5 ----> (highvalue + lowValue) / 2.0
        normalizedToValue.Scale(static_cast<double>(this->mValues.size() - 1), yValueSpan);
    
        const int yLinesCount = 11;
        gc->SetPen(wxPen(wxColor(128, 128, 128)));

        for (int i = 0; i < yLinesCount; ++i) {
            double normalizedLineY = static_cast<double>(i) / (yLinesCount - 1);
            auto lineStartPoint = normalizedToChartArea.TransformPoint({0, normalizedLineY});
            auto lineEndPoint = normalizedToChartArea.TransformPoint({1, normalizedLineY});

            wxPoint2DDouble linePoints[]  = {lineStartPoint, lineEndPoint};

            gc->StrokeLines(2, linePoints);

            gc->SetPen(wxPen(wxColor(128, 128, 128)));
            gc->SetFont(*wxNORMAL_FONT, *wxWHITE);

            double valueAtLineY = normalizedToValue.TransformPoint({0, normalizedLineY}).m_y;
            auto text = wxString::Format("%.2f", valueAtLineY);
            text = wxControl::Ellipsize(text, dc, wxELLIPSIZE_MIDDLE, chartArea.GetLeft() - labelsToChartAreaMargin);

            double tw, th;
            gc->GetTextExtent(text, &tw, &th);
            gc->DrawText(text, chartArea.GetLeft() - labelsToChartAreaMargin - tw, lineStartPoint.m_y - th / 2.0);
        }

        wxPoint2DDouble leftHLinePoints[] = {
            normalizedToChartArea.TransformPoint({0, 0}),
            normalizedToChartArea.TransformPoint({0, 1})
        };

        wxPoint2DDouble rightHLinePoints[] = {
            normalizedToChartArea.TransformPoint({1, 0}),
            normalizedToChartArea.TransformPoint({1, 1})
        };

        gc->StrokeLines(2, leftHLinePoints);
        gc->StrokeLines(2, rightHLinePoints);

        wxPoint2DDouble* pointArray = new wxPoint2DDouble[mValues.size()];
        wxAffineMatrix2D valueToNormalized = normalizedToValue;
        valueToNormalized.Invert();
        wxAffineMatrix2D valueToChartArea = normalizedToChartArea;
        valueToChartArea.Concat(valueToNormalized);
         
        for (int i = 0; i < this->mValues.size(); ++i) {
            pointArray[i] = valueToChartArea.TransformPoint({static_cast<double>(i), this->mValues[i]});   
        }

        gc->SetPen(wxPen(*wxBLUE, 3));
        gc->StrokeLines(this->mValues.size(), pointArray);

        delete[] pointArray;

        delete gc;
    }
}