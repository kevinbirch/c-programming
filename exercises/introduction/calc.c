#include <stdio.h>    // for printf(), getchar(), ungetc(), etc
#include <ctype.h>    // for isspace(), isdigit(), etc
#include <stdlib.h>   // for strtod() and EXIT_SUCCESS
#include <string.h>   // for strlen(), etc

#define MAX_REGISTERS 8
#define MAX_DEPTH 64

static const char MAX_REGISTER_IDENTIFER = 'a'+MAX_REGISTERS-1;
static const int  MAX_INPUT_LENGTH = 1024;
static const int  MAX_EXRESSION_LENGTH = 64;

enum token_kind_e
{
    ERROR,
    END_OF_INPUT,
    WHITESPACE,
    NUMBER,
    SYMBOL,
    QUOTE,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EXCLAMATION,
};

typedef enum token_kind_e TokenKind;

struct token_s
{
    TokenKind kind;
    int       offset;
    int       length;
};

typedef struct token_s Token;

enum opcode_e
{
    NOOP,
    LOAD,
    STORE,
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    PUSH,
    POP,
    DROP,
    ROTATE,
    DUPLICATE,
};

typedef enum opcode_e Opcode;

struct instruction_s
{
    Opcode opcode;
    union
    {
        double operand;
        int    reference;
    };
};

typedef struct instruction_s Instruction;

struct machine_s
{
    double registers[MAX_REGISTERS];

    struct
    {
        double entries[MAX_DEPTH];
        int    top;
    } stack;
};

typedef struct machine_s Machine;

static int push(double stack[], int *depth, double value)
{
    return 0;
}

static int pop(double stack[], int *depth, double *value)
{
    return 0;
}

static void drop(double stack[], int *depth)
{
}

static void view(Machine *machine)
{
    printf("registers: ");
    for(int i = 0; i < MAX_REGISTERS; i++)
    {
        printf("[%c]: %.8g ", 'a'+i, machine->registers[i]);
    }
    printf("\n");
    if(0 == machine->stack.top)
    {
        printf("stack: empty\n");
        return;
    }

    printf("stack: ");
    for(int i = 0; i < machine->stack.top; i++)
    {
        printf("%.8g ", machine->stack.entries[i]);
    }
    printf("\n");
}

static void evaluate(Machine *machine, Instruction *expression, int length)
{
    double a, b = 0.0;
    for(int i = 0; i < length; i++)
    {
        Instruction *instr = &expression[i];
        switch(instr->opcode)
        {
            case LOAD:
                if(push(machine->stack.entries, &machine->stack.top, machine->registers[instr->reference]))
                {
                    return;
                }
                break;
            case STORE:
                if(pop(machine->stack.entries, &machine->stack.top, &a))
                {
                    return;
                }
                machine->registers[instr->reference] = a;
                break;
            case ADD:
                if(pop(machine->stack.entries, &machine->stack.top, &a))
                {
                    return;
                }
                if(pop(machine->stack.entries, &machine->stack.top, &b))
                {
                    push(machine->stack.entries, &machine->stack.top, a);
                    return;
                }
                if(push(machine->stack.entries, &machine->stack.top, b + a))
                {
                    push(machine->stack.entries, &machine->stack.top, b);
                    return;
                }
                break;
            case SUBTRACT:
                if(pop(machine->stack.entries, &machine->stack.top, &a))
                {
                    return;
                }
                if(pop(machine->stack.entries, &machine->stack.top, &b))
                {
                    push(machine->stack.entries, &machine->stack.top, a);
                    return;
                }
                if(push(machine->stack.entries, &machine->stack.top, b - a))
                {
                    push(machine->stack.entries, &machine->stack.top, b);
                    return;
                }
                break;
            case MULTIPLY:
                if(pop(machine->stack.entries, &machine->stack.top, &a))
                {
                    return;
                }
                if(pop(machine->stack.entries, &machine->stack.top, &b))
                {
                    push(machine->stack.entries, &machine->stack.top, a);
                    return;
                }
                if(push(machine->stack.entries, &machine->stack.top, b * a))
                {
                    push(machine->stack.entries, &machine->stack.top, b);
                    return;
                }
                break;
            case DIVIDE:
                if(pop(machine->stack.entries, &machine->stack.top, &a))
                {
                    return;
                }
                if(pop(machine->stack.entries, &machine->stack.top, &b))
                {
                    push(machine->stack.entries, &machine->stack.top, a);
                    return;
                }
                if(push(machine->stack.entries, &machine->stack.top, b / a))
                {
                    push(machine->stack.entries, &machine->stack.top, b);
                    return;
                }
                break;
            case DROP:
                drop(machine->stack.entries, &machine->stack.top);
                break;
            case PUSH:
                if(push(machine->stack.entries, &machine->stack.top, instr->operand))
                {
                    return;
                }
                break;
            case POP:
                fprintf(stderr, "error: unsupported opcode POP.\n", instr->opcode);
                return;
            case ROTATE:
                fprintf(stderr, "error: unsupported opcode ROTATE.\n", instr->opcode);
                return;
            case DUPLICATE:
                fprintf(stderr, "error: unsupported opcode DUPLICATE.\n", instr->opcode);
                return;
            default:
                fprintf(stderr, "error: illegal opcode: %d.\n", instr->opcode);
                return;
        }
    }
}

static int match_integer(char *input)
{
    int length = 0;

    if('-' == input[length] || '+' == input[length])
    {
        length++;
    }

    while(isdigit(input[length]))
    {
        length++;
    }

    return length;
}

