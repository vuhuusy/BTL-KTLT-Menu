#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <stdbool.h>
#include "giao_dien.h" 	

// cac hang so
#define MIN 1
#define MAX 8
#define N 100
#define max_loop 1000 

// cac bien toan cuc
const char* option[] =
{	
    "Tim cac KPL nghiem cua phuong trinh",
    "Thu hep khoang phan ly nghiem",
    "Tim nghiem gan dung voi so lan lap n",
    "Tim nghiem gan dung voi sai so e",
    "Tim Xn thoa man |Xn - X(n-1)| <= e",
    "Huong dan dieu khien MENU",
    "Gioi thieu ve phuong phap tiep tuyen",
    "Exit"
};

int degree; 
int decimal_digit;		
int distance_count;
double lower_bround;
double upper_bround;
double coeff_poly[N];			
double survey_value[N]; 
double distance_value[N];

// cac ham trong chuong trinh chinh
void input();
void print_poly_to_file(FILE *file);
bool check_input(double a, double b);
void domain_solution();
double f(double x);
double df(double x);
double ddf(double x);
double f1(double x);
double f2(double x);
double min(double f(double x), double a, double b);
double max(double f(double x), double a, double b);
double sign(double x);
bool fourier_point(double a); 
double sai_so(double x, double x_old, double m1, double M2, int ct_saiso);
void chucnang_1();
void chucnang_2();
void chucnang_3();
void chucnang_4();
void chucnang_5();
void menu();

// ham in phuong trinh ra file
void print_poly_to_file (FILE *file){
	fprintf(file, "\n\nPhuong trinh: F(x) = %.*lfx^%d", decimal_digit, coeff_poly[0], degree);
	for (int i = 1; i <= degree; i++){
    	if(coeff_poly[i] >= 0)
        	fprintf(file, " +%.*lfx^%d", decimal_digit, coeff_poly[i], degree - i);
        else 
        	fprintf(file, " %.*lfx^%d", decimal_digit, coeff_poly[i], degree - i);
    }
    fprintf(file, " = 0\n");
}

// ham nhap phuong trinh
void input() {	
	int c;
    bool valid_input = false;
    FILE* file = fopen("input.txt", "w");
    
    if (file == NULL) {
    	TextColor(116);
        gotoxy(4,4); printf("%c Error. Khong the mo file de ghi.", 175);
        return;
    }
    
    while (!valid_input) {
    	khungngoai();
    	khungthongtin();
        TextColor(113); 
		gotoxy(4,4); printf("- Xet %c(x) la da thuc bac n co dang:", 159);
        gotoxy(4,6); printf(" %c(x) = a0*x^n + a1*x^(n-1) + a2*x^(n-2) +...+ an*x^0", 159);
        gotoxy(4,8); printf("Hay nhap da thuc %c(x) co dang nhu tren de bat dau tinh toan!", 159);
		gotoxy(4,10); printf("%c Nhap bac cua da thuc n = ", 175);
		
        if (scanf("%d", &degree) != 1 || degree < 0 || degree > N) {
        	TextColor(116);
        	gotoxy(4,12); printf("%c Error! Hay nhap mot so nguyen khong am nho hon 100.", 175);
        	gotoxy(4,13); printf("%c An Enter de nhap lai da thuc!", 175);
        	while (getchar() != '\n');  
            getchar();
            continue;
        }
        fprintf(file, "\nNguoi dung nhap vao: ");
        fprintf(file, "\n- Bac cua da thuc: %d.", degree);	
        
        TextColor(112); 
		gotoxy(4,12); printf("%c So chu so phan thap phan muon hien thi la: ", 175); 
		if (scanf("%d", &decimal_digit) != 1 || decimal_digit < 0 || decimal_digit > 20) {
        	TextColor(116);
        	gotoxy(4,13); printf("%c Error! Hay nhap mot so nguyen khong am nho hon 100.", 175);
        	gotoxy(4,14); printf("%c An Enter de nhap lai da thuc!", 175);
        	while (getchar() != '\n');
            getchar();
            continue;
        }
    	fprintf(file, "\n- So chu so phan thap phan muon hien thi la: %d.", decimal_digit);
    	
        TextColor(117);
		gotoxy(4,14); printf("%c Nhap cac he so cua da thuc: ", 175);
        fprintf(file, "\n\n- Cac he so cua da thuc:");
        for (int i = 0; i <= degree; i++) {
        	gotoxy(4,15 + i); printf("+) a%d = ", i);
            if (scanf("%lf", &coeff_poly[i]) != 1) {
            	TextColor(116);
            	gotoxy(4,16 + i); printf("%c Error! He so khong hop le.", 175);
            	gotoxy(4,17 + i); printf("%c An Enter de nhap lai da thuc!", 175);
            	while (getchar() != '\n');  
            	getchar();
                valid_input = false;
                break;
            }
            fprintf(file, "\n +> a%d = %.*lf", i, decimal_digit, coeff_poly[i]);
            valid_input = true;
        }
    }
    
    print_poly_to_file(file);
    fclose(file);
    
    TextColor(113);
    gotoxy(4,18 + degree); printf("%c Phuong trinh vua nhap la: ",175); 
    gotoxy(6,19 + degree); output(); 
    TextColor(116);
    gotoxy(4,21 + degree); printf("%c An Enter de bat dau su dung chuong trinh!",175);
    getch(); 
}

