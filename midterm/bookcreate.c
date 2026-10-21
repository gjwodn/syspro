#include <stdio.h> 

int main(int argc, char* argv[])  
{ 
   struct student rec;
   FILE *fp;

   if (argc != 2) {
      fprintf(stderr, "How to use: %s FileName\n",argv[0]);
      exit(1); 
   }

   fp = fopen(argv[1], "wb");
   printf("%-3s %-9s %-9s %-4s %-2s %-5s\n", "ID", "BookName", "author", "year", "numofborrow", "borrow"); 
   while (scanf("%d %s %d", &rec.id, rec.name, &rec.author, &rec.year, &rec.numofborrow, &rec.borrow) == 3) 
      fwrite(&rec, sizeof(rec), 1, fp);

   fclose(fp);
   exit(0);
} 

