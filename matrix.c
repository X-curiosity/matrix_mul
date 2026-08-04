#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int gen_rand(int s,int e){

    srand(time(NULL)); 

    int number = rand();

    if (number > e && number < s){
        return number;
    }

    return number%s;
}


int* create_matrix(int rows, int columns)
{
    // Allocate memory for the array
    int* matrix = (int*)malloc(rows*columns * sizeof(int));

    // Check if memory allocation was successful
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < rows*columns ; i++){

        matrix[i] =  gen_rand(10,0);

    }

    return matrix;
}


int* mul_matrix(int* m1 , int* m2, int row1,int column1,int row2,int column2){

    int* mat = (int*)malloc(row1*column2 * sizeof(int));

      // Check if memory allocation was successful
    if (mat == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Check if the dimensions fit
    if (column1 != row2) {
        printf("Those 2 matrices can't be multiplied!\n");
        exit(1);
    }


    for(int j = 0; j < row1*column2; j++){
        for(int i = 0; i < row1; i++ ){

            mat[j] = mat[j] + m1[i]*m2[j+column2*i];
      
        }
    }

    return mat;
    
}


void show_matrix(int*matrix , int row , int column){

    for(int i = 0; i < row; i++){
        for(int j = 0; j <column;j++){

        if (j == column-1){
           
            printf(" %d\n",matrix[j+i*row]);
        }

        else{
            printf(" %d",matrix[j+i*row]);
           
        }

        }


    }
    
}




int main(void){



    int* matrix1 = create_matrix(2, 3);
    int* matrix2 = create_matrix(3, 2);

    //Print the matrices
    show_matrix(matrix1,2,3);
    printf("**************************\n");
    show_matrix(matrix2,3,2);
    printf("**************************\n");


    int *final_mat = mul_matrix(matrix1,matrix2,2,3,3,2);

    //Print the final result 
    printf("The result of the multiplication is : \n");
    show_matrix(final_mat,2,2);


     //desallocation matrices from memory 
    free(matrix1);
    free(matrix2);
    free(final_mat);


    return 0;


}



