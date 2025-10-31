# include <stdio.h>
#include "raylib.h"
#include <time.h>

const bool SPITAK = true;
const bool SEV = false;

#define WIDTH 90
#define HEIGHT 90

const int CELL_WIDTH = 9;
const int CELL_HEIGHT = 9;

const int SPACING_X = 2;
const int SPACING_Y = 2;

#define SCREEN_WIDTH (CELL_WIDTH + SPACING_X) * WIDTH
#define SCREEN_HEIGHT  (CELL_HEIGHT + SPACING_Y) * HEIGHT



typedef struct{
	int x, y;
	int dir;
} Ant;



typedef struct {
	bool grid[WIDTH][HEIGHT];
} LangtonGrid;



LangtonGrid init_langton_grid() {

	LangtonGrid lgrid;

	int width = WIDTH / 2;
	int height = HEIGHT / 2;

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			lgrid.grid[i][j] = SEV;
		}
	}

	return lgrid;
}



Ant init_ant() {
	
	Ant ant;

	ant.dir = 0;
	ant.x = WIDTH / 2;
	ant.y = HEIGHT / 2;

	return ant;
}



void draw_langton_grid(LangtonGrid* lgrid, int start_x, int start_y) {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (lgrid->grid[i][j] == SEV) {
				DrawRectangle(start_x + (CELL_WIDTH + SPACING_X) * i, start_y + (CELL_HEIGHT + SPACING_Y) * j, CELL_WIDTH, CELL_HEIGHT, BLACK);
			}
			else {
				DrawRectangle(start_x + (CELL_WIDTH + SPACING_X) * i, start_y + (CELL_HEIGHT + SPACING_Y) * j, CELL_WIDTH, CELL_HEIGHT, RAYWHITE);
			}
		}
	}
}


// 0 = up, 1 = left, 2 = down, 3 = right
void turn_left(Ant* ant) {	
	if (ant->dir == 0) {
		ant->dir = 1;
	}
	else if (ant->dir == 1) {
		ant->dir = 2;
	}
	else if (ant->dir == 2) {
		ant->dir = 3;
	}
	else if (ant->dir == 3) {
		ant->dir = 0;
	}

}



void turn_right(Ant* ant) {
	if (ant->dir == 0) {
		ant->dir = 3;
	}
	else if (ant->dir == 1) {
		ant->dir = 0;
	}
	else if (ant->dir == 2) {
		ant->dir = 1;
	}
	else if (ant->dir == 3) {
		ant->dir = 2;
	}
}



void move_forward(Ant* ant) {
	if (ant->dir == 0) {
		if (ant->y == 0) {
			ant->y = HEIGHT - 1;
		}
		else {
			ant->y -= 1;
		}
	}
	else if (ant->dir == 1) {
		if (ant->x == 0) {
			ant->x = WIDTH - 1;
		}
		else {
			ant->x -= 1;
		}
	}
	else if (ant->dir == 2) {
		if (ant->y == HEIGHT - 1) {
			ant->y = 0;
		}
		else {
			ant->y += 1;
		}
	}
	else if (ant->dir == 3) {
		if (ant->x == WIDTH - 1) {
			ant->x = 0;
		}
		else {
			ant->x += 1;
		}
	}
}



void update_langton_grid(LangtonGrid* lgrid, Ant* ant) {
	bool current_cell = lgrid->grid[ant->x][ant->y];
	if (current_cell == SPITAK) {
		turn_right(ant);
	}
	else {
		turn_left(ant);
	}
	lgrid->grid[ant->x][ant->y] = !current_cell;
	move_forward(ant);

}



int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "s");
	SetRandomSeed(time(NULL));

	LangtonGrid lgrid = init_langton_grid();
	Ant ant = init_ant();

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		int start_x = 0;
		int start_y = 0;

		update_langton_grid(&lgrid, &ant);
		draw_langton_grid(&lgrid, start_x, start_y);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
