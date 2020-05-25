#include "FbxMeshConverter.h"
#include <fbxsdk.h>
#include <sstream>
#include <set>
#include <unordered_map>
#include <cstdlib>
#include <chrono>

const vl::fvec2 FbxMeshConverter::EMPTY_UV_VALUE = vl::fvec2(-1, -1);

FbxMeshConverter::FbxMeshConverter(fbxsdk::FbxMesh* fbx_mesh) : fbx_mesh_(fbx_mesh)
{
}

vl::ref<vl::Geometry> FbxMeshConverter::GetGeometry(int smoothing_group_index)
{
	return GetGeometry(std::vector<int>{smoothing_group_index});
}

vl::ref<vl::Geometry> FbxMeshConverter::GetGeometry(const std::vector<int>& smoothing_group_indices)
{
	static float allTime = 0.0f;
	auto now = std::chrono::high_resolution_clock::now();


	SmoothGroupIndices smoothing_groups_and_polygon_indices;
	{// раскидываем индексы полигонов по смуф-группам
		const int smoothingElementCount = fbx_mesh_->GetElementSmoothingCount();
		VL_CHECK(smoothingElementCount >= 0);

		for (int smoothElementIndex = 0; smoothElementIndex != smoothingElementCount; ++smoothElementIndex){
			auto& directArray = fbx_mesh_->GetElementSmoothing(smoothElementIndex)->GetDirectArray();
			const int arraySize = directArray.GetCount();

			for (int polygonIndex = 0; polygonIndex != arraySize; ++polygonIndex){
				unsigned int value = directArray[polygonIndex];
				for (int i = 1; i != 32 + 1; ++i){
					if (value % 2 == 1){
						smoothing_groups_and_polygon_indices[i].push_back(polygonIndex);
					}
					value = value >> 1;
				}
				smoothing_groups_and_polygon_indices[0].push_back(polygonIndex); // 0-group includes all indices
			}
		}
	}
	
	std::set<int> polygonIndices;
	{// оставляем индексы только необходимых полигонов
		for (auto& smooth_group_index : smoothing_group_indices){
			for (auto& the_simplest_index : smoothing_groups_and_polygon_indices[smooth_group_index]){
				polygonIndices.insert(the_simplest_index);
			}
		}
	}

	// transfer indices to std::vector to use 'FbxMeshConverter::create_vl_geometry'
	std::vector<int> geometryPolygonIndices;
	for (auto& index : polygonIndices){
		geometryPolygonIndices.push_back(index);
	}

	auto geom = create_vl_geometry(geometryPolygonIndices);
	allTime += std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - now).count();
	VL_LOG_NOTIFY << "  |_ GetGeometry < " << fbx_mesh_->GetName() << " > total: " << std::to_string(allTime) << "s.\n";
	return geom;
}

vl::vec4 FbxMeshConverter::get_position_from_control_point(int control_point_index)
{
	auto position_ = fbx_mesh_->GetControlPointAt(control_point_index);
	return vl::fvec4(
		(float)position_.mData[0],
		(float)position_.mData[1],
		(float)position_.mData[2],
		(float)position_.mData[3]);
}

vl::vec4 FbxMeshConverter::get_polygon_vertex_position(int i, int j)
{
	int control_point_index = fbx_mesh_->GetPolygonVertex(i, j);
	return get_position_from_control_point(control_point_index);
}

vl::vec4 FbxMeshConverter::get_polygon_vertex_normal(int i, int j)
{
	FbxVector4 normal_;
	fbx_mesh_->GetPolygonVertexNormal(i, j, normal_);

	return vl::fvec4(
		(float)normal_.mData[0],
		(float)normal_.mData[1],
		(float)normal_.mData[2],
		(float)normal_.mData[3]);
}

