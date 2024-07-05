import subprocess


def remove_extra_blank_lines(i):
    file_path = f"result/case_{i}/case_{i}_result_hashes.txt"
    with open(file_path, "r") as file:
        lines = file.readlines()

    # Loại bỏ các dòng trống thừa
    cleaned_lines = [line for line in lines if line.strip()]

    # Thêm 3 ký tự xuống hàng sau mỗi lần xuống hàng
    normalized_lines = []
    for line in cleaned_lines:
        if line.startswith("Running command:"):
            normalized_lines.append("\n" * 3)
        normalized_lines.append(line)

    with open(file_path, "w") as file:
        file.writelines(normalized_lines)

    print(f"Removed extra blank lines in case_{i} result file.")

def run_hashing_test_cases(i):
    # Danh sách các lệnh để chạy test case
    commands = [
        "SHA_224 file", 
        "SHA_256 file", 
        "SHA_384 file",
        "SHA_512 file", 
        "SHA3_224 file", 
        "SHA3_256 file", 
        "SHA3_384 file", 
        "SHA3_512 file", 
        "SHAKE128 file", 
        "SHAKE256 file"
    ]

    # Mở file để ghi kết quả
    with open(f"./result/case_{i}/case_{i}_result_hashes.txt", "w") as f:
        # Thực thi từng lệnh và ghi kết quả vào file
        for command in commands:
            mode = command.split()[0]
            # case_file_path = f"./all_test_cases/case_{i}.txt"
            case_file_path= "D:/adele/case_5.txt"
            hashed_file_path = f"./result/case_{i}/case_{i}_{mode}.txt"
            command = f"lab_4-1.exe {command} {case_file_path} {hashed_file_path}"

            f.write(f"\nRunning command: {command}\n")
            process = subprocess.Popen(
                command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            output, error = process.communicate()

            if process.returncode == 0:
                f.write("Command executed successfully.\n")
            else:
                f.write("Command execution failed.\n")
            f.write(output.decode().rstrip() + "\n")
            f.write(error.decode().rstrip() + "\n")
    
    print(f"Running Hashing for case_{i} successfully!")

# Thực hiện test case
i = 5
run_hashing_test_cases(i)
remove_extra_blank_lines(i)
