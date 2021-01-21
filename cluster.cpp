//
//  cluster.cpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//


#include "cluster.hpp"
static const char* ClusterType[4] = {"Row", "Column", "Box", "Diagonal"};
//--------------------------------------------------
Cluster::Cluster(ClusterT Ctype, Square** j, int n){
    N = n;
    this->printType = ClusterType[Ctype];
    joint = new Square*[N];
    for(int k=0; k<N; ++k){
        this->joint[k] = j[k];
        joint[k]->addCluster(this);
    }
}

//--------------------------------------------------
ostream& Cluster::print(ostream& out) const{
    out << printType << endl;
    for(int k=0; k<N; ++k){
        joint[k]->print(out);
    }
    return out << "\n";
}

//---------------------------------------------------
void Cluster::shoop(char val){
    int value = val - '0';
    for (int k=0; k<N; ++k){
        joint[k]->turnOff(value);
    }
}

//----------------------------------------------------
