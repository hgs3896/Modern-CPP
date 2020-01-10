#pragma once

#include <iostream>

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define COMPILE(compiled, code) CAT(COMPILE_, compiled) ## (code)
#define COMPILE_true(code) code
#define COMPILE_false(code) 
#define TEST(expr)                                                           \
if(!(expr)) {											                     \
    std::cout << __FILE__ << ", line " << __LINE__ << ": err" << std::endl;  \
    return 0;                                                                \
}