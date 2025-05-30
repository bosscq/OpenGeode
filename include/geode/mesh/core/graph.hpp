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

#include <optional>
#include <vector>

#include <absl/container/inlined_vector.h>

#include <geode/basic/passkey.hpp>

#include <geode/mesh/common.hpp>
#include <geode/mesh/core/vertex_set.hpp>

namespace geode
{
    class AttributeManager;
    class GraphBuilder;
} // namespace geode

namespace geode
{
    /*!
     * This struct represents a graph edge endpoint
     */
    struct opengeode_mesh_api EdgeVertex
    {
        EdgeVertex() = default;
        EdgeVertex( index_t edge_id_in, local_index_t vertex_id_in )
            : edge_id( edge_id_in ), vertex_id( vertex_id_in )
        {
        }
        [[nodiscard]] bool operator==( const EdgeVertex& other ) const
        {
            return edge_id == other.edge_id && vertex_id == other.vertex_id;
        }
        [[nodiscard]] bool operator!=( const EdgeVertex& other ) const
        {
            return !( *this == other );
        }
        [[nodiscard]] bool operator<( const EdgeVertex& other ) const
        {
            if( edge_id != other.edge_id )
            {
                return edge_id < other.edge_id;
            }
            return vertex_id < other.vertex_id;
        }
        [[nodiscard]] EdgeVertex opposite() const
        {
            const local_index_t opposite = vertex_id == 0 ? 1 : 0;
            return { edge_id, opposite };
        }
        [[nodiscard]] std::string string() const
        {
            return absl::StrCat( "(", edge_id, ", ", vertex_id, ")" );
        }
        template < typename Archive >
        void serialize( Archive& archive );

        /*!
         * Index of the edge
         */
        index_t edge_id{ NO_ID };
        /*!
         * Identification of the edge endpoint (0 or 1)
         */
        local_index_t vertex_id{ NO_LID };
    };

    using CurveVerticesAroundVertex = absl::InlinedVector< index_t, 2 >;

    using EdgesAroundVertex = absl::InlinedVector< EdgeVertex, 2 >;

    /*!
     * Interface class to represent a Graph.
     * A graph is a set of vertices linked by edges
     */
    class opengeode_mesh_api Graph : public VertexSet
    {
        PASSKEY( GraphBuilder, GraphKey );

    public:
        using Builder = GraphBuilder;

        ~Graph();

        /*!
         * Create a new Graph using default data structure.
         */
        [[nodiscard]] static std::unique_ptr< Graph > create();

        /*!
         * Create a new Graph using a specified data structure.
         * @param[in] impl Data structure implementation
         */
        [[nodiscard]] static std::unique_ptr< Graph > create(
            const MeshImpl& impl );

        [[nodiscard]] static MeshType type_name_static();

        [[nodiscard]] std::unique_ptr< Graph > clone() const;

        /*!
         * Return the vertex index corresponding to an edge endpoint
         * @param[in] edge_vertex Edge endpoint
         */
        [[nodiscard]] index_t edge_vertex(
            const EdgeVertex& edge_vertex ) const;

        /*!
         * Return the indices of the two edge vertices
         * @param[in] edge_id Index of the edge
         */
        [[nodiscard]] std::array< index_t, 2 > edge_vertices(
            index_t edge_id ) const;

        [[nodiscard]] index_t nb_edges() const;

        /*!
         * Access to the manager of attributes associated with edges.
         */
        [[nodiscard]] AttributeManager& edge_attribute_manager() const;

        /*!
         * Get all edge endpoints corresponding to a given vertex
         * @param[in] vertex_id Index of the vertex
         */
        [[nodiscard]] const EdgesAroundVertex& edges_around_vertex(
            index_t vertex_id ) const;

        /*!
         * Returns the vertices linked by an edge to the given mesh vertex.
         */
        [[nodiscard]] CurveVerticesAroundVertex vertices_around_vertex(
            index_t vertex_id ) const;

        [[nodiscard]] bool is_vertex_isolated( index_t vertex_id ) const;

        [[nodiscard]] std::optional< index_t > edge_from_vertices(
            index_t v0, index_t v1 ) const;

    public:
        void set_edges_around_vertex(
            index_t vertex_id, EdgesAroundVertex edges, GraphKey );

        void associate_edge_vertex_to_vertex(
            const EdgeVertex& edge_vertex, index_t vertex_id, GraphKey );

        void disassociate_edge_vertex_to_vertex(
            const EdgeVertex& edge_vertex, GraphKey );

    protected:
        Graph();
        Graph( Graph&& other ) noexcept;
        Graph& operator=( Graph&& other ) noexcept;

    private:
        friend class bitsery::Access;
        template < typename Archive >
        void serialize( Archive& archive );

        [[nodiscard]] virtual index_t get_edge_vertex(
            const EdgeVertex& edge_vertex ) const = 0;

    private:
        IMPLEMENTATION_MEMBER( impl_ );
    };
} // namespace geode

namespace std
{
    template <>
    struct opengeode_mesh_api hash< geode::EdgeVertex >
    {
        size_t operator()( const geode::EdgeVertex& edge_vertex ) const;
    };
} // namespace std