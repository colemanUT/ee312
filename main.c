#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* crossword;
int rows;
int columns;

#include "symmetry.c"
#include "match.c"
#include "max_len.c"

void print_crossword(){
  for(int r = 0; r < rows; r++){
    for(int c = 0; c < columns; c++){
      putchar(crossword[r*columns+c]);
    }
    putchar('\n');
  }
}

void load_file(const char* filename){
  FILE* file;
  file = fopen(filename, "r");
  fscanf(file, "%d %d", &rows, &columns);

  crossword = (char*) malloc(rows*columns*sizeof(char));

  for(int r = 0; r < rows; r++){
    char str[columns+1];
    fscanf(file, "%s", &str);
    for(int c = 0; c < columns; c++){
      crossword[r*columns + c] = str[c];
    }
  }

  fclose(file);
}

void run_tests(){
  int num_tests = 2;

  const char* test_names[] = {
    "test1.txt", "test2.txt"
  };

  const char* test_dicts[] = {
    "abc\ndef\na", "c\nd"
  };

  int test_results[][3] = {
    {5,6,0},
    {1,4,1}
  };

  for(int i = 0; i < num_tests; i++){
    load_file(test_names[i]);

    int passed;

    passed = (find_max_length() == test_results[i][0]);
    printf(" * find_max_length() for %s - %s\n", test_names[i], passed ? "PASSED" : "FAILED");

    char dict[10];
    strcpy(dict, test_dicts[i]);
    passed = (find_words_in_dict(dict) == test_results[i][1]);
    printf(" * find_words_in_dict() for %s - %s\n", test_names[i], passed ? "PASSED" : "FAILED");

    passed = (check_symmetric() == test_results[i][2]);
    printf(" * check_symmetric() for %s - %s\n", test_names[i], passed ? "PASSED" : "FAILED");

    free(crossword);
  }

}

int main(){
  char filename[20];
  printf("Enter the name of a file or \"test\" to run tests\n");
  scanf("%s", &filename);

  if(strcmp(filename, "test") == 0){
    run_tests();
    exit(0);
  }

  load_file(filename);

  printf("\n----------------\n");
  print_crossword();
  printf("----------------\n");
  while(1){
    printf("\nOptions (Enter a number):\n0 => Exit\n1 => Find max vertical word length\n2 => Find word positions\n3 => Check for symmetry\n");

    int input;
    scanf("%d", &input);
    printf("Your selection = %d\n\n", input);
    switch(input){
      case 0:
        free(crossword);
        exit(0);
      case 1:
        find_max_length();
        break;
      case 2:
        find_words_from_user();
        break;
      case 3:
        check_symmetric();
        break;
      default:
        break;
    }
  }


  return 0;
}
