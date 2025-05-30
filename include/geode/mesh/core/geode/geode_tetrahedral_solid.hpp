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

#include <geode/basic/passkey.hpp>
#include <geode/basic/pimpl.hpp>

#include <geode/mesh/common.hpp>
#include <geode/mesh/core/tetrahedral_solid.hpp>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( OpenGeodeTetrahedralSolidBuilder );
    FORWARD_DECLARATION_DIMENSION_CLASS( Point );
} // namespace geode

namespace geode
{
    template < index_t dimension >
    class OpenGeodeTetrahedralSolid : public TetrahedralSolid< dimension >
    {
        OPENGEODE_DISABLE_COPY( OpenGeodeTetrahedralSolid );
        PASSKEY( OpenGeodeTetrahedralSolidBuilder< dimension >,
            OGTetrahedralSolidKey );

    public:
        using Builder = OpenGeodeTetrahedralSolidBuilder< dimension >;
        static constexpr auto dim = dimension;

        OpenGeodeTetrahedralSolid();
        OpenGeodeTetrahedralSolid( OpenGeodeTetrahedralSolid&& other ) noexcept;
        OpenGeodeTetrahedralSolid& operator=(
            OpenGeodeTetrahedralSolid&& other ) noexcept;
        ~OpenGeodeTetrahedralSolid();

        [[nodiscard]] static MeshImpl impl_name_static()
        {
            return MeshImpl{ absl::StrCat(
                "OpenGeodeTetrahedralSolid", dimension, "D" ) };
        }

        [[nodiscard]] MeshImpl impl_name() const override
        {
            return impl_name_static();
        }

        [[nodiscard]] MeshType type_name() const override
        {
            return TetrahedralSolid< dimension >::type_name_static();
        }

        [[nodiscard]] static std::string_view native_extension_static()
        {
            static const auto extension =
                absl::StrCat( "og_tso", dimension, "d" );
            return extension;
        }

        [[nodiscard]] std::string_view native_extension() const override
        {
            return native_extension_static();
        }

    public:
        void set_vertex( index_t vertex_id,
            Point< dimension > point,
            OGTetrahedralSolidKey );

        void set_polyhedron_vertex( const PolyhedronVertex& polyhedron_vertex,
            index_t vertex_id,
            OGTetrahedralSolidKey );

        void set_polyhedron_adjacent( const PolyhedronFacet& polyhedron_facet,
            index_t adjacent_id,
            OGTetrahedralSolidKey );

        void add_tetrahedron(
            const std::array< index_t, 4 >& vertices, OGTetrahedralSolidKey );

    private:
        friend class bitsery::Access;
        template < typename Archive >
        void serialize( Archive& archive );

        [[nodiscard]] index_t get_polyhedron_vertex(
            const PolyhedronVertex& polyhedron_vertex ) const override;

        [[nodiscard]] PolyhedronVertex get_polyhedron_facet_vertex_id(
            const PolyhedronFacetVertex& polyhedron_facet_vertex )
            const override;

        [[nodiscard]] std::optional< index_t > get_polyhedron_adjacent(
            const PolyhedronFacet& polyhedron_facet ) const override;

    private:
        IMPLEMENTATION_MEMBER( impl_ );
    };
    ALIAS_3D( OpenGeodeTetrahedralSolid );
} // namespace geode
