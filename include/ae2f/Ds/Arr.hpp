#include "Arr.h"

// Fork + exec

#if !defined(ae2f_ds_Arr_hpp)
#define ae2f_ds_Arr_hpp

#include <ae2f/Pack/Beg.h>

#include "Alloc.hpp"
#include <type_traits>

#include "Arr/Defs.hpp"
#include "Arr/Pack.hpp"

#pragma region Ref
namespace ae2f { namespace Ds { namespace Arr {

    /// @warning
    /// Using this class directly may cause undefined behaviour. \n
    /// Using the binder instead is recommended.
    /// @brief 
    /// # This structure does not own the memory.
    ///
    /// Suggest the type is trivial. \n
    /// Therefore the element type will be [T] itself.
    /// @tparam T 
    /// Trivial data type
    template<typename T>
    struct __Refer<T, 1>
    :   public Alloc::cRefer,
        public __def<T> 
    {
        using _f = __def<T>;

        /// @brief
        /// Gets data from a class.
        /// @param index
        /// The Index [in an unit of bytes] where the element to copy is.
        /// @param perr
        /// The pointer to store the error state.
        /// @return 
        /// The element of index.
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocGets_t
        /// @see ae2f_cDsAllocRefGets
        /// @see ae2f::Ds::Alloc::cRefer::Read
        inline const typename _f::El_t Read(size_t index, ae2f_err_t* perr = &ae2f_errLast) const noexcept {
            if(!perr) perr = &ae2f_errLast;

            T b[1];

            perr[0] |= Alloc::cRefer::Read(
                index * sizeof(T), 
                ae2f_reinterpret_cast(void*, b), 
                sizeof(T)
            );

            return b[0];
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param el The element to write.
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocPuts_t
        /// @see ae2f_cDsAllocRefPuts
        /// @see ae2f::Ds::Alloc::cRefer::Write
        inline ae2f_err_t Write(size_t idx, const typename _f::El_t& el) noexcept {
            return Alloc::cRefer::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param el The element to write.
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocPuts_t
        /// @see ae2f_cDsAllocRefPuts
        /// @see ae2f::Ds::Alloc::cRefer::Write
        inline ae2f_err_t Write(size_t idx, const typename _f::El_t&& el) noexcept {
            return Alloc::cRefer::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        constexpr __Refer(const Alloc::rRefer& src) 
        : cRefer(src) {}

        constexpr __Refer(const Alloc::rRefer&& src) 
        : cRefer(src) {}
    };

    /// @warning
    /// Using this class directly may cause undefined behaviour. \n
    /// Using the binder instead is recommended.
    /// @brief 
    /// # This structure does not own the memory.
    ///
    /// Suggest the type is no trivial. \n
    /// Therefore the element type will be @ref ae2f::Ds::Arr::Pack<T>, in order to avoid the data destruction under wrong responsibility.
    /// @tparam T 
    /// Non-Trivial data type
    /// @see ae2f::Ds::Arr::Pack<T>
    template<typename T>
    struct __Refer<T, 0>
    :   public Alloc::cRefer,
        public __def<Pack<T>> 
    {
        using _f = __def<Pack<T>>;

        /// @brief
        /// Gets data from a class.
        /// @param index
        /// The Index [in an unit of bytes] where the element to copy is.
        /// @param perr
        /// The pointer to store the error state.
        /// @return 
        /// The element of index.
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocGets_t
        /// @see ae2f_cDsAllocRefGets
        /// @see ae2f::Ds::Alloc::cRefer::Read
        inline const typename _f::El_t Read(size_t index, ae2f_err_t* perr = 0) const noexcept {
            if(!perr) perr = &ae2f_errLast;

            typename _f::El_t b[1];

            perr[0] |= Alloc::cRefer::Read(
                index * _f::ElSize, 
                ae2f_reinterpret_cast(void*, b), 
                _f::ElSize
            );

            if(!b->isvalid())
            perr[0] |= eRef::EL_NON_VALID;

            return b[0];
        }

#pragma region non_trivial writing

        /// @brief
        /// Sets data to a class.
        /// @tparam Args 
        /// Arguments datatype.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param args Arguments to build the element to write.
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX \n
        /// @ref eRef::EL_NON_VALID
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocPuts_t
        /// @see ae2f_cDsAllocRefPuts
        /// @see ae2f::Ds::Alloc::cRefer::Write
        template<typename... Args>
        inline ae2f_err_t Write(size_t idx, Args&& ...args) noexcept {
            if(!_ae2f_DsAllocFndFunc(ae2f_static_cast(Alloc::rRefer*, this), Write)) {
                return ae2f_errGlob_IMP_NOT_FOUND;
            }

            ae2f_err_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[0] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            if(el->isvalid()) {
                el->Obj.~T();
            }
            new(el->c) T(args...);
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocPuts_t
        /// @see ae2f_cDsAllocRefPuts
        /// @see ae2f::Ds::Alloc::cRefer::Write
        inline ae2f_err_t Write(size_t idx) noexcept {
            if(!_ae2f_DsAllocFndFunc(ae2f_static_cast(Alloc::rRefer*, this), Write)) {
                return ae2f_errGlob_IMP_NOT_FOUND;
            }

            ae2f_err_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[0] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            if(el->isvalid()) el->Obj.~T();
            new(el->c) T();
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

#pragma endregion
        constexpr __Refer(const __Refer<T, 0>& src)
        : cRefer(src) {}

        constexpr __Refer(const __Refer<T, 0>&& src)
        : cRefer(src) {}

        constexpr __Refer(const __Owner<T, 0>& src)
        : cRefer(src) {}

        constexpr __Refer(const __Owner<T, 0>&& src)
        : cRefer(src) {}
    };


    /// @brief 
    /// The binder for [__Refer].
    /// @tparam T 
    /// Trivial data type
    template<typename T>
    using cRefer = __Refer<T, std::is_trivial<T>::value>;
 
}}}
#pragma endregion

#pragma region Own
namespace ae2f { namespace Ds { namespace Arr {
    #pragma region Own

    /// @warning
    /// Using this class directly may cause undefined behaviour. \n
    /// Using the binder instead is recommended.
    /// @brief
    /// # This structure owns the memory.
    /// 
    /// Suggest the type is trivial. \n
    /// Therefore the element type will be [T] itself.
    /// @tparam T 
    /// Trivial data type
    template<typename T>
    struct __Owner<T, 1>
    :   public Alloc::xrOwner,
        public __def<T> 
    {
        using _f = __def<T>;

        /// @brief
        /// Gets data from a class.
        /// @param index
        /// The Index [in an unit of bytes] where the element to copy is.
        /// @param perr
        /// The pointer to store the error state.
        /// @return 
        /// The element of index.
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocGets_t
        /// @see ae2f_cDsAllocRefGets
        /// @see ae2f_cDsAllocOwnGets
        /// @see ae2f::Ds::Alloc::xrOwner::Read
        inline const typename _f::El_t Read(size_t index, ae2f_err_t* perr = 0) const noexcept {
            if(!perr) perr = &ae2f_errLast;

            T b[1];

            perr[0] = Alloc::xrOwner::Read(
                index * sizeof(T), 
                ae2f_reinterpret_cast(void*, b), 
                sizeof(T)
            );

            return b[0];
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param el The element to write.
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
        /// @see ae2f::Ds::Alloc::xrOwner::Write
        inline ae2f_err_t Write(size_t idx, const typename _f::El_t& el) noexcept {
            return Alloc::xrOwner::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param el The element to write.
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
        /// @see ae2f::Ds::Alloc::xrOwner::Write
        inline ae2f_err_t Write(size_t idx, const typename _f::El_t&& el) noexcept {
            return Alloc::xrOwner::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        /// @exception ae2f_errGlob_IMP_NOT_FOUND
        constexpr ae2f_err_t ReConfig(size_t elcount, size_t elsize) {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        /// @exception ae2f_errGlob_IMP_NOT_FOUND
        constexpr ae2f_err_t Copy(const Alloc::rRefer& src) noexcept {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        /// @exception ae2f_errGlob_IMP_NOT_FOUND
        constexpr ae2f_err_t Copy(const Alloc::rRefer&& src) noexcept {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        inline ae2f_err_t Resize(size_t elcount) {
            return xrOwner::ReConfig(elcount, _f::ElSize);
        }

        inline __Owner(
            ae2f_err_t* perr,
            const ae2f_vDsAlloc* imp
        ) : Alloc::xrOwner(perr, imp) {}
    };

    /// @warning
    /// Using this class directly may cause undefined behaviour. \n
    /// Using the binder instead is recommended.
    /// @brief
    /// # This structure owns the memory.
    /// 
    /// Suggest the type is no trivial. \n
    /// Therefore the element type will be @ref ae2f::Ds::Arr::Pack<T>, in order to avoid the data destruction under wrong responsibility.
    /// @tparam T 
    /// Non-Trivial data type
    /// @see ae2f::Ds::Arr::Pack<T>
    template<typename T>
    struct __Owner<T, 0>
    :   public Alloc::xrOwner,
        public __def<Pack<T>> 
    {
        using _f = __def<Pack<T>>;

        /// @brief
        /// Gets data from a class.
        /// @param index
        /// The Index [in an unit of bytes] where the element to copy is.
        /// @param perr
        /// The pointer to store the error state.
        /// @return 
        /// The element of index.
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errDsAlloc_BAD_IDX \n
        /// @ref eRef::EL_NON_VALID
        /// @see ae2f_cDsAllocRef
        /// @see ae2f_fpDsAllocGets_t
        /// @see ae2f_cDsAllocRefGets
        /// @see ae2f_cDsAllocOwnGets
        /// @see ae2f::Ds::Alloc::xrOwner::Read
        inline const typename _f::El_t Read(size_t index, ae2f_err_t* perr = 0) const noexcept {
            if(!perr) perr = &ae2f_errLast;

            typename _f::El_t b[1];

            perr[0] |= Alloc::xrOwner::Read(
                index * _f::ElSize, 
                ae2f_reinterpret_cast(void*, b), 
                _f::ElSize
            );

            if(!b->isvalid())
            perr[0] |= eRef::EL_NON_VALID;

            return b[0];
        }

#pragma region non_trivial writing

        /// @brief
        /// Sets data to a class.
        /// @tparam Args 
        /// Arguments datatype.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param args Arguments to build the element to write.
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
        /// @see ae2f::Ds::Alloc::xrOwner::Write
        template<typename... Args>
        inline ae2f_err_t Write(size_t idx, Args&& ...args) noexcept {
            if(!_ae2f_DsAllocFndFunc(ae2f_static_cast(Alloc::rRefer*, this), Write)) {
                return ae2f_errGlob_IMP_NOT_FOUND;
            }

            ae2f_err_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[0] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            if(el->isvalid()) {
                el->Obj.~T();
            }
            new(el->c) T(args...);
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
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
        /// @see ae2f::Ds::Alloc::xrOwner::Write
        inline ae2f_err_t Write(size_t idx) noexcept {
            if(!_ae2f_DsAllocFndFunc(ae2f_static_cast(Alloc::rRefer*, this), Write)) {
                return ae2f_errGlob_IMP_NOT_FOUND;
            }

            ae2f_err_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[0] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            if(el->isvalid()) el->Obj.~T();
            new(el->c) T();
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

#pragma endregion
        
        inline ~__Owner() {
            size_t a[2] = {0, 0};
            ae2f_errLast |= this->Length(a, a+1);

            a[0] = (a[1] * a[0]) / this->ElSize;

            for(size_t i = 0; i < a[0]; i++) {
                Pack<T> t = this->Read(i, &ae2f_errLast);
                if(t.isvalid()) t.Obj.~T();
            }
        }


        inline ae2f_err_t Resize(size_t nCount) noexcept {
            size_t a, b; ae2f_err_t err = ae2f_errGlob_OK;
            err |= xrOwner::Length(&a, &b);
            if(err) {
                return err;
            }

            a = (b * a) / _f::ElSize;

            for(size_t i = nCount; i < a; i++) {
                typename _f::El_t read = Read(i, &err);
                if(err) return err;
                if(read._isvalid()) {
                    read.Obj.~T();
                }
            }

            return xrOwner::ReConfig(nCount, _f::ElSize);
        }

        constexpr ae2f_err_t ReConfig(size_t elcount, size_t elsize) {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        constexpr ae2f_err_t Copy(const Alloc::rRefer& src) noexcept {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        constexpr ae2f_err_t Copy(const Alloc::rRefer&& src) noexcept {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        inline __Owner(
            ae2f_err_t* perr,
            const ae2f_vDsAlloc* imp
        ) : Alloc::xrOwner(perr, imp) {}
    };

    template<typename T>
    using xrOwner = __Owner<T, std::is_trivial<T>::value>;

    #pragma endregion
}}}
#pragma endregion


namespace ae2f {
namespace Ds {
namespace Arr {

    template<typename T, const ae2f_vDsAlloc* __imp>
    struct iOwner : public xrOwner<T>, public Alloc::vfDef<__imp> {
        inline iOwner(
            ae2f_err_t* perr = 0
        ) noexcept : xrOwner<T>(perr, __imp) {}
    };

    namespace cOwner {
        template<typename T>
        using Linear_t = iOwner<T, &ae2f_vDsAllocLinear_imp>;
    }
}
}
}

#include <ae2f/Pack/End.h>

#endif