static int match_number(char *input)
{
    int length = match_integer(input);

    if('.' == input[length])
    {
        length++;
        length += match_integer(input+length);

        if('e' == input[length] || 'E' == input[length])
        {
            length++;
            length += match_integer(input+length);
        }
    }

    return length;
}

static void next_token(char *input, Token *token)
{
    token->length = 1;

    if(isspace(*input))
    {
        token->kind = WHITESPACE;

        while(isspace(*(input+token->length+1)))
        {
            token->length++;
        }

        return;
    }

    if(isdigit(*input))
    {
        token->kind = NUMBER;
        token->length = match_number(input);

        return;
    }

    if(islower(*input))
    {
        token->kind = SYMBOL;

        return;
    }

    switch(*input)
    {
        case '\0':
            token->kind = END_OF_INPUT;
            break;
        case '+':
            if(isdigit(*(input+1)))
            {
                token->kind = NUMBER;
                token->length = match_number(input);
                break;
            }

            token->kind = PLUS;
            break;
        case '-':
            if(isdigit(*(input+1)))
            {
                token->kind = NUMBER;
                token->length = match_number(input);
                break;
            }

            token->kind = MINUS;
            break;
        case '*':
            token->kind = STAR;
            break;
        case '/':
            token->kind = SLASH;
            break;
        case '`':
            token->kind = QUOTE;
            break;
        case '!':
            token->kind = EXCLAMATION;
            break;
        default:
            token->kind = ERROR;
            fprintf(stderr, "error: unexpected '%c'.\n", *input);
            break;
    }
}

static int parse(char *input, Instruction *expression, int limit)
{
    size_t input_length = strlen(input);
    int count = 0;

    for(int i = 0; i < input_length;)
    {
        if(count == limit)
        {
            fprintf(stderr, "error: expression too long.\n");
            return -1;
        }

        Token token;
        token.offset = i;

        next_token(input+i, &token);

        Instruction instr;
        instr.opcode = NOOP;

        switch(token.kind)
        {
            case ERROR:
                return -1;
            case END_OF_INPUT:
                break;
            case WHITESPACE:
                break;
            case NUMBER:
                instr.opcode = PUSH;
                instr.operand = strtod(input+i, NULL);
                break;
            case SYMBOL:
            {
                Token next;
                next_token(input+1, &next);
                if(WHITESPACE != next.kind && END_OF_INPUT != next.kind)
                {
                    fprintf(stderr, "error: register reference must be single lowercase letter ('a'-'%c').\n", MAX_REGISTER_IDENTIFER);
                    return -1;
                }
                if('a' > *input || MAX_REGISTER_IDENTIFER < *input)
                {
                    fprintf(stderr, "error: register reference must be single lowercase letter ('a'-'%c').\n", MAX_REGISTER_IDENTIFER);
                    return -1;
                }

                instr.opcode = LOAD;
                instr.reference = *input - 'a';
                break;
            }
            case QUOTE:
            {
                Token next;
                next_token(input+1, &next);
                if(SYMBOL != next.kind)
                {
                    fprintf(stderr, "error: quote must be followed by a register reference.\n");
                    return -1;
                }
                if('a' > *(input+1) || MAX_REGISTER_IDENTIFER < *(input+1))
                {
                    fprintf(stderr, "error: register reference must be single lowercase letter ('a'-'%c').\n", MAX_REGISTER_IDENTIFER);
                    return -1;
                }

                token.length++;
                instr.opcode = STORE;
                instr.reference = *(input+1) - 'a';
                break;
            }
            case PLUS:
                instr.opcode = ADD;
                break;
            case MINUS:
                instr.opcode = SUBTRACT;
                break;
            case STAR:
                instr.opcode = MULTIPLY;
                break;
            case SLASH:
                instr.opcode = DIVIDE;
                break;
            case EXCLAMATION:
                instr.opcode = DROP;
                break;
            default:
                fprintf(stderr, "error: illegal token: %d.\n", token.kind);
                return -1;
        }

        i += token.length;
        if(NOOP != instr.opcode)
        {
            expression[count++] = instr;
        }
    }

    return count;
}

static int get_input(char buf[], int limit)
{
    printf(">> ");
    fflush(stdout);

    if(NULL == fgets(buf, limit, stdin))
    {
        if(feof(stdin))
        {
            return 2;
        }
        return 1;
    }

    size_t len = strlen(buf);
    if('\n' != buf[len-1])
    {
        fprintf(stderr, "error: input too long.\n");
        return 1;
    }
    buf[len-1] = '\0';

    return 0;
}

int main(void)
{
    char        input[MAX_INPUT_LENGTH];
    Instruction expression[MAX_EXRESSION_LENGTH];
    Machine     machine;

    for(int i = 0; i < MAX_REGISTERS; i++)
    {
        machine.registers[i] = 0.0;
    }

    for(int i = 0; i < MAX_DEPTH; i++)
    {
        machine.stack.entries[i] = 0.0;
    }
    machine.stack.top = 0;

    while(1)
    {
        int result = get_input(input, MAX_INPUT_LENGTH);
        if(2 == result)
        {
            printf("\nbye!\n");
            break;
        }
        else if(result)
        {
            continue;
        }

        int expression_length = parse(input, expression, MAX_EXRESSION_LENGTH);
        if(-1 == expression_length)
        {
            continue;
        }

        evaluate(&machine, expression, expression_length);
        view(&machine);
    }

    return EXIT_SUCCESS;
}
