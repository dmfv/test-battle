#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

namespace sw::core
{
	class Attributes
	{
	public:
		void set(std::string key, int value)
		{
			values_[std::move(key)] = value;
		}

		bool contains(std::string_view key) const
		{
			return values_.find(std::string(key)) != values_.end();
		}

		/**
		 * Шаблонный метод для получения значения атрибута.
		 * Позволяет гибко поддерживать различные типы (например, int для характеристик и bool для тегов-флагов).
		 */
		template <typename T>
		T getOr(std::string_view key, T fallback) const
		{
			const auto iterator = values_.find(std::string(key));
			if (iterator == values_.end())
			{
				std::cerr << "Warning: Attribute '" << key << "' missing, using default " << fallback << std::endl;
				return fallback;
			}
			return static_cast<T>(iterator->second);
		}

		const std::unordered_map<std::string, int>& values() const
		{
			return values_;
		}

	private:
		std::unordered_map<std::string, int> values_{};
	};
}
