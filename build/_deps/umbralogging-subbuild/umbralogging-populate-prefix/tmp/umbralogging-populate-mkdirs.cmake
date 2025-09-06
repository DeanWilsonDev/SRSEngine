# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-src")
  file(MAKE_DIRECTORY "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-src")
endif()
file(MAKE_DIRECTORY
  "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-build"
  "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-subbuild/umbralogging-populate-prefix"
  "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-subbuild/umbralogging-populate-prefix/tmp"
  "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-subbuild/umbralogging-populate-prefix/src/umbralogging-populate-stamp"
  "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-subbuild/umbralogging-populate-prefix/src"
  "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-subbuild/umbralogging-populate-prefix/src/umbralogging-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-subbuild/umbralogging-populate-prefix/src/umbralogging-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/deanwilson/development/projects/srs-app/build/_deps/umbralogging-subbuild/umbralogging-populate-prefix/src/umbralogging-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
