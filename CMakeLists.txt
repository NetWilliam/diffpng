project(diffpng)

cmake_minimum_required(VERSION 2.4)

add_executable(
  diffpng diffpng.cpp lodepng.cpp)

install(TARGETS diffpng DESTINATION bin)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#
# Regression tests
#
# Each 'testline' contains a list of two images, and whether they should
# be perceived as the same (PASS), or as different (FAIL).
#
# The images are stored under the 'test' directory and subdirs.
#
# For the 'ctest' to pass, the diffpng program must correctly 
# show whether the images are similar or different.
#
# (The terminology Pass/Fail gets a little confusing.. ctest PASS means
# that diffpng FAILed when it was expected to)
#
# Note that ctest looks at the return values from diffpng's "main()"
# to determine pass (0) or fail (1).

enable_testing()

set(testlines
"FAIL basic/Bug1102605_ref.png basic/Bug1102605.png"
"PASS basic/Bug1471457_ref.png basic/Bug1471457.png"
"PASS basic/cam_mb_ref.png basic/cam_mb.png"
"PASS basic/cam_mb_ref.png basic/cam_mb_ref.png"
"FAIL basic/fish2.png basic/fish1.png"
"FAIL basic/square.png basic/square_scaled.png"
"FAIL basic/Aqsis_vase.png basic/Aqsis_vase_ref.png"
"PASS basic/ossphere_color.png basic/ossphere_color2.png"
"PASS basic/ossphere_mono.png basic/ossphere_mono2.png"
"FAIL basic/ossphere_color.png basic/ossphere_mono.png"
"FAIL basic/ossphere_color2.png basic/ossphere_mono.png"
"FAIL basic/ossphere_color.png basic/ossphere_mono2.png"
"FAIL basic/ossphere_color2.png basic/ossphere_mono2.png"
"FAIL basic/bar_notok.png basic/bar_ok.png"
"FAIL basic/bit_color.png basic/bit_mono.png"
"FAIL basic/blocks_missing.png basic/blocks_ok.png"
"FAIL basic/boxes_missing.png basic/boxes_there.png"
"FAIL basic/camangle_off.png basic/camangle_on.png"
"FAIL basic/camoff2_ok.png basic/camoff2.png"
"FAIL basic/camoff3ok.png basic/camoff3.png"
"FAIL basic/cube_color.png basic/cube_mono.png"
"FAIL basic/diamonds2_gone.png basic/diamonds2_ok.png"
"FAIL basic/diamonds_missing.png basic/diamonds_whole.png"
"FAIL basic/ellipse_missing.png basic/ellipseok.png"
"FAIL basic/gazebo_color.png basic/gazebo_mon.png"
"FAIL basic/greenblock_missing.png basic/greenblock_ok.png"
"FAIL basic/head_color.png basic/head_mono.png"
"FAIL basic/holeblocks_missing.png basic/holeblocks_ok.png"
"FAIL basic/holecube_color.png basic/holecube_mono.png"
"FAIL basic/hole_in_top2_missing.png basic/hole_in_top2.png"
"FAIL basic/hole_in_top_missing.png basic/hole_in_top.png"
"FAIL basic/macaroni2_ok.png basic/macaroni2_white.png"
"FAIL basic/macaroni_missing.png basic/macaroni_whole.png"
"FAIL basic/msphere_color.png basic/msphere_mono.png"
"FAIL basic/objects_missing.png basic/objects_ok.png"
"FAIL basic/orthosphere_color.png basic/orthosphere_distort.png"
"FAIL basic/prism_gone.png basic/prism_ok.png"
"FAIL basic/red_missing.png basic/red_ok.png"
"FAIL basic/shapes_color.png basic/shapes_mono.png"
"FAIL basic/sliver_ok.png basic/sliver_purple.png"
"FAIL basic/sphere_rod_missing.png basic/sphere_rod_ok.png"
"FAIL basic/squares_gone.png basic/squares_ok.png"
"FAIL basic/tinyholes_missing.png basic/tinyholes_ok.png"
"FAIL basic/trench_missing.png basic/trenchok.png"
"FAIL basic/twirls_gone.png basic/twirls_ok.png"

"PASS cgalpngtest/2d-3d-actual.png cgalpngtest/2d-3d-expected.png"
"PASS cgalpngtest/advance_intersection-actual.png cgalpngtest/advance_intersection-expected.png"
"PASS cgalpngtest/arc-actual.png cgalpngtest/arc-expected.png"
"PASS cgalpngtest/assign-tests-actual.png cgalpngtest/assign-tests-expected.png"
"PASS cgalpngtest/background-modifier-actual.png cgalpngtest/background-modifier-expected.png"
"PASS cgalpngtest/camera-tests-actual.png cgalpngtest/camera-tests-expected.png"
"PASS cgalpngtest/child-child-test-actual.png cgalpngtest/child-child-test-expected.png"
"PASS cgalpngtest/child-tests-actual.png cgalpngtest/child-tests-expected.png"
"PASS cgalpngtest/chopped_blocks-actual.png cgalpngtest/chopped_blocks-expected.png"
"PASS cgalpngtest/circle-actual.png cgalpngtest/circle-expected.png"
"PASS cgalpngtest/circle-advanced-expected.png cgalpngtest/circle-advanced-actual.png"
"PASS cgalpngtest/circle-double-expected.png cgalpngtest/circle-double-actual.png"
"PASS cgalpngtest/circle-small-actual.png cgalpngtest/circle-small-expected.png"
"PASS cgalpngtest/circle-tests-actual.png cgalpngtest/circle-tests-expected.png"
"PASS cgalpngtest/color-tests-actual.png cgalpngtest/color-tests-expected.png"
"PASS cgalpngtest/control-hull-dimension-actual.png cgalpngtest/control-hull-dimension-expected.png"
"PASS cgalpngtest/cube-tests-actual.png cgalpngtest/cube-tests-expected.png"
"FAIL cgalpngtest/cut_view-actual.png cgalpngtest/cut_view-expected.png"
"PASS cgalpngtest/cylinder-diameter-tests-actual.png cgalpngtest/cylinder-diameter-tests-expected.png"
"PASS cgalpngtest/cylinder-tests-actual.png cgalpngtest/cylinder-tests-expected.png"
"PASS cgalpngtest/demo_cut-actual.png cgalpngtest/demo_cut-expected.png"
"PASS cgalpngtest/difference-2d-tests-actual.png cgalpngtest/difference-2d-tests-expected.png"
"FAIL cgalpngtest/difference-actual.png cgalpngtest/difference-expected.png"
"PASS cgalpngtest/difference_cube-expected.png cgalpngtest/difference_cube-actual.png"
"PASS cgalpngtest/difference_sphere-actual.png cgalpngtest/difference_sphere-expected.png"
"PASS cgalpngtest/difference-tests-actual.png cgalpngtest/difference-tests-expected.png"
"PASS cgalpngtest/disable-modifier-actual.png cgalpngtest/disable-modifier-expected.png"
"PASS cgalpngtest/ellipse-actual.png cgalpngtest/ellipse-expected.png"
"PASS cgalpngtest/ellipse-arc-expected.png cgalpngtest/ellipse-arc-actual.png"
"PASS cgalpngtest/ellipse-arc-rot-expected.png cgalpngtest/ellipse-arc-rot-actual.png"
"PASS cgalpngtest/ellipse-reverse-actual.png cgalpngtest/ellipse-reverse-expected.png"
"PASS cgalpngtest/ellipse-rot-actual.png cgalpngtest/ellipse-rot-expected.png"
"PASS cgalpngtest/empty-shape-tests-actual.png cgalpngtest/empty-shape-tests-expected.png"
"PASS cgalpngtest/fan_view-actual.png cgalpngtest/fan_view-expected.png"
"PASS cgalpngtest/fence-actual.png cgalpngtest/fence-expected.png"
"PASS cgalpngtest/flat_body-actual.png cgalpngtest/flat_body-expected.png"
"PASS cgalpngtest/for-nested-tests-actual.png cgalpngtest/for-nested-tests-expected.png"
"PASS cgalpngtest/for-tests-actual.png cgalpngtest/for-tests-expected.png"
"PASS cgalpngtest/fractal-actual.png cgalpngtest/fractal-expected.png"
"PASS cgalpngtest/highlight-modifier-actual.png cgalpngtest/highlight-modifier-expected.png"
"PASS cgalpngtest/hull2-tests-actual.png cgalpngtest/hull2-tests-expected.png"
"PASS cgalpngtest/hull3-tests-actual.png cgalpngtest/hull3-tests-expected.png"
"PASS cgalpngtest/ifelse-tests-actual.png cgalpngtest/ifelse-tests-expected.png"
"PASS cgalpngtest/import_dxf-tests-actual.png cgalpngtest/import_dxf-tests-expected.png"
"PASS cgalpngtest/import-empty-tests-actual.png cgalpngtest/import-empty-tests-expected.png"
"PASS cgalpngtest/import_stl-tests-actual.png cgalpngtest/import_stl-tests-expected.png"
"PASS cgalpngtest/include-tests-actual.png cgalpngtest/include-tests-expected.png"
"PASS cgalpngtest/intersecting-actual.png cgalpngtest/intersecting-expected.png"
"PASS cgalpngtest/intersection2-tests-actual.png cgalpngtest/intersection2-tests-expected.png"
"PASS cgalpngtest/intersection-actual.png cgalpngtest/intersection-expected.png"
"PASS cgalpngtest/intersection_for-tests-actual.png cgalpngtest/intersection_for-tests-expected.png"
"PASS cgalpngtest/intersection-tests-actual.png cgalpngtest/intersection-tests-expected.png"
"FAIL cgalpngtest/issue112-actual.png cgalpngtest/issue112-expected.png"

"FAIL cgalpngtest/issue495b-actual.png cgalpngtest/issue495b-expected.png"
"PASS cgalpngtest/issue495-actual.png cgalpngtest/issue495-expected.png"
"PASS cgalpngtest/issue541-actual.png cgalpngtest/issue541-expected.png"
"PASS cgalpngtest/issue578-actual.png cgalpngtest/issue578-actual.png"
"PASS cgalpngtest/issue578b-expected.png cgalpngtest/issue578b-expected.png"
"PASS cgalpngtest/issue584-actual.png cgalpngtest/issue584-expected.png"
"PASS cgalpngtest/issue585-actual.png cgalpngtest/issue585-expected.png"
"FAIL cgalpngtest/issue591-actual.png cgalpngtest/issue591-expected.png"
"PASS cgalpngtest/issue612-actual.png cgalpngtest/issue612-expected.png"
"PASS cgalpngtest/issue666-actual.png cgalpngtest/issue666-expected.png"
"FAIL cgalpngtest/issue802-actual.png cgalpngtest/issue802-expected.png"

"PASS cgalpngtest/iteration-actual.png cgalpngtest/iteration-expected.png"
"FAIL cgalpngtest/linear_extrude-scale-zero-tests-actual.png cgalpngtest/linear_extrude-scale-zero-tests-expected.png"
"PASS cgalpngtest/linear_extrude-tests-actual.png cgalpngtest/linear_extrude-tests-expected.png"
"PASS cgalpngtest/localfiles-compatibility-test-actual.png cgalpngtest/localfiles-compatibility-test-expected.png"
"PASS cgalpngtest/localfiles-test-actual.png cgalpngtest/localfiles-test-expected.png"
"PASS cgalpngtest/lwpolyline2-actual.png cgalpngtest/lwpolyline2-expected.png"
"PASS cgalpngtest/lwpolyline-actual.png cgalpngtest/lwpolyline-closed-actual.png"
"PASS cgalpngtest/lwpolyline-closed-expected.png cgalpngtest/lwpolyline-expected.png"
"PASS cgalpngtest/minkowski2-hole-tests-actual.png cgalpngtest/minkowski2-hole-tests-expected.png"
"PASS cgalpngtest/minkowski2-tests-actual.png cgalpngtest/minkowski2-tests-expected.png"
"PASS cgalpngtest/minkowski3-tests-actual.png cgalpngtest/minkowski3-tests-expected.png"
"PASS cgalpngtest/module-recursion-actual.png cgalpngtest/module-recursion-expected.png"
"PASS cgalpngtest/modulevariables-actual.png cgalpngtest/modulevariables-expected.png"
"PASS cgalpngtest/multiple-layers-actual.png cgalpngtest/multiple-layers-expected.png"
"PASS cgalpngtest/nothing-decimal-comma-separated-actual.png cgalpngtest/nothing-decimal-comma-separated-expected.png"
"PASS cgalpngtest/null-polygons-actual.png cgalpngtest/null-polygons-expected.png"
"PASS cgalpngtest/offset-actual.png cgalpngtest/offset-expected.png"
"PASS cgalpngtest/offset-tests-actual.png cgalpngtest/offset-tests-expected.png"
"PASS cgalpngtest/polygon8-actual.png cgalpngtest/polygon8-expected.png"
"PASS cgalpngtest/polygon-concave-actual.png cgalpngtest/polygon-concave-expected.png"
"PASS cgalpngtest/polygon-concave-hole-actual.png cgalpngtest/polygon-concave-hole-expected.png"
"PASS cgalpngtest/polygon-concave-simple-actual.png cgalpngtest/polygon-concave-simple-expected.png"
"PASS cgalpngtest/polygon-holes-touch-actual.png cgalpngtest/polygon-holes-touch-expected.png"
"PASS cgalpngtest/polygon-intersect-actual.png cgalpngtest/polygon-intersect-expected.png"
"PASS cgalpngtest/polygon-many-holes-actual.png cgalpngtest/polygon-many-holes-expected.png"
"PASS cgalpngtest/polygon-mesh-actual.png cgalpngtest/polygon-mesh-expected.png"
"PASS cgalpngtest/polygon-overlap-actual.png cgalpngtest/polygon-overlap-expected.png"
"PASS cgalpngtest/polygon-riser-actual.png cgalpngtest/polygon-riser-expected.png"
"PASS cgalpngtest/polygons-actual.png cgalpngtest/polygons-expected.png"
"PASS cgalpngtest/polygon-self-intersect-expected.png cgalpngtest/polygon-self-intersect-actual.png"
"PASS cgalpngtest/polygon-tests-actual.png cgalpngtest/polygon-tests-expected.png"
"PASS cgalpngtest/polyhedron-actual.png cgalpngtest/polyhedron-expected.png"
"PASS cgalpngtest/polyhedron-nonplanar-tests-actual.png cgalpngtest/polyhedron-nonplanar-tests-expected.png"
"PASS cgalpngtest/polyhedron-tests-actual.png cgalpngtest/polyhedron-tests-expected.png"
"PASS cgalpngtest/primitive-inf-tests-actual.png cgalpngtest/primitive-inf-tests-expected.png"
"PASS cgalpngtest/projection-cut-tests-actual.png cgalpngtest/projection-cut-tests-expected.png"
"PASS cgalpngtest/projection-extrude-tests-actual.png cgalpngtest/projection-extrude-tests-expected.png"
"PASS cgalpngtest/projection-tests-actual.png cgalpngtest/projection-tests-expected.png"
"PASS cgalpngtest/render-2d-tests-actual.png cgalpngtest/render-2d-tests-expected.png"
"PASS cgalpngtest/render-tests-actual.png cgalpngtest/render-tests-expected.png"
"PASS cgalpngtest/resize-2d-tests-actual.png cgalpngtest/resize-2d-tests-expected.png"
"PASS cgalpngtest/resize-tests-actual.png cgalpngtest/resize-tests-expected.png"
"PASS cgalpngtest/root-modifier-actual.png cgalpngtest/root-modifier-expected.png"
"PASS cgalpngtest/rotate-empty-bbox-actual.png cgalpngtest/rotate-empty-bbox-expected.png"
"PASS cgalpngtest/rotate_extrude-tests-actual.png cgalpngtest/rotate_extrude-tests-expected.png"
"PASS cgalpngtest/rounded_box-actual.png cgalpngtest/rounded_box-expected.png"
"PASS cgalpngtest/scale2D-tests-actual.png cgalpngtest/scale2D-tests-expected.png"
"PASS cgalpngtest/scale3D-tests-actual.png cgalpngtest/scale3D-tests-expected.png"
"PASS cgalpngtest/search-actual.png cgalpngtest/search-expected.png"
"PASS cgalpngtest/sphere-actual.png cgalpngtest/sphere-expected.png"
"PASS cgalpngtest/sphere-tests-actual.png cgalpngtest/sphere-tests-expected.png"
"PASS cgalpngtest/square-tests-actual.png cgalpngtest/square-tests-expected.png"
"PASS cgalpngtest/surface-actual.png cgalpngtest/surface-expected.png"
"PASS cgalpngtest/surface-png-image2-tests-actual.png cgalpngtest/surface-png-image2-tests-expected.png"
"PASS cgalpngtest/surface-png-image3-tests-actual.png cgalpngtest/surface-png-image3-tests-expected.png"
"PASS cgalpngtest/surface-png-image-tests-actual.png cgalpngtest/surface-png-image-tests-expected.png"
"PASS cgalpngtest/surface-simple-actual.png cgalpngtest/surface-simple-expected.png"
"PASS cgalpngtest/surface-tests-actual.png cgalpngtest/surface-tests-expected.png"
"PASS cgalpngtest/text-actual.png cgalpngtest/text-expected.png"
"PASS cgalpngtest/text-font-direction-tests-actual.png cgalpngtest/text-font-direction-tests-expected.png"
"PASS cgalpngtest/text-font-simple-tests-actual.png cgalpngtest/text-font-simple-tests-expected.png"
"FAIL cgalpngtest/text-font-tests-actual.png cgalpngtest/text-font-tests-expected.png"
"PASS cgalpngtest/text-search-test-actual.png cgalpngtest/text-search-test-expected.png"
"PASS cgalpngtest/transform-insert-actual.png cgalpngtest/transform-insert-expected.png"
"PASS cgalpngtest/transform-nan-inf-tests-actual.png cgalpngtest/transform-nan-inf-tests-expected.png"
"PASS cgalpngtest/transform-tests-actual.png cgalpngtest/transform-tests-expected.png"
"PASS cgalpngtest/translate-actual.png cgalpngtest/translate-expected.png"
"PASS cgalpngtest/translation-actual.png cgalpngtest/translation-expected.png"
"PASS cgalpngtest/triangle-with-duplicate-vertex-actual.png cgalpngtest/triangle-with-duplicate-vertex-expected.png"
"PASS cgalpngtest/tripod-actual.png cgalpngtest/tripod-expected.png"
"PASS cgalpngtest/union-actual.png cgalpngtest/union-expected.png"
"PASS cgalpngtest/union-coincident-test-actual.png cgalpngtest/union-coincident-test-expected.png"
"PASS cgalpngtest/union-tests-actual.png cgalpngtest/union-tests-expected.png"
"PASS cgalpngtest/use-tests-actual.png cgalpngtest/use-tests-expected.png"
"FAIL cgalpngtest/text-font-alignment-tests-actual.png cgalpngtest/text-font-alignment-tests-expected.png"
"FAIL cgalpngtest/rotate_extrude_dxf-tests-actual.png cgalpngtest/rotate_extrude_dxf-tests-expected.png"

"PASS opencsgtest/2d-3d-actual.png opencsgtest/2d-3d-expected.png"
"PASS opencsgtest/advance_intersection-actual.png opencsgtest/advance_intersection-expected.png"
"PASS opencsgtest/arc-actual.png opencsgtest/arc-expected.png"
"PASS opencsgtest/assign-tests-actual.png opencsgtest/assign-tests-expected.png"
"PASS opencsgtest/background-modifier-actual.png opencsgtest/background-modifier-expected.png"
"PASS opencsgtest/camera-tests-actual.png opencsgtest/camera-tests-expected.png"
"PASS opencsgtest/child-child-test-actual.png opencsgtest/child-child-test-expected.png"
"PASS opencsgtest/child-tests-actual.png opencsgtest/child-tests-expected.png"
"PASS opencsgtest/chopped_blocks-actual.png opencsgtest/chopped_blocks-expected.png"
"PASS opencsgtest/circle-advanced-actual.png opencsgtest/circle-advanced-expected.png"
"PASS opencsgtest/circle-double-actual.png opencsgtest/circle-double-expected.png"
"PASS opencsgtest/circle-small-actual.png opencsgtest/circle-small-expected.png"
"PASS opencsgtest/circle-tests-actual.png opencsgtest/circle-tests-expected.png"
"PASS opencsgtest/color-tests-actual.png opencsgtest/color-tests-expected.png"
"PASS opencsgtest/control-hull-dimension-actual.png opencsgtest/control-hull-dimension-expected.png"
"PASS opencsgtest/cube-tests-actual.png opencsgtest/cube-tests-expected.png"
"FAIL opencsgtest/cut_view-actual.png opencsgtest/cut_view-expected.png"
"PASS opencsgtest/cylinder-diameter-tests-actual.png opencsgtest/cylinder-diameter-tests-expected.png"
"PASS opencsgtest/cylinder-tests-actual.png opencsgtest/cylinder-tests-expected.png"
"PASS opencsgtest/demo_cut-actual.png opencsgtest/demo_cut-expected.png"
"PASS opencsgtest/difference-2d-tests-actual.png opencsgtest/difference-2d-tests-expected.png"
"PASS opencsgtest/difference_cube-actual.png opencsgtest/difference_cube-expected.png"
"PASS opencsgtest/difference_sphere-actual.png opencsgtest/difference_sphere-expected.png"
"PASS opencsgtest/difference-tests-actual.png opencsgtest/difference-tests-expected.png"
"PASS opencsgtest/disable-modifier-actual.png opencsgtest/disable-modifier-expected.png"
"PASS opencsgtest/ellipse-arc-actual.png opencsgtest/ellipse-arc-expected.png"
"PASS opencsgtest/ellipse-arc-rot-actual.png opencsgtest/ellipse-arc-rot-expected.png"
"PASS opencsgtest/ellipse-actual.png opencsgtest/ellipse-expected.png"
"PASS opencsgtest/ellipse-reverse-actual.png opencsgtest/ellipse-reverse-expected.png"
"PASS opencsgtest/ellipse-rot-actual.png opencsgtest/ellipse-rot-expected.png"
"PASS opencsgtest/empty-shape-tests-actual.png opencsgtest/empty-shape-tests-expected.png"
"FAIL opencsgtest/fan_view-actual.png opencsgtest/fan_view-expected.png"
"PASS opencsgtest/fence-actual.png opencsgtest/fence-expected.png"
"PASS opencsgtest/flat_body-actual.png opencsgtest/flat_body-expected.png"
"PASS opencsgtest/for-nested-tests-actual.png opencsgtest/for-nested-tests-expected.png"
"PASS opencsgtest/for-tests-actual.png opencsgtest/for-tests-expected.png"
"PASS opencsgtest/fractal-actual.png opencsgtest/fractal-expected.png"
"PASS opencsgtest/highlight-and-background-modifier-actual.png opencsgtest/highlight-and-background-modifier-expected.png"
"PASS opencsgtest/highlight-modifier-actual.png opencsgtest/highlight-modifier-expected.png"
"PASS opencsgtest/hull2-tests-actual.png opencsgtest/hull2-tests-expected.png"
"PASS opencsgtest/hull3-tests-actual.png opencsgtest/hull3-tests-expected.png"
"PASS opencsgtest/ifelse-tests-actual.png opencsgtest/ifelse-tests-expected.png"
"PASS opencsgtest/import_dxf-tests-actual.png opencsgtest/import_dxf-tests-expected.png"
"PASS opencsgtest/import-empty-tests-actual.png opencsgtest/import-empty-tests-expected.png"
"PASS opencsgtest/import_stl-tests-actual.png opencsgtest/import_stl-tests-expected.png"
"PASS opencsgtest/include-tests-actual.png opencsgtest/include-tests-expected.png"
"PASS opencsgtest/intersection2-tests-actual.png opencsgtest/intersection2-tests-expected.png"
"PASS opencsgtest/intersection-actual.png opencsgtest/intersection-expected.png"
"PASS opencsgtest/intersection-prune-test-actual.png opencsgtest/intersection-prune-test-expected.png"
"PASS opencsgtest/intersection-tests-actual.png opencsgtest/intersection-tests-expected.png"
"PASS opencsgtest/issue112-actual.png opencsgtest/issue112-expected.png"
"FAIL opencsgtest/intersecting-actual.png opencsgtest/intersecting-expected.png"
"FAIL opencsgtest/intersection_for-tests-actual.png opencsgtest/intersection_for-tests-expected.png"
"FAIL opencsgtest/difference-actual.png opencsgtest/difference-expected.png"

"PASS opencsgtest/issue495b-actual.png opencsgtest/issue495b-expected.png"
"FAIL opencsgtest/issue495-expected.png opencsgtest/issue495-actual.png"
"PASS opencsgtest/issue541-actual.png opencsgtest/issue541-expected.png"
"PASS opencsgtest/issue578-actual.png opencsgtest/issue578-expected.png"
"PASS opencsgtest/issue578b-actual.png opencsgtest/issue578b-expected.png"
"FAIL opencsgtest/issue584-actual.png opencsgtest/issue584-expected.png"
"PASS opencsgtest/issue585-actual.png opencsgtest/issue585-expected.png"
"PASS opencsgtest/issue591-actual.png opencsgtest/issue591-expected.png"
"PASS opencsgtest/issue612-actual.png opencsgtest/issue612-expected.png"
"FAIL opencsgtest/issue666-actual.png opencsgtest/issue666-expected.png"
"PASS opencsgtest/issue802-actual.png opencsgtest/issue802-expected.png"

"PASS opencsgtest/iteration-actual.png opencsgtest/iteration-expected.png"
"PASS opencsgtest/linear_extrude-scale-zero-tests-actual.png opencsgtest/linear_extrude-scale-zero-tests-expected.png"
"PASS opencsgtest/linear_extrude-tests-actual.png opencsgtest/linear_extrude-tests-expected.png"
"PASS opencsgtest/localfiles-compatibility-test-actual.png opencsgtest/localfiles-compatibility-test-expected.png"
"PASS opencsgtest/localfiles-test-actual.png opencsgtest/localfiles-test-expected.png"
"PASS opencsgtest/lwpolyline2-actual.png opencsgtest/lwpolyline2-expected.png"
"PASS opencsgtest/lwpolyline-closed-actual.png opencsgtest/lwpolyline-closed-expected.png"
"PASS opencsgtest/lwpolyline-actual.png opencsgtest/lwpolyline-expected.png"
"PASS opencsgtest/minkowski2-hole-tests-actual.png opencsgtest/minkowski2-hole-tests-expected.png"
"PASS opencsgtest/minkowski2-tests-actual.png opencsgtest/minkowski2-tests-expected.png"
"PASS opencsgtest/minkowski3-tests-actual.png opencsgtest/minkowski3-tests-expected.png"
"PASS opencsgtest/module-recursion-actual.png opencsgtest/module-recursion-expected.png"
"PASS opencsgtest/modulevariables-actual.png opencsgtest/modulevariables-expected.png"
"PASS opencsgtest/multiple-layers-actual.png opencsgtest/multiple-layers-expected.png"
"PASS opencsgtest/nothing-decimal-comma-separated-actual.png opencsgtest/nothing-decimal-comma-separated-expected.png"
"PASS opencsgtest/null-polygons-actual.png opencsgtest/null-polygons-expected.png"
"PASS opencsgtest/offset-actual.png opencsgtest/offset-expected.png"
"PASS opencsgtest/offset-tests-actual.png opencsgtest/offset-tests-expected.png"
"PASS opencsgtest/polygon8-actual.png opencsgtest/polygon8-expected.png"
"PASS opencsgtest/polygon-concave-actual.png opencsgtest/polygon-concave-expected.png"
"PASS opencsgtest/polygon-concave-hole-actual.png opencsgtest/polygon-concave-hole-expected.png"
"PASS opencsgtest/polygon-concave-simple-actual.png opencsgtest/polygon-concave-simple-expected.png"
"PASS opencsgtest/polygon-holes-touch-actual.png opencsgtest/polygon-holes-touch-expected.png"
"PASS opencsgtest/polygon-intersect-actual.png opencsgtest/polygon-intersect-expected.png"
"PASS opencsgtest/polygon-many-holes-actual.png opencsgtest/polygon-many-holes-expected.png"
"PASS opencsgtest/polygon-mesh-actual.png opencsgtest/polygon-mesh-expected.png"
"PASS opencsgtest/polygon-overlap-actual.png opencsgtest/polygon-overlap-expected.png"
"PASS opencsgtest/polygon-riser-actual.png opencsgtest/polygon-riser-expected.png"
"PASS opencsgtest/polygon-self-intersect-actual.png opencsgtest/polygon-self-intersect-expected.png"
"PASS opencsgtest/polygons-actual.png opencsgtest/polygons-expected.png"
"PASS opencsgtest/polygon-tests-actual.png opencsgtest/polygon-tests-expected.png"
"PASS opencsgtest/polyhedron-actual.png opencsgtest/polyhedron-expected.png"
"PASS opencsgtest/polyhedron-nonplanar-tests-actual.png opencsgtest/polyhedron-nonplanar-tests-expected.png"
"PASS opencsgtest/polyhedron-tests-actual.png opencsgtest/polyhedron-tests-expected.png"
"PASS opencsgtest/primitive-inf-tests-actual.png opencsgtest/primitive-inf-tests-expected.png"
"PASS opencsgtest/projection-cut-tests-actual.png opencsgtest/projection-cut-tests-expected.png"
"PASS opencsgtest/projection-extrude-tests-actual.png opencsgtest/projection-extrude-tests-expected.png"
"PASS opencsgtest/projection-tests-actual.png opencsgtest/projection-tests-expected.png"
"PASS opencsgtest/render-2d-tests-actual.png opencsgtest/render-2d-tests-expected.png"
"PASS opencsgtest/render-tests-actual.png opencsgtest/render-tests-expected.png"
"PASS opencsgtest/resize-2d-tests-actual.png opencsgtest/resize-2d-tests-expected.png"
"PASS opencsgtest/resize-tests-actual.png opencsgtest/resize-tests-expected.png"
"PASS opencsgtest/root-modifier-actual.png opencsgtest/root-modifier-expected.png"
"PASS opencsgtest/rotate-empty-bbox-actual.png opencsgtest/rotate-empty-bbox-expected.png"
"FAIL opencsgtest/rotate_extrude_dxf-tests-actual.png opencsgtest/rotate_extrude_dxf-tests-expected.png"
"PASS opencsgtest/rotate_extrude-tests-actual.png opencsgtest/rotate_extrude-tests-expected.png"
"PASS opencsgtest/rounded_box-actual.png opencsgtest/rounded_box-expected.png"
"PASS opencsgtest/scale2D-tests-actual.png opencsgtest/scale2D-tests-expected.png"
"PASS opencsgtest/scale3D-tests-actual.png opencsgtest/scale3D-tests-expected.png"
"PASS opencsgtest/search-actual.png opencsgtest/search-expected.png"
"PASS opencsgtest/sphere-actual.png opencsgtest/sphere-expected.png"
"PASS opencsgtest/sphere-tests-actual.png opencsgtest/sphere-tests-expected.png"
"PASS opencsgtest/square-tests-actual.png opencsgtest/square-tests-expected.png"
"PASS opencsgtest/surface-actual.png opencsgtest/surface-expected.png"
"PASS opencsgtest/surface-png-image2-tests-actual.png opencsgtest/surface-png-image2-tests-expected.png"
"PASS opencsgtest/surface-png-image3-tests-actual.png opencsgtest/surface-png-image3-tests-expected.png"
"PASS opencsgtest/surface-png-image-tests-actual.png opencsgtest/surface-png-image-tests-expected.png"
"PASS opencsgtest/surface-simple-actual.png opencsgtest/surface-simple-expected.png"
"PASS opencsgtest/surface-tests-actual.png opencsgtest/surface-tests-expected.png"
"PASS opencsgtest/testcolornames-actual.png opencsgtest/testcolornames-expected.png"
"PASS opencsgtest/text-actual.png opencsgtest/text-expected.png"
"PASS opencsgtest/text-font-alignment-tests-actual.png opencsgtest/text-font-alignment-tests-expected.png"
"PASS opencsgtest/text-font-direction-tests-actual.png opencsgtest/text-font-direction-tests-expected.png"
"PASS opencsgtest/text-font-simple-tests-actual.png opencsgtest/text-font-simple-tests-expected.png"
"PASS opencsgtest/text-font-tests-actual.png opencsgtest/text-font-tests-expected.png"
"PASS opencsgtest/text-search-test-actual.png opencsgtest/text-search-test-expected.png"
"PASS opencsgtest/transform-insert-actual.png opencsgtest/transform-insert-expected.png"
"PASS opencsgtest/transform-nan-inf-tests-actual.png opencsgtest/transform-nan-inf-tests-expected.png"
"PASS opencsgtest/transform-tests-actual.png opencsgtest/transform-tests-expected.png"
"PASS opencsgtest/translate-actual.png opencsgtest/translate-expected.png"
"PASS opencsgtest/translation-actual.png opencsgtest/translation-expected.png"
"PASS opencsgtest/triangle-with-duplicate-vertex-actual.png opencsgtest/triangle-with-duplicate-vertex-expected.png"
"FAIL opencsgtest/tripod-actual.png opencsgtest/tripod-expected.png"
"PASS opencsgtest/union-actual.png opencsgtest/union-expected.png"
"PASS opencsgtest/union-coincident-test-expected.png opencsgtest/union-coincident-test-actual.png"
"PASS opencsgtest/union-tests-actual.png opencsgtest/union-tests-expected.png"
"PASS opencsgtest/use-tests-actual.png opencsgtest/use-tests-expected.png"
)

