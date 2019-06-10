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
