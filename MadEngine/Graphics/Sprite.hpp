#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include "../../stdafx.h"
#include "Texture.hpp"

namespace Mad
{
	namespace Graphics
	{
		class SpriteData;

		class Animation
		{
		public:
			Animation(SpriteData& data);

			void setLength(float time);
			void addFrame(int index);

			void draw(sf::Sprite& sp, const b2Vec2& size, float time, bool looped) const;

		private:
			SpriteData& m_Data;
			float m_Length;
			std::vector<sf::Rect<int> > m_Frames;
		};

		class SpriteData : public Mad::Interface::IResource
		{
		public:
			SpriteData();
			~SpriteData();

			void setTexture(Texture* tex);
			void divideIntoFrames(int frameW, int frameH);

			void loadFromJSON(const std::string& name);
			void unload();

			Texture* getTexture();
			Animation* addAnimation(const std::string& name);
			Animation* getAnimation(const std::string& name);
			const Animation* getAnimation(const std::string& name) const;
			sf::Rect<int> getFrameArea(int frameIndex) const;

		private:
			Texture* m_Texture;
			std::map<std::string, Animation*> m_Animations;
			std::vector<sf::Rect<int> > m_Frames;

			SpriteData(const SpriteData&);
		};

		class Sprite
		{
		public:
			Sprite();
			explicit Sprite(const std::string& spriteDataName);
			explicit Sprite(const SpriteData* sd);

			void setSource(const std::string& spriteDataName);
			void setSource(const SpriteData* sd);

			void setAnimation(const std::string& name);
			void setLooped(bool looped);
			void setTime(float time);
			float getTime() const;

			const Animation* getAnimation() const;

			void setPosition(const b2Vec2& pos);
			b2Vec2 getPosition() const;
			void setOrigin(const b2Vec2& org);
			void setDefaultOrigin();
			b2Vec2 getOrigin() const;
			void setSize(const b2Vec2& size);
			void setDefaultSize();
			b2Vec2 getSize() const;
			void setRotation(float rot);
			float getRotation() const;

			void draw(float time);

		private:
			const SpriteData* m_Data;
			const Animation* m_Anim;
			bool m_Looped;
			float m_Time;
			sf::Sprite m_Sprite;
			bool m_defOrigin;
			b2Vec2 m_Size;
		};
	}
}

#endif /* _SPRITE_HPP_ */
