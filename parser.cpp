
#include <stdio.h>
#include "scanner/scanner.h"

int main() {
    auto context = scanner_init_string((char *)"Hello World");
    char c;

    while ((c = scanner_move_next(context)) != '\0') 
    {
        printf("%c", c);
    }

    return 1;
}