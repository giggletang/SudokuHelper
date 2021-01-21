//
//  exception.hpp
//  P11Sixy
//
//  Created by ZihanTang on 11/20/19.
//  Copyright © 2019 ZihanTang. All rights reserved.
//

#ifndef exception_hpp
#define exception_hpp
#include "tools.hpp"
//----------------------------------------------------
class MoveError{
public:
    int row;
    int column;
    
    MoveError(int r, int c) : row(r), column(c) {}
    MoveError() = default;
    ~MoveError() = default;
    virtual void print(){
        cerr << " Your move is illegeal move.\n"
        << " This square is already fixed.\n"
        << " The character which you input is not in this square's possiblie list.\n"
        << " You can't undo or redo at this time.";
    }
    void pr(){
        cerr << " Row " << row << " Column " << column
        << " can't be changed. ";
    }
    
};
class FixError : public MoveError{
public:
    FixError(int r, int c) : MoveError(r, c) {}
    ~FixError() = default;
    virtual void print(){
        pr();
        cerr << " Beacuse this square is already fixed.\n";
    }
};
//--------------------------
class PossibleError : public MoveError{
public:
    PossibleError(int r, int c) : MoveError(r, c) {}
    ~PossibleError() = default;
    virtual void print(){
        pr();
        cerr << " Because the character which you input is not in this square's possiblie list.\n";
    }
};
//---------------------------
class UndoError : public MoveError{
public:
    UndoError() : MoveError() {}
    ~UndoError() = default;
    virtual void print(){
        cerr << " You can’t undo unless the stack has 2 or more Frame.\n";
    }
};
//----------------------------
class RedoError : public MoveError{
public:
    RedoError() : MoveError() {}
    ~RedoError() = default;
    virtual void print(){
        cerr << " The redo stack is empty, you can't redo this time.\n";
    }
};

//----------------------------------------------------------
//----------------------------------------------------------
class LogicError{
public:
    int size;
    char type;
    
    LogicError (int s, char t) : size(s), type(t) {};
    ~LogicError() = default;
    virtual void print(){
        cerr << " Legal typecode are D,d,T,t,S,s.\n"
        << " Legal size are 6 and 9.\n"
        << " Number of character in every line of puzzle should equal to size.\n";
    }
    void pr(){
        cerr << "  The type of puzzle now is: " << type << endl
        << " The size of puzzle now is: " << size << endl;
    }
};
//------------------------------------
class TypeError : public LogicError{
public:
    TypeError (int s, char t) : LogicError(s, t) {}
    ~TypeError() = default;
    virtual void print(){
        pr();
        cerr << " If typecode now is N, which means that the typecode is illegal.\n"
        << " Legal typecode are D,d,T,t,S,s.\n";
    }
};
//-----------------------------------
class SizeError : public LogicError{
public:
    SizeError (int s, char t) : LogicError(s, t) {}
    ~SizeError() = default;
    virtual void print(){
        pr();
        cerr << " If size now is 0, which means that the size is illegal.\n"
        << " Legal size are 6 and 9.\n";
    }
};
//------------------------------------
class LineError : public LogicError{
public:
    LineError (int s, char t): LogicError(s, t) {}
    ~LineError() = default;
    virtual void print(){
        pr();
        cerr << " The test character is not a newline, which means that the number of character in this line is illegal.\n"
        << " Number of character in every line of puzzle should equal to size of puzzle.\n";
    }
};

//------------------------------------------------------------
//------------------------------------------------------------
class StreamError{
public:
    StreamError() = default;
     ~StreamError() = default;
    virtual void print(){
        cerr << " Your puzzle file has stream errors, includes:\n"
        << " The puzzle file can't be opened.\n"
        << " The puzzle file can't be read.\n"
        << " The puzzle file is too long.\n"
        << " The puzzle file is too short.\n";
    }
};

//----------------------------------------
class OpenError : public StreamError{
public:
    OpenError() : StreamError() {}
    ~OpenError() = default;
    virtual void print(){
        cerr << " The puzzle file can't be opened.\n"
        << " It may not have the correct name or location. Please check it.\n";
    }
};
//-----------------------------------------
class GoodError : public StreamError{
public:
    GoodError() : StreamError() {}
    ~GoodError() = default;
    virtual void print(){
        cerr << " The puzzle file can't be read.\n"
        << " It causes the puzzle can't be loaded in Sudoku Helper. Please check the state of file good or not.\n";
    }
};
//--------------------------------------
class LongError : public StreamError{
public:
    LongError () : StreamError() {}
    ~LongError() = default;
    virtual void print(){
        cerr << " The puzzle file is too long.\n"
        << " The puzzle is already loaded, but there are still characters at the end, Please check the end of the puzzle file.\n";
    }
};
//--------------------------------------
class ShortError : public StreamError{
public:
    ShortError () : StreamError() {}
    ~ShortError() = default;
    virtual void print(){
        cerr << " The puzzle file is too short.\n"
        << " The puzzle is not loaded perfectly, but the puzzle file is already finish, Sudoku Helper can't work without enough character.\n";
    }
};
//-----------------------------------------------------
#endif /* exception_hpp */
