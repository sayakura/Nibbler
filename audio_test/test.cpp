#include "SoundEngine.hpp"

int     main(void)
{
   
    SoundEngine *sound = new SoundEngine();
    sound->playOnce("gameover.wav");
    while (1)
        ;
    return (0);
}