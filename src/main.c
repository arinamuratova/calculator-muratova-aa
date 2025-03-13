#include "calculator.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    CalcMode mode = INT_MODE;

    if (argc > 1 && strcmp(argv[1], "--float") == 0) {
        mode = FLOAT_MODE;
    }

    char expr[MAX_EXPR_LEN];
    if (!fgets(expr, MAX_EXPR_LEN, stdin)) {
        fprintf(stderr, "Ошибка: некорректное выражение");
        return 1;
    }

    Parser parser = { expr, 0, mode };
    double result = parse_expr(&parser);

    skip_whitespace(&parser);
    if (parser.expr[parser.pos] != '\0' && parser.expr[parser.pos] != '\n') {
        fprintf(stderr, "Ошибка: некорректное выражение");
        return 1;
    }

    if (mode == FLOAT_MODE) {
        printf("%.4f\n", result);
    } else {
        printf("%d\n", (int)result);
    }

    return 0;
}
