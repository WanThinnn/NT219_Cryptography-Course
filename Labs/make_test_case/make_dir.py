import os
import random
import shutil

# Tên thư mục chứa các tệp kiểm tra
result_dir = 'result/case_1'


# Tạo thư mục chứa các tệp kiểm tra nếu chưa tồn tại
if not os.path.exists(result_dir):
    os.makedirs(result_dir)
