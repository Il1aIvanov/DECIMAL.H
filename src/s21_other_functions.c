#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int code_error = 0;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  if (s21_get_sign(value) == 0) {
    s21_set_bit(result, 127, 1);
  } else if (s21_get_sign(value) == 1) {
    s21_set_bit(result, 127, 0);
  } else
    code_error = 1;
  return code_error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0U;
  int code_error = 0;
  int scale = 0;
  int last_number = 0;
  int flag_number = 0;
  scale = s21_get_degree(value);
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  if (scale) {
    for (int i = 1; i <= scale; i++) {
      last_number = s21_division_by_ten(result);
      if (last_number) flag_number++;
    }
  }
  if (flag_number == 1 && last_number == 5) {
    if (s21_get_bit(*result, 0) == 1) result->bits[0] += 1;
  } else if (last_number >= 5) {
    result->bits[0] += 1;
  }
  return code_error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0U;
  int code_error = 0;
  int power = s21_get_degree(value);
  big_decimal preres = {{0, 0, 0, 0, 0, 0, 0}};
  s21_from_decimal_to_big(value, &preres);
  while (power != 0) {
    s21_point_move_right(&preres);
    power = s21_get_degree_big(preres);
  }
  s21_from_big_to_decimal(&preres, result);
  return code_error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0U;
  int code_error = 1, scale = 0, sign = 0, last_number = 0;
  scale = s21_get_degree(value);
  sign = s21_get_sign(value);
  for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  if (scale) {
    code_error = 0;
    if (sign) {
      for (int i = 1; i <= scale; i++) {
        last_number = s21_division_by_ten(result);
      }
      if (last_number) result->bits[0] += 1;
    } else
      s21_truncate(value, result);
  } else {
    code_error = 0;
    for (int i = 0; i <= 3; i++) {
      result->bits[i] = value.bits[i];
    }
  }
  return code_error;
}