#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace sf;

int main()
{
    VideoMode vm = VideoMode::getDesktopMode();
    RenderWindow window(VideoMode(vm.width, vm.height), "Score Arena v1.0", Style::Fullscreen);
    window.setPosition(Vector2i(0, 0));

    Menu menu(vm.width, vm.height);
    menu.setActive(true, window);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;

                //when a key is pressed
                case Event::KeyPressed:
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                        window.close();
                    break;
            }
        }

        window.clear();
        
        menu.draw(window);

        window.display();
    }

    return 0;
}