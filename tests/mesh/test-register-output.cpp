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

#include <geode/basic/logger.hpp>

#include <geode/mesh/core/geode/geode_edged_curve.hpp>
#include <geode/mesh/core/geode/geode_graph.hpp>
#include <geode/mesh/core/geode/geode_point_set.hpp>
#include <geode/mesh/core/geode/geode_polygonal_surface.hpp>
#include <geode/mesh/core/geode/geode_polyhedral_solid.hpp>
#include <geode/mesh/core/geode/geode_tetrahedral_solid.hpp>
#include <geode/mesh/core/geode/geode_triangulated_surface.hpp>
#include <geode/mesh/io/geode/geode_edged_curve_output.hpp>
#include <geode/mesh/io/geode/geode_graph_output.hpp>
#include <geode/mesh/io/geode/geode_point_set_output.hpp>
#include <geode/mesh/io/geode/geode_polygonal_surface_output.hpp>
#include <geode/mesh/io/geode/geode_polyhedral_solid_output.hpp>
#include <geode/mesh/io/geode/geode_tetrahedral_solid_output.hpp>
#include <geode/mesh/io/geode/geode_triangulated_surface_output.hpp>
#include <geode/mesh/io/geode/register_output.hpp>

#include <geode/tests/common.hpp>

template < typename GeodeFactory >
void check_register( std::string_view extension )
{
    OPENGEODE_EXCEPTION( GeodeFactory::has_creator( extension.data() ),
        "[Test] No creator for extension ", extension, " is not correct" );
}

void test()
{
    /* To initialize the mesh library */
    geode::register_geode_mesh_output();

    /* Run checks */
    check_register< geode::GraphOutputFactory >(
        geode::OpenGeodeGraph::native_extension_static().data() );
    check_register< geode::PointSetOutputFactory2D >(
        geode::OpenGeodePointSet2D::native_extension_static().data() );
    check_register< geode::PointSetOutputFactory3D >(
        geode::OpenGeodePointSet3D::native_extension_static().data() );
    check_register< geode::EdgedCurveOutputFactory2D >(
        geode::OpenGeodeEdgedCurve2D::native_extension_static().data() );
    check_register< geode::EdgedCurveOutputFactory3D >(
        geode::OpenGeodeEdgedCurve3D::native_extension_static().data() );
    check_register< geode::PolygonalSurfaceOutputFactory2D >(
        geode::OpenGeodePolygonalSurface2D::native_extension_static().data() );
    check_register< geode::PolygonalSurfaceOutputFactory3D >(
        geode::OpenGeodePolygonalSurface3D::native_extension_static().data() );
    check_register< geode::TriangulatedSurfaceOutputFactory2D >(
        geode::OpenGeodeTriangulatedSurface2D::native_extension_static()
            .data() );
    check_register< geode::TriangulatedSurfaceOutputFactory3D >(
        geode::OpenGeodeTriangulatedSurface3D::native_extension_static()
            .data() );
    check_register< geode::PolyhedralSolidOutputFactory3D >(
        geode::OpenGeodePolyhedralSolid3D::native_extension_static().data() );
    check_register< geode::TetrahedralSolidOutputFactory3D >(
        geode::OpenGeodeTetrahedralSolid3D::native_extension_static().data() );
}

OPENGEODE_TEST( "register-output" )