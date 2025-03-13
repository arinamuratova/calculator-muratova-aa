#ifndef CALCULATOR_H
#define CALCULATOR_H

// Убедимся, что C-функции можно вызывать из C++
#ifdef __cplusplus
extern "C" {
#endif

// Константы
#define MAX_EXPR_LEN 1024
#define INT_MIN_VAL -2000000000
#define INT_MAX_VAL 2000000000
#define FLOAT_MIN_DIV 0.0001

// Enum для режимов работы
typedef enum {
    INT_MODE, // INT_MODE = 0
    FLOAT_MODE // FLOAT_MODE = 1
} CalcMode;

// Структура парсера
typedef struct {
    const char* expr; // Входная строка с выражением
    int pos; // Текущая позиция в выражении
    CalcMode mode; // Теперь это enum, а не int!
} Parser;

// Прототипы функций
void error_exit();
char peek(Parser* p);
char get(Parser* p);
void skip_whitespace(Parser* p);
double parse_number(Parser* p);
double parse_factor(Parser* p);
double parse_term(Parser* p);
double parse_expr(Parser* p);

#ifdef __cplusplus
}
#endif

#endif // CALCULATOR_H