// ham in ra phuong trinh khi chay chuong trinh
void output()
{		
	printf("%c(x) = %.3lfx^%d", 159, coeff_poly[0], degree);
    for (int i = 1; i <= degree; i++){
    	if(coeff_poly[i] >= 0)
        	printf(" +%.3lfx^%d", coeff_poly[i], degree - i);
        else 
        	printf(" %.3lfx^%d", coeff_poly[i], degree - i);
    }
    printf(" = 0");
    TextColor(0);
}

// ham tinh gia tri f(x)
double f(double x)
{
    double temp = 0;
    for (int i = degree; i >= 0; i--) {
        temp += coeff_poly[degree - i] * pow(x, i);
    }
    return temp;
}

// ham tinh gia tri dao ham cap 1 cua f(x)
double df(double x) {
    double h = 1e-7;
    return ((f(x + h) - f(x - h)) / (2 * h));
}

// ham tinh gia tri dao ham cap 2 cua f(x)
double ddf(double x) {
    double h = 1e-7;
    return ((df(x + h) - df(x - h)) / (2 * h));
}

// ham tim min cua ham so
double min(double f(double x), double a, double b){
    double x0 = a, alpha;
    double min = a;
    alpha = (b - a) / 10000;
    for (int i = 0; i < 10000; i++){
        if (f(min) > f(x0))
            min = x0;
        x0 = x0 + alpha;
    }
    return f(min);
}

// ham tim max cua ham so
double max(double f(double x), double a, double b){
    double x0 = a, alpha;
    double max = a;
    alpha = (b - a) / 10000;
    for (int i = 0; i < 10000; i++){
        if (f(max) < f(x0))
            max = x0;
        x0 = x0 + alpha;
    }
    return f(max);
}

// ham xac dinh dau cua mot gia tri x
double sign(double x)
{
	if (x>=0) return 1;
	else return -1;
}

// ham tra ve tri tuyet doi dao ham cap 1 cua f(x)
double f1(double x){
    return fabs(df(x));
}

// ham tra ve tri tuyet doi dao ham cap 2 cua f(x)
double f2(double x){
    return fabs(ddf(x));
}

// ham tinh sai so
double sai_so(double x, double x_old, double m1, double M2, int ct_saiso){
    if (ct_saiso == 1)
        return fabs(f(x))/ m1;
    else if (ct_saiso == 2)
        return M2 * pow((x - x_old), 2)/ (2 * m1);
}

// ham tim diem fourier
bool fourier_point(double a){
	if (sign(f(a)) == sign(ddf(a)))	
		return true;
    else return false;
}

// ham kiem tra dieu kien hoi tu
bool check_input(double a, double b){
    if (a == b) return false;
    else if (sign(f(a)) == sign(f(b))) return false;
    else if (a > b) return false;
    else if (sign(max(df, a, b)) != sign(min(df, a, b))) return false;
    else if (sign(max(ddf, a, b)) != sign(min(ddf, a, b))) return false;
    else return true;
}

// ham tim mien chua nghiem
void domain_solution()
{
    double temp[N], max, k;
    upper_bround = -1;
    lower_bround = 1;
    
    for (int i = 0; i <= degree; i++) {
        temp[i] = coeff_poly[i]; 
    }
    do {
        max = 0;
        k = 0;
        if (temp[0] < 0) {
            for (int i = 0; i <= degree; i++) {
                temp[i] = -temp[i];
            }
        }
        for (int i = 1; i <= degree; i++) {
            if (temp[i] < 0) {
                k = i;
                break;
            }
        }
        for (int i = 1; i <= degree; i++) {
            if (temp[i] < 0) {
                if (abs(temp[i]) > max) max = abs(temp[i]);
            }
        }
        if (max == 0) {
            if (upper_bround == -1) upper_bround = 0;
            else lower_bround = 0;
        }
        else {
            if (upper_bround == -1) upper_bround = 1 + pow((max / temp[0]), 1 / k);
            else lower_bround = -(1 + pow((max / temp[0]), 1 / k));
        }
        for (int i = 0; i <= degree; i++) {
            if (i % 2 == 1)
                temp[degree - i] = -temp[degree - i];
        }
    }
    while (lower_bround > 0);
}

