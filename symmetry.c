//RETURNS 1 IF MATRIX IS SYMMETRICAL, 0 OTHERWISE
int check_symmetric(){
  int symmetry = 1;
  int d_length = rows < columns ? rows : columns;
  int c_start = 1;
  for(int r = 0; r < d_length; r++){
    for(int c = 1 + r; c < d_length; c++){
      char top = crossword[r*columns + c];
      char bottom = crossword[c*columns + r];
      if(top != bottom && (top == '*' || bottom == '*')){
        printf("Mismatch between [%d,%d](\'%c\') and [%d,%d](\'%c\')\n", r,c,top, c,r,bottom);
        symmetry = 0;
      }
    }
  }
  if(rows > columns){
    printf("No mirrored cell exists for cells in rows %d - %d\n", columns, rows-1);
    symmetry = 0;
  }
  else if(columns > rows){
    printf("No mirrored cell exists for cells in columns %d-%d\n", rows, columns-1);
    symmetry = 0;
  }
  if(symmetry){
    printf("It's symmetrical!\n");
  }
  return symmetry;
};
