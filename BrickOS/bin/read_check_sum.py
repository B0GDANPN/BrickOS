boot_img = r"./scripts/boot.img"
mess_bin = r"./bin/mess.bin"

check_sum = 0

with open(boot_img, "rb") as f:
    bin_data = f.read()
    for i in range(0, len(bin_data)):
        byte = bin_data[i]
        check_sum = (check_sum + byte)


print(hex(check_sum%2**8))
