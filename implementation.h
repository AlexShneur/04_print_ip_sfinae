#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <string>

namespace impl
{
	template <
		template <typename, typename> typename T,
		typename Type,
		typename Allocator = std::allocator<Type>,
		typename = std::enable_if_t<
		std::is_same_v<T<Type, Allocator>, std::vector<Type, Allocator>> ||
		std::is_same_v<T<Type, Allocator>, std::list<Type, Allocator>>>>
		auto print_ip(const T<Type, Allocator>& addr)
	{
		std::string str = "";
		for (auto iter = std::begin(addr); iter != std::end(addr); ++iter)
		{
			if (iter != std::begin(addr))
				str += ".";
			str += std::to_string(*iter);
		}
		return str;
	}

	template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
	auto print_ip(const T& addr)
	{
		switch (sizeof(addr))
		{
			case sizeof(int8_t) :
				return std::to_string(addr & 0xFF);
				case sizeof(int16_t) :
					return std::to_string(((addr >> 8) & 0xFF)) + "." +
					std::to_string(addr & 0xFF);
					case sizeof(int32_t) :
						return std::to_string(((addr >> 24) & 0xFF)) + "." +
						std::to_string(((addr >> 16) & 0xFF)) + "." +
						std::to_string(((addr >> 8) & 0xFF)) + "." +
						std::to_string(addr & 0xFF);
						case sizeof(int64_t) :
							return std::to_string(((addr >> 56) & 0xFF)) + "." +
							std::to_string(((addr >> 48) & 0xFF)) + "." +
							std::to_string(((addr >> 40) & 0xFF)) + "." +
							std::to_string(((addr >> 32) & 0xFF)) + "." +
							std::to_string(((addr >> 24) & 0xFF)) + "." +
							std::to_string(((addr >> 16) & 0xFF)) + "." +
							std::to_string(((addr >> 8) & 0xFF)) + "." +
							std::to_string(addr & 0xFF);
						default:
							return std::to_string(addr);
		}
	}

	template <typename T>
	auto print_ip(const T& addr) -> decltype(addr.substr())
	{
		return addr;
	}
}
