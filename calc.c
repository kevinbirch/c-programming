#include <stdbool.h>  // for bool type
#include <stdio.h>    // for printf(), getchar(), ungetc(), etc
#include <ctype.h>    // for isspace(), isdigit(), etc
#include <stdlib.h>   // for strtod() and EXIT_SUCCESS
#include <string.h>   // for memset()

static const int MAX_DEPTH = 64;
static const int MAX_ATOM_LENGTH = 1024;

enum TOKEN
{
    ERROR,
    QUIT,
    EOL,
    WHITESPACE,
    NUMBER,
    STORE,
    LOAD,
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    POP,
    PEEK
};

typedef enum TOKEN token;

token get_token(char atom[]);
void push(double stack[], int *depth, double value);
double pop(double stack[], int *depth);
double peek(double stack[], int depth);
int read_number(char atom[]);
int read_integer(char atom[], int i);

int main(void)
{
    double registers[26];    
    double stack[MAX_DEPTH];
    int depth = 0;
    char atom[MAX_ATOM_LENGTH];
    bool finished = false;
    double a, b;

    for(int i = 0; i < 26; i++)
    {
        registers[i] = 0.0;
    }
    printf(">> ");
    while(!finished)
    {
        switch(get_token(atom))
        {
            case ERROR:
                break;
            case QUIT:
                finished = true;
                break;
            case EOL:
                printf(">> ");
                break;
            case WHITESPACE:
                break;
            case NUMBER:
            {
                char *endptr = atom;
                a = strtod(atom, &endptr);
                if(endptr == atom)
                {
                    fprintf(stderr, "error: %s is not a valid number.\n", atom);
                    break;
                }
                push(stack, &depth, a);
                break;
            }
            case STORE:
                break;
            case LOAD:
                break;
            case ADD:
                break;
            case SUBTRACT:
                break;
            case DIVIDE:
                break;
            case MULTIPLY:
                break;
            case POP:
                break;
            case PEEK:
                break;
        }
    }

    return EXIT_SUCCESS;
}

void push(double stack[], int *depth, double value)
{
}

double pop(double stack[], int *depth)
{
    return 0.0;
}

double peek(double stack[], int depth)
{
    return 0.0;
}

token get_token(char atom[])
{
    int reg;
    int c = getchar();

    if(EOF == c)
    {
        return QUIT;
    }
    if('\n' == c)
    {
        return EOL;
    }
    if(isspace(c))
    {
        return WHITESPACE;
    }
    if(isdigit(c) || '-' == c)
    {
        ungetc(c, stdin);
        if(-1 == read_number(atom))
        {
            return ERROR;
        }
        return NUMBER;
    }
    switch(c)
    {
        case 's':
        case '=':
            reg = getchar();
            if(!isalpha(reg))
            {
                fprintf(stderr, "error: store register operator `s` must be followed by a letter (a-z)\n");
                return ERROR;
            }
            atom[0] = tolower(reg);
            return STORE;
        case 'l':
        case ':':
            reg = getchar();
            if(!isalpha(reg))
            {
                fprintf(stderr, "error: load register operator `:` must be followed by a letter (a-z)\n");
                return ERROR;
            }
            atom[0] = tolower(reg);
            return LOAD;
        case '+':
            return ADD;
        case '-':
            return SUBTRACT;
        case '/':
            return DIVIDE;
        case '*':
            return MULTIPLY;
        case 'p':
        case '?':
            return PEEK;
        case 'P':
        case '!':
            return POP;
        default:
            fprintf(stderr, "error: the command '%c' is not supported.\n", c);
            return ERROR;
    }
}

#define CHECK_ATOM_LENGTH() if(MAX_ATOM_LENGTH <= i + 1)        \
    {                                                           \
        fprintf(stderr, "error: number too long.\n");           \
        return -1;                                              \
    }

int read_number(char atom[])
{
    int i = 0;
    int c;
    
    i = read_integer(atom, i);
    if('.' == (c = getchar()))
    {
        CHECK_ATOM_LENGTH();
        atom[i++] = '.';
        i = read_integer(atom, i);
    }
    else
    {
        ungetc(c, stdin);
    }
    c = getchar();
    if('e' == c || 'E' == c)
    {
        CHECK_ATOM_LENGTH();
        atom[i++] = 'e';
        i = read_integer(atom, i);
    }
    else
    {
        ungetc(c, stdin);
    }
    atom[i] = '\0';
    return i;
}

int read_integer(char atom[], int i)
{
    int c = getchar();
    if('-' == c || '+' == c)
    {
        CHECK_ATOM_LENGTH();
        atom[i++] = c;
    }
    else
    {
        ungetc(c, stdin);
    }
    for(c = getchar(); isdigit(c); c = getchar())
    {
        CHECK_ATOM_LENGTH();
        atom[i++] = c;
    }
    ungetc(c, stdin);

    return i;
}
