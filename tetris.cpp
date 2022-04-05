#include <conio.h> //入出力に関する関数
#include<string.h> //文字列操作に関する関数
#include<stdio.h> //入出力に関する関数
#include<time.h> //時間に関する関数
#include<stdlib.h> //いろいろ便利なものがある関数

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22

char field[FIELD_HEIGHT][FIELD_WIDTH];
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH];

enum {
	I,
	O,
	S,
	Z,
	J,
	L,
	T,
	MINO_MAX

};
enum {
	ANGLE_,
	ANGLE_90,
	ANGLE_180,
	ANGLE_270,
	ANGLE_MAX
};

#define MINO_WIDHT 4
#define MINO_HEIGHT 4
char minoshapes[MINO_MAX][ANGLE_MAX][MINO_HEIGHT][MINO_WIDHT] = {
	//I
	{
		//0
		{
		 0,1,0,0,
		 0,1,0,0,
		 0,1,0,0,
		 0,1,0,0,
		},
		//90
		{
		0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,
		},
		//180
		{
		0,0,1,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,0,
		},
		//270
		{
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0,
		},
	},
	//O
	{
		//0
		{
		0,0,0,0,
		0,1,1,0,	
		0,1,1,0,
		0,0,0,0,
		},
		//90
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//180
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//270
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
},
//S
	{
		//0
		{
			0,0,0,0,
			0,1,1,0,
			1,1,0,0,
			0,0,0,0,
		},
		//90
		{
			0,1,0,0,
			0,1,1,0,
			0,0,1,0,
			0,0,0,0,
		},
		//180
		{
			0,0,0,0,
			0,1,1,0,
			1,1,0,0,
			0,0,0,0,
		},
		//270
		{
			0,0,0,0,
			0,1,0,0,
			0,1,1,0,
			0,0,1,0,
		},
	},
	//Z
	{
		//0
		{
			0,0,0,0,
			1,1,0,0,
			0,1,1,0,
			0,0,0,0,
		},
		//90
		{
			0,0,0,0,
			0,0,1,0,
			0,1,1,0,
			0,1,0,0,
		},
		//180
		{
			0,0,0,0,
			0,1,1,0,
			0,0,1,1,
			0,0,0,0,
		},
		//270
		{
			0,0,1,0,
			0,1,1,0,
			0,1,0,0,
			0,0,0,0,
		},
	},
	//J
	{
		//0
		{
			0,0,1,0,
			0,0,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//90
		{
			0,0,0,0,
			1,1,1,0,
			0,0,1,0,
			0,0,0,0,
		},
		//180
		{
			0,0,0,0,
			0,1,1,0,
			0,1,0,0,
			0,1,0,0,
		},
		//270
		{
			0,0,0,0,
			0,1,0,0,
			0,1,1,1,
			0,0,0,0,
		},
	},
	//L
	{
		//0
		{
			0,1,0,0,
			0,1,0,0,
			0,1,1,0,
			0,0,0,0,
		},
		//90
		{
			0,0,0,0,
			0,0,1,0,
			1,1,1,0,
			0,0,0,0,
		},
		//180
		{
			0,0,0,0,
			0,1,1,0,
			0,0,1,0,
			0,0,1,0,
		},
		//270
		{
			0,0,0,0,
			0,1,1,1,
			0,1,0,0,
			0,0,0,0,
		},
	},
	//T
	{
		//0
		{
			0,0,0,0,
			1,1,1,0,
			0,1,0,0,
			0,0,0,0,
		},
		//90
		{
			0,0,0,0,
			0,1,0,0,
			0,1,1,0,
			0,1,0,0,
		},
		//180
		{
			0,0,0,0,
			0,0,1,0,
			0,1,1,1,
			0,0,0,0,
		},
		//270
		{
			0,0,1,0,
			0,1,1,0,
			0,0,1,0,
			0,0,0,0,
		},
	},

	

};

int minoType = 0, minoAngle = 0;
int minoX = 5, minoY = 0;
void display() {
	memcpy(displayBuffer, field, sizeof(field));


	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDHT; j++)
			displayBuffer[minoY + i][minoX + j] |= minoshapes[minoType][minoAngle][i][j];
	system("cls");

	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++)
			printf(displayBuffer[i][j] ? "■" : "　");
		printf("\n");
	}
}
bool isHit(int _minoX, int _minoY, int _minoType, int _minoAngle) {
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j<MINO_WIDHT; j++)
			if (minoshapes[_minoType][_minoAngle][i][j]
				&&
				field[_minoY + i][_minoX + j]
				)
			{
				return true;
			}
	return false;
}
void resetMino() {
	minoX = 5;
	minoY = 0;
	minoType =  rand() % MINO_MAX;
	minoAngle = rand() % ANGLE_MAX;
}
int main(){
	memset(field,0,sizeof(field));
	for (int i = 0; i < FIELD_HEIGHT; i++)
		field[i][0] = field[i][FIELD_WIDTH - 1] = 1;

	for (int i = 0; i < FIELD_WIDTH; i++)
		 field[FIELD_HEIGHT - 1][i] = 1;

	resetMino();
	time_t t = time(NULL);
	while (1) {
		if (_kbhit()) {
			switch (_getch()) {
			//case 'w':
			case 's': 
				if (!isHit(
					minoX , //int _minoX
					minoY+1, //int _minoY
					minoType, //int _minoType
					minoAngle)) //int _minoAngle
				minoY++;
				break;
			case 'a': 
				if (!isHit(
					minoX-1, //int _minoX
					minoY, //int _minoY
					minoType, //int _minoType
					minoAngle)) //int _minoAngle
					minoX--;
				    break;
			case 'd':
				if (!isHit(
					minoX + 1, //int _minoX
					minoY, //int _minoY
					minoType, //int _minoType
					minoAngle)) //int _minoAngle
				minoX++; 
				break;
			case 0x20: 
				if (!isHit(
					minoX , //int _minoX
					minoY, //int _minoY
					minoType, //int _minoType
					(minoAngle + 1) % ANGLE_MAX)) //int _minoAngle
				minoAngle = (minoAngle + 1) % ANGLE_MAX;//supace
				break;
			}
			display();
		}
		if (t != time(NULL)) {
			t = time(NULL);

			if (isHit(
				minoX, //int _minoX
				minoY + 1, //int _minoY
				minoType, //int _minoType
				minoAngle)) {//int _minoAngle
				for (int i = 0; i < MINO_HEIGHT; i++)
					for (int j = 0; j < MINO_WIDHT; j++)
						field[minoY + i][minoX + j] |= minoshapes[minoType][minoAngle][i][j];
				{
					for (int i = 0; i<FIELD_HEIGHT - 1; i++) {
						bool lineFill = true;
						for (int j = 1; j < FIELD_WIDTH - 1; j++) {
							if (!field[i][j])
								lineFill = false;
						}
						if (lineFill)
							//for (int j = 1; j < FIELD_WIDTH - 1; j++)
								//field[i][j] = 0;

							for (int j = i; 0 < j; j--)
								memcpy(&field[j], field[j - 1], FIELD_WIDTH);
					}
				}
				resetMino();
			}
			else
			minoY++;

			display();
			
		}
	}
	
	_getch();
}