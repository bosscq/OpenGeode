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

#include <geode/mesh/helpers/ray_tracing.h>

#include <absl/algorithm/container.h>

#include <geode/basic/pimpl_impl.h>

#include <geode/geometry/basic_objects/segment.h>
#include <geode/geometry/basic_objects/triangle.h>
#include <geode/geometry/bounding_box.h>
#include <geode/geometry/distance.h>
#include <geode/geometry/information.h>
#include <geode/geometry/intersection.h>
#include <geode/geometry/intersection_detection.h>

#include <geode/mesh/core/surface_mesh.h>

namespace
{
    geode::Point3D end(
        const geode::SurfaceMesh3D& mesh, const geode::Ray3D& ray )
    {
        auto bbox = mesh.bounding_box();
        bbox.add_point( ray.origin() );
        const auto diagonal =
            geode::point_point_distance( bbox.min(), bbox.max() );
        return ray.origin() + ray.direction() * diagonal;
    }
} // namespace

namespace geode
{
    class RayTracing3D::Impl
    {
    public:
        Impl( const SurfaceMesh3D& mesh, const Ray3D& ray )
            : mesh_( mesh ),
              end_{ end( mesh, ray ) },
              segment_{ ray.origin(), end_ }
        {
        }

        absl::optional< PolygonDistance > closest_polygon() const
        {
            if( results_.empty() )
            {
                return absl::nullopt;
            }
            absl::c_sort( results_ );
            return results_.front();
        }

        void compute( index_t polygon_id )
        {
            const auto& p0 =
                mesh_.point( mesh_.polygon_vertex( { polygon_id, 0 } ) );
            for( const auto e :
                LRange{ 1, mesh_.nb_polygon_edges( polygon_id ) - 1 } )
            {
                const auto edge_vertices =
                    mesh_.polygon_edge_vertices( { polygon_id, e } );
                const Triangle3D triangle{ p0,
                    mesh_.point( edge_vertices.front() ),
                    mesh_.point( edge_vertices.back() ) };
                const auto result = segment_triangle_intersection_detection(
                    segment_, triangle );
                if( result.first == Position::outside )
                {
                    continue;
                }
                const auto intersection =
                    segment_triangle_intersection( segment_, triangle );
                if( intersection.has_intersection() )
                {
                    const auto distance =
                        point_point_distance( segment_.vertices()[0].get(),
                            intersection.result.value() );
                    results_.emplace_back( polygon_id, distance );
                }
                else
                {
                    for( const auto e2 : LRange{ 3 } )
                    {
                        Point3D point;
                        std::tie( std::ignore, point,
                            std::ignore ) = segment_segment_distance( segment_,
                            { triangle.vertices()[e2].get(),
                                triangle.vertices()[( e2 + 1 ) % 3].get() } );
                        const auto distance = point_point_distance(
                            segment_.vertices()[0].get(), point );
                        results_.emplace_back( polygon_id, distance );
                    }
                }
                break;
            }
        }

    private:
        const SurfaceMesh3D& mesh_;
        DEBUG_CONST Point3D end_;
        DEBUG_CONST Segment3D segment_;
        mutable std::vector< PolygonDistance > results_;
    };

    RayTracing3D::RayTracing3D( const SurfaceMesh3D& mesh, const Ray3D& ray )
        : impl_{ mesh, ray }
    {
    }

    RayTracing3D::RayTracing3D( RayTracing3D&& other ) : impl_{ *other.impl_ }
    {
    }

    RayTracing3D::~RayTracing3D() {}

    absl::optional< RayTracing3D::PolygonDistance >
        RayTracing3D::closest_polygon() const
    {
        return impl_->closest_polygon();
    }

    void RayTracing3D::operator()( index_t polygon_id )
    {
        impl_->compute( polygon_id );
    }

} // namespace geode