#pragma once

#include "..\..\stdafx.h"
#include "Sprite.hpp"

namespace Mad
{
	namespace Graphics
	{
		class AniSprite:
			public Mad::Graphics::Sprite
		{
		private:
			sf::Clock m_Clock;
			int m_Fps;
			bool m_IsPlaying;
			bool m_IsInvert;
			int m_LoopStart;
			int m_LoopEnd;
			int m_CurrentFrame;
			int m_FrameWidth;
			int m_FrameHeight;

		public:
			AniSprite();
			AniSprite(const std::string& textureId, int frameWidth, int frameHeight);
			~AniSprite();
			
			sf::IntRect getFrameRect(int frame);
			int getFrameCount();
			int getCurrentFrame();

			void setFrameSize(int frameWidth, int frameHeight);
			void setCurrentFrame(int frame);
			void setLoopSpeed(int fps);
			void setInvertSprite(bool flag);

			void play();
			void play(int start, int end);

			bool isPlaying();
			bool isPlaying(int start, int end);

			void stop();

			void update();
		};
	}
}