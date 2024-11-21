#if !defined(ae2f_ds_Alloc_hpp)
#define ae2f_ds_Alloc_hpp

#include <ae2f/Pack/Beg.h>

#include "./Alloc.h"

namespace ae2f { namespace Ds { namespace Alloc {
	struct xrOwner;

	/// @brief 
	/// @tparam __imp 
	/// @see ae2f::Ds::Alloc::iOwner
	template<const ae2f_vDsAlloc* __imp>
	struct vfDef {
		static constexpr ae2f_vDsAlloc* ___vRef() noexcept { return __imp; }
	};
}}}

#pragma region Def
namespace ae2f { namespace Ds { namespace Alloc {
    /// @brief Structure for virtual function pointer.
    /// @see ae2f_vDsAlloc
    using vf = ae2f_vDsAlloc;

    /// @brief
    /// # This structure does not own the memory.
    /// 
    /// An interface to implement the linear array.
    /// @see ae2f_cDsAlloc
    /// @see ae2f_cDsAllocRef
    using rRefer = ae2f_cDsAllocRef;

    /// @brief
    /// # This structure owns the memory.
    /// 
    /// An interface to implement the linear array.
    /// @see ae2f_cDsAlloc
    /// @see ae2f_cDsAllocOwn
    using rOwner = ae2f_cDsAllocOwn;
}}}
#pragma endregion

#pragma region Ref
namespace ae2f { namespace Ds { namespace Alloc {

    /// @brief
    /// # This structure does not own the memory.
    /// 
    /// An interface to implement the linear array.
    /// @see ae2f_cDsAlloc
    /// @see ae2f_cDsAllocRef
    /// @see ae2f::Ds::Alloc::rRefer
    struct cRefer : public rRefer {
        public:

        /// @brief
        /// Gets data from a class.
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
        inline ae2f_err_t Read(size_t idx, void* buff, size_t elsize) const noexcept {
            return ae2f_cDsAllocRefGets(this, idx, buff, elsize);
        }

        /// @brief
        /// Sets data to a class.
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
        inline ae2f_err_t Write(size_t idx, const void* src, size_t srcsize) noexcept {
            return ae2f_cDsAllocRefPuts(this, idx, src, srcsize);
        }

        /// @brief
        /// Gets the length, and element size of the class.
        /// @param sizebuff A pointer where the count of the array, as an unit of elements.
        /// @param elsizebuff A pointer where the size of the element.
        /// @return 
        /// @ref ae2f_errGlob_OK \n
        /// @ref ae2f_errDsAlloc_NCOPIED
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocLen_t
        /// @see ae2f_cDsAllocRefGetSize
        inline ae2f_err_t Length(size_t* sizebuff, size_t* elsizebuff) const noexcept {
            return ae2f_cDsAllocRefGetSize(this, sizebuff, elsizebuff);
        }

        /// @brief
        /// Initialises the class for reffering.
        /// @param r {const ae2f_cDsAlloc*}
        /// @returns {const ae2f_cDsAllocRef} This initiated structure.
        /// @warning
        /// You need to suggest that returning value of this does not own the memory.
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_cDsAllocRefMk
        constexpr cRefer(const rRefer& r) noexcept : rRefer(ae2f_cDsAllocRefMk(&r)) {}

        /// @brief
        /// Initialises the class for reffering.
        /// @param r {const ae2f_cDsAlloc*}
        /// @returns {const ae2f_cDsAllocRef} This initiated structure.
        /// @warning
        /// You need to suggest that returning value of this does not own the memory.
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_cDsAllocRefMk
        constexpr cRefer(const rRefer&& r) noexcept : rRefer(ae2f_cDsAllocRefMk(&r)) {}

        /// @brief
        /// Initialises the class for reffering.
        /// @param r {const ae2f_cDsAlloc*}
        /// @returns {const ae2f_cDsAllocRef} This initiated structure.
        /// @warning
        /// You need to suggest that returning value of this does not own the memory.
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_cDsAllocRefMk
        constexpr cRefer(const xrOwner& r) noexcept;

