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

#pragma once

#include <array>
#include <vector>

#include <absl/container/inlined_vector.h>

#include <geode/mesh/builder/tetrahedral_solid_builder.hpp>
#include <geode/mesh/common.hpp>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( Point );
    FORWARD_DECLARATION_DIMENSION_CLASS( OpenGeodeTetrahedralSolid );
    class VertexSet;
} // namespace geode

namespace geode
{
    /*!
     * Implementation class for TetrahedralSolidBuilder using OpenGeode data
     * structure
     */
    template < index_t dimension >
    class OpenGeodeTetrahedralSolidBuilder
        : public TetrahedralSolidBuilder< dimension >
    {
    public:
        static constexpr auto dim = dimension;

        OpenGeodeTetrahedralSolidBuilder(
            VertexSet& vertex_set, MeshBuilderFactoryKey );

        explicit OpenGeodeTetrahedralSolidBuilder(
            OpenGeodeTetrahedralSolid< dimension >& mesh );

        OpenGeodeTetrahedralSolidBuilder(
            OpenGeodeTetrahedralSolidBuilder&& ) noexcept;

    private:
        void do_create_vertex() final;

        void do_create_vertices( index_t nb ) final;

        void do_delete_solid_vertices( const std::vector< bool >& to_delete,
            absl::Span< const index_t > old2new ) final;

        void do_permute_solid_vertices( absl::Span< const index_t > permutation,
            absl::Span< const index_t > old2new ) final;

        void do_set_polyhedron_vertex(
            const PolyhedronVertex& polyhedron_vertex,
            index_t vertex_id ) final;

        void do_create_tetrahedron(
            const std::array< index_t, 4 >& vertices ) final;

        void do_create_tetrahedra( index_t nb ) final;

        void do_delete_polyhedra( const std::vector< bool >& to_delete,
            absl::Span< const index_t > old2new ) final;

        void do_permute_polyhedra( absl::Span< const index_t > permutation,
            absl::Span< const index_t > old2new ) final;

        void do_set_polyhedron_adjacent(
            const PolyhedronFacet& polyhedron_facet,
            index_t adjacent_id ) final;

        void do_unset_polyhedron_adjacent(
            const PolyhedronFacet& polyhedron_facet ) final;

        void do_copy_points( const SolidMesh< dimension >& solid_mesh ) final;

        void do_copy_polyhedra(
            const SolidMesh< dimension >& solid_mesh ) final;

    private:
        OpenGeodeTetrahedralSolid< dimension >& geode_tetrahedral_solid_;
    };
    ALIAS_3D( OpenGeodeTetrahedralSolidBuilder );
} // namespace geode
