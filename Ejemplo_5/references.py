import random

def random_vectors_and_sum(size, min_val, max_val):
    vec1 = [random.randint(min_val, max_val) for _ in range(size)]
    # Calculates the sum of all elements in both vectors (no multiplication)
    total_sum = sum(vec1) 
    return vec1, total_sum

I_FILE = "golden_Inputs.dat"
R_FILE = "golden_Reference.dat"
TESTS = 100
N = 8

# Range for a 32-bit signed integer
# Min: -2^31 | Max: (2^31) - 1
min_val = 0
max_val = 2**28 - 1

with open(R_FILE, "w", encoding="UTF8") as gref:
    with open(I_FILE, "w", encoding="UTF8") as ginf:
        for tst in range(TESTS):
            vec1, res = random_vectors_and_sum(N, min_val, max_val)
            
            line_list = [f"{x}\n" for x in (vec1)]
            ginf.writelines(line_list)
            
            gref.write(f"{abs(res)}\n")