//
// Created by jesse on 31/10/2023.
//

#include <fmod_errors.h>
#include <algorithm>
#include "AudioWrapper.hpp"



AudioWrapper::AudioWrapper() : system(nullptr) {
    FMOD_RESULT result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        Logger::Error("FMOD system creation failed: " + std::string(FMOD_ErrorString(result)));
    } else {
        result = system->init(32, FMOD_INIT_NORMAL, nullptr); // Use system->init
        if (result != FMOD_OK) {
            Logger::Error("FMOD system initialization failed: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

AudioWrapper::~AudioWrapper() {
    if (system) {
        FMOD_RESULT result = system->release();
        if (result != FMOD_OK) {
            Logger::Error("Failed to release FMOD system: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

void AudioWrapper::CleanUp() {
    if (system) {
        FMOD_RESULT result = system->release();
        if (result != FMOD_OK) {
            Logger::Error("Failed to release FMOD system: " + std::string(FMOD_ErrorString(result)));
        }
        system = nullptr;
    }
}

int AudioWrapper::FindAvailableSFXChannel() const {
    int availableSFXChannels = ConfigSingleton::GetInstance().getAmountOfSFXChannels();

    if (availableSFXChannels <= 0) {
        Logger::Error("Invalid SFX channel count.");
        return -1;
    }

    for (int i = 0; i < availableSFXChannels; ++i) {
        if (soundEffectsChannelMap.find(i) == soundEffectsChannelMap.end()) {
            return i;
        }
    }
    return -1; // No available channel found
}

void AudioWrapper::PlaySound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    if (!IsValidAudioPath(audioComponent)) {
        Logger::Error("Invalid audio file path.");
        return;
    }

    int availableSFXChannels = ConfigSingleton::GetInstance().getAmountOfSFXChannels();

    if (availableSFXChannels <= 0) {
        Logger::Error("No available SFX channels.");
        return;
    }

    if (audioComponent.isSoundTrack) {
        if (soundTrackChannel < availableSFXChannels) {
            Logger::Error("SoundTrack channel should be greater than available SFX channels.");
            return;
        }

        soundTrackChannelPair.first = soundTrackChannel; // Set the channel ID
        soundTrackChannelPair.second->setVolume(audioComponent.volume); // Set volume

        // Check if there's an existing SoundTrack channel pair
        if (soundTrackChannelPair.second) {
            soundTrackChannelPair.second->stop(); // Stop the current SoundTrack
        }

        FMOD::Sound* sound = nullptr;
        FMOD_RESULT result = system->createSound(audioComponent.getAudioPath().c_str(), FMOD_DEFAULT, 0, &sound);

        if (result != FMOD_OK) {
            Logger::Error("Failed to create sound: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        result = system->playSound(sound, nullptr, true, &soundTrackChannelPair.second);

        if (result != FMOD_OK) {
            Logger::Error("Failed to play sound on SoundTrack channel: " + std::string(FMOD_ErrorString(result)));
            return;
        }
        Logger::Debug("Uploaded sound to Soundtrack Channel: " + std::to_string(soundTrackChannel) + ", Path: " + audioComponent.getAudioPath());
    } else { // SoundEffect
        // Find an available SFX channel to play the sound
        int channelID = FindAvailableSFXChannel();

        if (channelID == -1) {
            Logger::Debug("All SFX channels are currently in use.");
            return;
        }

        FMOD::Sound* sound = nullptr;
        FMOD_RESULT result = system->createSound(audioComponent.getAudioPath().c_str(), FMOD_DEFAULT, 0, &sound);

        if (result != FMOD_OK) {
            Logger::Error("Failed to create sound: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        // Play the sound on the available SFX channel
        FMOD::Channel* channel = nullptr;
        result = system->playSound(sound, nullptr, false, &channel);

        if (result != FMOD_OK) {
            Logger::Error("Failed to play sound on SFX channel: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        // Set the channel's ID and volume
        channel->setUserData(reinterpret_cast<void*>(channelID));
        channel->setVolume(audioComponent.volume);

        // Add the channel to the map
        soundEffectsChannelMap[channelID] = channel;

        Logger::Debug("Uploaded sound to Channel: " + std::to_string(channelID) + ", Path: " + audioComponent.getAudioPath());
    }
}

bool AudioWrapper::IsValidAudioPath(const AudioComponent& audioComponent){
    std::ifstream file(audioComponent.getAudioPath());

    if (!file.good()) {
        Logger::Error("Audio file not found at path: " + audioComponent.getAudioPath());
        return false;
    }

    // Extract the file extension
    size_t dotIndex = audioComponent.getAudioPath().find_last_of('.');
    if (dotIndex == std::string::npos) {
        Logger::Error("Invalid audio file path (no file extension): " + audioComponent.getAudioPath());
        return false;
    }

    std::string extension = audioComponent.getAudioPath().substr(dotIndex + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // List of common audio file extensions
    const std::vector<std::string> audioExtensions = {"mp3", "wav", "ogg", "flac", "aac", "m4a"};

    // Check if the extension is in the list of common audio file extensions
    if (std::find(audioExtensions.begin(), audioExtensions.end(), extension) == audioExtensions.end()) {
        Logger::Error("Invalid audio file extension at path: " + audioComponent.getAudioPath());
        return false;
    }

    return true;
}

