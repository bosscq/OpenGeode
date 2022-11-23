/*
 * Copyright (c) 2019 - 2022 Geode-solutions
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

#include <geode/model/helpers/aabb_model_helpers.h>

#include <async++.h>

#include <geode/geometry/aabb.h>
#include <geode/geometry/bounding_box.h>

#include <geode/mesh/core/edged_curve.h>
#include <geode/mesh/core/solid_mesh.h>
#include <geode/mesh/core/surface_mesh.h>

#include <geode/model/mixin/core/block.h>
#include <geode/model/mixin/core/line.h>
#include <geode/model/mixin/core/surface.h>
#include <geode/model/representation/core/brep.h>
#include <geode/model/representation/core/section.h>

namespace
{
    template < geode::index_t dimension, typename Range >
    std::tuple< geode::AABBTree< dimension >, absl::FixedArray< geode::uuid > >
        create_aabb( const Range& range, geode::index_t nb_elements )
    {
        absl::FixedArray< geode::BoundingBox< dimension > > boxes(
            nb_elements );
        absl::FixedArray< geode::uuid > mapping( nb_elements );
        absl::FixedArray< async::task< void > > tasks( nb_elements );
        geode::index_t id{ 0 };
        for( const auto& element : range )
        {
            tasks[id] = async::spawn( [id, &mapping, &boxes, &element] {
                mapping[id] = element.id();
                boxes[id] = element.mesh().bounding_box();
            } );
            id++;
        }
        async::when_all( tasks.begin(), tasks.end() ).wait();
        return std::make_tuple(
            geode::AABBTree< dimension >{ boxes }, std::move( mapping ) );
    }
} // namespace

namespace geode
{
    std::tuple< AABBTree3D, absl::FixedArray< uuid > > create_lines_aabb_tree(
        const BRep& model )
    {
        return create_aabb< 3 >( model.lines(), model.nb_lines() );
    }

    std::tuple< AABBTree3D, absl::FixedArray< uuid > >
        create_surfaces_aabb_tree( const BRep& model )
    {
        return create_aabb< 3 >( model.surfaces(), model.nb_surfaces() );
    }

    std::tuple< AABBTree3D, absl::FixedArray< uuid > > create_blocks_aabb_tree(
        const BRep& model )
    {
        return create_aabb< 3 >( model.blocks(), model.nb_blocks() );
    }

    std::tuple< AABBTree2D, absl::FixedArray< uuid > > create_lines_aabb_tree(
        const Section& model )
    {
        return create_aabb< 2 >( model.lines(), model.nb_lines() );
    }

    std::tuple< AABBTree2D, absl::FixedArray< uuid > >
        create_surfaces_aabb_tree( const Section& model )
    {
        return create_aabb< 2 >( model.surfaces(), model.nb_surfaces() );
    }
} // namespace geode