#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>

class Stone : public sf::RectangleShape
{
public:
    // **KRYTYCZNA POPRAWKA DLA B£ÊDU C2248:**
    // Umo¿liwienie dostêpu do metody draw klasy bazowej w klasie Stone.
    using sf::RectangleShape::draw;

    // Deklaracja statycznej tablicy kolorów
    static const std::array<sf::Color, 4> colorLUT;

    // Konstruktor
    Stone(sf::Vector2f startPos, sf::Vector2f size, int initialHP)
        : sf::RectangleShape(size), hp(initialHP), isDestroyed(false)
    {
        this->setPosition(startPos);
        this->setOutlineThickness(2.0f);
        this->setOutlineColor(sf::Color::Black);

        aktualizujKolor();
    }

    // Metoda trafienie()
    void trafienie()
    {
        if (isDestroyed) return;

        hp--;
        aktualizujKolor();

        if (hp <= 0)
        {
            isDestroyed = true;
        }
    }

    // Getter
    bool isDestroyedStatus() const
    {
        return isDestroyed;
    }

    // Przes³oniêcie draw()
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        if (!isDestroyed)
        {
            // Prawid³owe wywo³anie klasy bazowej
            sf::RectangleShape::draw(target, states);
        }
    }

private:
    int hp;
    bool isDestroyed;

    void aktualizujKolor()
    {
        int colorIndex = std::min(hp, (int)colorLUT.size() - 1);
        colorIndex = std::max(0, colorIndex);

        this->setFillColor(colorLUT[colorIndex]);
    }
};