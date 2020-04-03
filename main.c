#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <conio.h> 
#include <stdlib.h>
#include <locale.h>



int read(FILE* stream, int* count_keys, int* keys_C, int* keys_L, int* keys_W, char name[], int* count_file, int* final, int* Total_size, int* Total_line, int* Total_word)
{
	int c;
	int  inWord = 0, wordsCount = 0;
	int i = 0;
	int enter = 1;
	int size = 50;
	char* str = (char*)malloc(size);
	if (!(*str))
		return -1;
	for (int i = 0;i < size;i++)
	{
		str[i] = '0';
	}
	while ((c = fgetc(stream)) != EOF && c != 26)
	{
		if (i == size)
		{
			char* l = realloc(str, size += 50);
			if (!l)
				return -1;
			str = l;
		}
		str[i] = (char)c;
		if (str[i] == '\n')
			enter++;
		if (isspace(c) || ispunct(c))
		{
			if (inWord)
			{
				wordsCount += 1;
				inWord = 0;
			}
		}
		else
			inWord = 1;
		i++;
	}
	wordsCount += inWord;
	if (*count_keys == 0)
		printf("%s:\tРазмер: %i\t Кол-во строк: %i\t Кол-во слов: %i\n", name, i, enter, wordsCount);
	if (*count_keys == 1)
	{
		if (*keys_C == 1)
			printf("%s:\tРазмер: %i\n", name, i);
		if (*keys_L == 1)
			printf("%s:\tКол-во строк: %i\n", name, enter);
		if (*keys_W == 1)
			printf("%s:\tКол-во слов: %i\n", name, wordsCount);
	}
	if (*count_keys == 2)
	{
		printf("%s: \t ", name);
		if (*keys_C == 1)
			printf("Размер: %i \t ", i);
		if (*keys_L == 1 && *keys_C == 1)
			printf("Кол-во строк: %i \t \n", enter);
		if (*keys_L == 1 && *keys_C != 1)
			printf("Кол-во строк: %i \t ", enter);
		if (*keys_W == 1)
			printf("Кол-во слов: %i \t \n", wordsCount);
	}
	if (*count_keys == 3)
		printf("%s:\tРазмер: %i\tКол-во строк: %i\tКол-во слов: %i\n", name, i, enter, wordsCount);
	if (*count_file > 1)
	{
		*Total_size += i;
		*Total_word += wordsCount;
		*Total_line += enter;
		if (*final) {
			if (*count_keys == 0)
				printf("\tРазмер: %i\t Кол-во строк: %i\t Кол-во слов: %i", *Total_size, *Total_line, *Total_word);
			if (*count_keys == 1)
			{
				if (*keys_C == 1)
					printf("\tОбщий размер: %i", *Total_size);
				if (*keys_L == 1)
					printf("\tОбщее кол-во строк: %i", *Total_line);
				if (*keys_W == 1)
					printf("\tОбщее кол-во слов: %i", *Total_word);
			}
			if (*count_keys == 2)
			{
				if (*keys_C == 1)
					printf("Общий размер: %i \t ", *Total_size);
				if (*keys_L == 1 && *keys_C == 1)
					printf("Общее кол-во строк: %i \t ", *Total_line);
				if (*keys_L == 1 && *keys_C != 1)
					printf("Общее кол-во строк: %i \t ", *Total_line);
				if (*keys_W == 1)
					printf("Общее кол-во слов: %i \t ", *Total_word);
			}
			if (*count_keys == 3)
				printf(" \t Общий размер: %i \t Общее кол-во строк: %i \t Общее кол-во слов: %i", *Total_size, *Total_line, *Total_word);
		}
	}

	free(str);
	return 0;
}






int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");
	FILE* stream = stdin;
	int b = 0, d = 0;
	int count_file = 0, position_C = 0, position_L = 0, position_W = 0;
	char file[1000] = "stdin";
	int keys_C = 0, keys_L = 0, keys_W = 0;
	int Total_size = 0, Total_line = 0, Total_word = 0;
	int final = 0;
	char c[] = "-C", l[] = "-L", w[] = "-W";
	if (argc > 1) {
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(c, argv[i]) == 0)
			{
				keys_C = 1;
				position_C = i;
				b++;
			}
			if (strcmp(l, argv[i]) == 0)
			{
				keys_L = 1;
				position_L = i;
				b++;
			}
			if (strcmp(w, argv[i]) == 0)
			{
				keys_W = 1;
				position_W = i;
				b++;
			}
		}
		count_file = argc - 1 - b;
		for (int i = 1; i < argc; i++)
		{
			if (position_C != i && position_L != i && position_W != i)
			{
				d++;
				if (d == count_file)
					final = 1;
				if (fopen_s(&stream, argv[i], "r"))
				{
					printf("Не удалось открыть файл: %s\n", argv[i]);
					continue;
				}
				read(stream, &b, &keys_C, &keys_L, &keys_W, argv[i], &count_file, &final, &Total_size, &Total_line, &Total_word);
			}
		}
	}
	if (count_file == 0)
	{
		read(stream, &b, &keys_C, &keys_L, &keys_W, argv[1], &count_file, &final, &Total_size, &Total_line, &Total_word);
	}
	return 0;
}
