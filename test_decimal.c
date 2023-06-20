#include <check.h>
#include <stdlib.h>

#include "lib_decimal.h"

#define lib_EPS_TEST 1E-6

START_TEST(ADDTest01) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 0);
    lib_decimal result;

    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 10575);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 0);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(ADDTest02) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 0);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(ADDTest03) {
    // ---- проверка на переполнение (положительное)
    lib_decimal num1 = new_decimal(777, 99999999, 4022222222, 0, 0);
    lib_decimal num2 = new_decimal(777, 88889999, 4022222222, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 2);
}
END_TEST

START_TEST(ADDTest04) {
    // ---- проверка на переполнение (отрицательное)
    lib_decimal num1 = new_decimal(777, 99999999, 4022222222, 1, 0);
    lib_decimal num2 = new_decimal(777, 88889999, 4022222222, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 3);
}
END_TEST

START_TEST(ADDTest05) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 2);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 4);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1050075);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 4);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(ADDTest06) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 3);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 1);
    lib_decimal result;

    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 3000);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 3);
    ck_assert_uint_eq(get_minus(result), 1);
}
END_TEST

START_TEST(ADDTest07) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 3);
    lib_decimal num2 = new_decimal(75, 0, 0, 1, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 3000);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 3);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(ADDTest08) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 4);
    lib_decimal num2 = new_decimal(75, 0, 0, 1, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 64500);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 4);
    ck_assert_uint_eq(get_minus(result), 1);
}
END_TEST

START_TEST(ADDTest09) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 5);
    lib_decimal num2 = new_decimal(75, 0, 0, 1, 15);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 934514763);
    ck_assert_uint_eq(result.bits[1], 24447);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 15);
    ck_assert_uint_eq(get_minus(result), 1);
}
END_TEST

START_TEST(ADDTest10) {
    lib_decimal num1 = new_decimal(11111, 88888888, 5555555, 0, 5);
    lib_decimal num2 = new_decimal(9999, 9999999, 9999999, 0, 7);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1121099);
    ck_assert_uint_eq(result.bits[1], 308954207);
    ck_assert_uint_eq(result.bits[2], 565555501);
    ck_assert_uint_eq(get_multiplier(result), 7);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(ADDTest11) {
    lib_decimal num1 = new_decimal(10500, 86445646, 5445545, 0, 5);
    lib_decimal num2 = new_decimal(9999, 9999999, 9999999, 0, 10);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    // --- C# operation <ADD> testing result:
    // num1: 1004525753281499027063.54436
    // num1 bits: 0000327680 0005445545 0086445646 0000010500
    // num2: 18446742233330111.1115491087
    // num2 bits: 0000655360 0009999999 0009999999 0000009999
    // result: 1004544200023732357174.6559091
    // result bits: 0000458752 0544564502 0050345040 3020412019

    ck_assert_uint_eq(result.bits[0], 3020412019);
    ck_assert_uint_eq(result.bits[1], 50345040);
    ck_assert_uint_eq(result.bits[2], 544564502);
    ck_assert_uint_eq(get_multiplier(result), 7);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(ADDTest12) {
    lib_decimal num1 = new_decimal(911111, 12222222, 2122222222, 0, 0);
    lib_decimal num2 = new_decimal(777777777, 88888888, 2122999999, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 778688888);
    ck_assert_uint_eq(result.bits[1], 101111110);
    ck_assert_uint_eq(result.bits[2], 4245222221);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <ADD> testing result:
    // num1: 39148090196825710456906573575
    //       0000000000 2122222222 0012222222 0000911111
    // num2: 39162437650420408874774033009
    //       0000000000 2122999999 0088888888 0777777777
    // res : 78310527847246119331680606584
    //       0000000000 4245222221 0101111110 0778688888
}
END_TEST

START_TEST(ADDTest13) {
    lib_decimal num1 = new_decimal(0, 0, 0, 1, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <ADD> testing result:
    // num1: 0
    //       2147483648 0000000000 0000000000 0000000000
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       2147483648 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(ADDTest14) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 15);
    lib_decimal num2 = new_decimal(0, 0, 0, 1, 8);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 983040);

    // --- C# operation <ADD> testing result:
    // num1: 0.000000000000000
    //       0000983040 0000000000 0000000000 0000000000
    // num2: 0.00000000
    //       2148007936 0000000000 0000000000 0000000000
    // res : 0.000000000000000
    //       0000983040 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(ADDTest15) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 25);
    lib_decimal num2 = new_decimal(0, 0, 0, 1, 10);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 1638400);

    // --- C# operation <ADD> testing result:
    // num1: 0.0000000000000000000000000
    //       0001638400 0000000000 0000000000 0000000000
    // num2: 0.0000000000
    //       2148139008 0000000000 0000000000 0000000000
    // res : 0.0000000000000000000000000
    //       0001638400 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(ADDTest16) {
    lib_decimal num1 = new_decimal(0, 0, 0, 1, 25);
    lib_decimal num2 = new_decimal(0, 0, 0, 1, 15);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2149122048);

    // --- C# operation <ADD> testing result:
    // num1: 0.0000000000000000000000000
    //       2149122048 0000000000 0000000000 0000000000
    // num2: 0.000000000000000
    //       2148466688 0000000000 0000000000 0000000000
    // res : 0.0000000000000000000000000
    //       2149122048 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(ADDTest17) {
    lib_decimal num1 = new_decimal(0, 0, 0, 1, 25);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 15);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2149122048);

    // --- C# operation <ADD> testing result:
    // num1: 0.0000000000000000000000000
    //       2149122048 0000000000 0000000000 0000000000
    // num2: 0.000000000000000
    //       0000983040 0000000000 0000000000 0000000000
    // res : 0.0000000000000000000000000
    //       2149122048 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(ADDTest18) {
    lib_decimal num1 = new_decimal(1, 0, 0, 0, 28);
    lib_decimal num2 = new_decimal(9999, 999, 1111, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 1409065408);
    ck_assert_uint_eq(result.bits[1], 999000002);
    ck_assert_uint_eq(result.bits[2], 1111000000);
    ck_assert_uint_eq(result.bits[3], 2147876864);

    // --- C# operation <ADD> testing result:
    // num1: 0.0000000000000000000000000001
    //       0001835008 0000000000 0000000000 0000000001
    // num2: -20494332670181984184079
    //       2147483648 0000001111 0000000999 0000009999
    // res : -20494332670181984184079.000000
    //       2147876864 1111000000 0999000002 1409065408
}
END_TEST

START_TEST(ADDTest19) {
    lib_decimal num1 = new_decimal(111, 111, 111, 0, 0);
    lib_decimal num2 = new_decimal(111, 111, 111, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 222);
    ck_assert_uint_eq(result.bits[1], 222);
    ck_assert_uint_eq(result.bits[2], 222);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <ADD> testing result:
    // num1: 2047588592658501599343
    //       0000000000 0000000111 0000000111 0000000111
    // num2: 2047588592658501599343
    //       0000000000 0000000111 0000000111 0000000111
    // res : 4095177185317003198686
    //       0000000000 0000000222 0000000222 0000000222
}
END_TEST

START_TEST(ADDTest20) {
    lib_decimal num1 = new_decimal(111, 111, 111, 0, 0);
    lib_decimal num2 = new_decimal(111, 111, 111, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <ADD> testing result:
    // num1: 2047588592658501599343
    //       0000000000 0000000111 0000000111 0000000111
    // num2: -2047588592658501599343
    //       2147483648 0000000111 0000000111 0000000111
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(ADDTest21) {
    lib_decimal num1 = new_decimal(777, 888, 999999, 1, 0);
    lib_decimal num2 = new_decimal(777, 888, 999999, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <ADD> testing result:
    // num1: -18446725626969291837408009
    //       2147483648 0000999999 0000000888 0000000777
    // num2: 18446725626969291837408009
    //       0000000000 0000999999 0000000888 0000000777
    // res : 0
    //       2147483648 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(ADDTest22) {
    lib_decimal num1 = new_decimal(777, 99999999, 2022222222, 0, 0);
    lib_decimal num2 = new_decimal(777, 88889999, 2022222222, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 1554);
    ck_assert_uint_eq(result.bits[1], 188889998);
    ck_assert_uint_eq(result.bits[2], 4044444444);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <ADD> testing result:
    // num1: 37303415789831757976836244233
    //       0000000000 2022222222 0099999999 0000000777
    // num2: 37303415789784040890177684233
    //       0000000000 2022222222 0088889999 0000000777
    // res : 74606831579615798867013928466
    //       0000000000 4044444444 0188889998 0000001554
}
END_TEST

START_TEST(ADDTest23) {
    lib_decimal num1 = new_decimal(777, 99999999, 82222222, 0, 24);
    lib_decimal num2 = new_decimal(5556777, 3389999, 2022222222, 0, 6);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1522289064);
    ck_assert_uint_eq(result.bits[1], 3389999);
    ck_assert_uint_eq(result.bits[2], 2022222222);
    ck_assert_uint_eq(result.bits[3], 393216);

    // --- C# operation <ADD> testing result:
    // num1: 1516.732286835227841796244233
    //       0001572864 0082222222 0099999999 0000000777
    // num2: 37303415789416821186375.240233
    //       0000393216 2022222222 0003389999 0005556777
    // res : 37303415789416821187891.972520
    //       0000393216 2022222222 0003389999 1522289064
}
END_TEST

START_TEST(ADDTest24) {
    lib_decimal num1 = new_decimal(222777, 99999999, 982222222, 0, 24);
    lib_decimal num2 = new_decimal(5556777, 3389999, 2022222222, 0, 8);
    lib_decimal result;
    ck_assert_uint_eq(lib_add(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 3704520478);
    ck_assert_uint_eq(result.bits[1], 3390420);
    ck_assert_uint_eq(result.bits[2], 2022222222);
    ck_assert_uint_eq(result.bits[3], 524288);

    // --- C# operation <ADD> testing result:
    // num1: 18118.801953173824296196466233
    //       0001572864 0982222222 0099999999 0000222777
    // num2: 373034157894168211863.75240233
    //       0000524288 2022222222 0003389999 0005556777
    // res : 373034157894168229982.55435550
    //       0000524288 2022222222 0003390420 3704520478
}
END_TEST

START_TEST(SUBTest01) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 0);
    lib_decimal result;

    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 10425);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 0);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(SUBTest02) {
    // ---- проверка на переполнение (положительное)
    lib_decimal num1 = new_decimal(777, 99999999, 4022222222, 0, 0);
    lib_decimal num2 = new_decimal(777, 88889999, 4022222222, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 2);
}
END_TEST

START_TEST(SUBTest03) {
    // ---- проверка на переполнение (отрицательное)
    lib_decimal num1 = new_decimal(777, 99999999, 4022222222, 1, 0);
    lib_decimal num2 = new_decimal(777, 88889999, 4022222222, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 3);
}
END_TEST

START_TEST(SUBTest04) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 0);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(SUBTest05) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <SUB> testing result:
    // num1: 0
    //       0000000000 0000000000 0000000000 0000000000
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(SUBTest06) {
    lib_decimal num1 = new_decimal(0, 0, 0, 1, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <SUB> testing result:
    // num1: 0
    //       2147483648 0000000000 0000000000 0000000000
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       2147483648 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(SUBTest07) {
    lib_decimal num1 = new_decimal(0, 0, 0, 1, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <SUB> testing result:
    // num1: 0
    //       2147483648 0000000000 0000000000 0000000000
    // num2: 0
    //       2147483648 0000000000 0000000000 0000000000
    // res : 0
    //       2147483648 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(SUBTest08) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 15);
    lib_decimal num2 = new_decimal(0, 0, 0, 1, 8);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 983040);

    // --- C# operation <SUB> testing result:
    // num1: 0.000000000000000
    //       0000983040 0000000000 0000000000 0000000000
    // num2: 0.00000000
    //       2148007936 0000000000 0000000000 0000000000
    // res : 0.000000000000000
    //       0000983040 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(SUBTest09) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 2);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 104925);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 3);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(SUBTest10) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 3);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 18000);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 3);
    ck_assert_uint_eq(get_minus(result), 1);
}
END_TEST

START_TEST(SUBTest11) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 5);
    lib_decimal num2 = new_decimal(75, 0, 0, 1, 15);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 934514613);
    ck_assert_uint_eq(result.bits[1], 24447);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 15);
    ck_assert_uint_eq(get_minus(result), 1);
}
END_TEST

