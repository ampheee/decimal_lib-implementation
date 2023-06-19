# lib_decimal

## Information

The Decimal value type represents decimal numbers ranging from positive 79,228,162,514,264,337,593,543,950,335 to negative 79,228,162,514,264,337,593,543,950,335. The default value of a Decimal is 0. The Decimal value type is appropriate for financial calculations that require large numbers of significant integral and fractional digits and no round-off errors. The Decimal type does not eliminate the need for rounding. Rather, it minimizes errors due to rounding.

When the result of the division and multiplication is passed to the Round method, the result suffers no loss of precision.

A decimal number is a floating-point value that consists of a sign, a numeric value where each digit in the value ranges from 0 to 9, and a scaling factor that indicates the position of a floating decimal point that separates the integral and fractional parts of the numeric value.

The binary representation of a Decimal value consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the 96-bit integer and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28. Therefore, the binary representation of a Decimal value the form, ((-2^96 to 2^96) / 10^(0 to 28)), where -(2^96-1) is equal to MinValue, and 2^96-1 is equal to MaxValue.

The scaling factor also can preserve any trailing zeros in a Decimal number. Trailing zeros do not affect the value of a Decimal number in arithmetic or comparison operations.

### Binary representation

The binary representation of a Decimal number consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the integer number and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28.

Decimal number can be implemented as a four-element array of 32-bit signed integers (`int bits[4];`).

`bits[0]`, `bits[1]`, and `bits[2]` contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.

`bits[3]` contains the scale factor and sign, and consists of following parts:
- Bits 0 to 15, the lower word, are unused and must be zero.
- Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
- Bits 24 to 30 are unused and must be zero.
- Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.

Note that the bit representation differentiates between negative and positive zero. These values can be treated as being equal in all operations.

### Example:

```c
typedef struct 
{
    int bits[4];
} lib_decimal;
```

### Arithmetic Operators

| Operator name | Operators  | Function                                                                   | 
| ------ | ------ |----------------------------------------------------------------------------|
| Addition | + | int lib_add(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) |
| Subtraction | - | int lib_sub(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) |
| Multiplication | * | int lib_mul(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) | 
| Division | / | int lib_div(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) |
| Modulo | Mod | int lib_mod(lib_decimal value_1, lib_decimal value_2, lib_decimal *result) |

The functions return the error code:
- 0 - OK
- 1 - the number is too large or equal to infinity
- 2 - the number is too small or equal to negative infinity
- 3 - division by 0

*Note on the numbers that do not fit into the mantissa:*
- *When getting numbers that do not fit into the mantissa during arithmetic operations, use bank rounding (for example, 79,228,162,514,264,337,593,543,950,335 - 0.6 = 79,228,162,514,264,337,593,543,950,334)*

*Note on the mod operation:*
- *If an overflow occurred as a result, discard the fractional part (for example, 70,000,000,000,000,000,000,000,000,000 % 0.001 = 0.000)*

### Comparison Operators

| Operator name | Operators  | Function | 
| ------ | ------ | ------ |
| Less than | < | int lib_is_less(lib_decimal, lib_decimal) |
| Less than or equal to | <= | int lib_is_less_or_equal(lib_decimal, lib_decimal) | 
| Greater than | > |  int lib_is_greater(lib_decimal, lib_decimal) |
| Greater than or equal to | >= | int lib_is_greater_or_equal(lib_decimal, lib_decimal) | 
| Equal to | == |  int lib_is_equal(lib_decimal, lib_decimal) |
| Not equal to | != |  int lib_is_not_equal(lib_decimal, lib_decimal) |

Return value:
- 0 - FALSE
- 1 - TRUE

### Convertors and parsers

| Convertor/parser | Function | 
| ------ | ------ |
| From int  | int lib_from_int_to_decimal(int src, lib_decimal *dst) |
| From float  | int lib_from_float_to_decimal(float src, lib_decimal *dst) |
| To int  | int lib_from_decimal_to_int(lib_decimal src, int *dst) |
| To float  | int lib_from_decimal_to_float(lib_decimal src, float *dst) |

Return value - code error:
- 0 - OK
- 1 - convertation error

*Note on the conversion of a float type number:*
- *If the numbers are too small (0 < |x| < 1e-28), return an error and value equal to 0*
- *If the numbers are too large (|x| > 79,228,162,514,264,337,593,543,950,335) or are equal to infinity, return an error*
- *When processing a number with the float type, convert all the digits contained in it*

*Note on the conversion from decimal type to int:*
- *If there is a fractional part in a decimal number, it should be discarded (for example, 0.9 is converted to 0)*

### Another functions

| Description | Function                                                         | 
| ------ |------------------------------------------------------------------|
| Rounds a specified Decimal number to the closest integer toward negative infinity. | int lib_floor(lib_decimal value, lib_decimal *result)            |	
| Rounds a decimal value to the nearest integer. | int lib_round(lib_decimal value, lib_decimal *result)    |
| Returns the integral digits of the specified Decimal; any fractional digits are discarded, including trailing zeroes. | int lib_truncate(lib_decimal value, lib_decimal *result) |
| Returns the result of multiplying the specified Decimal value by negative one. | int lib_negate(lib_decimal value, lib_decimal *result)   |

Return value - code error:
- 0 - OK
- 1 - calculation error
