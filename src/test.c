#include <check.h>

#include "s21_decimal.h"

#define EPS 0.000001
#define deg 0x00ff0000    // 00000000 11111111 00000000 00000000
#define minus 0x90000000  // 10000000 00000000 00000000 00000000

START_TEST(test_s21_negate_1) {
  s21_decimal value = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b10000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  int function = s21_negate(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal value = {
      {0b11111111111111111111111111111100, 0b11111111111111111111111111111111,
       0b11111111111111111111100000000000, 0b00000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b11111111111111111111111111111100, 0b11111111111111111111111111111111,
       0b11111111111111111111100000000000, 0b10000000000001010000000000000000}};
  int function = s21_negate(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b11111111111111111111111111111111,
       0b00000000000000000000000000000000, 0b10000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000000000, 0b11111111111111111111111111111111,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  int function = s21_negate(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_round_1) {
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b11111111111111111111111111111111,
       0b00000000000000000000000000000000, 0b00000000000001100000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b11110111101000001010010100100111, 0b00000000000000000001000011000110,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int function = s21_round(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b11111111111111111111111111111111,
       0b00000000000000000000000000000000, 0b10000000000001100000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b11110111101000001010010100100111, 0b00000000000000000001000011000110,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  int function = s21_round(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b11111111111111111111111111111111,
       0b00000000000000000000000000000100, 0b00000000000011100000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000011100001001011100001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int function = s21_round(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_floor_1) {
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000001110000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b11110100100001010111011011001100, 0b01111111001010011010101111001010,
       0b00000000000000000000000110101101, 0b00000000000000000000000000000000}};
  int function = s21_floor(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b11111111111111111111111111111111,
       0b00000000000000000000000000000000, 0b10000000000001100000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b11110111101000001010010100100111, 0b00000000000000000001000011000110,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  int function = s21_floor(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b10000000000001110000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b11110100100001010111011011001101, 0b01111111001010011010101111001010,
       0b00000000000000000000000110101101, 0b10000000000000000000000000000000}};
  int function = s21_floor(value, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_1) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000001110010010110000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_2) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000001110010010110000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000001010000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_3) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000001101101101010000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_4) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000001101101101010000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000001010000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_5) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 1);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_6) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b10000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b10000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 2);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_7) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000001100, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000110000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_8) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_9) {
  s21_decimal value_1 = {
      {0b11111111111111111111111111110101, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000000000000000010100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_set_degree(&value_1, 1);
  s21_set_degree(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b10011001100110011001100110011010, 0b10011001100110011001100110011001,
       0b00011001100110011001100110011001, 0b00000000000000000000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_add_10) {
  s21_decimal value_1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000000000000000010100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_set_degree(&value_1, 1);
  s21_set_degree(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b10011001100110011001100110011100, 0b10011001100110011001100110011001,
       0b00011001100110011001100110011001, 0b00000000000000000000000000000000}};
  int function = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_1) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000010101000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000010000000000000000000}};
  int function = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_2) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000010101000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000010000000000000000000}};
  int function = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_3) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000010101000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000010000000000000000000}};
  int function = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_4) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000001010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000010101000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000010000000000000000000}};
  int function = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_5) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int function = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(function, 1);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_6) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b10000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000001110000000000000, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  int function = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(function, 2);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_7) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000001100, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int function = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_8) {
  s21_decimal value_1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal origin = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int function = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(function, 0);

  ck_assert_int_eq(result.bits[0], origin.bits[0]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
}
END_TEST

START_TEST(s21_div_1) {
  s21_decimal s21_res;
  s21_decimal var_a = {{1896812631, 1427804636, 1285780742, 458752}};
  // var: 2371846828871074418790,1775959
  s21_decimal var_b = {{839352747, -754803312, 0, 1769472}};
  // var: 0,000000015204888534596420011
  int return_res = s21_div(var_a, var_b, &s21_res);
  ck_assert_int_eq(return_res, 1);  // 15599238517758919065198085022
}  // 155992385177589190651980850217.3
END_TEST

START_TEST(s21_div_2) {
  s21_decimal value_1 = {{0b00001001001011011101101100000111,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000}};  // 154.000135
  s21_set_degree(&value_1, 6);
  s21_decimal value_2 = {{0b00000000000000000000000000000101,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000}};  // 0.0005
  s21_set_degree(&value_2, 4);
  s21_decimal result = {{0b00000000000000000000000000000000,
                         0b00000000000000000000000000000000,
                         0b00000000000000000000000000000000,
                         0b00000000000000000000000000000000}};  // 0.0
  s21_decimal true_result = {
      {0b00000001110101011111100010011011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000,
       0b00000000000000000000000000000000}};  // 308000.27
  s21_set_degree(&true_result, 2);
  ck_assert_int_eq(s21_div(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal src1, src2, result, origin;
  s21_from_int_to_decimal(12345, &src1);
  s21_from_int_to_decimal(1, &src2);
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_int_to_decimal(12345, &origin);
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal src1, src2, result, origin;
  s21_from_int_to_decimal(1000000000, &src1);
  s21_from_int_to_decimal(10, &src2);
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_int_to_decimal(100000000, &origin);
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal src1, src2, result;
  s21_from_int_to_decimal(123456789, &src1);
  s21_from_int_to_decimal(100, &src2);
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], 0b00000000000000100000000000000000);
  ck_assert_int_eq(result.bits[2], 0b00000000000000000000000000000000);
  ck_assert_int_eq(result.bits[1], 0b00000000000000000000000000000000);
  ck_assert_int_eq(result.bits[0], 0b00000111010110111100110100010101);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal src1, src2, result;
  s21_from_int_to_decimal(-987654321, &src1);
  s21_from_int_to_decimal(1000, &src2);
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], 0b10000000000000110000000000000000);
  ck_assert_int_eq(result.bits[2], 0b00000000000000000000000000000000);
  ck_assert_int_eq(result.bits[1], 0b00000000000000000000000000000000);
  ck_assert_int_eq(result.bits[0], 0b00111010110111100110100010110001);
}
END_TEST

