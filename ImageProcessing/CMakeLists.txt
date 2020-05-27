# CMakeList.txt: проект CMake для ImageProcessing; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenGL REQUIRED)

find_package(VL COMPONENTS VLCore VLGraphics VLQt5 VLVG VLMain REQUIRED)
include_directories(${VL_INCLUDE_DIRS})
include_directories("source")
include_directories(${FBXSDK_INCLUDE_DIRS})

set(GUI_DIR "source/GUI")
set(APP_LOGIC_DIR "source/AppLogic")
set(VLExtension_DIR "source/VLExtension")

add_executable (ImageProcessing 
	"main.cpp"
	# GUI
	"${GUI_DIR}/MainWindow.cpp"
	"${GUI_DIR}/ParamsWidget.cpp"
	"${GUI_DIR}/ParamWidget.cpp"
	"${GUI_DIR}/SelectableListWidget.cpp"
	"${GUI_DIR}/ImageProcessingModeWidget.cpp"
	"${GUI_DIR}/Editor3DModeWidget.cpp"

	# VLExtension_dir
	"${VLExtension_DIR}/Actor.cpp"
	"${VLExtension_DIR}/Effect.cpp"
	"${VLExtension_DIR}/EffectPipeline.cpp"
	"${VLExtension_DIR}/FBORender.cpp"
	"${VLExtension_DIR}/Pipeline.cpp"
	"${VLExtension_DIR}/Shader.cpp"
	"${VLExtension_DIR}/ViewWindow.cpp"
	"${VLExtension_DIR}/Actors/FPSActor.cpp"
	"${VLExtension_DIR}/Actors/TextureRatioViewActor.cpp"
	"${VLExtension_DIR}/Actors/TextureViewActor.cpp"
	"${VLExtension_DIR}/Util/TextureReader.cpp"
	"${VLExtension_DIR}/Util/FBX_Support/FbxResource.cpp"
	"${VLExtension_DIR}/Util/FBX_Support/FbxMeshConverter.cpp"
	"${VLExtension_DIR}/Effects/BorderHighlightingEffect.cpp"
	"${VLExtension_DIR}/Effects/BrightnessContrastEffect.cpp"
	"${VLExtension_DIR}/Effects/GaussianBlurEffect.cpp"

	# AppLogic_dir
		# AppModes_dir
		"${APP_LOGIC_DIR}/AppModes/AppMode.cpp"
		"${APP_LOGIC_DIR}/AppModes/AppModeList.cpp"
		"${APP_LOGIC_DIR}/AppModes/ImageProcessingMode.cpp"
		"${APP_LOGIC_DIR}/AppModes/Editor3DMode.cpp"
		# ImageProcessing_dir
		"${APP_LOGIC_DIR}/ImageProcessing/ImageEffect.cpp"
		"${APP_LOGIC_DIR}/ImageProcessing/ImageEffectList.cpp"
		"${APP_LOGIC_DIR}/ImageProcessing/ImageEffects/BorderHighlightingImageEffect.cpp"
		"${APP_LOGIC_DIR}/ImageProcessing/ImageEffects/BrightnessContrastImageEffect.cpp"
		"${APP_LOGIC_DIR}/ImageProcessing/ImageEffects/GaussianBlurImageEffect.cpp"
		# SelectTools_dir
		"${APP_LOGIC_DIR}/SelectTools/ParamsSelectable.cpp"
		"${APP_LOGIC_DIR}/SelectTools/Selectable.cpp"
		"${APP_LOGIC_DIR}/SelectTools/SelectableList.cpp"
		# Util_dir
		"${APP_LOGIC_DIR}/Util/ColorUtils.cpp"
		"${APP_LOGIC_DIR}/Util/Timer.cpp"
	)


target_link_libraries(ImageProcessing Qt5::Widgets Qt5::OpenGL ${VL_LIBRARIES} ${OPENGL_LIBRARIES} ${FBXSDK_LIBRARIES})

add_dependencies(ImageProcessing Qt5CopyBinaries)
add_dependencies(ImageProcessing VLCopyBinaries)
add_dependencies(ImageProcessing ImageProcessingResources)
add_dependencies(ImageProcessing FBXSDKCopyBinaries)
