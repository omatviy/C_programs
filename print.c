#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void err(char *s)
{
 printf("\a%s\nProgram terminated.\n",s);
 exit(EXIT_FAILURE);
}

struct PTInfo
{
  double (*f)(double);
  double a,b;
  double step;
};

void printTab(FILE *fp, struct PTInfo p)
{
  double i;
  fprintf(fp,"+=========+=========+\n");
  fprintf(fp,"|    x    |   f(x)  |\n");
  fprintf(fp,"+=========+=========+\n");
  for(i=p.a;i<=p.b;i+=p.step)
   if (EOF==fprintf(fp,"|  %5.4lf |  %5.4lf |\n",i,(*p.f)(i))) err("Can’t write");
  fprintf(fp,"+=========+=========+\n");
}

 void PrintInFile(struct PTInfo pt)
{
  char *filename;
  FILE *fp;
  if ((filename=malloc(80))==NULL) err("Not enough memory");
  printf("Input filename : ");
  scanf("%s", filename);
  if ((fp=fopen(filename,"w"))==NULL) err("Can’t open file");
  printTab(fp,pt);
  if (EOF==fclose(fp)) err("Can’t close file");
}


void PrintOnPrinter(struct PTInfo pt)
{
  //printTab(stdprn, pt);
}




void PrintOnScreen(struct PTInfo pt)
{
  printTab(stdout, pt);
}


void (*PrintFunc[])(struct PTInfo)={PrintInFile, PrintOnScreen,PrintOnPrinter};

int main(void)
{
  struct PTInfo p;
  int i;
  puts("Print Table of any arc… Function.\n");
  puts("1. arcsin");
  puts("2. arccos");
  puts("3. arctg");
  printf("Your choice is ");
  scanf("%d",&i);
  switch(i)
  {
     case 1: p.f=asin; break;
     case 2: p.f=acos; break;
     case 3: p.f=atan; break;
     default: err("Invalid choice");
  }
 printf("Enter interval: ");
 scanf("%lf %lf", &p.a, &p.b);

 if (((p.a<-1 || p.b>1) && (p.f!=atan)) || p.a>p.b) err("Invalid interval");
 printf("Enter step     :");
 scanf("%lf",&p.step);

 puts("1. Print in file");
 puts("2. Print on screen");
 puts("3. Print on printer");
 printf("Your choice is ");
 scanf("%d",&i);

 if (i<1 || i>3) err("Invalid choice");
 (*PrintFunc[i-1])(p);
 return EXIT_SUCCESS;
}
