#include <vlCore/VisualizationLibrary.hpp>
#include <iostream>
#include <VLExtension/Util/FBX_Support/FbxResource.h>

int main(int argc, char *argv[])
{
	vl::VisualizationLibrary::init();

	FbxResource fbxResource;
	fbxResource.LoadFile("resources/fbx/Sc2.fbx");

	auto geoms = fbxResource.GetGeometries();
	// test code
	// ...
	vl::VisualizationLibrary::shutdown();
	return 0;
}
