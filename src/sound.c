#include "sound.h"

static double AMPLITUDE = 10000.0; 
const static double SAMPLE_RATE = 44100.0; 
static double frequency = 440.0f;
static double sub = 0.0;

void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes)
{
    Sint16 *buffer = (Sint16*)raw_buffer;
    int length = bytes / 4;
    int* sample_nr = user_data;

    for(int sid = 0; sid < length; sid++)
    {
        double time = (double)(*sample_nr + sid) / (double)SAMPLE_RATE;
        buffer[2*sid] = (AMPLITUDE * sinf(2.0f * M_PI * frequency * time));
        buffer[2*sid+1] = (AMPLITUDE * sinf(2.0f * M_PI * frequency * time));

        if(AMPLITUDE >= 0)
            AMPLITUDE -= sub;
        
    }
    *sample_nr += length;
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
    
    frequency = 2*freq;
    AMPLITUDE = 10000.0f;
    sub = 500.0/(double)duration;

    SDL_PauseAudio(0);
    SDL_Delay(duration);
    SDL_PauseAudio(1);
}

int CloseSoundSystem(){
    
    SDL_CloseAudio();
    SDL_Quit();
    return 0;
};