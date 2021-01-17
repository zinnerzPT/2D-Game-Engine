#include "OpenALWrapper.h"
#include "InitError.h"

#include <vector>


//OpenAL error checking
#define OpenAL_ErrorCheck(message)\
{\
	ALenum error = alGetError();\
	if( error != AL_NO_ERROR)\
	{\
		throw InitError(this);\
	}\
}
#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)

OpenALWrapper* OpenALWrapper::instance = nullptr;

OpenALWrapper* OpenALWrapper::getInstance()
{
	if (instance == nullptr) {
		instance = new OpenALWrapper();
	}
	return instance;
}

AudioDevice* OpenALWrapper::openDefaultAudioDevice()
{
	const ALCchar* defaultDeviceString = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
	AudioDevice* audioDevice = new AudioDevice;
	audioDevice->device = alcOpenDevice(defaultDeviceString);
	if (!audioDevice)
	{
		throw InitError(this);
	}
	return audioDevice;
}

AudioContext* OpenALWrapper::createAudioContext(AudioDevice* audioDevice)
{
	AudioContext* audioContext = new AudioContext;
	audioContext->context = alcCreateContext(audioDevice->device, nullptr);
	if (!alcMakeContextCurrent(audioContext->context))
	{
		throw InitError(this);
	}
	return audioContext;
}

void OpenALWrapper::createAudioListener()
{
	alec(alListener3f(AL_POSITION, 0.f, 0.f, 0.f));
	alec(alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));
	ALfloat forwardAndUpVectors[] = 
	{
		1.f, 0.f, 0.f, // forward vector
		0.f, 1.f, 0.f  // up vector
	};
	alec(alListenerfv(AL_ORIENTATION, forwardAndUpVectors));
}

Sound* OpenALWrapper::loadSoundFromFile(const char* filePath)
{
	AudioFile<float> soundFile;
	soundFile.load(filePath);

	std::vector<uint8_t> PCMDataBytes;
	soundFile.writePCMToBuffer(PCMDataBytes);
	auto convertFileToOpenALFormat = [](const AudioFile<float>* audioFile) {
		int bitDepth = audioFile->getBitDepth();
		if (bitDepth == 16)
			return audioFile->isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		else if (bitDepth == 8)
			return audioFile->isStereo() ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
		else
			return -1; // this shouldn't happen!
	};
	ALuint soundBuffer;
	alec(alGenBuffers(1, &soundBuffer));
	alec(alBufferData(soundBuffer, convertFileToOpenALFormat(&soundFile), 
		PCMDataBytes.data(), PCMDataBytes.size(), soundFile.getSampleRate()));

	Sound* loadedSound = new Sound;
	loadedSound->buffer = soundBuffer;
	return loadedSound;
}

void OpenALWrapper::playSound(Sound* soundToPlay, float volume/*= 1.0f*/)
{
	if (soundToPlay->soundSource == -1)
	{
		// Create a sound source for the sound to play
		alec(alGenSources(1, &soundToPlay->soundSource));
		alec(alSourcef(soundToPlay->soundSource, AL_PITCH, 1.f));
		alec(alSourcef(soundToPlay->soundSource, AL_GAIN, volume));
		alec(alSourcei(soundToPlay->soundSource, AL_LOOPING, AL_FALSE));
		alec(alSourcei(soundToPlay->soundSource, AL_BUFFER, soundToPlay->buffer));
	}
	// Play the sound source
	alec(alSourcePlay(soundToPlay->soundSource));
}


void OpenALWrapper::destroySound(Sound* soundToDestroy)
{
	if (soundToDestroy->soundSource != -1)
	{
		alec(alDeleteSources(1, &soundToDestroy->soundSource));
	}
	if (soundToDestroy->buffer != -1)
	{
		alec(alDeleteBuffers(1, &soundToDestroy->buffer));
	}
}

void OpenALWrapper::closeAudioDevice(AudioDevice* deviceToClose)
{
	alcCloseDevice(deviceToClose->device);
}

void OpenALWrapper::destroyAudioContext(AudioContext* contextToDestroy)
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(contextToDestroy->context);
}