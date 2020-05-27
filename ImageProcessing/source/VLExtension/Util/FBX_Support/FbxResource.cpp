#include "FbxResource.h"
#include "FbxMeshConverter.h"

FbxResource::FbxResource()
	: geometry_(new vl::Geometry()), fbxManager(FbxManager::Create()), fbxScene(FbxScene::Create(fbxManager, ""))
{
}

bool FbxResource::LoadFile( const std::string& file_path, int meshIndex )
{
	auto fbxImporter = FbxSharedDestroyPtr<FbxImporter>(FbxImporter::Create(fbxManager, ""));
	auto fbxIOSettings = FbxSharedDestroyPtr<FbxIOSettings>(FbxIOSettings::Create(fbxManager, IOSROOT));
	bool is_init = fbxImporter->Initialize( file_path.c_str(), -1, fbxIOSettings);
	bool is_fbx = fbxImporter->IsFBX();
	if (!is_init || !is_fbx)
	{
		return false;
	}
	
	fbxImporter->Import(fbxScene);
	fbxMesh = FbxSharedDestroyPtr<FbxMesh>(static_cast<FbxMesh*>(fbxScene->GetGeometry(meshIndex)));
	VL_CHECK(fbxMesh->GetClassId() == FbxMesh::ClassId);
//	fbxMesh->SetName(stream->objectName().c_str());

	return true;
}

vl::ref<vl::Geometry> FbxResource::GetGeometry(const std::vector<int>& smoothing_group_indices)
{
	FbxMeshConverter meshConverter(fbxMesh);
	vl::ref<vl::Geometry> geom = meshConverter.GetGeometry(smoothing_group_indices);
	VL_LOG << "Mesh is ";
	if (!fbxMesh->IsTriangleMesh())
		VL_LOG << "non-";
	VL_LOG << "triangulated!\n";
	return geom;
}

int	FbxResource::GetGeometryCount()
{
	return fbxScene->GetGeometryCount();
}
