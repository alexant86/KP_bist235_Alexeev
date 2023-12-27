#include<stdio.h>
#include<locale.h>
#include<math.h>
#include<stdlib.h>
struct plitka {
	int type_material;
	float  shirina_plitka;
	float  high_plitka;
};
struct vanna {
	float col_vo_material;
	float s_with_openings;
	float s_without_openings;
};
float scanf_plitka(struct plitka * P);
float calculat(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V,int s);
float s_wall(float high, float length_wall);
float s_open(float open_hgh[], float open_sh[], float klv_open);
float scanf_vanna(float* l_w, float* h_w);
float scanf_open(float open_sh[], float open_hgh[]);
float klv_material(struct plitka * P,struct vanna * V,int hp);
float cor(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V,int s);
int otch(struct vanna * V, struct plitka * P);
int main()
{
	struct plitka P;
	struct vanna V;
	setlocale(LC_CTYPE, "RUS");
	float open_sh[5];
	float open_hgh[5];
	int s_w;
	int s_o;
	float length_wall, high, length_opening, high_opening;
	int flag;
	int d;
	int l_w = 0;
	int h_w = 0;
	float klv_open = 0;
	float material;
	int hp = 0;
	double c;
	char ct;
	int s = 0;
		puts("***********************************************************************************************************");
		puts("*Калькулятор для расчета необходимого количества сантехнической керамики для облицовки стен ванной комнаты* \n*с учетом размеров комнаты,окон и дверных проемов                                                         *");
		puts("***********************************************************************************************************");
		printf(" _________________________________________________________________________________________________________");
		puts("\n|Внимание!!!!!!!!                                                                                         |\n|При вводе данных, а именно при вводе длины и ширины стен, а также длины и ширины проёмов,                |\n|будьте внимательныи предельно осторожны                                                                  |\n|Ведь, если площадь стен будет меньше площади проёмов, программа завершит свою работу.                    |");
		puts("|_________________________________________________________________________________________________________|\n");
		puts("***********************************************************************************************************");
		puts("*Перечень пунктов меню                                                                                    *");
		puts("***********************************************************************************************************");
		printf("*1 - ввести параметры ванной                                                                              *\n*2 - ввести параметры проёмов                                                                             *\n*3 - ввести параметры плитки                                                                              *\n*4 - рассчитать площадь ванной                                                                            *\n*5 - узнать необходимое кол-во материала                                                                  *\n*6 - сохранить отчёт                                                                                      *\n*7 - завершение программы                                                                                 *\n");
		puts("***********************************************************************************************************");
		while (1) {
		puts("Введите номер пункта меню");
		scanf("%d", &d);
			switch (d) {
			case 1:
				scanf_vanna(&length_wall, &high);
				break;
			case 2:
				klv_open = scanf_open(open_sh, open_hgh);
				break;
			case 3:
				scanf_plitka(&P);
				break;
			case 4:
				printf("Если хотите узнать площадь ванной комнаты с учётом проёмов, нажмите 1");
				printf("\nЕсли хотите узнать площадь ванной комнаты без учёта проёмов, нажмите 2\n");
				scanf("%d", &s);
				calculat(length_wall, high, open_sh, open_hgh, klv_open, &V, s);
				if (cor(length_wall, high, open_sh, open_hgh, klv_open, &V, s) == 1) {
					return 0;
				}
				break;
			case 5:
				printf("Введите 2, если хотите узнать количество материала без проёмов");
				printf("\nВведите 1, если хотите узнать количество материала с проёмами\n");
				scanf("%d", &hp);
				while (hp != 1 && hp != 2) {
					puts("Вы должны ввести 1 или 2.");
					printf("Введите 2, если хотите узнать количество материала без проёмов");
					printf("\nВведите 1, если хотите узнать количество материала с проёмами\n");
					scanf("%d", &hp);
				}
				material = klv_material(&P, &V, hp);
				c = ceil(material);
				printf("Необходимое кол-во материала:%lf м\n", c);
				break;
			case 6:
				printf("Отчёт успешно сохранён\n");
				otch(&V, &P);
				break;
			case 7:
				return 0;
			default:
				scanf("%c", &ct);
				puts("Вы не выбрали пункт меню");
			}
	}
}
float calculat(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V,int s) {
	while(s!=1 && s!=2){
		puts("Вы должны ввести 1 или 2\nПовторите действие");
		printf("Если хотите узнать площадь ванной комнаты с учётом проёмов, нажмите 1");
		printf("\nЕсли хотите узнать площадь ванной комнаты без учёта проёмов, нажмите 2\n");
		scanf("%d", &s);
	}
	if (s == 2) 
	{
		V->s_without_openings = s_wall(l_w, h_w);
		V->s_with_openings = s_wall(l_w, h_w) - s_open(open_hgh, open_sh, klv_open);
		printf("%f\n", V->s_without_openings);
		return V->s_without_openings;
	}
	else if (s == 1) 
	{
		V->s_with_openings = s_wall(l_w, h_w) - s_open(open_hgh, open_sh, klv_open);
		V->s_without_openings = s_wall(l_w, h_w);
		printf("%.3f\n", V->s_with_openings);
		return V->s_with_openings;
	}
}
float cor(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V,int s) {
	if(V->s_with_openings<=0 && s == 1){
		puts("К сожалению вы не были бдительны при вводе данных\nПрограмма завершает своё действие так как площадь не может быть отрицательной");
		return 1;
	}
	else {
		return 0;
	}
}

