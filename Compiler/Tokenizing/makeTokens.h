#ifndef MAKETOKENS_H_INLUDED
#define MAKETOKENS_H_INLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../Config/config.h"
#include "Token.h"
#include <assert.h>
#include <ctype.h>
#include <string.h>

enum {
    SCANNEDSTR_SIZE = 32
};

class makeTokens
{
public:
                    makeTokens(FILE *inputFile);
                    ~makeTokens();
    
                    Token* firstToken_;

    makeTokens&     operator= (const makeTokens&);
                    makeTokens(const makeTokens&);
private:
    FILE*           inputFile_;
    char*           programString_;
    char*           strPointer_;
    
    Token*          makeList();
    size_t          getFileSize();
    void            dotDump(Token* root);
    void            dotNodeDump(Token* root, FILE* stream);
};

#endif
