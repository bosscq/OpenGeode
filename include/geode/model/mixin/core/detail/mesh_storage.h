/*
 * Copyright (c) 2019 Geode-solutions
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

#include <memory>

#include <geode/mesh/core/mesh_type.h>

namespace geode
{
    namespace detail
    {
        template < typename Mesh >
        class MeshStorage
        {
            using CreateMesh = typename std::add_pointer< void(
                const MeshType&, MeshStorage< Mesh >& ) >::type;

        public:
            MeshStorage() = default;

            MeshStorage( CreateMesh impl ) : create_mesh{ impl } {}

            void set_mesh( std::unique_ptr< Mesh > mesh )
            {
                mesh_type_ = mesh->type_name();
                mesh_ = std::move( mesh );
            }

            const Mesh& mesh() const
            {
                return *mesh_;
            }

            Mesh& modifiable_mesh()
            {
                return *mesh_;
            }

            void ensure_mesh_type()
            {
                if( !mesh_ || mesh_->type_name() != mesh_type_ )
                {
                    create_mesh( mesh_type_, *this );
                }
            }

            template < typename Archive >
            void serialize( Archive& archive )
            {
                archive.object( mesh_type_ );
            }

        private:
            std::unique_ptr< Mesh > mesh_;
            MeshType mesh_type_{ "" };
            CreateMesh create_mesh;
        };
    } // namespace detail
} // namespace geode