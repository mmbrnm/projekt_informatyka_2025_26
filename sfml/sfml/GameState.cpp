#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Stone.h"
#include <fstream> 

// Pobiera aktualny stan obiektów gry i zapisuje go w wewnêtrznych zmiennych
void GameState::capture(const Paddle& paddle, const Ball& ball, const std::vector<Stone>& stones)
{
    // Pobranie pozycji paletki i pi³ki
    paddlePosition = paddle.getPosition();
    ballPosition = ball.getPosition();

    // Pobranie wektora prêdkoœci pi³ki
    ballVelocity = sf::Vector2f(ball.getVelocityX(), ball.getVelocityY());

    // Zapisanie stanu klocków
    blocks.clear();
    for (const auto& stone : stones)
    {
        // Zapisujemy tylko klocki, które nie zosta³y zniszczone
        if (!stone.isDestroyed())
        {
            BlockData data;
            data.x = stone.getPosition().x;
            data.y = stone.getPosition().y;
            data.hp = stone.getHP();

            blocks.push_back(data);
        }
    }
}

// Zapisuje zgromadzone dane do pliku tekstowego
bool GameState::saveToFile(const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    // Zapis danych paletki
    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";

    // Zapis danych pi³ki (pozycja + prêdkoœæ)
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    // Zapis liczby klocków
    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    // Pêtla zapisuj¹ca parametry ka¿dego klocka
    for (const auto& block : blocks)
    {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    return true;
}

// Odczytuje dane z pliku tekstowego i wype³nia struktury wewnêtrzne
bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string keyword;
    blocks.clear();

    // Pêtla parsuj¹ca plik na podstawie s³ów kluczowych
    while (file >> keyword) {
        if (keyword == "PADDLE") {
            file >> paddlePosition.x >> paddlePosition.y;
        }
        else if (keyword == "BALL") {
            file >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;
        }
        else if (keyword == "BLOCKS_COUNT") {
            int count;
            file >> count;
            // Wczytanie okreœlonej liczby klocków
            for (int i = 0; i < count; ++i) {
                BlockData data;
                file >> data.x >> data.y >> data.hp;
                blocks.push_back(data);
            }
        }
    }
    file.close();
    return true;
}

// Aplikuje wczytane dane do rzeczywistych obiektów gry
void GameState::apply(Paddle& paddle, Ball& ball, std::vector<Stone>& stones) {
    // Aktualizacja paletki
    paddle.setPosition(paddlePosition.x, paddlePosition.y);

    // Aktualizacja pi³ki
    ball.setPosition(ballPosition.x, ballPosition.y);
    ball.setVelocity(ballVelocity.x, ballVelocity.y);

    // Odtworzenie klocków na planszy
    stones.clear();

    // Obliczenie rozmiaru bloku (zgodne z logik¹ generowania poziomu)
    float sizeX = (800.0f - (7 + 1) * 2.0f) / 7;
    sf::Vector2f blockSize(sizeX, 25.0f);

    for (const auto& data : blocks) {
        stones.emplace_back(sf::Vector2f(data.x, data.y), blockSize, data.hp);
    }
}