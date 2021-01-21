//
//  board.cpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//


#include "board.hpp"
#include "frame.hpp"

//-------------------------------------------
void SixyBoard::makeBox(){
    for(short j=1; j<=N; j+=2){
        for(short k=1; k<=N; k+=3){
            createHBox(j,k);
        }
    }
    for(short j=1; j<=N; j+=3){
        for(short k=1; k<=N; k+=2){
            createVBox(j,k);
        }
    }
}
//-------------------------------------------
void SixyBoard::createHBox(short j, short k){
    Square* temp[N];
    short n=0;
    for(short a=j; a<j+2; a++){
        for(short b=k; b<k+3; b++){
            temp[n] = &sub(a,b);
            n++;
        }
    }
    Cluster* pcl = new Cluster(box, temp, N);
    clues.push_back(pcl);
}

//-------------------------------------------
void SixyBoard::createVBox(short j, short k){
    Square* temp[N];
    short n=0;
    for(short a=j; a<j+3; a++){
        for(short b=k; b<k+2; b++){
            temp[n] = &sub(a,b);
            n++;
        }
    }
    Cluster* pcl = new Cluster(box, temp, N);
    clues.push_back(pcl);
    
}

//-------------------------------------------------
//-------------------------------------------------
void TradBoard::makeBox(){
    for(short j=1; j<=N; j+=3){
        for(short k=1; k<=N; k+=3){
            createBox(j,k);
        }
    }
}
//-------------------------------------------
void TradBoard::createBox(short j, short k){
    Square* temp[N];
    short n=0;
    for(short a=j; a<j+3; a++){
        for(short b=k; b<k+3; b++){
            temp[n] = &sub(a,b);
            n++;
        }
    }
    Cluster* pcl = new Cluster(box, temp, N);
    clues.push_back(pcl);
}

//----------------------------------------------------
//----------------------------------------------------
void DiagBoard::createDiagonal(){
    Square* temp[N];
    Cluster* pcl;
    for(short j=1; j<=N; ++j){
        temp[j-1] = &sub(j,j);
    }
    pcl = new Cluster(diagonal, temp, N);
    clues.push_back(pcl);
    
    for(short k=1; k<=N; ++k){
        temp[k-1] = &sub(k,10-k);
    }
    pcl = new Cluster(diagonal, temp, N);
    clues.push_back(pcl);
}

//-----------------------------------------------------------
//-----------------------------------------------------------
void Board::makeClusters(){
    for(short j=1; j<=N; ++j){
        createRow(j);
    }
    for(short k=1; k<=N; ++k){
        createColumn(k);
    }
}
//--------------------------------------------
void Board::createRow(short j){
    Square* temp[N];
    for (short k=1; k<=N; ++k){
        temp[k-1] = &sub(j,k);
    }
    Cluster* pcl = new Cluster(row, temp, N);
    clues.push_back(pcl);
}

//--------------------------------------------
void Board::createColumn(short k){
    Square* temp[N];
    for(short j=1; j<=N; ++j){
        temp[j-1] = &sub(j,k);
    }
    Cluster* pcl = new Cluster(column, temp, N);
    clues.push_back(pcl);
}

//------------------------------------------------------------
void Board::getPuzzle() throw (LineError, GoodError, LongError, ShortError){
    char input;
    myin.get(input);
    if(!myin.good()) throw GoodError();
    for(int j=1; j<=N; ++j){
        for(int k=1; k<=N; ++k){
            if (myin.eof()) throw ShortError();
            myin >> noskipws >>input;
            sub(j,k) = Square(State(input,N), j, k);
            if(k == N){
                myin.get(input);
                if(input != '\n') throw LineError(N, type);
            }
        }
    }
    myin.get(input);
    if (!myin.eof()) throw LongError();
}

//---------------------------------------------
void Board::shoop(){
    for(int p=0; p<N*N; ++p){
        bd[p].shoop();
    }
}

//----------------------------------------------
ostream& Board::print(ostream& out) const{
    for( Cluster* cl : clues){
        cl->print(out);
    }
    return out;
}

//--------------------------------------------
void Board::restoreState(Frame* f){
    for(int j=1; j<=N; ++j){
        for(int k=1; k<=N; ++k){
            sub(j,k) = Square(f->sub(j,k), j, k);
        }
    }
}

//-----------------------------------------------
