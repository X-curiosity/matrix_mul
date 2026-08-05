#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cjson/cJSON.h>


// We define here the list that we're gonna use to iterate over several sizes of matrices 

int rows1[24] = {
    16, 24, 32, 40, 48, 64,
    72, 80, 96, 112, 128, 144,
    160, 192, 224, 256, 288, 320,
    384, 448, 512, 576, 640, 768
};

int columns1[24] = {
    24, 32, 48, 64, 80, 96,
    128, 160, 192, 224, 256, 288,
    320, 384, 448, 512, 576, 640,
    768, 896, 1024, 1152, 1280, 1536
};

int rows2[24] = {
    24, 32, 48, 64, 80, 96,
    128, 160, 192, 224, 256, 288,
    320, 384, 448, 512, 576, 640,
    768, 896, 1024, 1152, 1280, 1536
};

int columns2[24] = {
    12, 16, 24, 32, 40, 48,
    64, 96, 128, 160, 192, 224,
    256, 288, 320, 384, 448, 512,
    576, 640, 768, 832, 896, 1024
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

        matrix[i] =  gen_rand(1000,10);

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


    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < column2; j++) {
            int sum = 0;
            
            for (int k = 0; k < column1; k++) {
                sum += m1[i * column1 + k]* m2[k * column2 + j];
            }
            mat[i * column2 + j] = sum;
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


int main(int argc, char *argv[]){

    if (argc < 2) {
        printf("Usage: %s <label>\n", argv[0]);
        return 1;
    }

    //Declare variables for matrices dimensions
    int row1 ;
    int column1;
    int row2 ;
    int column2;
    
    
    
    clock_t t;  //Time variable
    cJSON *results = cJSON_CreateArray(); // Json Array
    

    for(int i = 0; i < length ;i++){

        cJSON *data = cJSON_CreateObject();

        

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


        char matrix_size1[32];
        char matrix_size2[32];
        char matrix_size_final[32];


        int nbr_of_ops = row1*column2*(column1+2);


        snprintf(matrix_size1, sizeof(matrix_size1), "%dx%d", row1, column1);
        snprintf(matrix_size2, sizeof(matrix_size2), "%dx%d", row1, column1);
        snprintf(matrix_size_final, sizeof(matrix_size_final), "%dx%d", row1, column2);

        cJSON_AddStringToObject(data, "m1 size", matrix_size1);
        cJSON_AddStringToObject(data, "m2 size", matrix_size2);
        cJSON_AddStringToObject(data, "final_m size", matrix_size_final);
        cJSON_AddNumberToObject(data, "nb_operations", nbr_of_ops);
        cJSON_AddNumberToObject(data, "inference time (in sec)", time_taken);

        cJSON_AddItemToArray(results, data); // Adding data to array


        //desallocation matrices from memory 
        free(matrix1);
        free(matrix2);
        free(final_mat);
        



    }

    char filename[64];
    snprintf(filename, sizeof(filename), "result_%s.json", argv[1]);
    
    char *json_str = cJSON_Print(results);
    FILE *fp = fopen(filename, "w");
    fputs(json_str, fp);
    fclose(fp);
    cJSON_free(json_str);
    cJSON_Delete(results);
    return 0;

}



