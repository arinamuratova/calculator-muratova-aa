#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *expr;

void skip_spaces() {
    while (*expr == ' ' || *expr == '\t') expr++;
}

int parse_number() {
    int num = 0;
    while (isdigit(*expr)) {
        num = num * 10 + (*expr - '0');
        expr++;
    }
    return num;
}

int parse_expression();

int parse_factor() {
    skip_spaces();
    if (*expr == '(') {
        expr++;
        int result = parse_expression();
        skip_spaces();
        if (*expr == ')') expr++; // Пропускаем ')'
        return result;
    }
    return parse_number();
}

int parse_term() {
    int result = parse_factor();
    while (1) {
        skip_spaces();
        if (*expr == '*' || *expr == '/') {
            char op = *expr++;
            int next = parse_factor();
            if (op == '*') result *= next;
            else if (next != 0) result /= next;
            else {
                fprintf(stderr, "Error: division by zero\n");
                exit(1);
            }
        } else break;
    }
    return result;
}

int parse_expression() {
    int result = parse_term();
    while (1) {
        skip_spaces();
        if (*expr == '+' || *expr == '-') {
            char op = *expr++;
            int next = parse_term();
            if (op == '+') result += next;
            else result -= next;
        } else break;
    }
    return result;
}

int main() {
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), stdin)) return 1;
    expr = buffer;
    skip_spaces();
    int result = parse_expression();
    skip_spaces();
    if (*expr != '\0' && *expr != '\n') {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }
    printf("%d\n", result);
    return 0;
}