START_TEST(SUBTest12) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 8);
    lib_decimal num2 = new_decimal(75, 0, 0, 1, 10);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);

    //   --- C# operation <SUB> testing result:
    // num1: -0.00010500
    // num1 bits: 2148007936 0000000000 0000000000 0000010500
    // num2: -0.0000000075
    // num2 bits: 2148139008 0000000000 0000000000 0000000075
    // result: -0.0001049925
    // result bits: 2148139008 0000000000 0000000000 0001049925

    ck_assert_uint_eq(result.bits[0], 1049925);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 10);
    ck_assert_uint_eq(get_minus(result), 1);
}
END_TEST

START_TEST(SUBTest13) {
    lib_decimal num1 = new_decimal(10500, 86445646, 5445549, 0, 6);
    lib_decimal num2 = new_decimal(9999, 9999999, 9999999, 0, 10);
    lib_decimal result;
    ck_assert_uint_eq(lib_sub(num1, num2, &result), 0);

    // --- C# operation <SUB> testing result:
    // num1: 100452649115126197544.560900
    // num1 bits: 0000393216 0005445549 0086445646 0000010500
    // num2: 18446742233330111.1115491087
    // num2 bits: 0000655360 0009999999 0009999999 0000009999
    // result: 100434202372892867433.44935089
    // result bits: 0000524288 0544454902 0097479680 4167168177

    ck_assert_uint_eq(result.bits[0], 4167168177);
    ck_assert_uint_eq(result.bits[1], 97479680);
    ck_assert_uint_eq(result.bits[2], 544454902);
    ck_assert_uint_eq(get_multiplier(result), 8);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(MULTest01) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 0);
    lib_decimal result;

    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 787500);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 0);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(MULTest02) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 2);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 787500);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 5);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(MULTest03) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 3);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 787500);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 4);
    ck_assert_uint_eq(get_minus(result), 1);
}
END_TEST

START_TEST(MULTest04) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 5);
    lib_decimal num2 = new_decimal(175, 0, 0, 1, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 1837500);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 8);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(MULTest05) {
    lib_decimal num1 = new_decimal(111111, 55555, 666666, 0, 10);
    lib_decimal num2 = new_decimal(2222, 44444, 33333, 0, 20);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 1228745288);
    ck_assert_uint_eq(result.bits[1], 757513025);
    ck_assert_uint_eq(result.bits[2], 4099231370);
    ck_assert_uint_eq(get_multiplier(result), 10);
    ck_assert_uint_eq(get_minus(result), 0);

    //   --- C# operation <MUL> testing result:
    // num1: 1229781708488225.8845872647
    // num1 bits: 0000655360 0000666666 0000055555 0000111111
    // num2: 6148.85320399846010521774
    // num2 bits: 0001310720 0000033333 0000044444 0000002222
    // result: 7561747198456527992.2839169608
    // result bits: 0000655360 4099231370 0757513025 1228745288
}
END_TEST

START_TEST(MULTest06) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <MUL> testing result:
    // num1: 0
    //       0000000000 0000000000 0000000000 0000000000
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(MULTest07) {
    lib_decimal num1 = new_decimal(11, 222, 0, 0, 0);
    lib_decimal num2 = new_decimal(4444, 555, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 48884);
    ck_assert_uint_eq(result.bits[1], 992673);
    ck_assert_uint_eq(result.bits[2], 123210);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <MUL> testing result:
    // num1: 953482739723
    //       0000000000 0000000000 0000000222 0000000011
    // num2: 2383706853724
    //       0000000000 0000000000 0000000555 0000004444
    // res : 2272823341585251925278452
    //       0000000000 0000123210 0000992673 0000048884
}
END_TEST

START_TEST(MULTest08) {
    lib_decimal num1 = new_decimal(11, 222, 333, 0, 6);
    lib_decimal num2 = new_decimal(4444, 555, 44, 0, 8);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 103477403);
    ck_assert_uint_eq(result.bits[1], 159771634);
    ck_assert_uint_eq(result.bits[2], 2702816950);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <MUL> testing result:
    // num1: 6142765777498763.427851
    //       0000393216 0000000333 0000000222 0000000011
    // num2: 8116567416269.27124828
    //       0000524288 0000000044 0000000555 0000004444
    // res : 49858172555420439427586650267
    //       0000000000 2702816950 0159771634 0103477403
}
END_TEST

START_TEST(MULTest09) {
    lib_decimal num1 = new_decimal(23, 66, 789, 1, 15);
    lib_decimal num2 = new_decimal(888, 235, 1, 0, 7);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 1259616715);
    ck_assert_uint_eq(result.bits[1], 340017945);
    ck_assert_uint_eq(result.bits[2], 1455448187);
    ck_assert_uint_eq(result.bits[3], 2148073472);

    // --- C# operation <MUL> testing result:
    // num1: -14554481.074440304066583
    //       2148466688 0000000789 0000000066 0000000023
    // num2: 1844674508302.6867064
    //       0000458752 0000000001 0000000235 0000000888
    // res : -26848280219593927219.177863627
    //       2148073472 1455448187 0340017945 1259616715
}
END_TEST

START_TEST(MULTest10) {
    lib_decimal num1 = new_decimal(23, 66, 789, 0, 15);
    lib_decimal num2 = new_decimal(1, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 23);
    ck_assert_uint_eq(result.bits[1], 66);
    ck_assert_uint_eq(result.bits[2], 789);
    ck_assert_uint_eq(result.bits[3], 983040);

    // --- C# operation <MUL> testing result:
    // num1: 14554481.074440304066583
    //       0000983040 0000000789 0000000066 0000000023
    // num2: 1
    //       0000000000 0000000000 0000000000 0000000001
    // res : 14554481.074440304066583
    //       0000983040 0000000789 0000000066 0000000023
}
END_TEST

START_TEST(MULTest11) {
    lib_decimal num1 = new_decimal(23, 66, 789, 0, 15);
    lib_decimal num2 = new_decimal(1, 0, 0, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 23);
    ck_assert_uint_eq(result.bits[1], 66);
    ck_assert_uint_eq(result.bits[2], 789);
    ck_assert_uint_eq(result.bits[3], 2148466688);

    // --- C# operation <MUL> testing result:
    // num1: 14554481.074440304066583
    //       0000983040 0000000789 0000000066 0000000023
    // num2: -1
    //       2147483648 0000000000 0000000000 0000000001
    // res : -14554481.074440304066583
    //       2148466688 0000000789 0000000066 0000000023
}
END_TEST

START_TEST(MULTest12) {
    lib_decimal num1 = new_decimal(231551, 66154, 7896556, 0, 15);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <MUL> testing result:
    // num1: 145665747595.999731337365631
    //       0000983040 0007896556 0000066154 0000231551
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(MULTest13) {
    lib_decimal num1 = new_decimal(1, 0, 0, 1, 5);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_mul(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <MUL> testing result:
    // num1: -0.00001
    //       2147811328 0000000000 0000000000 0000000001
    // num2: 0
    //       2147483648 0000000000 0000000000 0000000000
    // res : 0.00000
    //       0000327680 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(DIVTest01) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(75, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 140);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 0);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(DIVTest02) {
    // ---- проверка деления на 0 ----
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 3);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 3);
}
END_TEST

START_TEST(DIVTest03) {
    // ---- проверка деления на очень маленькое число ----
    lib_decimal num1 = new_decimal(777, 444, 0, 0, 25);
    lib_decimal num2 = new_decimal(3333, 88888, 21111111, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 2);
}
END_TEST

START_TEST(DIVTest04) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 3);
    lib_decimal num2 = new_decimal(75, 0, 0, 1, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 14);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 1);
    ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(DIVTest05) {
    lib_decimal num1 = new_decimal(10500, 0, 0, 1, 8);
    lib_decimal num2 = new_decimal(75, 0, 0, 1, 10);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 14000);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(get_multiplier(result), 0);
    ck_assert_uint_eq(get_minus(result), 0);

    //   --- C# operation <DIV> testing result:
    // num1: -0.00010500
    // num1 bits: 2148007936 0000000000 0000000000 0000010500
    // num2: -0.0000000075
    // num2 bits: 2148139008 0000000000 0000000000 0000000075
    // result: 14000
    // result bits: 0000000000 0000000000 0000000000 0000014000
}
END_TEST

START_TEST(DIVTest06) {
    lib_decimal num1 = new_decimal(8024, 0, 0, 0, 2);
    lib_decimal num2 = new_decimal(35, 0, 0, 0, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 2377571182);
    ck_assert_uint_eq(result.bits[1], 3082367693);
    ck_assert_uint_eq(result.bits[2], 1242805461);
    ck_assert_uint_eq(get_multiplier(result), 27);
    ck_assert_uint_eq(get_minus(result), 0);

    //   --- C# operation <DIV> testing result:
    // num1: 80.24
    // num1 bits: 0000131072 0000000000 0000000000 0000008024
    // num2: 3.5
    // num2 bits: 0000065536 0000000000 0000000000 0000000035
    // result: 22.925714285714285714285714286
    // result bits: 0001769472 1242805461 3082367693 2377571182
}
END_TEST

START_TEST(DIVTest07) {
    lib_decimal num1 = new_decimal(7, 0, 0, 0, 2);
    lib_decimal num2 = new_decimal(3, 0, 0, 0, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 626349397);
    ck_assert_uint_eq(result.bits[1], 2432763277);
    ck_assert_uint_eq(result.bits[2], 1264902534);
    ck_assert_uint_eq(get_multiplier(result), 27);
    ck_assert_uint_eq(get_minus(result), 0);

    //   --- C# operation <DIV> testing result:
    // num1: 0.07
    // num1 bits: 0000131072 0000000000 0000000000 0000000007
    // num2: 0.003
    // num2 bits: 0000196608 0000000000 0000000000 0000000003
    // result: 23.333333333333333333333333333
    // result bits: 0001769472 1264902534 2432763277 0626349397
}
END_TEST

