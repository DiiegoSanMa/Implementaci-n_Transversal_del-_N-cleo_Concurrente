#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <iomanip>

// =========================================
// Clase Player: Representa a cada jugador
// =========================================
class Player {
public:
    int id;
    std::string name;
    int score = 0;

    void run(std::mutex& mtx) {
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            updateGameDisplay(mtx, i);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }

private:
    void updateGameDisplay(std::mutex& mtx, int round) {
        std::lock_guard<std::mutex> lock(mtx);
        score += 10;

        // Limpiar pantalla y mostrar encabezado
        std::cout << "\033[2J\033[H";
        std::cout << "========================================\n";
        std::cout << "         SIMULACIÓN DEL JUEGO          \n";
        std::cout << "========================================\n";
        std::cout << "Jugadores conectados: 3\n";
        std::cout << "----------------------------------------\n\n";

        // Mostrar ventanas de jugadores
        displayPlayerWindow(1, name, round, score);
        displayPlayerWindow(2, "Bob", round, 10 * (round + 1));
        displayPlayerWindow(3, "Carlos", round, 10 * (round + 1));

        std::cout << "\n----------------------------------------\n";
    }

    void displayPlayerWindow(int position, const std::string& playerName, int round, int playerScore) {
        std::cout << "+-------------------+\n";
        std::cout << "| " << std::setw(7) << playerName 
                 << " | Ronda " << (round + 1) 
                 << " | Puntos: " << playerScore << " |\n";
        std::cout << "+-------------------+\n";
    }
};

// =========================================
// Clase GameServer: Gestiona la partida
// =========================================
class GameServer {
private:
    std::vector<Player> players;
    std::vector<std::thread> threads;
    std::mutex gameMutex;

public:
    void addPlayer(const Player& p) {
        players.push_back(p);
    }

    void runGame() {
        startGame();
        runGameLoop();
        showFinalResults();
    }

private:
    void startGame() {
        std::cout << "========================================\n";
        std::cout << "         INICIANDO SIMULACIÓN          \n";
        std::cout << "========================================\n";
        std::cout << "Jugadores conectados: " << players.size() << "\n";
        std::cout << "----------------------------------------\n\n";
    }

    void runGameLoop() {
        for (auto& p : players) {
            threads.emplace_back(&Player::run, &p, std::ref(gameMutex));
        }

        for (auto& t : threads) {
            t.join();
        }
    }

    void showFinalResults() {
        std::cout << "\n========================================\n";
        std::cout << "            RESULTADOS FINALES          \n";
        std::cout << "========================================\n";
        std::cout << "Puntajes:\n";
        for (const auto& p : players) {
            std::cout << "  " << p.name << ": " << p.score << " puntos\n";
        }
        std::cout << "----------------------------------------\n";
        std::cout << "Total de jugadores: " << players.size() << "\n";
        std::cout << "========================================\n";
    }
};

// =========================================
// Función Principal
// =========================================
int main() {
    GameServer server;

    // Registrar jugadores
    server.addPlayer(Player{1, "Alice"});
    server.addPlayer(Player{2, "Bob"});
    server.addPlayer(Player{3, "Carlos"});

    // Iniciar juego
    server.runGame();

    return 0;
}