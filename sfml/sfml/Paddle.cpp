#include "Paddle.h"

// Konstruktor: ustawia rozmiar, prêdkoœæ, kolor i pozycjê pocz¹tkow¹ paletki
Paddle::Paddle(float startX, float startY)
    : rozmiar(100.0f, 20.0f), predkosc(500.0f)
{
    shape.setSize(rozmiar);
    shape.setFillColor(sf::Color::White);

    // Ustawienie punktu zaczepienia (origin) na œrodek u³atwia obliczanie odbiæ i kolizji
    shape.setOrigin(rozmiar.x / 2.0f, rozmiar.y / 2.0f);
    shape.setPosition(startX, startY);
}

// Obs³uga sterowania klawiatur¹ i poruszania paletk¹
void Paddle::update(float windowWidth, float dt) {
    // Ruch w lewo (zabezpieczenie przed wyjœciem poza lew¹ krawêdŸ)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (shape.getPosition().x - rozmiar.x / 2.0f > 0) {
            shape.move(-predkosc * dt, 0);
        }
    }
    // Ruch w prawo (zabezpieczenie przed wyjœciem poza praw¹ krawêdŸ)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (shape.getPosition().x + rozmiar.x / 2.0f < windowWidth) {
            shape.move(predkosc * dt, 0);
        }
    }
}

// Rysowanie paletki w oknie
void Paddle::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}

// Zwraca prostok¹t obramowuj¹cy (potrzebne do wykrywania kolizji)
sf::FloatRect Paddle::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

// Zwraca aktualn¹ pozycjê (x, y)
sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}

// Zwraca szerokoœæ paletki (potrzebne do obliczania k¹ta odbicia pi³ki)
float Paddle::getWidth() const {
    return rozmiar.x;
}

// Ustawia paletkê w konkretnym miejscu (u¿ywane przy wczytywaniu gry)
void Paddle::setPosition(float x, float y) {
    shape.setPosition(x, y);
}