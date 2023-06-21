#include "lib_decimal.h"

#include <math.h>

lib_decimal new_decimal(unsigned int bit0, unsigned int bit1, unsigned int bit2,
                        int minus, int multiplier) {
  lib_decimal number;
  reset_decimal(&number);
  number.bits[0] = bit0;
  number.bits[1] = bit1;
  number.bits[2] = bit2;
  if (minus) set_minus(&number);
  if (multiplier) set_multiplier(&number, multiplier);
  return number;
}

void set_minus(lib_decimal *number) { set_bit(number, 31 + 3 * 32); }

int get_minus(lib_decimal number) {
  return get_bit_status(number, 31 + 3 * 32);
}

void reset_decimal(lib_decimal *number) {
  for (int i = 0; i < 4; i++) number->bits[i] = 0;
}

void reset_decimal_long(lib_long_decimal *number) {
  for (int i = 0; i < 6; i++) number->bits[i] = 0;
}

lib_decimal copy_decimal(lib_decimal number) {
  lib_decimal result;
  for (int i = 0; i < 4; i++) result.bits[i] = number.bits[i];
  return result;
}

lib_long_decimal copy_decimal_long(lib_long_decimal number) {
  lib_long_decimal result;
  for (int i = 0; i < 6; i++) result.bits[i] = number.bits[i];
  return result;
}

lib_long_decimal convert_decimal_to_long(lib_decimal number) {
  lib_long_decimal result;
  reset_decimal_long(&result);
  for (int i = 0; i < 3; i++) result.bits[i] = number.bits[i];
  return result;
}

void inc_decimal_long(lib_long_decimal *number) {
  lib_long_decimal one = {{1, 0, 0, 0, 0, 0}};
  simple_add(*number, one, number);
}

lib_decimal convert_long_to_decimal(lib_long_decimal number, int operation,
                                    int *multiplier, int *func_status) {
  // 0 for add, sub, mul
  // 1 for div
  // 2 for mod
  // 3 for float convert
  lib_decimal result;
  reset_decimal(&result);

  int rang_long = get_rang(number);

  int temp = 0;
  int big_multiplier = 0;
  if (*multiplier > 28) big_multiplier = 1;

  int num_free = 29 - rang_long + *multiplier;
  if (*multiplier > num_free && num_free >= 0) {
    for (int i = 0; i < *multiplier - num_free; i++) {
      temp = decimal_div_10(&number, 1);
    }
    *multiplier = num_free;
  }

  while (*multiplier > 28) {
    temp = decimal_div_10(&number, 1);
    *multiplier = *multiplier - 1;
  }

  if (temp == 1) inc_decimal_long(&number);
  if (operation == 1 || operation == 3) del_nulls(&number, multiplier);

  for (int i = 0; i < 3; i++) result.bits[i] = number.bits[i];

  if (operation == 1 && big_multiplier && is_null(result)) *func_status = 2;
  if (operation == 0 && (number.bits[3] || number.bits[4] || number.bits[5]))
    *func_status = 2;
  if (operation == 3 && (number.bits[3] || number.bits[4] || number.bits[5]))
    *func_status = 2;

  return result;
}

void inverse_decimal(lib_long_decimal *number) {
  for (int i = 0; i < 6; i++) number->bits[i] = ~number->bits[i];
  lib_long_decimal one = {{1, 0, 0, 0, 0, 0}};
  simple_add(*number, one, number);
}

int get_bit_status_long(lib_long_decimal num, int index) {
  int func_res = 0;
  unsigned int mask = 1;
  mask = mask << index % 32;
  unsigned int result = 0;
  int bit_index = round(index / 32);
  result = num.bits[bit_index] & mask;
  if (result > 0) func_res = 1;
  return func_res;
}

int get_bit_status(lib_decimal num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  unsigned int result = num.bits[index / 32] & mask;
  if (result > 0)
    return 1;
  else
    return 0;
}

void set_bit(lib_decimal *num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  num->bits[index / 32] = num->bits[index / 32] | mask;
}

void set_bit_long(lib_long_decimal *num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  num->bits[index / 32] = num->bits[index / 32] | mask;
}

void reset_bit(lib_decimal *num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  mask = ~mask;
  num->bits[index / 32] = num->bits[index / 32] & mask;
}

void reset_minus(lib_decimal *number) { reset_bit(number, 31 + 3 * 32); }

