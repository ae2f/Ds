#include "Arr.h"

// Fork + exec

#if !defined(ae2f_ds_Arr_hpp)
#define ae2f_ds_Arr_hpp

#include <ae2f/Pack/Beg.h>

#include "Alloc.hpp"
#include <type_traits>

#include "Arr/Defs.hpp"
#include "Arr/Pack.hpp"

#include "Arr/Ref.hpp"
#include "Arr/Own.hpp"

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