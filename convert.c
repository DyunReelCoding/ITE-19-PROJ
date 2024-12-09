#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function prototypes
int romanToDecimal(char roman[]);
long long performOperation(int a, int b, char op);
void processInputFile();
int getValue(char c);
void numberToWords(long long num, char *result);

// Main function
int main()
{
    processInputFile();
    return 0;
}

// Function to get the decimal value of a single Roman numeral character
int getValue(char c)
{
    switch (c)
    {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0;
    }
}

// Function to convert Roman numeral string to decimal integer
int romanToDecimal(char roman[])
{
    int total = 0;
    int prevValue = 0;
    int currValue;

    for (int i = strlen(roman) - 1; i >= 0; i--)
    {
        currValue = getValue(roman[i]);
        if (currValue < prevValue)
        {
            total -= currValue;
        }
        else
        {
            total += currValue;
        }
        prevValue = currValue;
    }
    return total;
}

// Function to perform arithmetic operations
long long performOperation(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return (long long)a + b;
    case '-':
        return (long long)a - b;
    case '*':
        return (long long)a * b;
    default:
        return 0;
    }
}

// Function to convert a number into words
void numberToWords(long long num, char *result)
{
    char *singleDigits[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    char *teenNumbers[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    char *tensMultiple[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char *thousands[] = {"", "Thousand", "Million", "Billion"};

    if (num == 0)
    {
        strcpy(result, "Zero");
        return;
    }

    char temp[1000] = "";

    if (num < 0)
    {
        sprintf(temp, "Negative ");
        num = -num;
    }

    if (num >= 1000000000)
    {
        int billionPart = num / 1000000000;
        num %= 1000000000;
        sprintf(temp + strlen(temp), "%s Billion ", singleDigits[billionPart]);
    }
    if (num >= 1000000)
    {
        int millionPart = num / 1000000;
        num %= 1000000;
        numberToWords(millionPart, temp + strlen(temp));
        sprintf(temp + strlen(temp), " Million ");
    }
    if (num >= 1000)
    {
        int thousandPart = num / 1000;
        num %= 1000;
        numberToWords(thousandPart, temp + strlen(temp));
        sprintf(temp + strlen(temp), " Thousand ");
    }
    if (num >= 100)
    {
        int hundredPart = num / 100;
        num %= 100;
        sprintf(temp + strlen(temp), "%s Hundred ", singleDigits[hundredPart]);
    }
    if (num >= 20)
    {
        int tenPart = num / 10;
        num %= 10;
        sprintf(temp + strlen(temp), "%s ", tensMultiple[tenPart]);
    }
    else if (num >= 10)
    {
        sprintf(temp + strlen(temp), "%s ", teenNumbers[num - 10]);
        num = 0;
    }
    if (num > 0 && num < 10)
    {
        sprintf(temp + strlen(temp), "%s", singleDigits[num]);
    }

    // Remove trailing space
    if (temp[strlen(temp) - 1] == ' ')
    {
        temp[strlen(temp) - 1] = '\0';
    }

    strcpy(result, temp);
}

// Function to process input file and write to output file
void processInputFile()
{
    FILE *inputFile = fopen("Input.txt", "r");
    FILE *outputFile = fopen("Output.txt", "w");
    char line[256];
    char roman1[20], roman2[20], op;
    char resultStr[100];

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("File opened successfully.\n");

    while (fgets(line, sizeof(line), inputFile))
    {
        printf("Processing line: %s", line);
        if (sscanf(line, "%s %c %s", roman1, &op, roman2) == 3)
        {
            printf("Parsed: %s %c %s\n", roman1, op, roman2);
            int num1 = romanToDecimal(roman1);
            int num2 = romanToDecimal(roman2);
            printf("Decimal conversion: %d %c %d\n", num1, op, num2);
            long long result = performOperation(num1, num2, op);
            printf("Operation result: %lld\n", result);
            numberToWords(result, resultStr);
            fprintf(outputFile, "%s\n", resultStr);
            printf("Result: %s\n", resultStr);
        }
        else
        {
            printf("Failed to parse line: %s\n", line);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("File processed and closed successfully.\n");
}
