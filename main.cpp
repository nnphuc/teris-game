#include <iostream>


#include "console.cpp"
#include "shape.h"
#include <windows.h>
#include <time.h>

using namespace std;

int line=0;
bool rotate(Shape &board,Shape &s){
    Shape tmp=s;
    tmp.rotate();
    if(tmp.crashShape(board)|| s.getX()<0|| s.getX()+s.getWidth()>board.getWidth()) return false;
    s.rotate();
    return true;
}

bool move(Shape &board,Shape &s,int dx,int dy){
    Shape tmp=s;
    tmp.move(dx,dy);
    if(tmp.crashShape(board)|| tmp.getX()<0 || tmp.getX()+tmp.getWidth()>board.getWidth()
        || tmp.getHeight()+tmp.getY()>board.getHeight()) return false;
    s.move(dx,dy);
}

bool check_row(Shape &board,int i){
    for(int j=0;j<board.getWidth();j++){
        if(board.get(i,j)==Shape::NONE) return false;
    }
    return true;
}



bool eat(Shape &board,Shape &s){
    Shape tmp=s;
    tmp.move(0,1);
    if(tmp.crashShape(board)|| tmp.getHeight()+tmp.getY()>board.getHeight()){
        for(int i=0;i<s.getHeight();i++){
            for(int j=0;j<s.getWidth();j++){
                int ty=i+s.getY();
                int tx=j+s.getX();
                if(s.get(i,j)!=Shape::NONE)
                    board.set(ty,tx,s.get(i,j));
            }
        }
        reverse(board.matrix.begin(),board.matrix.end());
        int del_cnt=0;
        for(int i=0;i<board.matrix.size();i++){
            if(check_row(board,i)){
                del_cnt++;
            }else{
                board.matrix[i-del_cnt]=board.matrix[i];
            }
        }
        line+=del_cnt;
        for(int i=0;i<del_cnt;i++){
            board.matrix[board.matrix.size()-1-i]=vector<int>(board.getWidth(),-1);
        }
        reverse(board.matrix.begin(),board.matrix.end());
        return true;
    }


    return false;

}

int main()
{
    system("cls");
    Console con("xep hinh");

    con.setCursor(false);
    con.setBackground(con.WHITE);
    Shape board(20,10,Shape::NONE);
    Shape nextBoard(4,4,Shape::NONE);

    Shape L(3,2,con.LIGHT_RED);
    L.set(0,1,-1);
    L.set(1,1,-1);
    Shape T(2,3,con.BLUE);
    T.set(1,0,-1);
    T.set(1,2,-1);
    Shape I(1,4,con.LIGHT_YELLOW);
    Shape O(2,2,con.AQUA);
    Shape Z(3,2,con.GREEN);
    Z.set(0,0,-1);
    Z.set(2,1,-1);

    Shape S(3,2,con.LIGHT_PURPLE);
    S.set(2,0,-1);
    S.set(0,1,-1);

    const Shape sh[]={I,T,L,S,Z,O};
    Shape cur;
    Shape next;
    srand(time(NULL));
    cur=sh[rand()%6];
    next=sh[rand()%6];
    int tick=0;
    int Draw=20;
    cur.setX(4);
    next.setX(4);
    nextBoard.setX(20);
    nextBoard.setY(5);
    nextBoard.draw(con);
    next.setX(20);
    next.setY(5);
    next.draw(con);
    con.setTextColor(con.BLACK);
    int level=0;

    while(true){

        if(tick%Draw==0){
            con.gotoXY(20,12);
            printf("           ");
            con.gotoXY(20,12);
            printf("score: %d",line);
            board.draw(con);
            cur.draw(con);
            level=line/10;
            con.gotoXY(20,13);
            printf("           ");
            con.gotoXY(20,13);
            printf("level: %d",level+1);
            Draw=25-level;
            tick=0;
        }

        if(_kbhit()){
            int ch=getch();
            if(ch==224){
                switch(ch=getch()){
                case 72:
                    rotate(board,cur);break;
                case 75:move(board,cur,-1,0);break;
                case 77:move(board,cur,1,0);break;
                case 80:move(board,cur,0,1); break;
                }

            }
        }
        if(tick==0){
             move(board,cur,0,1);
        }
        bool canEat=eat(board,cur);
        tick++;
        if(canEat){
            if(cur.getY()==0){
                break;
            }
            cur=next;
            cur.setX(4);
            cur.setY(0);

            next=sh[rand()%6];
            nextBoard.draw(con);
            next.setX(20);
            next.setY(5);
            next.draw(con);
            tick=1;
            //FlushConsoleInputBuffer(con.getHandle());

        }
        Sleep(10);

    }

    return 0;
}
