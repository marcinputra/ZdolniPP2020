#if defined(UNICODE) && !defined(_UNICODE)

#define _UNICODE

#elif defined(_UNICODE) && !defined(UNICODE)

#define UNICODE

#endif
// nowy rok
// projekt zdolni2020
//Tomasz

#include <tchar.h>
#include <string>
#include <windows.h>
#include "Projekt.h"
#include <vector>
#include "DebugDataSave.h"
//#include <rysowanie.h>
//#include "resource.h"
// #include "menu.rc"


#define IDPRZYCISKU1 505



void AddMenus(HWND);

#define IDM_FILE_NEW 1
#define IDM_FILE_OPEN 2
#define IDM_FILE_QUIT 3

/* zmienne */


// int a = 150, b = 150;

/*  Declare Windows procedure  */

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);



/*  Make the class name into a global variable  */

TCHAR szClassName[] = _T("CodeBlocksWindowsApp");





HWND hText;

HDC hdc;

LPSTR bufor;

DWORD size;

HPEN kolorpisaka;

HWND czarny, czerwony, zielony, niebieski, prostokat, linia, krzywa;

int x, y, lastx, lasty;
//
double seconds_since_last_data_save = time(NULL);
std::vector <int> data_from_last_sec;
///for web and debuging purposes
int colour = 0;
///0 - black, 1 - red, 2 - green, 3 - blue

int WINAPI WinMain(HINSTANCE hThisInstance,

    HINSTANCE hPrevInstance,

    LPSTR lpszArgument,

    int nCmdShow)

{

    HWND hwnd;        /* This is the handle for our window */

    MSG messages;     /* Here messages to the application are saved */

    WNDCLASSEX wincl; /* Data structure for the windowclass */



    /* dodawanie menu programu */

    /* HMENU hMenu = LoadMenu(HINSTANCE hInstance, MAKEINTRESOURCE(200)); */

    // TEST - Krystian

    /* The Window structure */

    wincl.hInstance = hThisInstance;

    wincl.lpszClassName = szClassName;

    wincl.lpfnWndProc = WindowProcedure; /* This function is called by windows */

    wincl.style = CS_DBLCLKS;            /* Catch double-clicks */

    wincl.cbSize = sizeof(WNDCLASSEX);



    /* Use default icon and mouse-pointer */

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);

    wincl.lpszMenuName = NULL; /* No menu */

    wincl.cbClsExtra = 0;      /* No extra bytes after the window class */

    wincl.cbWndExtra = 0;      /* structure or the window instance */

    /* Use Windows's default colour as the background of the window */

    wincl.hbrBackground = (HBRUSH)0;




    /* Register the window class, and if it fails quit the program */

    if (!RegisterClassEx(&wincl))

        return 0;

    // WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU

    /* The class is registered, let's create the program*/
	HMENU hMenu = LoadMenu(hThisInstance, MAKEINTRESOURCE(IDC_PROJEKT));
    hwnd = CreateWindowEx(

        0,                                  /* Extended possibilites for variation */

        szClassName,                        /* Classname */

        _T("Drawboard"), /* Title Text */

        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,                /* default window */

        CW_USEDEFAULT,                      /* Windows decides the position */

        CW_USEDEFAULT,                      /* where the window ends up on the screen */

        1280,                                /* The programs width */

        800,                                /* and height in pixels */

        HWND_DESKTOP,                       /* The window is a child-window to desktop */

        hMenu,                               /* Menu */

        hThisInstance,                      /* Program Instance handler */

        NULL                                /* No Window Creation data */

    );



    /* dodawanie przycisku */

    czarny = CreateWindowEx(

        0,

        _T("BUTTON"),

        _T("BLACK"),

        BS_BOTTOM | WS_CHILD | WS_VISIBLE,

        10, 10, 80, 20,

        hwnd,

        NULL,

        hThisInstance,

        NULL);



    czerwony = CreateWindowEx(

        0,

        _T("BUTTON"),

        _T("RED"),

        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

        100, 10, 80, 20,

        hwnd,

        NULL,

        hThisInstance,

        NULL);

    zielony = CreateWindowEx(

        0,

        _T("BUTTON"),

        _T("GREEN"),

        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

        190, 10, 80, 20,

        hwnd,

        NULL,

        hThisInstance,

        NULL);
    niebieski = CreateWindowEx(

        0,

        _T("BUTTON"),

        _T("BLUE"),

        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

        280, 10, 80, 20,

        hwnd,

        NULL,

        hThisInstance,

        NULL);
    prostokat = CreateWindowEx(

        0,

        _T("BUTTON"),

        _T("PROSTOKAT"),

        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

        370, 10, 80, 20,

        hwnd,

        NULL,

        hThisInstance,

        NULL);
    linia = CreateWindowEx(

        0,

        _T("BUTTON"),

        _T("LINIA"),

        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

        460, 10, 80, 20,

        hwnd,

        NULL,

        hThisInstance,

        NULL);
    krzywa = CreateWindowEx(

        0,

        _T("BUTTON"),

        _T("KRZYWA"),

        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

        10, 35, 80, 20,

        hwnd,

        NULL,

        hThisInstance,

        NULL);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /*OBECNY PROGRESS!!!!!!*/
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //od tad
    //HANDLE czaIkona = LoadImage(hThisInstance, MAKEINTRESOURCE(IDR_BUTTON), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    //SendMessage(czarny, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)czaIkona);
    //do tad nie dziala

    /*hText = CreateWindowEx(

        0,

        _T("EDIT"),

        NULL,

        WS_CHILD | WS_VISIBLE | WS_BORDER,

        50, 20, 150, 25,

        hwnd,

        NULL,

        hThisInstance,

        NULL);*/

        /* Make the window visible on the screen */

    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */

    while (GetMessage(&messages, NULL, 0, 0))

    {

        /* Translate virtual-key messages into character messages */

        TranslateMessage(&messages);

        /* Send message to WindowProcedure */

        DispatchMessage(&messages);

    }



    /* The program return-value is 0 - The value that PostQuitMessage() gave */

    return messages.wParam;

}


