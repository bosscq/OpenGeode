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

#include <geode/basic/assert.hpp>
#include <geode/basic/logger.hpp>
#include <geode/basic/range.hpp>

#include <geode/model/helpers/detail/mappings_merger.hpp>
#include <geode/model/mixin/core/corner.hpp>
#include <geode/model/mixin/core/line.hpp>
#include <geode/model/mixin/core/surface.hpp>
#include <geode/model/representation/core/mapping.hpp>

#include <geode/tests/common.hpp>

void test_copy_mapping()
{
    geode::ModelCopyMapping copy_mapping;

    std::vector< geode::uuid > uuids_in( 3 );
    std::vector< geode::uuid > uuids_out( 3 );

    geode::BijectiveMapping< geode::uuid > corner_mapping;
    for( const auto i : geode::LRange{ 3 } )
    {
        corner_mapping.map( uuids_in[i], uuids_out[i] );
    }
    copy_mapping.emplace(
        geode::Corner3D::component_type_static(), std::move( corner_mapping ) );
    OPENGEODE_EXCEPTION( !copy_mapping.has_mapping_type(
                             geode::Surface3D::component_type_static() ),
        "[Test] Copy mappings should not exist for Surfaces" );
    OPENGEODE_EXCEPTION( copy_mapping.has_mapping_type(
                             geode::Corner3D::component_type_static() ),
        "[Test] Copy mappings should exist for Corners" );
    const auto& corner_copy_mappings =
        copy_mapping.at( geode::Corner3D::component_type_static() );
    OPENGEODE_EXCEPTION( corner_copy_mappings.size() == 3,
        "[Test] Wrong size for CopyMapping Corners" );
    for( const auto i : geode::LRange{ 3 } )
    {
        OPENGEODE_EXCEPTION(
            corner_copy_mappings.in2out( uuids_in[i] ) == uuids_out[i],
            "[Test] Wrong mapping for CopyMapping Corners" );
    }
}

void test_generic_mapping()
{
    geode::ModelGenericMapping generic_mapping;

    std::vector< geode::uuid > uuids_in( 3 );
    std::vector< geode::uuid > uuids_out( 3 );

    geode::GenericMapping< geode::uuid > corner_mapping;
    for( const auto i : geode::LRange{ 3 } )
    {
        for( const auto j : geode::Range{ i, 3 } )
        {
            corner_mapping.map( uuids_in[i], uuids_out[j] );
            DEBUG( i );
            DEBUG( j );
            DEBUG( "----" );
        }
    }
    generic_mapping.emplace(
        geode::Corner3D::component_type_static(), std::move( corner_mapping ) );
    OPENGEODE_EXCEPTION( !generic_mapping.has_mapping_type(
                             geode::Surface3D::component_type_static() ),
        "[Test] Generic mappings should not exist for Surfaces" );
    OPENGEODE_EXCEPTION( generic_mapping.has_mapping_type(
                             geode::Corner3D::component_type_static() ),
        "[Test] Generic mappings should exist for Corners" );
    const auto& corner_generic_mappings =
        generic_mapping.at( geode::Corner3D::component_type_static() );
    OPENGEODE_EXCEPTION( corner_generic_mappings.size_in() == 3,
        "[Test] Wrong size for CopyMapping Corners in" );
    OPENGEODE_EXCEPTION( corner_generic_mappings.size_out() == 3,
        "[Test] Wrong size for CopyMapping Corners out" );
    for( const auto i : geode::LRange{ 3 } )
    {
        OPENGEODE_EXCEPTION(
            corner_generic_mappings.in2out( uuids_in[i] ).size()
                == static_cast< geode::index_t >( 3 - i ),
            "[Test] Wrong mapping for CopyMapping Corners (in2out)" );
        OPENGEODE_EXCEPTION(
            corner_generic_mappings.out2in( uuids_out[i] ).size()
                == static_cast< geode::index_t >( i + 1 ),
            "[Test] Wrong mapping for CopyMapping Corners (out2in)" );
    }
}

