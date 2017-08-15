#include "Token.h"


Token::Token(TYPE type, int number):
    next_               (NULL),
    type_               (type),
    str_flag            (false)
{
    value_.number = number;
}

Token::Token(TYPE type, char* str):
    next_                   (NULL),
    type_                   (type),
    str_flag                (true)
{
    value_.identifier = str;
}

Token::Token(TYPE type, SYMBOL character):
    next_               (NULL),
    type_               (type),
    str_flag            (false)
{
    value_.value = character;
}

Token::~Token() {
    if(str_flag == true) {
        free(value_.identifier);
    }
    delete next_;
    next_ = NULL;
    //value_ = NULL;
}
