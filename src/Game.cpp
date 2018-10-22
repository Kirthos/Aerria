#include "../include/Game.hpp"
using namespace std;

Game::Game(int state, string nomMap)//state = 0 = on load, state = 1 = on crée
{
    cout << nomMap << " create Game\n";
    sf::RenderWindow& mWindow = Window::getWindow();
    mWindow.setFramerateLimit(60);
    m_world.init(state, nomMap);
}
//void Game::run() //ce run est temporaire et sert a chronometrer, vous pouvez le supprimer et juste decommenter celui qui est en dessous et qui est intacte
//{
//    sf::RenderWindow& mWindow = Window::getWindow();
//    sf::Clock clock;
//    sf::Time timeSinceLastUpdate = sf::Time::Zero;
//    sf::Time const TimePerFrame = sf::seconds(1.f / 60.f);
//
//    while (mWindow.isOpen())
//    {
//        sf::Clock chronoBouclePrincipale;
//
//        sf::Event event;
//        while(mWindow.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                mWindow.close();
//            handlePlayerInput(event);
//        }
//        timeSinceLastUpdate += clock.restart();
//        while(timeSinceLastUpdate > TimePerFrame)
//        {
//            timeSinceLastUpdate -= TimePerFrame;
//        sf::Clock chronoUpdate;
//
//        update();
//
//        std::cout << "temp de l'update: " << chronoUpdate.restart().asMicroseconds() << std::endl;        }
//        mWindow.clear();
//        sf::Clock chronoRender;
//
//        render();
//
//        std::cout << "temp du render: " << chronoRender.restart().asMicroseconds() << std::endl;
//
//        mWindow.display();
//
//        std::cout << "temp de la boucle Principale: " << chronoBouclePrincipale.restart().asMicroseconds() << std::endl;
//    }
//}

void Game::run()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time const TimePerFrame = sf::seconds(1.f / 60.f);

    while (mWindow.isOpen())
    {
        sf::Event event;
        while(mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();
            handlePlayerInput(event);
        }
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            update();
        }
        mWindow.clear();
        render();
        mWindow.display();
    }
}

void Game::handlePlayerInput(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseWheelMoved || event.type == sf::Event::MouseButtonPressed|| event.type == sf::Event::MouseButtonReleased)
        m_world.handlePlayerInput(event);
}
void Game::update()
{
    m_world.update();
}

void Game::render()
{
    m_world.render();
}
