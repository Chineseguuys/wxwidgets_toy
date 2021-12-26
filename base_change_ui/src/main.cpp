#include <wx/wx.h>
#include <wx/listctrl.h>
#include "base_change.h"
#include "frame.h"

extern "C" {
#include <simplelogs.h>
};

#define MAX_STRING_LENGTH 32

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, FRAME_ID_ONE, title, pos, size) {
    wxBoxSizer *h_box = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *v_box_10b = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *v_box_2b = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *v_box_16b = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *v_box_8b = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *base10_txt = new wxStaticText(this, wxID_ANY, wxT("10 进制:"));
    wxTextCtrl *  base10_input = new wxTextCtrl(this, TEXT_CTRL_ID_BASE10, wxT(""));
    base10_input->Bind(wxEVT_TEXT, &MyFrame::deal_with_10base, this);

    wxStaticText *base2_txt = new wxStaticText(this, wxID_ANY, wxT("2  进制:"));
    wxTextCtrl *  base2_input = new wxTextCtrl(this, TEXT_CTRL_ID_BASE2, wxT(""));
    base2_input->Bind(wxEVT_TEXT, &MyFrame::deal_with_2base, this);

    wxStaticText *base8_txt = new wxStaticText(this, wxID_ANY, wxT("8  进制:"));
    wxTextCtrl *  base8_input = new wxTextCtrl(this, TEXT_CTRL_ID_BASE8, wxT(""));
    base8_input->Bind(wxEVT_TEXT, &MyFrame::deal_with_8base, this);

    wxStaticText *base16_txt = new wxStaticText(this, wxID_ANY, wxT("16 进制:"));
    wxTextCtrl *  base16_input = new wxTextCtrl(this, TEXT_CTRL_ID_BASE16, wxT(""));
    base16_input->Bind(wxEVT_TEXT, &MyFrame::deal_with_16base, this);

    //
    this->text_ctrl_refs[0] = base2_input;
    this->text_ctrl_refs[1] = base8_input;
    this->text_ctrl_refs[2] = base10_input;
    this->text_ctrl_refs[3] = base16_input;

    v_box_10b->Add(base10_txt, 0, wxTOP | wxRIGHT | wxLEFT | wxBOTTOM | wxALIGN_CENTRE, 8);
    v_box_10b->Add(base10_input, 1, wxRIGHT | wxALIGN_CENTRE, 8);

    v_box_2b->Add(base2_txt, 0, wxTOP | wxRIGHT | wxLEFT | wxBOTTOM | wxALIGN_CENTRE, 8);
    v_box_2b->Add(base2_input, 1, wxRIGHT | wxALIGN_CENTRE, 8);

    v_box_8b->Add(base8_txt, 0, wxTOP | wxRIGHT | wxLEFT | wxBOTTOM | wxALIGN_CENTRE, 8);
    v_box_8b->Add(base8_input, 1, wxRIGHT | wxALIGN_CENTRE, 8);

    v_box_16b->Add(base16_txt, 0, wxTOP | wxRIGHT | wxLEFT | wxBOTTOM | wxALIGN_CENTRE, 8);
    v_box_16b->Add(base16_input, 1, wxRIGHT | wxALIGN_CENTRE, 8);

    h_box->Add(v_box_10b, 1, wxEXPAND | wxALL);
    h_box->Add(v_box_2b, 1, wxEXPAND | wxALL);
    h_box->Add(v_box_8b, 1, wxEXPAND | wxALL);
    h_box->Add(v_box_16b, 1, wxEXPAND | wxALL);

    this->SetSizerAndFit(h_box);
}

void MyFrame::deal_with_10base(wxCommandEvent &evt) {
    if (this->text_ctrl_refs[2]->HasFocus()) {
        int string_len = this->text_ctrl_refs[2]->GetLineLength(0);
        if (string_len >= MAX_STRING_LENGTH) {
            log_error("string is too long");
            this->text_ctrl_refs[2]->SetBackgroundColour(wxColour(200, 100, 100));
            return;
        }

        this->text_ctrl_refs[2]->SetBackgroundColour(wxColour(100, 200, 100));
        std::string nums = this->text_ctrl_refs[2]->GetLineText(0).ToStdString();

        for (int index = 0; index < string_len; ++index) {
            if (nums[index] < '0' || nums[index] > '9') {
                log_error("invarid char %c", nums[index]);
                this->text_ctrl_refs[2]->SetBackgroundColour(wxColour(200, 100, 100));
                return;
            }
        }

        std::string base = ConvertBase(nums, 10, 2);
        this->text_ctrl_refs[0]->Clear();
        (*this->text_ctrl_refs[0]) << base;
        base = ConvertBase(nums, 10, 8);
        this->text_ctrl_refs[1]->Clear();
        (*this->text_ctrl_refs[1]) << base;
        base = ConvertBase(nums, 10, 16);
        this->text_ctrl_refs[3]->Clear();
        (*this->text_ctrl_refs[3]) << base;
    } else {
        // 没有焦点，更新，颜色设置为绿色
        this->text_ctrl_refs[2]->SetBackgroundColour(wxColour(100, 200, 100));
    }
}

