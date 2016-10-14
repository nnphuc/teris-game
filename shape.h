#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include "console.h"

class Shape{

public:
    Shape(){
        x=y=0;
    }
    Shape(int m,int n,int v=NONE){
        x=y=0;
        matrix.resize(m,vector<int>(n,v));
    }

    int getWidth(){
        return matrix.size()?matrix[0].size():0;
    }
    int getHeight(){
        return matrix.size();
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    void setX(int x){
        this->x=x;
    }
    void setY(int y){
        this->y=y;
    }
    bool crashShape(Shape &other){
        for(int i=0;i<getHeight();i++){
            for(int j=0;j<getWidth();j++){
                if(matrix[i][j]==NONE) continue;
                int tx=x+j;
                int ty=y+i;
                int jj=tx-other.x;
                int ii=ty-other.y;
                if(ii>=0 and jj>=0 and ii<other.getHeight() and jj<other.getWidth() and other.matrix[ii][jj]!=NONE){
                    return true;
                }
            }
        }
        return false;
    }
    void move(int dx,int dy){
        x+=dx;
        y+=dy;
    }
    void moveTo(int x,int y){
        this->x=x;
        this->y=y;
    }

    void rotate(){ //left
        int m=getWidth(),n=getHeight();
        vector<vector<int>> temp(m,vector<int>(n,0));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                temp[i][j]=matrix[j][m-i-1];
            }
        }

        matrix=temp;
        x-=n-getHeight();
        y-=m-getWidth();
        if(x<=0) x=0;
    }


    void draw(Console &console){
        int lastBackground=console.getBackground();
        for(int i=0;i<getHeight();i++){
            for(int j=0;j<getWidth();j++){
                int tx=j+x;
                int ty=i+y;

                if(tx<0 or tx>=console.getWidth() or ty<0 or ty>=console.getHeight()){
                    continue;
                }

                if(matrix[i][j]==NONE){
                    console.setBackground(lastBackground);
                    console.gotoXY(tx,ty);
                    console.write(' ');
                }else{
                    console.setBackground(matrix[i][j]);
                    console.gotoXY(tx,ty);
                    console.write(' ');
                }

            }
        }
        console.setBackground(lastBackground);
    }

    void clear(Console &console){
        int lastBackground=console.getBackground();
        for(int i=0;i<getHeight();i++){
            for(int j=0;j<getWidth();j++){
                int tx=j+x;
                int ty=i+y;

                if(tx<0 or tx>=console.getWidth() or ty<0 or ty>=console.getHeight()){
                    continue;
                }


                console.setBackground(lastBackground);
                console.gotoXY(tx,ty);
                console.write(' ');


            }
        }
        console.setBackground(lastBackground);
    }
    static const int NONE=-1;
    void set(int y,int x,int w){
        matrix[y][x]=w;
    }
    int get(int y,int x){
        return matrix[y][x];
    }
    vector<vector<int>> matrix;
private:

    int x,y;

};


#endif // SHAPE_H_INCLUDED