float s_wall(float high, float length_wall) {
	return 4 * high * length_wall;
}
float s_open(float open_hgh[], float open_sh[],float klv_open) {
	float s = 0;
	for (int i = 0; i < klv_open; i++) {
		s = s + open_hgh[i] * open_sh[i];
	}
	return s;
}
float scanf_plitka(struct plitka* P) {
	int flag;
	char flag_1;
	float sh_p;
	float high_p;
		printf("Выберите вид строительного материала\n1.Керамическая плитка\n2.Стеклянная мозаика\n3.Натуральный камень\n");
		scanf("%d", &flag);
		switch (flag) {
		case 1:
			puts("Вы выбрали:Керамическая плитка");
			break;
		case 2:
			puts("Вы выбрали:Стеклянная мозаика");
			break;
		case 3:
			puts("Вы выбрали:Натуральный камень");
			break;
		default:
			scanf("%c", &flag_1);
			puts("Вы не выбрали вид строительного материала");
			printf("Выберите вид строительного материала\n1.Керамическая плитка\n2.Стеклянная мозаика\n3.Натуральный камень\n");
			scanf("%d", &flag);
		}
		P->type_material = flag;
		printf("Введите ширину плитки - м\n");
		scanf("%f", &sh_p);
		while (sh_p <= 0) {
			puts("Вы ввели некорекктное значение\nПопробуйте ещё раз");
			printf("Введите ширину плитки - м\n");
			scanf("%f", &sh_p);
		}
		P->shirina_plitka = sh_p;
		printf("Введите высоту плитки - м\n");
		scanf("%f", &high_p);
		while (high_p <= 0) {
			puts("Вы ввели некорекктное значение\nПопробуйте ещё раз");
			printf("Введите высоту плитки - м\n");
			scanf("%f", &high_p);
		}
		P->high_plitka = high_p;
}
float scanf_vanna(float* l_w, float* h_w) {
	puts("Введите ширину стены - м");
	scanf("%f", l_w);
	while (*l_w <= 0) {
		puts("Вы ввели некорректное значение");
		puts("Введите ширину стены - м");
		scanf("%f", l_w);
	}
	puts("Введите высоту стены - м");
	scanf("%f", h_w);
	while (*h_w <= 0) {
		puts("Вы ввели некорректное значение");
		puts("Введите высоту стены - м");
		scanf("%f", h_w);
	}
}
float scanf_open(float open_sh[], float open_hgh[]) {
	float klv_open;
	printf("Введите кол-во проёмов\n");
	scanf("%f", &klv_open);
	while (klv_open != ceil(klv_open) || klv_open <= 0) {
		puts("Вы ввели некорректное значение\nПопробуйте ещё раз");
		printf("Введите кол-во проёмов\n");
		scanf("%f", &klv_open);
	}
		for (int i = 0; i < klv_open; i++) {
			printf("Введите ширину %d проёма м\n", i + 1);
			scanf("%f", &open_sh[i]);
			while (open_sh[i] <= 0) {
				puts("Вы ввели некорректное значение\nПопробуйте ещё раз");
				printf("Введите ширину %d проёма м\n", i + 1);
				scanf("%f", &open_sh[i]);
			}
		}
	for (int i = 0; i < klv_open; i++) {
		printf("Введите высоту %d проёма м\n", i + 1);
		scanf("%f", &open_hgh[i]);
		while (open_hgh[i] <= 0) {
			puts("Вы ввели некорректное значение\nПопробуйте ещё раз");
			printf("Введите высоту %d проёма м\n", i + 1);
			scanf("%f", &open_hgh[i]);
		}
	}
	return klv_open;
}
int otch(struct vanna* V, struct plitka* P) {
	char fname[20] = "vanna.txt";
	FILE* out;
	if ((out = fopen(fname, "a")) == NULL) {
		printf("Ошибка открытия файла для записи");
		return 1;
	}
	fprintf(out, "Тип материала:%d\n", P->type_material);
	fprintf(out, "\nШирина плитки:%.4f м\n", P->shirina_plitka);
	fprintf(out, "\nВысота плитки:%.4f м\n", P->high_plitka);
	fprintf(out, "\nПлощадь ванной комнаты с учётом проёмов %f м^2\n", V->s_with_openings);
	fprintf(out, "\nПлощадь ванной комнаты без учёта проёмов %f м^2\n", V->s_without_openings);
	fprintf(out, "\nНеобходимое кол-во материала для облицовки стен ванной комнаты площадью:%f с учётом проёмов = %.0f м^2\n",V->s_with_openings,ceil(V->col_vo_material));
	fprintf(out, "\nНеобходимое кол-во материала для облицовки стен ванной комнаты площадью:%f без учёта проёмов = %.0f м^2\n", V->s_without_openings, ceil(V->col_vo_material));
	fclose(out);
	return 0;
}
float klv_material(struct plitka* P, struct vanna* V, int hp) {
	if (hp == 2) {
		V->col_vo_material = (V->s_without_openings) / (P->shirina_plitka * P->high_plitka);
		return (V->s_without_openings) / (P->shirina_plitka * P->high_plitka);
	}
	else if (hp == 1) {
		V->col_vo_material = (V->s_with_openings) / (P->shirina_plitka * P->high_plitka);
		return (V->s_with_openings) / (P->shirina_plitka * P->high_plitka);
	}
}