vl::vec4 FbxMeshConverter::get_polygon_vertex_color(int i, int j)
{
	const int ELEMENT_VERTEX_COLOR_COUNT = fbx_mesh_->GetElementVertexColorCount();

	if (ELEMENT_VERTEX_COLOR_COUNT != 0)
	{
		auto& color_direct_array = fbx_mesh_->GetElementVertexColor(0)->GetDirectArray();
		auto& color_index_array = fbx_mesh_->GetElementVertexColor(0)->GetIndexArray();

		const int INDEX = color_index_array[i * 3 + j];
		const auto& COLOR = color_direct_array[INDEX];

		return vl::fvec4((float)COLOR.mRed, (float)COLOR.mGreen, (float)COLOR.mBlue, (float)COLOR.mAlpha);
	}
	return vl::fvec4(0.f, 0.f, 0.f, -1.f);
}

Vertex::UV_Channel_values FbxMeshConverter::get_polygon_uv_channel_values(int i, int j)
{
	Vertex::UV_Channel_values return_value;

	for (auto& s : return_value)
		s = EMPTY_UV_VALUE;

	const int UV_FbxChannels_count = fbx_mesh_->GetElementUVCount();

	for (int UV_num = 0; UV_num != UV_FbxChannels_count; ++UV_num)
	{
		auto UV_element = fbx_mesh_->GetElementUV(UV_num);

		auto UV_ChannelName = UV_element->GetName();
		int UV_Channel_Index = get_uv_channel_index(UV_ChannelName);

		if (UV_Channel_Index > 0 && UV_Channel_Index < MAX_UV_CHANNEL_INDEX)
		{
			auto& UV_values_array = UV_element->GetDirectArray();
			auto& UV_indexes_array = UV_element->GetIndexArray();

			const int INDEX_IN_UV_VALUES_ARRAY = UV_indexes_array[i * 3 + j];
			const auto& UV_VALUE = UV_values_array[INDEX_IN_UV_VALUES_ARRAY];

			return_value[UV_Channel_Index] = vl::fvec2((float)UV_VALUE.mData[0], (float)UV_VALUE.mData[1]);
		}
	}
	return return_value;
}

std::shared_ptr<Vertex> FbxMeshConverter::make_vertex(int polygon_index, int polygon_vertex_index)
{
	std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>();

	vertex->position = get_polygon_vertex_position(polygon_index, polygon_vertex_index);
	vertex->normal = get_polygon_vertex_normal(polygon_index, polygon_vertex_index);
	vertex->color = get_polygon_vertex_color(polygon_index, polygon_vertex_index);
	vertex->uv_values = get_polygon_uv_channel_values(polygon_index, polygon_vertex_index);
	return vertex;
}

int FbxMeshConverter::get_polygon_count()
{
	return fbx_mesh_->GetPolygonCount();
}

int FbxMeshConverter::get_uv_channel_index(const std::string& channel_name)
{
	static const int SIZE_OF_SUBSTRING = 10; // size of "UVChannel_"

	int return_value = -1;

	if (channel_name.size() > SIZE_OF_SUBSTRING)
	{
		const char* uv_id_str = &channel_name.c_str()[SIZE_OF_SUBSTRING];
		return_value = atoi(uv_id_str);
	}
	return return_value;
}

vl::ref<vl::Geometry> FbxMeshConverter::create_vl_geometry(const std::vector<int>& polygon_indices)
{
	std::vector<std::shared_ptr<Vertex>> vertices;
	std::vector<MeshPolygon> polygons;
	get_vertices_and_polygons(polygon_indices, vertices, polygons);

	vl::ref<vl::Geometry> geometry = new vl::Geometry;
	set_vl_buffers(vertices, geometry.get());
	set_vl_draw_elements(polygons, geometry.get());

	return geometry;
}

template<typename T>
struct EqualOfSharedPtrs
{
	bool operator()(std::shared_ptr<T> left, std::shared_ptr<T> right) const
	{
		VL_CHECK(left && right);
		return *left == *right;;
	}
};

