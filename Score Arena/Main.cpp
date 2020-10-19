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

                case Event::KeyPressed:
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                        window.close();
                    break;

                case Event::MouseMoved:
                    menu.mouseMoved();
                    break;

                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Left)
                        menu.mousePressed();
                    break;
                    
                case Event::MouseButtonReleased:
                    if (event.mouseButton.button == Mouse::Left)
                        menu.mouseReleased();
                    break;
            }
        }

        window.clear();
        
        menu.draw(window);

        window.display();

        if (menu.queueExit)
            window.close();
    }

    return 0;
}