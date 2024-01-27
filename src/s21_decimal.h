#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define deg 0x00ff0000    // 00000000 11111111 00000000 00000000
#define minus 0x90000000  // 10000000 00000000 00000000 00000000

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int big[7];
} big_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_get_bit(s21_decimal value, int number);  // (0 plus, 1 minus)
int s21_get_degree(s21_decimal value);  // bits from 16 to 23 ( 0 to 28)
void s21_set_bit(s21_decimal *value, int number, int binary_number);
void s21_set_degree(s21_decimal *value, int binary_number);

int s21_point_move_left(big_decimal *value);  // увеличение степени
int s21_point_move_right(big_decimal *value);  // уменьшение степени
int s21_null_check(s21_decimal value);
int s21_get_sign(s21_decimal value);
// void s21_print_decimal(s21_decimal value);

void s21_normalization(big_decimal *value1, big_decimal *value2);

int s21_from_big_to_decimal(big_decimal *value, s21_decimal *result);
void s21_from_decimal_to_big(s21_decimal value, big_decimal *result);
int s21_get_sign_big(big_decimal value);
void s21_set_bit_big(big_decimal *value, int number, int binary_number);
int s21_get_bit_big(big_decimal value, int number);
void s21_set_degree_big(big_decimal *value, int number);
int s21_get_degree_big(big_decimal value);
// void s21_print_big(big_decimal value);

int s21_division_by_ten(s21_decimal *value);
void s21_round_with_scale(big_decimal *value);
void s21_plus(big_decimal result_big_1, big_decimal result_big_2,
              big_decimal *result_big);
int check_big(big_decimal *value, int *code_error, s21_decimal *result);
void minus_sub(big_decimal minuend, big_decimal subtrahend,
               big_decimal *result);

void mul_ten(big_decimal *value);
void simple_div(big_decimal value_1, big_decimal value_2, big_decimal *result,
                big_decimal *ostatok);
void s21_add_big(big_decimal value_1, big_decimal value_2, big_decimal *result);
void s21_sub_big(big_decimal value_1, big_decimal value_2,
                 big_decimal *big_result);
int is_less_mantissa(big_decimal value_1, big_decimal value_2);
int is_equal_mantissa(big_decimal value_1, big_decimal value_2);
int s21_null_check_big(big_decimal value);
void binary_left_shift(big_decimal *value);
void s21_mul_big(big_decimal value_1, big_decimal value_2, big_decimal *result);
void div_ten(big_decimal value, big_decimal *res, big_decimal *remainder);
