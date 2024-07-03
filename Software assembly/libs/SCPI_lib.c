/*
 * SCPI_lib.c
 *
 *  Created on: Apr 8, 2024
 *      Author: kuban
 */

#include "SCPI_Lib.h"

char* paramsList[3] = { "OFF", "ON", "? " };
int paramsLength = 3;

Class* classList;
//int classLength;
//int defaultClassIndex;
int classLength = 0;
int defaultClassIndex = -1;

void ReformatString(char* chararr, int arrMaxSize)
{
	for (int i = 0; i < arrMaxSize && chararr[i] != '\0'; i++)	// format into proper string so stdlib.h can be used
	{
		if (chararr[i] == '\r' || chararr[i] == '\n')
		{
			chararr[i] = '\0';
			return;
		}
	}
}

Subword* generateSubwordn(char* subcommand, int length, Class* class)
{
	Subword finalSubword = { .type = params, .integerParam = 0, .otherParam = NULL, .paramType = 0 };

	for (int i = 0; i < class->functionsLength; i++)
	{
		if (!strncmp(subcommand, class->functions[i].name, length))
		{
			finalSubword.type = function;
			finalSubword.functionIndex = i;
			return &finalSubword;
		}
	}

	for (int i = 0; i < paramsLength; i++)
	{
		if (!strncmp(subcommand, paramsList[i], length))
		{
			finalSubword.paramType = (ParamTypes)i;
			return &finalSubword;
		}
	}

	int n;
	if ((n = atoi(subcommand)))
	{
		finalSubword.paramType = INT_P;
		finalSubword.integerParam = n;
		return &finalSubword;
	}

	finalSubword.paramType = OTHER_P;
	finalSubword.otherParam = (char*)calloc(length + 1, sizeof(char));
	if (finalSubword.otherParam != NULL) strncpy(finalSubword.otherParam, subcommand, length);
	return &finalSubword;
}

int findClassIndex(char* subcommand, int length)
{
	for (int i = 0; i < classLength; i++)
	{
		if (!strncmp(subcommand, classList[i].name, length))
		{
			return i;
		}
	}

	return defaultClassIndex;
}

Word* generateWordDirect(char* command)
{
	Word finalWord = { .address = -1, .subwords = NULL, .subwordsCount = 0 };

	char* currSymbol = command;
	int intermediateLength = 0;
	Class* currentClass = classList;
	int currentClassIndex = defaultClassIndex;

	int isLast = 0;
	int firstSubWord = 1;

	while (!isLast)
	{
		isLast = *currSymbol == '\0';
		switch (*currSymbol)
		{
		case ':':
		case '\0':
		case '?':

			if (intermediateLength == 0) break;
			if (finalWord.address == -1)
			{
				finalWord.address = atoi(currSymbol - intermediateLength);
			}

			else
			{
				if (firstSubWord)
				{
					int index = findClassIndex(currSymbol - intermediateLength, intermediateLength);
					currentClass = &classList[index];
					finalWord.classIndex = index;
					currentClassIndex = index;
					firstSubWord = 0;
					if (currentClassIndex != defaultClassIndex)
					{
						intermediateLength = 0;
						break;
					}
				}

				finalWord.subwordsCount++;
				Subword* intermediate = (Subword*)realloc(finalWord.subwords, finalWord.subwordsCount * sizeof(Subword));
				if (intermediate != NULL)
				{
					finalWord.subwords = intermediate;																				///??????
					finalWord.subwords[finalWord.subwordsCount - 1] = *generateSubwordn(currSymbol - intermediateLength, intermediateLength, currentClass);
				}
			}

			intermediateLength = 0;

			break;

		default:
			intermediateLength++;
			break;

		}

		if (*currSymbol == '?')
		{
			finalWord.subwordsCount++;
			Subword* intermediate = (Subword*)realloc(finalWord.subwords, finalWord.subwordsCount * sizeof(Subword));
			if (intermediate != NULL)
			{
				finalWord.subwords = intermediate;																						///??????
				finalWord.subwords[finalWord.subwordsCount - 1] = *generateSubwordn("?", 1, currentClass);
			}
		}

		currSymbol += !isLast;
	}

	return &finalWord;
}

void executeWord(Word* word)
{
	if (word->subwordsCount < 1) return;
	if (word->subwords == NULL) return;
	if (word->subwords[0].type != function) return;
	int classIndex = word->classIndex;
	int functionIndex = word->subwords[0].functionIndex;
	classList[classIndex].functions[functionIndex].run(word->subwords + 1, word->subwordsCount - 1);
}

void addFunction(char* name, void (*func)(Subword*, int), Class* class)
{
	if(defaultClassIndex < 0)
	{
		classList = (Class*)realloc(classList, (classLength + 1) * sizeof(Class));
		int index = classLength;
		classList[index].functions = NULL;
		classList[index].functionsLength = 0;
		classList[index].name = "default";
		defaultClassIndex = index;
		classLength++;
		class = &classList[index];
	}

	class->functionsLength++;
	int length = class->functionsLength;
	Function newFunc = { .name = name, .run = func };
	class->functions = (Function*)realloc(class->functions, length * sizeof(Function));
	class->functions[length - 1] = newFunc;
}

void addEmptyClass(char* name, int isDefault)
{
	classList = (Class*)realloc(classList, (classLength + 1) * sizeof(Class));
	classList[classLength].name = name;
	classList[classLength].functions = NULL;
	classList[classLength].functionsLength = 0;
	if (isDefault) defaultClassIndex = classLength;
	classLength++;
}

void addClass(Class* class, int isDefault)
{
	classList = (Class*)realloc(classList, (classLength + 1) * sizeof(Class));
	classList[classLength] = *class;
	if (isDefault) defaultClassIndex = classLength;
	classLength++;
}
