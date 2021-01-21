//
//  square.hpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//


#ifndef square_hpp
#define square_hpp
#include "tools.hpp"

class Cluster;
//---------------------------------------------------
class State{
private:
    char value;
    short possibilities = 0x3fe;
    bool fixed = false;
    int N;
    
public:
    State() = default;
    ~State() = default;
    State(char val, int n);
    void mark(char ch);
    char getvalue(void) const{return value;}
    void turnOff(int n){ possibilities = possibilities & ~(1 << n);}
    ostream& print(ostream& out) const;
};
inline ostream& operator<< (ostream& out, State& st){
    st.print(out);
    return out;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class Square{
private:
    State status;
    short row;
    short column;
    vector <Cluster*> clues;
    
public:
    Square() = default;
    Square(State st, short ro, short col): status(st), row(ro), column(col){}
    ~Square() = default;
    void mark(char ch){ status.mark(ch); shoop();}
    ostream& print(ostream& out) const;
    inline void addCluster(Cluster* clPointer){ clues.push_back(clPointer);}
    void shoop();
    void turnOff(int n){ status.turnOff(n);}
    char getMarkChar() const;
    string getPossibilityString() const;
    State copyState() const{ State st = status; return st;};
};
inline ostream& operator<< (ostream& out, Square& sq){
    sq.print(out);
    return out;
}

//--------------------------------------------------------
#endif /* square_hpp */

