#ifndef SE_HPP
#define SE_HPP

#include <iostream>
#include <irrKlang/irrKlang.h>

class SoundEngine
{
    irrklang::ISoundEngine* _engine; 
    SoundEngine(SoundEngine &);
    SoundEngine& operator=(const SoundEngine& rhs );
    public:
        SoundEngine();
        ~SoundEngine();
        void playLoop(std::string);
        void playOnce(std::string);
};

#endif