// ham thuc hien chuc nang 1
void chucnang_1()
{
	double x0, x1, sign, temp0, temp1, value1, value2;
    double eta = 1e-11;
	int i = 0, j = 0, k = 1; 
    FILE* file = fopen("chucnang_1.txt", "w");
    
    domain_solution();
    TextColor(113);
    fprintf(file, "\nChuc nang 1: Tim cac khoang phan ly nghiem cua phuong trinh.");
    fprintf(file, "\n\nINPUT: Bac cua phuong trinh, cac he so cua phuong trinh f(x) = 0.");
    fprintf(file, "\nOUTPUT: Cac khoang phan ly nghiem cua phuong trinh.");
    print_poly_to_file(file);
    
    if (degree == 0) {
        if (coeff_poly[0] == 0){
        	gotoxy(84,2); printf("Khoang phan ly nghiem: (-00,+00)");
            gotoxy(84,4); printf("Phuong trinh co vo so nghiem!");
            fprintf(file, "\nKhoang phan ly nghiem: (-oo,+oo)\n");
            fprintf(file, "\nPhuong trinh co vo so nghiem!\n");
        }
        else{
        	gotoxy(84,2); printf("Khoang phan ly nghiem: (--,--)");
            gotoxy(84,4); printf("Phuong trinh vo nghiem!");
            fprintf(file, "\nKhoang phan ly nghiem: (--,--)\n");
            fprintf(file, "\nPhuong trinh vo nghiem!\n");
        }
    }
    else if (degree == 1){
    	gotoxy(84,2); printf("Khoang phan ly nghiem: ");
        gotoxy(84,3); printf("(%.*lf , %.*lf)", decimal_digit, (- coeff_poly[1] / coeff_poly[0]) - 1, decimal_digit, (- coeff_poly[1] / coeff_poly[0]) + 1);
        fprintf(file, "\nKhoang phan ly nghiem: (%.*lf , %.*lf)\n", decimal_digit, (- coeff_poly[1] / coeff_poly[0]) - 1, decimal_digit, (- coeff_poly[1] / coeff_poly[0]) + 1);
    }
    else if (lower_bround == upper_bround) {
        if (f(lower_bround) == 0) {
        	gotoxy(84,2); printf("Khoang phan ly nghiem: ");
        	gotoxy(84,3); printf("(%.*lf , %.*lf)", decimal_digit, lower_bround - 1, decimal_digit, upper_bround + 1);
        	fprintf(file, "\nKhoang phan ly nghiem: (%.*lf , %.*lf)\n", decimal_digit, lower_bround - 1, decimal_digit, upper_bround + 1);
        }
        else{
        	gotoxy(84,2); printf("Khoang phan ly nghiem: (--,--)");
        	gotoxy(84,4); printf("Phuong trinh vo nghiem!");
        	fprintf(file, "\nKhoang phan ly nghiem: (--,--)\n");
            fprintf(file, "\nPhuong trinh vo nghiem!\n");
    }
}
    else {
        x1 = lower_bround;
        while (x1 < upper_bround) {
            x0 = x1;
            temp0 = df(x0);
            if (temp0 < 0)
                sign = -1;
            else
                sign = 1;
            x1 = x0 + sign * eta * temp0;
            temp1 = df(x1);
            for (int i = 0; i < max_loop; i++) {
                if (temp0 * temp1 > 0) {
                    while (eta < 0.008) {
                        eta = eta * 2;
                        x1 = x0 + sign * eta * temp0;
                        if (df(x1) * temp0 < 0) {
                            eta = eta / 2;
                            break;
                        }
                    }
                }
                else {
                    while (eta > 0) {
                        eta = eta / 2;
                        x1 = x0 + sign * eta * temp0;
                        if (df(x1) * temp0 > 0)
                            break;
                    }
                }
                x1 = x0 + sign * eta * temp0;
                x0 = x1;
                if (abs(df(x1)) < 1e-4) {
                    survey_value[k] = x1;
                    k++; 
                    break;
                }
                eta = 1e-11;
                temp0 = df(x0);
                x1 = x0 + sign * eta * temp0;
                temp1 = df(x1);
                if (x1 > upper_bround)
                    break;
            }
            x1 = x1 + 0.001;
        }
        survey_value[0] = lower_bround;
        survey_value[k] = upper_bround;
    distance_count = 1;
    for (i = 0; i < k; i++) {
        value1 = f(survey_value[i]);
        value2 = f(survey_value[i + 1]);
        if (value1 * value2 < 0) {
        	distance_value[j] = survey_value[i];
        	j += 1;
			distance_value[j] = survey_value[i+1];
			j += 1;
            gotoxy(84, 2+3*(distance_count - 1));
            printf("%d. Khoang phan ly nghiem thu %d", distance_count, distance_count);
            gotoxy(84, 3+3*(distance_count - 1));
            printf("%c Can duoi: %.*lf", 175, decimal_digit, survey_value[i]);
            gotoxy(84, 4+3*(distance_count - 1));
            printf("%c Can tren: %.*lf", 175, decimal_digit, survey_value[i+1]);
        	fprintf(file, "\n\nKhoang phan ly nghiem thu %d", distance_count);
            fprintf(file, "\n- Can duoi: %.*lf", decimal_digit, survey_value[i]);
            fprintf(file, "\n- Can tren: %.*lf", decimal_digit, survey_value[i + 1]);
            distance_count += 1;
        }
    }
}
    fprintf(file, "\n\nKet thuc.");
    fclose(file);
}

