#pragma once

#include <vlGraphics/Geometry.hpp>
#include <vector>
#include <string>
#include "MeshStructures.h"
#include <memory>

namespace fbxsdk
{
	class FbxMesh;
}

class FbxMeshConverter : public vl::Object
{
public:
	FbxMeshConverter( const fbxsdk::FbxMesh* fbx_mesh );

	vl::ref<vl::Geometry> GetGeometry( int smoothing_group_index );
	vl::ref<vl::Geometry> GetGeometry( const std::vector<int>& smoothing_group_indices );


private:
	int get_polygon_count();
	vl::vec4 get_position_from_control_point( int control_point_index );

	vl::vec4 get_polygon_vertex_position( int polygon_index, int polygon_vertex_index );
	vl::vec4 get_polygon_vertex_normal( int polygon_index, int polygon_vertex_index );
	vl::vec4 get_polygon_vertex_color( int polygon_index, int polygon_vertex_index );
	Vertex::UV_Channel_values get_polygon_uv_channel_values( int polygon_index, int polygon_vertex_index );

	std::shared_ptr<Vertex> make_vertex( int polygon_index, int polygon_vertex_index );

	int get_uv_channel_index( const std::string& channel_name );


	using SmoothGroupIndices = std::array<std::vector<int>, 32 + 1>;
	vl::ref<vl::Geometry> create_vl_geometry( const std::vector<int>& polygon_indices );

	void get_vertices_and_polygons( const std::vector<int>& polygon_indices,
									std::vector<std::shared_ptr<Vertex>>& output_vtx_vec, std::vector<MeshPolygon>& output_triangle_vec );

	void set_vl_buffers( const std::vector<std::shared_ptr<Vertex>>& vtx_vec, vl::Geometry* geometry );
	void set_vl_draw_elements( const std::vector<MeshPolygon>& polygon_vec, vl::Geometry* geometry );

	// fields
	const fbxsdk::FbxMesh* fbx_mesh_;
	static const vl::fvec2 EMPTY_UV_VALUE;
};