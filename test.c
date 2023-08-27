#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
            Lexeme *seeked = stack_seek(stack);
            while (stack->size > 0 && seeked->type != NUMBER && lex->type != UNDEFINED) {
                seeked = stack_seek(stack);
                if (check_priority(seeked->chr, lex->chr) == SUCCESS || lex->chr == ')') {
                    if (seeked->chr == '(' && lex->chr == ')') {    
                        stack_pop(stack);
                        break;
                    } else {
                        queue_push(*res, stack_pop(stack));
                    }
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
    stack_free(stack);
    return Status;
}


int main() {
  char *str0 = "((sin(30) * cos(sin(30))) * 200 + (10 * 50) ^ 2 - ((55 ^ 2) - cos(40) * 15) * log(50))";
//   char *str0 = "sn(100)";
//   char *str1 = "124/12";
  Queue *res_que = queue_init();
  if (str_to_polish_debug(str0, &res_que) == SUCCESS) {
    int Status = SUCCESS;
    print_queue(res_que);
    double res = calculate(res_que, 0, &Status);
    Status == SUCCESS ?  printf("res: %lf\n", res) : printf("error!\n");;
  } else {
    printf("error!\n");
  }
  queue_free(res_que);
//   if (str_to_polish_debug(str1, &res_que)) {
//     print_queue(res_que);
//   } else {
//     printf("error!\n");
//   }
//   res = calculate(res_que, 0);
//   printf("res: %lf\n", res);
  free(res_que);
}