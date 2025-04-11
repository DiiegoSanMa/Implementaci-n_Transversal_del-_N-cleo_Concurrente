# Simulación de Juego Multijugador en C++

Este proyecto es una simulación de un juego multijugador utilizando **programación concurrente en C++** con **hilos (`std::thread`)** y **mutexes (`std::mutex`)** para asegurar el acceso seguro a los recursos compartidos.

## 🧠 Descripción

El programa simula a tres jugadores que compiten durante varias rondas. Cada jugador incrementa su puntuación y actualiza una interfaz simulada en consola que muestra su progreso. La ejecución de los jugadores ocurre en paralelo, y se sincroniza el acceso a la consola para evitar condiciones de carrera.

## 🚀 Características

- Uso de múltiples **hilos** para representar a cada jugador.
- Control de concurrencia mediante **mutexes**.
- Actualización visual del juego en consola (limpieza de pantalla incluida).
- Simulación de rondas y puntos por jugador.
- Resultados finales mostrados al finalizar la partida.

## 📦 Estructura del Código

- `Player`: Clase que representa a un jugador. Contiene lógica para simular rondas y actualizar la pantalla.
- `GameServer`: Clase que administra a los jugadores, controla la simulación y muestra los resultados.
- `main()`: Punto de entrada donde se registran los jugadores y se lanza la simulación.

## 🛠️ Compilación y Ejecución

### Requisitos:
- Compilador C++11 o superior (como `g++` o `clang++`)

### Compilación:

```bash
g++ -std=c++11 -pthread juego.cpp -o juego
