void output();
void TextColor(int x);
void gotoxy(int x, int y);
void arrowHere(int realPosition, int arrowPosition);
void khungngoai();
void khungtrong();
void khungketqua();
void khunghuongdan();
void khungtieptuyen();
void khungexit();
void khung();

// ham doi mau chu
void TextColor(int x) 
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

// ham di chuyen vi tri con tro
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// ham lam noi bat chuc nang dang chon
void arrowHere(int realPosition, int arrowPosition)
{
    if (realPosition == arrowPosition)	
    {
        TextColor(207); printf("%c  ", 175);
    }
    else {
        TextColor(113);  printf("    ");
    }
}

// ham in ra thong tin
void khungthongtin()
{		
	TextColor(7);	
    for (int i = 82; i <= 118; i++)
    {
        gotoxy(i, 0); printf("%c", 205);
        gotoxy(i, 10); printf("%c", 205);
    }
    for (int i = 0; i <= 10; i++)
    {
        gotoxy(82, i); printf("%c", 186);
        gotoxy(118, i); printf("%c", 186);
    }
    gotoxy(82,0); printf("%c", 201);
    gotoxy(118,0); printf("%c", 187);
    gotoxy(82,10); printf("%c", 200);
    gotoxy(118,10); printf("%c", 188);
    gotoxy(95,0); TextColor(111); printf(" Thong tin ");
    gotoxy(102,29); TextColor(8); printf("Made by Vu Huu Sy");
    TextColor(14);
    gotoxy(85,2); printf("Sinh vien: Vu Huu Sy - MI2-01 K66");
    gotoxy(85,3); printf("MSSV: 20216958");
    gotoxy(85,4); printf("Vien Toan ung dung va Tin hoc");
    gotoxy(85,5); printf("Dai hoc Bach Khoa Ha Noi");
    gotoxy(85,7); printf("BTL mon Ky Thuat Lap Trinh");
    gotoxy(85,8); printf("GVHD: TS. Nguyen Thi Thanh Huyen");
}
	
// ham ve giao dien khung ngoai 
void khungngoai()
{
	TextColor(113);
	for(int i=1; i<80;i++){
		for(int j=1;j<29;j++){
			gotoxy(i,j); printf(" ");
		}
	}
    TextColor(11);
    for (int i = 0; i <= 80; i++)
    {
        gotoxy(i, 0); printf("%c", 205);
        gotoxy(i, 29); printf("%c", 205);
    }
    for (int i = 0; i <= 14; i++)	
    {
        gotoxy(0, 14 - i); printf("%c", 186);	
        gotoxy(0, 14 + i); printf("%c", 186);
        gotoxy(80, 14 - i); printf("%c", 186);
        gotoxy(80, 14 + i); printf("%c", 186);
    }
    gotoxy(0, 0); printf("%c", 201);
    gotoxy(80, 0); printf("%c", 187);
    gotoxy(0, 29); printf("%c", 200);
    gotoxy(80, 29); printf("%c", 188);
    gotoxy(34, 0); TextColor(160); printf(" BAI TAP LON ");
    gotoxy(2, 2); TextColor(31); printf("%c CHU DE 4: GIAI GAN DUNG PHUONG TRINH F(X) = 0 BANG PHUONG PHAP TIEP TUYEN %c", 175, 174);
}

// ham ve giao dien ben trong khung 
void khungtrong()	
{	
    TextColor(116);
    for (int i = 0; i < 47; i++)
    {
        gotoxy(16 + i, 7); printf("%c", 205);
        gotoxy(16 + i, 19); printf("%c", 205);
    }
	TextColor(31);
    gotoxy(36,7); printf(" MENU ");
    TextColor(113);
    gotoxy(18,21); printf("$$$   $$    $$$$$$$$$   $$$       $$$$$$$$$\n"); Sleep(40);
    gotoxy(18,22); printf("$$$ $$      $$$$$$$$$   $$$       $$$$$$$$$\n"); Sleep(40); TextColor(114);
    gotoxy(18,23); printf("$$$$           $$$      $$$          $$$   \n"); Sleep(40);
    gotoxy(18,24); printf("$$$ $$         $$$      $$$          $$$   \n"); Sleep(40); TextColor(116);
    gotoxy(18,25); printf("$$$   $$       $$$      $$$$$$$      $$$   \n"); Sleep(40);
    gotoxy(18,26); printf("$$$    $$      $$$      $$$$$$$      $$$   \n");
}

