/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.hpp \n
/// Few definitions may lack.


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