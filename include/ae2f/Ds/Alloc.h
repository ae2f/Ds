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

#include "Alloc/Ref.h"
#include "Alloc/Own.h"

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
#define _ae2f_ds_Alloc_FndFun(This, Name) ae2f_CmpGetMem(ae2f_CmpGetMem(This, v, 0), Name, 0)

/// @warning
/// Notice that it can't handle the function without parameters. \n
/// For certain functions, use @ref _ae2f_DsAllocCallVoid.
/// @brief
/// @param This {const ae2f_cDsAlloc*} Structure
/// @param Name {Member Name} Function Name
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_cDsAlloc
/// @see _ae2f_ds_Alloc_FndFun
#define _ae2f_DsAllocCall(This, Name, ...) (_ae2f_ds_Alloc_FndFun(This, Name) ? _ae2f_ds_Alloc_FndFun(This, Name)(This, __VA_ARGS__) : ae2f_errGlob_IMP_NOT_FOUND)

/// @warning
/// Notice that it can't handle the function with parameters. \n
/// For certain functions, use @ref _ae2f_DsAllocCall.
/// @param This {const ae2f_cDsAlloc*} Structure
/// @param Name {Member Name} Function Name
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_cDsAlloc
/// @see _ae2f_ds_Alloc_FndFun
#define _ae2f_DsAllocCallVoid(This, Name) (_ae2f_ds_Alloc_FndFun(This, Name) ? _ae2f_ds_Alloc_FndFun(This, Name)(This) : ae2f_errGlob_IMP_NOT_FOUND)

#include <ae2f/Pack/End.h>

#endif