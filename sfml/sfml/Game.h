#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> 
#include "Ball.h"
#include "Paddle.h"
#include "Stone.h"

class Game {
private:
    // --- OBIEKTY GRY ---
    Paddle m_paletka;
    Ball m_pilka;
    std::vector<Stone> m_bloki;

    // --- ZMIENNE STANU ---
    int m_score;        // Aktualny wynik punktowy
    float m_totalTime;  // £¹czny czas rozgrywki
    bool m_gameOver;    // Flaga okreœlaj¹ca koniec gry

    // --- ELEMENTY INTERFEJSU (UI) ---
    sf::Text m_scoreText;
    sf::Text m_timerText;
    sf::Text m_gameOverText;
    sf::Font* m_font; // WskaŸnik na czcionkê (zasób zarz¹dzany w main)

    // Metoda pomocnicza: resetuje i uk³ada klocki na planszy
    void initLevel();

public:
    // Konstruktor: inicjalizuje obiekty, teksty i ustawia stan pocz¹tkowy
    Game(sf::Font& font, float screenWidth, float screenHeight);

    // Aktualizuje logikê gry (fizykê, kolizje) na podstawie up³ywu czasu (dt)
    void update(sf::Time dt, float screenWidth);

    // Rysuje wszystkie elementy gry na podanym celu (np. oknie)
    void render(sf::RenderTarget& target);

    // Tworzy obiekt GameState i zapisuje aktualny stan do pliku
    void saveGame();

    // Próbuje wczytaæ stan gry z pliku. Zwraca true w przypadku powodzenia
    bool loadGame();

    // Resetuje wszystkie parametry gry do stanu pocz¹tkowego (Nowa Gra)
    void reset();
};