// ham thuc hien chuc nang 2
void chucnang_2()
{	
	int i = 0, chon, lan_lap = 1;
	double temp=0;
	double a, b, value1, value2;
	FILE* file = fopen("chucnang_2.txt", "w");
	
	fprintf(file, "\nChuc nang 2: Thu hep khoang phan ly nghiem (a,b) thoa man |a-b| <= 0.5 bang cach su dung phuong phap chia doi\n");
	print_poly_to_file(file);
	fprintf(file, "\n\nINPUT: cac KPL nghiem tim duoc o chuc nang 1, lua chon cua nguoi dung.");
	fprintf(file, "\n\nOUTPUT: KPL nghiem duoc rut gon thoa man |a - b| <= 0.5.");
	
	khung();
	TextColor(287);
    gotoxy(33,7); printf(" CHUC NANG 2 ");
	TextColor(113);
	gotoxy(16, 9); printf("2. Thu hep khoang phan ly nghiem (a,b) thoa man");
    gotoxy(16, 10); printf("|a - b| <= 0.5 su dung phuong phap chia doi");
    
    if (distance_count == 0){
    	TextColor(116);
    	gotoxy(16, 12); printf("!!! Khong ton tai khoang phan ly de rut gon.");
    	gotoxy(16, 13); printf("- Neu phuong trinh co nghiem, hay thuc hien");
    	gotoxy(16, 14); printf("chuc nang 1 truoc de co khoang phan ly nghiem!");
    	fprintf(file, "\n!!! Khong ton tai khoang phan ly nghiem de rut gon.");
    	fprintf(file, "\n\nKet thuc.");
    	fclose(file);
	}
	else{
		while (1){
		TextColor(120);
    	gotoxy(16, 11); printf("(Nhap so nguyen duong nho hon %d!)", distance_count);
    	TextColor(113);
		gotoxy(16, 13); printf("Chon khoang phan ly nghiem thu: ");
    	if (scanf("%d", &chon) != 1 || chon < 1 || chon >= distance_count) {
    		TextColor(116);
        	gotoxy(16,14); printf("%c Khoang phan ly nghiem khong hop le. ", 175);
			gotoxy(16,15); printf("An Enter de nhap lai!");
            while (getchar() != '\n');  
            getchar();
        	khung();
        	TextColor(113);
			gotoxy(16, 9); printf("2. Thu hep khoang phan ly nghiem (a,b) thoa man");
    		gotoxy(16, 10); printf("|a - b| <= 0.5 su dung phuong phap chia doi");
            continue; 
        }
        break;
    }
    fprintf(file, "\nKhoang phan ly nguoi dung chon: %d\n", chon);
    a = distance_value[2 * chon -2];
    b = distance_value[2 * chon - 1];
    
    gotoxy(84, 3); printf("Khoang phan ly ban dau la:");
	gotoxy(84, 4); printf("Can duoi a: %.*lf", decimal_digit, distance_value[2 * chon -2]);
	gotoxy(84, 5); printf("Can tren b: %.*lf", decimal_digit, distance_value[2 * chon -1]);
	fprintf(file, "\nKhoang phan ly ban dau la:\n");
    fprintf(file, "- Can duoi a: %.*lf\n", decimal_digit, a);
    fprintf(file, "- Can tren b: %.*lf\n", decimal_digit, b);
    fprintf(file, "\nSu dung phuong phap chia doi de thu hep khoang cach ly:\n", lan_lap);
	while((b-a) > 0.5){
		temp = (a+b) / 2.0;
		value1 = f(a);
        value2 = f(temp);
        if(value1 * value2 < 0){
        	b = temp;
		}
		else a = temp;
		fprintf(file, "\nLan lap thu %d\n", lan_lap);
        fprintf(file, "- Can duoi a: %.*lf\n", decimal_digit, a);
        fprintf(file, "- Can tren b: %.*lf\n", decimal_digit, b);
        lan_lap++;
		}
		
	gotoxy(84, 7); printf("Khoang phan ly sau khi rut gon:");
	gotoxy(84, 8); printf("Can duoi a: %.*lf", decimal_digit, a);
	gotoxy(84, 9); printf("Can tren b: %.*lf", decimal_digit, b);
	gotoxy(84, 11); printf("|a - b| = %.*lf <= 0.5", decimal_digit, fabs(a-b));
	gotoxy(84, 13); printf("So lan lap chia doi: %d", lan_lap - 1);
	fprintf(file, "\n\nKhoang phan ly nghiem sau khi rut gon:");
	fprintf(file, "\n- Can duoi a: %.*lf", decimal_digit, a);
	fprintf(file, "\n- Can tren b: %.*lf", decimal_digit, b);
	fprintf(file, "\n\n|a - b| = %.*lf <= 0.5 thoa man de bai.", decimal_digit, fabs(a-b));
	fprintf(file, "\n\nSo lan lap chia doi: %d", lan_lap - 1);
}
    fprintf(file, "\n\nKet thuc.");
	fclose(file);
	}

