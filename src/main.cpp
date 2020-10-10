#include <unistd.h>
#include <iostream>

#define WIDTH 10
#define HEIGHT 10

struct Cell
{
    bool bAlive = false;
};

int module(int a, int b)
{
    return (a % b + b) % b; // is it right solution? did't i wrong?
}

Cell **createField(int h, int w)
{

    Cell **cells = new Cell *[h];

    for (int i = 0; i < h; i++)
    {
        cells[i] = new Cell[w];
    }

    return cells;
}

void drawField(Cell **cells)
{

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (cells[i][j].bAlive)
            {
                std::cout << "#";
            }
            else
            {
                std::cout << " ";
            }
        }
        printf("\n");
    }
}

void initField(Cell **cells)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            cells[i][j].bAlive = false;
        }
    }
}

int calc_nbors(Cell **cells, int y, int x)
{
    int result = 0;
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (dx != 0 || dy != 0)
            {
                if (cells[module(y + dy, HEIGHT)][module(x + dx, WIDTH)].bAlive)
                {
                    result += 1;
                }
            }
        }
    }
    return result;
}

void next_gen(Cell **prev, Cell **next)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            auto nbors = calc_nbors(prev, y, x);

            if (prev[y][x].bAlive)
            {
                next[y][x].bAlive = nbors == 3 || nbors == 2 ? true : false;
            }
            else
            {
                next[y][x].bAlive = nbors == 3 ? true : false;
            }
        }
    }
}

void putGlider(Cell **cells, int y, int x)
{
    cells[y + 0][x + 1].bAlive = true;
    cells[y + 1][x + 2].bAlive = true;
    cells[y + 2][x + 0].bAlive = true;
    cells[y + 2][x + 1].bAlive = true;
    cells[y + 2][x + 2].bAlive = true;
}

int main(int argc, char const *argv[])
{

    Cell **cells[2];
    cells[0] = createField(HEIGHT, WIDTH);
    cells[1] = createField(HEIGHT, WIDTH);

    int fb = 0;

    initField(cells[fb]);
    putGlider(cells[fb], 0, 0);
    putGlider(cells[fb], 4, 4);
    drawField(cells[fb]);

    while (true)
    {
        int bb = 1 - fb;
        next_gen(cells[fb], cells[bb]);
        fb = bb;

        std::cout << "\x1B[2J\x1B[H" << std::endl;

        drawField(cells[fb]);
        usleep(200000);
    }

    return 0;
}
