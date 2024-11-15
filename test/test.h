#define TEST_IF(buff, ...) if((buff) = (__VA_ARGS__))
#define TEST_VAL(buff, ...) TEST_IF(buff, __VA_ARGS__) return (buff);
#define TEST(fun, buff) if((buff) = ((fun)())) return (buff);

#include <ae2f/Call.h>
#include <ae2f/Cast.h>

ae2f_extern int AllocTest();
ae2f_extern int xAllocTest();
ae2f_extern int ArrTest();
ae2f_extern int xArrTest();