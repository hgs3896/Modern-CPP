#pragma once
#define true 1
#define false 0
#define IIF(cond) CAT(IIF_, cond)
#define IIF_0(t, f) f
#define IIF_1(t, f) t
#define A() 1

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define COMPL(b) CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BITAND(x) CAT(BITAND_, x)
#define BITAND_0(y) 0
#define BITAND_1(y) y

#define INC(x) PRIMITIVE_CAT(INC_, x)
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 9

#define DEC(x) PRIMITIVE_CAT(DEC_, x)
#define DEC_0 0
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8

/* Detection */
/* Detection techniques can be used to detect
 * if the parameter is a certain value or if it is parenthesis.
 * It relies on vardiac arguments expanding to different number of parameters.
 * At the core of detection is a CHECK macro with a PROBE macro like this */
#define CHECK_N(x, n, ...) n
// CHECK(xxx) -> CHECK_N(xxx, 0,) -> 0
// CHECK(PROBE(~)) -> CHECK(~, 1,) -> CHECK_N(~, 1, 0,) -> 1
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

// IS_PAREN(()) -> CHECK(IS_PAREN_PROBE ()) -> CHECK(PROBE(~)) -> ... -> 1
// IS_PAREN(xxx) -> CHECK(IS_PAREN_PROBE xxx) -> CHECK_N(IS_PAREN_PROBE xxx, 0,) -> 0
#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)
#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))