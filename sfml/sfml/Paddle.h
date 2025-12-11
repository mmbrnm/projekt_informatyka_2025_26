#pragma once
#include <SFML/Graphics.hpp>

// Klasa reprezentuj¹ca paletkê sterowan¹ przez gracza
class Paddle {
private:
    sf::RectangleShape shape; // Graficzny kszta³t paletki
    sf::Vector2f rozmiar;     // Wymiary (szerokoœæ, wysokoœæ)
    float predkosc;           // Prêdkoœæ poruszania siê (piksele na sekundê)

public:
    // Konstruktor ustawiaj¹cy pozycjê startow¹
    Paddle(float startX, float startY);

    // Obs³uguje logikê sterowania i aktualizuje pozycjê (z uwzglêdnieniem granic okna)
    void update(float windowWidth, float dt);

    // Rysuje paletkê na podanym celu
    void draw(sf::RenderTarget& target) const;

    // Ustawia paletkê w konkretnym punkcie (u¿ywane przy wczytywaniu stanu gry)
    void setPosition(float x, float y);

    // Zwraca prostok¹t obramowuj¹cy (wymagane do detekcji kolizji)
    sf::FloatRect getGlobalBounds() const;

    // Zwraca aktualn¹ pozycjê obiektu (x, y)
    sf::Vector2f getPosition() const;

    // Zwraca szerokoœæ paletki (pomocne przy obliczaniu k¹ta odbicia pi³ki)
    float getWidth() const;
};