// EMS Test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#ifndef EMS_TEST_H_INCLUDED
#define EMS_TEST_H_INCLUDED
#include "EMS Test.h"
#endif // !EMS_TEST_H_INCLUDED

#ifndef WINDOWS_H_INCLUDED
#define	WINDOWS_H_INCLUDED
#include <windows.h>
#endif	// !WINDOWS_H_INCLUDED

#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED
#include	"Resource.h"
#endif // !RESOURCE_H_INCLUDED

#ifndef SMH_H_INCLUDED
#define SMH_H_INCLUDED
#include "smh.h"
#endif	//!SMH_H_INCLUDED

#ifndef STDIO_H_INCLUDED
#define STDIO_H_INCLUDED
#include <stdio.h>
#endif // !STDIO_H_INCLUDED

#ifndef EMCO_H_INCLUDED
#define EMCO_H_INCLUDED
#include "emco.h"
#endif // !EMCO_H_INCLUDED

#ifndef ATLSTR_H_INCLUDED
#define	ATLSTR_H_INCLUDED
#include "atlstr.h"
#endif // !ATLSTR_H_INCLUDED

#ifndef URV5_H_INCLUDED
#define URV5_H_INCLUDED
#include "urv5.h"
#endif	// !URV5_H_INCLUDED

#ifndef AFG_H_INCLUDED
#define AFG_H_INCLUDED
#include "afg.h"
#endif	//	!AFG_H_INCLUDED

#ifndef HP_H_INCLUDED
#define HP_H_INCLUDED
#include "hp.h"
#endif	//	!HP_H_INCLUDED

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include "display.h"
#endif // !DISPLAY_H_INCLUDED

#ifndef RUN_MEASUREMENT_H_INCLUDED
#define RUN_MEASUREMENT_H_INCLUDED
#include "run_measurement.h"
#endif // !EMS_MEASUREMENT_H_INCLUDED

#ifndef RUN_TEST_H_INCLUDED
#define RUN_TEST_H_INCLUDED
#include "run_test.h"
#endif // !EMS_MEASUREMENT_H_INCLUDED

#ifndef COMMDLG_H_INCLUDED
#define COMMDLG_H_INCLUDED
#include <commdlg.h>
#endif // !COMMDLG_H_INCLUDED





#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND AboutWindow;
HWND StartAmpWindow;
BOOL ret;

// FUNCTION DEFINITION

ATOM                MyRegisterClass(HINSTANCE hInstance);
void				RegisterClassOpen();
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Want_to_exit(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	enter_configuration_dialog_function(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK	enter_amplifiers_dialog_function(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR pszFileName);
INT_PTR CALLBACK SaveFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK NewFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	/*AboutWindow = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, About, 0);
	ShowWindow(AboutWindow, nCmdShow);*/
    // TODO: Place code here.
	


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EMSTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	RegisterClassOpen();
	
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EMSTEST));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EMSTEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EMSTEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

void RegisterClassOpen() {
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0ALL Files (*.*)\0*.*\0";
	ofn.lpstrFile = (LPWSTR)szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | MB_TOPMOST;
	ofn.lpstrDefExt = L"txt";
	if (GetOpenFileName(&ofn)) {
		file_name = wstring_to_string(ofn.lpstrFile);
		int i = file_name.length();
		while (i > 0) {
			if (file_name[i] == '\\') {
				file_name.erase(file_name.begin(), file_name.end() - (file_name.length() - i - 1));
				file_name.erase(file_name.begin() + file_name.length() - 4, file_name.end());
				break;
			}
			i--;
		}
		current_path = current_path + "/";
		initial_configuration();
	}
}

BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwTextLength;

		dwTextLength = GetWindowTextLength(hEdit);
		// No need to bother if there's no text
		if (dwTextLength > 0) {
			LPSTR pszText;
			DWORD dwBufferSize = dwTextLength + 1;
			pszText = (LPSTR)GlobalAlloc(GPTR, dwBufferSize);
			if (pszText != NULL) {
				if (GetWindowText(hEdit, (LPWSTR)pszText, dwBufferSize)) {
					DWORD dwWritten;
					if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL)) {
						bSuccess = TRUE;
					}
				}
				GlobalFree(pszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   if (!hWnd)
   {
      return FALSE;
   }
   RECT Rect;
   ::GetWindowRect(hWnd, &Rect);
   ::SetWindowPos(hWnd, HWND_TOPMOST, (::GetSystemMetrics(SM_CXSCREEN) / 2 - ((Rect.right - Rect.left) / 2)),
	   (::GetSystemMetrics(SM_CYSCREEN) / 2 - ((Rect.bottom - Rect.top) / 2)),
	   (Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_SHOWWINDOW);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_FILE_NEW:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_NEWFILE), hWnd, NewFile);
				break;
			}
			case ID_FILE_OPEN:
			{
				RegisterClassOpen();
				break;
			}
			case ID_FILE_SAVE:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SAVEFILE), hWnd, SaveFile);
				break;
			}
            case ID_HELP_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_FILE_EXIT:
			{
				int ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_WANTTOEXIT), hWnd, Want_to_exit);
				if (ret == IDYES) {
					DestroyWindow(hWnd);
					break;
				}
				else if (ret == IDNO) {
					break;
				}
			}
			case ID_RUN_MEASUREMENT:
			{
				int ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_ENTERCONFIGTEST), hWnd, enter_configuration_dialog_function);
				if (ret == IDOK) {
					run_measurement();
					measurement_done = true;
					write_configuration_file();
				}
				break;
			}
			case ID_RUN_TEST:
			{
				if (measurement_done) {
					std::ostringstream sstream1, sstream2, sstream3, sstream4;
					sstream1 << field_at_eut;
					sstream2 << initial_frequency/1000000;
					sstream3 << final_frequency/1000000;
					std::string string1 = sstream1.str();
					std::string string2 = sstream2.str();
					std::string string3 = sstream3.str();
					display_message("A test will now be run with the characterisitics of the measurement.\nField: " + string1 + " V/m.\nInitial frequency: " + string2 + " MHz\nFinal frequency: " + string3 + " MHz");
					run_test();
				}
				else {
					display_message("Unable to run test. First a measurement has to be run.\nGo to Run >> Measurement.");
				}
				break;
			}
			case ID_CONFIGAMP:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ENTERCONFIGAMP), hWnd, enter_amplifiers_dialog_function);
				break;
			}
			case ID_GRAPHS_ELECTRICFIELD:
			{
				if (measurement_done) {
					plot("electric_field");
					display_message("A jpeg file has been created with the Electric Field Measurements.");
				}
				else {
					display_message("Unable to plot the Electric field measurements.\nFirst a measurement has to be run.\nGo to Run >> Measurement.");
				}
				break;
			}
			case ID_GRAPHS_VOLTAGE:
			{
				if (measurement_done) {
					plot("voltage");
					display_message("A jpeg file has been created with the Voltage Measurements.");
				}
				else {
					display_message("Unable to plot the Electric field measurements.\nFirst a measurement has to be run.\nGo to Run >> Measurement.");
				}
				break;
			}
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
		// TODO: Add any drawing code that uses hdc here...
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		PostQuitMessage(0);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Rect;
	::GetWindowRect(hDlg, &Rect);
	::SetWindowPos(hDlg, HWND_TOPMOST, (::GetSystemMetrics(SM_CXSCREEN) / 2 - ((Rect.right - Rect.left) / 2)),
		(::GetSystemMetrics(SM_CYSCREEN) / 2 - ((Rect.bottom - Rect.top) / 2)),
		(Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_SHOWWINDOW);
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
// Message handler for Want_to_exit box.
INT_PTR CALLBACK Want_to_exit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Rect;
	::GetWindowRect(hDlg, &Rect);
	::SetWindowPos(hDlg, HWND_TOPMOST, (::GetSystemMetrics(SM_CXSCREEN) / 2 - ((Rect.right - Rect.left) / 2)),
		(::GetSystemMetrics(SM_CYSCREEN) / 2 - ((Rect.bottom - Rect.top) / 2)),
		(Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_SHOWWINDOW);
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDNO || LOWORD(wParam) == IDCANCEL){
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDYES) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK enter_configuration_dialog_function(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			TCHAR buff[2048];
			GetDlgItemText(hDlg, IDC_INITIALFREQ, buff, MAX_LOADSTRING);
			initial_frequency = _tstoi64(buff)*1000000;
			GetDlgItemText(hDlg, IDC_FINALFREQ, buff, MAX_LOADSTRING);
			final_frequency = _tstoi64(buff)*1000000;
			GetDlgItemText(hDlg, IDC_MODULATION, buff, MAX_LOADSTRING);
			modulation_depth = _tstoi64(buff);
			GetDlgItemText(hDlg, IDC_FIELDEUT, buff, MAX_LOADSTRING);
			field_at_eut = _tstoi64(buff);
			GetDlgItemText(hDlg, IDC_MODULATIONFREQ, buff, MAX_LOADSTRING);
			carrier_frequency = _tstoi64(buff);
			write_configuration_file();
			det_amp();
			EndDialog(hDlg, LOWORD(wParam));
			std::string included_amplifiers = obtain_used_amplifiers();
			display_message("The amplifiers that will be used are:\n" + included_amplifiers);
			return (INT_PTR)TRUE;
		}
		break;

	case WM_PAINT:
		RECT Rect;
		::GetWindowRect(hDlg, &Rect);
		::SetWindowPos(hDlg, HWND_TOPMOST, (::GetSystemMetrics(SM_CXSCREEN) / 2 - ((Rect.right - Rect.left) / 2)),
			(::GetSystemMetrics(SM_CYSCREEN) / 2 - ((Rect.bottom - Rect.top) / 2)),
			(Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_SHOWWINDOW);
		SetDlgItemInt(hDlg, IDC_INITIALFREQ, 80, FALSE);
		SetDlgItemInt(hDlg, IDC_FINALFREQ, max_freq_amp_7/1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_FIELDEUT, 15, FALSE);
		SetDlgItemInt(hDlg, IDC_MODULATION, 80, FALSE);
		SetDlgItemInt(hDlg, IDC_MODULATIONFREQ, 1000, FALSE);
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK enter_amplifiers_dialog_function(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDNO || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			TCHAR buff[2048];
			std::string str = "asdf";
			LPSTR s = const_cast<char *>(str.c_str());
			GetDlgItemTextA(hDlg, IDC_AMPNAME1, s, MAX_LOADSTRING);
			amplifier_name_1 = s;
			GetDlgItemTextA(hDlg, IDC_AMPNAME2, s, MAX_LOADSTRING);
			amplifier_name_2 = s;
			GetDlgItemTextA(hDlg, IDC_AMPNAME3, s, MAX_LOADSTRING);
			amplifier_name_3 = s;
			GetDlgItemTextA(hDlg, IDC_AMPNAME4, s, MAX_LOADSTRING);
			amplifier_name_4 = s;
			GetDlgItemTextA(hDlg, IDC_AMPNAME5, s, MAX_LOADSTRING);
			amplifier_name_5 = s;
			GetDlgItemTextA(hDlg, IDC_AMPNAME6, s, MAX_LOADSTRING);
			amplifier_name_6 = s;
			GetDlgItemTextA(hDlg, IDC_AMPNAME7, s, MAX_LOADSTRING);
			amplifier_name_7 = s;
			GetDlgItemText(hDlg, IDC_MINFREQAMP1, buff, MAX_LOADSTRING);
			min_freq_amp_1 = _tstoi64(buff)*1000000;
			GetDlgItemText(hDlg, IDC_MINFREQAMP2, buff, MAX_LOADSTRING);
			min_freq_amp_2 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MINFREQAMP3, buff, MAX_LOADSTRING);
			min_freq_amp_3 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MINFREQAMP4, buff, MAX_LOADSTRING);
			min_freq_amp_4 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MINFREQAMP5, buff, MAX_LOADSTRING);
			min_freq_amp_5 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MINFREQAMP6, buff, MAX_LOADSTRING);
			min_freq_amp_6 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MINFREQAMP7, buff, MAX_LOADSTRING);
			min_freq_amp_7 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MAXFREQAMP1, buff, MAX_LOADSTRING);
			max_freq_amp_1 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MAXFREQAMP2, buff, MAX_LOADSTRING);
			max_freq_amp_2 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MAXFREQAMP3, buff, MAX_LOADSTRING);
			max_freq_amp_3 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MAXFREQAMP4, buff, MAX_LOADSTRING);
			max_freq_amp_4 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MAXFREQAMP5, buff, MAX_LOADSTRING);
			max_freq_amp_5 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MAXFREQAMP6, buff, MAX_LOADSTRING);
			max_freq_amp_6 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MAXFREQAMP7, buff, MAX_LOADSTRING);
			max_freq_amp_7 = _tstoi64(buff) * 1000000;
			GetDlgItemText(hDlg, IDC_MAXVOLTAMP1, buff, MAX_LOADSTRING);
			max_voltage_amp_1 = _tstoi64(buff);
			GetDlgItemText(hDlg, IDC_MAXVOLTAMP2, buff, MAX_LOADSTRING);
			max_voltage_amp_2 = _tstoi64(buff);
			GetDlgItemText(hDlg, IDC_MAXVOLTAMP3, buff, MAX_LOADSTRING);
			max_voltage_amp_3 = _tstoi64(buff);
			GetDlgItemText(hDlg, IDC_MAXVOLTAMP4, buff, MAX_LOADSTRING);
			max_voltage_amp_4 = _tstoi64(buff);
			GetDlgItemText(hDlg, IDC_MAXVOLTAMP5, buff, MAX_LOADSTRING);
			max_voltage_amp_5 = _tstoi64(buff);
			GetDlgItemText(hDlg, IDC_MAXVOLTAMP6, buff, MAX_LOADSTRING);
			max_voltage_amp_6 = _tstoi64(buff);
			GetDlgItemText(hDlg, IDC_MAXVOLTAMP7, buff, MAX_LOADSTRING);
			max_voltage_amp_7 = _tstoi64(buff);
			write_configuration_file();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	case WM_PAINT:
		RECT Rect;
		::GetWindowRect(hDlg, &Rect);
		::SetWindowPos(hDlg, HWND_TOPMOST, (::GetSystemMetrics(SM_CXSCREEN) / 2 - ((Rect.right - Rect.left) / 2)),
			(::GetSystemMetrics(SM_CYSCREEN) / 2 - ((Rect.bottom - Rect.top) / 2)),
			(Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_SHOWWINDOW);

		std::string str = amplifier_name_1;
		LPSTR s = const_cast<char *>(str.c_str());
		SetDlgItemTextA(hDlg, IDC_AMPNAME1, s);
		str = amplifier_name_2;
		s = const_cast<char *>(str.c_str());
		SetDlgItemTextA(hDlg, IDC_AMPNAME2, s);
		str = amplifier_name_3;
		s = const_cast<char *>(str.c_str());
		SetDlgItemTextA(hDlg, IDC_AMPNAME3, s);
		str = amplifier_name_4;
		s = const_cast<char *>(str.c_str());
		SetDlgItemTextA(hDlg, IDC_AMPNAME4, s);
		str = amplifier_name_5;
		s = const_cast<char *>(str.c_str());
		SetDlgItemTextA(hDlg, IDC_AMPNAME5, s);
		str = amplifier_name_6;
		s = const_cast<char *>(str.c_str());
		SetDlgItemTextA(hDlg, IDC_AMPNAME6, s);
		str = amplifier_name_7;
		s = const_cast<char *>(str.c_str());
		SetDlgItemTextA(hDlg, IDC_AMPNAME7, s);
		
		SetDlgItemInt(hDlg, IDC_MINFREQAMP1, min_freq_amp_1 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MINFREQAMP2, min_freq_amp_2 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MINFREQAMP3, min_freq_amp_3 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MINFREQAMP4, min_freq_amp_4 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MINFREQAMP5, min_freq_amp_5 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MINFREQAMP6, min_freq_amp_6 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MINFREQAMP7, min_freq_amp_7 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MAXFREQAMP1, max_freq_amp_1 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MAXFREQAMP2, max_freq_amp_2 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MAXFREQAMP3, max_freq_amp_3 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MAXFREQAMP4, max_freq_amp_4 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MAXFREQAMP5, max_freq_amp_5 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MAXFREQAMP6, max_freq_amp_6 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MAXFREQAMP7, max_freq_amp_7 / 1000000, FALSE);
		SetDlgItemInt(hDlg, IDC_MAXVOLTAMP1, max_voltage_amp_1, TRUE);
		SetDlgItemInt(hDlg, IDC_MAXVOLTAMP2, max_voltage_amp_2, TRUE);
		SetDlgItemInt(hDlg, IDC_MAXVOLTAMP3, max_voltage_amp_3, TRUE);
		SetDlgItemInt(hDlg, IDC_MAXVOLTAMP4, max_voltage_amp_4, TRUE);
		SetDlgItemInt(hDlg, IDC_MAXVOLTAMP5, max_voltage_amp_5, TRUE);
		SetDlgItemInt(hDlg, IDC_MAXVOLTAMP6, max_voltage_amp_6, TRUE);
		SetDlgItemInt(hDlg, IDC_MAXVOLTAMP7, max_voltage_amp_7, TRUE);

	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SaveFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDYES || LOWORD(wParam) == IDOK)
		{
			TCHAR buff[2048];
			std::string str = "asdf";
			std::string astr = "asdf";
			LPSTR a = const_cast<char *>(astr.c_str());
			LPSTR s = const_cast<char *>(str.c_str());
			GetDlgItemTextA(hDlg, IDC_FILENAME, s, MAX_LOADSTRING);
			file_name = s;
			current_path = current_path + "/" + file_name + "/";
			CreateDirectoryA(current_path.c_str(), NULL);
			file_name = file_name;
			write_configuration_file();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDNO || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK NewFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Rect;
	::GetWindowRect(hDlg, &Rect);
	::SetWindowPos(hDlg, HWND_TOPMOST, (::GetSystemMetrics(SM_CXSCREEN) / 2 - ((Rect.right - Rect.left) / 2)),
		(::GetSystemMetrics(SM_CYSCREEN) / 2 - ((Rect.bottom - Rect.top) / 2)),
		(Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_SHOWWINDOW);
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			TCHAR buff[2048];
			std::string str = "asdf";
			std::string astr = "asdf";
			LPSTR a = const_cast<char *>(astr.c_str());
			LPSTR s = const_cast<char *>(str.c_str());
			GetDlgItemTextA(hDlg, IDC_NEWFILENAME, s, MAX_LOADSTRING);
			file_name = s;
			current_path = current_path + "/" + file_name + "/";
			CreateDirectoryA(current_path.c_str(), NULL);
			make_new_file();
			initial_configuration();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_CANCELNEW ) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}

