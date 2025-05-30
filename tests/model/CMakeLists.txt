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

add_geode_test(
    SOURCE "test-brep.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
    ESSENTIAL
)
add_geode_test(
    SOURCE "test-component-mesh-edges.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-component-mesh-polygons.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-component-mesh-polyhedra.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-convert-brep.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-convert-model-meshes.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-convert-to-mesh.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
    ESSENTIAL
)
add_geode_test(
    SOURCE "test-model-component-filter.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-model-concatener.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-model-creator.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-model-crs.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-model-mapping.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-ray-tracing-helpers.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-relationships.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-section.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::model
)
add_geode_test(
    SOURCE "test-surface-radial-sort.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::model
)

add_geode_test(
    SOURCE "test-vertex-identifier.cpp"
    DEPENDENCIES
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::model
)
