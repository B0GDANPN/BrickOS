import numpy as np
import random

file_name = "mess"
check_sum = 0

N = 2**16 
bin_data=b""

for i in range(N):
    gen_byte = random.getrandbits(8)

    bin_data += gen_byte.to_bytes()
    check_sum = (check_sum + gen_byte)%2**8

with open(f"./bin/{file_name}.bin", "wb") as f:
    f.write(bin_data)
