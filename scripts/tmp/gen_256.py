import os

def generate_trampline_array(path):
    with open(path, "w") as f:
        for i in range(256):
            f.write(f"\ttramplins[{i}] = tramplin_{i};\n")


if __name__ == "__main__":
    generate_trampline_array("generated_tmp/file.txt")