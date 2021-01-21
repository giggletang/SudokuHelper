//
//  cluster.hpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//

#ifndef cluster_hpp
#define cluster_hpp
#include "square.hpp"
#include "tools.hpp"

//---------------------------------
enum ClusterT{
    row = 0,
    column,
    box,
    diagonal
};

//-------------------------------------------------------------
class Cluster{
private:
    const char* printType;
    Square** joint;
    int N;
    
public:
    ~Cluster(){ delete joint;}
    Cluster(ClusterT Ctype, Square** j, int n);
    ostream& print(ostream& out) const;
    void shoop(char val);
};
inline ostream& operator<< (ostream& out, Cluster& cl){
    cl.print(out);
    return out;
}

//---------------------------------------------------------------
#endif /* cluster_hpp */
