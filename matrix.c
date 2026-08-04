#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cjson/cJSON.h>


// We define here the list that we're gonna use to iterate over several sizes of matrices 

int rows1[50] = {
    3, 7, 9, 25, 50, 75, 100, 150, 200, 256,
    384, 512, 640, 768, 1024, 1280, 1536, 2048, 2560, 5400,
    5600, 5800, 6000, 6200, 6400, 6600, 6800, 7000, 7200, 7400,
    7600, 7800, 8000, 8200, 8400, 8600, 8800, 9000, 9200, 9400,
    9600, 9800, 10000, 10500, 11000, 11500, 12000, 12500, 13000, 13500
};

int columns1[50] = {
    4, 8, 16, 25, 50, 96, 128, 160, 200, 256,
    512, 768, 896, 1024, 1280, 1536, 1792, 2304, 3072, 4500,
    4800, 5000, 5200, 5400, 5600, 5800, 6000, 6200, 6400, 6600,
    6800, 7000, 7200, 7400, 7600, 7800, 8000, 8200, 8400, 8600,
    8800, 9000, 9200, 9400, 9600, 9800, 10000, 10500, 11000, 11500
};

int rows2[50] = {
    4, 8, 16, 25, 50, 96, 128, 160, 200, 256,
    512, 768, 896, 1024, 1280, 1536, 1792, 2304, 3072, 4500,
    4800, 5000, 5200, 5400, 5600, 5800, 6000, 6200, 6400, 6600,
    6800, 7000, 7200, 7400, 7600, 7800, 8000, 8200, 8400, 8600,
    8800, 9000, 9200, 9400, 9600, 9800, 10000, 10500, 11000, 11500
};

int columns2[50] = {
    8, 12, 20, 25, 50, 128, 160, 192, 224, 256,
    640, 768, 896, 1024, 1536, 1792, 2048, 2560, 3072, 5275,
    5500, 5700, 5900, 6100, 6300, 6500, 6700, 6900, 7100, 7300,
    7500, 7700, 7900, 8100, 8300, 8500, 8700, 8900, 9100, 9300,
    9500, 9700, 9900, 10100, 10300, 10500, 10700, 10900, 11100, 11300
};


int length =  sizeof(columns1)/sizeof(columns1[0]);



int gen_rand(int s,int e){
 
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


    for(int j = 0; j < (row1*column2)-2; j= j+2){
        for(int i = 0; i < row1; i++){
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

    // Create a file to write the results 
    FILE* fp = fopen("result.txt", "w");

    if (fp == NULL) {
       printf("Error: Unable to open the file.\n");
       return 1;
   }




    //Declare variables for matrices dimensions
    int row1 ;
    int column1;
    int row2 ;
    int column2;
    
    
    
    clock_t t;  //Time variable

    for(int i = 0; i < length ;i++){

        row1 = rows1[i];
        row2 = rows2[i];
        column1 = columns1[i];
        column2 = columns2[i];

        srand(time(NULL));


        int* matrix1 = create_matrix(row1, column1);
        int* matrix2 = create_matrix(row2, column2);
        
      
        t = clock();
        int *final_mat = mul_matrix(matrix1,matrix2,row1,column1,row2,column2);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds


        cJSON *json = cJSON_CreateObject();
        cJSON_AddStringToObject(json, "m1 size", row1"x"column1);
        cJSON_AddNumberToObject(json, "m2 size", row2"x"column2);
        cJSON_AddStringToObject(json, "final_m size", row1"x"column2);
        cJSON_AddStringToObject(json, "inference time", time_taken);


        char *json_str = cJSON_Print(json);
        fputs(json_str, fp);

        //desallocation matrices from memory 
        free(matrix1);
        free(matrix2);
        free(final_mat);


    }

    // Closing the file using fclose()
    fclose(fp);
    printf("Data successfully written in file "
        "result.txt\n");
    printf("The file is now closed.");
    cJSON_free(json_str);
    cJSON_Delete(json);

    return 0;

}



