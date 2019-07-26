
#include "Cod.h"
#include "KWnd.h"
#include <windows.h>

void getSecondReck(int &top, int &left, int &right, int &bottom)

{
	
	top = 50;
	left = 50;
	right = 250;
	bottom = 150;	
}
// Функция преобразования строки в число

int StrToInt(char *s)
{
	int temp = 0; // число
	int i = 0;
	int sign = 0; // знак числа 0- положительное, 1 - отрицательное
	if (s[i] == '-')
	{
		sign = 1;
		i++;
	}
	while (s[i] >= 0x30 && s[i] <= 0x39)
	{
		temp = temp + (s[i] & 0x0F);
		temp = temp * 10;
		i++;
	}
	temp = temp / 10;
	if (sign == 1)
		temp = -temp;
	return(temp);
}

// Функция преобразования числа в строку

char* IntToStr(int n) 
{
	char s[40], t, *temp;
	int i, k;
	int sign = 0;
	i = 0;
	k = n;
	if (k < 0)
	{
		sign = 1;
		k = -k;
	}
	do {
		t = k % 10;
		k = k / 10;
		s[i] = t | 0x30;
		i++;
	} while (k > 0);
	if (sign == 1)
	{
		s[i] = '-';
		i++;
	}
	temp = new char[i];
	k = 0;
	i--;
	while (i >= 0) {
		temp[k] = s[i];
		i--; k++;
	}
	temp[k] = '\0';
	return(temp);
}

char* DoubleToStr(double n, int tolerance)
{
	char s[40], t, *temp;
	double num;
	int i, j;
	i = tolerance;
	j = 0;
	num = n;
	if (num < 0) // определяем знак числа
	{
		num = -num;
		s[j] = '-';
		j++;
	}
	do { // преобразуем к нормированной форме (если не меньше 1)
		num = num / 10;
		i++;
	} while ((int)num > 0);
	num = num * 10;
	while (i > 0)
	{
		t = (int)num; // выделяем цифру, соответствующую целой части
		s[j] = t | 0x30;
		i--; j++;
		if (i == tolerance) { // определяем положение десятичного разделителя
			s[j] = '.';
			j++;
		}
		num = num -(double)t; // вычитаем из числа целую часть
		num = num * 10; // переходим к следующему разряду
	}
	s[j] = '\0';
	j++;
	temp = new char[j]; // выделяем память под возвращаемую строку
	for (i = 0; i < j; i++) // формируем возвращаемую строку
		temp[i] = s[i];
	return(temp);
}

// Функция для прорисовки пропила
BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	POINT pt;
	MoveToEx(hdc, x1, y1, &pt);
	return LineTo(hdc, x2, y2);
}


