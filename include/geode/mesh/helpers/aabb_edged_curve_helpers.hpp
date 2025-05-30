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

/*
 * Modified from RINGMesh https://github.com/ringmesh/RINGMesh
 * Copyright (c) 2012-2018, Association Scientifique pour la Geologie et ses
 * Applications (ASGA)
 */

#pragma once

#include <geode/mesh/common.hpp>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( Point );
    FORWARD_DECLARATION_DIMENSION_CLASS( AABBTree );
    FORWARD_DECLARATION_DIMENSION_CLASS( EdgedCurve );
    FORWARD_DECLARATION_DIMENSION_CLASS( CoordinateSystem );
    ALIAS_2D_AND_3D( CoordinateSystem );
    template < typename T >
    class GenericMeshAABB;
} // namespace geode

namespace geode
{
    template < index_t dimension >
    [[nodiscard]] AABBTree< dimension > create_aabb_tree(
        const EdgedCurve< dimension >& mesh );

    template < index_t dimension >
    class DistanceToEdge
    {
    public:
        explicit DistanceToEdge( const EdgedCurve< dimension >& mesh )
            : mesh_( mesh )
        {
        }

        [[nodiscard]] double operator()(
            const Point< dimension >& query, index_t cur_box ) const;

    private:
        const EdgedCurve< dimension >& mesh_;
    };
    ALIAS_1D_AND_2D_AND_3D( DistanceToEdge );

    template < index_t dimension >
    class AnisotropicDistanceToEdge
    {
    public:
        explicit AnisotropicDistanceToEdge( const EdgedCurve< dimension >& mesh,
            const CoordinateSystem< dimension >& coordinate_system )
            : mesh_( mesh ), coordinate_system_( coordinate_system )
        {
        }

        [[nodiscard]] double operator()(
            const Point< dimension >& query, index_t cur_box ) const;

    private:
        const EdgedCurve< dimension >& mesh_;
        const CoordinateSystem< dimension >& coordinate_system_;
    };
    ALIAS_2D_AND_3D( AnisotropicDistanceToEdge );

    template < index_t dimension >
    class GenericMeshAABB< EdgedCurve< dimension > >
    {
    public:
        explicit GenericMeshAABB( const EdgedCurve< dimension >& mesh )
            : elements_tree_{ create_aabb_tree( mesh ) },
              distance_action_{ mesh }
        {
        }

        [[nodiscard]] std::tuple< index_t, double > closest_element(
            const Point< dimension >& query ) const
        {
            return this->elements_aabb().closest_element_box(
                query, distance_action_ );
        }

    protected:
        [[nodiscard]] const AABBTree< dimension >& elements_aabb() const
        {
            return elements_tree_;
        }

    private:
        AABBTree< dimension > elements_tree_;
        const DistanceToEdge< dimension > distance_action_;
    };
    template < index_t dimension >
    using EdgedCurveAABB = GenericMeshAABB< EdgedCurve< dimension > >;
    ALIAS_1D_AND_2D_AND_3D( EdgedCurveAABB );
} // namespace geode
