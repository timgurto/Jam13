// (C) 2010 Tim Gurto

#include <cassert>
#include "SDL_mixer.h"
#include "Sound.h"
#include "globals.h"
#include "Debug.h"

namespace Game {

extern Debug debug;

int Sound::soundsLoaded_ = 0;

Sound::Sound(const std::string fileName):
fileName_(fileName),
sound_(loadSound(fileName)){}

Sound::Sound(const Sound &original):
fileName_(original.fileName_),
sound_(loadSound(fileName_)){}

Sound::~Sound(){
   unloadSound(sound_);
}

Sound &Sound::operator=(const Sound &rhs){
   if (this != &rhs){
      unloadSound(sound_);
      fileName_ = rhs.fileName_;
      sound_ = loadSound(fileName_);
   }
   return *this;
}

//change volume, directly (0 - MIX_MAX_VOLUME) or by double
void Sound::changeVolume(int volume){
    Mix_VolumeChunk(sound_, volume);
}

void Sound::changeVolume(double volumeLevel){
    int volume = int(volumeLevel * MIX_MAX_VOLUME + 0.5);
    changeVolume(volume);
}

void Sound::play(int channel, int loops) const{
#ifndef NO_ART
   if (!DEBUG)
      if (sound_)
         Mix_PlayChannel(channel, sound_, loops);
#endif
}

void Sound::quit(){
   assert(soundsLoaded_ == 0);
}

Mix_Chunk *Sound::loadSound(const std::string &fileName){
   Mix_Chunk *sound = 0;
   if (fileName != "" && fileName != SOUND_PATH){
      sound = Mix_LoadWAV(fileName.c_str());
      debug("Attempting to load sound: ", fileName);
      assert(sound);
      ++soundsLoaded_;
   }
   return sound;
}

void Sound::unloadSound(Mix_Chunk *&sound){
   if (sound){
      Mix_FreeChunk(sound);
      --soundsLoaded_;
      sound = 0;
   }
}

} // namespace Game
