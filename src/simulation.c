#include "screen.h"

#include "simulation.h"

#define _CELLS_X 100
#define _CELLS_Y 100

// Globals FTW

int viewport_x = 0, viewport_y = 0;
int screen_x = 1, screen_width = 38, screen_y = 1, screen_height = 10;

unsigned int generation;
char cells[_CELLS_X][_CELLS_Y];
char pastg[_CELLS_X][_CELLS_Y];
char debug[_CELLS_X][_CELLS_Y];
char simulation_live_cells_around(int x, int y);

void simulation_init()
{
    generation = 0;
    for (int x = 0; x < _CELLS_X; x++) {
        for (int y = 0; y < _CELLS_Y; y++) {
            cells[x][y] = 0;
        }
    }

    screen_write_word(0, 40, generation, DarkGrey, White);
}

void simulation_init_stilllife_block()
{
    simulation_init();

    cells[3][3] = 1;
    cells[3][4] = 1;
    cells[4][3] = 1;
    cells[4][4] = 1;
}

void simulation_init_oscillators_blinker()
{
    simulation_init();

    // 000
    // XXX
    // 000

    cells[3][4] = 1;
    cells[4][4] = 1;
    cells[5][4] = 1;

}
void simulation_init_spaceship_glider()
{
    simulation_init();

    // 0X0
    // 00X
    // XXX

    cells[4][2] = 1;
    cells[5][3] = 1;

    cells[3][4] = 1;
    cells[4][4] = 1;
    cells[5][4] = 1;

    debug[5][4] = (char)1;
}

void simulation_print()
{
    screen_write_word(0, 40, generation, DarkGrey, White);

    

    // draw
    for (int x = 0; x < screen_width; x++) {
        for (int y = 0; y < screen_height; y++) {
            screen_cursor_to(screen_y + y, screen_x + x);
            screen_write_char(screen_y + y, screen_x + x, cells[viewport_x + x][viewport_y + y] ? '+' : ' ', LightBlue, LightGrey);
        }
    }
}

void simulation_debug()
{
    int screen_x = 41, screen_width = 38, screen_y = 1, screen_height = 10;
    int viewport_x = 0, viewport_y = 0;

    // draw
    for (int x = 0; x < screen_width; x++) {
        for (int y = 0; y < screen_height; y++) {
            screen_cursor_to(screen_y + y, screen_x + x);
            screen_write_char(screen_y + y, screen_x + x, 48 + debug[viewport_x + x][viewport_y + y], pastg[viewport_x + x][viewport_y + y] ? Red : LightBlue, LightBrown);
        }
    }
}

void simulation_setup_viewport(int x, int y, int width, int heigth)
{
    viewport_x = 0;
    viewport_y = 0;
    screen_x = x;
    screen_width = width;
    screen_y = y; 
    screen_height = heigth;
}

void simulation_move_viewport(int x, int y)
{
    // change the starting point in the array 
    viewport_x += x;
    viewport_y += y;

    if (viewport_x < 0) {
        viewport_x = 0;
    }
    if (viewport_x >= _CELLS_X - screen_width) {
        viewport_x = (_CELLS_X - screen_width) - 1;
    }

    if (viewport_y < 0) {
        viewport_y = 0;
    }
    if (viewport_y >= _CELLS_Y - screen_height) {
        viewport_y = (_CELLS_Y - screen_height) - 1;
    }
}

void simulation_tick()
{
    // copy current world state to temp array
    for (int x = 0; x < _CELLS_X; x++) {
        for (int y = 0; y < _CELLS_Y; y++) {
            pastg[x][y] = cells[x][y];
        }
    }

    // process rules
    for (int x = 0; x < _CELLS_X; x++) {
        for (int y = 0; y < _CELLS_Y; y++) {
            char value = pastg[x][y];
            char liveCellsAroundCount = simulation_live_cells_around(x, y);

            // rule 1: Any live cell with fewer than two live neighbours dies, as if caused by under-population.
            // rule 2: Any live cell with two or three live neighbours lives on to the next generation.
            // rule 3: Any live cell with more than three live neighbours dies, as if by overcrowding.
            // rule 4: Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if (liveCellsAroundCount < 2) {
                value = 0;
            } else if (liveCellsAroundCount == 3) {
                value = 1;
            } else if (liveCellsAroundCount > 3) {
                value = 0;
            }
            
            cells[x][y] = value;
        }
    }

    generation++;
}

char simulation_live_cells_around(int x, int y) 
{
    int xs = x - 1, xe = x + 1;
    int ys = y - 1, ye = y + 1;
    if (xs < 0) xs = 0;
    if (xe >= _CELLS_X) xe = _CELLS_X - 1;
    if (ys < 0) ys = 0;
    if (ye >= _CELLS_Y) ye = _CELLS_Y - 1;

    // X X X
    // X 0 X
    // X X X
    char count = 0;
    for (int xd = xs; xd <= xe; xd++) {
        for (int yd = ys; yd <= ye; yd++) {
            if (xd == x && yd == y) 
                continue;

            if (pastg[xd][yd] == 1) {
                count++;
            }
        }
    }

    return debug[x][y] = count;
}
