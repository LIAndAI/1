#pragma warning(disable:4996);
#include <iostream>
#include <random>
#include <math.h>
#include <iomanip>
#include <stdio.h>
#include<stdlib.h>
float num[10000];
float random_number_create()//随机数生成
{
	std::random_device rd;
	return rd();
}

float random_number_size(int numbers, int nummax)//控制随机数大小
{
	int i;
	for (i = 0; i < numbers; i++)
	{
		num[i] = random_number_create();
		for (;;)
		{
			if (num[i] > nummax || num[i] < -nummax)
			{
				num[i] = num[i] / 10;
			}
			else
			{
				break;
			}
		}


	}
	return 0;
}

float without_brackets(int numbers, int point)//无括号四则运算
{
	int i;


	for (i = 0; i < numbers; i = i + 4)
	{
		if (point == 1)
		{
			printf("%.0f ", num[i]);
			if ((i + 1) % 2 == 0)
			{
				std::cout << "*";
			}
			else if (i % 3 == 0)
			{
				std::cout << "÷";
			}
			else if (i % 7 == 0)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << "+";
			}
			printf("%.0f", num[i + 1]);
			if (i % 6 == 0)
			{
				std::cout << "+";
			}
			else if (i % 5 == 0)
			{
				std::cout << "-";
			}
			else if ((i + 1) * 10 % 3 == 0)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << "÷";
			}

			printf("%.0f +%.0f=""\n", num[i + 2], num[i + 3]);
		}
		else if (point == 0)
		{
			printf("%.2f ", num[i]);
			if ((i + 1) % 2 == 0)
			{
				std::cout << "*";
			}
			else if (i % 3 == 0)
			{
				std::cout << "÷";
			}
			else if (i % 7 == 0)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << "+";
			}
			printf("%.2f", num[i + 1]);
			if (i % 6 == 0)
			{
				std::cout << "+";
			}
			else if (i % 5 == 0)
			{
				std::cout << "-";
			}
			else if ((i + 1) * 10 % 3 == 0)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << "÷";
			}

			printf("%.2f +%.2f=""\n", num[i + 2], num[i + 3]);

		}

	}



	return 0;
}
float on_brackets(int numbers, int point)//有括号的四则运算
{
	int i;


	for (i = 0; i < numbers; i = i + 4)
	{
		if (point == 1)
		{
			printf("%.0f ", num[i]);
			if ((i + 1) % 2 == 0)
			{
				std::cout << "*";
			}
			else if (i % 3 == 0)
			{
				std::cout << "÷";
			}
			else if (i % 7 == 0)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << "+";
			}
			printf("(%.0f", num[i + 1]);
			if (i % 6 == 0)
			{
				std::cout << "+";
			}
			else if (i % 5 == 0)
			{
				std::cout << "-";
			}
			else if ((i + 1) * 10 % 3 == 0)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << "÷";
			}

			printf("%.0f) +%.0f=""\n", num[i + 2], num[i + 3]);
		}
		else if (point == 0)
		{
			printf("%.2f ", num[i]);
			if ((i + 1) % 2 == 0)
			{
				std::cout << "*";
			}
			else if (i % 3 == 0)
			{
				std::cout << "÷";
			}
			else if (i % 7 == 0)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << "+";
			}
			printf("（%.2f", num[i + 1]);
			if (i % 6 == 0)
			{
				std::cout << "+";
			}
			else if (i % 5 == 0)
			{
				std::cout << "-";
			}
			else if ((i + 1) * 10 % 3 == 0)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << "÷";
			}

			printf("%.2f） +%.2f=""\n", num[i + 2], num[i + 3]);

		}

	}


	return 0;
}
float file_print1(int numbers, int point)//输出为文件
{
	int i;
	FILE* fp;
	fp = fopen("C:\\Users\\Administrator\\source\\repos\\四则运算\\杨强林.txt", "w");


	for (i = 0; i < numbers; i = i + 4)
	{
		if (point == 1)
		{
			fprintf(fp, "%.0f ", num[i]);
			if ((i + 1) % 2 == 0)
			{
				fprintf(fp, "*");
			}
			else if (i % 3 == 0)
			{
				fprintf(fp, "÷");
			}
			else if (i % 7 == 0)
			{
				fprintf(fp, "-");
			}
			else
			{
				fprintf(fp, "+");
			}
			fprintf(fp, "%.0f", num[i + 1]);
			if (i % 6 == 0)
			{
				fprintf(fp, "+");
			}
			else if (i % 5 == 0)
			{
				fprintf(fp, "-");
			}
			else if ((i + 1) * 10 % 3 == 0)
			{
				fprintf(fp, "*");
			}
			else
			{
				fprintf(fp, "÷");
			}

			fprintf(fp, "%.0f +%.0f=""\n", num[i + 2], num[i + 3]);
		}
		else if (point == 0)
		{
			fprintf(fp, "%.2f ", num[i]);
			if ((i + 1) % 2 == 0)
			{
				fprintf(fp, "*");
			}
			else if (i % 3 == 0)
			{
				fprintf(fp, "÷");
			}
			else if (i % 7 == 0)
			{
				fprintf(fp, "-");
			}
			else
			{
				fprintf(fp, "+");
			}
			fprintf(fp, "%.2f", num[i + 1]);
			if (i % 6 == 0)
			{
				fprintf(fp, "+");
			}
			else if (i % 5 == 0)
			{
				fprintf(fp, "-");
			}
			else if ((i + 1) * 10 % 3 == 0)
			{
				fprintf(fp, "*");
			}
			else
			{
				fprintf(fp, "÷");
			}

			fprintf(fp, "%.2f +%.2f=""\n", num[i + 2], num[i + 3]);

		}

	}
	fclose(fp);
	return 0;
}
float file_print2(int numbers, int point)//
{
	int i;
	FILE* fp;
	fp = fopen("C:\\Users\\Administrator\\source\\repos\\四则运算\\杨强林.txt", "w");


	for (i = 0; i < numbers; i = i + 4)
	{
		if (point == 1)
		{
			fprintf(fp, "%.0f ", num[i]);
			if ((i + 1) % 2 == 0)
			{
				fprintf(fp, "*");
			}
			else if (i % 3 == 0)
			{
				fprintf(fp, "÷");
			}
			else if (i % 7 == 0)
			{
				fprintf(fp, "-");
			}
			else
			{
				fprintf(fp, "+");
			}
			fprintf(fp, "(%.0f", num[i + 1]);
			if (i % 6 == 0)
			{
				fprintf(fp, "+");
			}
			else if (i % 5 == 0)
			{
				fprintf(fp, "-");
			}
			else if ((i + 1) * 10 % 3 == 0)
			{
				fprintf(fp, "*");
			}
			else
			{
				fprintf(fp, "÷");
			}

			fprintf(fp, "%.0f) +%.0f=""\n", num[i + 2], num[i + 3]);
		}
		else if (point == 0)
		{
			fprintf(fp, "%.2f ", num[i]);
			if ((i + 1) % 2 == 0)
			{
				fprintf(fp, "*");
			}
			else if (i % 3 == 0)
			{
				fprintf(fp, "÷");
			}
			else if (i % 7 == 0)
			{
				fprintf(fp, "-");
			}
			else
			{
				fprintf(fp, "+");
			}
			fprintf(fp, "(%.2f", num[i + 1]);
			if (i % 6 == 0)
			{
				fprintf(fp, "+");
			}
			else if (i % 5 == 0)
			{
				fprintf(fp, "-");
			}
			else if ((i + 1) * 10 % 3 == 0)
			{
				fprintf(fp, "*");
			}
			else
			{
				fprintf(fp, "÷");
			}

			fprintf(fp, "%.2f) +%.2f=""\n", num[i + 2], num[i + 3]);

		}

	}


	fclose(fp);
	return 0;
}
int main()
{
	int i = 0;
	int numbers = 0;
	int nummax = 0;
	int point = 0;
	int brackets = 0;
	int place = 0;
	int symbol = 0;
	printf("******************************************************\n");
	printf("         欢迎使用小学四则运算自动生成系统\n");
	printf("\n");
	printf("\n");
	printf("         请按照步骤输入相关要求出题\n");
	printf("*******************************************************\n");
	std::cout << "请输入出题数量:\n";
	std::cin >> numbers;
	std::cout << "请输入最大值:\n";
	std::cin >> nummax;
	std::cout << "是否有括号的运算，是请输入1，否输入2.\n";
	std::cin >> brackets;
	std::cout << "是否带小数的运算，是请输入0，否输入1.\n";
	std::cin >> point;
	std::cout << "需要打印到文件？需要请输入1,不需要请输入0\n";
	std::cin >> place;
	random_number_size(numbers * 4, nummax);
	if (brackets == 2)
	{
		without_brackets(numbers * 4, point);
		if (place == 1)
		{
			file_print1(numbers * 4, point);
		}
	}
	else if (brackets == 1)
	{
		on_brackets(numbers * 4, point);
		if (place == 1)
		{
			file_print2(numbers * 4, point);
		}
		return 0;
	}
	system("pause");
	return 0;
}