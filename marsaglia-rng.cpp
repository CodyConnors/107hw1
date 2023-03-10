
#include <stdio.h>
#include <inttypes.h>

#define MWC_UPPER (mwc_upper=36969*(mwc_upper&65535)+(mwc_upper>>16))
#define MWC_LOWER (mwc_lower=18000*(mwc_lower&65535)+(mwc_lower>>16))
#define MWC ((MWC_UPPER<<16)+MWC_LOWER )
#define SHR3 (shr3^=(shr3<<13), shr3^=(shr3>>17), shr3^=(shr3<<5))
#define CONG (cong=69069u*cong+12345u)
#define FIB ((fib_b=fib_a+fib_b),(fib_a=fib_b-fib_a))
#define KISS ((MWC^CONG)+SHR3)
#define LFIB4 (c++,t[c]=t[c]+t[(uint8_t)(c+58)]+t[(uint8_t)(c+119)]+t[(uint8_t)(c+178)])
#define SWB (c++,swb_bro=(swb_x<swb_y),t[c]=(swb_x=t[(uint8_t)(c+34)])-(swb_y=t[(uint8_t)(c+19)]+swb_bro))

#define MWC64 (mwc64 = UINT64_C(698769069) * (uint32_t)mwc64 + (mwc64 >> 32u), (uint32_t)mwc64)
#define MWC64_SEED(SEED_C, SEED_Z) ((((uint64_t)(SEED_C)) << 32u) | (SEED_Z))
#define KISS2 (MWC64 + CONG + SHR3)

#define UNI (KISS*2.328306e-10)
#define VNI (((long) KISS)*4.656613e-10)

/* Global static variables: */
/* Use random seeds to reset mwc_upper,mwc_lower,shr3,cong,fib_a,fib_b, and the table t[256]*/
static uint32_t mwc_upper = 362436069, mwc_lower = 521288629;
static uint32_t shr3 = 362436000;
static uint32_t cong = 380116160;
static uint32_t fib_a = 224466889, fib_b = 7584631;
static uint32_t t[256];

static uint32_t swb_bro = 0;
static uint8_t c = 0;

static uint64_t mwc64 = MWC64_SEED(7654321, 521288629);

uint32_t swb_x = 0, swb_y = 0;

/* Example procedure to set the table, using KISS: */
void settable(uint32_t i1, uint32_t i2, uint32_t i3, uint32_t i4, uint32_t i5, uint32_t i6)
{
    mwc_upper = i1;
    mwc_lower = i2;
    shr3 = i3;
    cong = i4;
    fib_a = i5;
    fib_b = i6;
}

void init_t(void)
{
    unsigned int    i;

    for (i = 0; i < 256; i++)
    {
        t[i] = KISS;
    }
}

uint32_t MWC64func(void)
{
  static uint32_t z = 521288629;
  static uint32_t c = 7654321;
  uint64_t t;
  uint64_t a = UINT64_C(698769069);

  t = a * z + c;
  c = t >> 32;
  z = t;

  return z;
}

uint32_t KISS2func(void)
{
  static uint64_t mwc64 = MWC64_SEED(7654321, 521288629);
  static uint32_t cong = 123456789;
  static uint32_t shr3 = 362436000;

  return KISS2;
}

/*-----------------------------------------------------
Write your own calling program and try one or more of
the above, singly or in combination, when you run a
simulation. You may want to change the simple 1-letter
names, to avoid conflict with your own choices. */

/* All that follows is comment, mostly from the initial
   post. You may want to remove it */