        /// @warning
        /// Notice that will have no implementation.
        /// @brief 
        /// A constructor for instance of class without any implementations.
        constexpr cRefer() noexcept : rRefer{ 0, 0 } {}
    };
}}}
#pragma endregion

#pragma region Own
namespace ae2f { namespace Ds { namespace Alloc {

    /// @brief
    /// # This structure owns the memory.
    /// 
    /// An interface to implement the linear array.
    /// @see ae2f_cDsAlloc
    /// @see ae2f_cDsAllocOwn
    /// @see ae2f::Ds::Alloc::rOwner
    struct xrOwner : public rOwner {
        public:
        /// @brief
        /// Gets data from a class.
        /// @param i The Index [in an unit of bytes] where the element to copy is.
        /// @param dest A pointer of buffer where the element to be copied.
        /// @param destlen The allocated size of the [dest].
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocGets_t
        /// @see ae2f_cDsAllocRefGets
        /// @see ae2f_cDsAllocOwnGets
        inline ae2f_err_t Read(size_t i, void* dest, size_t destlen) const noexcept {
            return ae2f_cDsAllocOwnGets(this, i, dest, destlen);
        }

        /// @brief
        /// Sets data to a class.
        /// @param i The Index [in an unit of bytes] where the element to be overwritten.
        /// @param src A pointer of an element.
        /// @param srclen An allocated size of the [src].
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocPuts_t
        /// @see ae2f_cDsAllocRefPuts
        /// @see ae2f_cDsAllocOwnPuts
        inline ae2f_err_t Write(size_t i, const void* src, size_t srclen) noexcept {
            return ae2f_cDsAllocOwnPuts(this, i, src, srclen);
        }

        /// @brief
        /// Gets the length, and element size of the class.
        /// @param lenbuff A pointer where the count of the array, as an unit of elements.
        /// @param elsizebuff A pointer where the size of the element.
        /// @return 
        /// @ref ae2f_errGlob_OK \n
        /// @ref ae2f_errDsAlloc_NCOPIED
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocLen_t
        /// @see ae2f_cDsAllocRefGetSize
        /// @see ae2f_cDsAllocOwnGetSize
        inline ae2f_err_t Length(size_t* lenbuff, size_t* elsizebuff) const noexcept {
            return ae2f_cDsAllocOwnGetSize(this, lenbuff, elsizebuff);
        }

        /// @warning
        /// This operation may not be efficient under certain implements.
        /// @brief 
        /// Resizes the memory of [This] as bytes count. \n
        /// Additional memories(newly allocated) must be initiated as 0. \n
        /// Element size will be suggested as 1.
        /// @param bytecount The byte length to resize.
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errGlob_ALLOC_FAILED
        /// @see ae2f_cDsAllocOwn
        /// @see ae2f_fpDsAllocReConfig_t
        /// @see ae2f_cDsAllocOwnReConfig
        /// @see ae2f_cDsAllocOwnReSize
        inline ae2f_err_t Resize(size_t bytecount) noexcept {
            return ae2f_cDsAllocOwnReSize(this, bytecount);
        }

        /// @brief 
        /// Resizes the memory of [This]. \n
        /// Additional memories(newly allocated) must be initiated as 0.
        /// @param elcount The count of the elements.
        /// @param elsize The size of each elements.
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errGlob_ALLOC_FAILED
        /// @see ae2f_cDsAllocOwn
        /// @see ae2f_fpDsAllocReConfig_t
        /// @see ae2f_cDsAllocOwnReConfig
        inline ae2f_err_t ReConfig(size_t elcount, size_t elsize) {
            return ae2f_cDsAllocOwnReConfig(this, elcount, elsize);
        }

