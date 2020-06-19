#include<stdio.h>
#include<graphics.h>

#define SPACE 10
#define HEIGHT 80
#define WIDTH 80

void draw(int map[HEIGHT][WIDTH]);
void drawRect(int x, int y, int flag);
void getAndSet(int map[HEIGHT][WIDTH]);

int main()
{
	initgraph(HEIGHT*SPACE, WIDTH*SPACE);
	int map[HEIGHT][WIDTH] = { 0 };
	char tips[3][256] = {
		"1","2","3"
	};
	settextcolor(RED);
	outtextxy(350, 400, "123");
	for (int i = 0; i < 3; i++)
	{
		cleardevice();
		outtextxy(300, 300, tips[i]);
		Sleep(1000);

	}
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)getAndSet, map, NULL, NULL);
	while (1) {
		draw(map);
		Sleep(10);
	}
}

void draw(int map[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			drawRect(i, j, map[i][j]);
		}
	}
}

void drawRect(int x, int y, int flag)
{
	setcolor(0x686868);
	if (flag) {
		setfillcolor(WHITE);
	}
	else {
		setfillcolor(BLACK);
	}
	fillrectangle(y * SPACE, x * SPACE, y * SPACE + SPACE, x * SPACE + SPACE);
}

void getAndSet(int map[HEIGHT][WIDTH]) {
	int x, y;
	MOUSEMSG msg;
	while (1) {
		msg=GetMouseMsg();
		x = msg.x / SPACE;
		y = msg.y / SPACE;
		if (msg.mkLButton) {
			if (y == HEIGHT - 1 && x == WIDTH - 1)
				return;
			map[y][x] = 1;
		}
		else {
			map[y][x] = 0;
		}
	}
}