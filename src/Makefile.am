bin_PROGRAMS = testConjecture output_nc_inc_rot rhochi testMI testRhoChiTransform

h_sources = graph.hpp invariants.hpp transformations.hpp graph6.hpp

output_nc_inc_rot_SOURCES = $(h_sources) output_nc_inc_rot.cpp
output_nc_inc_rot_LDADD = -lnauty

rhochi_SOURCES = $(h_sources) rhochi.cpp
testMI_SOURCES = $(h_sources) testUtil.hpp minimalIncluded.hpp testMI.cpp
testRhoChiTransform_SOURCES = $(h_sources) testUtil.hpp testRhoChiTransform.cpp
testConjecture_SOURCES = $(h_sources) testUtil.hpp testConjecture.cpp

check_PROGRAMS = testsBoost

testsBoost_SOURCES = $(h_sources) testsBoost.cpp

AM_CXXFLAGS = -std=c++11 -pg
