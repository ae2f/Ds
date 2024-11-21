/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.h \n
/// Few definitions may lack.

/// @brief
/// [imp] from ae2f_cDsAllocOwnInit was nullptr.
/// @see 
/// ae2f_cDsAllocOwnInit
/// @return
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_PTR_IS_NULL
#define ae2f_errDsAlloc_FUNPTR_NULL 0b1000010

/// @brief
/// # It is not a critical error.
///
/// One of [buff], [one] was null.
/// Data was not be copied either to [buff] or [one].
/// Operation has done gracefully.
/// @see ae2f_cDsAllocRefGetSize 
/// @return
/// @ref ae2f_errGlob_DONE_HOWEV \n
/// @ref ae2f_errGlob_PTR_IS_NULL
#define ae2f_errDsAlloc_NCOPIED 0b1000010

/// @brief
/// The index was not valid.
/// @return
/// @ref ae2f_errGlob_WRONG_OPERATION
#define ae2f_errDsAlloc_BAD_IDX ae2f_errGlob_WRONG_OPERATION