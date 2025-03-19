import subprocess

def run_test(args, input_str, expected_returncode, expected_output=None, float_precision=None):
    res = subprocess.run(args, input=input_str, text=True, capture_output=True)

    actual_returncode = res.returncode
    
    # Проверка кода возврата
    if expected_returncode != 0:
        assert actual_returncode != 0, (
            f"Input: {input_str!r}\n"
            f"Expected ERROR code (not 0), but got: {actual_returncode}\n"
            f"Stdout: {res.stdout!r}\n"
            f"Stderr: {res.stderr!r}"
        )
        if expected_output:
            assert res.stderr.strip() == expected_output, (
                f"Input: {input_str!r}\n"
                f"Expected stderr {expected_output!r} but got: {res.stderr.strip()!r}"
            )
    else:
        assert actual_returncode == 0, (
            f"Input: {input_str!r}\n"
            f"Expected return code 0 but got: {actual_returncode}\n"
            f"Stdout: {res.stdout!r}\n"
            f"Stderr: {res.stderr!r}"
        )

    if expected_output is None:
        return

    output = res.stdout.strip()

    if float_precision is not None:
        try:
            expected_val = round(float(expected_output), float_precision)
            output_val   = round(float(output), float_precision)
            assert output_val == expected_val, (
                f"Input: {input_str!r}\n"
                f"Expected float output: {expected_val:.{float_precision}f} but got: {output!r}"
            )
        except ValueError:
            assert False, f"Output is not a valid float: {output!r}"
    else:
        try:
            expected_val = int(expected_output)
            output_val   = int(output)
            assert output_val == expected_val, (
                f"Input: {input_str!r}\n"
                f"Expected integer output: {expected_val} but got: {output!r}"
            )
        except ValueError:
            assert False, f"Output is not a valid integer: {output!r}"

# Примеры тестов
def test_basic_addition():
    run_test(["./build/app.exe"], "10 + 5", 0, "15")

def test_subtraction():
    run_test(["./build/app.exe"], "10 - 5", 0, "5")

def test_multiplication():
    run_test(["./build/app.exe"], "5 * 6", 0, "30")

def test_division():
    run_test(["./build/app.exe"], "10 / 2", 0, "5")

def test_division_truncate():
    run_test(["./build/app.exe"], "10 / 3", 0, "3")

def test_large_number_addition():
    run_test(["./build/app.exe"], "2000000000  + 1000000000", 1)

def test_large_number_multiplication():
    run_test(["./build/app.exe"], "200000000*2", 0, "400000000")

def test_negative_numbers():
    run_test(["./build/app.exe"], "-5 +  10 ", 1)

def test_parentheses():
    run_test(["./build/app.exe"], "(10 + 5) * 2", 0, "30")

def test_float_mode_addition():
    run_test(["./build/app.exe", "--float"], "5 / 2", 0, "2.5000", float_precision=4)

def test_float_mode_multiplication():
    run_test(["./build/app.exe", "--float"], "5.5 * 2", 0, "11.0000", float_precision=4)

def test_float_mode_large_division():
    run_test(["./build/app.exe", "--float"], "1000000000 / 3", 0, "333333333.3333", float_precision=4)

def test_invalid_expression_missing_operator():
    run_test(["./build/app.exe"], "10 5", 1)

def test_invalid_expression_unknown_characters():
    run_test(["./build/app.exe"], "10 + x", 1)

def test_invalid_expression_unmatched_parentheses():
    run_test(["./build/app.exe"], "(10 + 5", 1)

def test_zero_division():
    run_test(["./build/app.exe"], "10 / 0", 1)

def test_small_value_division_float_mode():
    run_test(["./build/app.exe", "--float"], "1 / 0.0001", 0, "10000.0000", float_precision=4)

def test_underflow_in_integer_mode():
    run_test(["./build/app.exe"], "0 - 10000000000", 1)

def test_invalid_float_division_by_zero():
    run_test(["./build/app.exe", "--float"], "1 / 0.0", 1)
def test_invalid_float_range():
    run_test(["./build/app.exe", "--float"], "1 / 0.0000000000000001", 1)

def test_valid_expression_with_float_and_parentheses():
    run_test(["./build/app.exe", "--float"], "(5 + 5) * 2 / 5", 0, "4.0000", float_precision=4)

def test_expression_with_mixed_operations():
    run_test(["./build/app.exe"], "5 + 3 * (2 + 3)", 0, "20")

def test_expression_with_float_and_negative_numbers():
    run_test(["./build/app.exe", "--float"], "0-5 + 4.5", 0, "-0.5000", float_precision=4)

def test_expression_with_large_parentheses():
    run_test(["./build/app.exe"], "(1000 + 2000) * (10 + 5)", 0, "45000")

# Функция для запуска всех тестов
def all_tests():
    tests = [
        test_basic_addition,
        test_subtraction,
        test_multiplication,
        test_division,
        test_division_truncate,
        test_large_number_addition,
        test_large_number_multiplication,
        test_negative_numbers,
        test_parentheses,
        test_float_mode_addition,
        test_float_mode_multiplication,
        test_float_mode_large_division,
        test_invalid_expression_missing_operator,
        test_invalid_expression_unknown_characters,
        test_invalid_expression_unmatched_parentheses,
        test_zero_division,
        test_small_value_division_float_mode,
        test_underflow_in_integer_mode,
        test_invalid_float_division_by_zero,
        test_invalid_float_range,
        test_valid_expression_with_float_and_parentheses,
        test_expression_with_mixed_operations,
        test_expression_with_float_and_negative_numbers,
        test_expression_with_large_parentheses
    ]
    for test in tests:
        test()
        print(f"{test.__name__} passed.")

if __name__ == "__main__":
    all_tests()
