#include <stdio.h>
#include <stdlib.h>
#include "./Compiler/Tokenizing/makeTokens.h"

int main() {
    FILE *file = fopen("program.txt", "rb");
    makeTokens program(file);

    return 0;
}
