cmake_minimum_required (VERSION 3.8)

find_package(OpenGL REQUIRED)
find_package(VL COMPONENTS VLCore VLGraphics VLQt5 VLVG VLMain REQUIRED)

include_directories(${VL_INCLUDE_DIRS})
include_directories(${FBXSDK_INCLUDE_DIRS})

add_library (VLExtension STATIC
	"Actor.cpp"
	"Effect.cpp"
	"EffectPipeline.cpp"
	"FBORender.cpp"
	"Pipeline.cpp"
	"Shader.cpp"
	"ViewWindow.cpp"
	"Actors/FPSActor.cpp"
	"Actors/TextureRatioViewActor.cpp"
	"Actors/TextureViewActor.cpp"
	"Effects/BorderHighlightingEffect.cpp"
	"Effects/BrightnessContrastEffect.cpp"
	"Effects/GaussianBlurEffect.cpp"
	"Util/TextureReader.cpp"
	"Util/FBX_Support/FbxResource.cpp"
	"Util/FBX_Support/FbxMeshConverter.cpp"
	"Util/ColorUtils.cpp"
	"Util/Timer.cpp"
	)
target_link_libraries(VLExtension ${VL_LIBRARIES} ${OPENGL_LIBRARIES} ${FBXSDK_LIBRARIES})
target_include_directories(VLExtension PUBLIC ${CMAKE_HOME_DIRECTORY}/3rdparty)
target_include_directories(VLExtension PUBLIC ${VL_INCLUDE_DIRS})
target_include_directories(VLExtension PUBLIC ${FBXSDK_INCLUDE_DIRS})