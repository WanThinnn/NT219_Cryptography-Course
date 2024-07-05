import re

def calculate_mode_times(file_path):
    mode_times = {}
    with open(file_path, "r") as file:
        for line in file:
            algo_match = re.search(r"algo: (\w+)", line)
            if algo_match:
                current_algo = algo_match.group(1)
                mode_times.setdefault(current_algo, 0)
            else:
                time_match = re.search(r"Hashing time: (\d+) milliseconds", line)
                if time_match and current_algo:
                    time = int(time_match.group(1))
                    mode_times[current_algo] += time

    return mode_times

def calculate_avg_times(mode_times, num_runs=1000):
    avg_times = {mode: total_time / num_runs for mode, total_time in mode_times.items()}
    return avg_times

def process_file(file_path):
    mode_times = calculate_mode_times(file_path)
    avg_times = calculate_avg_times(mode_times)

    return mode_times, avg_times

def save_results(file_path, output_file_path):
    mode_times, avg_times = process_file(file_path)
    
    with open(output_file_path, "w") as output_file:
        output_file.write("Total Hashing Times:\n")
        for mode, total_time in mode_times.items():
            output_file.write(f"{mode}: {total_time} milliseconds\n")

        output_file.write("\nAverage Hashing Times (over 1000 runs):\n")
        for mode, avg_time in avg_times.items():
            output_file.write(f"{mode}: {avg_time} milliseconds\n")




# Đường dẫn tới file của bạn
i = 5
intput_file_path = f"result/case_{i}/case_{i}_result_hashes.txt"
output_file_path = f"result/case_{i}/case_{i}_result_hashes_sumtime.txt"

save_results(intput_file_path, output_file_path)

print(f"Results saved to {output_file_path}")

