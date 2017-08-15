#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

enum TYPE {
#define TYPES

#define TYPE(type)                          \
    type,
#include "config_macros.txt"
#undef TYPE

#undef TYPES
};

enum SYMBOL {
#define CHARS 
#define OPERS

#define CHAR(symbol, character)           \
    symbol,                                 
#include "config_macros.txt"    
#undef CHAR 
#undef OPERS

#define BRACKETS

#define CHAR(symbol, character)           \
    symbol,                                 
#include "config_macros.txt"    
#undef CHAR 
#undef BRACKETS

#undef CHARS
};

enum KEY_WORD {
#define KEYWORDS

#define KEYWORD(key_word)                   \
    key_word,
#include "config_macros.txt"
#undef KEYWORD

#undef KEYWORDS    
};

#endif
