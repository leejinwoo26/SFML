#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Game
{
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key,
        bool isPressed);
private:
    sf::RenderWindow mWindow;
    sf::Time TimePerFrame;
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    float PlayerSpeed;
};

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "SFML Application")
    , mPlayer() 
    , PlayerSpeed(500.f) 
    , mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false)
    , TimePerFrame()
    , mTexture()
{
   
}
void Game::run()
{
    sf::Clock clock;
    while (mWindow.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}
void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}
void Game::handlePlayerInput(sf::Keyboard::Key key,
    bool isPressed)
{
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}
void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;

    mPlayer.move(movement * deltaTime.asSeconds());
}
void Game::render()
{
    if (!mTexture.loadFromFile("Textures/mother.jpg"))
    {
    }
    mPlayer.setTexture(mTexture);
    mPlayer.setScale(0.5, 0.5);

    mWindow.clear();    
    mWindow.draw(mPlayer);
    mWindow.display();
}



int main()
{
    Game game;
    game.run();
}

