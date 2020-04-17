cmake_minimum_required( VERSION 3.9 )
set(PROJECT_NAME example1 )

# sources to include in project
set( SOURCE
main.cpp
)

set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -rdynamic" )
set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -rdynamic -s" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -rdynamic")
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -rdynamic" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")

# find_package( Boost COMPONENTS system filesystem REQUIRED )
# if(NOT Boost_FOUND)
# 	message(SEND_ERROR "Failed to find boost::system|filesystem")
# 	return()
# else()
# 	include_directories(${Boost_INCLUDE_DIRS})
# endif()
#
add_executable( ${PROJECT_NAME} ${SOURCE} )

target_link_libraries( 	${PROJECT_NAME}
			#boost_stacktrace_backtrace
			#backtrace
			#boost_stacktrace_addr2line
			# dl
			# ${Boost_LIBRARIES}
)