// ham thuc hien chuc nang 3
void chucnang_3()
{
	double a, b, eps;
	double x, x_old, m1, M2, delta1, delta2;
	int n, i, j = 0;
	bool check;
	FILE* file = fopen("chucnang_3.txt", "w");
	
    fprintf(file, "\nChuc nang 3: Tim nghiem gan dung voi so lan lap cho truoc trong khoang (a, b) va danh gia sai so epsilon theo hai cong thuc sai so.");
    print_poly_to_file(file);
	fprintf(file, "\nINPUT: KPL nghiem (a,b), so lan lap.");
	fprintf(file, "\nOUTPUT: Nghiem gan dung Xn, sai so epsilon.");
    khung();
    TextColor(287);
    gotoxy(33,7); printf(" CHUC NANG 3 ");
    TextColor(113);
    gotoxy(16, 9); printf("%c Nhap khoang phan ly nghiem (a,b): ", 175);
   	gotoxy(16, 10); printf("%c Nhap can duoi a: ", 175);scanf("%lf", &a);
   	gotoxy(16, 11); printf("%c Nhap can tren b: ", 175);scanf("%lf", &b);
   	fprintf(file, "\n\nKhoang phan ly nghiem (a,b):");
   	fprintf(file, "\n- Can duoi a: %.*lf", decimal_digit, a);
   	fprintf(file, "\n- Can tren b: %.*lf", decimal_digit, b);
   	check = check_input(a, b);
   	
   	if (check == true){
        TextColor(113);
    	gotoxy(16,12); printf("%c Nhap so lan lap: n = ", 175);scanf("%d", &n);
    	fprintf(file, "\n\nSo lan lap nguoi dung nhap la: %d", n);
    	if (fourier_point(a) == true) x_old = a;
    	else if (fourier_point(a) == false) x_old = b;
    	
    	m1 = min(f1, a, b);
	    M2 = max(f2, a, b);
	    fprintf(file, "\n\n- Gia tri nho nhat cua |f'(x)| la: m1 = %.*lf", decimal_digit, m1);
	   	fprintf(file, "\n- Gia tri lon nhat cua |f''(x)| la: M2 = %.*lf", decimal_digit, M2);
	
		gotoxy(84,2); printf("%c Diem Fourier la:", 175);
		gotoxy(84,3); printf("           x0 = %.*lf", decimal_digit, x_old);
		fprintf(file, "\n\nDiem Fourier la: x0 = %.*lf", decimal_digit, x_old);
		
    	x = x_old; 
    	for (i = 1; i<= n; i++){
    		TextColor(113);
    		x_old = x;
	        x = x_old - f(x_old) / df(x_old);
	        delta1 = sai_so(x, x_old, m1, M2, 1);
	        delta2 = sai_so(x, x_old, m1, M2, 2);
	        gotoxy(84,5 + j); printf("Lan lap %d: x%d = %.*lf", i, i, decimal_digit, x);
	        TextColor(118);
	        gotoxy(84,6 + j); printf("- Sai so 1 = %.15lf", delta1);
	        TextColor(117);
	        gotoxy(84,7 + j); printf("- Sai so 2 = %.15lf", delta2);
	        j += 4;
	        fprintf(file, "\n\nLan lap thu %d: ", i);
	        fprintf(file, "\nNghiem xap xi x%d = %.*lf", i, decimal_digit, x);
	        fprintf(file, "\nSai so muc tieu             = %.20lf", delta1);
	        fprintf(file, "\nSai so hai xap xi lien tiep = %.20lf", delta2);
		}
		if(delta1 < delta2){
			TextColor(112);
			gotoxy(16,14); printf("%c Danh gia sai so:", 175);
			TextColor(114);
			gotoxy(16,15); printf("- Phuong phap tiep tuyen co toc do hoi tu cao");
			gotoxy(16,16); printf("va ket qua co do chinh xac cao.");
			gotoxy(16,17); printf("- Cong thuc sai so 1 co sai so nho hon so voi");
			gotoxy(16,18); printf("cong thuc sai so 2 o nhung lan lap dau.");
			fprintf(file, "\n\nDanh gia sai so cua hai cong thuc:");
			fprintf(file, "\n- Uu diem: Toc do hoi tu cao, ket qua co do chinh xac cao.");
			fprintf(file, "\n- Nhuoc diem: Dieu kien lua chon x0 ban dau kha chat.");
			fprintf(file, "\n- Cong thuc sai so 1 co sai so nho hon so voi cong thuc sai so 2 o nhung lan lap dau. ");
		}
		else {
			TextColor(112);
			gotoxy(16,14); printf("%c Danh gia sai so:", 175);
			TextColor(114);
			gotoxy(16,15); printf("- Phuong phap tiep tuyen co toc do hoi tu cao");
			gotoxy(16,16); printf("va ket qua co do chinh xac cao.");
			gotoxy(16,17); printf("- Cong thuc sai so 2 co sai so nho hon so voi");
			gotoxy(16,18); printf("cong thuc sai so 1 o nhung lan lap dau.");
			fprintf(file, "\n\nDanh gia sai so cua hai cong thuc:");
			fprintf(file, "\n- Uu diem: Toc do hoi tu cao, ket qua co do chinh xac cao.");
			fprintf(file, "\n- Nhuoc diem: Dieu kien lua chon x0 ban dau kha chat.");
			fprintf(file, "\n- Cong thuc sai so 2 co sai so nho hon so voi cong thuc sai so 1 o nhung lan lap dau. ");
		}
		fprintf(file, "\n\nGhi chu: Vi phuong phap tiep tuyen hoi tu nhanh va co sai so rat nho gan 0 nen sai so em se de nhieu chu so phan thap phan hon.");
		fprintf(file, "\n\nKet thuc.");
		fclose(file);
		}
    else if (check == false){
    	TextColor(116);
        gotoxy(16, 13); printf("!!! Error: Loi nhap KPL nghiem.");
        gotoxy(16, 14); printf("%c KPL nghiem khong thoa man dieu kien hoi tu", 175);
        gotoxy(16, 15); printf("cua phuong phap tiep tuyen."); 
        fprintf(file, "\n\nINPUT khong hop le. Khoang phan ly nghiem khong thoa man dieu kien hoi tu cua phuong phap tiep tuyen.\n\nKet thuc.");
        fclose(file);
	}
}	

