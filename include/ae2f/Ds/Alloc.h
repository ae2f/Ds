#if !defined(ae2f_ds_Alloc_h)
#define ae2f_ds_Alloc_h

#include <ae2f/Pack/Beg.h>

#include <ae2f/Cast.h>
#include <ae2f/Cmp.h>
#include <ae2f/err.h>
#include <ae2f/Call.h>

#include "Alloc/Err.h"
 
struct ae2f_vDsAlloc;
struct ae2f_cDsAlloc;

#pragma region Ref

/// @brief
/// # This structure does not own the memory.
/// 
/// An interface to implement the linear array.
/// @see ae2f_cDsAlloc
#define ae2f_cDsAllocRef ae2f_cDsAlloc

#pragma region functions pointers

/// @brief
/// Gets the length, and element size of the class.
/// @param _this The constant instance of the class.
/// @param pSize A pointer where the count of the array, as an unit of elements.
/// @param pel A pointer where the size of the element.
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_errDsAlloc_NCOPIED
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @see ae2f_cDsAllocRef
typedef ae2f_err_t(*ae2f_fpDsAllocLen_t)(
	const ae2f_struct ae2f_cDsAllocRef* _this,
	size_t* pSize,
	size_t* pel
);

/// @brief
/// Gets data from a class.
/// @param _this The constant instance of the class.
/// @param Index The Index [in an unit of bytes] where the element to copy is.
/// @param lpBuff A pointer of buffer where the element to be copied.
/// @param Buff_size The allocated size of the `lpBuff`.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errDsAlloc_BAD_IDX
/// @see ae2f_cDsAllocRef
typedef ae2f_err_t(*ae2f_fpDsAllocGets_t)(
	const ae2f_struct ae2f_cDsAllocRef* _this, 
	size_t Index, 
	void* lpBuff, 
	size_t Buff_size
);

/// @brief
/// Sets data to a class.
/// @param _this The instance of the class.
/// @param Index The Index [in an unit of bytes] where the element to be overwritten.
/// @param lpBuff A pointer of an element.
/// @param Buff_size An allocated size of the `lpBuff`.
/// @return 
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errDsAlloc_BAD_IDX
/// @see ae2f_cDsAllocRef
typedef ae2f_err_t(*ae2f_fpDsAllocPuts_t)(
	ae2f_struct ae2f_cDsAllocRef* _this, 
	size_t Index, 
	const void* lpBuff,
	size_t Buff_size
);

#pragma endregion


/// @brief
/// Initialises the class for reffering.
/// @param This	{const ae2f_cDsAlloc*}
/// @returns {const ae2f_cDsAllocRef} This initiated structure.
/// @warning
/// You need to suggest that returning value of this does not own the memory.
/// @see ae2f_cDsAllocRef
#define ae2f_cDsAllocRefMk(This) ae2f_RecordMk(ae2f_struct ae2f_cDsAllocRef, (This)->data, (This)->v)


#pragma region Methods

/// @brief
/// Gets the length, and element size of the class.
/// @param This The constant instance of the class.
/// @param sizebuff A pointer where the count of the array, as an unit of elements.
/// @param elsizebuff A pointer where the size of the element.
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_errDsAlloc_NCOPIED
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @see ae2f_cDsAllocRef
/// @see ae2f_fpDsAllocLen_t
#define ae2f_cDsAllocRefGetSize(This, sizebuff, elsizebuff) _ae2f_DsAllocCall(This, GetSize, sizebuff, elsizebuff)

/// @brief
/// Gets data from a class.
/// @param This The constant instance of the class.
/// @param idx The Index [in an unit of bytes] where the element to copy is.
/// @param buff A pointer of buffer where the element to be copied.
/// @param elsize The allocated size of the [buff].
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errDsAlloc_BAD_IDX
/// @see ae2f_cDsAllocRef
/// @see ae2f_fpDsAllocGets_t
#define ae2f_cDsAllocRefGets(This, idx, buff, elsize) _ae2f_DsAllocCall(This, Read, idx, buff, elsize)

/// @brief
/// Sets data to a class.
/// @param This The instance of the class.
/// @param idx The Index [in an unit of bytes] where the element to be overwritten.
/// @param src A pointer of an element.
/// @param srcsize An allocated size of the [src].
/// @return 
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errDsAlloc_BAD_IDX
/// @see ae2f_cDsAllocRef
/// @see ae2f_fpDsAllocPuts_t
#define ae2f_cDsAllocRefPuts(This, idx, src, srcsize) _ae2f_DsAllocCall(This, Write, idx, src, srcsize)

#pragma endregion
#pragma endregion
#pragma region Own