START_TEST(DIVTest08) {
    lib_decimal num1 = new_decimal(8, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(3, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 715827883);
    ck_assert_uint_eq(result.bits[1], 2780300888);
    ck_assert_uint_eq(result.bits[2], 1445602896);
    ck_assert_uint_eq(get_multiplier(result), 28);
    ck_assert_uint_eq(get_minus(result), 0);

    //   --- C# operation <DIV> testing result:
    // num1: 8
    // num1 bits: 0000000000 0000000000 0000000000 0000000008
    // num2: 3
    // num2 bits: 0000000000 0000000000 0000000000 0000000003
    // result: 2.6666666666666666666666666667
    // result bits: 0001835008 1445602896 2780300888 0715827883
}
END_TEST

START_TEST(DIVTest09) {
    lib_decimal num1 = new_decimal(8, 0, 0, 0, 1);
    lib_decimal num2 = new_decimal(3, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 1789569707);
    ck_assert_uint_eq(result.bits[1], 2855010466);
    ck_assert_uint_eq(result.bits[2], 144560289);
    ck_assert_uint_eq(get_multiplier(result), 28);
    ck_assert_uint_eq(get_minus(result), 0);

    //   --- C# operation <DIV> testing result:
    // num1: 0.8
    // num1 bits: 0000065536 0000000000 0000000000 0000000008
    // num2: 3
    // num2 bits: 0000000000 0000000000 0000000000 0000000003
    // result: 0.2666666666666666666666666667
    // result bits: 0001835008 0144560289 2855010466 1789569707
}
END_TEST

START_TEST(DIVTest10) {
    lib_decimal num1 = new_decimal(354546, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(654, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 3464418144);
    ck_assert_uint_eq(result.bits[1], 67171418);
    ck_assert_uint_eq(result.bits[2], 2938834430);
    ck_assert_uint_eq(result.bits[3], 1703936);

    // --- C# operation <DIV> testing result:
    // num1: 354546
    //       0000000000 0000000000 0000000000 0000354546
    // num2: 654
    //       0000000000 0000000000 0000000000 0000000654
    // res : 542.11926605504587155963302752
    //       0001703936 2938834430 0067171418 3464418144
}
END_TEST

START_TEST(DIVTest11) {
    lib_decimal num1 = new_decimal(10, 1, 55, 0, 0);
    lib_decimal num2 = new_decimal(7, 56, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 1603828433);
    ck_assert_uint_eq(result.bits[1], 1538858751);
    ck_assert_uint_eq(result.bits[2], 22867295);
    ck_assert_uint_eq(result.bits[3], 1114112);

    // --- C# operation <DIV> testing result:
    // num1: 1014570924058320306186
    //       0000000000 0000000055 0000000001 0000000010
    // num2: 240518168583
    //       0000000000 0000000000 0000000056 0000000007
    // res : 4218271451.32366071433034449
    //       0001114112 0022867295 1538858751 1603828433
}
END_TEST

START_TEST(DIVTest12) {
    lib_decimal num1 = new_decimal(8, 0, 0, 0, 8);
    lib_decimal num2 = new_decimal(3, 0, 0, 0, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 3869944491);
    ck_assert_uint_eq(result.bits[1], 124410055);
    ck_assert_uint_eq(result.bits[2], 14456);
    ck_assert_uint_eq(get_multiplier(result), 28);
    ck_assert_uint_eq(get_minus(result), 0);

    //   --- C# operation <DIV> testing result:
    // num1: 0.00000008
    // num1 bits: 0000524288 0000000000 0000000000 0000000008
    // num2: 0.003
    // num2 bits: 0000196608 0000000000 0000000000 0000000003
    // result: 0.0000266666666666666666666667
    // result bits: 0001835008 0000014456 0124410055 3869944491
}
END_TEST

START_TEST(DIVTest13) {
    lib_decimal num1 = new_decimal(10, 1, 55, 0, 0);
    lib_decimal num2 = new_decimal(7, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 756423899);
    ck_assert_uint_eq(result.bits[1], 3082119497);
    ck_assert_uint_eq(result.bits[2], 785714285);
    ck_assert_uint_eq(result.bits[3], 524288);

    // --- C# operation <DIV> testing result:
    // num1: 1014570924058320306186
    //       0000000000 0000000055 0000000001 0000000010
    // num2: 7
    //       0000000000 0000000000 0000000000 0000000007
    // res : 144938703436902900883.71428571
    //       0000524288 0785714285 3082119497 0756423899
}
END_TEST

START_TEST(DIVTest14) {
    lib_decimal num1 = new_decimal(1, 2, 3, 0, 0);
    lib_decimal num2 = new_decimal(4, 5, 6, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 4289596349);
    ck_assert_uint_eq(result.bits[1], 476131325);
    ck_assert_uint_eq(result.bits[2], 271050543);
    ck_assert_uint_eq(result.bits[3], 1835008);

    // --- C# operation <DIV> testing result:
    // num1: 55340232229718589441
    //       0000000000 0000000003 0000000002 0000000001
    // num2: 110680464463732146180
    //       0000000000 0000000006 0000000005 0000000004
    // res : 0.4999999999805974463569071037
    //       0001835008 0271050543 0476131325 4289596349
}
END_TEST

START_TEST(DIVTest15) {
    lib_decimal num1 = new_decimal(777, 444, 5555, 0, 10);
    lib_decimal num2 = new_decimal(3333, 88888, 111, 0, 5);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 2054553333);
    ck_assert_uint_eq(result.bits[1], 2930122307);
    ck_assert_uint_eq(result.bits[2], 271294);
    ck_assert_uint_eq(result.bits[3], 1835008);

    // --- C# operation <DIV> testing result:
    // num1: 10247166333136.3524707081
    //       0000655360 0000005555 0000000444 0000000777
    // num2: 20475889739528132.39557
    //       0000327680 0000000111 0000088888 0000003333
    // res : 0.0005004503571512442995736309
    //       0001835008 0000271294 2930122307 2054553333
}
END_TEST

START_TEST(DIVTest16) {
    lib_decimal num1 = new_decimal(777, 444, 5555, 0, 10);
    lib_decimal num2 = new_decimal(3333, 88888, 11111, 0, 5);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 1756309468);
    ck_assert_uint_eq(result.bits[1], 112304069);
    ck_assert_uint_eq(result.bits[2], 271);
    ck_assert_uint_eq(result.bits[3], 1769472);

    // --- C# operation <DIV> testing result:
    // num1: 10247166333136.3524707081
    //       0000655360 0000005555 0000000444 0000000777
    // num2: 2049617737847578810.15557
    //       0000327680 0000011111 0000088888 0000003333
    // res : 0.000004999549986280607524828
    //       0001769472 0000000271 0112304069 1756309468
}
END_TEST

START_TEST(DIVTest17) {
    lib_decimal num1 = new_decimal(1, 2, 3, 1, 10);
    lib_decimal num2 = new_decimal(4, 5, 6, 1, 7);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 231922863);
    ck_assert_uint_eq(result.bits[1], 2332643373);
    ck_assert_uint_eq(result.bits[2], 271050);
    ck_assert_uint_eq(result.bits[3], 1835008);

    // --- C# operation <DIV> testing result:
    // num1: -5534023222.9718589441
    //       2148139008 0000000003 0000000002 0000000001
    // num2: -11068046446373.2146180
    //       2147942400 0000000006 0000000005 0000000004
    // res : 0.0004999999999805974463569071
    //       0001835008 0000271050 2332643373 0231922863
}
END_TEST

START_TEST(DIVTest18) {
    lib_decimal num1 = new_decimal(10, 222, 3333, 1, 10);
    lib_decimal num2 = new_decimal(41, 51, 60, 0, 7);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 2077368994);
    ck_assert_uint_eq(result.bits[1], 2291490553);
    ck_assert_uint_eq(result.bits[2], 3011371);
    ck_assert_uint_eq(result.bits[3], 2149253120);

    // --- C# operation <DIV> testing result:
    // num1: -6148299799862.7418275850
    //       2148139008 0000003333 0000000222 0000000010
    // num2: 110680464464161.6429097
    //       0000458752 0000000060 0000000051 0000000041
    // res : -0.055549999989867792464749218
    //       2149253120 0003011371 2291490553 2077368994
}
END_TEST

START_TEST(DIVTest19) {
    lib_decimal num1 = new_decimal(10, 222, 3333, 0, 10);
    lib_decimal num2 = new_decimal(41, 51, 60, 1, 7);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 2077368994);
    ck_assert_uint_eq(result.bits[1], 2291490553);
    ck_assert_uint_eq(result.bits[2], 3011371);
    ck_assert_uint_eq(result.bits[3], 2149253120);

    // --- C# operation <DIV> testing result:
    // num1: 6148299799862.7418275850
    //       0000655360 0000003333 0000000222 0000000010
    // num2: -110680464464161.6429097
    //       2147942400 0000000060 0000000051 0000000041
    // res : -0.055549999989867792464749218
    //       2149253120 0003011371 2291490553 2077368994
}
END_TEST

START_TEST(DIVTest20) {
    lib_decimal num1 = new_decimal(10, 222, 3333, 0, 15);
    lib_decimal num2 = new_decimal(41, 51, 60, 1, 9);
    lib_decimal result;
    ck_assert_uint_eq(lib_div(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 2984301124);
    ck_assert_uint_eq(result.bits[1], 3072341685);
    ck_assert_uint_eq(result.bits[2], 30113);
    ck_assert_uint_eq(result.bits[3], 2149318656);

    // --- C# operation <DIV> testing result:
    // num1: 61482997.998627418275850
    //       0000983040 0000003333 0000000222 0000000010
    // num2: -1106804644641.616429097
    //       2148073472 0000000060 0000000051 0000000041
    // res : -0.0000555499999898677924647492
    //       2149318656 0000030113 3072341685 2984301124
}
END_TEST

START_TEST(MODTest01) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;

    ck_assert_uint_eq(lib_mod(num1, num2, &result), 3);
}
END_TEST

START_TEST(MODTest02) {
    lib_decimal num1 = new_decimal(255, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(16, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 15);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <MOD> testing result:
    // num1: 255
    //       0000000000 0000000000 0000000000 0000000255
    // num2: 16
    //       0000000000 0000000000 0000000000 0000000016
    // res : 15
    //       0000000000 0000000000 0000000000 0000000015
}
END_TEST

START_TEST(MODTest03) {
    lib_decimal num1 = new_decimal(255, 0, 0, 0, 3);
    lib_decimal num2 = new_decimal(16, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 255);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 196608);

    // --- C# operation <MOD> testing result:
    // num1: 0.255
    //       0000196608 0000000000 0000000000 0000000255
    // num2: 16
    //       0000000000 0000000000 0000000000 0000000016
    // res : 0.255
    //       0000196608 0000000000 0000000000 0000000255
}
END_TEST

START_TEST(MODTest04) {
    lib_decimal num1 = new_decimal(255, 0, 0, 0, 3);
    lib_decimal num2 = new_decimal(16, 0, 0, 0, 2);
    lib_decimal result;
    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 95);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 196608);

    // --- C# operation <MOD> testing result:
    // num1: 0.255
    //       0000196608 0000000000 0000000000 0000000255
    // num2: 0.16
    //       0000131072 0000000000 0000000000 0000000016
    // res : 0.095
    //       0000196608 0000000000 0000000000 0000000095
}
END_TEST

START_TEST(MODTest05) {
    lib_decimal num1 = new_decimal(255, 2589, 425, 0, 3);
    lib_decimal num2 = new_decimal(16, 456, 45, 0, 2);
    lib_decimal result;
    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 255);
    ck_assert_uint_eq(result.bits[1], 2589);
    ck_assert_uint_eq(result.bits[2], 425);
    ck_assert_uint_eq(result.bits[3], 196608);

    // --- C# operation <MOD> testing result:
    // num1: 7839866242446229766.399
    //       0000196608 0000000425 0000002589 0000000255
    // num2: 8301034852754349097.12
    //       0000131072 0000000045 0000000456 0000000016
    // res : 7839866242446229766.399
    //       0000196608 0000000425 0000002589 0000000255
}
END_TEST

START_TEST(MODTest06) {
    lib_decimal num1 = new_decimal(255, 2589, 425, 0, 3);
    lib_decimal num2 = new_decimal(16, 456, 45, 0, 8);
    lib_decimal result;
    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);

    ck_assert_uint_eq(result.bits[0], 10388896);
    ck_assert_uint_eq(result.bits[1], 4123200832);
    ck_assert_uint_eq(result.bits[2], 19);
    ck_assert_uint_eq(result.bits[3], 524288);

    // --- C# operation <MOD> testing result:
    // num1: 7839866242446229766.399
    //       0000196608 0000000425 0000002589 0000000255
    // num2: 8301034852754.34909712
    //       0000524288 0000000045 0000000456 0000000016
    // res : 3681971501287.71859872
    //       0000524288 0000000019 4123200832 0010388896
}
END_TEST

START_TEST(MODTest07) {
    lib_decimal num1 = new_decimal(255, 2589, 425, 0, 3);
    lib_decimal num2 = new_decimal(16, 456, 45, 0, 1);
    lib_decimal result;

    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 255);
    ck_assert_uint_eq(result.bits[1], 2589);
    ck_assert_uint_eq(result.bits[2], 425);
    ck_assert_uint_eq(result.bits[3], 196608);

    // --- C# operation <MOD> testing result:
    // num1: 7839866242446229766.399
    //       0000196608 0000000425 0000002589 0000000255
    // num2: 83010348527543490971.2
    //       0000065536 0000000045 0000000456 0000000016
    // res : 7839866242446229766.399
    //       0000196608 0000000425 0000002589 0000000255
}
END_TEST

