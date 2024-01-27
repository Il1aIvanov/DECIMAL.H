#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0U;
  int flag_sign = 0;
  int code_error = 0;
  if ((s21_get_sign(value_1) == 0) && (s21_get_sign(value_2) == 1)) {
    s21_set_bit(&value_2, 127, 0);
    s21_sub(value_1, value_2, result);
  } else if ((s21_get_sign(value_1) == 1) && (s21_get_sign(value_2) == 0)) {
    s21_set_bit(&value_1, 127, 0);
    s21_sub(value_2, value_1, result);
  } else {
    if ((s21_get_sign(value_1) == 1) && (s21_get_sign(value_2) == 1))
      flag_sign = 1;
    big_decimal result_big = {{0, 0, 0, 0, 0, 0, 0}};
    big_decimal result_big_1 = {{0, 0, 0, 0, 0, 0, 0}};
    big_decimal result_big_2 = {{0, 0, 0, 0, 0, 0, 0}};
    if (s21_null_check(value_1) == 1) {
      for (int i = 0; i < 3; i++) {
        result->bits[i] = value_2.bits[i];
      }
    }
    if (s21_null_check(value_2) == 1) {
      if (s21_null_check(value_1) == 1) {
        for (int i = 0; i < 3; i++) {
          result->bits[i] = 0;
        }
      }
      for (int i = 0; i < 3; i++) {
        result->bits[i] = value_1.bits[i];
      }
    }
    s21_from_decimal_to_big(value_1, &result_big_1);
    s21_from_decimal_to_big(value_2, &result_big_2);
    s21_normalization(&result_big_1, &result_big_2);
    s21_plus(result_big_1, result_big_2, &result_big);
    if (s21_get_degree_big(result_big_1) == s21_get_degree_big(result_big_2)) {
      s21_set_degree_big(&result_big, s21_get_degree_big(result_big_1));
    }
    if (flag_sign) {
      s21_set_bit_big(&result_big, 223, 1);
    }
    code_error = s21_from_big_to_decimal(&result_big, result);
  }
  return code_error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0U;
  int flag_sign = 0;
  int code_error = 0;
  if (((s21_get_sign(value_1) == 1) && (s21_get_sign(value_2) == 0)) ||
      ((s21_get_sign(value_1) == 0) && (s21_get_sign(value_2) == 1)))
    flag_sign = 1;

  if (s21_null_check(value_1) || s21_null_check(value_2)) {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
  } else {
    big_decimal result_big = {{0, 0, 0, 0, 0, 0, 0}};
    big_decimal big_1 = {{0, 0, 0, 0, 0, 0, 0}};
    s21_from_decimal_to_big(value_1, &big_1);
    for (int i = 0; i < 96; i++) {
      if (s21_get_bit(value_2, i)) s21_plus(big_1, result_big, &result_big);
      int position = 159;
      for (int j = 5; j >= 0; j--) {
        big_1.big[j] <<= 1;
        if (j == 0) position = 0;
        if (s21_get_bit_big(big_1, position) && j) big_1.big[j] += 1;
        position -= 32;
      }
    }
    if (flag_sign) {
      s21_set_bit_big(&result_big, 223, 1);
    }

    s21_set_degree_big(&result_big,
                       s21_get_degree_big(big_1) + s21_get_degree(value_2));
    code_error = s21_from_big_to_decimal(&result_big, result);
  }
  return code_error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0U;
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int err_cod = 0, flag = 0;
  big_decimal big_val1 = {{0, 0, 0, 0, 0, 0, 0}};
  big_decimal big_val2 = {{0, 0, 0, 0, 0, 0, 0}};
  big_decimal big_result = {{0, 0, 0, 0, 0, 0, 0}};
  s21_from_decimal_to_big(value_1, &big_val1);
  s21_from_decimal_to_big(value_2, &big_val2);
  s21_normalization(&big_val1, &big_val2);
  s21_set_bit(&value_1, 127, 0);
  s21_set_bit(&value_2, 127, 0);
  if (s21_is_greater(value_1, value_2))
    flag = 1;
  else if (s21_is_greater(value_2, value_1))
    flag = 2;
  int power = s21_get_degree_big(big_val1);
  if (sign1 != sign2) {
    s21_set_bit_big(&big_val1, 223, 0);
    s21_set_bit_big(&big_val2, 223, 0);
    s21_set_degree_big(&big_result, power);
    s21_plus(big_val1, big_val2, &big_result);
    if (!sign2) s21_set_bit_big(&big_result, 223, 1);
    err_cod = s21_from_big_to_decimal(&big_result, result);
  } else {
    if (sign1) {
      s21_set_bit_big(&big_val1, 223, 0);
      s21_set_bit_big(&big_val2, 223, 0);
    }
    if (flag == 1) {
      minus_sub(big_val1, big_val2, &big_result);
      s21_set_degree_big(&big_result, power);
      if (sign1) s21_set_bit_big(&big_result, 223, 1);
    } else if (flag == 2) {
      minus_sub(big_val2, big_val1, &big_result);
      s21_set_degree_big(&big_result, power);
      if (!sign1) s21_set_bit_big(&big_result, 223, 1);
    } else if (!flag)
      result = result;
  }
  if (flag) err_cod = s21_from_big_to_decimal(&big_result, result);
  return err_cod;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0U;
  int code_error = 0;
  if (s21_null_check(value_2)) {
    code_error = 3;
    return code_error;
  } else if (s21_null_check(value_1)) {
    *result = value_1;
    return code_error;
  }
  big_decimal value_1_big = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  big_decimal value_2_big = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  s21_from_decimal_to_big(value_1, &value_1_big);
  s21_from_decimal_to_big(value_2, &value_2_big);
  value_1_big.big[6] = 0U;
  value_2_big.big[6] = 0U;
  // handle a degree
  int degree_1 = s21_get_degree(value_1);
  int degree_2 = s21_get_degree(value_2);
  int res_power = degree_1 - degree_2;
  if (res_power < 0) {
    res_power = -res_power;
    for (; res_power > 0; res_power--) mul_ten(&value_1_big);
  }
  // division process
  big_decimal remainder = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  big_decimal result_extended = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  simple_div(value_1_big, value_2_big, &result_extended, &remainder);
  big_decimal zero = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  while (!is_equal_mantissa(remainder, zero) && !result_extended.big[3]) {
    big_decimal tmp_result = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
    for (int i = 0; i < 7; i++) value_1_big.big[i] = remainder.big[i];
    for (int i = 0; i < 7; i++) remainder.big[i] = 0U;
    mul_ten(&value_1_big);
    mul_ten(&result_extended);
    res_power++;
    simple_div(value_1_big, value_2_big, &tmp_result, &remainder);
    s21_add_big(result_extended, tmp_result, &result_extended);
  }
  // bankers rounding
  big_decimal result_big = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  if (result_extended.big[3] != 0U) {
    big_decimal next_digit_big = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
    div_ten(result_extended, &result_extended, &next_digit_big);
    res_power--;
    result_big = result_extended;
    big_decimal last_digit_big = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
    div_ten(result_extended, &result_extended, &last_digit_big);
    if (next_digit_big.big[0] > 5U ||
        (next_digit_big.big[0] == 5U && last_digit_big.big[0] % 2)) {
      for (int i = 0; i < 6; i++) {
        result_big.big[i]++;
        if (result_big.big[i] != 0U && i != 5)
          break;
        else if (result_big.big[i] == 0U && i == 5) {
          result_big.big[3] = 1U;
          div_ten(result_big, &result_big, &next_digit_big);
          res_power--;
        }
      }
    }
  } else
    result_big = result_extended;
  big_decimal ten_remainder = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  result_extended = result_big;
  while (ten_remainder.big[0] == 0U) {
    result_big = result_extended;
    res_power--;
    div_ten(result_big, &result_extended, &ten_remainder);
  }
  res_power++;
  int last_number = 0;
  int flag_number = 0;
  if (res_power > 28) {
    while (res_power > 28) {
      last_number = s21_point_move_right(&result_big);
      if (last_number) flag_number++;
      res_power--;
    }
    if (s21_get_bit_big(result_big, 0) == 1 && last_number == 5 &&
        flag_number == 1) {
      for (int i = 0; i < 6; i++) {
        result_big.big[i]++;
        if (result_big.big[i] != 0U && i != 5)
          break;
        else if (result_big.big[i] == 0U && i == 5) {
          result_big.big[3] = 1U;
          s21_point_move_right(&result_big);
          res_power--;
        }
      }
    } else if (last_number >= 5) {
      for (int i = 0; i < 6; i++) {
        result_big.big[i]++;
        if (result_big.big[i] != 0U && i != 5)
          break;
        else if (result_big.big[i] == 0U && i == 5) {
          result_big.big[3] = 1U;
          s21_point_move_right(&result_big);
          res_power++;
        }
      }
    }
  }
  while (res_power < 0) {
    mul_ten(&result_big);
    res_power++;
  }
  int sign = s21_get_sign(value_1) ^ s21_get_sign(value_2);
  s21_set_bit_big(&result_big, 223, sign);
  code_error = s21_from_big_to_decimal(&result_big, result);
  s21_set_degree(result, res_power);
  return code_error;
}