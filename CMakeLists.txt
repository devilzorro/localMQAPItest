cmake_minimum_required (VERSION 2.6)
project (localMQAPItest)

unset(src)

set(srcdirs
$ENV{NUTHOME}/include/
${PROJECT_SOURCE_DIR}
)

set(CMAKE_INSTALL_PREFIX "$ENV{NUTHOME}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

INCLUDE_DIRECTORIES(${srcdirs})

FOREACH(srcdir ${srcdirs})
AUX_SOURCE_DIRECTORY(${srcdir} src)
ENDFOREACH()

LINK_DIRECTORIES(
$ENV{NUTHOME}/lib
${CMAKE_CURRENT_SOURCE_DIR} 
/usr/lib
)

ADD_EXECUTABLE(localMQAPItest ${src})
TARGET_LINK_LIBRARIES(localMQAPItest localMQ paho-mqtt3as)
INSTALL(TARGETS localMQAPItest DESTINATION bin)
