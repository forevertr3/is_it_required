#ifndef WIN_EVENTS_H_INCLUDED
#define WIN_EVENTS_H_INCLUDED

#include <windows.h>
#include <commdlg.h>
#include <tchar.h>

TCHAR *win_event_openfiledialog(TCHAR *Filters, TCHAR *Tittles){          /*Open File Dialog */

     OPENFILENAME ofn;
     ZeroMemory(&ofn,sizeof(ofn));
     ofn.lStructSize=sizeof(ofn);

     TCHAR *DefaultExtension=0;
     TCHAR *FileName_m= new TCHAR[MAX_PATH];
     TCHAR *FileName_i= new TCHAR[MAX_PATH];
     TCHAR *Filter= 0;
     int FilterIndex=1;
     int Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
     TCHAR *InitialDir=0;
     HWND Owner=0;
     TCHAR *Tittle=0;
     bool file_ok=false;

     Filter=_T(Filters);
        Tittle=_T(Tittles);
        ofn.hwndOwner= Owner;
        ofn.lpstrDefExt = DefaultExtension;
        ofn.lpstrFile = FileName_m;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrFilter = Filter;
        ofn.nFilterIndex = FilterIndex;
        ofn.lpstrInitialDir = InitialDir;
        ofn.lpstrTitle = Tittle;
        ofn.Flags = Flags;

        GetOpenFileName(&ofn);
        if (_tcslen(FileName_m) == 0) file_ok=false;
        else    file_ok=true;

       // cout <<  FileName_m << endl;
        return FileName_m;

}



#endif // WIN_EVENTS_H_INCLUDED