/// @brief
/// # This structure owns the memory.
/// @see ae2f_cDsAlloc
#define ae2f_cDsAllocOwn ae2f_cDsAlloc

#pragma region Virtual Functions

/// @brief 
/// Frees the memory of `_this`.
/// @param _this The instance of a class where the memory to free is located.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_cDsAllocOwn
typedef ae2f_err_t(*ae2f_fpDsAllocDel_t)(
    ae2f_struct ae2f_cDsAllocOwn* _this
);

/// @brief 
/// Resizes the memory of `_this`. \n
/// Additional memories(newly allocated) must be initiated as 0.
/// @param _this The owner of the memory.
/// @param elcount The count of the elements.
/// @param elsize The size of each elements.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_cDsAllocOwn
typedef ae2f_err_t(*ae2f_fpDsAllocReConfig_t)(
    ae2f_struct ae2f_cDsAllocOwn* _this, 
    size_t elcount, 
    size_t elsize
);


#pragma endregion


#pragma region inits

/// @brief 
///	Initialises the pointer. \n
///	Injects the function pointers automatically.
/// @param This 
/// Address to be set. \n
/// Do not pass when it is allocated.
/// @param imp
/// Class Implementations
/// @return @ref ae2f_errGlob_OK
/// @exception  \
/// @ref ae2f_errDsAlloc_FUNPTR_NULL  \n
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_cDsAllocOwn
ae2f_SHAREDCALL ae2f_extern ae2f_err_t ae2f_cDsAllocOwnInit(
	ae2f_struct ae2f_cDsAllocOwn* This, 
	const ae2f_struct ae2f_vDsAlloc* imp
);

/// @brief 
///	Initialises the pointer. \n
///	Injects the function pointers automatically.
/// @param This 
/// Address to be set. \n
/// Do not pass when it is allocated.
/// @param imp
/// Class Implementations
/// @return @ref ae2f_errGlob_OK
/// @exception  \
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_cDsAllocOwn
/// @see ae2f_cDsAllocOwnInit
#define ae2f_cDsAllocOwnInitAuto(This) ae2f_cDsAllocOwnInit(This, &ae2f_vDsAllocLinear_imp)

/// @brief 
/// Allocates the memory.
/// Copies the data from [Source] to [This].
/// @param This Points the allocated memory.
/// @param Source Source to copy.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_cDsAllocRefGetSize
/// @see ae2f_cDsAllocRefGets
/// @see ae2f_cDsAllocRefPuts
/// @see ae2f_cDsAllocOwn
/// @see ae2f_cDsAllocOwnReConfig
ae2f_SHAREDCALL ae2f_extern ae2f_err_t ae2f_cDsAllocOwnCpy_imp(
	ae2f_struct ae2f_cDsAllocOwn* This, 
	const ae2f_struct ae2f_cDsAlloc* Source
);

/// @brief 
/// Allocates the memory.
/// Copies the data from [Source] to [This].
/// @param This Points the allocated memory.
/// @param Source Source to copy.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_cDsAllocRefGetSize
/// @see ae2f_cDsAllocRefGets
/// @see ae2f_cDsAllocRefPuts
/// @see ae2f_cDsAllocOwn
/// @see ae2f_cDsAllocOwnReConfig
/// @see ae2f_cDsAllocOwnCpy_imp
#define ae2f_cDsAllocOwnCpy(This, Source) ae2f_cDsAllocOwnCpy_imp(This, ae2f_reinterpret_cast(const ae2f_struct ae2f_cDsAlloc*, Source))

#pragma endregion


#pragma region Methods Call

/// @brief
/// Gets the length, and element size of the class.
/// @param _this The constant instance of the class.
/// @param pSize A pointer where the count of the array, as an unit of elements.
/// @param pel A pointer where the size of the element.
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_errDsAlloc_NCOPIED
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @see ae2f_cDsAllocRef
/// @see ae2f_fpDsAllocLen_t
/// @see ae2f_cDsAllocRefGetSize
#define ae2f_cDsAllocOwnGetSize ae2f_cDsAllocRefGetSize

/// @brief
/// Gets data from a class.
/// @param This The constant instance of the class.
/// @param idx The Index [in an unit of bytes] where the element to copy is.
/// @param buff A pointer of buffer where the element to be copied.
/// @param elsize The allocated size of the [buff].
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errDsAlloc_BAD_IDX
/// @see ae2f_cDsAllocRef
/// @see ae2f_fpDsAllocGets_t
/// @see ae2f_cDsAllocRefGets
#define ae2f_cDsAllocOwnGets ae2f_cDsAllocRefGets

