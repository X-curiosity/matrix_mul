import sys
import numpy as np
import random as rd
import time
import json
from pathlib import Path


#Define different sizes of matrices 

rows1 = [
    3, 7, 9, 25, 50, 75, 100, 150, 200, 256,
    384, 512, 640, 768, 1024, 1280, 1536, 2048, 2560, 5400,
    5600, 5800, 6000, 6200, 6400, 6600, 6800, 7000, 7200, 7400,
    7600, 7800, 8000, 8200, 8400, 8600, 8800, 9000, 9200, 9400,
    9600, 9800, 10000, 10500, 11000, 11500, 12000, 12500, 13000, 13500
]

columns1 = [
    4, 8, 16, 25, 50, 96, 128, 160, 200, 256,
    512, 768, 896, 1024, 1280, 1536, 1792, 2304, 3072, 4500,
    4800, 5000, 5200, 5400, 5600, 5800, 6000, 6200, 6400, 6600,
    6800, 7000, 7200, 7400, 7600, 7800, 8000, 8200, 8400, 8600,
    8800, 9000, 9200, 9400, 9600, 9800, 10000, 10500, 11000, 11500
]

rows2 = columns1.copy()

columns2 = [
    8, 12, 20, 25, 50, 128, 160, 192, 224, 256,
    640, 768, 896, 1024, 1536, 1792, 2048, 2560, 3072, 5275,
    5500, 5700, 5900, 6100, 6300, 6500, 6700, 6900, 7100, 7300,
    7500, 7700, 7900, 8100, 8300, 8500, 8700, 8900, 9100, 9300,
    9500, 9700, 9900, 10100, 10300, 10500, 10700, 10900, 11100, 11300
]

assert len(rows1) == 50
assert len(columns1) == 50
assert len(rows2) == 50
assert len(columns2) == 50
assert columns1 == rows2


all_results = []




def generate_random_matrix(rows = 0,columns = 0):
    
    
    m=np.zeros(((rows,columns)))

    for i in range (rows):
        for j in range(columns):
            m[i][j] = rd.randrange(100,10e6)
            
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
        
        data = {
            "matrix1 size" :f"{row1}x{column1}",
            "matrix2 size" : f"{row2}x{column2}",
            "final_matrix size" : f"{row1}x{column2}",
            "inference time" : f"{t:.3e} s",
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