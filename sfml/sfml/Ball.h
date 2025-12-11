#pragma once
#include <SFML/Graphics.hpp>

// Klasa reprezentuj¹ca pi³kê w grze
class Ball {
private:
    sf::CircleShape shape; // Graficzna reprezentacja pi³ki
    float promien;         // Promieñ pi³ki
    sf::Vector2f predkosc; // Wektor prêdkoœci (x, y)

public:
    // Konstruktor: ustawia pozycjê startow¹
    Ball(float startX, float startY);

    // Aktualizuje fizykê pi³ki (ruch) w zale¿noœci od czasu
    void update(float dt);

    // Rysuje pi³kê na ekranie
    void draw(sf::RenderTarget& target) const;

    // Metody dostêpowe (Gettery)
    sf::FloatRect getGlobalBounds() const; // Granice (potrzebne do wykrywania kolizji)
    sf::Vector2f getPosition() const;      // Pozycja œrodka
    float getRadius() const;               // Promieñ

    // Gettery prêdkoœci (potrzebne do zapisu stanu gry i logiki kolizji)
    float getVelocityX() const;
    float getVelocityY() const;

    // Metody modyfikuj¹ce fizykê (odbicia)
    void reverseVelocityX(); // Odbicie od pionowej przeszkody (œciana boczna)
    void reverseVelocityY(); // Odbicie od poziomej przeszkody (sufit, paletka, blok)

    // Settery prêdkoœci (zmiana kierunku lub wartoœci prêdkoœci)
    void setVelocityX(float vx);
    void setVelocityY(float vy);

    // Metody s³u¿¹ce do przywracania stanu gry (Wczytywanie z pliku)
    void setPosition(float x, float y);
    void setVelocity(float vx, float vy);
};