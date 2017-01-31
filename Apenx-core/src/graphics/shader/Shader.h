#pragma once

#include <GLEW\glew.h>
#include <iostream>
#include <vector>
#include "../../utils/FileUtils.h"

namespace apenx
{
	namespace graphics
	{
		class Shader
		{
		private:
			GLuint m_Shader;
			GLuint m_ShaderID;
			const char *m_VertexPath;
			const char *m_FragmentPath;
		public:
			Shader(const char *vertexpath, const char *fragmentpath);
			~Shader();

			void enable() const;
			void disable() const;
		private:
			GLuint load();
		};
	}
}