#
# when under ./matches, file1.png, file2.png should match
# when under ./differs, file1.png, file2.png should not match
#
# for each file pair (file1.png / file2.png) set up a 'test line'
# that is formatted with three entires. Here are two examples:
#
# FAIL differs/sphere1.png differs/sphere2.png
# PASS matches/cube1.png matches/cube2.png
#
# Thus, when diffpng runs with input cube1, cube2, it should PASS (they match)
# and when diffpng runs with input sphere1, sphere2, it should FAIL (dont match)
#
# This can be confusing, because successfully determining whether the images
# match or not is considered PASS in ctest. 
#
# Todo: fix terminology of diffpng to be MATCHES or DIFFERS

file(GLOB differspngs "${PROJECT_SOURCE_DIR}/test/differs/*1.png")
file(GLOB matchespngs "${PROJECT_SOURCE_DIR}/test/matches/*1.png")
#message(STATUS "differs--> ${failpngs}")

function(setup_testline filename1 test_or_fail)
  string(REPLACE "${PROJECT_SOURCE_DIR}/test" "" pngfile ${pngfile})
  set(filename1 "${pngfile}")
  string(REPLACE "1.png" "2.png" filename2 ${filename1})
  set(testline "${test_or_fail} ${filename1} ${filename2}")
  # message(STATUS "testline--> ${testline}")
  set(testlines "${testlines};${testline}" PARENT_SCOPE)
