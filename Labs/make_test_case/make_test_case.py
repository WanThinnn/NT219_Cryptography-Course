import os
import random
import shutil

# Hàm đọc nội dung từ tệp văn bản với mã hóa được chỉ định
def read_text_file(file_path, encoding='utf-8'):
    with open(file_path, 'r', encoding=encoding) as file:
        return file.read().split()



# Hàm tạo tệp kiểm tra với kích thước xác định
def create_test_case(words, size, output_file, i):
    with open(output_file, 'w', encoding='utf-8') as file:
        total_size = 0
        while total_size < size:
            word = random.choice(words)
            word_size = len(word.encode('utf-8')) + len(' ')  # Độ dài của từ và một dấu cách
            if total_size + word_size <= size:
                file.write(word + ' ')
                total_size += word_size
            else:
                break
    print(f'Test cases {i}: size bytes created successfully!.')


# Tệp văn bản chứa tiếng Việt
vietnam_file = './vietnamese.txt'
# Tệp văn bản chứa tiếng Anh
english_file = './english.txt'
# Tên thư mục chứa các tệp kiểm tra
test_cases_dir = 'all_test_cases'

# Đọc từ hai tệp văn bản
vietnamese_words = read_text_file(vietnam_file, encoding='utf-8')
english_words = read_text_file(english_file, encoding='latin-1')

# Kết hợp các từ từ hai danh sách thành một danh sách tổng hợp
combined_words = vietnamese_words + english_words

# # Tạo thư mục chứa các tệp kiểm tra nếu chưa tồn tại
# if not os.path.exists(test_cases_dir):
#     os.makedirs(test_cases_dir)


create_test_case(combined_words, 10**3, f'{test_cases_dir}/case_1.txt', 1) #1 KB
create_test_case(combined_words, 10**4, f'{test_cases_dir}/case_2.txt', 2) #10 KB
create_test_case(combined_words, 5*10**4, f'{test_cases_dir}/case_3.txt', 3) #50 KB
create_test_case(combined_words, 10**5, f'{test_cases_dir}/case_4.txt', 4) #100 KB
create_test_case(combined_words, 10**6, f'{test_cases_dir}/case_5.txt', 5) #1 MB
create_test_case(combined_words, 5*10**6, f'{test_cases_dir}/case_6.txt', 6) #5 MB
# create_test_case(combined_words, 5*10**7, f'{test_cases_dir}/case_7.txt', 7) #50 MB
# create_test_case(combined_words, 10**8, f'{test_cases_dir}/case_8.txt', 8) #100 MB

