#include "../../include/Menu/Menu.hpp"
Menu::Menu()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    mainView.reset(sf::FloatRect(0.f, 0.f, 639.f, 645.f));
    mWindow.setView(mainView);
    mWindow.setMouseCursorVisible(false);

    backPlanT.loadFromFile("ressources/back.png");
    bouton1T.loadFromFile("ressources/Play.png");
    bouton2T.loadFromFile("ressources/Option.png");
    bouton3T.loadFromFile("ressources/Quit.png");
    boutonMultiT.loadFromFile("ressources/multiplay.png");
    cursorT.loadFromFile("ressources/cursor.png");
    cloudT.loadFromFile("ressources/cloud.png");

    sf::Vector2f cacheSize(216, 64);
    cache.setFillColor(sf::Color(0, 0, 0, 50));
    cache.setSize(cacheSize);
    cache.setPosition(200, 200);

    moon.setTexture(moonT);
    sun.setTexture(sunT);
    cloud.setTexture(cloudT);
    cloud2.setTexture(cloudT);
    cursor.setTexture(cursorT);
    bouton1.setTexture(bouton1T);
    bouton2.setTexture(bouton2T);
    bouton3.setTexture(bouton3T);
    boutonMulti.setTexture(boutonMultiT);

    backPlan.setTexture(backPlanT);
    backPlan.setScale(0.332812, 0.597222);

    cursor.setTexture(cursorT);
    bouton1.setPosition(214.5, 207.5);
    bouton1.setScale(0.8, 0.8);
    bouton2.setPosition(214.5, 287.5);
    bouton2.setScale(0.8, 0.8);
    bouton3.setPosition(214.5, 367.5);
    bouton3.setScale(0.8, 0.8);
    boutonMulti.setPosition(214.5, 447.5);
    boutonMulti.setScale(0.8, 0.8);
    cursor.setOrigin(0, 0);
    cursor.setPosition(0, 0);
    backPlan.setPosition(0, 0);
    cloudPos.x = -1;
    cloudPos.y = -200;
    cloud2Pos.x = 0;
    cloud2Pos.y = -200;

    cloud.setPosition(cloudPos.x, 0);
    cloud2.setPosition(cloud2Pos.x, 0);

    sunPos.x = -1;
    sunPos.y = 20;
    moonPos.x = 0;
    moonPos.y = 20;

    sun.setPosition(sunPos.x, 0);
    moon.setPosition(moonPos.x, 0);

    cacheActivated = false;

    //fond.openFromFile("ressources/menu1.ogg");
    //fond.setLoop(true);
}

void Menu::run()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f/20.f); //frame setting
    mWindow.setVerticalSyncEnabled(true);
    sf::Event event;
    //fond.play();
    while (mWindow.isOpen())
    {
        update();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            updateSM();
            updateCloud();
            update();
        }
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window::closeWindow();
                return;
            }

        }
        render();
    }
}

void Menu::update()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    MousePos = sf::Mouse::getPosition(mWindow);
    MousePosCoo = mWindow.mapPixelToCoords(MousePos);
    cursor.setPosition(MousePosCoo);
    tempCache = checkBox(MousePosCoo.x, MousePosCoo.y);
    if (tempCache != 0)
    {
        cacheActivated = true;
        if (tempCache == 1)
            cache.setPosition(214.5, 207.5);
        else if (tempCache == 2)
            cache.setPosition(214.5, 287.5);
        else if (tempCache == 3)
            cache.setPosition(214.5, 367.5);
        else if (tempCache == 4)
            cache.setPosition(214.5,447.5);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
    {
        tempCache = checkBox(MousePosCoo.x, MousePosCoo.y);
        if (tempCache != 0)
        {
            if(tempCache == 1)
            {
                mWindow.setMouseCursorVisible(true);
                Game game(0,"Test");
                game.run();
            }
            if (tempCache == 3)
                mWindow.close();
            if (tempCache == 4)
                m_sousMenuMulti.launch(cursor);
        }
    }

}

void Menu::updateSM()
{
    sunPos.x = sunPos.x +10;
    if (sunPos.x > 639)
        sunPos.x = 0;
    moonPos.x = moonPos.x +10;
    if (moonPos.x > 0)
        moonPos.x = -639;
    sun.setPosition(sunPos);
    moon.setPosition(moonPos);
}

void Menu::updateCloud()
{
    cloudPos.x = cloudPos.x +1;
    if (cloudPos.x > 639)
        cloudPos.x = 0;
    cloud2Pos.x = cloud2Pos.x +1;
    if (cloud2Pos.x > 0)
        cloud2Pos.x = -639;
    cloud.setPosition(cloudPos);
    cloud2.setPosition(cloud2Pos);
}

const void Menu::render()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    mWindow.clear();
    mWindow.draw(backPlan);
  //  mWindow.draw(sun);
  //  mWindow.draw(moon);
    mWindow.draw(cloud);
    mWindow.draw(cloud2);
    mWindow.draw(bouton1);
    mWindow.draw(bouton2);
    mWindow.draw(bouton3);
    mWindow.draw(boutonMulti);
    mWindow.draw(cursor);
    if (cacheActivated)
        mWindow.draw(cache);
    mWindow.display();
}

int Menu::checkBox(float x, float y)
{
    if ((x > 214.5 && x < 430.5) && (y > 207.5 && y < 271.5))
    {
        return (1);
    }
    if ((x > 214.5 && x < 430.5) && (y > 287.5 && y < 351.5))
    {

        return (2);
    }
    if ((x > 214.5 && x < 430.5) && (y > 367.5 && y < 431.5))
    {

        return (3);
    }
    if ((x > 214.5 && x < 430.5) && (y > 447.5 && y < 501.5))
    {

        return (4);
    }
    cacheActivated = false;
    return (0);
}