START_TEST(s21_div_7) {
  s21_decimal src1, src2, result, origin;
  s21_from_int_to_decimal(-999999999, &src1);
  s21_from_int_to_decimal(999999999, &src2);
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_int_to_decimal(-1, &origin);
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal src1, src2, result, origin;
  src1.bits[0] = 0b00000000000000000000000000001010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000001010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal src1, src2, result;
  s21_from_int_to_decimal(42, &src1);
  s21_from_int_to_decimal(0, &src2);

  int check = s21_div(src1, src2, &result);
  int check_origin = 3;
  ck_assert_int_eq(check_origin, check);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal src1, src2, result;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111110;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000111000000000000000000;

  int check = s21_div(src1, src2, &result);
  int check_origin = 1;
  ck_assert_int_eq(check_origin, check);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(s21_is_less_test_1) {
  // value_1 = 79; value_2 = -203;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000001001111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000011001011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_test_2) {
  // value_1 = 2; value_2 = 3;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_test_3) {
  // value_1 = 202; value_2 = 33;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000011001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000100001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_test_4) {
  // value_1 = 20.209838832; value_2 = 31331331.31313;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b10110100100110011010101011110000;
  value_1.bits[1] = 0b00000000000000000000000000000100;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000010010000000000000000;

  value_2.bits[0] = 0b01111101010010011000111000110001;
  value_2.bits[1] = 0b00000000000000000000001011011001;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000001010000000000000000;
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_test_5) {
  // value_1 = -2.2; value_2 = 3.3;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000010110;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000010000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000100001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_equal_test_1) {
  // value_1 = 79; value_2 = -203;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000001001111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000011001011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_test_2) {
  // value_1 = 2; value_2 = 3;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_test_3) {
  // value_1 = 202; value_2 = 202;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000011001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000011001010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_equal_test_4) {
  // value_1 = 20.209838832; value_2 = 31331331.31313;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b10110100100110011010101011110000;
  value_1.bits[1] = 0b00000000000000000000000000000100;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000010010000000000000000;

  value_2.bits[0] = 0b01111101010010011000111000110001;
  value_2.bits[1] = 0b00000000000000000000001011011001;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000001010000000000000000;
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_test_5) {
  // value_1 = -3.3; value_2 = -3.3;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000100001;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000010000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000100001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000010000000000000000;
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_1) {
  // value_1 = 79; value_2 = -203;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000001001111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000011001011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_2) {
  // value_1 = 2; value_2 = 2;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_3) {
  // value_1 = 202; value_2 = 33;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000011001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000100001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_4) {
  // value_1 = 20.209838832; value_2 = 31331331.31313;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b10110100100110011010101011110000;
  value_1.bits[1] = 0b00000000000000000000000000000100;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000010010000000000000000;

  value_2.bits[0] = 0b01111101010010011000111000110001;
  value_2.bits[1] = 0b00000000000000000000001011011001;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000001010000000000000000;
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_5) {
  // value_1 = -0; value_2 = 0;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_test_1) {
  // value_1 = 79; value_2 = -203;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000001001111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000011001011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_test_2) {
  // value_1 = 3; value_2 = 2;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000011;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_test_3) {
  // value_1 = 202; value_2 = 33;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000011001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000100001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_test_4) {
  // value_1 = 20.209838832; value_2 = 31331331.31313;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b10110100100110011010101011110000;
  value_1.bits[1] = 0b00000000000000000000000000000100;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000010010000000000000000;

  value_2.bits[0] = 0b01111101010010011000111000110001;
  value_2.bits[1] = 0b00000000000000000000001011011001;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000001010000000000000000;
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_greater_test_5) {
  // value_1 = -0; value_2 = 0;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_1) {
  // value_1 = -0; value_2 = 0;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_2) {
  // value_1 = 3; value_2 = 3;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000011;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_3) {
  // value_1 = 202; value_2 = 33;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000011001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000100001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_4) {
  // value_1 = -20.209838832; value_2 = 31331331.31313;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b10110100100110011010101011110000;
  value_1.bits[1] = 0b00000000000000000000000000000100;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000010010000000000000000;

  value_2.bits[0] = 0b01111101010010011000111000110001;
  value_2.bits[1] = 0b00000000000000000000001011011001;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000001010000000000000000;
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_5) {
  // value_1 = -2.2; value_2 = -2.2;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000010110;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000010000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000010110;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000010000000000000000;
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_1) {
  // value_1 = 79; value_2 = -203;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000001001111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000011001011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_2) {
  // value_1 = 2; value_2 = 2;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_3) {
  // value_1 = 202; value_2 = 33;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000011001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000100001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_4) {
  // value_1 = 20.209838832; value_2 = 31331331.31313;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b10110100100110011010101011110000;
  value_1.bits[1] = 0b00000000000000000000000000000100;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000010010000000000000000;

  value_2.bits[0] = 0b01111101010010011000111000110001;
  value_2.bits[1] = 0b00000000000000000000001011011001;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000001010000000000000000;
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_5) {
  // value_1 = -0; value_2 = 0;
  s21_decimal value_1, value_2;
  value_1.bits[0] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_sub_test_1) {
  s21_decimal value_1 = {{0b00000000000000000000010010001111,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000100000000000000000}};  // 11.67

  s21_decimal value_2 = {{0b00000000000000000000001001000001,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000110000000000000000}};  // 0.577

  s21_decimal result = {{0, 0, 0, 0}};

  s21_decimal true_result = {{0b00000000000000000010101101010101,
                              0b00000000000000000000000000000000,
                              0b00000000000000000000000000000000,
                              0b00000000000000110000000000000000}};  // 11.093

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_2) {
  s21_decimal value_1 = {{0b00000000000000000000000000000111,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b10000000000000000000000000000000}};  //-7.0

  s21_decimal value_2 = {{0b00000000000000000000000000000100,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b10000000000000000000000000000000}};  //-4.0

  s21_decimal result = {{0, 0, 0, 0}};

  s21_decimal true_result = {{0b00000000000000000000000000000011,
                              0b00000000000000000000000000000000,
                              0b00000000000000000000000000000000,
                              0b10000000000000000000000000000000}};  //-3.0
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_3) {
  s21_decimal value_1 = {{0b00000000000000000000001001000001,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000110000000000000000}};  // 0.577

  s21_decimal value_2 = {{0b00000000000000000001100011001001,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000001000000000000000000}};  // 0.6345

  s21_decimal result = {{0, 0, 0, 0}};

  s21_decimal true_result = {{0b00000000000000000000001000111111,
                              0b00000000000000000000000000000000,
                              0b00000000000000000000000000000000,
                              0b10000000000001000000000000000000}};  // -0.0575
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_4) {
  s21_decimal value_1 = {
      {0b00101110010100100110101111001001, 0b10010100001010111011111111100110,
       0b00000000000001110110111010000010,
       0b00000000000101110000000000000000}};  // 89.84349803985984390589385

  s21_decimal value_2 = {
      {0b01010100010100100110101111001001, 0b10001001000011000011101010111010,
       0b00000000000001110001100111001110,
       0b00000000000101110000000000000000}};  // 85.84349803985984390589385

  s21_decimal result = {{0, 0, 0, 0}};

  s21_decimal true_result = {{0b11011010000000000000000000000000,
                              0b00001011000111111000010100101011,
                              0b00000000000000000101010010110100,
                              0b00000000000101110000000000000000}};  // 4.0
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_5) {
  s21_decimal value_1 = {
      {0b11010000000100010101110001000011, 0b00001101000111000101001000001110,
       0b00000000000000000000000000000010,
       0b00000000000100010000000000000000}};  // 378.38208392833883203

  s21_decimal value_2 = {{0b00000010010001110111011101000111,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000010100000000000000000}};  // 0.0038238023

  s21_decimal result = {{0, 0, 0, 0}};

  s21_decimal true_result = {
      {0b11111010010010100001111011000011, 0b00001101000110101111011001001000,
       0b00000000000000000000000000000010,
       0b00000000000100010000000000000000}};  // 378.37826012603883203

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_6) {
  s21_decimal value_1 = {
      {0b00101101100001000000111010100001, 0b01000101010001010011100111011100,
       0b00000000000000000000000000000001,
       0b10000000000100010000000000000000}};  // -234.38203453538832033

  s21_decimal value_2 = {{0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000}};  // 0.0

  s21_decimal result = {{0, 0, 0, 0}};

  s21_decimal true_result = {
      {0b00101101100001000000111010100001, 0b01000101010001010011100111011100,
       0b00000000000000000000000000000001,
       0b10000000000100010000000000000000}};  // -234.38203453538832033

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_7) {
  s21_decimal value_1 = {{0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000}};  // 0.0
  s21_decimal value_2 = {
      {0b10101101100001000000111010100001, 0b01000101010001010011100111011100,
       0b00000000000000000000000000000001,
       0b10000000000100010000000000000000}};  // -234.38203453538832033

  s21_decimal result = {{0, 0, 0, 0}};

  s21_decimal true_result = {
      {0b10101101100001000000111010100001, 0b01000101010001010011100111011100,
       0b00000000000000000000000000000001,
       0b00000000000100010000000000000000}};  // 234.38203453538832033

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_8) {
  s21_decimal value_1 = {{0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000}};  // 0.0
  s21_decimal value_2 = {
      {0b10101101100001000000111010100001, 0b01000101010001010011100111011100,
       0b00000000000000000000000000000001,
       0b00000000000100010000000000000000}};  // 234.38203453538832033

  s21_decimal result = {{0, 0, 0, 0}};

  s21_decimal true_result = {
      {0b10101101100001000000111010100001, 0b01000101010001010011100111011100,
       0b00000000000000000000000000000001,
       0b10000000000100010000000000000000}};  // -234.38203453538832033

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_9) {
  s21_decimal value_1 = {{0b00000000000000000000000000001110,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000}};  // 14.0
  s21_decimal value_2 = {
      {0b00000000000000000000000000011100,
       0b00000000000000000000000000000000,  // 000000000000000000000000000000000000000000000000000000000000000011100
       0b00000000000000000000000000000000,
       0b00000000000110010000000000000000}};  // 0.0000000000000000000000028

  s21_decimal result = {{0, 0, 0, 0}};  // 0.0

  s21_decimal true_result = {
      {0b00001011111111111111111111100100, 0b00110101000110000001000111110100,
       0b00000000011100111100111000100111,
       0b00000000000110010000000000000000}};  // 13.9999999999999999999999972
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_10) {
  s21_decimal value_1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111,
       0b00000000000000000000000000000000}};  // 79228162514264337593543950335.0

  s21_decimal value_2 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111,
       0b10000000000000000000000000000000}};  // -79228162514264337593543950335.0

  s21_decimal result = {{0, 0, 0, 0}};  // 0.0

  s21_decimal true_result = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000,
       0b00000000000000000000000000000000}};  // code_error = 1

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 1);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

