//
//  stack.hpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp
#include "frame.hpp"
#include "tools.hpp"
//----------------------------------------
template <class T>
class Stack : vector<Frame*>{
public:
    Stack() = default;
    ~Stack() = default;
    inline void pop(){ vector::pop_back();}
    inline Frame* top(){ return vector::back();}
    inline void push(Frame* f){ vector::push_back(f);}
    inline int size(){ return (int)vector::size();}
    inline void zap(){ vector::clear();}
};

//----------------------------------------
#endif /* stack_hpp */
