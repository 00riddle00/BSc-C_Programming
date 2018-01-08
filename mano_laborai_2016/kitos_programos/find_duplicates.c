 for(i = 0; i < size; i++) {
  for (j=0; j<i; j++){
      if (array[i] == array[j])
       break;
       }
      
     if (i == j){
      /* No duplicate element found between index 0 to i */
      printf("%d ", array[i]);
  }
 }
