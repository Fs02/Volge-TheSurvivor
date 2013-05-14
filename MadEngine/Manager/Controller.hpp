#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "Exceptions.hpp"

namespace Mad
{
	namespace Manager
	{
		class Controller
		{
		public:
			enum Type{
				Keyboard,
				Mouse
			};
			static Controller* initialise();
			static void deinitialise();

			static Controller* getSingleton();
			static bool getControl(const std::string& name);

			static void setKeyboardControl(const std::string& name, sf::Keyboard::Key keyboardCode);
			static void setMouseControl(const std::string& name, sf::Mouse::Button mouseButtonCode);

		private:
			Controller();
			~Controller();

			struct Keys{
				Type ControllerType;
				sf::Keyboard::Key KeyboardCode;
				sf::Mouse::Button mouseButton;
			};
			static Controller *instance;
			static std::map<std::string,Keys> m_KeyMap;
		};
	}
}

#endif