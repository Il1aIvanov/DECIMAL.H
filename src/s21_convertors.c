#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0U;
  int sign = 0;
  if (src < 0) {
    sign = 1;
    src = -src;
  }
  src = (unsigned int)src;
  s21_set_bit(dst, 127, sign);
  dst->bits[0] = src;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = 0;
  int err_code = 0, bit = 0;
  int sign = s21_get_sign(src);
  s21_decimal tmp = {{0, 0, 0, 0}};
  s21_truncate(src, &tmp);
  s21_set_bit(&tmp, 127, 0);

  if (tmp.bits[1] || tmp.bits[2] || tmp.bits[3] || s21_get_bit(tmp, 31))
    err_code = 1;
  else {
    for (int i = 31; i >= 0; i--) {
      bit = s21_get_bit(tmp, i);
      *dst = *dst + bit * pow(2, i);
    }
    if (*dst != 0 && sign) *dst *= -1;
  }
  return err_code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0U;
  if (isnan(src) || isinf(src) || fabs(src) > 79228162514264337593543950335. ||
      (fabs(src) < 1e-28 && src != 0.)) {
    return 1;
  } else if (*(unsigned int *)(&src) == 0b00000000000000000000000000000000) {
    for (int i = 0; i < 3; i++) dst->bits[i] = 0;
    return 0;
  } else if (*(unsigned int *)(&src) == 0b10000000000000000000000000000000) {
    for (int i = 0; i < 3; i++) dst->bits[i] = 0;
    dst->bits[3] = 0b10000000000000000000000000000000;
    return 0;
  }
  int sign = 0;
  if (src < 0) {
    sign = 1;
    src = -src;
  }
  unsigned int mantissa;
  int exp = 0;
  exp = (int)(log10l(src)) - 7;
  src /= powl(10, exp);
  while (src >= 10000000) {
    src /= 10;
    exp += 1;
  }
  mantissa = (unsigned int)(src + 0.5);
  while ((mantissa > 9999999) || (mantissa % 10 == 0)) {
    mantissa /= 10;
    exp += 1;
  }
  unsigned int exp_pattern = 0b10000000111111110000000000000000;
  if (exp < 0) {
    dst->bits[0] = mantissa;
    exp = (unsigned int)(-exp);
    dst->bits[3] = (exp << 16) & exp_pattern;
  } else {
    long double num_long = mantissa * powl(10, exp);
    while ((int)num_long != 0) {
      s21_set_bit(dst, (int)log2l(num_long), 1);
      num_long = num_long - powl(2., (int)log2l(num_long));
    }
  }
  dst->bits[3] |= sign << 31;
  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = 0.000000000;
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(src, i)) {
      *dst += pow(2, i);
    }
  }
  int exp = 0;
  for (int i = 96 + 16; i < 96 + 24; i++) {
    if (s21_get_bit(src, i)) {
      exp += pow(2, i - 96 - 16);
    }
  }
  *dst *= (1. / pow(10, exp)) * pow(-1, s21_get_sign(src));
  return 0;
}