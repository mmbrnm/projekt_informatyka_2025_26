#include "Ball.h"
#include <cmath> 

// Konstruktor: ustawia promieñ, kolor, prêdkoœæ pocz¹tkow¹ i pozycjê
Ball::Ball(float startX, float startY)
    : promien(10.0f), predkosc(300.0f, -300.0f)
{
    shape.setRadius(promien);
    shape.setFillColor(sf::Color::White);

    // Ustawienie punktu zaczepienia (origin) na œrodek ko³a
    // Dziêki temu wspó³rzêdne (x,y) oznaczaj¹ œrodek pi³ki, a nie lewy górny róg
    shape.setOrigin(promien, promien);
    shape.setPosition(startX, startY);
}

// Aktualizuje pozycjê pi³ki na podstawie prêdkoœci i up³ywu czasu (dt)
void Ball::update(float dt) {
    shape.move(predkosc * dt);
}

// Rysuje pi³kê w oknie
void Ball::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}

// Zwraca prostok¹t obramowuj¹cy (potrzebne do detekcji kolizji)
sf::FloatRect Ball::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

// Zwraca aktualn¹ pozycjê œrodka pi³ki
sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

// Zwraca promieñ pi³ki
float Ball::getRadius() const {
    return promien;
}

// Zwraca sk³adow¹ poziom¹ prêdkoœci
float Ball::getVelocityX() const {
    return predkosc.x;
}

// Zwraca sk³adow¹ pionow¹ prêdkoœci
float Ball::getVelocityY() const {
    return predkosc.y;
}

// Odwraca prêdkoœæ poziom¹ (odbicie od bocznych œcian)
void Ball::reverseVelocityX() {
    predkosc.x *= -1;
}

// Odwraca prêdkoœæ pionow¹ (odbicie od sufitu, paletki lub klocka)
void Ball::reverseVelocityY() {
    predkosc.y *= -1;
}

// Ustawia konkretn¹ wartoœæ prêdkoœci poziomej (np. przy odbiciu od paletki pod k¹tem)
void Ball::setVelocityX(float vx) {
    predkosc.x = vx;
}

// Ustawia konkretn¹ wartoœæ prêdkoœci pionowej
void Ball::setVelocityY(float vy) {
    predkosc.y = vy;
}

// Ustawia pozycjê pi³ki (u¿ywane przy wczytywaniu gry)
void Ball::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

// Ustawia pe³ny wektor prêdkoœci (u¿ywane przy wczytywaniu gry)
void Ball::setVelocity(float vx, float vy) {
    predkosc.x = vx;
    predkosc.y = vy;
}