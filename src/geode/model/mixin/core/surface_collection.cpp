/*
 * Copyright (c) 2019 - 2025 Geode-solutions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <geode/model/mixin/core/surface_collection.hpp>

#include <geode/basic/bitsery_archive.hpp>
#include <geode/basic/pimpl_impl.hpp>

namespace geode
{
    template < index_t dimension >
    template < typename Archive >
    void SurfaceCollection< dimension >::serialize( Archive &archive )
    {
        archive.ext( *this,
            Growable< Archive, SurfaceCollection >{
                { []( Archive &a, SurfaceCollection &surface_collection ) {
                    a.ext( surface_collection,
                        bitsery::ext::BaseClass< Component< dimension > >{} );
                } } } );
    }

    template class opengeode_model_api SurfaceCollection< 2 >;
    template class opengeode_model_api SurfaceCollection< 3 >;

    SERIALIZE_BITSERY_ARCHIVE( opengeode_model_api, SurfaceCollection< 2 > );
    SERIALIZE_BITSERY_ARCHIVE( opengeode_model_api, SurfaceCollection< 3 > );
} // namespace geode
