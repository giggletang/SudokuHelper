//
//  main.cpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//

#include "tools.hpp"
#include "game.hpp"

//------------------------------------
int main(int argc, char* argv[]) {
    banner();
    try{
        Game g(argv[1]);
        g.run();
    }
    catch (LogicError& le){
        le.print();
    }
    catch (StreamError& se){
        se.print();
    }
    catch (MoveError& me){
        me.print();
    }
    catch (bad_alloc ba){
        cerr << "  Allocation error for puzzle board.\n";
        return 1;
    }
    catch (...){
        cerr << "  Last-ditch effort to catch exceptions.\n";
    }
    bye();
    return 0;
}

//------------------------------------

