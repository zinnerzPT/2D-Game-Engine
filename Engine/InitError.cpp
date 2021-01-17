#include "InitError.h"
#include "SDLWrapper.h"
#include "OpenALWrapper.h"

#include <SDL2/SDL.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

InitError::InitError() :
	exception(), msg(SDL_GetError()) {}

InitError::InitError(OpenALWrapper* alWrapper) :
	exception(), msg(alGetString(alGetError())) {}

InitError::InitError(const std::string& m) :
	exception(), msg(m) {}

InitError::~InitError() throw() {}

const char* InitError::what() const throw() {
	return msg.c_str();
}