// ham thuc hien chuc nang 4
void chucnang_4()
{
	double a, b, eps;
	double x, x_old, m1, M2, delta;
	int ct_saiso, i = 1;
	bool check;
	FILE* file = fopen("chucnang_4.txt", "w");
	
    fprintf(file, "\nChuc nang 4: Tim nghiem gan dung trong khoang (a, b) voi sai so epsilon cho truoc.");
    print_poly_to_file(file);
    fprintf(file, "\nINPUT: KPL nghiem (a,b), sai so epsilon, cong thuc sai so.");
	fprintf(file, "\nOUTPUT: Nghiem gan dung Xn thoa man sai so epsilon.");
	
    khung();
    TextColor(287);
    gotoxy(33,7); printf(" CHUC NANG 4 ");
    TextColor(113);
    gotoxy(16, 9); printf("%c Nhap khoang phan ly nghiem (a,b): ", 175);
   	gotoxy(16, 10); printf("%c Nhap can duoi a: ", 175);scanf("%lf", &a);
   	gotoxy(16, 11); printf("%c Nhap can tren b: ", 175);scanf("%lf", &b);
   	fprintf(file, "\n\nKhoang phan ly nghiem (a,b):");
   	fprintf(file, "\n- Can duoi a: %.*lf", decimal_digit, a);
   	fprintf(file, "\n- Can tren b: %.*lf", decimal_digit, b);
   	
   	check = check_input(a, b);
   	if (check == true){
        // tim nghiem trong KPL nghiem hop le
        TextColor(113);
        gotoxy(16, 12); printf("%c Nhap sai so: ", 175); scanf("%lf", &eps);
        fprintf(file, "\nSai so epsilon: %.20lf", eps);
    	gotoxy(16,13); printf("Cong thuc sai so:");
		gotoxy(16,14); printf("1. |Xn - X*| <= |f(Xn)| / m1");
		gotoxy(16,15); printf("2. |Xn - X*| <= (M2 / 2m1) * (Xn - X(n-1))^2");
		gotoxy(16,17); printf("%c Chon cong thuc sai so: ", 175); scanf("%d", &ct_saiso);
		
		if (ct_saiso == 1){
			fprintf(file, "\n\nNguoi dung chon cong thuc sai so muc tieu:");
			fprintf(file, "\n\t\t|Xn - X*| <= |f(Xn)| / m1");
		}
		else if (ct_saiso == 2){
			fprintf(file, "\n\nNguoi dung chon cong thuc sai so theo hai xap xi lien tiep:");
			fprintf(file, "\n\t\t|Xn - X*| <= (M2 / 2m1) * (Xn - X(n-1))^2");
		}
		
		m1 = min(f1, a, b);
	    M2 = max(f2, a, b);
	    fprintf(file, "\n\n- Gia tri nho nhat cua |f'(x)| la: m1 = %.*lf", decimal_digit, m1);
	   	fprintf(file, "\n- Gia tri lon nhat cua |f''(x)| la: M2 = %.*lf", decimal_digit, M2);
		
		if (fourier_point(a) == true) x_old = a;		// diem fourier 
    	else if (fourier_point(a) == false) x_old = b;
    	x = x_old;
		gotoxy(84,3); printf("%c Diem Fourier la:", 175);
		gotoxy(84,4); printf("           x0 = %.*lf", decimal_digit, x_old);
	    fprintf(file, "\n\nDiem Fourier la: x0 = %.*lf \n", decimal_digit, x_old);
	    
	    do {
	        x_old = x;
	        x = x_old - f(x_old) / df(x_old);
	        delta = sai_so(x, x_old, m1, M2, ct_saiso);
	        gotoxy(84,4 + i); printf("Lan lap %d: x%d = %.*lf", i, i, decimal_digit, x);
	        fprintf(file, "\n\nLan lap thu %d: ", i);
	        fprintf(file, "Nghiem x%d = %.*lf,  Sai so = %.20lf", i, decimal_digit, x, delta);
	        i++;
	    }
	    while (delta > eps);
		
		gotoxy(84,5 + i); printf("Ket luan: ");
		gotoxy(84,6 + i); printf("%c So lan lap: %d", 175, i - 1);
		gotoxy(84,8 + i); printf("%c Nghiem gan dung:", 175);
		gotoxy(84,9 + i); printf("            x = %.*lf", decimal_digit, x);
		gotoxy(84,11 + i); printf("%c Sai so = %.20lf", 175, delta);
	    fprintf(file, "\n\nKet luan: ");
	    fprintf(file, "\nSo lan lap: %d", i - 1);
	    fprintf(file, "\nNghiem gan dung: x = %.*lf", decimal_digit, x);
	    fprintf(file, "\nSai so = %.20lf <= %.20lf thoa man yeu cau de bai.", delta, eps);
	    fprintf(file, "\n\nGhi chu: Vi phuong phap tiep tuyen hoi tu nhanh va co sai so rat nho gan 0 nen sai so em se de nhieu chu so phan thap phan hon.");
	    fprintf(file, "\n\nKet thuc.");
		fclose(file);
    }
    else if (check == false){
    	TextColor(116);
        gotoxy(16, 13); printf("!!! Error: Loi nhap KPL nghiem.");
        gotoxy(16, 14); printf("%c KPL nghiem khong thoa man dieu kien hoi tu", 175);
        gotoxy(16, 15); printf("cua phuong phap tiep tuyen.");
        fprintf(file, "\n\nINPUT khong hop le. Khoang phan ly nghiem khong thoa man dieu kien hoi tu cua phuong phap tiep tuyen.\n\nKet thuc.");
        fclose(file);
	}
}

