#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <string>
#include <cmath> // std::abs

// Sta³e konfiguracyjne poziomu
const int ILOSC_KOLUMN = 7;
const int ILOSC_WIERSZY = 6;
const float PRZERWA = 2.0f;
const float OFFSET_TOP = 50.0f;
const float ROZMIAR_BLOKU_Y = 25.0f;

// Konstruktor: Inicjalizacja obiektów, tekstów i generowanie poziomu
Game::Game(sf::Font& font, float screenWidth, float screenHeight)
    : m_paletka(screenWidth / 2.0f, screenHeight - 40.0f),
    m_pilka(screenWidth / 2.0f, screenHeight / 2.0f),
    m_score(0), m_totalTime(0.0f), m_gameOver(false), m_font(&font)
{
    // Konfiguracja tekstu punktacji
    m_scoreText.setFont(*m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(screenWidth - 250.0f, 10.0f);

    // Konfiguracja tekstu czasu
    m_timerText.setFont(*m_font);
    m_timerText.setCharacterSize(24);
    m_timerText.setFillColor(sf::Color::White);
    m_timerText.setPosition(10.0f, 10.0f);

    // Konfiguracja napisu Game Over
    m_gameOverText.setFont(*m_font);
    m_gameOverText.setString("GAME OVER\n Press ESC");
    m_gameOverText.setCharacterSize(35);
    m_gameOverText.setFillColor(sf::Color::Red);

    // Wyœrodkowanie napisu Game Over na ekranie
    sf::FloatRect textRect = m_gameOverText.getLocalBounds();
    m_gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_gameOverText.setPosition(screenWidth / 2.0f, screenHeight / 2.0f);

    initLevel();
}

// Generuje uk³ad klocków na podstawie sta³ych
void Game::initLevel() {
    m_bloki.clear();

    // Obliczamy szerokoœæ bloku tak, aby wype³ni³y ekran z uwzglêdnieniem przerw
    float screenW = 800.0f;
    float rozmiarBlokuX = (screenW - (ILOSC_KOLUMN + 1) * PRZERWA) / ILOSC_KOLUMN;
    sf::Vector2f rozmiarBloku(rozmiarBlokuX, ROZMIAR_BLOKU_Y);

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
            float posX = PRZERWA + x * (rozmiarBlokuX + PRZERWA);
            float posY = OFFSET_TOP + y * (ROZMIAR_BLOKU_Y + PRZERWA);
            sf::Vector2f pozycja(posX, posY);

            // Im wy¿szy rz¹d, tym wiêcej punktów ¿ycia (HP)
            int hp = (y < 3) ? 3 : (y < 5) ? 2 : 1;

            m_bloki.emplace_back(pozycja, rozmiarBloku, hp);
        }
    }
}

// Przywraca grê do stanu pocz¹tkowego (dla opcji "Nowa Gra")
void Game::reset() {
    m_score = 0;
    m_totalTime = 0.0f;
    m_gameOver = false;

    // Reset pozycji pi³ki i paletki na œrodek
    m_pilka = Ball(800.0f / 2.0f, 600.0f / 2.0f);
    m_paletka = Paddle(800.0f / 2.0f, 600.0f - 40.0f);

    initLevel();
}

// G³ówna logika gry: fizyka, kolizje, aktualizacja stanu
void Game::update(sf::Time dtTime, float screenWidth) {
    if (m_gameOver) return;

    float dt = dtTime.asSeconds();
    m_totalTime += dt;

    // Poruszanie obiektami
    m_paletka.update(screenWidth, dt);
    m_pilka.update(dt);

    // Aktualizacja tekstów UI
    m_timerText.setString("Time: " + std::to_string(static_cast<int>(m_totalTime)));
    m_scoreText.setString("Score: " + std::to_string(m_score));

    // --- LOGIKA KOLIZJI ---
    sf::Vector2f posPilki = m_pilka.getPosition();
    float r = m_pilka.getRadius();

    // 1. Kolizje ze œcianami
    if (posPilki.x - r < 0 && m_pilka.getVelocityX() < 0) m_pilka.reverseVelocityX();
    if (posPilki.x + r > screenWidth && m_pilka.getVelocityX() > 0) m_pilka.reverseVelocityX();
    if (posPilki.y - r < 0 && m_pilka.getVelocityY() < 0) m_pilka.reverseVelocityY();

    // 2. Sprawdzenie przegranej (pi³ka dotknê³a do³u)
    if (posPilki.y + r > 600.0f) {
        m_gameOver = true;
    }

    // 3. Kolizja z paletk¹
    if (m_pilka.getGlobalBounds().intersects(m_paletka.getGlobalBounds())) {
        // Odbicie pi³ki w górê
        m_pilka.setVelocityY(-std::abs(m_pilka.getVelocityY()));

        // Zmiana k¹ta odbicia w zale¿noœci od miejsca uderzenia w paletkê
        float impactFactor = (m_pilka.getPosition().x - m_paletka.getPosition().x) / (m_paletka.getWidth() / 2.0f);
        m_pilka.setVelocityX(impactFactor * 300.0f);
    }

    // 4. Kolizja z blokami
    for (auto& blok : m_bloki) {
        if (!blok.isDestroyed() && m_pilka.getGlobalBounds().intersects(blok.getGlobalBounds())) {
            blok.trafienie(); // Zmniejszenie HP bloku
            m_pilka.reverseVelocityY(); // Odbicie pi³ki

            m_score++; // Dodanie punktu
            break; // Przerywamy pêtlê, ¿eby nie uderzyæ w dwa bloki w jednej klatce
        }
    }
}

// Rysowanie wszystkich elementów gry na ekranie
void Game::render(sf::RenderTarget& target) {
    m_paletka.draw(target);
    m_pilka.draw(target);

    for (const auto& blok : m_bloki) {
        blok.draw(target);
    }

    target.draw(m_scoreText);
    target.draw(m_timerText);

    if (m_gameOver) {
        target.draw(m_gameOverText);
    }
}

// Tworzy stan gry i zapisuje go do pliku
void Game::saveGame()
{
    GameState state;
    // Przechwycenie aktualnych danych
    state.capture(m_paletka, m_pilka, m_bloki);

    if (state.saveToFile("zapis.txt"))
    {
        std::cout << "Gra zostala pomyslnie zapisana do pliku zapis.txt!" << std::endl;
    }
    else
    {
        std::cout << "Blad zapisu gry!" << std::endl;
    }
}

// Wczytuje stan gry z pliku i aplikuje go
bool Game::loadGame() {
    GameState state;
    if (state.loadFromFile("zapis.txt")) {
        // Jeœli plik istnieje i zosta³ wczytany, nak³adamy dane na grê
        state.apply(m_paletka, m_pilka, m_bloki);
        m_gameOver = false; // Upewniamy siê, ¿e gra nie jest w stanie Game Over
        return true;
    }
    return false;
}