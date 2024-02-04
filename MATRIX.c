/*This code is prepared to solve high order matrix functions */
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10

//Function to print matrix output
void Print_Matrix(int matrix[][MAX_SIZE],int rows,int columns)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

//DETERMINANT
double determinant(int matrix[MAX_SIZE][MAX_SIZE], int n) 
{
    double det = 0;

    if (n == 1) {
        return matrix[0][0];
    } else if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        for (int k = 0; k < n; ++k) {
            // Create a submatrix excluding the k-th row and column
            int submatrix[MAX_SIZE][MAX_SIZE];
            for (int i = 1; i < n; ++i) 
            {
                int submatrixCol = 0;
                for (int j = 0; j < n; ++j) 
                {
                    if (j != k) 
                    {
                        submatrix[i - 1][submatrixCol] = matrix[i][j];
                        submatrixCol++;
                    }
                }
            }

            // Recursive call to find the determinant of the submatrix
            det += matrix[0][k] * determinant(submatrix, n - 1) * ((k % 2 == 0) ? 1 : -1);
        }
    }

    return det;
}



//Transpose
void trans(int matrix[][MAX_SIZE],int rows,int columns)
{
    int c[MAX_SIZE][MAX_SIZE];
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            c[j][i]=matrix[i][j];
        }
    }
    Print_Matrix(c,columns,rows);
}

//MINOR FOR INVERSE
double minor(int mat[MAX_SIZE][MAX_SIZE], int row, int col, int size)
{
    int i_minor = 0, j_minor = 0;
    int minor[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < size; i++) 
    {
        if (i != row) 
        {
            for (int j = 0; j < size; j++) 
            {
                if (j != col) 
                {
                    minor[i_minor][j_minor++] = mat[i][j];

                    if (j_minor == size - 1) 
                    {
                        j_minor = 0;
                        i_minor++;
                    }
                }
            }
        }
    }
    double value_of_minor=determinant(minor,size-1);
    return value_of_minor;
}
//INVERSE
void inverse(int matrix[][MAX_SIZE],int n)
{
    double det=determinant(matrix,n);
    if(det==0)
    {
        printf("The value of the determinant of the matrix is 0\nHence Inverse is not possible\n");
        return;
    }
    if(n==1)
    {
        double ans=1/(double)matrix[0][0];
        printf("%.2f\n",ans);
        return;
    }
    double cofactor[MAX_SIZE][MAX_SIZE];
    double adjoint[MAX_SIZE][MAX_SIZE];
    double inverse[MAX_SIZE][MAX_SIZE];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            matrix[i][j]=(double)matrix[i][j];
            cofactor[i][j]=minor(matrix,i,j,n)* (((i+j)% 2 == 0) ? 1 : -1);
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            adjoint[j][i]=cofactor[i][j];
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            inverse[i][j]=adjoint[i][j]/det;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%.2f ",inverse[i][j]);
        }
        printf("\n");
    }
}

//MULTIPLICATION
void mul(int x[][MAX_SIZE],int y[][MAX_SIZE],int arows,int acolumns,int brows,int bcolumns)
{
    if(acolumns!=brows)
    {
        printf("The column of first matrix should be equal to the row of the second matrix for matrix multiplication to work\nHence the multipication of matrices cannot happen\n");
        return ;
    }
    int sum=0,c[MAX_SIZE][MAX_SIZE];
    for(int i=0;i<arows;i++)
    {
        for(int j=0;j<bcolumns;j++)
        {
            for(int k=0;k<acolumns;k++)
            {
                sum+=x[i][k]*y[k][j];
            }
            c[i][j]=sum;
            sum=0;
        }
    }
    Print_Matrix(c,arows,bcolumns);
}

//Addition
void sum(int a[][MAX_SIZE],int b[][MAX_SIZE],int rows,int columns)
{
    int c[MAX_SIZE][MAX_SIZE];
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            c[i][j]=a[i][j]+b[i][j];
        }
    }
    Print_Matrix(c,rows,columns);
}
//Substraction
void minus(int x[][MAX_SIZE],int y[][MAX_SIZE],int rows,int columns)
{
    int c[MAX_SIZE][MAX_SIZE];
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            c[i][j]=x[i][j]-y[i][j];
        }
    }
    Print_Matrix(c,rows,columns);
}

