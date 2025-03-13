#include "calculator.h" // Подключаем заголовочный файл калькулятора
#include <gtest/gtest.h>

// Тест для parse_number (целые числа)
TEST(CalculatorTest, ParseNumberInt)
{
    Parser p = { "123", 0, INT_MODE };
    EXPECT_EQ(parse_number(&p), 123);
}

// Тест для parse_number (дробные числа)
TEST(CalculatorTest, ParseNumberFloat)
{
    Parser p = { "3.14", 0, FLOAT_MODE };
    EXPECT_DOUBLE_EQ(parse_number(&p), 3.14);
}

// Тест для parse_factor (отрицательные числа)
TEST(CalculatorTest, ParseFactorNegative)
{
    Parser p = { "-5", 0, INT_MODE };
    EXPECT_EQ(parse_factor(&p), -5);
}

// Тест для parse_factor (число в скобках)
TEST(CalculatorTest, ParseFactorParentheses)
{
    Parser p = { "(8)", 0, INT_MODE };
    EXPECT_EQ(parse_factor(&p), 8);
}

// Тест для parse_term (умножение)
TEST(CalculatorTest, ParseTermMultiplication)
{
    Parser p = { "2*3", 0, INT_MODE };
    EXPECT_EQ(parse_term(&p), 6);
}

// Тест для parse_term (деление в целочисленном режиме)
TEST(CalculatorTest, ParseTermDivisionInt)
{
    Parser p = { "8/2", 0, INT_MODE };
    EXPECT_EQ(parse_term(&p), 4);
}

// Тест для parse_term (деление в float режиме)
TEST(CalculatorTest, ParseTermDivisionFloat)
{
    Parser p = { "9/2", 0, FLOAT_MODE };
    EXPECT_DOUBLE_EQ(parse_term(&p), 4.5);
}

// Тест для parse_expr (сложение)
TEST(CalculatorTest, ParseExprAddition)
{
    Parser p = { "4+5", 0, INT_MODE };
    EXPECT_EQ(parse_expr(&p), 9);
}

// Тест для parse_expr (вычитание)
TEST(CalculatorTest, ParseExprSubtraction)
{
    Parser p = { "10-3", 0, INT_MODE };
    EXPECT_EQ(parse_expr(&p), 7);
}

// Тест для parse_expr (смешанные операции)
TEST(CalculatorTest, ParseExprMixed)
{
    Parser p = { "2+3*4", 0, INT_MODE }; // 2 + (3 * 4) = 14
    EXPECT_EQ(parse_expr(&p), 14);
}

// Тест для skip_whitespace (пропуск пробелов)
TEST(CalculatorTest, SkipWhitespace)
{
    Parser p = { "   42", 0, INT_MODE };
    skip_whitespace(&p);
    EXPECT_EQ(p.pos, 3); // Должно перескочить пробелы
}

// Тест для peek (чтение текущего символа)
TEST(CalculatorTest, PeekTest)
{
    Parser p = { "123", 1, INT_MODE };
    EXPECT_EQ(peek(&p), '2'); // Должен вернуть '2'
}

// Тест для get (чтение и сдвиг позиции)
TEST(CalculatorTest, GetTest)
{
    Parser p = { "789", 0, INT_MODE };
    EXPECT_EQ(get(&p), '7'); // Должен вернуть '7'
    EXPECT_EQ(p.pos, 1); // Позиция должна увеличиться
}

// Тест для парсинга выражения с пробелами
TEST(CalculatorTest, ParseExprWithSpaces)
{
    Parser p = { "  7 +  8  ", 0, INT_MODE };
    EXPECT_EQ(parse_expr(&p), 15);
}

// Тест для обработки некорректного ввода (ожидаем выброс исключения)
TEST(CalculatorTest, InvalidExpression)
{
    Parser p = { "abc", 0, INT_MODE };

    // Ожидаем завершение программы с кодом 1 и вывод ошибки
    EXPECT_EXIT(parse_number(&p), ::testing::ExitedWithCode(1), ::testing::MatchesRegex("Ошибка: некорректное выражение"));
}

TEST(CalculatorTest, DivisionByZero)
{
    Parser p = { "5/0", 0, INT_MODE };

    // Ожидаем завершение программы с ошибкой, выводом "Oshibka"
    EXPECT_EXIT({
        parse_term(&p); // Это вызовет ошибку при делении на ноль
    },
        ::testing::ExitedWithCode(1), ::testing::MatchesRegex("Ошибка: некорректное выражение"));
}

// Простой тест для проверки GoogleTest
TEST(SampleTest, BasicAssertions)
{
    EXPECT_EQ(2 + 2, 4);
}

// Главная функция тестов
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
