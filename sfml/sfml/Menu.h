#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Maksymalna liczba elementów w menu (Nowa Gra, Wczytaj, Wyjœcie)
#define MAX_ITEMS 3

class Menu {
public:
    // Konstruktor: inicjalizuje wygl¹d i pozycjê opcji menu
    Menu(float width, float height, sf::Font& font);

    ~Menu();

    // Rysuje elementy menu w podanym oknie
    void draw(sf::RenderWindow& window);

    // Przesuwa zaznaczenie o jedn¹ pozycjê w górê
    void MoveUp();

    // Przesuwa zaznaczenie o jedn¹ pozycjê w dó³
    void MoveDown();

    // Zwraca indeks aktualnie wybranej opcji (0, 1, 2...)
    int GetPressedItem() const { return selectedItemIndex; }

private:
    int selectedItemIndex;           // Przechowuje indeks zaznaczonej opcji
    sf::Font* font;                  // WskaŸnik na czcionkê (by unikn¹æ kosztownego kopiowania obiektu)
    std::vector<sf::Text> menuItems; // Lista obiektów tekstowych wyœwietlanych w menu
};