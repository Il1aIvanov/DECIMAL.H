#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return (!s21_is_greater_or_equal(value_1, value_2));
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2));
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = 1, flag = 0;
  big_decimal big_value_1 = {{0, 0, 0, 0, 0, 0, 0}};
  big_decimal big_value_2 = {{0, 0, 0, 0, 0, 0, 0}};
  s21_from_decimal_to_big(value_1, &big_value_1);
  s21_from_decimal_to_big(value_2, &big_value_2);
  s21_normalization(&big_value_1, &big_value_2);
  if (s21_get_bit_big(big_value_1, 223) && !s21_get_bit_big(big_value_2, 223)) {
    result = 0;
  } else if (!s21_get_bit_big(big_value_1, 223) &&
             s21_get_bit_big(big_value_2, 223)) {
    result = 1;
  } else if (s21_get_bit_big(big_value_1, 223) ==
             s21_get_bit_big(big_value_2, 223)) {
    for (int i = 5; i >= 0; i--) {
      if (big_value_1.big[i] != big_value_2.big[i]) {
        if (big_value_1.big[i] > big_value_2.big[i])
          result = 1;
        else
          result = 0;
        break;
      } else if (big_value_1.big[i] == big_value_2.big[i]) {
        flag += 1;
        result = 0;
        continue;
      }
    }
    if (s21_get_bit_big(big_value_1, 223)) {
      if (result == 1)
        result = 0;
      else
        result = 1;
    }
  }
  if (flag == 6) result = 0;
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2));
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  int value_is_zero_1 = 0, value_is_zero_2 = 0;
  big_decimal big_value_1;
  big_decimal big_value_2;
  s21_from_decimal_to_big(value_1, &big_value_1);
  s21_from_decimal_to_big(value_2, &big_value_2);
  s21_normalization(&big_value_1, &big_value_2);
  if (big_value_1.big[0] == 0 && big_value_1.big[1] == 0 &&
      big_value_1.big[2] == 0)
    value_is_zero_1 = 1;
  if (big_value_2.big[0] == 0 && big_value_2.big[1] == 0 &&
      big_value_2.big[2] == 0)
    value_is_zero_2 = 1;
  if (s21_get_sign_big(big_value_1) != s21_get_sign_big(big_value_2)) {
    if (value_is_zero_1 && value_is_zero_2) {
      result = 1;
    } else {
      result = 0;
    }
  } else if (big_value_1.big[0] == big_value_2.big[0] &&
             big_value_1.big[1] == big_value_2.big[1] &&
             big_value_1.big[2] == big_value_2.big[2])
    result = 1;
  else
    result = 0;
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return (!s21_is_equal(value_1, value_2));
}