// ham thuc hien chuc nang 5
void chucnang_5()
{
	double a, b, eps;
	double x, x_old, m1, M2, delta;
	int i = 1, j = 1;
	bool check;
	FILE* file = fopen("chucnang_5.txt", "w");
	
    fprintf(file, "\nChuc nang 5: Tim nghiem gan dung Xn trong khoang (a, b) thoa man dieu kien: |Xn - X(n-1)| <= e.");
    print_poly_to_file(file);
    fprintf(file, "\nINPUT: KPL nghiem (a,b), sai so epsilon");
	fprintf(file, "\nOUTPUT: Nghiem gan dung Xn thoa man |Xn - X(n-1)| <= e.");
    m1 = min(f1, a, b);
    M2 = max(f2, a, b);
    
    khung();
    TextColor(287);
    gotoxy(33,7); printf(" CHUC NANG 5 ");
    TextColor(113);
    gotoxy(16, 9); printf("%c Nhap khoang phan ly nghiem (a,b): ", 175);
   	gotoxy(16, 10); printf("%c Nhap can duoi a: ", 175);scanf("%lf", &a);
   	gotoxy(16, 11); printf("%c Nhap can tren b: ", 175);scanf("%lf", &b);
   	fprintf(file, "\n\nKhoang phan ly nghiem (a,b):");
   	fprintf(file, "\n- Can duoi a: %.*lf", decimal_digit, a);
   	fprintf(file, "\n- Can tren b: %.*lf", decimal_digit, b);

   	check = check_input(a, b);
   	if (check == true){

        TextColor(113);
        gotoxy(16, 12); printf("%c Nhap sai so: ", 175); scanf("%lf", &eps);
        fprintf(file, "\n\nSai so epsilon: %.20lf", eps);
		
		if (fourier_point(a) == true) x_old = a;
    	else if (fourier_point(a) == false) x_old = b;
    	x = x_old;
		gotoxy(84,2); printf("%c Diem Fourier la:", 175);
		gotoxy(84,3); printf("           x0 = %.*lf", decimal_digit, x_old);
	    fprintf(file, "\n\nDiem Fourier la: x0 = %.*lf \n", decimal_digit, x_old);
	    
	    do {
	        x_old = x;
	        x = x_old - f(x_old) / df(x_old);
	        delta = fabs(x - x_old);
	        gotoxy(84,4 + j); printf("Lan lap %d: x%d = %.*lf", i, i, decimal_digit, x);
	        gotoxy(84,5 + j); printf("|x%d - x%d| = %.15lf", i, i - 1, delta);
	        fprintf(file, "\n\nLan lap thu %d:", i);
	        fprintf(file, "   x%d = %.*lf", i, decimal_digit, x);
	        fprintf(file, "\n- |x%d - x%d| = %.20lf", i, i - 1, delta);
	        i++;
	        j += 3;
	    }
	    while (delta > eps);
		TextColor(125); 
		gotoxy(16,14); printf("Ket luan: ");
		gotoxy(16,15); printf("%c So lan lap: %d", 175, i - 1);
		gotoxy(16,16); printf("%c |x%d - x%d| = %.15lf <= %.15lf", 175, i - 1, i - 2, delta, eps);
		gotoxy(16,17); printf("%c Nghiem gan dung: x%d = %.*lf", 175, i - 1, decimal_digit, x);
	    fprintf(file, "\n\nKet luan: ");
	    fprintf(file, "\nSo lan lap: %d", i - 1);
	    fprintf(file, "\nNghiem gan dung: x%d = %.*lf", i - 1, decimal_digit, x);
	    fprintf(file, "\nSai so |x%d - x%d| = %.20lf <= %.20lf thoa man yeu cau de bai.\n\nKet thuc.", i - 1, i - 2, delta, eps);
	    fclose(file);
    }
    else if (check == false){
    	TextColor(116);
        gotoxy(16, 13); printf("!!! Error: Loi nhap KPL nghiem.");
        gotoxy(16, 14); printf("%c KPL nghiem khong thoa man dieu kien hoi tu", 175);
        gotoxy(16, 15); printf("cua phuong phap tiep tuyen.");
        fprintf(file, "\n\nINPUT khong hop le. Khoang phan ly nghiem khong thoa man dieu kien hoi tu cua phuong phap tiep tuyen.\n\nKet thuc.");
        fclose(file);
	}
}

