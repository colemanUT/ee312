//PRINTS AND RETURNS LENGTH OF LONGEST VERTICAL WORD
int find_max_length(){
  int max_len = 0;
  int current_len = 0;
  for(int c = 0; c < columns; c++){
    for(int r = 0; r <= rows; r++){
      char el = crossword[r*columns+c];
      if(el == '*' || r == rows){
        if(current_len > max_len){
          max_len = current_len;
        }
        current_len = 0;
      }else{
        current_len++;
      }
    }
  }
  printf("Max vertical word length is %d\n", max_len);
  return max_len;
};
