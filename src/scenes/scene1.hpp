#pragma once

#include "../base/scene.hpp"
#include "../skyfall.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SkyFall
{
    namespace Scenes
    {
        class Scene1 : public BaseScene
        {
        private:
            sf::RectangleShape m_background;
        public:
            Scene1();
        public:
            virtual void draw(sf::RenderTarget& renderTarget) override;
            virtual void update(float f_delta) override;
        };
    }
};
