#ifndef SRC_lib_DECIMAL_H_
#define SRC_lib_DECIMAL_H_

#include <math.h>
#include <stdlib.h>

typedef struct {
    unsigned int bits[4];
} lib_decimal;

typedef struct {
    unsigned int bits[6];
} lib_long_decimal;

#define lib_INT_MAX 4294967295

int lib_add(lib_decimal value_1, lib_decimal value_2, lib_decimal *result);
int lib_sub(lib_decimal value_1, lib_decimal value_2, lib_decimal *result);
int lib_mul(lib_decimal value_1, lib_decimal value_2, lib_decimal *result);
int lib_div(lib_decimal value_1, lib_decimal value_2, lib_decimal *result);
int lib_mod(lib_decimal value_1, lib_decimal value_2, lib_decimal *result);

int lib_is_less(lib_decimal, lib_decimal);
int lib_is_less_or_equal(lib_decimal, lib_decimal);
int lib_is_greater(lib_decimal, lib_decimal);
int lib_is_greater_or_equal(lib_decimal, lib_decimal);
int lib_is_equal(lib_decimal, lib_decimal);
int lib_is_not_equal(lib_decimal, lib_decimal);

int lib_from_int_to_decimal(int src, lib_decimal *dst);
int lib_from_float_to_decimal(float src, lib_decimal *dst);
int lib_from_decimal_to_int(lib_decimal src, int *dst);
int lib_from_decimal_to_float(lib_decimal src, float *dst);

int lib_floor(lib_decimal value, lib_decimal *result);
int lib_round(lib_decimal value, lib_decimal *result);
int lib_truncate(lib_decimal value, lib_decimal *result);
int lib_negate(lib_decimal value, lib_decimal *result);

lib_decimal new_decimal(unsigned int bit0, unsigned int bit1, unsigned int bit2,
                        int minus, int multiplier);
int get_bit_status(lib_decimal num, int index);
int get_bit_status_long(lib_long_decimal num, int index);
void set_bit(lib_decimal *num, int index);
void set_bit_long(lib_long_decimal *num, int index);
void reset_bit(lib_decimal *num, int index);
int simple_add(lib_long_decimal num1, lib_long_decimal num2,
               lib_long_decimal *result);
int get_multiplier(lib_decimal number);
void set_multiplier(lib_decimal *number, int multipler);
int left_bit_shift(lib_long_decimal *number, int count);
int right_bit_shift(lib_long_decimal *number, int count);
int decimal_mul_10(lib_long_decimal *number, int count);
void set_minus(lib_decimal *number);
void reset_minus(lib_decimal *number);
int get_minus(lib_decimal number);
int decimal_div_10(lib_long_decimal *number, int count);

int decimal_great(lib_long_decimal num1, lib_long_decimal num2);
int decimal_equal(lib_long_decimal num1, lib_long_decimal num2);
int decimal_lite(lib_long_decimal num1, lib_long_decimal num2);

void reset_decimal(lib_decimal *number);
void reset_decimal_long(lib_long_decimal *number);
lib_decimal copy_decimal(lib_decimal number);
lib_long_decimal copy_decimal_long(lib_long_decimal number);
lib_long_decimal convert_decimal_to_long(lib_decimal number);
lib_decimal convert_long_to_decimal(lib_long_decimal number, int operation,
                                    int *multiplier, int *func_status);
void inverse_decimal(lib_long_decimal *number);
int get_left_index(lib_long_decimal number);
int get_rang(lib_long_decimal number);

int del_nulls(lib_long_decimal *number, int *mult);
void inc_decimal_long(lib_long_decimal *number);
int is_null(lib_decimal num);

int decimal_simple_div(lib_long_decimal dividend, lib_long_decimal divider,
                       lib_long_decimal *result, lib_long_decimal *ostatok);

int get_float_params(float number, int *rank, int *mantissa);

int _pow(int x, int y);
double float_div10(double num, int count);
double float_mul10(double num, int count);

#endif  // SRC_lib_DECIMAL_H_