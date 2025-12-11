#include "Menu.h"

Menu::Menu(float width, float height, sf::Font& fontRef) {
    font = &fontRef;
    selectedItemIndex = 0;

    // Tablica nazw opcji menu
    std::string options[MAX_ITEMS] = { "Nowa Gra", "Wczytaj Gre", "Wyjscie" };

    for (int i = 0; i < MAX_ITEMS; i++) {
        sf::Text text;
        text.setFont(*font);
        text.setString(options[i]);
        text.setCharacterSize(40);

        // Ustawienie pozycji:
        // X: Œrodek ekranu przesuniêty w lewo (by wyœrodkowaæ tekst)
        // Y: Równomierne roz³o¿enie w pionie
        text.setPosition(sf::Vector2f(width / 2.0f - 100.0f, height / (MAX_ITEMS + 1) * (i + 1)));

        // Logika kolorów: Pierwszy element zaznaczony (Czerwony), reszta bia³a
        if (i == 0) {
            text.setFillColor(sf::Color::Red);
        }
        else {
            text.setFillColor(sf::Color::White);
        }

        menuItems.push_back(text);
    }
}

Menu::~Menu() {}

// Rysuje wszystkie elementy tekstu menu w oknie
void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

// Obs³uga klawisza W GÓRÊ
void Menu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        // Odznaczamy obecny element (na bia³o)
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);

        // Zmniejszamy indeks
        selectedItemIndex--;

        // Zaznaczamy nowy element (na czerwono)
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

// Obs³uga klawisza W DÓ£
void Menu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_ITEMS) {
        // Odznaczamy obecny element
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);

        // Zwiêkszamy indeks
        selectedItemIndex++;

        // Zaznaczamy nowy element
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}