int simple_add(lib_long_decimal num1, lib_long_decimal num2,
               lib_long_decimal *result) {
  int perenos = 0;

  reset_decimal_long(result);

  for (int i = 0; i < 192; i++) {
    int temp_summ = 0;
    temp_summ = get_bit_status_long(num1, i) + get_bit_status_long(num2, i);
    if (temp_summ == 2 && perenos) set_bit_long(result, i);
    if (temp_summ == 1 && !perenos) set_bit_long(result, i);
    if (temp_summ == 0 && perenos) {
      set_bit_long(result, i);
      perenos = 0;
    }
    if (temp_summ == 2) perenos = 1;
  }
  if (perenos == 1) return 1;
  return 0;
}

int get_multiplier(lib_decimal number) {
  int result = 0;
  for (int i = 16; i < 24; i++) {
    int bit = 0;
    bit = get_bit_status(number, i + 3 * 32);
    result = result + _pow(2, i - 16) * bit;
  }
  return result;
}

void set_multiplier(lib_decimal *number, int multipler) {
  int minus = get_bit_status(*number, 96 + 31);
  number->bits[3] = multipler << 16;
  if (minus) set_minus(number);
}

int left_bit_shift(lib_long_decimal *number, int count) {
  for (int j = 0; j < count; j++) {
    for (int i = 0; i < 6; i++) {
      number->bits[5 - i] = number->bits[5 - i] << 1;
      if (i < 5)
        if (get_bit_status_long(*number, 31 + (4 - i) * 32))
          set_bit_long(number, 0 + 32 * (5 - i));
    }
  }
  return 0;
}

int right_bit_shift(lib_long_decimal *number, int count) {
  for (int j = 0; j < count; j++) {
    for (int i = 0; i < 6; i++) {
      number->bits[i] = number->bits[i] >> 1;
      if (i < 5)
        if (get_bit_status_long(*number, 32 + i * 32))
          set_bit_long(number, 31 + 32 * i);
    }
  }
  return 0;
}

int decimal_mul_10(lib_long_decimal *number, int count) {
  for (int i = 0; i < count; i++) {
    lib_long_decimal temp = copy_decimal_long(*number);
    lib_long_decimal temp2 = copy_decimal_long(*number);
    left_bit_shift(&temp, 1);
    left_bit_shift(&temp2, 3);
    simple_add(temp, temp2, number);
  }
  return 0;
}

int decimal_simple_div(lib_long_decimal dividend, lib_long_decimal divider,
                       lib_long_decimal *result, lib_long_decimal *ostatok) {
  lib_long_decimal temp_dividend = copy_decimal_long(dividend);
  lib_long_decimal temp_divider = copy_decimal_long(divider);

  reset_decimal_long(result);

  int count = get_left_index(temp_dividend) - get_left_index(temp_divider);

  left_bit_shift(&temp_divider, count);
  lib_long_decimal temp_divider_inv;

  for (int i = 0; i < count + 1; i++) {
    if (i != 0) right_bit_shift(&temp_divider, 1);

    left_bit_shift(result, 1);

    if (decimal_great(temp_dividend, temp_divider) ||
        decimal_equal(temp_dividend, temp_divider)) {
      temp_divider_inv = copy_decimal_long(temp_divider);
      inverse_decimal(&temp_divider_inv);
      simple_add(temp_dividend, temp_divider_inv, &temp_dividend);
      set_bit_long(result, 0);
    }
  }
  *ostatok = copy_decimal_long(temp_dividend);
  return 0;
}

int decimal_div_10(lib_long_decimal *number, int count) {
  lib_long_decimal temp = copy_decimal_long(*number);
  lib_long_decimal ten = {{10, 0, 0, 0, 0, 0}};
  lib_long_decimal result = copy_decimal_long(*number);
  lib_long_decimal ost = {{0, 0, 0, 0}};
  for (int i = 0; i < count; i++) {
    decimal_simple_div(temp, ten, &result, &ost);
    temp = copy_decimal_long(result);
  }
  *number = copy_decimal_long(result);
  if (ost.bits[0] == 0)
    return 0;
  else if (ost.bits[0] >= 5)
    return 1;
  else
    return 2;
}

