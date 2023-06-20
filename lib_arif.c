#include "lib_decimal.h"

int lib_add(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) {
  lib_long_decimal n1, n2, res_long;
  reset_decimal_long(&res_long);

  int mult = 0;
  int func_result = 0;
  decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);
  int minus_flag = 0;
  int n1_great = decimal_great(n1, n2);

  if (!minus_flag1 && !minus_flag2) {  // n1>0 & n2>0
    func_result = simple_add(n1, n2, &res_long);
  }

  if (minus_flag1 && minus_flag2) {  // n1<0 & n2<0
    func_result = simple_add(n1, n2, &res_long);
    minus_flag = 1;
    if (func_result == 1) func_result = 2;
  }

  if (!minus_flag1 && minus_flag2 && n1_great) {  // n1>0 & n2<0 & |n1|>|n2|
    inverse_decimal(&n2);
    simple_add(n1, n2, &res_long);
  }

  if (!minus_flag1 && minus_flag2 && !n1_great) {  // n1>0 & n2<0 & |n1|<|n2|
    inverse_decimal(&n1);
    simple_add(n1, n2, &res_long);
    minus_flag = 1;
  }

  if (minus_flag1 && !minus_flag2 && !n1_great) {  // n1<0 & n2>0 & |n1|<|n2|
    inverse_decimal(&n1);
    simple_add(n1, n2, &res_long);
  }

  if (minus_flag1 && !minus_flag2 && n1_great) {  // n1<0 & n2>0 & |n1|>|n2|
    inverse_decimal(&n2);
    simple_add(n1, n2, &res_long);
    minus_flag = 1;
  }

  *result = convert_long_to_decimal(res_long, 0, &mult, &func_result);
  set_multiplier(result, mult);
  if (minus_flag) set_minus(result);

  if (is_null(*result) && (minus_flag1)) set_minus(result);
  if (is_null(*result) && (!minus_flag1)) reset_minus(result);

  if (func_result == 2 && minus_flag) func_result = 3;

  return func_result;
}

int lib_sub(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) {
  lib_decimal n1 = copy_decimal(value_1);
  lib_decimal n2 = copy_decimal(value_2);

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);
  if (!minus_flag2) set_minus(&n2);
  if (minus_flag2) reset_minus(&n2);
  int func_result = lib_add(n1, n2, result);

  if (is_null(*result) && (!minus_flag1 || minus_flag2)) reset_minus(result);
  if (is_null(*result) && (minus_flag1 && minus_flag2)) set_minus(result);

  return func_result;
}

int lib_mul(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) {
  lib_long_decimal res_long;
  reset_decimal_long(&res_long);
  int func_result = 0;

  reset_decimal(result);

  if (is_null(value_1) || is_null(value_2)) return func_result;

  lib_long_decimal n1 = convert_decimal_to_long(value_1);
  lib_long_decimal n2 = convert_decimal_to_long(value_2);

  int left_index = get_left_index(n2);
  lib_long_decimal temp = copy_decimal_long(n1);

  for (int i = 0; i < left_index + 1; i++) {
    if (i != 0) left_bit_shift(&temp, 1);
    if (get_bit_status_long(n2, i)) {
      simple_add(res_long, temp, &res_long);
    }
  }

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);
  int mult1 = get_multiplier(value_1);
  int mult2 = get_multiplier(value_2);
  int mult = mult1 + mult2;

  *result = convert_long_to_decimal(res_long, 0, &mult, &func_result);
  reset_minus(result);
  if ((minus_flag1 && !minus_flag2) || (!minus_flag1 && minus_flag2))
    set_minus(result);
  set_multiplier(result, mult);
  return func_result;
}

int lib_div(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) {
  reset_decimal(result);
  int func_result = 0;

  if (is_null(value_2)) {
    func_result = 3;
    return func_result;
  }

  lib_long_decimal n1 = convert_decimal_to_long(value_1);
  lib_long_decimal n2 = convert_decimal_to_long(value_2);

  lib_long_decimal res_long;
  lib_long_decimal ost_long;

  int mult1 = get_multiplier(value_1);
  int mult2 = get_multiplier(value_2);
  int mult = 0;
  int rang1 = get_rang(n1);
  int rang2 = get_rang(n2);
  int shift = 30 - rang1 + rang2;

  decimal_mul_10(&n1, shift);
  mult = mult1 + shift - mult2;

  decimal_simple_div(n1, n2, &res_long, &ost_long);
  del_nulls(&res_long, &mult);

  *result = convert_long_to_decimal(res_long, 1, &mult, &func_result);
  set_multiplier(result, mult);
  reset_minus(result);

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);

  if ((minus_flag1 && !minus_flag2) || (!minus_flag1 && minus_flag2))
    set_minus(result);

  return func_result;
}