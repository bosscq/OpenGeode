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

#include <bitsery/ext/std_smart_ptr.h>

#include <geode/basic/attribute_manager.hpp>
#include <geode/basic/variable_attribute.hpp>

#include <geode/mesh/core/graph.hpp>

#include <geode/model/common.hpp>
#include <geode/model/mixin/core/component_type.hpp>
#include <geode/model/mixin/core/detail/uuid_to_index.hpp>
#include <geode/model/representation/core/mapping.hpp>

namespace geode
{
    namespace detail
    {
        /*!
         * This class stores all the relations between a set of components.
         * Each relationship links two components.
         */
        class opengeode_model_api RelationshipsImpl
        {
        public:
            using Iterator = typename EdgesAroundVertex::const_iterator;

            [[nodiscard]] index_t nb_components_with_relations() const;

            [[nodiscard]] index_t nb_relations(
                const uuid& component_id ) const;

            [[nodiscard]] Iterator begin_edge( const uuid& component_id ) const;

            [[nodiscard]] Iterator end_edge( const uuid& component_id ) const;

            [[nodiscard]] const ComponentID& graph_component_id(
                index_t graph_component ) const;

            [[nodiscard]] const ComponentID& graph_component_id(
                const EdgeVertex& graph_edge_vertex ) const;

            void remove_component( const uuid& component_id );

            index_t add_relation_edge(
                const ComponentID& from, const ComponentID& to );

            void remove_relation(
                const uuid& component_id1, const uuid& component_id2 );

            [[nodiscard]] AttributeManager& component_attribute_manager() const;

            [[nodiscard]] AttributeManager& relation_attribute_manager() const;

            [[nodiscard]] std::optional< index_t > relation_edge_index(
                const uuid& component_id1, const uuid& component_id2 ) const;

            [[nodiscard]] std::tuple< ComponentID, ComponentID >
                relation_components_from_index( index_t id ) const;

            void copy( const RelationshipsImpl& impl,
                const ModelCopyMapping& mapping );

        protected:
            RelationshipsImpl();

            void initialize_attributes();

            [[nodiscard]] std::optional< index_t > vertex_id(
                const uuid& component_id ) const;

            [[nodiscard]] const Graph& graph() const;

            void delete_isolated_vertices();

        private:
            friend class bitsery::Access;
            template < typename Archive >
            void serialize( Archive& archive )
            {
                archive.ext( *this,
                    Growable< Archive, RelationshipsImpl >{
                        { []( Archive& a, RelationshipsImpl& impl ) {
                            a.ext( impl.graph_, bitsery::ext::StdSmartPtr{} );
                            a.object( impl.uuid2index_ );
                            a.ext( impl.ids_, bitsery::ext::StdSmartPtr{} );
                            impl.delete_isolated_vertices();
                        } } } );
            }

            index_t register_component( const ComponentID& id );

            [[nodiscard]] const ComponentID& component_from_index(
                index_t id ) const;

            index_t do_add_relation_edge(
                const ComponentID& from, const ComponentID& to );

            index_t find_or_create_vertex_id( const ComponentID& id );

        protected:
            std::unique_ptr< Graph > graph_;
            detail::UuidToIndex uuid2index_;
            std::shared_ptr< VariableAttribute< ComponentID > > ids_;
        };
    } // namespace detail
} // namespace geode