START_TEST(MODTest08) {
    lib_decimal num1 = new_decimal(255, 2589, 425, 1, 3);
    lib_decimal result;
    lib_decimal num2 = new_decimal(16, 456, 45, 0, 1);

    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 255);
    ck_assert_uint_eq(result.bits[1], 2589);
    ck_assert_uint_eq(result.bits[2], 425);
    ck_assert_uint_eq(result.bits[3], 2147680256);

    // --- C# operation <MOD> testing result:
    // num1: -7839866242446229766.399
    //       2147680256 0000000425 0000002589 0000000255
    // num2: 83010348527543490971.2
    //       0000065536 0000000045 0000000456 0000000016
    // res : -7839866242446229766.399
    //       2147680256 0000000425 0000002589 0000000255
}
END_TEST

START_TEST(MODTest09) {
    lib_decimal num1 = new_decimal(255, 2589, 425, 1, 3);
    lib_decimal num2 = new_decimal(16, 456, 45, 1, 1);
    lib_decimal result;

    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 255);
    ck_assert_uint_eq(result.bits[1], 2589);
    ck_assert_uint_eq(result.bits[2], 425);
    ck_assert_uint_eq(result.bits[3], 2147680256);

    // --- C# operation <MOD> testing result:
    // num1: -7839866242446229766.399
    //       2147680256 0000000425 0000002589 0000000255
    // num2: -83010348527543490971.2
    //       2147549184 0000000045 0000000456 0000000016
    // res : -7839866242446229766.399
    //       2147680256 0000000425 0000002589 0000000255
}
END_TEST

START_TEST(MODTest10) {
    lib_decimal num1 = new_decimal(255, 2589, 425, 0, 3);
    lib_decimal num2 = new_decimal(16, 456, 45, 1, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 255);
    ck_assert_uint_eq(result.bits[1], 2589);
    ck_assert_uint_eq(result.bits[2], 425);
    ck_assert_uint_eq(result.bits[3], 196608);

    // --- C# operation <MOD> testing result:
    // num1: 7839866242446229766.399
    //       0000196608 0000000425 0000002589 0000000255
    // num2: -83010348527543490971.2
    //       2147549184 0000000045 0000000456 0000000016
    // res : 7839866242446229766.399
    //       0000196608 0000000425 0000002589 0000000255
}
END_TEST

START_TEST(MODTest11) {
    lib_decimal num1 = new_decimal(255, 2589, 425, 0, 25);
    lib_decimal num2 = new_decimal(16, 456, 45, 0, 28);
    lib_decimal result;
    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 103896);
    ck_assert_uint_eq(result.bits[1], 4293249832);
    ck_assert_uint_eq(result.bits[2], 19);
    ck_assert_uint_eq(result.bits[3], 1835008);

    // --- C# operation <MOD> testing result:
    // num1: 0.0007839866242446229766399
    //       0001638400 0000000425 0000002589 0000000255
    // num2: 0.0000000830103485275434909712
    //       0001835008 0000000045 0000000456 0000000016
    // res : 0.0000000368927505022479078872
    //       0001835008 0000000019 4293249832 0000103896
}
END_TEST

START_TEST(MODTest12) {
    lib_decimal num1 = new_decimal(25, 26, 27, 0, 5);
    lib_decimal num2 = new_decimal(25, 26, 27, 0, 5);
    lib_decimal result;
    ck_assert_uint_eq(lib_mod(num1, num2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 327680);

    // --- C# operation <MOD> testing result:
    // num1: 4980620901018270.43353
    //       0000327680 0000000027 0000000026 0000000025
    // num2: 4980620901018270.43353
    //       0000327680 0000000027 0000000026 0000000025
    // res : 0.00000
    //       0000327680 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(GREATTest01) {
    lib_decimal num1 = new_decimal(429496, 429495, 42945, 0, 5);
    lib_decimal num2 = new_decimal(25, 26, 27, 0, 5);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 1);

    // --- C# operation <GREAT> testing result:
    // num1: 7921954260901236733.74136
    //       0000327680 0000042945 0000429495 0000429496
    // num2: 4980620901018270.43353
    //       0000327680 0000000027 0000000026 0000000025
    // res : True 1
}
END_TEST

START_TEST(GREATTest02) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 0);

    // --- C# operation <GREAT> testing result:
    // num1: 0
    //       0000000000 0000000000 0000000000 0000000000
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(GREATTest03) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 20);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 10);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 0);

    // --- C# operation <GREAT> testing result:
    // num1: 0.00000000000000000000
    //       0001310720 0000000000 0000000000 0000000000
    // num2: 0.0000000000
    //       0000655360 0000000000 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(GREATTest04) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 10);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 0);

    // --- C# operation <GREAT> testing result:
    // num1: 0
    //       0000000000 0000000000 0000000000 0000000000
    // num2: 0.0000000000
    //       0000655360 0000000000 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(GREATTest05) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 0, 10);
    lib_decimal num2 = new_decimal(0, 5454, 5454, 0, 15);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 1);

    // --- C# operation <GREAT> testing result:
    // num1: 16395466133046.7684352000
    //       0000655360 0000008888 0000000777 0000000000
    // num2: 100608542.201436646146048
    //       0000983040 0000005454 0000005454 0000000000
    // res : True 1
}
END_TEST

START_TEST(GREATTest06) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 1, 10);
    lib_decimal num2 = new_decimal(0, 5454, 5454, 0, 15);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 0);

    // --- C# operation <GREAT> testing result:
    // num1: -16395466133046.7684352000
    //       2148139008 0000008888 0000000777 0000000000
    // num2: 100608542.201436646146048
    //       0000983040 0000005454 0000005454 0000000000
    // res : False 0
}
END_TEST

START_TEST(GREATTest07) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 1, 1);
    lib_decimal num2 = new_decimal(0, 5454, 5454, 0, 15);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 0);

    // --- C# operation <GREAT> testing result:
    // num1: -16395466133046768435200.0
    //       2147549184 0000008888 0000000777 0000000000
    // num2: 100608542.201436646146048
    //       0000983040 0000005454 0000005454 0000000000
    // res : False 0
}
END_TEST

START_TEST(GREATTest08) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 0, 1);
    lib_decimal num2 = new_decimal(0, 5454, 5454, 1, 15);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 1);

    // --- C# operation <GREAT> testing result:
    // num1: 16395466133046768435200.0
    //       0000065536 0000008888 0000000777 0000000000
    // num2: -100608542.201436646146048
    //       2148466688 0000005454 0000005454 0000000000
    // res : True 1
}
END_TEST

START_TEST(GREATTest09) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 1, 1);
    lib_decimal num2 = new_decimal(10, 5454, 5454, 1, 15);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 0);

    // --- C# operation <GREAT> testing result:
    // num1: -16395466133046768435200.0
    //       2147549184 0000008888 0000000777 0000000000
    // num2: -100608542.201436646146058
    //       2148466688 0000005454 0000005454 0000000010
    // res : False 0
}
END_TEST

START_TEST(GREATTest10) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 0, 28);
    lib_decimal num2 = new_decimal(10, 5454, 5454, 1, 15);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 1);

    // --- C# operation <GREAT> testing result:
    // num1: 0.0000163954661330467684352000
    //       0001835008 0000008888 0000000777 0000000000
    // num2: -100608542.201436646146058
    //       2148466688 0000005454 0000005454 0000000010
    // res : True 1
}
END_TEST

START_TEST(GREATTest11) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 1, 15);
    lib_decimal num2 = new_decimal(1, 777, 8888, 1, 15);
    ck_assert_uint_eq(lib_is_greater(num1, num2), 1);
}
END_TEST

START_TEST(LESSTest01) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 0, 28);
    lib_decimal num2 = new_decimal(10, 5454, 5454, 0, 15);
    ck_assert_uint_eq(lib_is_less(num1, num2), 1);

    // --- C# operation <LESS> testing result:
    // num1: 0.0000163954661330467684352000
    //       0001835008 0000008888 0000000777 0000000000
    // num2: 100608542.201436646146058
    //       0000983040 0000005454 0000005454 0000000010
    // res : True 1
}
END_TEST

START_TEST(LESSTest02) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 1, 28);
    lib_decimal num2 = new_decimal(10, 5454, 5454, 0, 15);
    ck_assert_uint_eq(lib_is_less(num1, num2), 1);

    // --- C# operation <LESS> testing result:
    // num1: -0.0000163954661330467684352000
    //       2149318656 0000008888 0000000777 0000000000
    // num2: 100608542.201436646146058
    //       0000983040 0000005454 0000005454 0000000010
    // res : True 1
}
END_TEST

START_TEST(LESSTest03) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 1, 28);
    lib_decimal num2 = new_decimal(10, 5454, 5454, 1, 15);
    ck_assert_uint_eq(lib_is_less(num1, num2), 0);

    // --- C# operation <LESS> testing result:
    // num1: -0.0000163954661330467684352000
    //       2149318656 0000008888 0000000777 0000000000
    // num2: -100608542.201436646146058
    //       2148466688 0000005454 0000005454 0000000010
    // res : False 0
}
END_TEST

START_TEST(LESSTest04) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 0, 28);
    lib_decimal num2 = new_decimal(10, 5454, 5454, 1, 15);
    ck_assert_uint_eq(lib_is_less(num1, num2), 0);

    // --- C# operation <LESS> testing result:
    // num1: 0.0000163954661330467684352000
    //       0001835008 0000008888 0000000777 0000000000
    // num2: -100608542.201436646146058
    //       2148466688 0000005454 0000005454 0000000010
    // res : False 0
}
END_TEST

START_TEST(LESSTest05) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    ck_assert_uint_eq(lib_is_less(num1, num2), 0);

    // --- C# operation <LESS> testing result:
    // num1: 0
    //       0000000000 0000000000 0000000000 0000000000
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(LESSTest06) {
    lib_decimal num1 = new_decimal(0, 10, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 200, 0, 0);
    ck_assert_uint_eq(lib_is_less(num1, num2), 1);

    // --- C# operation <LESS> testing result:
    // num1: 42949672960
    //       0000000000 0000000000 0000000010 0000000000
    // num2: 3689348814741910323200
    //       0000000000 0000000200 0000000000 0000000000
    // res : True 1
}
END_TEST

START_TEST(LESSTest07) {
    lib_decimal num1 = new_decimal(0, 10, 0, 0, 25);
    lib_decimal num2 = new_decimal(0, 0, 200, 0, 4);
    ck_assert_uint_eq(lib_is_less(num1, num2), 1);

    // --- C# operation <LESS> testing result:
    // num1: 0.0000000000000042949672960
    //       0001638400 0000000000 0000000010 0000000000
    // num2: 368934881474191032.3200
    //       0000262144 0000000200 0000000000 0000000000
    // res : True 1
}
END_TEST

START_TEST(LESSTest08) {
    lib_decimal num1 = new_decimal(0, 10, 0, 0, 25);
    lib_decimal num2 = new_decimal(0, 0, 200, 1, 4);
    ck_assert_uint_eq(lib_is_less(num1, num2), 0);

    // --- C# operation <LESS> testing result:
    // num1: 0.0000000000000042949672960
    //       0001638400 0000000000 0000000010 0000000000
    // num2: -368934881474191032.3200
    //       2147745792 0000000200 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(LESSTest09) {
    lib_decimal num1 = new_decimal(0, 10, 200, 1, 25);
    lib_decimal num2 = new_decimal(0, 10, 200, 1, 25);
    ck_assert_uint_eq(lib_is_less(num1, num2), 0);

    // --- C# operation <LESS> testing result:
    // num1: -0.0003689348814784859996160
    //       2149122048 0000000200 0000000010 0000000000
    // num2: -0.0003689348814784859996160
    //       2149122048 0000000200 0000000010 0000000000
    // res : False 0
}
END_TEST

