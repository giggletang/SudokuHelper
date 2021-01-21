//
//  board.hpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//


#ifndef board_hpp
#define board_hpp
#include "tools.hpp"
#include "cluster.hpp"
#include "exception.hpp"
#include "CanView.hpp"
class Frame;
//------------------------------------------------
class Board : public CanView{
protected:
    int N;
    char type;
    Square* bd;
    ifstream& myin;
    void getPuzzle() throw (LineError, GoodError, LongError, ShortError);
    
    vector <Cluster*> clues;
    void makeClusters();
    void createRow(short j);
    void createColumn(short k);

public:
    ~Board(){
        delete[] bd;
        cerr << " Deleting "<< N << "*" << N <<" Board" << endl;}
    Board(int n, char t, ifstream& puzfile): N(n), type(t), myin(puzfile){
        bd = new Square[N*N];
        getPuzzle();
        makeClusters();
        cerr << " Board " << N << "*" << N << " constructed." <<endl;
    }
    Square& sub( int j, int k ) const{ return bd[(j-1)*N+(k-1)];}
    ostream& print(ostream& out) const;
    void shoop();
    void mark(int row, int col, char val){ sub(row, col).mark(val);}
    char getMarkChar(int row, int col) const{
        return sub(row, col).getMarkChar();
    }
    string getPossibilityString(int row, int col) const{
        return sub(row, col).getPossibilityString();
    }
    State copyState(int row, int col) const{
        return sub(row, col).copyState();
    }
    void turnOff(int row, int col, int n){ sub(row, col).turnOff(n);}
    void restoreState(Frame* f);
   
};
inline ostream& operator<< (ostream& out, Board& b){
    b.print(out);
    return out;
}

//---------------------------------------
class SixyBoard : public Board{
private:
    void makeBox();
    void createHBox(short j, short k);
    void createVBox(short j, short k);

public:
    SixyBoard(int n, char t, ifstream& puzfile): Board(n, t, puzfile){
        makeBox();
        cerr << " SixyBoard " << N << "*" << N << " constructed." <<endl;
    }
    ~SixyBoard() = default;
};

//--------------------------------------------------
class TradBoard : public Board{
private:
    void makeBox();
    void createBox(short j, short k);
    
public:
    TradBoard(int n, char t, ifstream& puzfile): Board(n, t, puzfile){
        makeBox();
        cerr << " TradBoard " << N << "*" << N << " constructed." <<endl;
    }
    ~TradBoard() = default;
};
//---------------------------------------
class DiagBoard : public TradBoard{
private:
    void createDiagonal();
    
public:
    DiagBoard(int n, char t, ifstream& puzfile): TradBoard(n, t, puzfile){
        createDiagonal();
        cerr << " DiagBoard " << N << "*" << N << " constructed." <<endl;
    }
    ~DiagBoard() = default;
    
};
//-----------------------------------------------------------------------
#endif /* board_hpp */
