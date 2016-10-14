#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <windows.h>
#include <conio.h>
#include <bits/stdc++.h>
#include <tchar.h>
using namespace std;

class Console {
public:
    Console();
    Console(char *);
    bool gotoXY(int ,int );
    void setTitle(char *);
    int getWidth();
    int getHeight();
    void write(char *);
    void write(int );
    bool getCursor();
    void setCursor(bool);
    void setTextAttr(int ,int);
    void clear();
    int getX();
    int getY();
    void setTextColor(int);
    void setBackground(int);
    int getBackground();
    int getTextColor();
    HANDLE getHandle();


    const static int DEFAULT=7;
    const static int BLACK=0;
    const static int BLUE=1;
    const static int GREEN=2;
    const static int AQUA=3;
    const static int RED=4;
    const static int PURPEL=5;
    const static int YELLOW=6;
    const static int LIGHT_GRAY=7;
    const static int GRAY=8;
    const static int LIGHT_BLUE=9;
    const static int LIGHT_GREEN=10;
    const static int LIGHT_AQUA=11;
    const static int LIGHT_RED=12;
    const static int LIGHT_PURPLE=13;
    const static int LIGHT_YELLOW=14;
    const static int WHITE=15;
private:
    HANDLE m_handle ;


};

#endif // CONSOLE_H_INCLUDED
