# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
project ("ImageProcessing")
cmake_minimum_required (VERSION 3.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(VL_ROOT "C:/VisualizationLibrary/install")
set(FBXSDK_ROOT "${CMAKE_HOME_DIRECTORY}/3rdparty/FBX SDK")
set(FBXSDK_LIBRARIES "${FBXSDK_ROOT}/lib/x64/${CMAKE_BUILD_TYPE}/libfbxsdk.lib")
set(FBXSDK_INCLUDE_DIRS "${FBXSDK_ROOT}/include")
set(VLExtension_DIR "${CMAKE_HOME_DIRECTORY}/3rdparty/VLExtension")

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/5.12.5/msvc2017_64")
list(APPEND CMAKE_PREFIX_PATH "${VL_ROOT}/x64-Debug")
list(APPEND CMAKE_PREFIX_PATH "${VL_ROOT}/x64-Release")

list(APPEND CMAKE_MODULE_PATH "${VL_ROOT}/x64-Debug/cmake" )
list(APPEND CMAKE_MODULE_PATH "${VL_ROOT}/x64-Release/cmake" )
list(APPEND CMAKE_MODULE_PATH "${VLExtension_DIR}" )

# Включите подпроекты.
add_subdirectory ("ImageProcessing")
add_subdirectory ("3rdparty/VLExtension")

find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(VL COMPONENTS VLCore VLGraphics VLQt5 VLVG VLMain REQUIRED)

message("CMAKE_HOME_DIRECTORY is ${CMAKE_HOME_DIRECTORY}/ImageProcessing/resources")

add_custom_target(ImageProcessingResources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_HOME_DIRECTORY}/ImageProcessing/resources         ${CMAKE_BINARY_DIR}/ImageProcessing/resources
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_custom_target(Qt5CopyBinaries
      COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Cored.dll         ${CMAKE_BINARY_DIR}/ImageProcessing/Qt5Cored.dll
      COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Guid.dll          ${CMAKE_BINARY_DIR}/ImageProcessing/Qt5Guid.dll
      COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGLd.dll       ${CMAKE_BINARY_DIR}/ImageProcessing/Qt5OpenGLd.dll
      COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgetsd.dll      ${CMAKE_BINARY_DIR}/ImageProcessing/Qt5Widgetsd.dll
    )
    add_custom_target(VLCopyBinaries
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Debug/bin/VLCore-d.dll       ${CMAKE_BINARY_DIR}/ImageProcessing/VLCore-d.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Debug/bin/VLGraphics-d.dll   ${CMAKE_BINARY_DIR}/ImageProcessing/VLGraphics-d.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Debug/bin/VLQt5-d.dll        ${CMAKE_BINARY_DIR}/ImageProcessing/VLQt5-d.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Debug/bin/VLVG-d.dll         ${CMAKE_BINARY_DIR}/ImageProcessing/VLVG-d.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Debug/bin/VLMain-d.dll       ${CMAKE_BINARY_DIR}/ImageProcessing/VLMain-d.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Debug/bin/VLX-d.dll          ${CMAKE_BINARY_DIR}/ImageProcessing/VLX-d.dll
    )

else(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	add_custom_target(Qt5CopyBinaries
      COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Core.dll          ${CMAKE_BINARY_DIR}/ImageProcessing/Qt5Core.dll
      COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Gui.dll           ${CMAKE_BINARY_DIR}/ImageProcessing/Qt5Gui.dll
      COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGL.dll        ${CMAKE_BINARY_DIR}/ImageProcessing/Qt5OpenGL.dll
      COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgets.dll       ${CMAKE_BINARY_DIR}/ImageProcessing/Qt5Widgets.dll
    )
    add_custom_target(VLCopyBinaries
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Release/bin/VLCore.dll       ${CMAKE_BINARY_DIR}/ImageProcessing/VLCore.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Release/bin/VLGraphics.dll   ${CMAKE_BINARY_DIR}/ImageProcessing/VLGraphics.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Release/bin/VLQt5.dll        ${CMAKE_BINARY_DIR}/ImageProcessing/VLQt5.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Release/bin/VLVG.dll         ${CMAKE_BINARY_DIR}/ImageProcessing/VLVG.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Release/bin/VLMain.dll       ${CMAKE_BINARY_DIR}/ImageProcessing/VLMain.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${VL_ROOT}/x64-Release/bin/VLX.dll          ${CMAKE_BINARY_DIR}/ImageProcessing/VLX.dll
    )
endif()

add_custom_target(FBXSDKCopyBinaries
      COMMAND ${CMAKE_COMMAND} -E copy ${FBXSDK_ROOT}/lib/x64/${CMAKE_BUILD_TYPE}/libfbxsdk.dll ${CMAKE_BINARY_DIR}/ImageProcessing/libfbxsdk.dll
    )