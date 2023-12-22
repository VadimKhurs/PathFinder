#include <resource.hpp>
namespace visualisation {
	namespace sound {
		extern sf::SoundBuffer soundBuf;
		extern sf::Sound sound;

		void loadAssets();
		void setVolume(float vol);
		void playSound(float pitch);
		

	}
}