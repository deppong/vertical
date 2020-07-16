#include <stdio.h>

#define STACK_SIZE 1024
#define LOOP_SIZE 512
#define PROGRAM_SIZE 4096

struct Instructions {
    unsigned short command;
    unsigned short loop;
};

static struct Instructions program[PROGRAM_SIZE];
static unsigned short loop_stack[LOOP_SIZE];
static unsigned short loop_sp = 0;

int compile_vert(FILE *fp) {
    unsigned short i = 0, loop_ptr;
    int c;
    while ((c = getc(fp)) != EOF && i < PROGRAM_SIZE) {
        switch (c) {
            case 'l':  program[i].command = 1; break;
            case 'I':  program[i].command = 2; break;
            case '1':  program[i].command = 3; break;
            case '|':  program[i].command = 4; break;
            case ')':  program[i].command = 5; break;
            case 'T':  program[i].command = 6; break;
            case '/':  
                program[i].command = 7;
                if (loop_sp == LOOP_SIZE) {
                    return 1;
                }
                loop_stack[loop_sp++] = i;
                break;
            case '\\': 
                if (loop_sp == 0) {
                    return 1;
                }
                loop_ptr = loop_stack[--loop_sp];
                program[i].command = 8;
                program[i].loop = loop_ptr;
                program[loop_ptr].loop = i;
                break;
            case '!':  program[i].command = 9; break;
            case '(':  program[i].command = 10; break;
            case '[': program[i].command = 11; break;
            case ']': program[i].command = 12; break;
            default: i--; break;
        }
        i++;
    }
    if (loop_sp != 0 || i == STACK_SIZE) {
        return 1;
    }
    program[i].command = 0;
    return 0;
}

int run() {
    unsigned short stack[STACK_SIZE], i = 0;
    unsigned int sp = STACK_SIZE;
    unsigned int reg = 0, swp, swp1;
    while (--sp) { stack[sp] = 0; }
    while (program[i].command != 0 && sp < STACK_SIZE) {
        switch (program[i].command) {
            case 1:  stack[++sp] = reg; break;
            case 2:  stack[--sp]; break;
            case 3:  reg++; break;
            case 4:  reg--; break;
            case 5:  reg = 0; break;
            case 6:
                swp = stack[sp];
                sp--;
                swp1 = stack[sp];
                stack[sp++] = swp;
                stack[sp++] = swp1;
                sp--;
                break;
            case 7:  if (!stack[sp]) { i = program[i].loop; } break;
            case 8:  if (stack[sp]) { i = program[i].loop; } break;
            case 9:  putchar(stack[sp]); break;
            case 10:  reg = (unsigned int)getchar(); break;
            case 11: stack[sp]++; break;
            case 12: stack[sp]--; break;
            default: return 1;
        }
        i++;
    }
    return sp != STACK_SIZE ? 0 : 1;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    if (argc != 2 || (fp = fopen(argv[1], "r")) == NULL) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    int compiled = compile_vert(fp);
    fclose(fp);
    if (compiled == 0) {
        compiled = run();
    }
    if (compiled == 1) {
        puts("Your Vertical code failed to run!");
    }
    return compiled;
}
