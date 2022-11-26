#include <visualGrid.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
extern "C" {
#include <logs.h>
}

#define COLOR_8BIT_RANGE_VALUE (255.0)
#define GRID_MARGIN_WIDTH (1.0)

VisualGrid::VisualGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int xSquaresCount, 
    std::vector<float>& v, std::mutex& m) 
    : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE), 
      mSquaresCounts(xSquaresCount), 
      mValues(v) ,
      mValuesMutex(m){

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &VisualGrid::OnPaint, this);
}

void VisualGrid::OnPaint(wxPaintEvent& evt) {
    wxAutoBufferedPaintDC dc(this);

#ifdef DEBUG_COMPILER
    this->dbgOnPaintExecutions ++;
    log_debug("Refresh requests: %d, On Painted: %d", this->dbgRefReqs, this->dbgOnPaintExecutions);
#endif /* DEBUG_COMPILER */

    wxGraphicsContext* gc = wxGraphicsContext::CreateFromUnknownDC(dc);
    if (gc != nullptr) {
        float squareWidth = static_cast<float>(this->GetSize().GetWidth() / this->mSquaresCounts);

        std::lock_guard<std::mutex> lock(this->mValuesMutex);

        for (int i = 0; i < this->mValues.size(); ++i) {
            int colorIntensity = static_cast<int>( this->mValues[i] * COLOR_8BIT_RANGE_VALUE);

            gc->SetBrush(wxBrush(wxColor(0, colorIntensity, colorIntensity)));
            gc->DrawRectangle(
                i % this->mSquaresCounts * squareWidth,
                i / this->mSquaresCounts * squareWidth,
                squareWidth - GRID_MARGIN_WIDTH,
                squareWidth - GRID_MARGIN_WIDTH
            );
        }

        delete gc;
    }
}