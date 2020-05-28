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

	bool LoadFile( const std::string& file_path );
	std::vector<vl::ref<vl::Geometry>> GetGeometries() const;

	int	GetGeometryCount() const;
	vl::ref<vl::Geometry> GetGeometry( int meshIndex ) const;
	vl::ref<vl::Geometry> GetGeometry( int meshIndex, const std::vector<int>& smoothing_group_indices ) const;
private:
	fbxsdk::FbxSharedDestroyPtr<fbxsdk::FbxManager> fbxManager;
	fbxsdk::FbxSharedDestroyPtr<fbxsdk::FbxScene> fbxScene;

	vl::ref<vl::Geometry> geometry_;
};