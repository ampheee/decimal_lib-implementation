#include "lib_decimal.h"

int lib_from_int_to_decimal(int src, lib_decimal *dst) {
  reset_decimal(dst);
  dst->bits[0] = abs(src);
  if (src < 0) set_minus(dst);
  return 0;
}

int lib_from_float_to_decimal(float src, lib_decimal *dst) {
  reset_decimal(dst);
  int float_rank, float_mantissa;
  get_float_params(src, &float_rank, &float_mantissa);
  if (!float_mantissa) return 0;
  if (float_rank < -28) return 1;
  lib_long_decimal number;
  reset_decimal_long(&number);

  if (float_mantissa > 0)
    number.bits[0] = float_mantissa;
  else
    number.bits[0] = -float_mantissa;

  if (float_rank > 0) decimal_mul_10(&number, float_rank);

  int mult = 0;
  if (float_rank < 0) mult = -float_rank;
  int res = 0;

  *dst = convert_long_to_decimal(number, 3, &mult, &res);
  if (float_mantissa < 0) set_minus(dst);
  set_multiplier(dst, mult);

  return res;
}

int lib_from_decimal_to_int(lib_decimal src, int *dst) {
  int result = 0;
  int mult = get_multiplier(src);
  int minus = get_minus(src);
  lib_long_decimal num = convert_decimal_to_long(src);
  if (mult) decimal_div_10(&num, mult);
  if (num.bits[1]) result = 1;
  if (num.bits[1] && minus) result = 2;
  if (!num.bits[1]) {
    *dst = num.bits[0];
    if (minus) *dst = *dst * (-1);
  }
  return result;
}

int lib_from_decimal_to_float(lib_decimal src, float *dst) {
  int result = 0;
  int mult = get_multiplier(src);
  int minus = get_minus(src);

  double dst1 = (src.bits[0] + src.bits[1] * (lib_INT_MAX + 1) +
                 src.bits[2] * pow(lib_INT_MAX + 1, 2));
  dst1 = float_div10(dst1, mult);
  *dst = (float)dst1;
  if (minus) *dst = *dst * (-1);

  return result;
}