// ham giao dien ket qua
void khungketqua()
{	
	TextColor(113);
	for(int i=83; i<118;i++){
		for(int j=1;j<29;j++){
			gotoxy(i,j);
			printf(" ");
		}
	}
	TextColor(12);	
    for (int i = 82; i <= 118; i++)
    {
        gotoxy(i, 0); printf("%c", 205);
        gotoxy(i, 29); printf("%c", 205);
    }
    for (int i = 0; i <= 29; i++)
    {
        gotoxy(82, i); printf("%c", 186);
        gotoxy(118, i); printf("%c", 186);
    }
    gotoxy(82, 0); printf("%c", 201);
    gotoxy(118, 0); printf("%c", 187);
    gotoxy(82, 29); printf("%c", 200);
    gotoxy(118, 29); printf("%c", 188);
    gotoxy(96, 0); TextColor(160); printf(" Ket qua ");
    gotoxy(100, 28); TextColor(120); printf("Made by Vu Huu Sy");
}

// ham in ra huong dan
void khunghuongdan(){
	TextColor(113);
	for(int i=84; i<118;i++){
		for(int j=1;j<29;j++){
			gotoxy(i,j);
			printf(" ");
		}
	}
	TextColor(10);	
    for (int i = 82; i <= 118; i++)
    {
        gotoxy(i, 0); printf("%c", 205);
        gotoxy(i, 29); printf("%c", 205);
    }
    for (int i = 0; i <= 29; i++)
    {
        gotoxy(82, i); printf("%c", 186);
        gotoxy(118, i); printf("%c", 186);
    }
    gotoxy(82, 0); printf("%c", 201);
    gotoxy(118, 0); printf("%c", 187);
    gotoxy(82, 29); printf("%c", 200);
    gotoxy(118, 29); printf("%c", 188);
    gotoxy(95, 0); TextColor(160); printf(" Huong dan ");
    gotoxy(100, 28); TextColor(120); printf("Made by Vu Huu Sy");
    TextColor(116);
    gotoxy(84,2); printf("%c MENU duoc dieu khien bang cac", 175);
    gotoxy(84,3); printf("phim chuc nang tren ban phim!");
    gotoxy(84,5); printf("%c Chi tiet:", 175);
    TextColor(117);
    gotoxy(84,6); printf("- Phan ban phim chu:");
    TextColor(113);
    gotoxy(84,7); printf("+ An \"s\" hoac \"S\" de xuong");
    gotoxy(84,8); printf("+ An \"w\" hoac \"W\" de len");
    TextColor(117);
    gotoxy(84,9); printf("- Phan ban phim so:");
    TextColor(113);
    gotoxy(84,10); printf("+ An \"2\" de xuong");
    gotoxy(84,11); printf("+ An \"8\" de len");
    TextColor(117);
    gotoxy(84,13); printf("%c Cac phim mui ten hoat dong", 175);
    gotoxy(84,14); printf("tuong tu.");
    TextColor(116);
    gotoxy(84,16); printf("%c Chu y:", 175);
    TextColor(113);
    gotoxy(84,17); printf("-Khi an xuong o chuc nang cuoi thi");
    gotoxy(84,18); printf("se tro lai chuc nang dau tien.");
    gotoxy(84,19); printf("-An phim Tab se xuong 2 lan.");
    gotoxy(84,21); printf("%c An Enter de chuong trinh thuc", 175);
    gotoxy(84,22); printf("hien chuc nang dang chon.");
    gotoxy(84,24); printf("%c Khi thuc hien xong 1 chuc nang,", 175);
    gotoxy(84,25); printf("an Enter de quay tro lai MENU.");
    gotoxy(84,27); printf("%c An ESC de ket thuc chuong trinh.", 175);
}

