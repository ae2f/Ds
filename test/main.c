#include "test.h"

int main() {
    int a = 0;
    TEST(AllocTest, a);
    TEST(xAllocTest, a);

    TEST(ArrTest, a);
    TEST(xArrTest, a);
    
    return a;
}