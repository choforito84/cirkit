/*
 *   Copyright (c) 2012, Michael Lehn, Klaus Pototzky
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3) Neither the name of the FLENS development group nor the names of
 *      its contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CXXLAPACK_INTERFACE_LARRD_TCC
#define CXXLAPACK_INTERFACE_LARRD_TCC 1

#include <iostream>
#include <cxxlapack/interface/interface.h>
#include <cxxlapack/netlib/netlib.h>

namespace cxxlapack {

template <typename IndexType>
IndexType
larrd(char                  range,
      char                  order,
      IndexType             n,
      float                 vl,
      float                 vu,
      IndexType             il,
      IndexType             iu,
      const float           *gers,
      float                 reltol,
      const float           *d,
      const float           *e,
      const float           *e2,
      const float           pivmin,
      IndexType             nsplit,
      IndexType             *isplit,
      IndexType             &m,
      float                 *w,
      float                 *werr,
      float                 &wl,
      float                 &wu,
      IndexType             *iblock,
      IndexType             *indexw,
      float                 *work,
      IndexType             *iWork)
{
    CXXLAPACK_DEBUG_OUT("slarrd");

    IndexType info;
    LAPACK_IMPL(slarrd)(&range,
                        &order,
                        &n,
                        &vl,
                        &vu,
                        &il,
                        &iu,
                        gers,
                        &reltol,
                        d,
                        e,
                        e2,
                        &pivmin,
                        &nsplit,
                        isplit,
                        &m,
                        w,
                        werr,
                        &wl,
                        &wu,
                        iblock,
                        indexw,
                        work,
                        iWork,
                        &info);
#   ifndef NDEBUG
    if (info<0) {
        std::cerr << "info = " << info << std::endl;
    }
#   endif
    ASSERT(info>=0);
    return info;
}


template <typename IndexType>
IndexType
larrd(char                  range,
      char                  order,
      IndexType             n,
      double                vl,
      double                vu,
      IndexType             il,
      IndexType             iu,
      const double          *gers,
      double                reltol,
      const double          *d,
      const double          *e,
      const double          *e2,
      const double          pivmin,
      IndexType             nsplit,
      IndexType             *isplit,
      IndexType             &m,
      double                *w,
      double                *werr,
      double                &wl,
      double                &wu,
      IndexType             *iblock,
      IndexType             *indexw,
      double                *work,
      IndexType             *iWork)
{
    CXXLAPACK_DEBUG_OUT("dlarrd");

    IndexType info;
    LAPACK_IMPL(dlarrd)(&range,
                        &order,
                        &n,
                        &vl,
                        &vu,
                        &il,
                        &iu,
                        gers,
                        &reltol,
                        d,
                        e,
                        e2,
                        &pivmin,
                        &nsplit,
                        isplit,
                        &m,
                        w,
                        werr,
                        &wl,
                        &wu,
                        iblock,
                        indexw,
                        work,
                        iWork,
                        &info);
#   ifndef NDEBUG
    if (info<0) {
        std::cerr << "info = " << info << std::endl;
    }
#   endif
    ASSERT(info>=0);
    return info;
}


} // namespace cxxlapack

#endif // CXXLAPACK_INTERFACE_LARRD_TCC
