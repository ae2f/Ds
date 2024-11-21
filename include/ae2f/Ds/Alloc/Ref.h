/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.h \n
/// Few definitions may lack.

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
/// @ref ae2f_ds_Alloc_Err_NCOPIED
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
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
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
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
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
/// @ref ae2f_ds_Alloc_Err_NCOPIED
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
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
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
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
/// @see ae2f_cDsAllocRef
/// @see ae2f_fpDsAllocPuts_t
#define ae2f_cDsAllocRefPuts(This, idx, src, srcsize) _ae2f_DsAllocCall(This, Write, idx, src, srcsize)

#pragma endregion