void FbxMeshConverter::get_vertices_and_polygons(const std::vector<int>& polygon_indices,
	std::vector<std::shared_ptr<Vertex>>& output_vtx_vec, std::vector<MeshPolygon>& output_polygon_vec){
	output_vtx_vec.clear();
	output_polygon_vec.clear();
	const int POLYGON_COUNT = (int)polygon_indices.size();
	output_polygon_vec.resize(POLYGON_COUNT);
	using PolygonIndexPair = std::pair<int, int>; // pair<PolygonIndex, PolygonVertexIndex>
	using PrimaryKey = int; // для задания упорядоченности конечных вертексов(в порядке добавления)
	using PolygonIndexPairsPtr = std::shared_ptr<std::vector<PolygonIndexPair>>;
	using VertexPtr = std::shared_ptr<Vertex>;
	std::unordered_map<VertexPtr, std::pair<PolygonIndexPairsPtr, PrimaryKey>, HashUtils::hash<VertexPtr>, EqualOfSharedPtrs<Vertex>> vertex_map;
	for (int polygon_index = 0; polygon_index != POLYGON_COUNT; ++polygon_index){
		const int FBX_POLYGON_INDEX = polygon_indices[polygon_index];
		const int POLYGON_VERTEX_COUNT = fbx_mesh_->GetPolygonSize(FBX_POLYGON_INDEX);
		for (int polygon_vertex_index = 0; polygon_vertex_index != POLYGON_VERTEX_COUNT; ++polygon_vertex_index){
			const PrimaryKey PRIMARY_KEY = polygon_index * 4 + polygon_vertex_index;
			auto new_vertex = make_vertex(FBX_POLYGON_INDEX, polygon_vertex_index);
			auto& element = vertex_map[new_vertex];
			if (element.first == nullptr){
				element.first = std::make_shared<std::vector<PolygonIndexPair>>();
				element.second = PRIMARY_KEY;
			}
			element.first->push_back(PolygonIndexPair{ polygon_index, polygon_vertex_index });
		}
	}
	// сорт. за O(n) и запись в выходной массив(output_vtx_vec)
	const int INITIAL_VTX_COUNT = POLYGON_COUNT * 4;
	std::vector<std::pair<VertexPtr, PolygonIndexPairsPtr>> vtx_info(INITIAL_VTX_COUNT);
	for (auto& s : vertex_map){
		VertexPtr vtx = s.first;
		PolygonIndexPairsPtr index_pairs = s.second.first;
		const PrimaryKey PRIMARY_KEY = s.second.second;
		vtx_info[PRIMARY_KEY] = std::pair<VertexPtr, PolygonIndexPairsPtr>{ vtx, index_pairs };
	}
	for (int i = 0, vertex_index = 0; i != INITIAL_VTX_COUNT; ++i){
		auto& pair = vtx_info[i];
		auto& vtx_ptr = pair.first;
		auto& index_pairs_ptr = pair.second;
		if (vtx_ptr && index_pairs_ptr){
			output_vtx_vec.push_back(vtx_ptr);
			for (auto& index_pair : *index_pairs_ptr){
				const int POLYGON_INDEX = index_pair.first;
				const int POLYGON_VERTEX_INDEX = index_pair.second;
				output_polygon_vec[POLYGON_INDEX].vertex_indexes[POLYGON_VERTEX_INDEX] = vertex_index;
				if (POLYGON_VERTEX_INDEX == 3)
					output_polygon_vec[POLYGON_INDEX].ePolygonType = EMeshPolygonType::PT_Quad;
			}
			++vertex_index;
		}
	}
}