void test_components_mapping()
{
    geode::ComponentMeshVertexMapping vertices_mapping;
    geode::ComponentMeshVertexMapping elements_mapping;

    std::vector< geode::uuid > uuids_in( 3 );
    std::vector< geode::uuid > uuids_out( 3 );

    for( const auto mesh_id : geode::LRange{ 2 } )
    {
        for( const auto vertex_id : geode::Range{ 10 } )
        {
            vertices_mapping.map( { uuids_in[mesh_id], vertex_id },
                { { geode::Line3D::component_type_static(),
                      uuids_out[mesh_id] },
                    2 * vertex_id } );
        }
        for( const auto element_id : geode::Range{ 8 } )
        {
            elements_mapping.map( { uuids_in[mesh_id], element_id },
                { { geode::Line3D::component_type_static(),
                      uuids_out[mesh_id] },
                    8 - element_id } );
        }
    }
    for( const auto vertex_id : geode::Range{ 9 } )
    {
        vertices_mapping.map( { uuids_in[2], vertex_id },
            { { geode::Surface3D::component_type_static(), uuids_out[2] },
                3 * vertex_id } );
    }
    for( const auto element_id : geode::Range{ 5 } )
    {
        elements_mapping.map( { uuids_in[2], element_id },
            { { geode::Surface3D::component_type_static(), uuids_out[2] },
                element_id + 2 } );
    }

    OPENGEODE_EXCEPTION( vertices_mapping.size_in() == 29,
        "[Test] Wrong size for vertices mappings" );
    OPENGEODE_EXCEPTION( elements_mapping.size_out() == 21,
        "[Test] Wrong size for elements mappings" );
    for( const auto mesh_id : geode::LRange{ 2 } )
    {
        for( const auto vertex_id : geode::Range{ 10 } )
        {
            geode::ComponentMeshVertex value{
                { geode::Line3D::component_type_static(), uuids_out[mesh_id] },
                2 * vertex_id
            };
            OPENGEODE_EXCEPTION(
                vertices_mapping.in2out( { uuids_in[mesh_id], vertex_id } )
                        .at( 0 )
                    == value,
                "[Test] Wrong mapping for vertices (in2out)" );
        }
        for( const auto element_id : geode::Range{ 8 } )
        {
            geode::ComponentMeshVertex value{
                { geode::Line3D::component_type_static(), uuids_out[mesh_id] },
                8 - element_id
            };
            OPENGEODE_EXCEPTION(
                elements_mapping.in2out( { uuids_in[mesh_id], element_id } )
                        .at( 0 )
                    == value,
                "[Test] Wrong mapping for elements (in2out)" );
        }
    }
}

void test_merge_mappings()
{
    std::vector< geode::uuid > uuids_in( 3 );
    std::vector< geode::uuid > uuids_mid( 3 );
    std::vector< geode::uuid > uuids_out( 3 );

    geode::ModelGenericMapping generic_mapping;
    geode::GenericMapping< geode::uuid > first_mapping;
    for( const auto i : geode::LRange{ 3 } )
    {
        for( const auto j : geode::Range{ i, 3 } )
        {
            first_mapping.map( uuids_in[i], uuids_mid[j] );
        }
    }
    generic_mapping.emplace(
        geode::Corner3D::component_type_static(), std::move( first_mapping ) );

    geode::ModelCopyMapping copy_mapping;
    geode::BijectiveMapping< geode::uuid > second_mapping;
    for( const auto i : geode::LRange{ 3 } )
    {
        second_mapping.map( uuids_mid[i], uuids_out[i] );
    }
    copy_mapping.emplace(
        geode::Corner3D::component_type_static(), std::move( second_mapping ) );

    const auto merged_mapping =
        geode::detail::merge_mappings( generic_mapping, copy_mapping );
    OPENGEODE_EXCEPTION( !merged_mapping.has_mapping_type(
                             geode::Surface3D::component_type_static() ),
        "[Test] Generic mappings should not exist for Surfaces" );
    OPENGEODE_EXCEPTION( generic_mapping.has_mapping_type(
                             geode::Corner3D::component_type_static() ),
        "[Test] Generic mappings should exist for Corners" );
    const auto& corner_merged_mappings =
        merged_mapping.at( geode::Corner3D::component_type_static() );
    OPENGEODE_EXCEPTION( corner_merged_mappings.size_in() == 3,
        "[Test] Wrong size for CopyMapping Corners in" );
    OPENGEODE_EXCEPTION( corner_merged_mappings.size_out() == 3,
        "[Test] Wrong size for CopyMapping Corners out" );
    for( const auto i : geode::LRange{ 3 } )
    {
        OPENGEODE_EXCEPTION( corner_merged_mappings.in2out( uuids_in[i] ).size()
                                 == static_cast< geode::index_t >( 3 - i ),
            "[Test] Wrong mapping for CopyMapping Corners (in2out)" );
        OPENGEODE_EXCEPTION(
            corner_merged_mappings.out2in( uuids_out[i] ).size()
                == static_cast< geode::index_t >( i + 1 ),
            "[Test] Wrong mapping for CopyMapping Corners (out2in)" );
    }
}

void test()
{
    test_copy_mapping();
    test_generic_mapping();
    test_components_mapping();
}

OPENGEODE_TEST( "model-mapping" )