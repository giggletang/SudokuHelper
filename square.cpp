//
//  square.cpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//


#include "cluster.hpp"
//----------------------------------------------
char Square::getMarkChar() const{
    return status.getvalue();
}

//----------------------------------------------
string Square::getPossibilityString() const{
    ostringstream os;
    status.print(os);
    string Pos = os.str();
    return Pos;
}

//-----------------------------------------------
void Square::shoop(){
    if(isdigit(status.getvalue())){
        for( Cluster* cl : clues){
            cl->shoop(status.getvalue());
        }
    }
}

//-----------------------------------------------
ostream& Square::print(ostream& out) const{
    out << "Square" << " [" << row << "," << column << "] ";
    out << " Value:" << status.getvalue();
    out << " Possible:";
    status.print(out);
    return out;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
State::State(char val, int n){
    N = n;
    value = val;
    if(isdigit(val)){
        possibilities = 0;
        fixed = true;
    }
}

//-----------------------------------------------------
void State::mark(char ch){
    if(possibilities){
        value = ch;
        possibilities = 0;
        fixed = true;
    }
    else{
        cout << " Error, this state can't be marked." << endl;
    }
}

//------------------------------------------------------
ostream& State::print(ostream& out) const{
    short possible = possibilities;
    short mask = 1;
    for(int k =1; k<=9; ++k){
        if((N==6)&&(k>6)) out << " ";
        else{
            if((mask & (possible>>1)) == 0) out << "-";
            else out << k;
            possible >>= 1;
        }
    }
    return out << endl;

}
//-----------------------------------------------------