void FbxMeshConverter::set_vl_buffers(const std::vector<std::shared_ptr<Vertex>>& vtx_vec, vl::Geometry* geometry)
{
	const int VERTEX_COUNT = (int)vtx_vec.size();

	if (VERTEX_COUNT == 0)
		return;

	// set Vertex, Normal, Color Arrays
	{
		vl::ref<vl::ArrayFloat3> vertex_array = new vl::ArrayFloat3;
		vl::ref<vl::ArrayFloat3> normal_array = new vl::ArrayFloat3;
		vl::ref<vl::ArrayFloat4> color_array = nullptr;

		vertex_array->resize(VERTEX_COUNT);
		normal_array->resize(VERTEX_COUNT);

		geometry->setVertexArray(vertex_array.get());
		geometry->setNormalArray(normal_array.get());

		bool is_colored = vtx_vec[0]->color.w() != -1;

		if (is_colored)
		{
			color_array = new vl::ArrayFloat4;
			color_array->resize(VERTEX_COUNT);
			geometry->setColorArray(color_array.get());
		}

		for (int vertex_index = 0; vertex_index != VERTEX_COUNT; ++vertex_index)
		{
			(*vertex_array)[vertex_index] = vtx_vec[vertex_index]->position.xyz();
			(*normal_array)[vertex_index] = vtx_vec[vertex_index]->normal.xyz();
			if (color_array)
				(*color_array)[vertex_index] = vtx_vec[vertex_index]->color;
		}

	}

	// set UV Channels
	{
		//	MAX_VL_UV_CHANNELS_COUNT; // UV-indices = { 0-10 }

		for (int VL_UV_Index = 0; VL_UV_Index != MAX_VL_UV_CHANNELS_COUNT; ++VL_UV_Index)
		{
			const int FBX_UV_INDEX = VL_UV_Index + 1;

			if (vtx_vec[0]->uv_values[FBX_UV_INDEX] != EMPTY_UV_VALUE)
			{
				vl::ref<vl::ArrayFloat4> current_textureUV_array = new vl::ArrayFloat4;
				current_textureUV_array->resize(VERTEX_COUNT);

				for (int vertex_index = 0; vertex_index != VERTEX_COUNT; ++vertex_index)
				{
					(*current_textureUV_array)[vertex_index] = vl::vec4(vtx_vec[vertex_index]->uv_values[FBX_UV_INDEX], vl::vec2(0.f));
				}
				geometry->setTexCoordArray(VL_UV_Index, current_textureUV_array.get());
			}
		}
	}
}

void FbxMeshConverter::set_vl_draw_elements(const std::vector<MeshPolygon>& polygon_vec, vl::Geometry* geometry)
{
	const int POLYGON_COUNT = (int)polygon_vec.size();
	int triangle_count = 0, quad_count = 0;
	for (int i = 0; i != POLYGON_COUNT; ++i){
		switch (polygon_vec[i].ePolygonType){
		case EMeshPolygonType::PT_Triangle:
			++triangle_count;
			break;
		case EMeshPolygonType::PT_Quad:
			++quad_count;
			break;
		}
	}
	vl::ref<vl::DrawElementsUInt> triangles_draw_element = nullptr;
	vl::ref<vl::DrawElementsUInt> quads_draw_element = nullptr;
	if (triangle_count){
		triangles_draw_element = new vl::DrawElementsUInt(vl::PT_TRIANGLES);
		triangles_draw_element->indexBuffer()->resize(triangle_count * 3);
		geometry->drawCalls().push_back(triangles_draw_element.get());
	}
	if (quad_count){
		quads_draw_element = new vl::DrawElementsUInt(vl::PT_QUADS);
		quads_draw_element->indexBuffer()->resize(quad_count * 4);
		geometry->drawCalls().push_back(quads_draw_element.get());
	}

	int triangle_draw_buffer_index = 0;
	int quad_draw_buffer_index = 0;

	for (int i = 0; i != POLYGON_COUNT; ++i){
		switch (polygon_vec[i].ePolygonType){
		case EMeshPolygonType::PT_Triangle:
			triangles_draw_element->indexBuffer()->at(triangle_draw_buffer_index++) = polygon_vec[i].vertex_indexes[0];
			triangles_draw_element->indexBuffer()->at(triangle_draw_buffer_index++) = polygon_vec[i].vertex_indexes[1];
			triangles_draw_element->indexBuffer()->at(triangle_draw_buffer_index++) = polygon_vec[i].vertex_indexes[2];
			break;
		case EMeshPolygonType::PT_Quad:
			quads_draw_element->indexBuffer()->at(quad_draw_buffer_index + 0) = polygon_vec[i].vertex_indexes[0];
			quads_draw_element->indexBuffer()->at(quad_draw_buffer_index + 1) = polygon_vec[i].vertex_indexes[1];
			quads_draw_element->indexBuffer()->at(quad_draw_buffer_index + 2) = polygon_vec[i].vertex_indexes[2];
			quads_draw_element->indexBuffer()->at(quad_draw_buffer_index + 3) = polygon_vec[i].vertex_indexes[3];
			quad_draw_buffer_index += 4;
			break;
		}
	}
}