/*  This function is called by the Windows function DispatchMessage()  */

/*void rysuj(HWND hwnd)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HPEN kolorpisaka, apka, czarnykolor;
    hdc = BeginPaint(hwnd, &ps);

    kolorpisaka = CreatePen(PS_DASHDOTDOT, 2, 0x11AAFF);
    SelectObject(hdc, kolorpisaka);

    MoveToEx(hdc, 50, 50, NULL);
    for (int i = 0; i < 50; i++)
    {
        LineTo(hdc, i + 50, i * i / 80 + 50);
    }
    czarnykolor = CreatePen(PS_DASHDOT, 8, 0xDD3300);
    SelectObject(hdc, czarnykolor);
    MoveToEx(hdc, 50, 50, NULL);

    LineTo(hdc, 50, 100);
    LineTo(hdc, 100, 100);
    LineTo(hdc, 50, 50);

    MoveToEx(hdc, 150, 150, NULL);
    SelectObject(hdc, kolorpisaka);
    Ellipse(hdc, 250, 100, 20, 20);
    ////////////////////////////////////////////////*/
    /*HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);
    */
    /*    EndPaint(hwnd, &ps);
    }*/

int tool = 0;  //zmieniany po wcisnieciu przycisku, determinuje typ rysowanego obiektu
//dla 0 krzywe, dla 1 prostokaty, dla 2 linia prosta
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

