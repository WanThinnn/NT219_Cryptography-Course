import subprocess
import os


# Nhớ tạo key trước khi gọi 2 hàm bên dưới: AES__CLI genkey 256 DER key_AES.key",


def remove_extra_blank_lines(i, string):
    if i == 0:
        file_path = f"result_linux/result_{string}.txt"
    else:
        file_path = f"result_linux/case_{i}/case_{i}_result_{string}.txt"
    with open(file_path, "r") as file:
        lines = file.readlines()

    # Loại bỏ các dòng trống thừa
    cleaned_lines = []
    for line in lines:
        if line.strip():  # Kiểm tra xem dòng có chứa ký tự nào không
            cleaned_lines.append(line)

     # Thêm 3 ký tự xuống hàng sau mỗi lần xuống hàng
    normalized_lines = []
    for line in cleaned_lines:
        if line.startswith("Running command:"):
            normalized_lines.append("\n" * 3)
        normalized_lines.append(line)

    with open(file_path, "w") as file:
        file.writelines(normalized_lines)

    print(f"----------------------------------------------------------")

def run_genkey_test_cases():
    # Danh sách các lệnh để chạy test case
    commands = [
        "genkey 256 HEX key_AES.key",
    ]

    # Mở file để ghi kết quả
    with open(f"./result_linux/result_genkey.txt", "w") as f:
        # Thực thi từng lệnh và ghi kết quả vào file
        for command in commands:
            key_iv_exist = os.path.exists("./keys/key_AES.key")
            if "genkey" in command and key_iv_exist:
                f.write("Key and IV already exist. Skipping command execution.\n")
                continue

            if "genkey" in command:
                command = f"./main {command}"
            # In lệnh đang chạy
            f.write(f"\nRunning command: {command}\n")
            # Thực hiện lệnh và chứa output vào một biến
            process = subprocess.Popen(
                command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            output, error = process.communicate()

            # Kiểm tra và ghi kết quả vào file
            if process.returncode == 0:
                f.write("Command executed successfully.\n")
            else:
                f.write("Command execution failed.\n")
            # In output vào file
            # Sử dụng rstrip() để loại bỏ ký tự xuống dòng thừa
            f.write(output.decode().rstrip())
            # In error vào file
            # Sử dụng rstrip() để loại bỏ ký tự xuống dòng thừa
            f.write(error.decode().rstrip())
    remove_extra_blank_lines(0, "genkey")
    print(f"Running Genkey AES-CBC-Manual for all cases successfully!")



def run_encrypt_test_cases(i):
    # Danh sách các lệnh để chạy test case
    commands = [
        "encrypt",
        
    ]

    # Mở file để ghi kết quả
    with open(f"./result_linux/case_{i}/case_{i}_result_encrypt.txt", "w") as f:
        # Thực thi từng lệnh và ghi kết quả vào file
        for command in commands:
            # Lấy phần thứ hai của lệnh (ECB, CBC, CFB, ...)
            case_file_path = f"./all_test_cases/case_{i}.txt"
            # Tạo tên tệp dựa trên 'mode'
            cipher_file_path = f"./result_linux/case_{i}/case_{i}_cp.txt"
            if "encrypt" in command:
                command = f"./main {command} HEX key_AES.key Text {case_file_path} HEX {cipher_file_path}"

            # In lệnh đang chạy
            f.write(f"\nRunning command: {command}\n")
            # Thực hiện lệnh và chứa output vào một biến
            process = subprocess.Popen(
                command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            output, error = process.communicate()

            # Kiểm tra và ghi kết quả vào file
            if process.returncode == 0:
                f.write("Command executed successfully.\n")
            else:
                f.write("Command execution failed.\n")
            # In output vào file
            # Sử dụng rstrip() để loại bỏ ký tự xuống dòng thừa
            f.write(output.decode().rstrip())
            # In error vào file
            # Sử dụng rstrip() để loại bỏ ký tự xuống dòng thừa
            f.write(error.decode().rstrip())
    print(f"Running Encryption AES-CBC-Manual for case_{i} successfully!")


def run_decrypt_test_cases(i):
    # Danh sách các lệnh để chạy test case
    commands = [
        "decrypt",

    ]

    # Mở file để ghi kết quả
    with open(f"./result_linux/case_{i}/case_{i}_result_decrypt.txt", "w") as f:
        # Thực thi từng lệnh và ghi kết quả vào file
        for command in commands:
            cipher_file_path = f"./result_linux/case_{i}/case_{i}_cp.txt"
            # Tạo tên tệp dựa trên 'mode'
            rcv_file_path = f"./result_linux/case_{i}/case_{i}_rcv.txt"
            if "decrypt" in command:
                command = f"./main {command} HEX key_AES.key HEX {cipher_file_path} Text {rcv_file_path}"


            # In lệnh đang chạy
            f.write(f"\nRunning command: {command}\n")
            # Thực hiện lệnh và chứa output vào một biến
            process = subprocess.Popen(
                command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            output, error = process.communicate()

            # Kiểm tra và ghi kết quả vào file
            if process.returncode == 0:
                f.write("Command executed successfully.\n")
            else:
                f.write("Command execution failed.\n")
            # In output vào file
            # Sử dụng rstrip() để loại bỏ ký tự xuống dòng thừa
            f.write(output.decode().rstrip())
            # In error vào file
            # Sử dụng rstrip() để loại bỏ ký tự xuống dòng thừa
            f.write(error.decode().rstrip())
    print(f"Running Decryption AES-CBC-Manual for case_{i} successfully!")
    print(f"----------------------------------------------------------")


i = 6
run_encrypt_test_cases(i)
# run_decrypt_test_cases(i)
