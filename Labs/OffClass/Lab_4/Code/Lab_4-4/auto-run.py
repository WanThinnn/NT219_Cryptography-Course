import subprocess

def run_hashpump(current_hash, original_data, additional_data, key_length):
    # Lệnh hashpump
    command = [
        "./hashpump",
        "-s", current_hash,
        "-d", original_data,
        "-a", additional_data,
        "-k", str(key_length)
    ]
    result = subprocess.run(command, capture_output=True, text=True)
    return result.stdout.strip()

# Thông số ban đầu
current_hash = "a4d7ed376e1dba151591d9f643a6e82948aee654"
original_data = "xin-chao-the-gioi"
additional_data = "con-meo-de-thuong-qua"
key_length = 16

# Thực hiện tấn công
output = run_hashpump(current_hash, original_data, additional_data, key_length)
print(output)
