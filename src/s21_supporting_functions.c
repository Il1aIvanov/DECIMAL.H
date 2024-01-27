#include "s21_decimal.h"

int s21_get_bit(s21_decimal value, int number) {
  unsigned int bit_index =
      number / 32;  // узнаем, в каком из байтов изменение: 0, 1, 2 или 3
  unsigned int bit_position =
      number % 32;  // узнаем, какой именно бит изменяем из 32
  unsigned int shift = (value.bits[bit_index] >> bit_position);
  return (1U & shift);
}

void s21_set_bit(s21_decimal *value, int number, int binary_number) {
  unsigned int bit_index = number / 32;
  unsigned int bit_position = number % 32;
  if (binary_number) {
    unsigned int shift = (1U << bit_position);
    value->bits[bit_index] |= shift;
  } else {
    unsigned int shift = (1U << bit_position);
    value->bits[bit_index] &= ~shift;
  }
}

int s21_get_sign(s21_decimal value) { return s21_get_bit(value, 127); }

// void s21_print_decimal(s21_decimal value) {
//   for (int i = 127; i >= 0; i--) {
//     if (((i + 1) % 32) == 0) printf("\n");
//     printf("%d", s21_get_bit(value, i));
//   }
// }

int s21_get_sign_big(big_decimal value) { return s21_get_bit_big(value, 223); }

void s21_from_decimal_to_big(s21_decimal value, big_decimal *result_big) {
  //  big_decimal result_big = {{0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    result_big->big[i] = value.bits[i];  // result предварительно должен быть
                                         // занулен
  }
  result_big->big[6] =
      value.bits[3];  // сохраняем и помещаем знаки и степень в нужный байт
}

int s21_from_big_to_decimal(big_decimal *value, s21_decimal *result) {
  int code_error = 0;
  s21_round_with_scale(value);
  check_big(value, &code_error, result);
  s21_set_bit(result, 127, s21_get_bit_big(*value, 223));
  return code_error;
}

void s21_round_with_scale(big_decimal *value) {
  int last_number = 0;
  int flag_number = 0;
  while (
      ((value->big[3] != 0) || (value->big[4] != 0) || (value->big[5] != 0)) &&
      s21_get_degree_big(*value) > 0) {
    last_number = s21_point_move_right(value);
    if (last_number) flag_number++;
  }
  if (flag_number == 1 && last_number == 5) {
    if (s21_get_bit_big(*value, 0) == 1) value->big[0] += 1;
  } else if (last_number >= 5) {
    value->big[0] += 1;
  }
}

int check_big(big_decimal *value, int *code_error, s21_decimal *result) {
  if ((value->big[3] == 0) && (value->big[4] == 0) && (value->big[5] == 0)) {
    for (int i = 0; i < 3; i++) {
      result->bits[i] = value->big[i];
    }
    result->bits[3] = value->big[6];
  } else {
    if (s21_get_bit_big(*value, 223)) {
      *code_error = 2;
    } else {
      *code_error = 1;
    }
  }
  return *code_error;
}

void s21_set_bit_big(big_decimal *value, int number, int binary_number) {
  unsigned int bit_index = number / 32;
  unsigned int bit_position = number % 32;
  if (binary_number) {
    unsigned int shift = (1U << bit_position);
    value->big[bit_index] |= shift;
  } else {
    unsigned int shift = (1U << bit_position);
    value->big[bit_index] &= ~shift;
  }
}

int s21_get_bit_big(big_decimal value, int number) {
  unsigned int bit_index = number / 32;  // узнаем, в каком из байтов
                                         // изменение: 0, 1, 2, 3, 4, 5  или 6
  unsigned int bit_position =
      number % 32;  // узнаем, какой именно бит изменяем из 32
  unsigned int shift = (value.big[bit_index] >> bit_position);
  return (1U & shift);
}

// void s21_print_big(big_decimal value) {
//   for (int i = 223; i >= 0; i--) {
//     if (((i + 1) % 32) == 0) printf("\n");
//     printf("%d", s21_get_bit_big(value, i));
//   }
// }

int s21_point_move_left(big_decimal *value) {
  uint64_t remain = 0;
  uint64_t remain_shift = 0;
  uint64_t copy_value = 0;
  for (int i = 0; i < 6; i++) {
    copy_value = (uint64_t)value->big[i] * 10 + remain;
    remain = copy_value >> 32;
    remain_shift = remain << 32;
    value->big[i] = copy_value & ~remain_shift;
  }
  int scale = s21_get_degree_big(*value) + 1;
  s21_set_degree_big(value, scale);
  return remain;
}

