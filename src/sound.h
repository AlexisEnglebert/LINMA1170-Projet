#pragma once
#include <SDL2/SDL.h>



int InitSoundSystem();
void PlayFrequency(double freq, uint32_t duration);
int CloseSoundSystem();