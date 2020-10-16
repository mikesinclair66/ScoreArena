#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm = VideoMode::getDesktopMode();
    RenderWindow window(VideoMode(vm.width, vm.height), "Score Arena v1.0", Style::Fullscreen);
    window.setPosition(Vector2i(0, 0));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

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
        
        

        window.display();
    }

    return 0;
}