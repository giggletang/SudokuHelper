//
//  game.cpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//


#include "game.hpp"
//----------------------------------
Game::Game(string filename) throw (TypeError, SizeError, LineError, OpenError, GoodError, LongError, ShortError){
    char typecode;
    const string valid = "DdTtSs";
    myin.open(filename);
    if (!myin.is_open()) throw OpenError();
    myin >> typecode;
    if (valid.find_first_of(typecode) != string::npos) {
        type = typecode;
        if(type == 's'){
            size = 6;
            boardp = new SixyBoard(size, type, myin);
        }
        if(type == 't'){
            size = 9;
            boardp = new TradBoard(size, type, myin);
        }
        if(type == 'd'){
            size = 9;
            boardp = new DiagBoard(size, type, myin);
        }
        boardp->shoop();
        Frame* f = new Frame(boardp, size);
        un.push(f);
        Viewer fancyView(size, size, *boardp);
        fancyView.show(cout);
    }
    if (type == 'N') throw TypeError(size, type);
    if (size == 0) throw SizeError(size, type);
    myin.close();
}

//----------------------------
void Game::run(){
    char choice;
    for(;;){
        choice = menu_c ( "Sudoku Helper", 7, menu, "MmTtUuRrSsGgQq");
        switch(toupper(choice)){
            case 'M':
                move();
                break;
            case 'T':
                turnOff();
                break;
            case 'U':
                undo();
                break;
            case 'R':
                redo();
                break;
            case 'S':
                save();
                break;
            case 'G':
                restore();
                break;
            case 'Q':
                cout << " Thank you, Bye" << endl;
                exit(0);
        }
    }
}

//------------------------------------------------------
void Game::move() throw (FixError, PossibleError){
    int row;
    int col;
    char val;
    cout << " Input row: ";
    cin >> row;
    cout << " Input column: ";
    cin >> col;
    cout << " Input value: ";
    cin >> val;
    
    if(isdigit(boardp->getMarkChar(row,col))) throw FixError(row, col);
    if(boardp->getPossibilityString(row, col).find_first_of(val) == string::npos) throw PossibleError(row, col);
    
    boardp->mark(row, col, val);
    Frame* f = new Frame(boardp, size);
    un.push(f);
    re.zap();
    Viewer fancyView(size, size, *boardp);
    fancyView.show(cout);
}
//--------------------------------------
void Game::turnOff() throw (FixError,PossibleError){
    int row;
    int col;
    char val;
    cout << " Input row: ";
    cin >> row;
    cout << " Input column: ";
    cin >> col;
    cout << " Input which number you want turn off: ";
    cin >> val;
    
    if(isdigit(boardp->getMarkChar(row,col))) throw FixError(row, col);
    if(boardp->getPossibilityString(row, col).find_first_of(val) == string::npos) throw PossibleError(row, col);
    
    int bit = val - '0';
    boardp->turnOff(row, col, bit);
    Frame* f = new Frame(boardp, size);
    un.push(f);
    re.zap();
    Viewer fancyView(size, size, *boardp);
    fancyView.show(cout);
}

//--------------------------------------
void Game::undo() throw (UndoError){
    if(un.size() < 2) throw UndoError();
    re.push(un.top());
    un.pop();
    boardp->restoreState(un.top());
    Viewer fancyView(size, size, *boardp);
    fancyView.show(cout);
}

//--------------------------------------
void Game::redo() throw (RedoError){
    if(re.size() == 0) throw RedoError();
    un.push(re.top());
    re.pop();
    boardp->restoreState(un.top());
    Viewer fancyView(size, size, *boardp);
    fancyView.show(cout);
}

//---------------------------------------
void Game::save(){
    string filename;
    cout << " Please input the saving filename: ";
    cin >> filename;
    ofstream gameOut;
    gameOut.open(filename);
    if (!gameOut.is_open()) throw OpenError();
    un.top()->serialize(gameOut,size);
    cout << " Save current board successfully !" <<endl;
    gameOut.close();
}

//----------------------------------------
void Game::restore(){
    string filename;
    cout << " Please input the saved filename: ";
    cin >> filename;
    ifstream gameIn;
    gameIn.open(filename);
    if (!gameIn.is_open()) throw OpenError();
    un.zap();
    re.zap();
    Frame* f = new Frame;
    f->realize(gameIn,size);
    un.push(f);
    boardp->restoreState(f);
    cout << " Restore the board successfully !" <<endl;
    Viewer fancyView(size, size, *boardp);
    fancyView.show(cout);
    gameIn.close();
}

//-----------------------------------------
