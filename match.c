//returns column as string
char* get_column(char* str, int column){
  for(int r = 0; r < rows; r++){
    str[r] = crossword[r*columns + column];
  }
  str[rows] = 0;
  return str;
}

//returns row as string
char* get_row(char* str, int row){
  for(int c = 0; c < columns; c++){
    str[c] = crossword[row*columns + c];
  }
  str[columns]  = 0;
  return str;
}

//RETURNS 1 IF WORD FOUND IN DICT, 0 OTHERWISE (copied from Project 1)
int is_misspelled(char word[], char dictionary[]){
	int last_word = 0;
	int index = 0;
	while(1){
		char c = dictionary[index];
		if(c == '\n' || c == 0){
			dictionary[index] = 0;

			int cmp = strcmp(word, &dictionary[last_word]);

			dictionary[index] = c;
			if(cmp==0) return 0;
			last_word = index + 1;
		}
		if(c==0) return 1;
		index++;
	}

}

//FINDS OCCURRENCES OF STRINGS AND CHECKS AGAINST DICTIONARY, RETURNS NUMBER OF MATCHES
int string_occurences(char str[], char dictionary[], int is_column, int row_or_column_index){
  int r = 0;
  int index = 0;
  int last_word = -1;
  while(1){
    char el = str[index];
    int word_char = !(el == '*' || el == 0);
    if(last_word == -1){
      //if entering word
      if(word_char){
        last_word = index;
      }
    }else{
      //if exiting word
      if(!word_char){
        char* word = &str[last_word];
        str[index] = 0;
        if(!is_misspelled(word, dictionary)){
          r++;
          if(is_column){
            printf("\"%s\" vertical at row %d, column %d\n", word, last_word, row_or_column_index);
          }else{
            printf("\"%s\" horizontal at row %d, column %d\n", word, row_or_column_index, last_word);
          }
        }
        last_word = -1;
        str[index] = el;
      }
    }

    if(el == 0){
      break;
    }
    index++;
  }
  return r;

};

//FINDS WORDS IN DICT, RETURNS NUMBER OF MATCHES
int find_words_in_dict(char* dict_buffer){
  int matches = 0;
  for(int r = 0; r < rows; r++){
    char str[columns+1];
    get_row(str, r);
    matches += string_occurences(str, dict_buffer, 0, r);
  }
  for(int c = 0; c < columns; c++){
    char str[rows+1];
    get_column(str, c);
    matches += string_occurences(str, dict_buffer, 1, c);
  }
  return matches;
}

//FINDS WORDS PROVIDED BY USER, RETURNS NUMBER OF MATCHES
int find_words_from_user(){
  printf("Enter words to search for separated by newline, end with \"q\"\n");
  int dict_len = 20;
  char* dict_buffer = (char*) malloc(dict_len*sizeof(char));
  int index = 0;
  int max_len = rows > columns ? rows : columns;
  while(1){
    //dynamically resize dictionary if needed
    if(index == dict_len){
      dict_len += 20;
      dict_buffer = (char*) realloc(dict_buffer, dict_len*sizeof(char));
    }

    char c = fgetc(stdin);
    //stop if user entered q
    if(c == '\n' && index >= 2 && dict_buffer[index - 1] == 'q' && dict_buffer[index - 2] == '\n'){
      dict_buffer[index - 1] = 0;
      break;
    }
    dict_buffer[index] = c;
    index++;
  }

  int matches = find_words_in_dict(dict_buffer);
  free(dict_buffer);
  return matches;
};
