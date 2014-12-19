#pragma once

#include <glm/glm.hpp>

#include "../shader/LColorRGBA.hpp"
#include "../shader/LShaderProgram.hpp"

class LFontProgram2D : public LShaderProgram {
	public:
		LFontProgram2D(void);

		bool loadProgram(void);
		void setVertexPointer(GLsizei stride, const GLvoid *data);
		void setTexCoorPointer(GLsizei stride, const GLvoid *data);

		void enableVertexPointer(void);
		void disableVertexPointer(void);

		void enableTexCoordPointer(void);
		void disableTexCoordPointer(void);

		void setProjection(glm::mat4 matrix);
		void setModelView(glm::mat4 matrix);

		void leftMultProjection(glm::mat4 matrix);
		void leftMultModelView(glm::mat4 matrix);

		void updateProjection(void);
		void updateModelView(void);

		void setTextColor(LColorRGBA color);
		void setTextureUnit(GLuint unit);

	private:
		GLint mVertexPos2DLocation;
		GLint mTexCoordLocation;

		GLint mTextColorLocation;
		GLint mTextureUnitLocation;

		glm::mat4 mProjectionMatrix;
		glm::mat4 mModelViewMatrix;

		GLint mProjectionMatrixLocation;
		GLint mModelViewMatrixLocation;
};
