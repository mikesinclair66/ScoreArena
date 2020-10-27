#include <iostream>
#include "map.h"
#include "menu.h"
#include "selector.h"

using namespace Game;
using namespace MenuItems;
using namespace sf;
using namespace std;

int main()
{
    VideoMode vm = VideoMode::getDesktopMode();
    RenderWindow window(VideoMode(vm.width, vm.height), "Score Arena v1.0", Style::Fullscreen);
    window.setPosition(Vector2i(0, 0));

    Menu menu(vm.width, vm.height);
    menu.setActive(true, window);

    Map map(vm.width, vm.height);

    while (window.isOpen())
    {
        if (menu.getExitQueue())
            window.close();
        if (menu.getStartGameQueue()) {
            //get map texture and required stats to start game
            switch (menu.getSelectedMap()) {
            case 1:
                //map = map1();
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            default:
                throw runtime_error("Selected map variable not recorded.");
                break;
            }
            map.loadMenuStats(menu);
            map.initPoints();
            map.setActive(true);

            //return game queue to false since it now has been activated
            menu.setStartGameQueue(false);
        }

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
                    else {
                        menu.keyPressed();
                        if (map.isActive()) {
                            map.players[0].keyPressed(map.clock);
                            map.players[1].keyPressed(map.clock);
                        }
                    }
                    break;
                case Event::KeyReleased:
                    menu.keyReleased(event);
                    if (map.isActive()) {
                        map.players[0].keyReleased(event, map.clock);
                        map.players[1].keyReleased(event, map.clock);
                    }
                    break;
                case Event::MouseMoved:
                    menu.mouseMoved();
                    break;
                case Event::MouseButtonReleased:
                    if (event.mouseButton.button == Mouse::Left)
                        menu.mouseReleased();
            }
        }

        window.clear();
        menu.draw(window);
        map.draw(window);
        window.display();
    }

    return 0;
}