{
    bool spr;
    switch (message) /* handle the messages */
    {      //////////////////////
    case WM_LBUTTONDOWN:					//If Left mouse button is pressed
        lastx = LOWORD(lParam);			//Store the x-coordiante in lastx
        lasty = HIWORD(lParam);			//Store the y-coordinate in lasty
        return 0;
    case WM_LBUTTONUP:						//When mouse is moved on the client area (or form for VB users)
        hdc = GetDC(hwnd);					//hdc is handle to device context
        x = LOWORD(lParam);					//Store the current x 
        y = HIWORD(lParam);					//Store the current y
        //if (wParam & MK_LBUTTON)			//If Left mouse button is down then draw
        //{
            //line(hdc, lastx, lasty, x, y, kolorpisaka);		//Draw the line frome the last pair of coordiates to current
        if (tool == 1)
        {
            rectangle(hdc, lastx, lasty, x, y, kolorpisaka);
            data_from_last_sec.push_back(1);
            data_from_last_sec.push_back(lastx);
            data_from_last_sec.push_back(lasty);
            data_from_last_sec.push_back(x);
            data_from_last_sec.push_back(y);
            data_from_last_sec.push_back(colour);
            DebugDataSave(&seconds_since_last_data_save, &data_from_last_sec);
        }
        if (tool == 2)
        {
            line(hdc, lastx, lasty, x, y, kolorpisaka);
            data_from_last_sec.push_back(2);
            data_from_last_sec.push_back(lastx);
            data_from_last_sec.push_back(lasty);
            data_from_last_sec.push_back(x);
            data_from_last_sec.push_back(y);
            data_from_last_sec.push_back(colour);
            DebugDataSave(&seconds_since_last_data_save, &data_from_last_sec);
        }
        //lastx = x;						//The current x becomes the lastx for next line to be drawn
        //lasty = y;						//The current y becomes the lasty for next line to be drawn
    //}
        ReleaseDC(hwnd, hdc);
        return 0;
    case WM_MOUSEMOVE:						//When mouse is moved on the client area (or form for VB users)
        hdc = GetDC(hwnd);					//hdc is handle to device context
        x = LOWORD(lParam);					//Store the current x 
        y = HIWORD(lParam);					//Store the current y
        if (wParam & MK_LBUTTON)			//If Left mouse button is down then draw
        {
            if (tool == 0)
            {
                line(hdc, lastx, lasty, x, y, kolorpisaka);		//Draw the line frome the last pair of coordiates to current
                lastx = x;						//The current x becomes the lastx for next line to be drawn
                lasty = y;						//The current y becomes the lasty for next line to be drawn
                data_from_last_sec.push_back(0);
                data_from_last_sec.push_back(lastx);
                data_from_last_sec.push_back(lasty);
                data_from_last_sec.push_back(x);
                data_from_last_sec.push_back(y);
                data_from_last_sec.push_back(colour);
                DebugDataSave(&seconds_since_last_data_save, &data_from_last_sec);
            }
            ReleaseDC(hwnd, hdc);
            return 0;
        }
        /////////////////
    case WM_KEYDOWN:
        if (wParam == VK_RETURN)
        {
            MessageBox(NULL, __T("TEXT"), __T("Drugi?"), MB_OK);
            break;
        }
        /*if (wParam == VK_F10)
        {

            rysuj(hwnd);
        }*/
        break;
        /*case WM_PAINT:



            break;*/
    case WM_DESTROY:
        PostQuitMessage(0); /* send a WM_QUIT to the message queue */
        break;
    case WM_COMMAND:
		if (LOWORD(wParam) == IDM_EXIT)	PostQuitMessage(0);
		if (LOWORD(wParam) == ID_WIDOK_ROZMIAROKNA) { }
		if (LOWORD(wParam) == IDM_ABOUT)	MessageBox(hwnd, _T("Q: Co to jest?\nA: Bardzo Fajny Program do rysowania śmiesznych kształtów.\n\nQ: Kto to zrobił?\nA: Team Zdolnych z Pomorza 2020/21.\n\nQ: Nie działa!!!11\nA: Proszę złożyć zażalenie do skrzynki na zażalenia.\n\nQ: Kto pisze to FAQ a powinien już spać?\nA: koniec pytań"), _T("FAQ"), MB_ICONINFORMATION);
		if (HWND(lParam) == czarny && HIWORD(wParam) == BN_CLICKED)
        {
            kolorpisaka = CreatePen(PS_DASHDOTDOT, 2, 0x000000);
            colour = 0;
            //SelectObject(hdc, kolorpisaka);
            //MessageBox(NULL, _T("result"), _T("b1"), NULL);

        }
        if (HWND(lParam) == czerwony && HIWORD(wParam) == BN_CLICKED)
        {
            kolorpisaka = CreatePen(PS_DASHDOTDOT, 2, 0x0000AA);
            colour = 1;
            //SelectObject(hdc, kolorpisaka);
        }
        if (HWND(lParam) == zielony && HIWORD(wParam) == BN_CLICKED)
        {
            colour = 2;
            kolorpisaka = CreatePen(PS_DASHDOTDOT, 2, 0x00AA00);
            //SelectObject(hdc, kolorpisaka);
        }
        if (HWND(lParam) == niebieski && HIWORD(wParam) == BN_CLICKED)
        {
            colour = 3;
            kolorpisaka = CreatePen(PS_DASHDOTDOT, 2, 0xAA0000);
            //SelectObject(hdc, kolorpisaka);
        }
        if (HWND(lParam) == krzywa && HIWORD(wParam) == BN_CLICKED)
        {
            tool = 0;
        }
        if (HWND(lParam) == prostokat && HIWORD(wParam) == BN_CLICKED)
        {
            tool = 1;
            //MessageBox(NULL, _T("result"), _T("b1"), NULL);
            //kolorpisaka = CreatePen(PS_DASHDOTDOT, 2, 0xAA0000);
            //SelectObject(hdc, kolorpisaka);
        }
        if (HWND(lParam) == linia && HIWORD(wParam) == BN_CLICKED)
        {
            tool = 2;
            //kolorpisaka = CreatePen(PS_DASHDOTDOT, 2, 0xAA0000);
            //SelectObject(hdc, kolorpisaka);
        }
        
        ////


    default: /* for messages that we don't deal with */

        return DefWindowProc(hwnd, message, wParam, lParam);

    }

    return 0;

}