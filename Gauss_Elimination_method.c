#include<stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
  int i,j,k,n;
  float A[20][20],ratio,x[10],sum=0;

  FILE *inputFile;
  inputFile = fopen("input.dat", "r");

  if(inputFile == NULL){
    printf("Error: failed to read input.dat.\n");
    exit(1);
  }

  fscanf(inputFile, "%d", &n);
  printf("Order of the matrix: %d\n", n);

  printf("Reading matrix elements...\n");
  for(i = 1; i <= n; i++){
    for(j = 1; j <= (n+1); j++){
      if(fscanf(inputFile,"%f" , &A[i][j]) != 1){
        printf("Error: cannot read matrix elements.\n");
        fclose(inputFile);
        exit(1);
      }
    }
  }

  fclose(inputFile);
  printf("Successful read of the document.\n\n");



  clock_t start_time, end_time;
  double cpu_time_used;

  start_time = clock();

  for(j=1;j<=n;j++)
  {
    for(i=1;i<=n;i++)
    {
      if(i>j)
      {
        ratio=A[i][j]/A[j][j];
        for(k=1;k<=n+1;k++)
        {
          A[i][k]=A[i][k]-ratio*A[j][k];
        }
      }
    }
  }

  x[n]=A[n][n+1]/A[n][n];

  for(i=n-1;i>=1;i--)
  {
    sum=0;
    for(j=i+1;j<=n;j++)
    {
      sum=sum+A[i][j]*x[j];
    }
    x[i]=(A[i][n+1]-sum)/A[i][i];
  }


  end_time = clock();
  cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

  printf("\nSolution:");
  for(i=1;i<=n;i++)
  {
    printf("\nx%d=%f\t",i,x[i]);
  }

  printf("\n\nTime of execution: %f seconds\n", cpu_time_used);

  return(0);
}
