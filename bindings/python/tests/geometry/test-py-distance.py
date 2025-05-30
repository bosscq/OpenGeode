# -*- coding: utf-8 -*-
# Copyright (c) 2019 - 2025 Geode-solutions
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import sys
import platform

if sys.version_info >= (3, 8, 0) and platform.system() == "Windows":
    for path in [x.strip() for x in os.environ["PATH"].split(";") if x]:
        os.add_dll_directory(path)

import math
import opengeode_py_basic as og
import opengeode_py_geometry as geom


def test_point_segment_distance():
    a = geom.Point2D([1.0, 5.0])
    b = geom.Point2D([-1.0, -5.0])
    segment2D = geom.Segment2D(a, b)

    distance = geom.point_segment_distance2D(a, segment2D)
    if distance != 0:
        raise ValueError(
            "[Test] Wrong result for point_segment_distance2D with query point a"
        )

    distance = geom.point_segment_distance2D(b, segment2D)
    if distance != 0:
        raise ValueError(
            "[Test] Wrong result for point_segment_distance2D with query point b"
        )

    q1 = geom.Point2D([0.0, 0.0])
    distance = geom.point_segment_distance2D(q1, segment2D)
    if distance != 0:
        raise ValueError(
            "[Test] Wrong result for point_segment_distance2D with query point q1"
        )

    q2 = geom.Point2D([10.0, 10.0])
    distance = geom.point_segment_distance2D(q2, segment2D)
    if math.fabs(distance - math.sqrt(106)) > og.GLOBAL_EPSILON:
        raise ValueError(
            "[Test] Wrong result for point_segment_distance2D with query point q2"
        )

    q3 = geom.Point2D([5.0, -1.0])
    distance = geom.point_segment_distance2D(q3, segment2D)
    result_q3 = geom.Point2D([0.0, 0.0])
    if math.fabs(distance - math.sqrt(26)) > og.GLOBAL_EPSILON:
        raise ValueError(
            "[Test] Wrong result for point_segment_distance2D with query point q3"
        )

    q4 = geom.Point2D([5.5, 1.5])
    distance = geom.point_segment_distance2D(q4, segment2D)
    result_q4 = geom.Point2D([0.5, 2.5])
    if math.fabs(distance - math.sqrt(26)) > og.GLOBAL_EPSILON:
        raise ValueError(
            "[Test] Wrong result for point_segment_distance2D with query point q4"
        )


def test_segment_segment_distance():
    a = geom.Point3D([0.0, 0.0, 0.0])
    b = geom.Point3D([2.0, 2.0, 0.0])
    c = geom.Point3D([0.0, 2.0, 1.0])
    d = geom.Point3D([2.0, 0.0, 1.0])
    e = geom.Point3D([0.0, 0.0, 1.0])
    f = geom.Point3D([2.0, 2.0, 1.0])
    g = geom.Point3D([3.0, 0.0, 1.0])
    h = geom.Point3D([5.0, -2.0, 1.0])
    segment_ab = geom.Segment3D(a, b)
    segment_cd = geom.Segment3D(c, d)
    segment_ef = geom.Segment3D(e, f)
    segment_gh = geom.Segment3D(g, h)

    distance, closest_point0, closest_point1 = geom.segment_segment_distance3D(
        segment_ab, segment_cd
    )
    r00 = geom.Point3D([1.0, 1.0, 0.0])
    r01 = geom.Point3D([1.0, 1.0, 1.0])
    if (
        abs(distance - 1) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_segment_distance3D with query segment_ab and segment_cd"
        )

    distance, closest_point0, closest_point1 = geom.segment_segment_distance3D(
        segment_ab, segment_ef
    )
    r00 = geom.Point3D([0.0, 0.0, 0.0])
    r01 = geom.Point3D([0.0, 0.0, 1.0])
    if (
        abs(distance - 1) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_segment_distance3D with query segment_ab and segment_ef"
        )

    distance, closest_point0, closest_point1 = geom.segment_segment_distance3D(
        segment_cd, segment_gh
    )
    if (
        abs(distance - 1) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(d)
        or not closest_point1.inexact_equal(g)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_segment_distance3D with query segment_cd and segment_gh"
        )


