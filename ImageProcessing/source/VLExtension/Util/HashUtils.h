#pragma once
#include <vlCore/Vector4.hpp>
#include <functional>
#include <memory>
#include <array>

namespace HashUtils
{
	template <typename...> struct hash;

	template<typename T>
	struct hash<T>
		: public std::hash<T>
	{
		//	using std::hash<T>::hash;
	};

	template <typename T, typename... Rest>
	struct hash<T, Rest...>
	{
		inline std::size_t operator()(const T& v, const Rest&... rest) {
			std::size_t seed = hash<Rest...>{}(rest...);
			seed ^= hash<T>{}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};

	template <typename... Types>
	std::size_t make_hash(const Types&... values)
	{
		return hash<Types...>{}(values...);
	}

	template<typename T, std::size_t array_size>
	struct hash<std::array<T, array_size>>
	{
		std::size_t operator()(const std::array<T, array_size> &array) const
		{
			std::size_t result = 0U;
			for (std::size_t i = 0; i < array_size; ++i) {
				result = make_hash(result, array[i]);
			}
			return result;
		}
	};

	template<>
	struct hash<vl::vec2>
	{
		size_t operator()(const vl::vec2 &vec) const
		{
			return make_hash(vec.x(), vec.y());
		}
	};

	template<>
	struct hash<vl::vec3>
	{
		size_t operator()(const vl::vec3 &vec) const
		{
			return make_hash(vec.x(), vec.y(), vec.z());
		}
	};

	template<>
	struct hash<vl::vec4>
	{
		size_t operator()(const vl::vec4 &vec) const
		{
			return make_hash(vec.x(), vec.y(), vec.z(), vec.w());
		}
	};

	template<typename T>
	struct hash<std::shared_ptr<T>>
	{
		size_t operator()(const std::shared_ptr<T> &ptr) const
		{
			return hash<T>()(*ptr);
		}
	};
}