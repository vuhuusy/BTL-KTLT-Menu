#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>


void TextColor(int x) 	// doi mau chu
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

int main(){
	
	for(int i=0; i<400;i++){
		TextColor(i);
		printf("This color %d\n", i);
		Sleep(50);
	}
	getch();
}
