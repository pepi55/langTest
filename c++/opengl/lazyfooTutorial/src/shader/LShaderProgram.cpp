#include "LShaderProgram.hpp"

LShaderProgram::LShaderProgram(void) {
	mProgramID = 0x0;
}

LShaderProgram::~LShaderProgram(void) {
	freeProgram();
}

void LShaderProgram::freeProgram(void) {

}