START_TEST(s21_sub_test_11) {
  s21_decimal value_1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111,
       0b10000000000000000000000000000000}};  // -79228162514264337593543950335.0

  s21_decimal value_2 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111,
       0b00000000000000000000000000000000}};  // 79228162514264337593543950335.0

  s21_decimal result = {{0, 0, 0, 0}};  // code_error = 2

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 2);
}
END_TEST

START_TEST(s21_sub_test_12) {
  s21_decimal value_1 = {
      {0b11001010010011100101011100010100, 0b00000000000000000100001010111101,
       0b00000000000000000000000000000000,
       0b00000000000000000000000000000000}};  // 73382910.383892
  s21_decimal value_2 = {
      {0b00100111001111000000000110010010, 0b00000000000000000000000001011001,
       0b00000000000000000000000000000000,
       0b00000000000000000000000000000000}};  // 382910.333330

  s21_decimal result = {{0b00000000000000000000000000000000,
                         0b00000000000000000000000000000000,
                         0b00000000000000000000000000000000,
                         0b00000000000000000000000000000000}};  // 0.0

  s21_decimal true_result = {
      {0b10100011000100100101010110000010, 0b00000000000000000100001001100100,
       0b00000000000000000000000000000000,
       0b00000000000000000000000000000000}};  // 73000000.050562

  s21_set_degree(&value_1, 6);
  s21_set_degree(&value_2, 6);
  s21_set_degree(&true_result, 6);

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_uint_eq(result.bits[3], true_result.bits[3]);
  ck_assert_uint_eq(result.bits[2], true_result.bits[2]);
  ck_assert_uint_eq(result.bits[1], true_result.bits[1]);
  ck_assert_uint_eq(result.bits[0], true_result.bits[0]);
}
END_TEST

