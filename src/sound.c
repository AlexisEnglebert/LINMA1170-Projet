#include "sound.h"

const int AMPLITUDE = 10000;
const int SAMPLE_RATE = 41000; 

double frequency = 440.0f;

void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes)
{
    Sint16 *buffer = (Sint16*)raw_buffer;
    int length = bytes / 2;
    int sample_nr = *(int*)user_data;

    for(int i = 0; i < length; i++, sample_nr++)
    {
        double time = (double)sample_nr / (double)SAMPLE_RATE;
        buffer[i] = (Sint16)(AMPLITUDE * sinf(2.0f * M_PI * frequency * time));
    }
}

int InitSoundSystem(){
    SDL_Init(SDL_INIT_AUDIO);

	int sample_nr = 0;
	SDL_AudioSpec desiredSpec;
	desiredSpec.freq = SAMPLE_RATE;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1; 
    desiredSpec.samples = 1024; 
    desiredSpec.callback = audio_callback;
    desiredSpec.userdata = &sample_nr;

	SDL_AudioSpec have;
	if(SDL_OpenAudio(&desiredSpec, &have) != 0){
		fprintf(stderr,"ERROR\n");
		return -1;
	}

    if(desiredSpec.format != have.format){
		fprintf(stderr, "ERROR\n");
		return -1;
	}

    return 0;
}
void PlayFrequency(double freq, uint32_t duration){
    
    frequency = freq;

    SDL_PauseAudio(0);
    SDL_Delay(duration);
    SDL_PauseAudio(1);
}

int CloseSoundSystem(){
    SDL_CloseAudio();
    return 0;
};