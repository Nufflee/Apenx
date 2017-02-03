#pragma once

#include <GLEW/glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include "../../utils/FileUtils.h"

namespace apenx
{
	namespace graphics
	{
		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char *m_VertexPath;
			const char *m_FragmentPath;
			bool m_Enabled;
		public:
			Shader(const char *vertexpath, const char *fragmentpath);
			~Shader();

			void setUniform1f(const GLchar *name, float value);
			void setUniform1i(const GLchar *name, int value);
			void setUniform2f(const GLchar *name, glm::vec2 &vector);
			void setUniform3f(const GLchar *name, glm::vec3 &vector);
			void setUniform3f(const GLchar *name, glm::vec4 &vector);
			void setUnifromMat4(const GLchar *name, const glm::mat4 &matrix);

			void enable();
			void disable();

			GLuint getShaderID()
			{
				return m_ShaderID;
			}
		private:
			GLint getUniformLocation(const GLchar *name);
			GLuint load();
		};
	}
}