START_TEST(LESSTest10) {
    lib_decimal num1 = new_decimal(0, 10, 200, 1, 25);
    lib_decimal num2 = new_decimal(0, 10, 200, 0, 25);
    ck_assert_uint_eq(lib_is_less(num1, num2), 1);

    // --- C# operation <LESS> testing result:
    // num1: -0.0003689348814784859996160
    //       2149122048 0000000200 0000000010 0000000000
    // num2: 0.0003689348814784859996160
    //       0001638400 0000000200 0000000010 0000000000
    // res : True 1
}
END_TEST

START_TEST(EQUALTest01) {
    lib_decimal num1 = new_decimal(0, 10, 200, 0, 25);
    lib_decimal num2 = new_decimal(0, 10, 200, 0, 25);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.0003689348814784859996160
    //       0001638400 0000000200 0000000010 0000000000
    // num2: 0.0003689348814784859996160
    //       0001638400 0000000200 0000000010 0000000000
    // res : True 1
}
END_TEST

START_TEST(EQUALTest02) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: 0
    //       0000000000 0000000000 0000000000 0000000000
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : True 1
}
END_TEST

START_TEST(EQUALTest03) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 5);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 1);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.00000
    //       0000327680 0000000000 0000000000 0000000000
    // num2: 0.0
    //       0000065536 0000000000 0000000000 0000000000
    // res : True 1
}
END_TEST

START_TEST(EQUALTest04) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 5);
    lib_decimal num2 = new_decimal(0, 0, 0, 1, 1);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.00000
    //       0000327680 0000000000 0000000000 0000000000
    // num2: 0.0
    //       2147549184 0000000000 0000000000 0000000000
    // res : True 1
}
END_TEST

START_TEST(EQUALTest05) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 0, 28);
    lib_decimal num2 = new_decimal(10, 5454, 5454, 1, 15);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.0000163954661330467684352000
    //       0001835008 0000008888 0000000777 0000000000
    // num2: -100608542.201436646146058
    //       2148466688 0000005454 0000005454 0000000010
    // res : False 0
}
END_TEST

START_TEST(EQUALTest06) {
    lib_decimal num1 = new_decimal(25000, 0, 0, 0, 3);
    lib_decimal num2 = new_decimal(25, 0, 0, 0, 0);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: 25.000
    //       0000196608 0000000000 0000000000 0000025000
    // num2: 25
    //       0000000000 0000000000 0000000000 0000000025
    // res : True 1
}
END_TEST

START_TEST(EQUALTest07) {
    lib_decimal num1 = new_decimal(25000, 0, 0, 0, 15);
    lib_decimal num2 = new_decimal(250000, 0, 0, 0, 16);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.000000000025000
    //       0000983040 0000000000 0000000000 0000025000
    // num2: 0.0000000000250000
    //       0001048576 0000000000 0000000000 0000250000
    // res : True 1
}
END_TEST

START_TEST(EQUALTest08) {
    lib_decimal num1 = new_decimal(25000, 0, 0, 1, 15);
    lib_decimal num2 = new_decimal(250000, 0, 0, 0, 16);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: -0.000000000025000
    //       2148466688 0000000000 0000000000 0000025000
    // num2: 0.0000000000250000
    //       0001048576 0000000000 0000000000 0000250000
    // res : False 0
}
END_TEST

START_TEST(EQUALTest09) {
    lib_decimal num1 = new_decimal(1, 0, 0, 0, 28);
    lib_decimal num2 = new_decimal(1, 0, 0, 0, 28);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.0000000000000000000000000001
    //       0001835008 0000000000 0000000000 0000000001
    // num2: 0.0000000000000000000000000001
    //       0001835008 0000000000 0000000000 0000000001
    // res : True 1
}
END_TEST

START_TEST(EQUALTest10) {
    lib_decimal num1 = new_decimal(2222222, 333333, 444444, 1, 28);
    lib_decimal num2 = new_decimal(2222222, 333333, 444444, 1, 28);
    ck_assert_uint_eq(lib_is_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: -0.0008198544724527422294321294
    //       2149318656 0000444444 0000333333 0002222222
    // num2: -0.0008198544724527422294321294
    //       2149318656 0000444444 0000333333 0002222222
    // res : True 1
}
END_TEST

START_TEST(NOTEQUALTest01) {
    lib_decimal num1 = new_decimal(0, 10, 200, 0, 25);
    lib_decimal num2 = new_decimal(0, 10, 200, 0, 25);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.0003689348814784859996160
    //       0001638400 0000000200 0000000010 0000000000
    // num2: 0.0003689348814784859996160
    //       0001638400 0000000200 0000000010 0000000000
    // res : False 0
}
END_TEST

START_TEST(NOTEQUALTest02) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 0);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: 0
    //       0000000000 0000000000 0000000000 0000000000
    // num2: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(NOTEQUALTest03) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 5);
    lib_decimal num2 = new_decimal(0, 0, 0, 0, 1);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.00000
    //       0000327680 0000000000 0000000000 0000000000
    // num2: 0.0
    //       0000065536 0000000000 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(NOTEQUALTest04) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 5);
    lib_decimal num2 = new_decimal(0, 0, 0, 1, 1);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.00000
    //       0000327680 0000000000 0000000000 0000000000
    // num2: 0.0
    //       2147549184 0000000000 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(NOTEQUALTest05) {
    lib_decimal num1 = new_decimal(0, 777, 8888, 0, 28);
    lib_decimal num2 = new_decimal(10, 5454, 5454, 1, 15);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.0000163954661330467684352000
    //       0001835008 0000008888 0000000777 0000000000
    // num2: -100608542.201436646146058
    //       2148466688 0000005454 0000005454 0000000010
    // res : True 1
}
END_TEST

START_TEST(NOTEQUALTest06) {
    lib_decimal num1 = new_decimal(25000, 0, 0, 0, 3);
    lib_decimal num2 = new_decimal(25, 0, 0, 0, 0);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: 25.000
    //       0000196608 0000000000 0000000000 0000025000
    // num2: 25
    //       0000000000 0000000000 0000000000 0000000025
    // res : False 0
}
END_TEST

START_TEST(NOTEQUALTest07) {
    lib_decimal num1 = new_decimal(25000, 0, 0, 0, 15);
    lib_decimal num2 = new_decimal(250000, 0, 0, 0, 16);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.000000000025000
    //       0000983040 0000000000 0000000000 0000025000
    // num2: 0.0000000000250000
    //       0001048576 0000000000 0000000000 0000250000
    // res : False 0
}
END_TEST

START_TEST(NOTEQUALTest08) {
    lib_decimal num1 = new_decimal(25000, 0, 0, 1, 15);
    lib_decimal num2 = new_decimal(250000, 0, 0, 0, 16);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 1);

    // --- C# operation <EQUAL> testing result:
    // num1: -0.000000000025000
    //       2148466688 0000000000 0000000000 0000025000
    // num2: 0.0000000000250000
    //       0001048576 0000000000 0000000000 0000250000
    // res : True 1
}
END_TEST

START_TEST(NOTEQUALTest09) {
    lib_decimal num1 = new_decimal(1, 0, 0, 0, 28);
    lib_decimal num2 = new_decimal(1, 0, 0, 0, 28);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: 0.0000000000000000000000000001
    //       0001835008 0000000000 0000000000 0000000001
    // num2: 0.0000000000000000000000000001
    //       0001835008 0000000000 0000000000 0000000001
    // res : False 0
}
END_TEST

START_TEST(NOTEQUALTest10) {
    lib_decimal num1 = new_decimal(2222222, 333333, 444444, 1, 28);
    lib_decimal num2 = new_decimal(2222222, 333333, 444444, 1, 28);
    ck_assert_uint_eq(lib_is_not_equal(num1, num2), 0);

    // --- C# operation <EQUAL> testing result:
    // num1: -0.0008198544724527422294321294
    //       2149318656 0000444444 0000333333 0002222222
    // num2: -0.0008198544724527422294321294
    //       2149318656 0000444444 0000333333 0002222222
    // res : False 0
}
END_TEST

START_TEST(GREATEQTest01) {
    lib_decimal num1 = new_decimal(1, 0, 0, 1, 10);
    lib_decimal num2 = new_decimal(0, 0, 0, 1, 28);
    ck_assert_uint_eq(lib_is_greater_or_equal(num1, num2), 0);

    // --- C# operation <GREATEQ> testing result:
    // num1: -0.0000000001
    //       2148139008 0000000000 0000000000 0000000001
    // num2: 0.0000000000000000000000000000
    //       2149318656 0000000000 0000000000 0000000000
    // res : False 0
}
END_TEST

START_TEST(GREATEQTest02) {
    lib_decimal num1 = new_decimal(1, 0, 0, 1, 25);
    lib_decimal num2 = new_decimal(1, 0, 0, 1, 28);
    ck_assert_uint_eq(lib_is_greater_or_equal(num1, num2), 0);

    // --- C# operation <GREATEQ> testing result:
    // num1: -0.0000000000000000000000001
    //       2149122048 0000000000 0000000000 0000000001
    // num2: -0.0000000000000000000000000001
    //       2149318656 0000000000 0000000000 0000000001
    // res : False 0
}
END_TEST

START_TEST(GREATEQTest03) {
    lib_decimal num1 = new_decimal(1, 0, 0, 0, 25);
    lib_decimal num2 = new_decimal(1, 0, 0, 0, 28);
    ck_assert_uint_eq(lib_is_greater_or_equal(num1, num2), 1);

    // --- C# operation <GREATEQ> testing result:
    // num1: 0.0000000000000000000000001
    //       0001638400 0000000000 0000000000 0000000001
    // num2: 0.0000000000000000000000000001
    //       0001835008 0000000000 0000000000 0000000001
    // res : True 1
}
END_TEST

START_TEST(GREATEQTest04) {
    lib_decimal num1 = new_decimal(1, 0, 8888, 0, 28);
    lib_decimal num2 = new_decimal(1, 0, 8888, 0, 28);
    ck_assert_uint_eq(lib_is_greater_or_equal(num1, num2), 1);

    // --- C# operation <GREATEQ> testing result:
    // num1: 0.0000163954661327130494763009
    //       0001835008 0000008888 0000000000 0000000001
    // num2: 0.0000163954661327130494763009
    //       0001835008 0000008888 0000000000 0000000001
    // res : True 1
}
END_TEST

START_TEST(GREATEQTest05) {
    lib_decimal num1 = new_decimal(1, 0, 8888, 1, 28);
    lib_decimal num2 = new_decimal(1, 0, 8888, 0, 28);
    ck_assert_uint_eq(lib_is_greater_or_equal(num1, num2), 0);

    // --- C# operation <GREATEQ> testing result:
    // num1: -0.0000163954661327130494763009
    //       2149318656 0000008888 0000000000 0000000001
    // num2: 0.0000163954661327130494763009
    //       0001835008 0000008888 0000000000 0000000001
    // res : False 0
}
END_TEST

START_TEST(LESSEQTest01) {
    lib_decimal num1 = new_decimal(1, 0, 8888, 1, 28);
    lib_decimal num2 = new_decimal(1, 0, 8888, 0, 28);
    ck_assert_uint_eq(lib_is_less_or_equal(num1, num2), 1);

    // --- C# operation <LESSEQ> testing result:
    // num1: -0.0000163954661327130494763009
    //       2149318656 0000008888 0000000000 0000000001
    // num2: 0.0000163954661327130494763009
    //       0001835008 0000008888 0000000000 0000000001
    // res : True 1
}
END_TEST

START_TEST(LESSEQTest02) {
    lib_decimal num1 = new_decimal(1, 0, 8888, 1, 28);
    lib_decimal num2 = new_decimal(1, 0, 8888, 1, 28);
    ck_assert_uint_eq(lib_is_less_or_equal(num1, num2), 1);

    // --- C# operation <LESSEQ> testing result:
    // num1: -0.0000163954661327130494763009
    //       2149318656 0000008888 0000000000 0000000001
    // num2: -0.0000163954661327130494763009
    //       2149318656 0000008888 0000000000 0000000001
    // res : True 1
}
END_TEST

