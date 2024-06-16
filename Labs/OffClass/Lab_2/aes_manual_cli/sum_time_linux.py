# import re
import re
def  calculate_total_encryption_time(file_path):
    total_time = 0
    with open(file_path, "r") as file:
        for line in file:
            match = re.search(r"Encryption time: (\d+) milliseconds", line)
            if match:
                time = int(match.group(1))
                total_time += time
    return total_time

def calculate_total_decryption_time(file_path):
    total_time = 0
    with open(file_path, "r") as file:
        for line in file:
            match = re.search(r"Decryption time: (\d+) milliseconds", line)
            if match:
                time = int(match.group(1))
                total_time += time
    return total_time

def calculate_enc_mode_times(file_path, num_runs=8):
    mode_times = {}
    current_mode = None
    mode_counts = {}
    with open(file_path, "r") as file:
        for line in file:
            mode_match = re.match(r"Mode: (\w+)", line)
            if mode_match:
                current_mode = mode_match.group(1)
                mode_times.setdefault(current_mode, 0)
                mode_counts.setdefault(current_mode, 0)
            else:
                time_match = re.search(r"Encryption time: (\d+) milliseconds", line)
                if time_match and current_mode:
                    time = int(time_match.group(1))
                    mode_times[current_mode] += time
                    mode_counts[current_mode] += 1
                    if mode_counts[current_mode] == num_runs:
                        mode_counts[current_mode] = 0
    return mode_times

def calculate_dec_mode_times(file_path, num_runs=8):
    mode_times = {}
    current_mode = None
    mode_counts = {}
    with open(file_path, "r") as file:
        for line in file:
            mode_match = re.match(r"Mode: (\w+)", line)
            if mode_match:
                current_mode = mode_match.group(1)
                mode_times.setdefault(current_mode, 0)
                mode_counts.setdefault(current_mode, 0)
            else:
                time_match = re.search(r"Decryption time: (\d+) milliseconds", line)
                if time_match and current_mode:
                    time = int(time_match.group(1))
                    mode_times[current_mode] += time
                    mode_counts[current_mode] += 1
                    if mode_counts[current_mode] == num_runs:
                        mode_counts[current_mode] = 0
    return mode_times


# Thay đường dẫn tới file của bạn vào hàm calculate_mode_times
def get_enc_file_path(case_i):
    return f"./result_linux/case_{case_i}/case_{case_i}_result_encrypt.txt"

def get_dec_file_path(case_i):
    return f"./result_linux/case_{case_i}/case_{case_i}_result_decrypt.txt"



def show_result(i):
    file_path = f"./result_linux/case_{i}/sum_time_case_{i}.txt"    
    with open(file_path, "w") as f:
        enc_file = get_enc_file_path(i)
        mode_times = calculate_enc_mode_times(enc_file)
        f.write(f"- File: {enc_file}\n")
        
        total_time = calculate_total_encryption_time(enc_file)
        f.write(f"- Total encryption time: {total_time/1000} seconds\n")
        f.write(f"- AVG encryption time: {total_time/(1000*10000)} seconds ~ {total_time/(1000*10)} miliseconds\n\n\n")


        dec_file = get_dec_file_path(i)
        mode_times = calculate_dec_mode_times(dec_file)
        f.write(f"- File: {dec_file}\n")
       
        total_time = calculate_total_decryption_time(dec_file)
        f.write(f"- Total decryption time: {total_time/1000} seconds\n")
        f.write(f"- AVG decryption time: {total_time/(1000*10000)} seconds ~ {total_time/(1000*10)} miliseconds\n")
    print(f"Export time for each mode in test case {i} successfully!")


test_case = 6
show_result(test_case)