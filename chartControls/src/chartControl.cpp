#include "chartControl.h"

#include <wx/settings.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

ChartControl::ChartControl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE) {   // 每次改变窗口的大小都需要重新绘制

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &ChartControl::OnPaint, this);
}

void ChartControl::OnPaint(wxPaintEvent& evt) {
    wxAutoBufferedPaintDC dc(this);

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc) {
        // 顶部 title 的字体大小为正常的字体大小的两杯，这样看起来可以大一些
        wxFont titleFont = wxFont(wxNORMAL_FONT->GetPointSize() * 2.0, 
                wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD
        );
        // 在我的电脑上这里的执行有点问题，子窗口是黑色的，但是并不是夜间模式， 所以这里采用直接显示白色 基于gtk编译的代码没有这个 bug
        gc->SetFont(titleFont, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);
        //gc->SetFont(titleFont, *wxWHITE);

        double tw, th;
        gc->GetTextExtent(this->mTitle, &tw, &th);  // 我们获取显示的文字的长度和宽度
        // 我们在画布当中绘制的图像和整个画布的顶端以及低端具有一定的距离
        const double titleTopBottomMinimumMargin = this->FromDIP(10);
        // 整个画布从左上角的位置为坐标的原点(0,0), 一直延伸到画布的右下角
        wxRect2DDouble fullArea{0, 0, static_cast<double>(GetSize().GetWidth()), static_cast<double>(GetSize().GetHeight())};

        // marginX 表示绘制曲线的区域距离整个画布的左右边界的距离，这里设置为 1/8 的画布宽度。
        const double marginX = fullArea.GetSize().GetWidth() / 8.0;
        // 对于顶部，我们希望 title 可以和画布的顶部边界有 titleTopBottomMinimumMargin 距离的空间，绘制曲线的区域和 title 还可以预留出 titleTopBottomMinimumMargin 的空间
        const double marginTop = std::max(fullArea.GetSize().GetHeight() / 8.0, titleTopBottomMinimumMargin * 2.0 + th);
        // 绘制区域的底部和整个画布的底部边界也预留了一定的距离
        const double marginBottom = fullArea.GetSize().GetHeight() / 8.0;
        // 纵坐标的数值需要和绘制曲线区域的 y 轴之间有一些空格，不能紧贴在一起
        double labelsToChartAreaMargin = this->FromDIP(10);

        wxRect2DDouble chartArea = fullArea;
        chartArea.Inset(marginX, marginTop, marginX, marginBottom);

        gc->DrawText(this->mTitle, (fullArea.GetSize().GetWidth() - tw) / 2.0, (marginTop - th) / 2.0);
        
        //gc->SetBrush(*wxRED_BRUSH); // 设置毛刷的颜色，绘制的图像将会被填充为该颜色
        //gc->DrawRectangle(chartArea.m_x, chartArea.m_y, chartArea.m_width, chartArea.m_height);

        wxAffineMatrix2D normalizedToChartArea {};
        // 使用这个变换矩阵，将 [0, 1] 范围内的坐标映射到 chartArea 的范围内
        // x  -----> x * m_width + left_margin
        // y  -----> y * m_height + top_margin
        normalizedToChartArea.Translate(chartArea.GetLeft(), chartArea.GetTop());
        normalizedToChartArea.Scale(chartArea.m_width, chartArea.m_height);
        
        // printf("[%f, %f, %f, %f]\n", chartArea.GetLeft(), chartArea.GetTop(), chartArea.m_width, chartArea.m_height);

        double lowValue = *std::min_element(this->mValues.begin(), this->mValues.end());
        double highValue = *std::max_element(this->mValues.begin(), this->mValues.end());
        double yValueSpan = highValue - lowValue;

        // const auto& [segmentCount, rangeLow, rangeHigh] = this->calculateChartSegmentCountAndRange(lowValue, highValue); // c++17 can use
        const auto &rangeTuple = this->calculateChartSegmentCountAndRange(lowValue, highValue);
        lowValue = std::get<1>(rangeTuple); // double
        highValue = std::get<2>(rangeTuple);    // double
        const int yLinesCount = std::get<0>(rangeTuple);    // int
        yValueSpan = highValue - lowValue;

        wxAffineMatrix2D normalizedToValue {};
        normalizedToValue.Translate(0, highValue);
        normalizedToValue.Scale(1, -1);
        // y*(highValue - lowValue) *(-1) + highvalue;
        // 0 ------> highValue
        // 1 ------> lowValue
        // 0.5 ----> (highvalue + lowValue) / 2.0
        normalizedToValue.Scale(static_cast<double>(this->mValues.size() - 1), yValueSpan);

        gc->SetPen(wxPen(wxColor(128, 128, 128)));

        // 绘制 11 条 y轴的参考线 gaid
        for (int i = 0; i < yLinesCount; ++i) {
            double normalizedLineY = static_cast<double>(i) / (yLinesCount - 1);    // 这 11 条线的值的返回从 [0,1]
            auto lineStartPoint = normalizedToChartArea.TransformPoint({0, normalizedLineY});
            auto lineEndPoint = normalizedToChartArea.TransformPoint({1, normalizedLineY});

            wxPoint2DDouble linePoints[]  = {lineStartPoint, lineEndPoint};

            gc->StrokeLines(2, linePoints);

            gc->SetPen(wxPen(wxColor(128, 128, 128)));
            // 在我的电脑上这里的执行有点问题，子窗口是黑色的，但是并不是夜间模式， 所以这里采用直接显示白色 基于gtk编译的代码没有这个 bug
            gc->SetFont(*wxNORMAL_FONT, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);
            //gc->SetFont(*wxNORMAL_FONT, *wxWHITE);

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
            // 先将实际点的坐标转化为 [0, 1] 范围内的归一化坐标，之后在映射到绘图坐标当中
            pointArray[i] = valueToChartArea.TransformPoint({static_cast<double>(i), this->mValues[i]});   
        }

        gc->SetPen(wxPen(*wxBLUE, 3));
        gc->StrokeLines(this->mValues.size(), pointArray);

        delete[] pointArray;

        delete gc;
    }
}


std::tuple<int, double, double> ChartControl::calculateChartSegmentCountAndRange(double origLow, double origHigh) {
    constexpr double rangeMults[] = {0.2, 0.25, 0.5, 1.0, 2.0, 2.5, 5.0};
    constexpr int maxSegments = 6;

    double magnitude = std::floor(std::log10(origHigh - origLow));

    for (auto r : rangeMults) {
        double stepSize = r * std::pow(10.0, magnitude);
        double low = std::floor(origLow / stepSize) * stepSize;
        double high = std::ceil(origHigh / stepSize) * stepSize;

        int segment = round((high - low) / stepSize);
        if (segment <= maxSegments) {
            return std::make_tuple(segment, low, high);
        }
    }

    return std::make_tuple(11, origLow, origHigh);
}