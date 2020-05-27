#pragma once
#include <vlCore/Object.hpp>
#include <vlGraphics/Geometry.hpp>
#include <string>
#include <vector>
#include <fbxsdk.h>

class FbxResource : public vl::Object
{
public:
	FbxResource();

	bool LoadFile( const std::string& file_path, int meshIndex );
	vl::ref<vl::Geometry> GetGeometry(const std::vector<int>& smoothing_group_indices);
	int	GetGeometryCount();

private:
	fbxsdk::FbxSharedDestroyPtr<fbxsdk::FbxManager> fbxManager;
	fbxsdk::FbxSharedDestroyPtr<fbxsdk::FbxScene> fbxScene;
	fbxsdk::FbxSharedDestroyPtr<fbxsdk::FbxMesh> fbxMesh;

	vl::ref<vl::Geometry> geometry_;
};