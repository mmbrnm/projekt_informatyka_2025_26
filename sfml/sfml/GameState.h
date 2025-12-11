#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Zapowiedzi klas (Forward Declarations)
// Pozwalaj¹ na u¿ycie nazw typów w argumentach funkcji bez do³¹czania ca³ych plików .h
class Paddle;
class Ball;
class Stone;

// Struktura pomocnicza do przechowywania surowych danych o pojedynczym klocku
struct BlockData
{
	float x, y;
	int hp;
};

// Klasa odpowiedzialna za przechwytywanie, zapisywanie i odtwarzanie stanu gry
class GameState
{
private:
	sf::Vector2f paddlePosition;   // Zapisana pozycja paletki
	sf::Vector2f ballPosition;     // Zapisana pozycja pi³ki
	sf::Vector2f ballVelocity;     // Zapisany wektor prêdkoœci pi³ki
	std::vector<BlockData> blocks; // Lista danych o aktywnych klockach

public:
	// Pobiera aktualny stan z obiektów gry
	void capture(const Paddle& paddle, const Ball& ball, const std::vector<Stone>& stones);

	// Serializuje (zapisuje) stan do pliku tekstowego
	bool saveToFile(const std::string& filename);

	// Deserializuje (wczytuje) stan z pliku tekstowego
	bool loadFromFile(const std::string& filename);

	// Przywraca wczytany stan na obiekty gry
	void apply(Paddle& paddle, Ball& ball, std::vector<Stone>& stones);
};