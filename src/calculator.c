#include "calculator.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_exit()
{
    fprintf(stderr, "Ошибка: некорректное выражение");
    exit(1);
}

char peek(Parser* p)
{
    return p->expr[p->pos];
}

char get(Parser* p)
{
    return p->expr[p->pos++];
}

void skip_whitespace(Parser* p)
{
    while (isspace(peek(p)))
        p->pos++;
}

double parse_number(Parser* p)
{
    skip_whitespace(p);
    int start = p->pos;

    if (!isdigit(peek(p))) {
        error_exit(); // Некорректный ввод
    }

    while (isdigit(peek(p)))
        get(p);

    if (p->mode == FLOAT_MODE && peek(p) == '.') {
        get(p);
        while (isdigit(peek(p)))
            get(p);
    }

    char num_str[MAX_EXPR_LEN];
    int len = p->pos - start;
    strncpy(num_str, p->expr + start, len);
    num_str[len] = '\0';

    double num = atof(num_str);
    if (num > INT_MAX_VAL)
        error_exit();

    return num;
}
double parse_factor(Parser* p)
{
    skip_whitespace(p);

    if (peek(p) == '(') {
        get(p);
        double result = parse_expr(p);
        skip_whitespace(p);
        if (get(p) != ')')
            error_exit();
        return result;
    } else if (isdigit(peek(p))) { 
        return parse_number(p);
    } else {
        error_exit();
        return 0.0; 
    }
}

double parse_term(Parser* p)
{
    double result = parse_factor(p);

    while (1) {
        skip_whitespace(p);
        char op = peek(p);

        if (op == '*' || op == '/') {
            get(p);
            double rhs = parse_factor(p);

            if (op == '/') {
                if (p->mode == FLOAT_MODE) {
                    if (fabs(rhs) < FLOAT_MIN_DIV)
                        error_exit();
                    result /= rhs;
                } else {
                    if (rhs == 0)
                        error_exit();
                    result = floor(result / rhs);
                }
            } else {
                result *= rhs;
            }

            if (result < INT_MIN_VAL || result > INT_MAX_VAL)
                error_exit();
        } else {
            break;
        }
    }

    return result;
}

double parse_expr(Parser* p)
{
    double result = parse_term(p);

    while (1) {
        skip_whitespace(p);
        char op = peek(p);

        if (op == '+' || op == '-') {
            get(p);
            skip_whitespace(p);

            if (!isdigit(peek(p)) && peek(p) != '(') {
                error_exit(); 
            }

            double rhs = parse_term(p);
            result = (op == '+') ? result + rhs : result - rhs;

            if (result < INT_MIN_VAL || result > INT_MAX_VAL)
                error_exit();
        } else {
            break;
        }
    }

    return result;
}
