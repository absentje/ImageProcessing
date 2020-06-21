# CMakeList.txt: проект CMake для ImageProcessing; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_library(VLExtension REQUIRED)

include_directories("source")
include_directories("${CMAKE_HOME_DIRECTORY}/3rdparty")


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

	# AppLogic_dir
		# AppModes_dir
		"${APP_LOGIC_DIR}/AppModes/AppMode.cpp"
		"${APP_LOGIC_DIR}/AppModes/AppModeList.cpp"
		"${APP_LOGIC_DIR}/AppModes/ImageProcessingMode.cpp"
		"${APP_LOGIC_DIR}/AppModes/Editor3DMode.cpp"
		# Editor3D_dir
		"${APP_LOGIC_DIR}/Editor3D/Mode3D.cpp"
		"${APP_LOGIC_DIR}/Editor3D/Mode3DList.cpp"
		"${APP_LOGIC_DIR}/Editor3D/Modes3D/PBRViewMode.cpp"

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
	)

add_executable (vlTest "vlTest.cpp")

target_link_libraries(ImageProcessing Qt5::Widgets Qt5::OpenGL VLExtension)
target_link_libraries(vlTest VLExtension)

add_dependencies(ImageProcessing Qt5CopyBinaries)
add_dependencies(ImageProcessing VLCopyBinaries)
add_dependencies(ImageProcessing ImageProcessingResources)