def test_segment_line_distance():
    a = geom.Point3D([0.0, 0.0, 0.0])
    b = geom.Point3D([2.0, 2.0, 0.0])
    c = geom.Point3D([0.0, 2.0, 1.0])
    d = geom.Point3D([2.0, 0.0, 1.0])
    e = geom.Point3D([0.0, 0.0, 1.0])
    f = geom.Point3D([2.0, 2.0, 1.0])
    g = geom.Point3D([3.0, 0.0, 1.0])
    h = geom.Point3D([5.0, -2.0, 1.0])
    segment_ab = geom.Segment3D(a, b)
    segment_cd = geom.Segment3D(c, d)
    segment_ef = geom.Segment3D(e, f)
    segment_gh = geom.Segment3D(g, h)
    line_cd = geom.InfiniteLine3D(segment_cd)
    line_ef = geom.InfiniteLine3D(segment_ef)
    line_gh = geom.InfiniteLine3D(segment_gh)

    distance, closest_point0, closest_point1 = geom.segment_line_distance3D(
        segment_ab, line_cd
    )
    r00 = geom.Point3D([1.0, 1.0, 0.0])
    r01 = geom.Point3D([1.0, 1.0, 1.0])
    if (
        abs(distance - 1) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_line_distance3D with query segment_ab and line_cd"
        )

    distance, closest_point0, closest_point1 = geom.segment_line_distance3D(
        segment_ab, line_ef
    )
    r00 = geom.Point3D([0.0, 0.0, 0.0])
    r01 = geom.Point3D([0.0, 0.0, 1.0])
    if (
        abs(distance - 1) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_line_distance3D with query segment_ab and line_ef"
        )

    distance, closest_point0, closest_point1 = geom.segment_line_distance3D(
        segment_cd, line_gh
    )
    r01 = geom.Point3D([0.5, 2.5, 1.0])
    if (
        abs(distance - math.sqrt(2) / 2.0) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(c)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_line_distance3D with query segment_cd and line_gh"
        )


def test_point_triangle_distance():
    a = geom.Point2D([0.0, 0.0])
    b = geom.Point2D([1.0, 0.0])
    c = geom.Point2D([1.0, 1.0])
    triangle2D = geom.Triangle2D(a, b, c)

    distance, closest_point = geom.point_triangle_distance2D(a, triangle2D)
    if distance != 0 or closest_point != a:
        raise ValueError(
            "[Test] Wrong result for point_triangle_distance2D with query point a"
        )

    distance, closest_point = geom.point_triangle_distance2D(b, triangle2D)
    if distance != 0 or closest_point != b:
        raise ValueError(
            "[Test] Wrong result for point_triangle_distance2D with query point b"
        )

    q1 = geom.Point2D([0.5, 0.5])
    distance, closest_point = geom.point_triangle_distance2D(q1, triangle2D)
    if distance != 0 or closest_point != q1:
        raise ValueError(
            "[Test] Wrong result for point_triangle_distance2D with query point q1"
        )

    q2 = geom.Point2D([0.0, 1.0])
    distance, closest_point = geom.point_triangle_distance2D(q2, triangle2D)
    result_q2 = geom.Point2D([0.5, 0.5])
    if distance != math.sqrt(2) / 2.0 or closest_point != result_q2:
        raise ValueError(
            "[Test] Wrong result for point_triangle_distance2D with query point q2"
        )

    q3 = geom.Point2D([2.0, 1.0])
    distance, closest_point = geom.point_triangle_distance2D(q3, triangle2D)
    if distance != 1 or closest_point != c:
        raise ValueError(
            "[Test] Wrong result for point_triangle_distance2D with query point q3"
        )

    q4 = geom.Point2D([0.5, 0.5])
    distance, closest_point = geom.point_triangle_distance2D(q4, triangle2D)
    if distance != 0 or closest_point != q4:
        raise ValueError(
            "[Test] Wrong result for point_triangle_distance2D with query point q4"
        )