void MyFrame::deal_with_2base(wxCommandEvent &evt) {
    if (this->text_ctrl_refs[0]->HasFocus()) {
        int string_len = this->text_ctrl_refs[0]->GetLineLength(0);
        if (string_len >= MAX_STRING_LENGTH * 4) {
            log_error("string is too long, delete some");
            this->text_ctrl_refs[0]->SetBackgroundColour(wxColour(200, 100, 100));
            return;
        }

        this->text_ctrl_refs[0]->SetBackgroundColour(wxColour(100, 200, 100));
        std::string nums = this->text_ctrl_refs[0]->GetLineText(0).ToStdString();

        for (int index = 0; index < string_len; ++index) {
            if (nums[index] < '0' || nums[index] > '1') {
                log_error("invalid char %c", nums[index]);
                this->text_ctrl_refs[0]->SetBackgroundColour(wxColour(200, 100, 100));
                return;
            }
        }

        std::string base = ConvertBase(nums, 2, 8);
        this->text_ctrl_refs[1]->Clear();
        (*this->text_ctrl_refs[1]) << base;
        base = ConvertBase(nums, 2, 10);
        this->text_ctrl_refs[2]->Clear();
        (*this->text_ctrl_refs[2]) << base;
        base = ConvertBase(nums, 2, 16);
        this->text_ctrl_refs[3]->Clear();
        (*this->text_ctrl_refs[3]) << base;
    } else {
        // 没有获得焦点，只是更新
        this->text_ctrl_refs[0]->SetBackgroundColour(wxColour(100, 200, 100));
    }
}

void MyFrame::deal_with_8base(wxCommandEvent &evt) {
    if (this->text_ctrl_refs[1]->HasFocus()) {
        int string_len = this->text_ctrl_refs[1]->GetLineLength(0);
        if (string_len >= MAX_STRING_LENGTH) {
            log_error("string is too long, delete some");
            this->text_ctrl_refs[1]->SetBackgroundColour(wxColour(200, 100, 100));
            return;
        }

        this->text_ctrl_refs[1]->SetBackgroundColour(wxColour(100, 200, 100));
        std::string nums = this->text_ctrl_refs[1]->GetLineText(0).ToStdString();

        for (int index = 0; index < string_len; ++index) {
            if (nums[index] < '0' || nums[index] > '7') {
                log_error("invalid char %c", nums[index]);
                this->text_ctrl_refs[1]->SetBackgroundColour(wxColour(200, 100, 100));
                return;
            }
        }

        std::string base = ConvertBase(nums, 8, 2);
        this->text_ctrl_refs[0]->Clear();
        (*this->text_ctrl_refs[0]) << base;
        base = ConvertBase(nums, 8, 10);
        this->text_ctrl_refs[2]->Clear();
        (*this->text_ctrl_refs[2]) << base;
        base = ConvertBase(nums, 8, 16);
        this->text_ctrl_refs[3]->Clear();
        (*this->text_ctrl_refs[3]) << base;
    } else {
        // 没有获得焦点，只是更新
        this->text_ctrl_refs[1]->SetBackgroundColour(wxColour(100, 200, 100));
    }
}

void MyFrame::deal_with_16base(wxCommandEvent &evt) {
    if (this->text_ctrl_refs[3]->HasFocus()) {
        int string_len = this->text_ctrl_refs[3]->GetLineLength(0);
        if (string_len >= MAX_STRING_LENGTH) {
            log_error("string is too long, delete some");
            this->text_ctrl_refs[3]->SetBackgroundColour(wxColour(200, 100, 100));
            return;
        }

        this->text_ctrl_refs[3]->SetBackgroundColour(wxColour(100, 200, 100));
        std::string nums = this->text_ctrl_refs[3]->GetLineText(0).ToStdString();

        for (int index = 0; index < string_len; ++index) {
            if (nums[index] < '0' || (nums[index] > '9' && nums[index] < 'A') || (nums[index] > 'F' && nums[index] < 'a') || nums[index] > 'f') {
                log_error("invalid char %c", nums[index]);
                this->text_ctrl_refs[3]->SetBackgroundColour(wxColour(200, 100, 100));
                return;
            }
        }

        std::string base = ConvertBase(nums, 16, 2);
        this->text_ctrl_refs[0]->Clear();
        (*this->text_ctrl_refs[0]) << base;
        base = ConvertBase(nums, 16, 8);
        this->text_ctrl_refs[1]->Clear();
        (*this->text_ctrl_refs[1]) << base;
        base = ConvertBase(nums, 16, 10);
        this->text_ctrl_refs[2]->Clear();
        (*this->text_ctrl_refs[2]) << base;
    } else {
        // 没有获得焦点，只是更新
        this->text_ctrl_refs[3]->SetBackgroundColour(wxColour(100, 200, 100));
    }
}