int s21_point_move_right(big_decimal *value) {
  uint64_t remain = 0;
  uint64_t copy_value = 0;
  for (int i = 5; i >= 0; i--) {
    copy_value = value->big[i] + (remain << 32);
    remain = copy_value % 10;
    copy_value /= 10;
    value->big[i] = copy_value;
  }
  int scale = s21_get_degree_big(*value) - 1;
  s21_set_degree_big(value, scale);
  return remain;
}

int s21_null_check(s21_decimal value) {
  int code_result = 0;

  if ((value.bits[0] == 0) && (value.bits[1] == 0) && (value.bits[2] == 0))
    code_result = 1;

  return code_result;
}

int s21_get_degree(s21_decimal value) {
  int p[8] = {0}, power = 0;
  for (int i = 112, j = 0; i <= 116; i++, j++) p[j] = s21_get_bit(value, i);

  for (int i = 0; i < 8; i++) {
    power += p[i] * pow(2, i);
  }
  return power;
}

void s21_set_degree(s21_decimal *value, int number) {
  int n = 16, mas[8] = {0};
  for (int i = 0; i < 8; i++) {
    mas[i] = (number >> i) & 1U;
  }
  for (int i = 0; i < 8; i++) {
    int bit = s21_get_bit(*value, 96 + n);
    if (bit != mas[i]) value->bits[3] ^= (1 << n);
    n++;
  }
}

int s21_get_degree_big(big_decimal value) {
  int p[8] = {0}, power = 0;
  for (int i = 208, j = 0; i <= 213; i++, j++) p[j] = s21_get_bit_big(value, i);

  for (int i = 0; i < 8; i++) {
    power += p[i] * pow(2, i);
  }
  return power;
}

void s21_set_degree_big(big_decimal *value, int number) {
  // value->big[6] ^= number << 16;
  int n = 16, mas[8] = {0};
  for (int i = 0; i < 8; i++) {
    mas[i] = (number >> i) & 1U;
  }
  for (int i = 0; i < 8; i++) {
    int bit = s21_get_bit_big(*value, 192 + n);
    if (bit != mas[i]) value->big[6] ^= (1 << n);
    n++;
  }
}

void s21_normalization(big_decimal *value1, big_decimal *value2) {
  int power1 = s21_get_degree_big(*value1);
  int power2 = s21_get_degree_big(*value2);
  if (power1 > power2) {
    while (power1 != power2 && power2 <= 28) {
      s21_point_move_left(value2);
      power2 = s21_get_degree_big(*value2);
    }
  } else if (power2 > power1) {
    while (power1 != power2 && power1 <= 28) {
      s21_point_move_left(value1);
      power1 = s21_get_degree_big(*value1);
    }
  }
}

int s21_division_by_ten(s21_decimal *value) {
  uint64_t remain = 0;
  uint64_t copy_value = 0;
  for (int i = 2; i >= 0; i--) {
    copy_value = value->bits[i] + (remain << 32);
    remain = copy_value % 10;
    copy_value /= 10;
    value->bits[i] = copy_value;
  }
  int scale = s21_get_degree(*value) - 1;
  s21_set_degree(value, scale);
  return remain;
}

void mul_ten(big_decimal *value) {
  big_decimal temp_val1 = *value;
  for (int i = 0; i < 7; i++) value->big[i] = 0U;
  binary_left_shift(&temp_val1);
  big_decimal temp_val2 = temp_val1;
  for (int i = 0; i < 2; i++) binary_left_shift(&temp_val2);
  s21_add_big(temp_val1, temp_val2, value);
}