def test_point_plane_distance():
    a = geom.Point3D([0.0, 0.0, 0.0])
    b = geom.Point3D([1.0, 0.0, 0.0])
    c = geom.Point3D([1.0, 1.0, 0.0])
    triangle = geom.Triangle3D(a, b, c)
    plane = triangle.plane()

    q1 = geom.Point3D([0.5, 0.5, 1])
    distance, closest_point = geom.point_plane_distance3D(q1, plane)
    answer = geom.Point3D([0.5, 0.5, 0.0])
    if distance != 1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_plane_distance with query point q1"
        )
    distance, closest_point = geom.point_plane_signed_distance3D(q1, plane)
    answer = geom.Point3D([0.5, 0.5, 0.0])
    if distance != 1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_plane_signed_distance with query point q1"
        )

    q2 = geom.Point3D([0.5, 0.5, -1])
    distance, closest_point = geom.point_plane_distance3D(q2, plane)
    answer = geom.Point3D([0.5, 0.5, 0.0])
    if distance != 1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_plane_distance with query point q2"
        )
    distance, closest_point = geom.point_plane_signed_distance3D(q2, plane)
    answer = geom.Point3D([0.5, 0.5, 0.0])
    if distance != -1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_plane_signed_distance with query point q2"
        )


def test_point_sphere_distance():
    a = geom.Point3D([0.0, 0.0, 1.0])
    sphere = geom.Sphere3D(a, 2.0)

    q1 = geom.Point3D([2.0, 0.0, 1.0])
    distance, closest_point = geom.point_sphere_distance3D(q1, sphere)
    if distance != 0.0 or closest_point != q1:
        raise ValueError(
            "[Test] Wrong result for point_sphere_distance with query point q1"
        )
    q1 = geom.Point3D([2.0, 0.0, 1.0])
    distance, closest_point = geom.point_sphere_signed_distance3D(q1, sphere)
    if distance != 0.0 or closest_point != q1:
        raise ValueError(
            "[Test] Wrong result for point_sphere_signed_distance with query point q1"
        )
    q1 = geom.Point3D([2.0, 0.0, 1.0])
    distance, closest_point = geom.point_ball_distance3D(q1, sphere)
    if distance != 0.0 or closest_point != q1:
        raise ValueError(
            "[Test] Wrong result for point_ball_distance with query point q1"
        )

    q2 = geom.Point3D([0.0, 3.0, 1.0])
    distance, closest_point = geom.point_sphere_distance3D(q2, sphere)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != 1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_sphere_distance with query point q3"
        )
    q2 = geom.Point3D([0.0, 3.0, 1.0])
    distance, closest_point = geom.point_sphere_signed_distance3D(q2, sphere)
    if distance != 1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_sphere_signed_distance with query point q3"
        )
    q2 = geom.Point3D([0.0, 3.0, 1.0])
    distance, closest_point = geom.point_ball_distance3D(q2, sphere)
    if distance != 1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_ball_distance with query point q3"
        )

    q3 = geom.Point3D([0.0, 1.0, 1.0])
    distance, closest_point = geom.point_sphere_distance3D(q3, sphere)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != 1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_sphere_distance with query point q3"
        )
    q3 = geom.Point3D([0.0, 1.0, 1.0])
    distance, closest_point = geom.point_sphere_signed_distance3D(q3, sphere)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != -1.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_sphere_signed__distance with query point q3"
        )
    q3 = geom.Point3D([0.0, 1.0, 1.0])
    distance, closest_point = geom.point_ball_distance3D(q3, sphere)
    if distance != 0.0 or closest_point != q3:
        raise ValueError(
            "[Test] Wrong result for point_ball_distance with query point q3"
        )

    distance, closest_point = geom.point_sphere_distance3D(a, sphere)
    answer = geom.Point3D([2.0, 0.0, 1.0])
    if distance != 2.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_sphere_distance with query point a"
        )
    distance, closest_point = geom.point_sphere_signed_distance3D(a, sphere)
    answer = geom.Point3D([2.0, 0.0, 1.0])
    if distance != -2.0 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_sphere_signed_distance with query point a"
        )
    distance, closest_point = geom.point_ball_distance3D(a, sphere)
    answer = geom.Point3D([2.0, 0.0, 1.0])
    if distance != 0.0 or closest_point != a:
        raise ValueError(
            "[Test] Wrong result for point_ball_distance with query point a"
        )


