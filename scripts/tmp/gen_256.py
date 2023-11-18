import os

error_code_tramplines = [0x8, 0xa, 0xb, 0xc, 0xd, 0xe, 0x11, 0x15, 0x1d, 0x1e]

def generate_trampline_array(path):
    with open(path, "w") as f:
        for i in range(256):
            f.write(f"_tramplin_{i}:\n")
            if i not in error_code_tramplines:
                f.write(f"\tpush 0xDEADC0DE\n")
            f.write(f"\tpush {i}\n")
            f.write(f"\tjmp make_context\n")



if __name__ == "__main__":
    generate_trampline_array("generated_tmp/file.txt")