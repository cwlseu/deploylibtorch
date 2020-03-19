cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
PROJECT(custom_ops)
CMAKE_POLICY(SET CMP0054 NEW)
IF(WIN32)
    SET(target_os_arch windows-x86_64)
ELSE()
    SET(target_os_arch linux-x86_64)
	SET(CMAKE_C_COMPILER /usr/bin/gcc-5)
	SET(CMAKE_CXX_COMPILER /usr/bin/g++-5)
ENDIF()
SET(TARGET_BUILD_TYPE release)
SET(CMAKE_BUILD_TYPE ${TARGET_BUILD_TYPE})
SET(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps/${target_os_arch}-${TARGET_BUILD_TYPE}/libtorch/share/cmake)

MESSAGE(STATUS "TARGET_OS_ARCH ${target_os_arch}")
MESSAGE(STATUS "TARGET_BUILD_TYPE ${CMAKE_BUILD_TYPE}")
MESSAGE(STATUS "TARGET_OS_ARCH ${target_os_arch}")

FIND_PACKAGE(Torch REQUIRED)
MESSAGE(STATUS "TORCH_LIBRARIES: ${TORCH_LIBRARIES}")
INCLUDE_DIRECTORIES(include)

FILE(GLOB samples ${PROJECT_SOURCE_DIR}/*.cpp)

FOREACH (sample ${samples})
	STRING(REGEX MATCH "[^/]+$" sample_file ${sample})
	STRING(REPLACE ".cpp" "" sample_basename ${sample_file})
	ADD_EXECUTABLE(test_${sample_basename} ${sample})

	TARGET_LINK_LIBRARIES(test_${sample_basename} "${TORCH_LIBRARIES}")

	IF(CMAKE_TARGET_OS STREQUAL "ANDROID")
		TARGET_LINK_LIBRARIES(test_${sample_basename} log) ## we need to use android-log in SDK_LOG_XXX
	ELSEIF(NOT WIN32)
		TARGET_LINK_LIBRARIES(test_${sample_basename} pthread)
	ENDIF()
	SET_PROPERTY(TARGET test_${sample_basename} PROPERTY CXX_STANDARD 11)
	INSTALL(TARGETS test_${sample_basename} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
ENDFOREACH()
