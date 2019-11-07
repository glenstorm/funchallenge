cmake_minimum_required( VERSION 3.10 )
set(PROJECT_NAME dlms_async_server )

#SET(Boost_USE_STATIC_LIBS OFF)
#SET(Boost_USE_MULTITHREAD ON)

# sources to include in project
set( SOURCE
main.cpp
)

add_compile_options(-std=c++11)

set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -rdynamic" )
set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -rdynamic -s" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -rdynamic")
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -rdynamic" )

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

find_package( Boost COMPONENTS system thread coroutine REQUIRED )
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost::system|thread|coroutine")
	return()
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable( ${PROJECT_NAME} ${SOURCE} )

target_link_libraries( 	${PROJECT_NAME}
			${Boost_LIBRARIES}
)