        /// @brief 
        /// Frees the memory of class. \n
        /// Error code will be stored in @ref ae2f_errLast.
        /// @param This The instance of a class where the memory to free is located.
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL
        /// @see ae2f_cDsAllocOwn
        /// @see ae2f_fpDsAllocDel_t
        /// @see ae2f_cDsAllocOwnDel
        /// @see ae2f_errLast
        inline ~xrOwner() noexcept {
            ae2f_errLast |= (ae2f_cDsAllocOwnDel(this));
        }

        /// @brief 
        /// Allocates the memory.
        /// Copies the data from [src] to a class.
        /// @param src Source to copy.
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
        /// @see ae2f_cDsAllocOwnCpy
        inline ae2f_err_t Copy(const rRefer& src) noexcept {
            return ae2f_cDsAllocOwnCpy(this, &src);
        }

        /// @brief 
        /// Allocates the memory.
        /// Copies the data from [src] to a class.
        /// @param src Source to copy.
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
        /// @see ae2f_cDsAllocOwnCpy
        inline ae2f_err_t Copy(const rRefer&& src) noexcept {
            return ae2f_cDsAllocOwnCpy(this, &src);
        }

        /// @brief 
        ///	Initialises the pointer. \n
        ///	Injects the function pointers automatically.
        /// @param perr 
        /// An address where state number be stored. \n
        /// Setting it 0 will cause a status number stored in @ref ae2f_errLast.
        /// @param imp
        /// Class Implementations
        /// @return @ref ae2f_errGlob_OK
        /// @exception  \
        /// @ref ae2f_errDsAlloc_FUNPTR_NULL  \n
        /// @ref ae2f_errGlob_PTR_IS_NULL
        /// @see ae2f_cDsAllocOwn
        inline xrOwner(
            ae2f_err_t* perr,
            const ae2f_vDsAlloc* imp
        ) noexcept : rOwner() {
            perr = perr ? perr : &ae2f_errLast;
            *perr |= ae2f_cDsAllocOwnInit(this, imp);
        }
    };

    /// @brief
    /// # This structure owns the memory.
    /// 
    /// An interface to implement the linear array.
    /// @tparam __imp
    /// Function implementations set.
    /// @see ae2f_cDsAlloc
    /// @see ae2f_cDsAllocOwn
    /// @see ae2f::Ds::Alloc::rOwner
    template<const ae2f_vDsAlloc* __imp>
    struct iOwner : public xrOwner, public vfDef<__imp> {
        /// @brief 
        ///	Initialises the pointer. \n
        ///	Injects the function pointers automatically.
        /// @param perr 
        /// An address where state number be stored. \n
        /// Setting it 0 will cause a status number stored in @ref ae2f_errLast.
        /// @param imp
        /// Class Implementations
        /// @return @ref ae2f_errGlob_OK
        /// @exception  \
        /// @ref ae2f_errDsAlloc_FUNPTR_NULL  \n
        /// @ref ae2f_errGlob_PTR_IS_NULL
        /// @see ae2f_cDsAllocOwn
        /// @see ae2f::Ds::Alloc::xrOwner::xrOwner
        inline iOwner(
            ae2f_err_t* perr = 0
        ) noexcept : xrOwner(perr, __imp) {}
    };
}}}
#pragma endregion

namespace ae2f { namespace Ds { namespace Alloc {

	constexpr cRefer::cRefer(const xrOwner& r) noexcept : cRefer(ae2f_cDsAllocRefMk(&r)) {}

	/// @brief 
	/// Pre-defined implementations of @ref ae2f::Ds::Alloc::iOwner
	namespace cOwner {
		/// @brief
		/// Each elements will be physically linear.
		/// @see ae2f::Ds::Alloc::iOwner
		/// @see ae2f_vDsAllocLinear_imp
		using Linear_t = iOwner<&ae2f_vDsAllocLinear_imp>;
	}
}}}

#include <ae2f/Pack/End.h>

#endif