/*------------------------------truncate------------------------------*/

START_TEST(s21_truncate_test_1) {
  /*1874865805.50000*/
  s21_decimal value = {
      {0b10011111000010001010100101110000, 0b00000000000000001010101010000100,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};

  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_truncate(value, &result), 0); /*1874865805*/
  ck_assert_int_eq(result.bits[3], result.bits[3]);
  ck_assert_int_eq(result.bits[2], result.bits[2]);
  ck_assert_int_eq(result.bits[1], result.bits[1]);
  ck_assert_int_eq(result.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncate_test_2) {
  /*22.222222*/
  s21_decimal value = {
      {0b00000001010100110001010110001110, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001100000000000000000}};

  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_truncate(value, &result), 0); /*22*/
  ck_assert_int_eq(result.bits[3], result.bits[3]);
  ck_assert_int_eq(result.bits[2], result.bits[2]);
  ck_assert_int_eq(result.bits[1], result.bits[1]);
  ck_assert_int_eq(result.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncate_test_3) {
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_int_eq(result.bits[3], result.bits[3]);
  ck_assert_int_eq(result.bits[2], result.bits[2]);
  ck_assert_int_eq(result.bits[1], result.bits[1]);
  ck_assert_int_eq(result.bits[0], result.bits[0]);
}
END_TEST

/*---------------------------------decimal_to_int----------------------------------*/

START_TEST(s21_decimal_to_int_test_1) {
  s21_decimal value = {
      {0b00000000011101001100101110110001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 7654321);
}
END_TEST

START_TEST(s21_decimal_to_int_test_2) {
  s21_decimal value = {
      {0b00000000011101001100101110110001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, -7654321);
}
END_TEST

START_TEST(s21_decimal_to_int_test_3) {
  s21_decimal value = {
      {0b11111111111111111111111111111111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 1);
}
END_TEST

START_TEST(s21_decimal_to_int_test_4) {  // uint max
  s21_decimal value = {
      {0b11111111111111111111111111111111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 1);
}
END_TEST

START_TEST(s21_decimal_to_int_test_5) {  // uint_max scale = 7
  s21_decimal value = {
      {0b11111111111111111111111111111111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001110000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 429);
}
END_TEST

START_TEST(s21_decimal_to_int_test_6) {  // 1.37438953471
  s21_decimal value = {
      {0b11111111111111111111111111111111, 0b00000000000000000000000000011111,
       0b00000000000000000000000000000000, 0b00000000000010110000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_decimal_to_int_test_7) {  // -0?
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_decimal_to_int_test_9) {  // 1.8446744073709551616
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000001, 0b00000000000100110000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_decimal_to_int_test_10) {  // 0.18446744073709551616
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000001, 0b00000000000101000000000000000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

/*--------------------s21_int_to_decimal--------------------*/

START_TEST(s21_int_to_decimal_test_1) {
  int value = 7654321;
  s21_decimal result = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), 0);
  ck_assert_int_eq(result.bits[3], result.bits[3]);
  ck_assert_int_eq(result.bits[2], result.bits[2]);
  ck_assert_int_eq(result.bits[1], result.bits[1]);
  ck_assert_int_eq(result.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_int_to_decimal_test_2) {
  int value = -7654321;
  s21_decimal result = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), 0);
  ck_assert_int_eq(result.bits[3], result.bits[3]);
  ck_assert_int_eq(result.bits[2], result.bits[2]);
  ck_assert_int_eq(result.bits[1], result.bits[1]);
  ck_assert_int_eq(result.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_int_to_decimal_test_3) {
  int value = 0;
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), 0);
  ck_assert_int_eq(result.bits[3], result.bits[3]);
  ck_assert_int_eq(result.bits[2], result.bits[2]);
  ck_assert_int_eq(result.bits[1], result.bits[1]);
  ck_assert_int_eq(result.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_int_to_decimal_test_4) {
  int value = 2147483647;
  s21_decimal result = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), 0);

  ck_assert_int_eq(result.bits[3], result.bits[3]);
  ck_assert_int_eq(result.bits[2], result.bits[2]);
  ck_assert_int_eq(result.bits[1], result.bits[1]);
  ck_assert_int_eq(result.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_int_to_decimal_test_5) {
  int value = -2147483648;
  s21_decimal result = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), 0);

  ck_assert_int_eq(result.bits[3], result.bits[3]);
  ck_assert_int_eq(result.bits[2], result.bits[2]);
  ck_assert_int_eq(result.bits[1], result.bits[1]);
  ck_assert_int_eq(result.bits[0], result.bits[0]);
}
END_TEST
/*---------------------------from_decimal_to_float------------------------------------*/

START_TEST(s21_decimal_to_float_test_1) {
  /*2144*/
  s21_decimal value = {
      {0b0000000000000000000100001100000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  float result = 0.0;
  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), 0);
  ck_assert_float_eq_tol(result, 2144.000000, EPS);
}
END_TEST

START_TEST(s21_decimal_to_float_test_2) {
  /*-2144*/
  s21_decimal value = {
      {0b0000000000000000000100001100000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  float result = 0.0;
  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), 0);
  ck_assert_float_eq_tol(result, -2144.000000, EPS);
}
END_TEST

START_TEST(s21_decimal_to_float_test_8) {
  s21_decimal value = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  float result = 0.0;
  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), 0);
  ck_assert_float_eq_tol(result, 79228162514264337593543950335.000000, EPS);
}
END_TEST

/*---------------------------from_float_to_decimal------------------------------------*/

START_TEST(s21_float_to_decimal_test_5) {
  float value = 12.75;
  s21_decimal true = {
      {0b00000000000000000000010011111011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_set_degree(&true, 2);
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_from_float_to_decimal(value, &result), 0);

  ck_assert_int_eq(result.bits[3], true.bits[3]);
  ck_assert_int_eq(result.bits[2], true.bits[2]);
  ck_assert_int_eq(result.bits[1], true.bits[1]);
  ck_assert_int_eq(result.bits[0], true.bits[0]);
}
END_TEST
// /*-------------------------------------------------*/

START_TEST(s21_float_to_decimal_test_7) {
  float value = 1e-29;
  s21_decimal true = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_from_float_to_decimal(value, &result), 1);

  ck_assert_int_eq(result.bits[3], true.bits[3]);
  ck_assert_int_eq(result.bits[2], true.bits[2]);
  ck_assert_int_eq(result.bits[1], true.bits[1]);
  ck_assert_int_eq(result.bits[0], true.bits[0]);
}
END_TEST
/*-------------------------------------------------*/

START_TEST(s21_float_to_decimal_test_8) {
  float value = 1e+31;

  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_from_float_to_decimal(value, &result), 1);
}
END_TEST
/*-------------------------------------------------*/

