#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <alsa/asoundlib.h>

#define CHANNELS 2
#define FRAMES 768
int main(int argc, char * argv[])
{
    
    snd_pcm_t * pcm;
    snd_pcm_hw_params_t *params;
    FILE * fd = fopen(argv[1], "w");

    int ret = snd_pcm_open(&pcm, "hw:0", SND_PCM_STREAM_CAPTURE,0);

    snd_pcm_hw_params_alloca(&params);
    ret = snd_pcm_hw_params_any(pcm,params);

    ret = snd_pcm_hw_params_set_access(pcm,params,SND_PCM_ACCESS_RW_INTERLEAVED);

    ret = snd_pcm_hw_params_set_format(pcm,params, SND_PCM_FORMAT_S32_LE);

    ret = snd_pcm_hw_params_set_channels(pcm,params,CHANNELS);

    int rate = 48000;

    ret = snd_pcm_hw_params_set_rate_near(pcm,params, &rate,0);

    int size = FRAMES*CHANNELS*sizeof(uint32_t);
    char *buffer = malloc(size);

    int audio_fd = open(argv[1], O_RDONLY);
    while(1)
    {
        int n = read(audio_fd, buffer, FRAMES*CHANNELS*sizeof(uint32_t));
        if (n <= 0)
        {
            break;
        }
        ret = snd_pcm_writei(pcm,buffer, n /4 / 2);
        if(ret == -EPIPE)
        {
            snd_pcm_prepare(pcm);
        }
        else if(ret<0)
        {
            printf("Writei error\n\r");
        }
        else if(ret != n /4 / 2)
        {

        }

    }
    snd_pcm_drain(pcm);

    close(audio_fd);
    snd_pcm_hw_params_free(params);
    snd_pcm_close(pcm);

    return 0;
}