////////////////////////////////////////////////////////////
//
// FrameClock - Utility class for tracking frame statistics.
// Copyright (C) 2013 Lee R (lee-r@outlook.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once

#include "..\..\..\stdafx.h"
#include "FrameClock.hpp"

class ClockHUD : public sf::Drawable
{
    struct Stat
    {
        sf::Color color;
        std::string str;
    };

    typedef std::vector<Stat> Stats_t;

public:

    ClockHUD(const sfx::FrameClock& clock, const sf::Font& font)
        : m_clock (&clock)
        , m_font  (&font)
    {}

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const
    {
        // Gather the available frame time statistics.
        const Stats_t stats = build();

        sf::Text elem;
        elem.setFont(*m_font);
        elem.setCharacterSize(16);
        elem.setPosition(5.0f, 5.0f);

        // Draw the available frame time statistics.
        for (std::size_t i = 0; i < stats.size(); ++i)
        {
            elem.setString(stats[i].str);
            elem.setColor(stats[i].color);

            rt.draw(elem, states);

            // Next line.
            elem.move(0.0f, 16.0f);
        }
    }

private:

    template<typename T>
    static std::string format(std::string name, std::string resolution, T value)
    {
        std::ostringstream os;
        os.precision(4);
        os << std::left << std::setw(5);
        os << name << " : ";
        os << std::setw(5);
        os << value << " " << resolution;
        return os.str();
    }

    Stats_t build() const
    {
        const int count = 10;
        const Stat stats[count] = {
            { sf::Color::Yellow, format("Time",  "(sec)", m_clock->getTotalFrameTime().asSeconds())        },
            { sf::Color::White,  format("Frame", "",      m_clock->getTotalFrameCount())                   },
            { sf::Color::Green,  format("FPS",   "",      m_clock->getFramesPerSecond())                   },
            { sf::Color::Green,  format("min.",  "",      m_clock->getMinFramesPerSecond())                },
            { sf::Color::Green,  format("avg.",  "",      m_clock->getAverageFramesPerSecond())            },
            { sf::Color::Green,  format("max.",  "",      m_clock->getMaxFramesPerSecond())                },
            { sf::Color::Cyan,   format("Delta", "(ms)",  m_clock->getLastFrameTime().asMilliseconds())    },
            { sf::Color::Cyan,   format("min.",  "(ms)",  m_clock->getMinFrameTime().asMilliseconds())     },
            { sf::Color::Cyan,   format("avg.",  "(ms)",  m_clock->getAverageFrameTime().asMilliseconds()) },
            { sf::Color::Cyan,   format("max.",  "(ms)",  m_clock->getMaxtFrameTime().asMilliseconds())    }
        };
        return Stats_t(&stats[0], &stats[0] + count);
    }

private:

    const sf::Font* m_font;
    const sfx::FrameClock* m_clock;
};