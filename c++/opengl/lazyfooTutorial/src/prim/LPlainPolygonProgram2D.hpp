#ifndef LPLAIN_POLYGON_PROGRAM_2D_H
#define LPLAIN_POLYGON_PROGRAM_2D_H

#include "../shader/LShaderProgram.hpp"

class LPlainPolygonProgram2D : public LShaderProgram {
	public:
		LPlainPolygonProgram2D(void);

		bool loadProgram(void);
		void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	private:
		GLint mPolygonColorLocation;
};

#endif
