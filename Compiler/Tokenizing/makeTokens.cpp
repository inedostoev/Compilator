#include "makeTokens.h"

const int firstChar = 0;

makeTokens::makeTokens(FILE *inputFile) :
    firstToken_     (NULL),
    inputFile_      (inputFile),
    programString_  (NULL),
    strPointer_     (NULL)
{
    assert(inputFile_ != NULL);
    size_t fileSize = getFileSize();
    assert(fileSize > 1);
    strPointer_ = (char*)calloc(fileSize, sizeof(char));
    assert(strPointer_ != NULL);
    programString_ = strPointer_;
    int i = 0;
    i = fread(programString_, sizeof(char), fileSize, inputFile_);
    firstToken_ = makeList();
    assert(firstToken_ != NULL);
    dotDump(firstToken_);
}

makeTokens::~makeTokens() {
    free(strPointer_);  
    strPointer_ = NULL;
    
    delete firstToken_;

    fclose(inputFile_);
    inputFile_ = NULL;
}

size_t makeTokens::getFileSize() {
	fseek(inputFile_, 0, SEEK_END);
	size_t fileSize = (size_t)ftell(inputFile_) + 1;
    if (fileSize <= 1) {
        printf("Empty file\n");
        exit(1);
    }
	rewind(inputFile_);
    return fileSize;
}

Token* makeTokens::makeList() {
    Token* newToken = NULL;
    if(isspace(programString_[firstChar])) {
        programString_++;
        newToken = makeList();
        return newToken;
    }
    else if(programString_[firstChar] == '\0') {
        return NULL;
    }
    else if(isalpha(programString_[firstChar]) || programString_[firstChar] == '_') {
        int length = 0;
        char* scannedStr = (char*)calloc(SCANNEDSTR_SIZE, sizeof(char));
        sscanf(programString_, "%[A-Za-z_] %n", scannedStr, &length);
        programString_ += length;
        if(false) {}
#define KEYWORDS
#define KEYWORD(key_word)                                               \
        else if(!strcmp(scannedStr, #key_word)) {                       \
            newToken = new Token(KEY_WORD, scannedStr);                 \
            newToken->next_ = makeList();                               \
            return newToken;                                            \
        }    
#include "../Config/config_macros.txt"
#undef KEYWORD
#undef KEYWORDS
        else {
            newToken = new Token(INDENTIFICATOR, scannedStr);
            newToken->next_ = makeList();
            return newToken;
        }
    }
    else if(isdigit(programString_[firstChar])) {
        int number = 0;
        int length = 0;
        sscanf(programString_, "%d%n", &number, &length);
        programString_ += length;
        newToken = new Token(NUMBER, number);
        newToken->next_ = makeList();
        return newToken;
    }
#define CHARS 
#define OPERS
#define CHAR(symbol, character)                                         \
        else if(programString_[firstChar] == character) {               \
            programString_++;                                           \
            newToken = new Token(OPERATOR, symbol);                     \
            newToken->next_ = makeList();                               \
            return newToken;                                            \
        }    
#include "../Config/config_macros.txt"
#undef CHAR
#undef OPERS

#define BRACKETS
#define CHAR(symbol, character)                                         \
        else if(programString_[firstChar] == character) {               \
            programString_++;                                           \
            newToken = new Token(BRACKET, symbol);                      \
            newToken->next_ = makeList();                               \
            return newToken;                                            \
        }                                                                   
#include "../Config/config_macros.txt"
#undef CHAR
#undef BRACKETS
#undef CHARS
        else {
            printf("Error in makeList().\n");
            printf("Unknown char %s",programString_);
    }
}

void makeTokens::dotDump(Token* root) {
    FILE* ptrFile = fopen("./Compiler/dump/dumpNode.gv", "w");
    if (ptrFile == NULL) {
        printf("Error with dumpNode.gv\n");
        exit(1);
    }
    fprintf(ptrFile, "digraph graf {\n");
    dotNodeDump(root, ptrFile);
    fprintf(ptrFile, "}");
    fclose(ptrFile);
    ptrFile = NULL;

    int i = 0;
    i = system("dot ./Compiler/dump/dumpNode.gv -Tpng -o ./Compiler/dump/dumpNode.png");
    i = system("xdot ./Compiler/dump/dumpNode.gv");
}

void makeTokens::dotNodeDump(Token* root, FILE* stream) {
    fprintf(stream, "listNode%p [label=\""
                    "listNode[%p]\\l",
                    root, root);
    fprintf(stream, "{\\l");
    if(root->type_ == NUMBER) {
        fprintf(stream, "  type_ = NUMBER\\l");
        fprintf(stream, "  value_ = %d\\l", root->value_);
    }
    else if(root->type_ == INDENTIFICATOR) {
        fprintf(stream, "  type_ = INDENTIFICATOR\\l");
        fprintf(stream, "  value_ = %s\\l", root->value_);
    }
    else if(root->type_ == KEY_WORD) {
        fprintf(stream, "  type_ = KEY_WORD\\l");
        fprintf(stream, "  value_ = %s\\l", root->value_);
    }
    else if(root->type_ == DELIMITER) {
        fprintf(stream, "  type_ = DELIMITER\\l");
        fprintf(stream, "  value_ = %c\\l", root->value_);
    }
    else if(root->type_ == OPERATOR) {
        fprintf(stream, "  type_ = OPERATOR\\l");
        fprintf(stream, "  value_(type of symbol) = %d\\l", root->value_);
    }
    else if(root->type_ == BRACKET) {
        fprintf(stream, "  type_ = BRACKET\\l");
        fprintf(stream, "  value_(type of symbol) = %d\\l", root->value_);
    }
    else {
        printf("Error in dotNodeDump\n");
        exit(1);
    }
    fprintf(stream, "}\\l");
    fprintf(stream, "\"]\n");
    if(root->next_ == NULL) return; 
    fprintf(stream, "listNode%p->listNode%p\n", root, root->next_);
    dotNodeDump(root->next_, stream);
}
