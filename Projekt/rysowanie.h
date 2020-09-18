#pragma once
//plik naglowkowy z funkcjami rysujacymi

void line(HDC _hdc, int x1, int y1, int x2, int y2, HPEN kolor)
{
    SelectObject(_hdc, kolor);
    MoveToEx(_hdc, x1, y1, NULL);
    LineTo(_hdc, x2, y2);
}

void ellipse(HDC _hdc, int x1, int y1, int x2, int y2, HPEN kolor)
{
    SelectObject(_hdc, kolor);
    //MoveToEx(_hdc, x1, y1, NULL);
    Ellipse(_hdc, x1, y1, x2, y2);
}

void rectangle(HDC _hdc, int x1, int y1, int x2, int y2, HPEN kolor)
{
    SelectObject(_hdc, kolor);
    //MoveToEx(_hdc, x1, y1, NULL);
    //Rectangle(_hdc, x1, y1, x2, y2);
    MoveToEx(_hdc, x1, y1, NULL);
    LineTo(_hdc, x1, y2);
    LineTo(_hdc, x2, y2);
    LineTo(_hdc, x2, y1);
    LineTo(_hdc, x1, y1);
}