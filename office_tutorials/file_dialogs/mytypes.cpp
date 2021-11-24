#include "mytypes.h"
#include <wx/wx.h>

typedef struct FILE_INFORMATION {
    wxString path;
    wxString file_name;
    int filterIndex;
} FILE_INFORMATION;