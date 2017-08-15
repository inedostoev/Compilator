#include <stdio.h>
#include <stdlib.h>
#include "./Config/config.h"
//#include "Tokenizing/Token.h"
#include "Tokenizing/makeTokens.h"

int main() {
    FILE *file = fopen("program.txt", "rb");
    makeTokens program(file);

    return 0;
}
