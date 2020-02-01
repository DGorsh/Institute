#include "stdafx.h"
#include "Laba7.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	HelpDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	SizeDialog(HWND, UINT, WPARAM, LPARAM);

BOOL PopFileOpenDlg(HWND hwnd, PSTR pstrFileName, PSTR pstrTitleName);
void PopFileInitialize(HWND hwnd);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LABA7, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA7));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
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
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA7));
	wcex.hCursor		= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LABA7);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; 

   hWnd = CreateWindow(szWindowClass, szTitle,  WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

bool
	inEdit = false;
char str[8] = { 0 }, *pStr = str;
char nstr[8] = { 0 }, *pnStr = nstr;

float k = 1;
int kx = 0, ky = 0;
Draft object[10];
int startX, startY, countOb = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int
		wmId, wmEvent;
	PAINTSTRUCT 
		ps;
	static RECT 
		rect, infoRect, groupRect, nameRect, assRect;
	HDC 
		hdc;
	static char szFileName[_MAX_PATH];
	static char szTitleName[_MAX_FNAME + _MAX_EXT];
	switch (message)
	{
	case WM_CREATE:
		lstrcpy(szFileName, (PSTR)
			(((LPCREATESTRUCT)lParam)->lpCreateParams));
		if (strlen(szFileName) > 0)
		{
			GetFileTitle(szFileName, szTitleName,
				sizeof(szTitleName));
		}
		PopFileInitialize(hWnd);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId)
		{
		case IDM_OPEN:
			countOb = 0;
			if (PopFileOpenDlg(hWnd, szFileName, szTitleName))
			{
				FILE *fin = fopen(szFileName, "r");
				char
					ch,
					str[6] = { 0 }, *pStr = str;
				int num[5], j = 0;
				while ((ch = fgetc(fin)) != EOF)
				{
					if (j == 5)
					{
						object[countOb].Set(num[0], num[1], num[2], num[3], num[4]);
						j = 0;
						countOb++;
						continue;
					}
					if (ch == ' ')
					{
						num[j] = atoi(str);
						j++;
						pStr = str;
						continue;
					}
					if (isdigit(ch))
					{
						*pStr++ = ch;
						*pStr = 0;
					}
				}
				fclose(fin);
				InvalidateRect(hWnd, &rect, TRUE);
			}


			break;
		case IDM_SIZE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SIZEBOX), hWnd, SizeDialog);
			InvalidateRect(hWnd, &rect, TRUE);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, HelpDialog);
			break;
		case IDM_DESCRIPTION:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DESCRIPTIONBOX), hWnd, HelpDialog);
			break;
		case IDM_ZPLUS:
			k+=0.2;
			if (k > 1.9) EnableMenuItem(GetMenu(hWnd), IDM_ZPLUS, MF_DISABLED | MF_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_ZMINUS, MF_DEFAULT);
			InvalidateRect(hWnd, &rect, TRUE);
			break;
		case IDM_ZMINUS:
			k-=0.2;
			if (k < 0.3) EnableMenuItem(GetMenu(hWnd), IDM_ZMINUS, MF_DISABLED | MF_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_ZPLUS, MF_DEFAULT);
			InvalidateRect(hWnd, &rect, TRUE);
			break;
		case IDM_ZNORMAL:
			k = 1;
			EnableMenuItem(GetMenu(hWnd), IDM_ZMINUS, MF_DEFAULT);
			EnableMenuItem(GetMenu(hWnd), IDM_ZPLUS, MF_DEFAULT);
			startX = 0;
			startY = 0;
			SendMessage(hWnd, WM_PAINT, wParam, lParam);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}	
		break;
	case WM_LBUTTONDOWN:
		if (LOWORD(lParam) < 150 && HIWORD(lParam) < 25) inEdit = true;
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == 13) inEdit = false;
		if (inEdit)
		{
			if (wParam == 8 && strlen(nstr) > 0)
			{
				pnStr--;
				*pnStr = 0;
				InvalidateRect(hWnd, &assRect, TRUE);
			}
			if (strlen(nstr) > 6 && wParam != 8) break;
			if (wParam !=8) *pnStr++ = wParam;
			InvalidateRect(hWnd, &assRect, FALSE);
		}
	case WM_MOUSEMOVE:
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			kx = (startX - LOWORD(lParam));
			ky = (startY - HIWORD(lParam));
			InvalidateRect(hWnd, &rect, TRUE);
		}
		startX = LOWORD(lParam);
		startY = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < countOb; i++)
		{
			object[i].Draw(hdc, kx, ky, k);
		}
		ReleaseDC(hWnd, hdc);
		hdc = GetDC(hWnd);
		//Прямоугольник в правом нижнем углу с информацией
			GetClientRect(hWnd, &rect);
			Rectangle(hdc, rect.right - 300, rect.bottom - 100, rect.right, rect.bottom);
			MoveToEx(hdc, rect.right - 150, rect.bottom, NULL);
			LineTo(hdc, rect.right - 150, rect.bottom - 100);
			MoveToEx(hdc, rect.right - 300, rect.bottom - 50, NULL);
			LineTo(hdc, rect.right - 150, rect.bottom - 50);
			infoRect.left = rect.right - 300;
			infoRect.bottom = rect.bottom - 50;
			infoRect.right = rect.right - 150;
			infoRect.top = rect.bottom - 100;
			DrawText(hdc, "Водяков А.С.", 11, &infoRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			groupRect.left = rect.right - 300;
			groupRect.bottom = rect.bottom;
			groupRect.right = rect.right - 150;
			groupRect.top = rect.bottom - 50;
			DrawText(hdc, "М8О-113Б-17", 11, &groupRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			nameRect.left = rect.right - 150;
			nameRect.bottom = rect.bottom;
			nameRect.right = rect.right;
			nameRect.top = rect.bottom - 100;
			DrawText(hdc, "Чертёж", 6, &nameRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		//-----------------------------------------------------------------------------------
		//Прямоугольник в левом верхнем углу с оценкой
			assRect.left = 1; assRect.top = 1; assRect.right = 149; assRect.bottom = 24;
			Rectangle(hdc, 0, 0, 150, 25);
			SetTextColor(hdc, RGB(0, 255, 0));
			DrawText(hdc, nstr, strlen(nstr), &assRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		//------------------------------------------------------------------------------------
		EndPaint(hWnd, &ps); 
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK HelpDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
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

INT_PTR CALLBACK SizeDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char str[5];
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_OK)
		{
			GetWindowText(GetDlgItem(hDlg, 1000), str, 4);
			k = atof(str) / 100;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

static OPENFILENAME ofn;

void PopFileInitialize(HWND hwnd)
{
	static char szFilter[] = "Text Files(*.TXT)\0*.txt\0";
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = NULL;          // Set in Open and Close functions 
	ofn.nMaxFile = _MAX_PATH;
	ofn.lpstrFileTitle = NULL;          // Set in Open and Close functions 
	ofn.nMaxFileTitle = _MAX_FNAME + _MAX_EXT;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	ofn.Flags = 0;             // Set in Open and Close functions 
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = "txt";
	ofn.lCustData = 0L;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;
}

BOOL PopFileOpenDlg(HWND hwnd, PSTR pstrFileName, PSTR pstrTitleName)
{
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = pstrFileName;
	ofn.lpstrFileTitle = pstrTitleName;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	return GetOpenFileName(&ofn);
}