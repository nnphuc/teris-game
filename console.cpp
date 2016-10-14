
#include "console.h"

Console::Console(){
    m_handle=GetStdHandle(STD_OUTPUT_HANDLE);
    setCursor(false);
}

Console::Console(char *title){
    SetConsoleTitle(_T(title));
    m_handle=GetStdHandle(STD_OUTPUT_HANDLE);
    setCursor(false);
}
HANDLE Console::getHandle(){
    return m_handle;
}

void Console::setTitle(char *title){
    SetConsoleTitle(_T(title));
}

int Console::getWidth(){
    CONSOLE_SCREEN_BUFFER_INFO buff;
    GetConsoleScreenBufferInfo(m_handle,&buff);
    int width=buff.srWindow.Right-buff.srWindow.Left+1;
    return width;
}

int Console::getHeight(){
    CONSOLE_SCREEN_BUFFER_INFO buff;
    GetConsoleScreenBufferInfo(m_handle,&buff);
    int height=buff.srWindow.Bottom-buff.srWindow.Top+1;
    return height;
}

bool Console::gotoXY(int x,int y){
    if(x<0 or x>= getWidth() or y<0 or y>=getHeight()) return false;
    COORD coord={.X=SHORT(x),.Y=SHORT(y)};
    SetConsoleCursorPosition(m_handle,coord);
    return true;
}

void Console::write(char *s){
    printf("%s",s);
}

void Console::write(int c){
    putchar(c);
}

bool Console::getCursor(){
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(m_handle,&cursor);
    return cursor.bVisible;
}

void Console::setCursor(bool visible){

    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(m_handle,&cursor);
    cursor.bVisible=visible;
    SetConsoleCursorInfo(m_handle,&cursor);
}

void Console::setTextAttr(int textColor,int backgroundColor){
    SetConsoleTextAttribute(m_handle,textColor+16*backgroundColor);
}

void Console::setTextColor(int color){
    CONSOLE_SCREEN_BUFFER_INFO buff;
    GetConsoleScreenBufferInfo(m_handle,&buff);
    buff.wAttributes=(buff.wAttributes&0xF0)|color;
    SetConsoleTextAttribute(m_handle,buff.wAttributes);
}
void Console::setBackground(int color){
    CONSOLE_SCREEN_BUFFER_INFO buff;
    GetConsoleScreenBufferInfo(m_handle,&buff);
    buff.wAttributes=(buff.wAttributes&0xF)|(color<<4);
    SetConsoleTextAttribute(m_handle,buff.wAttributes);
}

void Console::clear(){
    COORD topLeft  = { 0, 0 };

    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(m_handle, &screen);
    FillConsoleOutputCharacterA(
        m_handle, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        m_handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(m_handle, topLeft);
}


int Console::getX(){
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if (!GetConsoleScreenBufferInfo(
         m_handle,
         &csbi
         ))
    return -1;
  return csbi.dwCursorPosition.X;
}

int Console::getY(){
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(
         m_handle,
         &csbi
         ))
    return -1;
   return csbi.dwCursorPosition.Y;
}

int Console::getTextColor(){
    CONSOLE_SCREEN_BUFFER_INFO buff;
    GetConsoleScreenBufferInfo(m_handle,&buff);
    return buff.wAttributes&0xF;
}
int Console::getBackground(){
    CONSOLE_SCREEN_BUFFER_INFO buff;
    GetConsoleScreenBufferInfo(m_handle,&buff);
    return buff.wAttributes>>4;

}
