#include "lib_decimal.h"

int lib_is_greater(lib_decimal value_1, lib_decimal value_2) {
  lib_long_decimal n1, n2;
  int mult = 0;
  decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  int minus1 = get_minus(value_1);
  int minus2 = get_minus(value_2);
  int result = decimal_great(n1, n2);

  if (minus2 && !minus1) result = 1;
  if (minus1 && !minus2) result = 0;
  if (minus1 && minus2) {
    if (result)
      result = 0;
    else
      result = 1;
  }
  return result;
}

int lib_is_less(lib_decimal value_1, lib_decimal value_2) {
  lib_long_decimal n1, n2;
  int mult = 0;
  decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  int minus1 = get_minus(value_1);
  int minus2 = get_minus(value_2);
  int result = decimal_lite(n1, n2);

  if (minus2 && !minus1) result = 0;
  if (minus1 && !minus2) result = 1;
  if (minus1 && minus2) {
    if (decimal_great(n1, n2))
      result = 1;
    else
      result = 0;
  }
  return result;
}

int lib_is_equal(lib_decimal value_1, lib_decimal value_2) {
  lib_long_decimal n1, n2;
  int mult = 0;
  decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  int minus1 = get_minus(value_1);
  int minus2 = get_minus(value_2);
  int result = decimal_equal(n1, n2);
  if (result && !(is_null(value_1) && is_null(value_2)) && (minus1 != minus2))
    result = 0;
  return result;
}

int lib_is_not_equal(lib_decimal value_1, lib_decimal value_2) {
  return !lib_is_equal(value_1, value_2);
}

int lib_is_less_or_equal(lib_decimal value_1, lib_decimal value_2) {
  return lib_is_less(value_1, value_2) == 1 ||
         lib_is_equal(value_1, value_2) == 1;
}

int lib_is_greater_or_equal(lib_decimal value_1, lib_decimal value_2) {
  return lib_is_greater(value_1, value_2) == 1 ||
         lib_is_equal(value_1, value_2) == 1;
}
