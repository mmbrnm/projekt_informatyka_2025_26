#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Menu.h"

// Definicja mo¿liwych stanów aplikacji
enum class AppState {
    Menu,
    Playing,
    Scores,
    Exiting
};

int main() {
    // Konfiguracja okna
    const int WIDTH = 800;
    const int HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arkanoid - Projekt 5");
    window.setFramerateLimit(60);

    // £adowanie czcionki systemowej
    sf::Font font;
    if (!font.loadFromFile("fast_money.ttf")) {
        std::cerr << "Blad: Nie udalo sie zaladowac czcionki!" << std::endl;
        return -1;
    }

    // Inicjalizacja g³ównych obiektów: Menu oraz Logiki Gry
    Menu menu(WIDTH, HEIGHT, font);
    Game game(font, WIDTH, HEIGHT);

    AppState currentState = AppState::Menu;
    sf::Clock clock;

    // G³ówna pêtla aplikacji
    while (window.isOpen()) {
        // Obliczenie czasu klatki (Delta Time)
        sf::Time dt = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            // Obs³uga zamkniêcia okna przyciskiem 'X'
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Obs³uga wejœcia w zale¿noœci od stanu aplikacji
            if (currentState == AppState::Menu) {
                if (event.type == sf::Event::KeyPressed) {
                    // Nawigacja po menu
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.MoveUp();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        menu.MoveDown();
                    }
                    // Zatwierdzenie wyboru
                    if (event.key.code == sf::Keyboard::Enter) {
                        int selected = menu.GetPressedItem();

                        if (selected == 0) { // Nowa Gra
                            game.reset();
                            currentState = AppState::Playing;
                        }
                        else if (selected == 1) { // Wczytaj Grê
                            if (game.loadGame()) {
                                std::cout << "Gra wczytana poprawnie." << std::endl;
                                currentState = AppState::Playing;
                            }
                            else {
                                std::cout << "Blad wczytywania (brak pliku zapisu)." << std::endl;
                            }
                        }
                        else if (selected == 2) { // Wyjœcie
                            currentState = AppState::Exiting;
                        }
                    }
                }
            }
            else if (currentState == AppState::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    // ESC - Powrót do menu
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::Menu;
                    }
                    // F5 - Zapis stanu gry
                    if (event.key.code == sf::Keyboard::F5) {
                        game.saveGame();
                    }
                }
            }
        }

        // Realizacja wyjœcia z aplikacji
        if (currentState == AppState::Exiting) {
            window.close();
            continue;
        }

        // Aktualizacja logiki gry (tylko w trakcie rozgrywki)
        if (currentState == AppState::Playing) {
            game.update(dt, WIDTH);
        }

        // Rysowanie klatki
        window.clear(sf::Color::Black);

        if (currentState == AppState::Menu) {
            menu.draw(window);
        }
        else if (currentState == AppState::Playing) {
            game.render(window);
        }

        window.display();
    }

    return 0;
}