/* Any one of KISS, MWC, FIB, LFIB4, SWB, SHR3, or CONG
   can be used in an expression to provide a random 32-bit
   integer.


   The KISS generator, (Keep It Simple Stupid), is
   designed to combine the two multiply-with-carry
   generators in MWC with the 3-shift register SHR3 and
   the congruential generator CONG, using addition and
   exclusive-or. Period about 2^123.
   It is one of my favorite generators.


   The MWC generator concatenates two 16-bit multiply-
   with-carry generators, x(n)=36969x(n-1)+carry,
   y(n)=18000y(n-1)+carry mod 2^16, has period about
   2^60 and seems to pass all tests of randomness. A
   favorite stand-alone generator---faster than KISS,
   which contains it.


   FIB is the classical Fibonacci sequence
   x(n)=x(n-1)+x(n-2),but taken modulo 2^32.
   Its period is 3*2^31 if one of its two seeds is odd
   and not 1 mod 8. It has little worth as a RNG by
   itself, but provides a simple and fast component for
   use in combination generators.


   SHR3 is a 3-shift-register generator with period
   2^32-1. It uses y(n)=y(n-1)(I+L^17)(I+R^13)(I+L^5),
   with the y's viewed as binary vectors, L the 32x32
   binary matrix that shifts a vector left 1, and R its
   transpose. SHR3 seems to pass all except those
   related to the binary rank test, since 32 successive
   values, as binary vectors, must be linearly
   independent, while 32 successive truly random 32-bit
   integers, viewed as binary vectors, will be linearly
   independent only about 29% of the time.


   CONG is a congruential generator with the widely used 69069
   multiplier: x(n)=69069x(n-1)+1234567. It has period
   2^32. The leading half of its 32 bits seem to pass
   tests, but bits in the last half are too regular.


   LFIB4 is an extension of what I have previously
   defined as a lagged Fibonacci generator:
   x(n)=x(n-r) op x(n-s), with the x's in a finite
   set over which there is a binary operation op, such
   as +,- on integers mod 2^32, * on odd such integers,
   exclusive-or(xor) on binary vectors. Except for
   those using multiplication, lagged Fibonacci
   generators fail various tests of randomness, unless
   the lags are very long. (See SWB below).
   To see if more than two lags would serve to overcome
   the problems of 2-lag generators using +,- or xor, I
   have developed the 4-lag generator LFIB4 using
   addition: x(n)=x(n-256)+x(n-179)+x(n-119)+x(n-55)
   mod 2^32. Its period is 2^31*(2^256-1), about 2^287,
   and it seems to pass all tests---in particular,
   those of the kind for which 2-lag generators using
   +,-,xor seem to fail. For even more confidence in
   its suitability, LFIB4 can be combined with KISS,
   with a resulting period of about 2^410: just use
   (KISS+LFIB4) in any C expression.


   SWB is a subtract-with-borrow generator that I
   developed to give a simple method for producing
   extremely long periods:
   x(n)=x(n-222)-x(n-237)- borrow mod 2^32.
   The 'borrow' is 0, or set to 1 if computing x(n-1)
   caused overflow in 32-bit integer arithmetic. This
   generator has a very long period, 2^7098(2^480-1),
   about 2^7578. It seems to pass all tests of
   randomness, except for the Birthday Spacings test,
   which it fails badly, as do all lagged Fibonacci
   generators using +,- or xor. I would suggest
   combining SWB with KISS, MWC, SHR3, or CONG.
   KISS+SWB has period >2^7700 and is highly
   recommended.
   Subtract-with-borrow has the same local behaviour
   as lagged Fibonacci using +,-,xor---the borrow
   merely provides a much longer period.
   SWB fails the birthday spacings test, as do all
   lagged Fibonacci and other generators that merely
   combine two previous values by means of =,- or xor.
   Those failures are for a particular case: m=512
   birthdays in a year of n=2^24 days. There are
   choices of m and n for which lags >1000 will also
   fail the test. A reasonable precaution is to always
   combine a 2-lag Fibonacci or SWB generator with
   another kind of generator, unless the generator uses
   *, for which a very satisfactory sequence of odd
   32-bit integers results.


   The classical Fibonacci sequence mod 2^32 from FIB
   fails several tests. It is not suitable for use by
   itself, but is quite suitable for combining with
   other generators.


   The last half of the bits of CONG are too regular,
   and it fails tests for which those bits play a
   significant role. CONG+FIB will also have too much
   regularity in trailing bits, as each does. But keep
   in mind that it is a rare application for which
   the trailing bits play a significant role. CONG
   is one of the most widely used generators of the
   last 30 years, as it was the system generator for
   VAX and was incorporated in several popular
   software packages, all seemingly without complaint.


   Finally, because many simulations call for uniform
   random variables in 0<x<1 or -1<x<1, I use #define
   statements that permit inclusion of such variates
   directly in expressions: using UNI will provide a
   uniform random real (float) in (0,1), while VNI will
   provide one in (-1,1).


   All of these: MWC, SHR3, CONG, KISS, LFIB4, SWB, FIB
   UNI and VNI, permit direct insertion of the desired
   random quantity into an expression, avoiding the
   time and space costs of a function call. I call
   these in-line-define functions. To use them, static
   variables mwc_upper,mwc_lower,shr3,cong,fib_a and
   fib_b should be assigned seed values other than their
   initial values. If LFIB4 or SWB are used, the static
   table t[256] must be initialized.


   A note on timing: It is difficult to provide exact
   time costs for inclusion of one of these in-line-
   define functions in an expression. Times may differ
   widely for different compilers, as the C operations
   may be deeply nested and tricky. I suggest these
   rough comparisons, based on averaging ten runs of a
   routine that is essentially a long loop:
   for(i=1;i<10000000;i++) L=KISS; then with KISS
   replaced with SHR3, CONG,... or KISS+SWB, etc. The
   times on my home PC, a Pentium 300MHz, in nanoseconds:
   FIB 49;LFIB4 77;SWB 80;CONG 80;SHR3 84;MWC 93;KISS 157;
   VNI 417;UNI 450;
*/