int decimal_normalize(lib_decimal num1, lib_decimal num2,
                      lib_long_decimal *n1_out, lib_long_decimal *n2_out,
                      int *multipler) {
  int mult1 = get_multiplier(num1);
  int mult2 = get_multiplier(num2);

  if (mult1 > mult2)
    *multipler = mult1;
  else
    *multipler = mult2;

  *n1_out = convert_decimal_to_long(num1);
  *n2_out = convert_decimal_to_long(num2);
  if (*multipler > mult1) decimal_mul_10(n1_out, *multipler - mult1);
  if (*multipler > mult2) decimal_mul_10(n2_out, *multipler - mult2);
  return 0;
}

int decimal_great(lib_long_decimal num1, lib_long_decimal num2) {
  int result = 0, bit1 = 0, bit2 = 0;
  for (int i = 0; i < 192 && bit1 == bit2; i++) {
    bit1 = get_bit_status_long(num1, 191 - i);
    bit2 = get_bit_status_long(num2, 191 - i);
    if (bit1 != bit2) {
      if (bit1 > bit2) result = 1;
    }
  }
  return result;
}

int decimal_equal(lib_long_decimal num1, lib_long_decimal num2) {
  int result = 1, bit1 = 0, bit2 = 0;
  for (int i = 0; i < 192 && bit1 == bit2; i++) {
    bit1 = get_bit_status_long(num1, 191 - i);
    bit2 = get_bit_status_long(num2, 191 - i);
    if (bit1 != bit2) result = 0;
  }
  return result;
}

int decimal_lite(lib_long_decimal num1, lib_long_decimal num2) {
  int result = 0, bit1 = 0, bit2 = 0;
  for (int i = 0; i < 192 && bit1 == bit2; i++) {
    bit1 = get_bit_status_long(num1, 191 - i);
    bit2 = get_bit_status_long(num2, 191 - i);
    if (bit1 != bit2) {
      if (bit1 < bit2) result = 1;
    }
  }
  return result;
}

int get_left_index(lib_long_decimal number) {
  int i = 191;
  while (get_bit_status_long(number, i) == 0 && i != 0) {
    i--;
  }
  return i;
}

int get_rang(lib_long_decimal number) {
  int rang = 0;
  lib_long_decimal temp = {{1, 0, 0, 0, 0, 0}};
  while (!decimal_great(temp, number)) {
    rang++;
    decimal_mul_10(&temp, 1);
  }
  return rang;
}

int del_nulls(lib_long_decimal *number, int *mult) {
  lib_long_decimal temp = copy_decimal_long(*number);

  while (*mult != 0 && decimal_div_10(&temp, 1) == 0) {
    decimal_div_10(number, 1);
    *mult = *mult - 1;
  }
  return 0;
}

int is_null(lib_decimal num) {
  if (!num.bits[0] && !num.bits[1] && !num.bits[2])
    return 1;
  else
    return 0;
}

int lib_mod(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) {
  int func_result = 0;

  if (is_null(value_2)) {
    func_result = 3;
    return func_result;
  }

  lib_long_decimal n1;
  lib_long_decimal n2;
  lib_long_decimal div_result;
  lib_long_decimal div_mod;
  int mult = 0;

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);

  decimal_normalize(value_1, value_2, &n1, &n2, &mult);
  decimal_simple_div(n1, n2, &div_result, &div_mod);

  *result = convert_long_to_decimal(div_mod, 2, &mult, &func_result);

  set_multiplier(result, mult);
  if ((minus_flag1 && !minus_flag2) || (minus_flag1 && minus_flag2))
    set_minus(result);

  return func_result;
}

int _pow(int x, int y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  return x * _pow(x, y - 1);
}

double float_div10(double num, int count) {
  double result = num;
  for (int i = 0; i < count; i++) result /= 10;
  return result;
}

double float_mul10(double num, int count) {
  double result = num;
  for (int i = 0; i < count; i++) result *= 10;
  return result;
}

int get_float_params(float number, int *rank, int *mantissa) {
  int func_res = 0;

  union {
    float fl;
    unsigned int dw;
  } f;
  f.fl = number;
  *rank = (f.dw >> 23) & 0xFF;
  *rank = (*rank - 127) / 3;

  double mantissa_float;
  if (*rank > 0)
    mantissa_float = float_div10(f.fl, *rank);
  else
    mantissa_float = float_mul10(f.fl, -(*rank));

  *mantissa = round(float_mul10(mantissa_float, 6));
  *rank = *rank - 6;
  return func_res;
}
