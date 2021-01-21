//
//  game.hpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//

#ifndef game_hpp
#define game_hpp
#include "board.hpp"
#include "exception.hpp"
#include "Viewer.hpp"
#include "stack.hpp"

//------------------------------------
class Game{
private:
    const char* menu[7] = {
        "Move", "Turn off", "Undo", "Redo", "Save game", "Game restore", "Quit and discard game"
    };
    Board* boardp;
    int size = 0;
    char type = 'N';
    ifstream myin;
    Stack<State> un;
    Stack<State> re;
    
public:
    ~Game(){ delete boardp;}
    Game(string filename) throw (TypeError, SizeError, LineError, OpenError, GoodError, LongError, ShortError);
    void run();
    void move() throw (FixError, PossibleError);
    void turnOff()throw (FixError,PossibleError);
    void undo()throw (UndoError);
    void redo()throw (RedoError);
    void save();
    void restore();
};

//----------------------------------------------
#endif /* game_hpp */

