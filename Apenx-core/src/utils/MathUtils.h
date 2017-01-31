#pragma once

#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

namespace apenx
{
	namespace utils
	{
		class MathUtils
		{
			friend std::ostream &operator<<(std::ostream &stream, const glm::vec2 &vector)
			{
				stream << glm::to_string(vector) << std::endl;
				return stream;
			}

			friend std::ostream &operator<<(std::ostream &stream, const glm::vec3 &vector)
			{
				stream << glm::to_string(vector) << std::endl;
				return stream;
			}

			friend std::ostream &operator<<(std::ostream &stream, const glm::vec4 &vector)
			{
				stream << glm::to_string(vector) << std::endl;
				return stream;
			}

			friend std::ostream &operator<<(std::ostream &stream, const glm::mat2 &matrix)
			{
				stream << glm::to_string(matrix) << std::endl;
				return stream;
			}

			friend std::ostream &operator<<(std::ostream &stream, const glm::mat3 &matrix)
			{
				stream << glm::to_string(matrix) << std::endl;
				return stream;
			}

			friend std::ostream &operator<<(std::ostream &stream, const glm::mat4 &matrix)
			{
				stream << glm::to_string(matrix) << std::endl;
				return stream;
			}
		};
	}
}