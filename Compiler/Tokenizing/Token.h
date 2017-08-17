#ifndef TOKENS_H_INCLUDED
#define TOKENS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../Config/config.h"

union VALUE {
    int         number;
    char*       identifier;
    SYMBOL      symbol;
};

class Token
{
public:
                Token(TYPE type, int number);
                Token(TYPE type, char* str);
                Token(TYPE type, SYMBOL character);
                ~Token();

    Token       *next_;
    TYPE        type_;
    VALUE       value_;

    Token&      operator= (const Token&);
                Token(const Token&);
private:
    bool        idFlag;
};

#endif
