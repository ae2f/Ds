#if !defined(ae2f_ds_Arr_h)
#define ae2f_ds_Arr_h

#include <ae2f/Pack/Beg.h>

#include "Alloc.h"
#include "Arr/Err.h"

/// @brief 
/// Finds the element [wanted] via binary search.
/// @param arr 
/// Array to see.
/// It must be sorted.
/// @param wanted 
/// The element which is wanted
/// @param fpElCmp 
/// comparing will be proceed as
/// ```c
/// fpElCmp(element, wanted);
/// ```
/// @param out 
/// Buffer where the Index may be stored
/// @param elsize
/// Suggested each element's size.
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_ds_Arr_NOT_FOUND 
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_ALLOC_FAILED \n 
/// @see ae2f_cDsAllocRefGetSize
/// @see ae2f_cDsAllocRefGets
ae2f_SHAREDCALL ae2f_extern ae2f_err_t ae2f_cDsArrBSearch_imp(
	const ae2f_struct ae2f_cDsAlloc* arr,
	const void* wanted,
	const ae2f_fpCmp_t fpElCmp,
	size_t* out,
	size_t elsize
) noexcept;

/// @brief 
/// Finds the element [wanted] via binary search.
/// @param arr 
/// Array to see.
/// It must be sorted.
/// @param wanted 
/// The element which is wanted
/// @param fpElCmp 
/// Comparing function.
/// comparing will be proceed as
/// ```c
/// fpElCmp(element, wanted);
/// ```
/// @param retidx
/// Buffer where the Index may be stored
/// @param elw
/// Suggested each element's size.
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_ds_Arr_NOT_FOUND 
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_ALLOC_FAILED \n
/// @ref ae2f_errGlob_WRONG_OPERATION 
/// @see ae2f_cDsAllocRefGetSize
/// @see ae2f_cDsAllocRefGets
/// @see ae2f_cDsArrBSearch_imp
#define ae2f_cDsArrBSearch(arr, wanted, fpElCmp, retidx, elw) ae2f_cDsArrBSearch_imp(arr, wanted, ae2f_reinterpret_cast(ae2f_fpCmp_t, fpElCmp), retidx, elw)

/// @brief 
/// Order the arr via quick sort.
/// @param arr 
/// An array to sort
/// @param fpElCmp 
/// comparing will be proceed as
/// ```c
/// fpElCmp(element, wanted);
/// ```
/// @param elsize
/// Suggested each element's size.
/// @return
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_ALLOC_FAILED \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_cDsAllocRefGetSize
/// @see ae2f_cDsAllocRefGets
/// @see ae2f_cDsAllocRefPuts
ae2f_SHAREDCALL ae2f_extern ae2f_err_t ae2f_cDsArrQSort_imp(
	ae2f_struct ae2f_cDsAlloc* arr,
	const ae2f_fpCmp_t fpElCmp,
	size_t elsize
) noexcept;

/// @brief 
/// Order the arr via quick sort.
/// @param arr 
/// An array to sort
/// @param fpElCmp 
/// comparing will be proceed as
/// ```c
/// fpElCmp(element, wanted);
/// ```
/// @param elw
/// Suggested each element's size.
/// @return
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_ALLOC_FAILED \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_cDsAllocRefGetSize
/// @see ae2f_cDsAllocRefGets
/// @see ae2f_cDsAllocRefPuts
/// @see ae2f_cDsArrQSort_imp
#define ae2f_cDsArrQSort(arr, fpElCmp, elw) ae2f_cDsArrQSort_imp(arr, ae2f_reinterpret_cast(ae2f_fpCmp_t, fpElCmp), elw)

#include <ae2f/Pack/End.h>

#endif