endfunction(setup_testline)

foreach(pngfile ${differspngs})
  setup_testline(${pngfile} "FAIL")
endforeach()
foreach(pngfile ${matchespngs})
  setup_testline(${pngfile} "PASS")
endforeach()

# message(STATUS "xxxxxx ${testlines}")

# store our --output generated 'difference' images.
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/imagediffs")

set(counter ".")
foreach(testline ${testlines})

  # message(STATUS "Processing testline: ${testline}")
  string(REGEX REPLACE "(.*) .* .*" "\\1" expected_result ${testline})
  string(REGEX REPLACE ".* (.*) .*" "\\1" img1 ${testline})
  string(REGEX REPLACE ".* .* (.*)" "\\1" img2 ${testline})
  #message(STATUS "img1 ${img1}")
  #message(STATUS "img2 ${img2}")
  #message(STATUS "expected_result ${expected_result}")

  set(testname "${img1}_vs_${img2}")
  string(REGEX REPLACE "\\.png" "" testname ${testname})
  string(REGEX REPLACE "/" "-" testname ${testname})
  string(REGEX REPLACE "^-" "" testname ${testname})
  string(REGEX REPLACE "_-" "_" testname ${testname})
  string(REGEX REPLACE "[^A-Za-z0-9_-]+" "" testname ${testname})

  set(img1 "${PROJECT_SOURCE_DIR}/test/${img1}")
  set(img2 "${PROJECT_SOURCE_DIR}/test/${img2}")

  if(${expected_result} STREQUAL "FAIL")
    set(fliparg "--flipexit")
  else()
    set(fliparg "")
  endif()

  set(diffimg "${PROJECT_BINARY_DIR}/imagediffs/${testname}.png")
  add_test(NAME ${testname} COMMAND "${PROJECT_BINARY_DIR}/diffpng" "${img1}" "${img2}" ${fliparg} "--output" "${diffimg}")
  set(counter "${counter}.")

endforeach()
string(LENGTH ${counter} numtests)
message(STATUS "Tests added: " ${numtests})

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS "diffpng")
