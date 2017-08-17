#include "Token.h"


Token::Token(TYPE type, int number):
    next_               (NULL),
    type_               (type),
    idFlag              (false)
{
    value_.number = number;
}

Token::Token(TYPE type, char* str):
    next_               (NULL),
    type_               (type),
    idFlag              (true)
{
    value_.identifier = str;
}

Token::Token(TYPE type, SYMBOL character):
    next_               (NULL),
    type_               (type),
    idFlag              (false)
{
    value_.symbol = character;
}

Token::~Token() {
    if(idFlag == true) {
        free(value_.identifier);
    }
    delete next_;
    next_ = NULL;
}
