/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.h \n
/// Few definitions may lack.

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
/// @ref ae2f_ds_Alloc_Err_FPIMPNULL  \n
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_cDsAllocOwn
ae2f_SHAREDCALL ae2f_extern ae2f_err_t ae2f_cDsAllocOwn_Init(
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
/// @see ae2f_cDsAllocOwn_Init
#define ae2f_cDsAllocOwn_InitAuto(This) ae2f_cDsAllocOwn_Init(This, &ae2f_vDsAllocLinear_imp)

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
/// @ref ae2f_ds_Alloc_Err_NCOPIED
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
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
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
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
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