START_TEST(s21_float_to_decimal_test_9) {
  float value = 3.67;
  s21_decimal true = {
      {0b00000000000000000000000101101111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_set_degree(&true, 2);
  ck_assert_int_eq(s21_from_float_to_decimal(value, &result), 0);

  ck_assert_int_eq(result.bits[3], true.bits[3]);
  ck_assert_int_eq(result.bits[2], true.bits[2]);
  ck_assert_int_eq(result.bits[1], true.bits[1]);
  ck_assert_int_eq(result.bits[0], true.bits[0]);
}
END_TEST
/*-------------------------------------------------*/

// Функция, создающая набор тестов
Suite *test_suite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("decimal");

  // Создание тестового случая и добавление тестовой функции
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_s21_negate_1);
  tcase_add_test(tc_core, test_s21_negate_2);
  tcase_add_test(tc_core, test_s21_negate_3);

  tcase_add_test(tc_core, test_s21_round_1);
  tcase_add_test(tc_core, test_s21_round_2);
  tcase_add_test(tc_core, test_s21_round_3);

  tcase_add_test(tc_core, test_s21_floor_1);
  tcase_add_test(tc_core, test_s21_floor_2);
  tcase_add_test(tc_core, test_s21_floor_3);

  tcase_add_test(tc_core, test_s21_add_1);
  tcase_add_test(tc_core, test_s21_add_2);
  tcase_add_test(tc_core, test_s21_add_3);
  tcase_add_test(tc_core, test_s21_add_4);
  tcase_add_test(tc_core, test_s21_add_5);
  tcase_add_test(tc_core, test_s21_add_6);
  tcase_add_test(tc_core, test_s21_add_7);
  tcase_add_test(tc_core, test_s21_add_8);
  tcase_add_test(tc_core, test_s21_add_9);
  tcase_add_test(tc_core, test_s21_add_10);

  tcase_add_test(tc_core, test_s21_mul_1);
  tcase_add_test(tc_core, test_s21_mul_2);
  tcase_add_test(tc_core, test_s21_mul_3);
  tcase_add_test(tc_core, test_s21_mul_4);
  tcase_add_test(tc_core, test_s21_mul_5);
  tcase_add_test(tc_core, test_s21_mul_6);
  tcase_add_test(tc_core, test_s21_mul_7);
  tcase_add_test(tc_core, test_s21_mul_8);

  tcase_add_test(tc_core, s21_div_1);
  tcase_add_test(tc_core, s21_div_2);
  tcase_add_test(tc_core, s21_div_3);
  tcase_add_test(tc_core, s21_div_4);
  tcase_add_test(tc_core, s21_div_5);
  tcase_add_test(tc_core, s21_div_6);
  tcase_add_test(tc_core, s21_div_7);
  tcase_add_test(tc_core, s21_div_8);
  tcase_add_test(tc_core, s21_div_9);
  tcase_add_test(tc_core, s21_div_10);

  tcase_add_test(tc_core, s21_is_less_test_1);
  tcase_add_test(tc_core, s21_is_less_test_2);
  tcase_add_test(tc_core, s21_is_less_test_3);
  tcase_add_test(tc_core, s21_is_less_test_4);
  tcase_add_test(tc_core, s21_is_less_test_5);

  tcase_add_test(tc_core, s21_is_equal_test_1);
  tcase_add_test(tc_core, s21_is_equal_test_2);
  tcase_add_test(tc_core, s21_is_equal_test_3);
  tcase_add_test(tc_core, s21_is_equal_test_4);
  tcase_add_test(tc_core, s21_is_equal_test_5);

  tcase_add_test(tc_core, s21_is_greater_or_equal_test_1);
  tcase_add_test(tc_core, s21_is_greater_or_equal_test_2);
  tcase_add_test(tc_core, s21_is_greater_or_equal_test_3);
  tcase_add_test(tc_core, s21_is_greater_or_equal_test_4);
  tcase_add_test(tc_core, s21_is_greater_or_equal_test_5);

  tcase_add_test(tc_core, s21_is_greater_test_1);
  tcase_add_test(tc_core, s21_is_greater_test_2);
  tcase_add_test(tc_core, s21_is_greater_test_3);
  tcase_add_test(tc_core, s21_is_greater_test_4);
  tcase_add_test(tc_core, s21_is_greater_test_5);

  tcase_add_test(tc_core, s21_is_less_or_equal_test_1);
  tcase_add_test(tc_core, s21_is_less_or_equal_test_2);
  tcase_add_test(tc_core, s21_is_less_or_equal_test_3);
  tcase_add_test(tc_core, s21_is_less_or_equal_test_4);
  tcase_add_test(tc_core, s21_is_less_or_equal_test_5);

  tcase_add_test(tc_core, s21_is_not_equal_test_1);
  tcase_add_test(tc_core, s21_is_not_equal_test_2);
  tcase_add_test(tc_core, s21_is_not_equal_test_3);
  tcase_add_test(tc_core, s21_is_not_equal_test_4);
  tcase_add_test(tc_core, s21_is_not_equal_test_5);

  tcase_add_test(tc_core, s21_truncate_test_1);
  tcase_add_test(tc_core, s21_truncate_test_2);
  tcase_add_test(tc_core, s21_truncate_test_3);

  tcase_add_test(tc_core, s21_sub_test_1);
  tcase_add_test(tc_core, s21_sub_test_2);
  tcase_add_test(tc_core, s21_sub_test_3);
  tcase_add_test(tc_core, s21_sub_test_4);
  tcase_add_test(tc_core, s21_sub_test_5);
  tcase_add_test(tc_core, s21_sub_test_6);
  tcase_add_test(tc_core, s21_sub_test_7);
  tcase_add_test(tc_core, s21_sub_test_8);
  tcase_add_test(tc_core, s21_sub_test_9);
  tcase_add_test(tc_core, s21_sub_test_10);
  tcase_add_test(tc_core, s21_sub_test_11);
  tcase_add_test(tc_core, s21_sub_test_12);

  tcase_add_test(tc_core, s21_int_to_decimal_test_1);
  tcase_add_test(tc_core, s21_int_to_decimal_test_2);
  tcase_add_test(tc_core, s21_int_to_decimal_test_3);
  tcase_add_test(tc_core, s21_int_to_decimal_test_4);
  tcase_add_test(tc_core, s21_int_to_decimal_test_5);

  tcase_add_test(tc_core, s21_decimal_to_int_test_1);
  tcase_add_test(tc_core, s21_decimal_to_int_test_2);
  tcase_add_test(tc_core, s21_decimal_to_int_test_3);
  tcase_add_test(tc_core, s21_decimal_to_int_test_4);
  tcase_add_test(tc_core, s21_decimal_to_int_test_5);
  tcase_add_test(tc_core, s21_decimal_to_int_test_6);
  tcase_add_test(tc_core, s21_decimal_to_int_test_7);
  tcase_add_test(tc_core, s21_decimal_to_int_test_9);
  tcase_add_test(tc_core, s21_decimal_to_int_test_10);

  tcase_add_test(tc_core, s21_decimal_to_float_test_1);
  tcase_add_test(tc_core, s21_decimal_to_float_test_2);
  tcase_add_test(tc_core, s21_decimal_to_float_test_8);

  tcase_add_test(tc_core, s21_float_to_decimal_test_5);
  tcase_add_test(tc_core, s21_float_to_decimal_test_7);
  tcase_add_test(tc_core, s21_float_to_decimal_test_8);
  tcase_add_test(tc_core, s21_float_to_decimal_test_9);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  // Создание исполнителя тестов
  SRunner *runner = srunner_create(test_suite());
  srunner_set_fork_status(runner, CK_NOFORK);
  // Запуск всех тестов
  srunner_run_all(runner, CK_VERBOSE);

  // Получение количества неудачных тестов
  int failures = srunner_ntests_failed(runner);

  // Освобождение памяти, занятой исполнителем тестов
  srunner_free(runner);

  // Возврат количества неудачных тестов в качестве кода возврата
  return (failures == 0) ? 0 : 1;
}
