/* 
 * CS:APP Data Lab 
 * 
 * <Jorge Contreras ID:205-379-811>
 * 
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
,. */
int bitParity(int x) {
/*
Odd number of 1's means odd numbers of 0's
And XORing removes 1's in multiples of 2 ONLY
A number subtracted by a factor of two will remain odd or even
So I XOR the original number by its other half to reduce the number of relevant bits
Until the relavant bits are stored into only 4 bits, so I can add up the ones using AND 1, and compare the last bit of this addition to 1
If that last bit is 1, then odd. If 0, then even*/
  int relBits;
  relBits = x ^ (x >> 16);
  relBits = relBits ^ (relBits >> 8);
  relBits = relBits ^ (relBits >> 4);
  relBits = (relBits & 0x01) + ((relBits >> 1) & 0x01) + ((relBits >> 2) & 0x01) + ((relBits >> 3) & 0x01);
  return (relBits & 0x01);
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
/*Store the least significant n bits using mask
Right shift x by n bits and zero out those most significant n bits to make space
Left shift the n relevant bits to move by 32 - n to get them in place
Then OR the relevant bits and the modified x
 */
  int relBits;
  relBits = (~(~0x00 << n)) & x;
  x = (x >> n) & ~(((!!n) << 31) >> (n + ~(!!n) + 1));
  relBits = relBits << (0x21 + ~n);
  return x | relBits;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
/*Create a mask that has only the bytes to be swapped filled with 1
Then use ~ operator to create a mask that will zero out those bytes
Store in save first the nth byte, savesecond the mth byte.
After using mask to zero out bytes m and n:
OR result with saveFirst at the mth byte, saveSecond at the nth byte
Effectively switches those bytes
   */
  int toAND;
  int saveFirst;
  int saveSecond;
  n = n << 3;
  m = m << 3;
  toAND = (0xFF << n);
  toAND = toAND | (0xFF << m);
  toAND = ~toAND;
  saveFirst = (x >> n) & 0xFF;
  saveSecond = (x >> m) & 0xFF;
  x = x & toAND;
  x = (x | (saveFirst << m)) | (x | (saveSecond << n)); 
  return x;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
/*For an integer to fit in a short, which is 16 bits, the least significant 15 bits are irrelevant
So I shift them out of the way
The remaining relative bits should be all 1 or all 0, matching the most significant bit
By shifting x fully to the right we get a number full of 1's or zeroes
A negative number that fits the bill will have relBits filled with 1, so XORing with resulting x gives 0
A positive number that fits will have relBits filled with 0, so XORing will also give 0
Using the not operator we switch this result to be true
*/
  int relBits = x >> 15;
  x = x >> 31;
  return !(relBits ^ x);
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/*For each bit pair, & only gives 1 if both are 1, so try to do the opposite then reverse
so use ~ on each, now 1 stands for 0 and vice versa. So if either is (prior 0)1, now give (will become 0)1
Use ~ on result to reverse the reverse and get correct answer
*/
  return ~(~x | ~y);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  /*if x and y share a sign, subtraction is ok. To find this XOR most significant bits
    if x and y are different signs, then if the result of their subtraction is different from x subtraction is NOT ok
   */
  int xSign;
  int isSignDiff;
  xSign = (x >> 31) & 0x01;
  isSignDiff = xSign ^ ((y>>31) & 0x01);
  y = x + ~y + 1;
  y = (y >> 31) & 0x01;
  y = y ^ xSign;
  return (!isSignDiff) | (isSignDiff & (!y));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /*use similar logic to subOK
   */
  int diffSigns;
  int resDiffSigns;
  int xSign;
  int ySign;
  xSign = x >> 31 & 0x01;
  ySign = y >> 31 & 0x01;
  diffSigns = ySign ^ xSign;
  diffSigns = diffSigns & 0x01;
  y = x + ~y;
  resDiffSigns = y >> 31;
  resDiffSigns = resDiffSigns & 0x01;
  return (!diffSigns & !resDiffSigns) | (diffSigns & ySign);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* more general form of fits short
     n-1 least significant bits are never relevant, so shift by that amount.
     then use similar method to fitsShort
   */
  int relBits = x >> (n + ((~0x01) + 1));
  int posneg = x >> 31;
  return !(relBits ^ posneg);
  
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*this was discussed once in lecture
   */
  return ~x+1;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /*Tmax + 1 gives Tmin, and XOR'ing Tmin and Tmax gives full 1's. Uing ~ gives all 0's. To account for the problematic -1
    I have variable NegOne which will only have value of 1 if x is 1. Adding this to x before returning !x give correct result for all inputs
   */
  int y = x + 1;
  int negOne = !(x+1);
  x = x ^ y;
  x = ~x;
  x = x + negOne;
  return !x;
}