START_TEST(LESSEQTest03) {
    lib_decimal num1 = new_decimal(1, 0, 8888, 1, 5);
    lib_decimal num2 = new_decimal(1, 0, 8888, 1, 8);
    ck_assert_uint_eq(lib_is_less_or_equal(num1, num2), 1);

    // --- C# operation <LESSEQ> testing result:
    // num1: -1639546613271304947.63009
    //       2147811328 0000008888 0000000000 0000000001
    // num2: -1639546613271304.94763009
    //       2148007936 0000008888 0000000000 0000000001
    // res : True 1
}
END_TEST

START_TEST(LESSEQTest04) {
    lib_decimal num1 = new_decimal(1, 0, 8888, 0, 5);
    lib_decimal num2 = new_decimal(1, 0, 8888, 0, 8);
    ck_assert_uint_eq(lib_is_less_or_equal(num1, num2), 0);

    // --- C# operation <LESSEQ> testing result:
    // num1: 1639546613271304947.63009
    //       0000327680 0000008888 0000000000 0000000001
    // num2: 1639546613271304.94763009
    //       0000524288 0000008888 0000000000 0000000001
    // res : False 0
}
END_TEST

START_TEST(LESSEQTest05) {
    lib_decimal num1 = new_decimal(128400, 0, 0, 0, 5);
    lib_decimal num2 = new_decimal(1284, 0, 0, 0, 3);
    ck_assert_uint_eq(lib_is_less_or_equal(num1, num2), 1);

    // --- C# operation <LESSEQ> testing result:
    // num1: 1.28400
    //       0000327680 0000000000 0000000000 0000128400
    // num2: 1.284
    //       0000196608 0000000000 0000000000 0000001284
    // res : True 1
}
END_TEST

START_TEST(CONVERT_FROM_INT_Test01) {
    int int_num = 1231243;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_int_to_decimal(int_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1231243);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <CONVERT_FROM_INT> testing result:
    // int_num: 1231243
    // res : 1231243
    //       0000000000 0000000000 0000000000 0001231243
}
END_TEST

START_TEST(CONVERT_FROM_INT_Test02) {
    int int_num = 0;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_int_to_decimal(int_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <CONVERT_FROM_INT> testing result:
    // int_num: 0
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(CONVERT_FROM_INT_Test03) {
    int int_num = 2121212211;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_int_to_decimal(int_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2121212211);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <CONVERT_FROM_INT> testing result:
    // int_num: 2121212211
    // res : 2121212211
    //       0000000000 0000000000 0000000000 2121212211
}
END_TEST

START_TEST(CONVERT_FROM_INT_Test04) {
    int int_num = -2121212211;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_int_to_decimal(int_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2121212211);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <CONVERT_FROM_INT> testing result:
    // int_num: -2121212211
    // res : -2121212211
    //       2147483648 0000000000 0000000000 2121212211
}
END_TEST

START_TEST(CONVERT_FROM_INT_Test05) {
    int int_num = -95452;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_int_to_decimal(int_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 95452);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <CONVERT_FROM_INT> testing result:
    // int_num: -95452
    // res : -95452
    //       2147483648 0000000000 0000000000 0000095452
}
END_TEST

START_TEST(CONVERT_TO_INT_Test01) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 5);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 0);
    ck_assert_uint_eq(result, 0);

    // --- C# operation <CONVERT_TO_INT> testing result:
    // decimal_num : 0.00000
    //       0000327680 0000000000 0000000000 0000000000
    // int_num: 0
}
END_TEST

START_TEST(CONVERT_TO_INT_Test02) {
    lib_decimal num1 = new_decimal(128568, 0, 0, 0, 0);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 0);
    ck_assert_uint_eq(result, 128568);

    // --- C# operation <CONVERT_TO_INT> testing result:
    // decimal_num : 128568
    //       0000000000 0000000000 0000000000 0000128568
    // int_num: 128568
}
END_TEST

START_TEST(CONVERT_TO_INT_Test03) {
    lib_decimal num1 = new_decimal(128568, 0, 0, 0, 7);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 0);
    ck_assert_uint_eq(result, 0);

    // --- C# operation <CONVERT_TO_INT> testing result:
    // decimal_num : 0.0128568
    //       0000458752 0000000000 0000000000 0000128568
    // int_num: 0
}
END_TEST

START_TEST(CONVERT_TO_INT_Test04) {
    lib_decimal num1 = new_decimal(128568, 0, 0, 0, 4);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 0);
    ck_assert_uint_eq(result, 12);

    // --- C# operation <CONVERT_TO_INT> testing result:
    // decimal_num : 12.8568
    //       0000262144 0000000000 0000000000 0000128568
    // int_num: 12
}
END_TEST

START_TEST(CONVERT_TO_INT_Test05) {
    lib_decimal num1 = new_decimal(128568, 565656, 1215445, 0, 25);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 0);
    ck_assert_uint_eq(result, 2);

    // --- C# operation <CONVERT_TO_INT> testing result:
    // decimal_num : 2.2421002853099379984823864
    //       0001638400 0001215445 0000565656 0000128568
    // int_num: 2
}
END_TEST

START_TEST(CONVERT_TO_INT_Test06) {
    lib_decimal num1 = new_decimal(128568, 565656, 1215445, 1, 25);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 0);
    ck_assert_uint_eq(result, -2);

    // --- C# operation <CONVERT_TO_INT> testing result:
    // decimal_num : -2.2421002853099379984823864
    //       2149122048 0001215445 0000565656 0000128568
    // int_num: -2
}
END_TEST

START_TEST(CONVERT_TO_INT_Test07) {
    lib_decimal num1 = new_decimal(128568, 565656, 1, 1, 15);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 0);
    ck_assert_uint_eq(result, -18449);

    // --- C# operation <CONVERT_TO_INT> testing result:
    // decimal_num : -18449.173547730466360
    //       2148466688 0000000001 0000565656 0000128568
    // int_num: -18449
}
END_TEST

START_TEST(CONVERT_TO_INT_Test08) {
    lib_decimal num1 = new_decimal(128568, 565656, 13214342, 0, 15);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 1);
}
END_TEST

START_TEST(CONVERT_TO_INT_Test09) {
    lib_decimal num1 = new_decimal(128568, 565656, 13214342, 1, 15);
    int result;
    ck_assert_uint_eq(lib_from_decimal_to_int(num1, &result), 2);
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test01) {
    float float_num = -1.006;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1006);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147680256);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: -1.006
    // res : -1.006
    //       2147680256 0000000000 0000000000 0000001006
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test02) {
    float float_num = 1.34351E+10;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 550198112);
    ck_assert_uint_eq(result.bits[1], 3);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: 1.34351E+10
    // res : 13435100000
    //       0000000000 0000000000 0000000003 0550198112
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test03) {
    float float_num = 1.34351E+15;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1280138240);
    ck_assert_uint_eq(result.bits[1], 312810);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: 1.34351E+15
    // res : 1343510000000000
    //       0000000000 0000000000 0000312810 1280138240
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test04) {
    float float_num = 1.4517E+20;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 997523456);
    ck_assert_uint_eq(result.bits[1], 3735253467);
    ck_assert_uint_eq(result.bits[2], 7);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: 1.4517E+20
    // res : 145170000000000000000
    //       0000000000 0000000007 3735253467 0997523456
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test05) {
    float float_num = 0;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: 0
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}

START_TEST(CONVERT_FROM_FLOAT_Test06) {
    float float_num = 150.8974;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1508974);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 262144);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: 150.8974
    // res : 150.8974
    //       0000262144 0000000000 0000000000 0001508974
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test07) {
    float float_num = -150.8974;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1508974);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147745792);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: -150.8974
    // res : -150.8974
    //       2147745792 0000000000 0000000000 0001508974
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test08) {
    float float_num = 1.8974E32f;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 2);
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test09) {
    float float_num = -1.50896E+10;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2204698112);
    ck_assert_uint_eq(result.bits[1], 3);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: -1.50896E+10
    // res : -15089600000
    //       2147483648 0000000000 0000000003 2204698112
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test10) {
    float float_num = -1.50896E-10;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 0);
    ck_assert_uint_eq(result.bits[0], 150896);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2148466688);

    // --- C# operation <CONVERT_FROM_FLOAT> testing result:
    // float_num: -1.50896E-10
    // res : -0.000000000150896
    //       2148466688 0000000000 0000000000 0000150896
}
END_TEST

START_TEST(CONVERT_FROM_FLOAT_Test11) {
    float float_num = 1.8974E-32f;
    lib_decimal result;
    ck_assert_uint_eq(lib_from_float_to_decimal(float_num, &result), 1);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(CONVERT_TO_FLOAT_Test01) {
    lib_decimal num1 = new_decimal(12845, 0, 0, 0, 2);
    float result;
    ck_assert_uint_eq(lib_from_decimal_to_float(num1, &result), 0);
    ck_assert_float_eq_tol(result, 128.45, lib_EPS_TEST);

    // --- C# operation <CONVERT_TO_FLOAT> testing result:
    // decimal_num : 128.45
    //       0000131072 0000000000 0000000000 0000012845
    // float_num: 128.45
}
END_TEST

START_TEST(CONVERT_TO_FLOAT_Test02) {
    lib_decimal num1 = new_decimal(478, 237, 425, 0, 5);
    float result;
    ck_assert_uint_eq(lib_from_decimal_to_float(num1, &result), 0);
    ck_assert_float_eq_tol(result, 7.839867E+16, lib_EPS_TEST);

    // --- C# operation <CONVERT_TO_FLOAT> testing result:
    // decimal_num : 78398662323444666.86430
    //       0000327680 0000000425 0000000237 0000000478
    // float_num: 7.839867E+16
}
END_TEST

START_TEST(CONVERT_TO_FLOAT_Test03) {
    lib_decimal num1 = new_decimal(478, 237, 425, 1, 5);
    float result;
    ck_assert_uint_eq(lib_from_decimal_to_float(num1, &result), 0);
    ck_assert_float_eq_tol(result, -7.839867E+16, lib_EPS_TEST);

    // --- C# operation <CONVERT_TO_FLOAT> testing result:
    // decimal_num : -78398662323444666.86430
    //       2147811328 0000000425 0000000237 0000000478
    // float_num: -7.839867E+16
}
END_TEST

START_TEST(CONVERT_TO_FLOAT_Test04) {
    lib_decimal num1 = new_decimal(478, 237, 425, 1, 25);
    float result;
    ck_assert_uint_eq(lib_from_decimal_to_float(num1, &result), 0);
    ck_assert_float_eq_tol(result, -0.0007839866, lib_EPS_TEST);

    // --- C# operation <CONVERT_TO_FLOAT> testing result:
    // decimal_num : -0.0007839866232344466686430
    //       2149122048 0000000425 0000000237 0000000478
    // float_num: -0.0007839866
}
END_TEST

START_TEST(CONVERT_TO_FLOAT_Test05) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    float result;
    ck_assert_uint_eq(lib_from_decimal_to_float(num1, &result), 0);
    ck_assert_float_eq_tol(result, 0, lib_EPS_TEST);

    // --- C# operation <CONVERT_TO_FLOAT> testing result:
    // decimal_num : 0
    //       0000000000 0000000000 0000000000 0000000000
    // float_num: 0
}
END_TEST

START_TEST(CONVERT_TO_FLOAT_Test06) {
    lib_decimal num1 = new_decimal(10000, 0, 0, 0, 0);
    float result;
    ck_assert_uint_eq(lib_from_decimal_to_float(num1, &result), 0);
    ck_assert_float_eq_tol(result, 10000, lib_EPS_TEST);

    // --- C# operation <CONVERT_TO_FLOAT> testing result:
    // decimal_num : 10000
    //       0000000000 0000000000 0000000000 0000010000
    // float_num: 10000
}
END_TEST

