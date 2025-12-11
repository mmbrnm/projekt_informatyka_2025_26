#include "Stone.h"
#include <algorithm> // Do std::max

// Tablica kolorów przypisana do punktów ¿ycia (HP)
// Indeks 0 = zniszczony, 1 = czerwony, 2 = ¿ó³ty, 3 = niebieski
const std::array<sf::Color, 4> Stone::colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue
};

// Konstruktor: ustawia pozycjê, rozmiar i pocz¹tkowy kolor klocka
Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int hp)
    : punktyZycia(hp), jestZniszczony(false)
{
    setPosition(startPos);
    setSize(rozmiar);

    // Ustawienie obramowania dla lepszej widocznoœci
    setOutlineThickness(2.0f);
    setOutlineColor(sf::Color(80, 80, 80));

    aktualizujKolor();
}

// Obs³uga uderzenia pi³ki w klocek
void Stone::trafienie() {
    if (jestZniszczony) {
        return;
    }

    punktyZycia--; // Zmniejszenie HP

    if (punktyZycia <= 0) {
        punktyZycia = 0;
        jestZniszczony = true;
    }

    aktualizujKolor(); // Odœwie¿enie wygl¹du po utracie HP
}

// Ustawia kolor klocka na podstawie aktualnego HP korzystaj¹c z tablicy colorLUT
void Stone::aktualizujKolor() {
    int colorIndex = punktyZycia;

    // Zabezpieczenie przed wyjœciem poza zakres tablicy kolorów
    if (colorIndex >= static_cast<int>(colorLUT.size())) {
        colorIndex = static_cast<int>(colorLUT.size()) - 1;
    }

    setFillColor(colorLUT[colorIndex]);
}

// Zwraca informacjê, czy klocek zosta³ zniszczony
bool Stone::isDestroyed() const {
    return jestZniszczony;
}

// Rysuje klocek w oknie, tylko jeœli nie jest zniszczony
void Stone::draw(sf::RenderTarget& target) const {
    if (!jestZniszczony) {
        // Rzutowanie na klasê bazow¹ RectangleShape, aby wywo³aæ domyœlne rysowanie
        target.draw(static_cast<const sf::RectangleShape&>(*this));
    }
}

// Zwraca aktualn¹ liczbê punktów ¿ycia (potrzebne do zapisu stanu gry)
int Stone::getHP() const
{
    return punktyZycia;
}