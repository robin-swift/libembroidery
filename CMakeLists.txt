cmake_minimum_required(VERSION 3.5)

project(libembroidery VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

option( EMBROIDERY_BUILD_SHARED_LIBS "Build shared library." ON )
option( EMBROIDERY_BUILD_CLI "Build embroider command line tool." ON )
option( EMBROIDERY_TESTING "Run tests." ON )

if (WIN32)
#add_compile_options(
#    -O2
#)
else (WIN32)
add_compile_options(
    -g
    -O2
    -fPIC
    -std=c99
    -Wall
    -Wextra
#    -Werror
)
endif (WIN32)

set(LIBRARY_SRC
	src/pattern.c
	src/compress.c
	src/formats.c
	src/geometry.c
	src/script.c
	src/testing.c
	src/data.c
	src/designs.c
	src/embroidery.h

	extern/mpc/mpc.c
	extern/mpc/mpc.h
)

add_library(embroidery_static STATIC ${LIBRARY_SRC})

if(EMBROIDERY_BUILD_SHARED_LIBS)
add_library(embroidery SHARED ${LIBRARY_SRC})

target_compile_definitions(embroidery PUBLIC LIBEMBROIDERY_SHARED)
endif()

if(EMBROIDERY_BUILD_CLI)
add_executable(embroider src/embroider.c)

target_link_libraries(embroider PRIVATE embroidery_static)

if (WIN32)
else (WIN32)
target_link_libraries(embroider PRIVATE m)
endif (WIN32)
endif()

if(EMBROIDERY_BUILD_SHARED_LIBS)
if(WIN32)

# TODO: Test this.
# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Install.html

install(
    FILES src/embroidery.h
    DESTINATION "<SystemDrive>/Program Files/<Project Name>"
)

install(
    TARGETS
       embroidery
       embroidery_static
       embroider
    EXPORT embroidery
    LIBRARY DESTINATION "<SystemDrive>/Program Files/<Project Name>"
    ARCHIVE DESTINATION "<SystemDrive>/Program Files/<Project Name>"
    RUNTIME DESTINATION "<SystemDrive>/Program Files/<Project Name>"
)

else(WIN32)

include(GNUInstallDirs)

install(
    FILES src/embroidery.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    TARGETS
       embroidery
       embroidery_static
       embroider
    EXPORT embroidery
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
endif(WIN32)
endif()

# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Packaging%20With%20CPack.html

if(WIN32)
set(CPACK_GENERATOR "WIX")
set(CPACK_SOURCE_GENERATOR "WIX")
else(WIN32)
set(CPACK_GENERATOR "DEB")
set(CPACK_SOURCE_GENERATOR "DEB")
endif(WIN32)
set(CPACK_PACKAGE_DIRECTORY build)
set(CPACK_PACKAGE_VENDOR "The Embroidermodder Team")
set(CPACK_SOURCE_IGNORE_FILES .git .github)

include(CPack)