// ham gioi thieu ve phuong phap tiep tuyen
void khungtieptuyen(){
	TextColor(113);
	for(int i=84; i<118;i++){
		for(int j=1;j<29;j++){
			gotoxy(i,j);
			printf(" ");
		}
	}
	
	TextColor(10);	
    for (int i = 82; i <= 118; i++)
    {
        gotoxy(i, 0); printf("%c", 205);
        gotoxy(i, 29); printf("%c", 205);
    }
    for (int i = 0; i <= 29; i++)
    {
        gotoxy(82, i); printf("%c", 186);
        gotoxy(118, i); printf("%c", 186);
    }
    gotoxy(82, 0); printf("%c", 201);
    gotoxy(118, 0); printf("%c", 187);
    gotoxy(82, 29); printf("%c", 200);
    gotoxy(118, 29); printf("%c", 188);
    gotoxy(89, 0); TextColor(160); printf(" Phuong phap tiep tuyen ");
    gotoxy(100, 28); TextColor(120); printf("Made by Vu Huu Sy");
    TextColor(113);
    gotoxy(84,2); printf("%c Trong GIAI TICH SO, phuong phap", 175);
    gotoxy(84,3); printf("tiep tuyen (con duoc goi la phuong");
    gotoxy(84,4); printf("phap Newton Raphson), dat ten theo");
    gotoxy(84,5); printf("Isaac Newton va Joseph Raphson,");
    gotoxy(84,6); printf("la mot phuong phap tim nghiem xap");
    gotoxy(84,7); printf("xi gan dung cua mot ham so f(x) co");
    gotoxy(84,8); printf("tham so thuc.");
    gotoxy(84,10); printf("%c Dinh nghia: Diem x0 duoc goi la", 175);
    gotoxy(84,11); printf("diem Fourier cua f neu: ");
    gotoxy(84,12); printf("        f(x0).f\"(x0) > 0");
    gotoxy(84,14); printf("%c Cong thuc lap: ", 175);
    gotoxy(84,15); printf("    X(n+1) = Xn - f(Xn)/f'(Xn)");
    gotoxy(84,17); printf("%c Cong thuc sai so:", 175);
    gotoxy(84,18); printf("- Sai so muc tieu: ");
    gotoxy(84,19); printf("|Xn - X*| <= |f(Xn)| / m1");
    gotoxy(84,21); printf("- Sai so hai xap xi lien tiep:");
    gotoxy(84,22); printf("|Xn - X*|<=(M2/2m1)*(Xn-X(n-1))^2");
    gotoxy(84,24); printf("Trong do: ");
    gotoxy(84,25); printf("- m1 la min cua |f'(x)| tren (a,b)");
    gotoxy(84,26); printf("- M2 la max cua |f\"(x)| tren (a,b)");
    
}

// ham giao dien khi ket thuc chuong trinh
void khungexit(){
	int i = 0;
	TextColor(113);
	for(int i=0; i<120;i++){
		for(int j=0;j<30;j++){
			gotoxy(i,j); printf(" ", 178);
		}
	}
	
	for (int i = 40; i <= 80; i++)
    {
        gotoxy(i, 0); printf("%c", 205);
        gotoxy(i, 4); printf("%c", 205);
        Sleep(1);
    }
    for (int i = 0; i <= 4; i++)
    {
        gotoxy(40, i); printf("%c", 186);
        gotoxy(80, i); printf("%c", 186);
        Sleep(1);
    }
	gotoxy(40, 0); printf("%c", 201);
    gotoxy(80, 0); printf("%c", 187);
    gotoxy(40, 4); printf("%c", 200);
    gotoxy(80, 4); printf("%c", 188);
	
	TextColor(116);
	gotoxy(48,2); printf("KET THUC CHUONG TRINH !!!");
    getch();
} 

// ham giao dien chinh
void khung(){
    khungngoai();
    TextColor(113);
    gotoxy(2,4); output(); 
    khungketqua();
    khungtrong();
}

