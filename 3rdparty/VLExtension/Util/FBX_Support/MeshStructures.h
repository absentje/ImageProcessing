#pragma once
#include <array>
#include <vector>
#include <vlCore/Vector4.hpp>
#include <VLExtension/Util/HashUtils.h>

const int MAX_VL_UV_CHANNELS_COUNT = 11;
const int MAX_UV_CHANNEL_INDEX = MAX_VL_UV_CHANNELS_COUNT + 1;

struct Vertex{
	using UV_Channel_values = std::array<vl::fvec2, MAX_UV_CHANNEL_INDEX>;

	vl::vec4 position;
	vl::vec4 normal;
	vl::vec4 color;
	UV_Channel_values uv_values;


	inline bool operator==(const Vertex& vtx) const {
		return position == vtx.position && normal == vtx.normal && color == vtx.color && uv_values == vtx.uv_values;
	}

	/*
	inline bool operator<(const Vertex& vtx) const {
		return position < vtx.position ||
			position == vtx.position && normal < vtx.normal ||
			(position == vtx.position && normal == vtx.normal && color < vtx.color) ||
			(position == vtx.position && normal == vtx.normal && color == vtx.color && uv_values < vtx.uv_values);
	}
	*/
};

enum class EMeshPolygonType : unsigned char
{
	PT_Triangle,
	PT_Quad
};

struct MeshPolygon{
	std::array<int, 4> vertex_indexes;
	EMeshPolygonType ePolygonType;
};

namespace HashUtils
{
	template<>
	struct hash<Vertex>
	{
		size_t operator()(const Vertex &vtx) const
		{
			return make_hash(vtx.position, vtx.normal);
		}
	};
}