def test_point_circle_distance():
    a = geom.Point3D([0.0, 0.0, 1.0])
    normal_x = geom.Vector3D([-1.0, 0.0, 0.0])
    normal_z = geom.Vector3D([0.0, 0.0, 1.0])
    plane_x = geom.Plane(normal_x, a)
    plane_z = geom.Plane(normal_z, a)
    circle_x = geom.Circle(plane_x, 2)
    circle_z = geom.Circle(plane_z, 2)

    q1 = geom.Point3D([2.0, 0.0, 1.0])
    distance, closest_point = geom.point_circle_distance3D(q1, circle_x)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != math.sqrt(8) or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_circle_distance with query Point3D q1 and circle_x"
        )

    distance, closest_point = geom.point_circle_distance3D(q1, circle_z)
    if distance != 0 or closest_point != q1:
        raise ValueError(
            "[Test] Wrong result for point_circle_distance with query Point3D q1 and circle_z"
        )

    distance, closest_point = geom.point_circle_signed_distance3D(q1, circle_x)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != -math.sqrt(8) or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_circle_signed_distance with query Point3D q1 and circle_x"
        )

    distance, closest_point = geom.point_circle_signed_distance3D(q1, circle_z)
    if distance != 0 or closest_point != q1:
        raise ValueError(
            "[Test] Wrong result for point_circle_signed_distance with query Point3D q1 and circle_z"
        )

    distance, closest_point = geom.point_disk_distance3D(q1, circle_x)
    answer = geom.Point3D([0.0, 0.0, 1.0])
    if distance != 2 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_disk_distance with query Point3D q1 and circle_x"
        )

    distance, closest_point = geom.point_disk_distance3D(q1, circle_z)
    if distance != 0 or closest_point != q1:
        raise ValueError(
            "[Test] Wrong result for point_disk_distance with query Point3D q1 and circle_z"
        )

    q2 = geom.Point3D([0.0, 3.0, 1.0])
    distance, closest_point = geom.point_circle_distance3D(q2, circle_x)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != 1 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_circle_distance with query Point3D q2 and circle_x"
        )

    distance, closest_point = geom.point_circle_signed_distance3D(q2, circle_x)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != 1 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_circle_signed_distance with query Point3D q2 and circle_x"
        )

    distance, closest_point = geom.point_disk_distance3D(q2, circle_x)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != 1 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_disk_distance with query Point3D q2 and circle_x"
        )

    distance, closest_point = geom.point_circle_distance3D(a, circle_x)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != 2 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_circle_distance with query Point3D a and circle_x"
        )

    distance, closest_point = geom.point_circle_signed_distance3D(a, circle_x)
    answer = geom.Point3D([0.0, 2.0, 1.0])
    if distance != 2 or closest_point != answer:
        raise ValueError(
            "[Test] Wrong result for point_circle_signed_distance with query Point3D a and circle_x"
        )

    distance, closest_point = geom.point_disk_distance3D(a, circle_x)
    if distance != 0 or closest_point != a:
        raise ValueError(
            "[Test] Wrong result for point_disk_distance with query Point3D a and circle_x"
        )


def test_line_triangle_distance():
    a = geom.Point3D([0.0, 0.0, 0.0])
    b = geom.Point3D([2.0, 2.0, 0.0])
    c = geom.Point3D([0.0, 2.0, 1.0])
    d = geom.Point3D([2.0, 0.0, 1.0])
    e = geom.Point3D([0.0, 0.0, 1.0])
    f = geom.Point3D([2.0, 2.0, 1.0])
    g = geom.Point3D([3.0, 3.0, 1.0])
    h = geom.Point3D([5.0, 5.0, 1.0])
    cdg = geom.Triangle3D(c, d, g)
    seg_ab = geom.Segment3D(a, b)
    seg_ef = geom.Segment3D(e, f)
    line_ab = geom.InfiniteLine3D(seg_ab)
    line_ef = geom.InfiniteLine3D(seg_ef)
    zdir = geom.Vector3D([0.0, 0.0, 1.0])
    xdir = geom.Vector3D([1.0, 0.0, 0.0])
    line_bz = geom.InfiniteLine3D(zdir, b)
    line_hx = geom.InfiniteLine3D(xdir, h)

    distance, closest_point0, closest_point1 = geom.line_triangle_distance3D(line_ab, cdg)
    r00 = geom.Point3D([1.0, 1.0, 0.0])
    r01 = geom.Point3D([1.0, 1.0, 1.0])
    if (
        abs(distance - 1) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for line_triangle_distance with query line_ab"
        )

    distance, closest_point0, closest_point1 = geom.line_triangle_distance3D(line_ef, cdg)
    r00 = geom.Point3D([1.0, 1.0, 1.0])
    r01 = geom.Point3D([1.0, 1.0, 1.0])
    if (
        abs(distance) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for line_triangle_distance with query line_ef"
        )

    distance, closest_point0, closest_point1 = geom.line_triangle_distance3D(line_bz, cdg)
    if (
        abs(distance) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(f)
        or not closest_point1.inexact_equal(f)
    ):
        raise ValueError(
            "[Test] Wrong result for line_triangle_distance with query line_bz"
        )

    distance, closest_point0, closest_point1 = geom.line_triangle_distance3D(line_hx, cdg)
    r00 = geom.Point3D([3.0, 5.0, 1.0])
    if (
        abs(distance - 2) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(g)
    ):
        raise ValueError(
            "[Test] Wrong result for line_triangle_distance with query line_hx"
        )


