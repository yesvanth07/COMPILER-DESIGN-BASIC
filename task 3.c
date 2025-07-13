
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

// Check if word is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }
    return 0;
}

// Check if char is a symbol
int isSymbol(char ch) {
    char symbols[] = {';', '{', '}', '(', ')', '[', ']', ','};
    for (int i = 0; i < sizeof(symbols); i++) {
        if (ch == symbols[i]) return 1;
    }
    return 0;
}

// Check if char is operator
int isOperator(char ch) {
    char operators[] = {'+', '-', '*', '/', '=', '<', '>', '%'};
    for (int i = 0; i < sizeof(operators); i++) {
        if (ch == operators[i]) return 1;
    }
    return 0;
}

int main() {
    FILE *fp = fopen("code.c", "r");
    if (!fp) {
        printf("Cannot open code.c\n");
        return 1;
    }

    char ch, word[50];
    int i;

    printf("Lexical Analysis Result:\n\n");

    while ((ch = fgetc(fp)) != EOF) {
        // Skip whitespace
        if (isspace(ch)) continue;

        // Word: keyword, identifier or number
        if (isalpha(ch)) {
            i = 0;
            word[i++] = ch;
            while (isalnum(ch = fgetc(fp))) {
                word[i++] = ch;
            }
            word[i] = '\0';
            ungetc(ch, fp);

            if (isKeyword(word))
                printf("Keyword: %s\n", word);
            else
                printf("Identifier: %s\n", word);
        }
        else if (isdigit(ch)) {
            i = 0;
            word[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                word[i++] = ch;
            }
            word[i] = '\0';
            ungetc(ch, fp);
            printf("Number: %s\n", word);
        }
        else if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
        }
        else if (isSymbol(ch)) {
            printf("Symbol: %c\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
