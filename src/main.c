#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_EXPR_LEN 1024
#define INT_MIN_VAL -2000000000
#define INT_MAX_VAL  2000000000
#define FLOAT_MIN_DIV 0.0001

typedef enum { INT_MODE, FLOAT_MODE } CalcMode;

typedef struct {
    const char *expr;
    int pos;
    CalcMode mode;
} Parser;

double parse_expr(Parser *p);
double parse_term(Parser *p);
double parse_factor(Parser *p);
double parse_number(Parser *p);
void skip_whitespace(Parser *p);

void error_exit() {
    fprintf(stderr, "Ошибка: некорректное выражение\n");
    exit(1);
}

char peek(Parser *p) {
    return p->expr[p->pos];
}

char get(Parser *p) {
    return p->expr[p->pos++];
}

void skip_whitespace(Parser *p) {
    while (isspace(peek(p))) p->pos++;
}

double parse_number(Parser *p) {
    skip_whitespace(p);
    
    int start = p->pos;
    while (isdigit(peek(p))) get(p);
    
    if (p->mode == FLOAT_MODE && peek(p) == '.') {
        get(p);
        while (isdigit(peek(p))) get(p);
    }
    
    char num_str[MAX_EXPR_LEN];
    int len = p->pos - start;
    strncpy(num_str, p->expr + start, len);
    num_str[len] = '\0';

    double num = atof(num_str);
    if (num < 0 || num > INT_MAX_VAL) error_exit();

    return num;
}

double parse_factor(Parser *p) {
    skip_whitespace(p);
    
    if (peek(p) == '(') {
        get(p);
        double result = parse_expr(p);
        skip_whitespace(p);
        if (get(p) != ')') error_exit();
        return result;
    } else if (peek(p) == '-') {
        get(p);
        return -parse_factor(p);
    } else {
        return parse_number(p);
    }
}

double parse_term(Parser *p) {
    double result = parse_factor(p);
    
    while (1) {
        skip_whitespace(p);
        char op = peek(p);
        
        if (op == '*' || op == '/') {
            get(p);
            double rhs = parse_factor(p);
            
            if (op == '/') {
                if (p->mode == FLOAT_MODE) {
                    if (fabs(rhs) < FLOAT_MIN_DIV) error_exit();
                    result /= rhs;
                } else {
                    if (rhs == 0) error_exit();
                    result = floor(result / rhs);
                }
            } else {
                result *= rhs;
            }
            
            if (result < INT_MIN_VAL || result > INT_MAX_VAL) error_exit();
        } else {
            break;
        }
    }
    
    return result;
}

double parse_expr(Parser *p) {
    double result = parse_term(p);
    
    while (1) {
        skip_whitespace(p);
        char op = peek(p);
        
        if (op == '+' || op == '-') {
            get(p);
            double rhs = parse_term(p);
            result = (op == '+') ? result + rhs : result - rhs;

            if (result < INT_MIN_VAL || result > INT_MAX_VAL) error_exit();
        } else {
            break;
        }
    }
    
    return result;
}

// Главная функция
int main(int argc, char *argv[]) {
    CalcMode mode = INT_MODE;
    
    if (argc > 1 && strcmp(argv[1], "--float") == 0) {
        mode = FLOAT_MODE;
    }
    
    char expr[MAX_EXPR_LEN];
    if (!fgets(expr, MAX_EXPR_LEN, stdin)) {
        fprintf(stderr, "Ошибка: пустой ввод\n");
        return 1;
    }
    
    Parser parser = { expr, 0, mode };
    double result = parse_expr(&parser);
    
    skip_whitespace(&parser);
    if (parser.expr[parser.pos] != '\0' && parser.expr[parser.pos] != '\n') {
        error_exit();
    }

    if (mode == FLOAT_MODE) {
        printf("%.4f\n", result);
    } else {
        printf("%d\n", (int)result);
    }

    return 0;
}
