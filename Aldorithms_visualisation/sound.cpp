#include <sound.hpp>

namespace visualisation {
	namespace sound {
		sf::SoundBuffer soundBuf;
		sf::Sound sound;

		void loadAssets() {
			soundBuf.loadFromFile("beep.wav");
			sound.setBuffer(soundBuf);	
			sound.setVolume(50.0f);
		}

		void setVolume(float vol) {
			sound.setVolume(vol);
		}

		void playSound(float pitch) {
			
					sound.setPitch(pitch);
					sound.play();
			
			
		}
	}
}