def test_segment_triangle_distance():
    a = geom.Point3D([0.0, 0.0, 0.0])
    b = geom.Point3D([2.0, 2.0, 0.0])
    bplus = geom.Point3D([2.0, 2.0, 2.0])
    bminus = geom.Point3D([2.0, 2.0, -2.0])
    c = geom.Point3D([0.0, 2.0, 1.0])
    d = geom.Point3D([2.0, 0.0, 1.0])
    e = geom.Point3D([0.0, 0.0, 1.0])
    f = geom.Point3D([2.0, 2.0, 1.0])
    g = geom.Point3D([3.0, 3.0, 1.0])
    h = geom.Point3D([5.0, 5.0, 1.0])
    h2 = geom.Point3D([0.0, 5.0, 1.0])
    cdg = geom.Triangle3D(c, d, g)
    seg_ab = geom.Segment3D(a, b)
    seg_ef = geom.Segment3D(e, f)
    seg_bz0 = geom.Segment3D(bplus, b)
    seg_bz1 = geom.Segment3D(bminus, b)
    seg_hx = geom.Segment3D(h2, h)

    distance, closest_point0, closest_point1 = geom.segment_triangle_distance3D(
        seg_ab, cdg
    )
    r00 = geom.Point3D([1.0, 1.0, 0.0])
    r01 = geom.Point3D([1.0, 1.0, 1.0])
    if (
        abs(distance - 1) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_triangle_distance with query seg_ab"
        )

    distance, closest_point0, closest_point1 = geom.segment_triangle_distance3D(
        seg_ef, cdg
    )
    r00 = geom.Point3D([1.0, 1.0, 1.0])
    r01 = geom.Point3D([1.0, 1.0, 1.0])
    if (
        abs(distance) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(r01)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_triangle_distance with query seg_ef"
        )

    distance, closest_point0, closest_point1 = geom.segment_triangle_distance3D(
        seg_bz0, cdg
    )
    if (
        abs(distance) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(f)
        or not closest_point1.inexact_equal(f)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_triangle_distance with query seg_bz0"
        )

    distance, closest_point0, closest_point1 = geom.segment_triangle_distance3D(
        seg_bz1, cdg
    )
    if (
        abs(distance - 1) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(b)
        or not closest_point1.inexact_equal(f)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_triangle_distance with query seg_bz1"
        )

    distance, closest_point0, closest_point1 = geom.segment_triangle_distance3D(
        seg_hx, cdg
    )
    r00 = geom.Point3D([3.0, 5.0, 1.0])
    if (
        abs(distance - 2) > og.GLOBAL_EPSILON
        or not closest_point0.inexact_equal(r00)
        or not closest_point1.inexact_equal(g)
    ):
        raise ValueError(
            "[Test] Wrong result for segment_triangle_distance with query seg_hx"
        )


if __name__ == "__main__":
    test_point_segment_distance()
    test_segment_segment_distance()
    test_segment_line_distance()
    test_point_triangle_distance()
    test_point_plane_distance()
    test_point_sphere_distance()
    test_point_circle_distance()
    test_line_triangle_distance()
    test_segment_triangle_distance()
