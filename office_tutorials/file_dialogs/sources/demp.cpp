#include "frame.h"
#include "mydialog.h"
extern "C" {
// added by myself in dir /usr/local/include with dynamic link
#include <simplelogs.h> // C 库
};
#include <stdio.h>

/* https://wiki.wxwidgets.org/Writing_Your_First_Application-Using_The_WxTextCtrl */

// 为 open file 按钮指定的事件 ID
#define wxID_OPEN_FILE_DIALOG 6001

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
EVT_MENU(wxID_OPEN_FILE_DIALOG, MyFrame::OnOpenFile)
EVT_MENU(MENU_New, MyFrame::Newfile)
EVT_MENU(MENU_Close, MyFrame::Closefile)
EVT_MENU(MENU_Save, MyFrame::Savefile)
END_EVENT_TABLE()

void MyFrame::OnQuit(wxCommandEvent &event) {
    // Destroy the frame
    Close();
}

void MyFrame::Newfile(wxCommandEvent &WXUNUSED(evt)) {
}

void MyFrame::Closefile(wxCommandEvent &evt) {
    if (this->main_edit_box->IsModified()) {
        log_warn("file %s is modified, you should save it",
                 static_cast<const char *>(this->file_name.mb_str(wxConvUTF8)));

        wxMessageDialog dialog(NULL, wxT("Save"), wxT("Save the file?"), wxNO_DEFAULT | wxYES_NO | wxCANCEL);
        switch (dialog.ShowModal()) {
        case wxID_YES:
            this->main_edit_box->SaveFile(this->file_path);
            this->main_edit_box->Clear();
            break;
        case wxID_NO:
            this->main_edit_box->Clear();
            break;
        case wxID_CANCEL:
            break;
        default:
            log_error("error when excute wxMessageDialog");
        }
    } else {
        this->main_edit_box->Clear();
    }
}

void MyFrame::Savefile(wxCommandEvent &evt) {
    log_info("save file with name : %s", static_cast<const char *>(this->file_path.mb_str(wxConvUTF8)));
    this->main_edit_box->SaveFile(this->file_path);
}

/**
 * @brief 点击打开文件按钮之后的事件处理
 *
 * @param evt   点击按钮的事件
 */
void MyFrame::OnOpenFile(wxCommandEvent &evt) {
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("CPP files (*.cpp)|*.cpp|H files (*.h)|*.h|Text files (*.txt)|*.txt");
    wxString defaultDir = wxT("/home/yjh/");
    wxString defaultFilename = wxEmptyString;

    wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard,
                        wxFD_DEFAULT_STYLE);
    if (dialog.ShowModal() == wxID_OK) {
        this->file_path = dialog.GetPath();
        this->file_name = dialog.GetFilename();
        int filterIndex = dialog.GetFilterIndex();

        log_info("file name is %s, file path is %s",
                 static_cast<const char *>(this->file_name.mb_str(wxConvUTF8)),
                 static_cast<const char *>(this->file_path.mb_str(wxConvUTF8)));

        this->main_edit_box->LoadFile(this->file_path);
    }
}

/**
 * @brief Construct a new My Frame:: My Frame object
 *
 * @param 主窗口的名称
 */
MyFrame::MyFrame(const wxString &title) :
    wxFrame(NULL, wxID_ANY, title) {
    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;

    fileMenu->Append(wxID_EXIT, wxT("&Exit\tAlt-X"), wxT("Quit this program"));
    fileMenu->Append(wxID_OPEN_FILE_DIALOG, wxT("&Open\tAlt-O"),
                     wxT("Open file"));
    fileMenu->Append(MENU_New, wxT("&New"), wxT("Create a new file"));
    fileMenu->Append(MENU_Close, wxT("&close"), wxT("Close file"));
    fileMenu->Append(MENU_Save, wxT("&Save"), wxT("Save file"));

    // Now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

    this->main_edit_box = new wxTextCtrl(
        this, TEXT_Main, wxT("Please Open a File, or Create a New File!"),
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH,
        wxDefaultValidator, wxTextCtrlNameStr);

    // 窗口最大化
    Maximize();

    // Create a status bar just for fun
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}