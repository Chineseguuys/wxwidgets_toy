#include "delete_line.h"

std::string delete_lines(const std::wstring& raw_string){
    int string_len = raw_string.length();
    std::string new_string {};
    wchar_t ch;

    for (int idx = 0; idx < string_len; ++idx) {
        ch = raw_string[idx];
        if (ch != '\n')
            new_string.push_back(ch);
        else {
            if (new_string.length() >= 1 && new_string.back() == '-') {
                new_string.pop_back();
            }
            else {
                new_string.push_back(' ');
            }
        }
    }

    return new_string;
}

wxString delete_lines_wxString(wxString& raw_string) {
    int string_len = raw_string.Length();
    wxString new_string {};

    for (int idx = 0; idx < string_len; ++idx) {
        wxUniChar ch = raw_string[idx].GetValue();
        if (ch != '\n') 
            new_string.Append(ch, 1);
        else {
            if (new_string.Length() >= 1 && new_string.Last() == '-') {
                new_string.RemoveLast();
            }
            else {
                new_string.Append(' ', 1);
            }
        }
    }

    return new_string;
}