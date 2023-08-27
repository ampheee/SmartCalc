#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "queue.h"
#include "parse.h"
#include "arithmetics.h"

int str_to_polish_debug(char *str, Queue **res) {
    Stack *stack = stack_init();
    int Status = SUCCESS;
    size_t len = strlen(str);
    double result = 1;
    while (*str && Status == SUCCESS) {
        remove_spaces(&str);
        Lexeme *lex = (Lexeme *) calloc (1, sizeof(Lexeme));
        lex->type = UNDEFINED;
        if (parse_num(&str, &result) == SUCCESS) {
            lex->type = NUMBER, lex->num = result;
            queue_push(*res, lex);
        } else if (parse_func(&str, &lex->chr) == SUCCESS) {
            lex->type = FUNCTION;
            stack_push(stack, lex);
        } else {
            if (parse_operator(&str, &lex->chr) == SUCCESS) lex->type = OPERATOR;
            else if (parse_bracket(&str, &lex->chr) == SUCCESS) lex->type = BRACKET;
            if (lex->chr == ')' && stack->size <= 0) {
                Status = FAIL;
                break;
            }
            // ok 
            Lexeme *seeked = stack_seek(stack);
            while (stack->size > 0 && seeked->type != NUMBER && lex->type != UNDEFINED) {
                //ok
                //if close bracket - queue_push while open bracket.
                //else if non bracket - check_priority.
                seeked = stack_seek(stack);
                if (check_priority(seeked->chr, lex->chr) != FAIL) {
                    if (seeked->chr == '(') {
                        stack_pop(stack);
                        break;
                    } else {
                        queue_push(*res, stack_pop(stack));
                    }
                    // lex->type == BRACKET ? (lex->chr = seeked->chr) : 0;
                } else {
                    break;
                }
            }
            lex->type == UNDEFINED ? Status = FAIL : lex->chr != ')' ? stack_push(stack, lex) : 0;
        } 
        if (lex->type == UNDEFINED || Status == FAIL) free(lex);
    }
    while (stack->size > 0) {
        queue_push(*res, stack_pop(stack));
    }
    free(stack);
    return Status;
}


int main() {
//   char *str = "(sin(30) * cos(sin(30)))*200 + (10 * 50) ^ 2";
char  *str = "(sin(30) - cos(sin(60))) * 200";
  Queue *res_que = queue_init();
  if (str_to_polish_debug(str, &res_que)) {
    print_queue(res_que);
  } else {
    printf("error!\n");
  }
  double res = calculate(res_que, 0);
  printf("res: %lf\n", res);
  
}