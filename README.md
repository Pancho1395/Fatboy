# *Fatboy: Juego estilo Bomberman*

## *Descripción*
Fatboy es un juego de estrategia inspirado en el clásico Bomberman. Diseñado para dos jugadores, el objetivo es sobrevivir utilizando bombas para destruir bloques, esquivar explosiones y derrotar al oponente. Este proyecto combina gráficos dinámicos, sonidos inmersivos y controles intuitivos.

---

## *Características principales*
1. *Modo para dos jugadores:*
   - *Jugador 1:* Controlado con teclas de flecha y la barra espaciadora.
   - *Jugador 2:* Controlado con las teclas *W, A, S, D* y la tecla *Q*.

2. *Dinámica del juego:*
   - Explosiones animadas con imágenes dinámicas.
   - Bloques destructibles para abrir caminos y generar ventaja táctica.

3. *Sistema de vidas:*
   - Cada jugador inicia con 3 vidas.
   - Las vidas se reducen al ser alcanzado por una explosión.
   - El juego termina cuando un jugador pierde todas sus vidas.

4. *Música y efectos:*
   - Utiliza la biblioteca *SFML* para gráficos, sonido y manejo de eventos.

---

## *Controles*

### *Jugador 1*
- *Movimiento:* Flechas del teclado.
- *Colocar bomba:* Barra espaciadora.

### *Jugador 2*
- *Movimiento:* Teclas *W, A, S, D*.
- *Colocar bomba:* Tecla *Q*.

---

## *Instalación*

### *Requisitos previos*
- *Dependencias:*
  - Biblioteca SFML (Graphics, Audio, Window, System).
  - Compilador C++ compatible (como *g++*).
  
### *Pasos de instalación*
1. Clona o descarga este repositorio.
2. Navega al directorio principal del proyecto.
3. Compila el proyecto ejecutando:
   bash
   make all
   
4. Inicia el juego con:
   bash
   make run
   

---

## *Estructura del proyecto*
- src/: Archivos fuente del juego.
- include/: Archivos de encabezado.
- assets/images/: Recursos gráficos (sprites y texturas).
- assets/music/: Música y efectos de sonido.
- bin/: Binarios generados durante la compilación.
- Makefile: Automatiza el proceso de compilación y ejecución.

---

## *Cómo jugar*
1. *Inicio:* 
   Cada jugador comienza en una esquina del mapa.
2. *Acciones:* 
   - Usa los controles para moverte y colocar bombas.
   - Destruye bloques para ganar ventaja táctica.
   - Evita las explosiones de las bombas propias y del oponente.
3. *Objetivo:* 
   Haz que tu oponente pierda todas sus vidas antes que tú.

---

## *Créditos*
Desarrollado como parte de un proyecto de ingeniería, inspirado en el clásico juego Bomberman. 

---

## *Licencia*
Uso académico y personal. Los recursos externos, como fuentes y texturas, pertenecen a sus respectivos propietarios.