/// @brief
/// Sets data to a class.
/// @param This The instance of the class.
/// @param idx The Index [in an unit of bytes] where the element to be overwritten.
/// @param src A pointer of an element.
/// @param srcsize An allocated size of the [src].
/// @return 
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errDsAlloc_BAD_IDX
/// @see ae2f_cDsAllocRef
/// @see ae2f_fpDsAllocPuts_t
/// @see ae2f_cDsAllocRefPuts
#define ae2f_cDsAllocOwnPuts ae2f_cDsAllocRefPuts

/// @brief 
/// Frees the memory of [This].
/// @param This The instance of a class where the memory to free is located.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_cDsAllocOwn
/// @see ae2f_fpDsAllocDel_t
#define ae2f_cDsAllocOwnDel(This) _ae2f_DsAllocCallVoid(This, Del)

/// @brief 
/// Resizes the memory of [This]. \n
/// Additional memories(newly allocated) must be initiated as 0.
/// @param This The owner of the memory.
/// @param elcount The count of the elements.
/// @param elsize The size of each elements.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_cDsAllocOwn
/// @see ae2f_fpDsAllocReConfig_t
#define ae2f_cDsAllocOwnReConfig(This, elcount, elsize) _ae2f_DsAllocCall(This, ReConfig, elcount, elsize)

/// @warning
/// This operation may not be efficient under certain implements.
/// @brief 
/// Resizes the memory of [This] as bytes count. \n
/// Additional memories(newly allocated) must be initiated as 0. \n
/// Element size will be suggested as 1.
/// @param This The owner of the memory.
/// @param bytecount The byte length to resize.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_cDsAllocOwn
/// @see ae2f_fpDsAllocReConfig_t
/// @see ae2f_cDsAllocOwnReConfig
#define ae2f_cDsAllocOwnReSize(This, bytecount) ae2f_cDsAllocOwnReConfig(This, bytecount, 1)
#pragma endregion
#pragma endregion

#pragma region vOwner

/// @brief Structure for virtual function pointer.
struct ae2f_vDsAlloc {
	const ae2f_fpDsAllocLen_t GetSize;
	const ae2f_fpDsAllocGets_t Read;
	const ae2f_fpDsAllocPuts_t Write;	
	const ae2f_fpDsAllocDel_t Del;
	const ae2f_fpDsAllocReConfig_t ReConfig;
};

/// @brief
/// Each elements will be physically linear.
ae2f_SHAREDCALL ae2f_extern const ae2f_struct ae2f_vDsAlloc ae2f_vDsAllocLinear_imp;

#pragma endregion

/// @brief
/// The data holder for [cRef] and [cOwn].
/// @see
/// ae2f_cDsAllocRef \n
/// ae2f_cDsAllocOwn
struct ae2f_cDsAlloc {
	/// @brief Where data is hold.
	char* data;
	/// @brief The implementations.
	const ae2f_struct ae2f_vDsAlloc* v;
};

/// @param This {const ae2f_cDsAlloc*} Structure
/// The structure suggested to have a function pointer.
/// @param Name {Member Name} The valid member's name.
/// Wanted Function Name.
/// @returns
/// The Function Pointer with the given name.
/// @exception 0: [This] was nullptr.
#define _ae2f_DsAllocFndFunc(This, Name) ae2f_CmpGetMem(ae2f_CmpGetMem(This, v, 0), Name, 0)

/// @warning
/// Notice that it can't handle the function without parameters. \n
/// For certain functions, use @ref _ae2f_DsAllocCallVoid.
/// @brief
/// @param This {const ae2f_cDsAlloc*} Structure
/// @param Name {Member Name} Function Name
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_cDsAlloc
/// @see _ae2f_DsAllocFndFunc
#define _ae2f_DsAllocCall(This, Name, ...) (_ae2f_DsAllocFndFunc(This, Name) ? _ae2f_DsAllocFndFunc(This, Name)(This, __VA_ARGS__) : ae2f_errGlob_IMP_NOT_FOUND)

/// @warning
/// Notice that it can't handle the function with parameters. \n
/// For certain functions, use @ref _ae2f_DsAllocCall.
/// @param This {const ae2f_cDsAlloc*} Structure
/// @param Name {Member Name} Function Name
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_cDsAlloc
/// @see _ae2f_DsAllocFndFunc
#define _ae2f_DsAllocCallVoid(This, Name) (_ae2f_DsAllocFndFunc(This, Name) ? _ae2f_DsAllocFndFunc(This, Name)(This) : ae2f_errGlob_IMP_NOT_FOUND)

#include <ae2f/Pack/End.h>

#endif