START_TEST(CONVERT_TO_FLOAT_Test07) {
    lib_decimal num1 = new_decimal(0, 0, 77, 1, 6);
    float result;
    ck_assert_uint_eq(lib_from_decimal_to_float(num1, &result), 0);
    ck_assert_float_eq_tol(result / -1.420399E+15, -1.420399E+15 / result,
                           lib_EPS_TEST);

    // --- C# operation <CONVERT_TO_FLOAT> testing result:
    // decimal_num : -1420399293675635.474432
    //       2147876864 0000000077 0000000000 0000000000
    // float_num: -1.420399E+15
}
END_TEST

START_TEST(CONVERT_TO_FLOAT_Test08) {
    lib_decimal num1 = new_decimal(666, 8888, 7777, 1, 6);
    float result;
    ck_assert_uint_eq(lib_from_decimal_to_float(num1, &result), 0);
    ck_assert_float_eq_tol(result / -1.434603E+17, -1.434603E+17 / result,
                           lib_EPS_TEST);

    // --- C# operation <CONVERT_TO_FLOAT> testing result:
    // decimal_num : -143460328699412852.245146
    //       2147876864 0000007777 0000008888 0000000666
    // float_num: -1.434603E+17
}
END_TEST

START_TEST(FLOORTest01) {
    lib_decimal num1 = new_decimal(1, 0, 0, 1, 25);
    lib_decimal result;
    ck_assert_uint_eq(lib_floor(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <FLOOR> testing result:
    // num: -0.0000000000000000000000001
    //       2149122048 0000000000 0000000000 0000000001
    // res : -1
    //       2147483648 0000000000 0000000000 0000000001
}
END_TEST

START_TEST(FLOORTest02) {
    lib_decimal num1 = new_decimal(1, 0, 0, 0, 25);
    lib_decimal result;
    ck_assert_uint_eq(lib_floor(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <FLOOR> testing result:
    // num: 0.0000000000000000000000001
    //       0001638400 0000000000 0000000000 0000000001
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(FLOORTest03) {
    lib_decimal num1 = new_decimal(125684, 0, 0, 0, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_floor(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 125);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <FLOOR> testing result:
    // num: 125.684
    //       0000196608 0000000000 0000000000 0000125684
    // res : 125
    //       0000000000 0000000000 0000000000 0000000125
}
END_TEST

START_TEST(FLOORTest04) {
    lib_decimal num1 = new_decimal(125684, 0, 0, 1, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_floor(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 126);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <FLOOR> testing result:
    // num: -125.684
    //       2147680256 0000000000 0000000000 0000125684
    // res : -126
    //       2147483648 0000000000 0000000000 0000000126
}
END_TEST

START_TEST(FLOORTest05) {
    lib_decimal num1 = new_decimal(125684, 6556, 65652323, 0, 25);
    lib_decimal result;
    ck_assert_uint_eq(lib_floor(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 121);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <FLOOR> testing result:
    // num: 121.1071600225543448684522228
    //       0001638400 0065652323 0000006556 0000125684
    // res : 121
    //       0000000000 0000000000 0000000000 0000000121
}
END_TEST

START_TEST(FLOORTest06) {
    lib_decimal num1 = new_decimal(125684, 6556, 65652323, 1, 25);
    lib_decimal result;
    ck_assert_uint_eq(lib_floor(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 122);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <FLOOR> testing result:
    // num: -121.1071600225543448684522228
    //       2149122048 0065652323 0000006556 0000125684
    // res : -122
    //       2147483648 0000000000 0000000000 0000000122
}
END_TEST

START_TEST(FLOORTest07) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_floor(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <FLOOR> testing result:
    // num: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(FLOORTest08) {
    lib_decimal num1 = new_decimal(lib_INT_MAX, lib_INT_MAX, lib_INT_MAX, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_floor(num1, &result), 2);
}
END_TEST

START_TEST(ROUNDTest01) {
    lib_decimal num1 = new_decimal(15, 0, 0, 0, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_round(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <ROUND> testing result:
    // num: 1.5
    //       0000065536 0000000000 0000000000 0000000015
    // res : 2
    //       0000000000 0000000000 0000000000 0000000002
}
END_TEST

START_TEST(ROUNDTest02) {
    lib_decimal num1 = new_decimal(15, 0, 0, 1, 1);
    lib_decimal result;
    ck_assert_uint_eq(lib_round(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <ROUND> testing result:
    // num: -1.5
    //       2147549184 0000000000 0000000000 0000000015
    // res : -2
    //       2147483648 0000000000 0000000000 0000000002
}
END_TEST

START_TEST(ROUNDTest03) {
    lib_decimal num1 = new_decimal(14242, 0, 0, 0, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_round(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 14);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <ROUND> testing result:
    // num: 14.242
    //       0000196608 0000000000 0000000000 0000014242
    // res : 14
    //       0000000000 0000000000 0000000000 0000000014
}
END_TEST

START_TEST(ROUNDTest04) {
    lib_decimal num1 = new_decimal(14242, 0, 0, 1, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_round(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 14);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <ROUND> testing result:
    // num: -14.242
    //       2147680256 0000000000 0000000000 0000014242
    // res : -14
    //       2147483648 0000000000 0000000000 0000000014
}
END_TEST

START_TEST(ROUNDTest05) {
    lib_decimal num1 = new_decimal(14242, 8888, 9999941, 0, 15);
    lib_decimal result;
    ck_assert_uint_eq(lib_round(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 4077725947);
    ck_assert_uint_eq(result.bits[1], 42);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <ROUND> testing result:
    // num: 184466352379.233340965795746
    //       0000983040 0009999941 0000008888 0000014242
    // res : 184466352379
    //       0000000000 0000000000 0000000042 4077725947
}
END_TEST

START_TEST(ROUNDTest06) {
    lib_decimal num1 = new_decimal(14242, 8888, 9999941, 1, 15);
    lib_decimal result;
    ck_assert_uint_eq(lib_round(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 4077725947);
    ck_assert_uint_eq(result.bits[1], 42);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <ROUND> testing result:
    // num: -184466352379.233340965795746
    //       2148466688 0009999941 0000008888 0000014242
    // res : -184466352379
    //       2147483648 0000000000 0000000042 4077725947
}
END_TEST

START_TEST(ROUNDTest07) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_round(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <ROUND> testing result:
    // num: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(TRUNCATETest01) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_truncate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <TRUNCATE> testing result:
    // num: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       0000000000 0000000000 0000000000 0000000000
}
END_TEST

START_TEST(TRUNCATETest02) {
    lib_decimal num1 = new_decimal(45800000, 0, 0, 0, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_truncate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 45800);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <TRUNCATE> testing result:
    // num: 45800.000
    //       0000196608 0000000000 0000000000 0045800000
    // res : 45800
    //       0000000000 0000000000 0000000000 0000045800
}
END_TEST

START_TEST(TRUNCATETest03) {
    lib_decimal num1 = new_decimal(45800000, 0, 0, 1, 3);
    lib_decimal result;
    ck_assert_uint_eq(lib_truncate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 45800);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <TRUNCATE> testing result:
    // num: -45800.000
    //       2147680256 0000000000 0000000000 0045800000
    // res : -45800
    //       2147483648 0000000000 0000000000 0000045800
}
END_TEST

START_TEST(TRUNCATETest04) {
    lib_decimal num1 = new_decimal(45800000, 65656, 65455454, 0, 24);
    lib_decimal result;
    ck_assert_uint_eq(lib_truncate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1207);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <TRUNCATE> testing result:
    // num: 1207.440008166750155580299840
    //       0001572864 0065455454 0000065656 0045800000
    // res : 1207
    //       0000000000 0000000000 0000000000 0000001207
}
END_TEST

START_TEST(TRUNCATETest05) {
    lib_decimal num1 = new_decimal(45800000, 65656, 65455454, 1, 24);
    lib_decimal result;
    ck_assert_uint_eq(lib_truncate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1207);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <TRUNCATE> testing result:
    // num: -1207.440008166750155580299840
    //       2149056512 0065455454 0000065656 0045800000
    // res : -1207
    //       2147483648 0000000000 0000000000 0000001207
}
END_TEST

START_TEST(TRUNCATETest06) {
    lib_decimal num1 = new_decimal(45800000, 65656667, 654554541, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_truncate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 45800000);
    ck_assert_uint_eq(result.bits[1], 65656667);
    ck_assert_uint_eq(result.bits[2], 654554541);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <TRUNCATE> testing result:
    // num: -12074400100393418962901850688
    //       2147483648 0654554541 0065656667 0045800000
    // res : -12074400100393418962901850688
    //       2147483648 0654554541 0065656667 0045800000
}
END_TEST

START_TEST(TRUNCATETest07) {
    lib_decimal num1 = new_decimal(45800000, 65656667, 654554541, 1, 28);
    lib_decimal result;
    ck_assert_uint_eq(lib_truncate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <TRUNCATE> testing result:
    // num: -1.2074400100393418962901850688
    //       2149318656 0654554541 0065656667 0045800000
    // res : -1
    //       2147483648 0000000000 0000000000 0000000001
}
END_TEST

START_TEST(TRUNCATETest08) {
    lib_decimal num1 = new_decimal(45800000, 65656667, 654554541, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_truncate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 45800000);
    ck_assert_uint_eq(result.bits[1], 65656667);
    ck_assert_uint_eq(result.bits[2], 654554541);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <TRUNCATE> testing result:
    // num: 12074400100393418962901850688
    //       0000000000 0654554541 0065656667 0045800000
    // res : 12074400100393418962901850688
    //       0000000000 0654554541 0065656667 0045800000
}
END_TEST

START_TEST(NEGATETest01) {
    lib_decimal num1 = new_decimal(45800000, 65656667, 654554541, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_negate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 45800000);
    ck_assert_uint_eq(result.bits[1], 65656667);
    ck_assert_uint_eq(result.bits[2], 654554541);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <NEGATE> testing result:
    // num: 12074400100393418962901850688
    //       0000000000 0654554541 0065656667 0045800000
    // res : -12074400100393418962901850688
    //       2147483648 0654554541 0065656667 0045800000
}
END_TEST

START_TEST(NEGATETest02) {
    lib_decimal num1 = new_decimal(4500, 65667, 6554541, 1, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_negate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 4500);
    ck_assert_uint_eq(result.bits[1], 65667);
    ck_assert_uint_eq(result.bits[2], 6554541);
    ck_assert_uint_eq(result.bits[3], 0);

    // --- C# operation <NEGATE> testing result:
    // num: -120909940347918315776119188
    //       2147483648 0006554541 0000065667 0000004500
    // res : 120909940347918315776119188
    //       0000000000 0006554541 0000065667 0000004500
}
END_TEST

START_TEST(NEGATETest03) {
    lib_decimal num1 = new_decimal(4500, 65667, 6554541, 1, 15);
    lib_decimal result;
    ck_assert_uint_eq(lib_negate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 4500);
    ck_assert_uint_eq(result.bits[1], 65667);
    ck_assert_uint_eq(result.bits[2], 6554541);
    ck_assert_uint_eq(result.bits[3], 983040);

    // --- C# operation <NEGATE> testing result:
    // num: -120909940347.918315776119188
    //       2148466688 0006554541 0000065667 0000004500
    // res : 120909940347.918315776119188
    //       0000983040 0006554541 0000065667 0000004500
}
END_TEST

START_TEST(NEGATETest04) {
    lib_decimal num1 = new_decimal(4500, 65667, 6554541, 0, 15);
    lib_decimal result;
    ck_assert_uint_eq(lib_negate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 4500);
    ck_assert_uint_eq(result.bits[1], 65667);
    ck_assert_uint_eq(result.bits[2], 6554541);
    ck_assert_uint_eq(result.bits[3], 2148466688);

    // --- C# operation <NEGATE> testing result:
    // num: 120909940347.918315776119188
    //       0000983040 0006554541 0000065667 0000004500
    // res : -120909940347.918315776119188
    //       2148466688 0006554541 0000065667 0000004500
}
END_TEST

START_TEST(NEGATETest05) {
    lib_decimal num1 = new_decimal(0, 0, 0, 0, 0);
    lib_decimal result;
    ck_assert_uint_eq(lib_negate(num1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 2147483648);

    // --- C# operation <NEGATE> testing result:
    // num: 0
    //       0000000000 0000000000 0000000000 0000000000
    // res : 0
    //       2147483648 0000000000 0000000000 0000000000
}
END_TEST

Suite *my_suite_create() {
    Suite *my_suite = suite_create("Test_decimal");
    TCase *DecimalTest = tcase_create("DECIMAL");

    suite_add_tcase(my_suite, DecimalTest);
    tcase_add_test(DecimalTest, ADDTest01);
    tcase_add_test(DecimalTest, ADDTest02);
    tcase_add_test(DecimalTest, ADDTest03);
    tcase_add_test(DecimalTest, ADDTest04);
    tcase_add_test(DecimalTest, ADDTest05);
    tcase_add_test(DecimalTest, ADDTest06);
    tcase_add_test(DecimalTest, ADDTest07);
    tcase_add_test(DecimalTest, ADDTest08);
    tcase_add_test(DecimalTest, ADDTest09);
    tcase_add_test(DecimalTest, ADDTest10);
    tcase_add_test(DecimalTest, ADDTest11);
    tcase_add_test(DecimalTest, ADDTest12);
    tcase_add_test(DecimalTest, ADDTest13);
    tcase_add_test(DecimalTest, ADDTest14);
    tcase_add_test(DecimalTest, ADDTest15);
    tcase_add_test(DecimalTest, ADDTest16);
    tcase_add_test(DecimalTest, ADDTest17);
    tcase_add_test(DecimalTest, ADDTest18);
    tcase_add_test(DecimalTest, ADDTest19);
    tcase_add_test(DecimalTest, ADDTest20);
    tcase_add_test(DecimalTest, ADDTest21);
    tcase_add_test(DecimalTest, ADDTest22);
    tcase_add_test(DecimalTest, ADDTest23);
    tcase_add_test(DecimalTest, ADDTest24);

    tcase_add_test(DecimalTest, SUBTest01);
    tcase_add_test(DecimalTest, SUBTest02);
    tcase_add_test(DecimalTest, SUBTest03);
    tcase_add_test(DecimalTest, SUBTest04);
    tcase_add_test(DecimalTest, SUBTest05);
    tcase_add_test(DecimalTest, SUBTest06);
    tcase_add_test(DecimalTest, SUBTest07);
    tcase_add_test(DecimalTest, SUBTest08);
    tcase_add_test(DecimalTest, SUBTest09);
    tcase_add_test(DecimalTest, SUBTest10);
    tcase_add_test(DecimalTest, SUBTest11);
    tcase_add_test(DecimalTest, SUBTest12);
    tcase_add_test(DecimalTest, SUBTest13);

    tcase_add_test(DecimalTest, MULTest01);
    tcase_add_test(DecimalTest, MULTest02);
    tcase_add_test(DecimalTest, MULTest03);
    tcase_add_test(DecimalTest, MULTest04);
    tcase_add_test(DecimalTest, MULTest05);
    tcase_add_test(DecimalTest, MULTest06);
    tcase_add_test(DecimalTest, MULTest07);
    tcase_add_test(DecimalTest, MULTest08);
    tcase_add_test(DecimalTest, MULTest09);
    tcase_add_test(DecimalTest, MULTest10);
    tcase_add_test(DecimalTest, MULTest11);
    tcase_add_test(DecimalTest, MULTest12);
    tcase_add_test(DecimalTest, MULTest13);

    tcase_add_test(DecimalTest, DIVTest01);
    tcase_add_test(DecimalTest, DIVTest02);
    tcase_add_test(DecimalTest, DIVTest03);
    tcase_add_test(DecimalTest, DIVTest04);
    tcase_add_test(DecimalTest, DIVTest05);
    tcase_add_test(DecimalTest, DIVTest06);
    tcase_add_test(DecimalTest, DIVTest07);
    tcase_add_test(DecimalTest, DIVTest08);
    tcase_add_test(DecimalTest, DIVTest09);
    tcase_add_test(DecimalTest, DIVTest10);
    tcase_add_test(DecimalTest, DIVTest11);
    tcase_add_test(DecimalTest, DIVTest12);
    tcase_add_test(DecimalTest, DIVTest13);
    tcase_add_test(DecimalTest, DIVTest14);
    tcase_add_test(DecimalTest, DIVTest15);
    tcase_add_test(DecimalTest, DIVTest16);
    tcase_add_test(DecimalTest, DIVTest17);
    tcase_add_test(DecimalTest, DIVTest18);
    tcase_add_test(DecimalTest, DIVTest19);
    tcase_add_test(DecimalTest, DIVTest20);

    tcase_add_test(DecimalTest, MODTest01);
    tcase_add_test(DecimalTest, MODTest02);
    tcase_add_test(DecimalTest, MODTest03);
    tcase_add_test(DecimalTest, MODTest04);
    tcase_add_test(DecimalTest, MODTest05);
    tcase_add_test(DecimalTest, MODTest06);
    tcase_add_test(DecimalTest, MODTest07);
    tcase_add_test(DecimalTest, MODTest08);
    tcase_add_test(DecimalTest, MODTest09);
    tcase_add_test(DecimalTest, MODTest10);
    tcase_add_test(DecimalTest, MODTest11);
    tcase_add_test(DecimalTest, MODTest12);

    tcase_add_test(DecimalTest, GREATTest01);
    tcase_add_test(DecimalTest, GREATTest02);
    tcase_add_test(DecimalTest, GREATTest03);
    tcase_add_test(DecimalTest, GREATTest04);
    tcase_add_test(DecimalTest, GREATTest05);
    tcase_add_test(DecimalTest, GREATTest06);
    tcase_add_test(DecimalTest, GREATTest07);
    tcase_add_test(DecimalTest, GREATTest08);
    tcase_add_test(DecimalTest, GREATTest09);
    tcase_add_test(DecimalTest, GREATTest10);
    tcase_add_test(DecimalTest, GREATTest11);

    tcase_add_test(DecimalTest, LESSTest01);
    tcase_add_test(DecimalTest, LESSTest02);
    tcase_add_test(DecimalTest, LESSTest03);
    tcase_add_test(DecimalTest, LESSTest04);
    tcase_add_test(DecimalTest, LESSTest05);
    tcase_add_test(DecimalTest, LESSTest06);
    tcase_add_test(DecimalTest, LESSTest07);
    tcase_add_test(DecimalTest, LESSTest08);
    tcase_add_test(DecimalTest, LESSTest09);
    tcase_add_test(DecimalTest, LESSTest10);

    tcase_add_test(DecimalTest, EQUALTest01);
    tcase_add_test(DecimalTest, EQUALTest02);
    tcase_add_test(DecimalTest, EQUALTest03);
    tcase_add_test(DecimalTest, EQUALTest04);
    tcase_add_test(DecimalTest, EQUALTest05);
    tcase_add_test(DecimalTest, EQUALTest06);
    tcase_add_test(DecimalTest, EQUALTest07);
    tcase_add_test(DecimalTest, EQUALTest08);
    tcase_add_test(DecimalTest, EQUALTest09);
    tcase_add_test(DecimalTest, EQUALTest10);

    tcase_add_test(DecimalTest, NOTEQUALTest01);
    tcase_add_test(DecimalTest, NOTEQUALTest02);
    tcase_add_test(DecimalTest, NOTEQUALTest03);
    tcase_add_test(DecimalTest, NOTEQUALTest04);
    tcase_add_test(DecimalTest, NOTEQUALTest05);
    tcase_add_test(DecimalTest, NOTEQUALTest06);
    tcase_add_test(DecimalTest, NOTEQUALTest07);
    tcase_add_test(DecimalTest, NOTEQUALTest08);
    tcase_add_test(DecimalTest, NOTEQUALTest09);
    tcase_add_test(DecimalTest, NOTEQUALTest10);

    tcase_add_test(DecimalTest, GREATEQTest01);
    tcase_add_test(DecimalTest, GREATEQTest02);
    tcase_add_test(DecimalTest, GREATEQTest03);
    tcase_add_test(DecimalTest, GREATEQTest04);
    tcase_add_test(DecimalTest, GREATEQTest05);

    tcase_add_test(DecimalTest, LESSEQTest01);
    tcase_add_test(DecimalTest, LESSEQTest02);
    tcase_add_test(DecimalTest, LESSEQTest03);
    tcase_add_test(DecimalTest, LESSEQTest04);
    tcase_add_test(DecimalTest, LESSEQTest05);

    tcase_add_test(DecimalTest, CONVERT_FROM_INT_Test01);
    tcase_add_test(DecimalTest, CONVERT_FROM_INT_Test02);
    tcase_add_test(DecimalTest, CONVERT_FROM_INT_Test03);
    tcase_add_test(DecimalTest, CONVERT_FROM_INT_Test04);
    tcase_add_test(DecimalTest, CONVERT_FROM_INT_Test05);

    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test01);
    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test02);
    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test03);
    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test04);
    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test05);
    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test06);
    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test07);
    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test08);
    tcase_add_test(DecimalTest, CONVERT_TO_INT_Test09);

    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test01);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test02);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test03);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test04);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test05);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test06);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test07);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test08);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test09);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test10);
    tcase_add_test(DecimalTest, CONVERT_FROM_FLOAT_Test11);

    tcase_add_test(DecimalTest, CONVERT_TO_FLOAT_Test01);
    tcase_add_test(DecimalTest, CONVERT_TO_FLOAT_Test02);
    tcase_add_test(DecimalTest, CONVERT_TO_FLOAT_Test03);
    tcase_add_test(DecimalTest, CONVERT_TO_FLOAT_Test04);
    tcase_add_test(DecimalTest, CONVERT_TO_FLOAT_Test05);
    tcase_add_test(DecimalTest, CONVERT_TO_FLOAT_Test06);
    tcase_add_test(DecimalTest, CONVERT_TO_FLOAT_Test07);
    tcase_add_test(DecimalTest, CONVERT_TO_FLOAT_Test08);

    tcase_add_test(DecimalTest, FLOORTest01);
    tcase_add_test(DecimalTest, FLOORTest02);
    tcase_add_test(DecimalTest, FLOORTest03);
    tcase_add_test(DecimalTest, FLOORTest04);
    tcase_add_test(DecimalTest, FLOORTest05);
    tcase_add_test(DecimalTest, FLOORTest06);
    tcase_add_test(DecimalTest, FLOORTest07);
    tcase_add_test(DecimalTest, FLOORTest08);

    tcase_add_test(DecimalTest, ROUNDTest01);
    tcase_add_test(DecimalTest, ROUNDTest02);
    tcase_add_test(DecimalTest, ROUNDTest03);
    tcase_add_test(DecimalTest, ROUNDTest04);
    tcase_add_test(DecimalTest, ROUNDTest05);
    tcase_add_test(DecimalTest, ROUNDTest06);
    tcase_add_test(DecimalTest, ROUNDTest07);

    tcase_add_test(DecimalTest, TRUNCATETest01);
    tcase_add_test(DecimalTest, TRUNCATETest02);
    tcase_add_test(DecimalTest, TRUNCATETest03);
    tcase_add_test(DecimalTest, TRUNCATETest04);
    tcase_add_test(DecimalTest, TRUNCATETest05);
    tcase_add_test(DecimalTest, TRUNCATETest06);
    tcase_add_test(DecimalTest, TRUNCATETest07);
    tcase_add_test(DecimalTest, TRUNCATETest08);

    tcase_add_test(DecimalTest, NEGATETest01);
    tcase_add_test(DecimalTest, NEGATETest02);
    tcase_add_test(DecimalTest, NEGATETest03);
    tcase_add_test(DecimalTest, NEGATETest04);
    tcase_add_test(DecimalTest, NEGATETest05);

    return my_suite;
}

int main() {
    int number_failed;
    Suite *my_suite;
    SRunner *sr;
    my_suite = my_suite_create();
    sr = srunner_create(my_suite);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}