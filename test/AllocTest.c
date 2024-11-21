// fully regress
// 다른 프로세스를 fully regress(아예 회귀)하고 싶음

// scrafolding

#include <ae2f/Ds/Alloc.h>
#include "./test.h"

 
#pragma region Test Alloc
// resize / getsize / init / del
static int Test0x0() {
    int code = 0;
    struct ae2f_cDsAllocOwn a;
    size_t sizeBuff;

    TEST_VAL(code, ae2f_cDsAllocOwnInitAuto(&a));
    TEST_VAL(code, ae2f_cDsAllocOwnReSize(&a, 34));

    TEST_IF(code, ae2f_cDsAllocOwnGetSize(&a, &sizeBuff, 0) & ~ae2f_errDsAlloc_NCOPIED)
    goto __END;

    if(sizeBuff != 34) {
        code = ae2f_errGlob_NFOUND;
        goto __END;
    }

    __END:
    ae2f_cDsAllocOwnDel(&a);
    return code;
}

// read / write
static int Test0x1() {
    int code = 0; int data = 45;
    struct ae2f_cDsAllocOwn a;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_cDsAllocOwnInitAuto(&a));
    TEST_VAL(code, ae2f_cDsAllocOwnReSize(&a, sizeof(int)));
    TEST_IF(code, ae2f_cDsAllocOwnPuts(&a, 0, &data, sizeof(int)))
        goto END;

    data = 3;
    TEST_IF(code, ae2f_cDsAllocOwnGets(&a, 0, &data, sizeof(int)))
        goto END;

    if(data != 45) {
        code = ae2f_errGlob_NFOUND;
        goto END;
    }

    END:
    ae2f_cDsAllocOwnDel(&a);
    return code;
}

// if it works on ref
static int Test0x2() {
    int code = 0; int data = 45;
    struct ae2f_cDsAllocOwn a;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_cDsAllocOwnInitAuto(&a));
    TEST_VAL(code, ae2f_cDsAllocOwnReSize(&a, sizeof(int)));
    TEST_IF(code, ae2f_cDsAllocOwnPuts(&a, 0, &data, sizeof(int))) {
        goto END;
    }
    data = 3;

    struct ae2f_cDsAlloc b = ae2f_cDsAllocRefMk(&a);
    TEST_IF(code, ae2f_cDsAllocRefGets(&b, 0, &data, sizeof(int))) {
        goto END;
    }

    if(data != 45) {
        goto END;
    }
    
    END:
    ae2f_cDsAllocOwnDel(&a);
    return code;
}

// test copy
static int Test0x3() {
    int code = 0; int data = 45;
    struct ae2f_cDsAllocOwn a, b;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_cDsAllocOwnInitAuto(&a));
    TEST_VAL(code, ae2f_cDsAllocOwnInitAuto(&b));

    TEST_VAL(code, ae2f_cDsAllocOwnReSize(&a, sizeof(int)));

    TEST_IF(code, ae2f_cDsAllocOwnPuts(&a, 0, &data, sizeof(int)))
    goto __KILL_A_ONLY;

    data = 3;

    TEST_IF(code, ae2f_cDsAllocOwnCpy(&b, &a))
    goto __KILL_ALL;

    TEST_IF(code, ae2f_cDsAllocOwnGets(&b, 0, &data, sizeof(int)))
    goto __KILL_ALL;

    if(data != 45) {
        code = ae2f_errGlob_NFOUND;
        goto __KILL_ALL;
    }

    __KILL_ALL:
    ae2f_cDsAllocOwnDel(&b);

    __KILL_A_ONLY:
    ae2f_cDsAllocOwnDel(&a);
    return code;
}

// Error
static int Test0x4() {
    struct ae2f_cDsAllocOwn a;
    if(ae2f_cDsAllocOwnInit(&a, 0))
    return ae2f_errGlob_OK;
    return ae2f_errGlob_NFOUND;
}

#pragma endregion

int AllocTest() {
    int ErrCode;

    TEST(Test0x0, ErrCode);
    TEST(Test0x1, ErrCode);
    TEST(Test0x2, ErrCode);
    TEST(Test0x3, ErrCode);
    TEST(Test0x4, ErrCode);

    return ErrCode;
}