//MAIN FUNCTION
void main()
{
    printf("WELCOME USER\nTHIS PROGRAM IS PREPARED BY MEGH PATEL\n\n=>It is dedicated to matrix operations\n=>You can only operate on 2 matrices at a time so it is advisable to keep a book to record outputs in case of long calculations\n=>You can calculate upto 10x10 Matrix\n");

    int operation,operator;
    int a[MAX_SIZE][MAX_SIZE],b[MAX_SIZE][MAX_SIZE];
    int m1,n1,m2,n2;
  
    printf("Do you want to operate with 1 or 2 matrices:");
    scanf("%d",&operator);
    if(operator>2 || operator<1)
    {
        printf("Please enter the values correctly");
        exit(0);
    }
    printf("In Matrix A\nHow many rows do you want:");
    scanf("%d",&m1);
    printf("How many columns do you want:");
    scanf("%d",&n1);
    if(m1<0 || n1<0 || m1>10 || n1>10)
    {
        printf("Please enter the values of row and column correctly");
        exit(0);
    }
    printf("Enter the elements of the matrix as you would write in a book\nWrite matrix A\n");
    //getting a matrix
    for(int i=0;i<m1;i++)
    {
        for(int j=0;j<n1;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    if(operator==1)
    goto menu;
    printf("\nIn Matrix B\nHow many rows do you want:");
    scanf("%d",&m2);
    printf("How many columns do you want:");
    scanf("%d",&n2);
    if(m2<0 || n2<0 || m2>10 || n2>10)
    {
        printf("Please enter the values of row and column correctly");
        exit(0);
    }
    printf("Write matrix B\n");
    for(int i=0;i<m2;i++)
    {
        for(int j=0;j<n2;j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
    menu:
    printf("\n******************************************\nHere are the categories we offer\nPress 0 to exit\n[1]ADDITION\n[2]SUBTRACTION\n[3]MULTIPLICATION\n[4]Transpose\n[5]INVERSE\n[6]DETERMINANT\n*****************************************************\nSELECT YOUR OPTION:");
    scanf("%d",&operation);
    switch(operation)
    {
        int choice,option;
        case 0:
        {
            printf("\n%c %c %c THANK YOU %c %c %c \n",001,001,001,001,001,001);
            exit(0);
        }
        case 1:
        {
            if(operator==1)
            {
                printf("This service is only available for 2 Matrices\nPlease select appropriate option");
                goto menu;  
            }
            if(m1!=m2 || n1!=n2)
            {
                printf("Two matrices need to have the same number of rows and columns");
                goto menu;
            }
            printf("Matrix A+B:-\n");
            sum(a,b,m1,n1);
            
            goto menu;
            break;
        }
        case 2:
        {
            if(operator==1)
            {
                printf("This service is only available for 2 Matrices\nPlease select appropriate option");
                goto menu;  
            }
            if(m1!=m2 || n1!=n2)
            {
                printf("Two matrices need to have the same number of rows and columns");
                goto menu;
            }

            printf("What do you want\n[1]A-B\n[2]B-A\nEnter:");
            scanf("%d",&option);
            printf("The diffrence:-");
            if(option==1)
            minus(a,b,m1,n1);
            else if(option==2)
            minus(b,a,m1,n1);
            else{
                printf("Please select appropriate option");
                goto menu;
            }

            
            goto menu;
            break;
        }
        case 3: //MULTIPLICATION
        {
            if(operator==1)
            {
                printf("This service is only available for 2 Matrices\nPlease select appropriate option");
                goto menu;  
            }
            
            printf("[1]AxB\n[2]BxA\nEnter:");
            scanf("%d",&option);
            if(option==1)
            mul(a,b,m1,n1,m2,n2);
            else if(option==2)
            mul(b,a,m2,n2,m1,n1);
            else{
                printf("Please select appropriate option");
                goto menu;
            }
            
            goto menu;
            break;
        }
        case 4: //TRANSPOSE
        {   
            if(operator==1)
            {
                printf("Transpose of Matrix:-\n");
                trans(a,m1,n1);
                goto skip_choice_trans;
            }
            printf("Which matrix do you want to operate [1]A\n[2]B:\nEnter:");
            int d;
            scanf("%d",&d);
            printf("Transpose of Matrix:-\n");
            if(d==1)
            trans(a,m1,n1);
            else if(d==2)
            trans(b,m2,n2);
            else
            {
                printf("Please select appropriate option");
                goto menu;
            }
            skip_choice_trans:
            
            goto menu;
            break;

        }
        case 5: //INVERSE
        {
            if(operator==1)
            {
                printf("Inverse of Matrix:-\n");
                inverse(a,m1);
                goto skip_choice_inverse;
            }
            printf("Which matrix do you want to operate [1]A\n[2]B:\nEnter:");
            int d;
            scanf("%d",&d);
            printf("Inverse of Matrix:-\n");
            if(d==1)
            {
                if(m1!=n1)
                {
                    printf("This is only possible for square matrices which have the same number of rows and colums\n");
                    goto menu;
                }
                inverse(a,m1);
            }
            else if(d==2)
            {
                if(m2!=n2)
                {
                    printf("This is only possible for square matrices which have the same number of rows and colums\n");
                    goto menu;
                }
                inverse(b,m2);
                
            }
            else
            {
                printf("Please select appropriate option");
                goto menu;
            }
            skip_choice_inverse:
            
            goto menu;
            break;
            
        }
        case 6: //DETERMINANT
        {
            if(operator==1)
            goto skip_choice_det;
            printf("Which matrix do you want to operate [1]A\n[2]B:\nEnter:");
            int d;
            scanf("%d",&d);
            double det;
            skip_choice_det:
            if(d==1 || operator==1)
            {
                if(m1!=n1)
                {
                    printf("This is only possible for square matrices which have the same number of rows and colums\n");
                    goto menu;
                }
                det = determinant(a,n1);
            }
            else if(d==2)
            {
                if(m2!=n2)
                {
                    printf("This is only possible for square matrices which have the same number of rows and colums\n");
                    goto menu;
                }
                det = determinant(b,n2);
            }
            else
            {
                printf("Please select appropriate option");
                goto menu;
            }

            printf("Determinant of the matrix:%.2f\n", det);
            
            goto menu;
            break;
        }
        default:
        {
            printf("Enter a valid choice\n");
            goto menu;
        }
    }
}