void menu()	
{	
	int position = 1;
    int keyPress = 0;
	khung();
    while (keyPress != 13) {
        for (int i = 1; i <= MAX; i++) {
            gotoxy(16, 9 + i);
            arrowHere(i, position);
            printf("%d. %s \n", i, option[i - 1]);
        }
        keyPress = getch();
        if (keyPress == 80 || keyPress == 's' || keyPress == 'S' || keyPress == '2') {
            if (position == MAX) position = MIN;
            else position++;
        }
        else if (keyPress == 72 || keyPress == 'w' || keyPress == 'W' || keyPress == '8') {
            if (position == MIN ) position = MAX;
            else position--;
        }
        else if (keyPress == 9) {
            position += 2;
            if (position > MAX) position = MIN;
        }
        else if (keyPress == 27) {
        	system("cls");
            return;
        }
}
    switch (position) {
    case 1:
        chucnang_1();
        getch();
        menu();
        break;
    case 2:
        chucnang_2();
        getch();
        menu();
        break;
    case 3:
        chucnang_3();
        getch();
        menu();
        break;
    case 4:
        chucnang_4();
        getch();
        menu();
        break;
    case 5:
        chucnang_5();
        getch();
        menu();
        break;
    case 6: 
        khunghuongdan();
        getch();
        menu();
        break;
    case 7:
    	khungtieptuyen();
    	getch();
        menu();
        break;
    case 8: 
    	khungexit();
		exit(0);
    }
}
 
int main()
{
    input();
	menu();
	khungexit();
    return 0;
}
