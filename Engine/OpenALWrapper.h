#pragma once
// OpenAL library
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
// AudioFile library
#include <AudioFile/AudioFile.h>

#include "Sound.h"

typedef struct AudioDevice
{
	ALCdevice* device = nullptr;
}AudioDevice;

typedef struct AudioContext 
{
	ALCcontext* context = nullptr;
}AudioContext;

class OpenALWrapper
{
public:
	static OpenALWrapper* getInstance();

	AudioDevice* openDefaultAudioDevice();
	AudioContext* createAudioContext(AudioDevice* audioDevice);
	void createAudioListener();

	Sound* loadSoundFromFile(const char* filePath);
	void playSound(Sound* soundToPlay);

	void destroySound(Sound* soundToDestroy);
	void closeAudioDevice(AudioDevice* deviceToClose);
	void destroyAudioContext(AudioContext* contextToDestroy);
private:
	static OpenALWrapper* instance;
};

