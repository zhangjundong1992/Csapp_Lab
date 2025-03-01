/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 * zjd
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    // 否定和合取构成了完备集
    int var1 = x & y;
    int var2 = (~x) & (~y);
    int var3 = (~var1) & (~var2);
    return var3;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    //直接移位得到
    return 1 << 31;
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    // x=Tmax和-1时，经过+1和取反操作后等于本身，此时var2==1;其他情况，var2==0
    int var1 = ~(x + 1);
    int var2 = !(var1 ^ x);

    //排除-1的情况，x==-1时，var3==0；其他情况时，var3==1
    int var3 = !!(x + 1);

    return var2 & var3;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    int var1 = 0x55;                    //二进制01010101b
    int var2 = (x | var1) << 24 >> 24;  //奇数位全1的话得到结果0xffffffff
    int var3 = ((x >> 8) | var1) << 24 >> 24;
    int var4 = ((x >> 16) | var1) << 24 >> 24;
    int var5 = ((x >> 24) | var1) << 24 >> 24;

    return !(~var2 | ~var3 | ~var4 | ~var5);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    //按位取反+1
    return ~x + 1;
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    // x-0x30、x-0x39之后取移位，如果为正则结果为0；为负则为0xffffffff
    int var1 = (x + (~0x30 + 1)) >> 31;
    int var2 = (x + (~0x3a + 1)) >> 31;
    return !var1 & !!var2;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int var1 = ~(!x << 31 >> 31);  // x!=0时，var1==0xffffffff;x==0时，var1==0
    return (y & var1) + (z & ~var1);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //符号判断，同号为1，异号为0
    int var1 = !((x >> 31) ^ (y >> 31));

    //异号且x为负，y为正时满足
    int var2 = (!!(x >> 31)) & (!(y >> 31));

    //同号且x<=y满足
    int var3 = !((y + ~x + 1) >> 31);

    return (!var1 & var2) | (var1 & var3);
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
    //对x的所有位进行或操作，x==0则结果为0；x！=0则结果为1，保存到最低位。
    int var1 = x | (x >> 8) | (x >> 16) | (x >> 24);
    int var2 = var1 | (var1 >> 2) | (var1 >> 4) | (var1 >> 6);
    int var3 = var2 | var2 >> 1;

    return ~var3 & 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    /* 核心思想为从高位开始找第一个与符号位不同的值 */

    // x为正，则不改变x;x为负，则取反码。其结果将x符号位（包括扩展的）置0
    x = x ^ (x >> 31);

    int b16 = !!(x >> 16) << 4;
    x = x >> b16;

    int b8 = !!(x >> 8) << 3;
    x = x >> b8;

    int b4 = !!(x >> 4) << 2;
    x = x >> b4;

    int b2 = !!(x >> 2) << 1;
    x = x >> b2;

    int b1 = !!(x >> 1);
    x = x >> b1;

    int b0 = x;

    return b16 + b8 + b4 + b2 + b1 + b0 + 1; /* 加1表示符号位 */
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    //取阶码值
    unsigned int exp = (uf << 1 >> 24) & 0xff;

    //阶码全0的情况，直接按照无符号数运算规则计算2f,再加上符号位，等价于浮点数2f
    if (exp == 0u) {
        return (uf << 1) + (uf >> 31 << 31);
    }

    //阶码全1的情况,直接返回参数本身.如果uf=无穷，返回无穷;如果uf=NaN，返回NaN
    if (exp == 0xffu) {
        return uf;
    }

    //阶码为11111110b时,2f结果为无穷
    if (exp >= 0xfeu) {
        return (0xff << 23) + (uf >> 31 << 31);
    }

    //其他情况，只需将阶码+1即可
    return uf + (1 << 23);
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    //取阶码值
    int exp = (uf << 1 >> 24) & 0xff;

    //浮点数值越界，返回最小值(exp=158，E=158-127=31)
    //-2^31不越界，但是刚好返回原本的补码值0x80000000u
    if (exp - 127 >= 31) {
        return 0x80000000u;
    }

    //小于1的数值直接返回0
    if (exp - 127 < 0) {
        return 0;
    }

    //构造出尾数（视为已经左移23位之后的值）
    int M = ((uf & 0x7fffff) + 0x800000);
    if (exp - 127 >= 23) {
        M = M << ((exp - 127) - 23);
    } else {
        M = M >> (23 - (exp - 127));
    }

    //判断符号位,如果时负值，则取-M
    if (uf >= 0x80000000u) {
        M = ~M + 1;
    }

    return M;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    //下溢,-126+-23=-149
    if (x < -149) {
        return 0;
    }

    //非规格化表示
    if (x >= -149 && x < -126) {
        return 1 << (x + 149);
    }

    //规格化表示
    if (x >= -126 && x <= 127) {
        return (x + 127) << 23;
    }

    //上溢
    if (x > 127) {
        return 0xff << 23;
    }
}