void simple_div(big_decimal value_1, big_decimal value_2, big_decimal *result,
                big_decimal *ostatok) {
  for (int i = 0; i < 7; i++) result->big[i] = 0U;
  for (int i = 0; i < 7; i++) ostatok->big[i] = 0U;
  big_decimal value_1_tmp = value_1;
  big_decimal value_2_tmp = value_2;
  value_1_tmp.big[6] = 0U;
  value_2_tmp.big[6] = 0U;
  for (int i = 0; i < 7; i++) result->big[i] = 0U;
  for (int i = 0; i < 7; i++) ostatok->big[i] = 0U;

  int position = 95 + 96;
  while (!s21_get_bit_big(value_1_tmp, position)) position -= 1;
  big_decimal dividend = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  big_decimal remainder = {{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
  while (position >= 0) {
    s21_add_big(dividend, remainder, &dividend);
    for (int i = 0; i < 7; i++) remainder.big[i] = 0U;
    binary_left_shift(&dividend);
    s21_set_bit_big(&dividend, 0, s21_get_bit_big(value_1_tmp, position));
    binary_left_shift(result);
    if (is_less_mantissa(dividend, value_2_tmp))
      s21_set_bit_big(result, 0, 0);
    else {
      s21_set_bit_big(result, 0, 1);
      s21_sub_big(dividend, value_2_tmp, &remainder);
      for (int i = 0; i < 7; i++) dividend.big[i] = 0U;
    }
    position--;
  }
  big_decimal whole_num = {{0u, 0u, 0u, 0u, 0u, 0u, 0u}};
  s21_mul_big(*result, value_2_tmp, &whole_num);
  s21_sub_big(value_1_tmp, whole_num, ostatok);
}

void s21_add_big(big_decimal value_1, big_decimal value_2,
                 big_decimal *result) {
  for (int i = 0; i < 7; i++) result->big[i] = 0U;
  int flag_sign = 0;
  if ((s21_get_sign_big(value_1) == 0) && (s21_get_sign_big(value_2) == 1)) {
    s21_set_bit_big(&value_2, 127, 0);
    s21_sub_big(value_1, value_2, result);
  } else if ((s21_get_sign_big(value_1) == 1) &&
             (s21_get_sign_big(value_2) == 0)) {
    s21_set_bit_big(&value_1, 127, 0);
    s21_sub_big(value_2, value_1, result);
  } else {
    if ((s21_get_sign_big(value_1) == 1) && (s21_get_sign_big(value_2) == 1))
      flag_sign = 1;
    if (s21_null_check_big(value_1) == 1) {
      for (int i = 0; i < 6; i++) {
        result->big[i] = value_2.big[i];
      }
    }
    if (s21_null_check_big(value_2) == 1) {
      if (s21_null_check_big(value_1) == 1) {
        for (int i = 0; i < 6; i++) {
          result->big[i] = 0;
        }
      }
      for (int i = 0; i < 6; i++) {
        result->big[i] = value_1.big[i];
      }
    }
    s21_normalization(&value_1, &value_2);
    s21_plus(value_1, value_2, result);

    if (s21_get_degree_big(value_1) == s21_get_degree_big(value_2)) {
      s21_set_degree_big(result, s21_get_degree_big(value_1));
    }
    if (flag_sign) {
      s21_set_bit_big(result, 223 + 96, 1);
    }
  }
}

void minus_sub(big_decimal minuend, big_decimal subtrahend,
               big_decimal *result) {
  int occup = 0, diff = 0;
  int sign = s21_get_sign_big(minuend);
  for (int i = 0; i <= 192; i++) {
    if (s21_get_bit_big(minuend, i) >=
        (s21_get_bit_big(subtrahend, i) + occup)) {
      diff =
          s21_get_bit_big(minuend, i) - s21_get_bit_big(subtrahend, i) - occup;
      occup = 0;
    } else {
      diff = s21_get_bit_big(minuend, i) + 2 - s21_get_bit_big(subtrahend, i) -
             occup;
      occup = 1;
    }
    if (diff) s21_set_bit_big(result, i, 1);
  }
  if (sign) s21_set_bit_big(result, 223, 1);
}

void s21_sub_big(big_decimal value_1, big_decimal value_2,
                 big_decimal *big_result) {
  for (int i = 0; i < 7; i++) big_result->big[i] = 0U;
  int sign1 = s21_get_sign_big(value_1);
  int sign2 = s21_get_sign_big(value_2);
  int status = 0;
  big_decimal big_val1 = value_1;
  big_decimal big_val2 = value_2;
  s21_normalization(&big_val1, &big_val2);
  int power = s21_get_degree_big(big_val1);

  if (sign1 != sign2) {
    s21_set_bit_big(&big_val1, 223, 0);
    s21_set_bit_big(&big_val2, 223, 0);
    s21_set_degree_big(big_result, power);
    s21_plus(big_val1, big_val2, big_result);
    if (!sign2) s21_set_bit_big(big_result, 223, 1);
  } else {
    if (sign1) {
      s21_set_bit_big(&big_val1, 127 + 96, 0);
      s21_set_bit_big(&big_val2, 127 + 96, 0);
      status = 1;
    }
    if (!is_equal_mantissa(big_val1, big_val2) &&
        !is_less_mantissa(big_val1, big_val2)) {
      minus_sub(big_val1, big_val2, big_result);
      s21_set_degree_big(big_result, power);
      if (status) s21_set_bit_big(big_result, 127 + 96, 1);
    } else if (!is_equal_mantissa(big_val1, big_val2) &&
               !is_less_mantissa(big_val2, big_val1)) {
      minus_sub(big_val2, big_val1, big_result);
      s21_set_degree_big(big_result, power);
      if (!status) s21_set_bit_big(big_result, 127 + 96, 1);
    } else if (is_equal_mantissa(big_val1, big_val2))
      big_result = big_result;
  }
}

int is_less_mantissa(big_decimal value_1, big_decimal value_2) {
  int result = 0;
  for (int i = 95 + 96; i >= 0; i--) {
    int digit1 = 0, digit2 = 0;
    if ((digit1 = s21_get_bit_big(value_1, i)) !=
        (digit2 = s21_get_bit_big(value_2, i))) {
      if (digit1 < digit2) result = 1;
      break;
    }
  }
  return result;
}

int is_equal_mantissa(big_decimal value_1, big_decimal value_2) {
  int equal = 1;
  for (int i = 95 + 96; i >= 0; i--) {
    if (s21_get_bit_big(value_1, i) != s21_get_bit_big(value_2, i)) equal = 0;
  }
  return equal;
}

int s21_null_check_big(big_decimal value) {
  int code_result = 0;

  if ((value.big[0] == 0) && (value.big[1] == 0) && (value.big[2] == 0) &&
      (value.big[3] == 0) && (value.big[4] == 0) && (value.big[5] == 0))
    code_result = 1;

  return code_result;
}

void binary_left_shift(big_decimal *value) {
  unsigned int old_overflow = 0, new_overflow = 0;
  for (int i = 0; i <= 5; i++) {
    new_overflow = s21_get_bit_big(*value, 32 * (i + 1) - 1);
    value->big[i] = (value->big[i] << 1) + old_overflow;
    old_overflow = new_overflow;
  }
}

void s21_mul_big(big_decimal value_1, big_decimal value_2,
                 big_decimal *result) {
  for (int i = 0; i < 7; i++) result->big[i] = 0U;
  int flag_sign = 0;
  if (((s21_get_sign_big(value_1) == 1) && (s21_get_sign_big(value_2) == 0)) ||
      ((s21_get_sign_big(value_1) == 0) && (s21_get_sign_big(value_2) == 1)))
    flag_sign = 1;

  if (s21_null_check_big(value_1) || s21_null_check_big(value_2)) {
    result->big[0] = 0;
    result->big[1] = 0;
    result->big[2] = 0;
    result->big[3] = 0;
    result->big[4] = 0;
    result->big[5] = 0;
  } else {
    for (int i = 0; i < 96 + 96; i++) {
      if (s21_get_bit_big(value_2, i)) s21_plus(value_1, *result, result);
      int position = 159;
      for (int j = 5; j >= 0; j--) {
        value_1.big[j] <<= 1;
        if (j == 0) position = 0;
        if (s21_get_bit_big(value_1, position) && j) value_1.big[j] += 1;
        position -= 32;
      }
    }
    if (flag_sign) {
      s21_set_bit_big(result, 223, 1);
    }

    s21_set_degree_big(
        result, s21_get_degree_big(value_1) + s21_get_degree_big(value_2));
  }
}

void div_ten(big_decimal value, big_decimal *res, big_decimal *remainder) {
  big_decimal value_tmp = value;
  for (int i = 0; i < 7; i++) res->big[i] = 0U;
  for (int i = 0; i < 7; i++) remainder->big[i] = 0U;
  big_decimal ten = {{10U, 0U, 0U, 0U, 0U, 0U, 0U}};
  simple_div(value_tmp, ten, res, remainder);
}

void s21_plus(big_decimal result_big_1, big_decimal result_big_2,
              big_decimal *result_big) {
  uint64_t digit = 0;
  uint64_t summ = 0;
  for (int i = 0; i <= 192; i++) {
    summ = s21_get_bit_big(result_big_1, i) + s21_get_bit_big(result_big_2, i) +
           digit;

    if (summ == 3) {
      digit = 1;
      s21_set_bit_big(result_big, i, 1);

    } else if (summ == 2) {
      digit = 1;
      s21_set_bit_big(result_big, i, 0);

    } else if (summ == 1) {
      digit = 0;
      s21_set_bit_big(result_big, i, 1);

    } else if (summ == 0) {
      digit = 0;
      s21_set_bit_big(result_big, i, 0);
    }
  }
}