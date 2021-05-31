#ifndef __DELETE_LINE_H__
#define __DELETE_LINE_H__
#include <string>
#include <wx/wx.h>

std::string delete_lines(const std::wstring& raw_wstring);

void delete_lines_c_array(const char *raw_string, char* results);

wxString delete_lines_wxString(wxString& raw_string);

#endif