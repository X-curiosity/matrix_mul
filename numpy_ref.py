import sys
import numpy as np
import random as rd
import time
import json
from pathlib import Path


#Define different sizes of matrices 

rows1 = [
    16, 24, 32, 40, 48, 64,
    72, 80, 96, 112, 128, 144,
    160, 192, 224, 256, 288, 320,
    384, 448, 512, 576, 640, 768
]

columns1 = [
    24, 32, 48, 64, 80, 96,
    128, 160, 192, 224, 256, 288,
    320, 384, 448, 512, 576, 640,
    768, 896, 1024, 1152, 1280, 1536
]

rows2 = columns1.copy()

columns2 = [
    12, 16, 24, 32, 40, 48,
    64, 96, 128, 160, 192, 224,
    256, 288, 320, 384, 448, 512,
    576, 640, 768, 832, 896, 1024
]








assert len(rows1) == 24
assert len(columns1) == 24
assert len(rows2) == 24
assert len(columns2) == 24
assert columns1 == rows2


all_results = []




def generate_random_matrix(rows = 0,columns = 0):
    
    
    m=np.zeros(((rows,columns)))

    for i in range (rows):
        for j in range(columns):
            m[i][j] = rd.randrange(100,10000)
            
    return m
            

def main():
    
    for i in range(len(rows1)):
        
        row1 = rows1[i]
        row2 = rows2[i]
        column1 = columns1[i]
        column2 = columns2[i]
        
        
        m1 = generate_random_matrix(row1,column1)
        m2 = generate_random_matrix(row2,column2)
        
        
        start = time.time()
        m = m1@m2
        end = time.time()
        t = end-start
        
        nbr_of_ops = row1*column2*(column1+2);
        
        data = {
            "matrix1 size" :f"{row1}x{column1}",
            "matrix2 size" : f"{row2}x{column2}",
            "final_matrix size" : f"{row1}x{column2}",
            "inference time (in sec)" : t,
            "number of operations " : nbr_of_ops,
        }
        
        all_results.append(data)
        
    destination = Path("results/numpy_reference.json")
    destination.parent.mkdir(parents=True, exist_ok=True)
    
    with destination.open("w", encoding="utf-8") as file:
        json.dump(all_results, file, indent=2)
    
            
  
    return 0

if __name__ == "__main__":
    # Passing main() to sys.exit() maps the return value to standard shell exit codes
    sys.exit(main())