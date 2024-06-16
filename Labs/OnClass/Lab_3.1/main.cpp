#include <iostream>

int main(int argc, char* argv[]) {
    // Kiểm tra số lượng đối số dòng lệnh
    if (argc != 4) {
        std::cerr << "Sử dụng: " << argv[0] << " <số thứ nhất> <số thứ hai> <số thứ ba>" << std::endl;
        return 1;
    }

    // Lấy các đối số từ dòng lệnh và chuyển đổi sang kiểu số nguyên
    int num1 = std::stoi(argv[1]);
    int num2 = std::stoi(argv[2]);
    int num3 = std::stoi(argv[3]);

    // Tính tổng của 3 số
    int sum = num1 + num2 + num3;

    // Xuất kết quả
    std::cout << "Tổng của 3 số là: " << sum << std::endl;

    return 0;
}
