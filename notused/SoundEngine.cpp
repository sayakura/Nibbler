#include "SoundEngine.hpp"

SoundEngine::SoundEngine() {
    _engine = irrklang::createIrrKlangDevice();
    if (!_engine)
		std::cerr << "Could not startup engine" << std::endl;
}

SoundEngine::~SoundEngine() {
    if (_engine)
        _engine->drop(); 
}

void SoundEngine::playLoop(std::string filename) {
    if (_engine)
	    _engine->play2D(filename.c_str(), true);
}

void SoundEngine::playOnce(std::string filename) {
    if (_engine)
	    _engine->play2D(filename.c_str());
}

SoundEngine::SoundEngine(SoundEngine const & other)
{
    static_cast<void>(other);
}

SoundEngine const & SoundEngine::operator=(SoundEngine const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}
