#pragma once
#include <SFML/Graphics.hpp>
#include <array>

// Klasa reprezentuj¹ca pojedynczy klocek do zbijania
// Dziedziczy po RectangleShape, co u³atwia rysowanie i zarz¹dzanie pozycj¹/rozmiarem
class Stone : public sf::RectangleShape {
private:
    int punktyZycia;      // Wytrzyma³oœæ klocka (ile razy trzeba go trafiæ)
    bool jestZniszczony;  // Flaga okreœlaj¹ca, czy klocek zosta³ ju¿ zniszczony

    // Tablica kolorów (Look-Up Table) przypisana do poziomów ¿ycia
    static const std::array<sf::Color, 4> colorLUT;

    // Metoda pomocnicza aktualizuj¹ca kolor w zale¿noœci od aktualnego HP
    void aktualizujKolor();

public:
    // Konstruktor inicjalizuj¹cy pozycjê, rozmiar i wytrzyma³oœæ
    Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int hp);

    // Obs³uguje logikê trafienia pi³k¹ (zmniejsza HP, zmienia kolor)
    void trafienie();

    // Zwraca true, jeœli klocek jest zniszczony (HP <= 0)
    bool isDestroyed() const;

    // Zwraca aktualne punkty ¿ycia (wykorzystywane przy zapisie stanu gry)
    int getHP() const;

    // Rysuje klocek na ekranie, jeœli nie jest zniszczony
    void draw(sf::RenderTarget& target) const;
};