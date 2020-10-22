#include "menu.h"
#include "selector.h"

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
        if (menu.getExitQueue())
            window.close();

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
                    else
                        menu.keyPressed();
                    break;

                case Event::KeyReleased:
                    menu.keyReleased(event);
                    break;
                    
                case Event::MouseMoved:
                    menu.mouseMoved();
                    break;
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}