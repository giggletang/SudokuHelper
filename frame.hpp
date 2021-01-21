//
//  frame.hpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//

#ifndef frame_hpp
#define frame_hpp
#include "board.hpp"

//----------------------------------
class Frame{
private:
    State st[81];
    int N;

public:
    inline State& operator[] (int k){
        return st[k];
    }
    Frame(Board* bp, int n){
        N = n;
        int p=0;
        for(int j=1; j<=N; ++j){
            for(int k=1; k<=N; ++k){
                st[p] = bp->copyState(j,k);
                ++p;
            }
        }
    }
    Frame() = default;
    ~Frame() = default;
    State sub( int j, int k ) const{ return st[(j-1)*N+(k-1)];}
    void serialize( ofstream& gameOut, int n){
        N = n;
        int k = N*N;
        for(int m=0; m<k; ++m){
            gameOut.write((char*)& st[m],sizeof(st[m]));
        }
    }
    void realize( ifstream& gameIn, int n){
        N = n;
        int k = N*N;
        for(int m=0; m<k; ++m){
            gameIn.read((char*)& st[m], sizeof(st[m]));
        }
    }
};

//------------------------------------------
#endif /* frame_hpp */
