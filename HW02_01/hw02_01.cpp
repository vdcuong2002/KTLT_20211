/*
Chương trình viết 1 số có 40 chữ số theo dãy Fibonacci
Người viết: Vũ Đức Cường        MSSV: 20202313
Viện Điện - Trường Điện - Điện tử
Ngày chỉnh sửa cuối cùng: 18/11/2021
Giải thích thuật toán: Tạo ra 3 mảng hoạt động liên tục, chạy xuyên suốt cảm hàm.
VD: arr1 -> số thứ nhất     arr2 -> số thứ 2      arr3 - > bằng 0
Cộng arr1 và arr2 lại sẽ được arr3
Khi đó gán số thứ 2 thành arr1, và gán số thứ 3 thành arr3, reset lại số thứ 3 bằng 0
Làm tương tự, lặp đi lặp lại
*/

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <math.h>

int arr1[40];                                                       // Khởi tạo các mảng là các biến toàn cục chạy
int arr2[40];                                                       // trong toàn bộ chương trình đó là các số n-2;
int arr3[40];                                                       // n-1; n trong dãy Fibonacci

void Fibonacci(int part);                                           // Hàm để cộng các mảng như các số bình thường

int main()
{
    for (int i = 0; i  < 40; i++)
    {
        arr1[i] = 0; arr2[i] = 0; arr3[i] = 0;                      // Khởi tạo tất cả các giá trị ban đầu là 0
    }
    arr2[39] = 1;

    int n;
    std::cout << "Enter your numer: " ;
    std::cin >> n;
    std::cout << "Please Wait a moment . . ." << std::endl;         // Một số dòng rườm rà để làm cho chương trình ngầu hơn
    sleep(1);
    std::cout << "OK, done!" << std::endl;
    sleep(1);                                                       // Một số dòng cout rườm rà
    std::cout << std::setw(12) << std::left << "n" << std::setw(40) << std::left << "F(n)" << std::endl;

    for (int i = 0; i < n; i++)
    {
        std::cout << std::setw(5) << std::left << i + 1;            // Một số dòng set để in ra màn hình
        std::cout << std::setw(7) << std::left << "-";
        Fibonacci(1);                                               // Gọi hàm cộng và đồng thời in ra màn hình
        std::cout << std::endl;
    }

    std::cout << std::endl << "Next . . ." << std::endl;            // Phần 2 chương trình, nhập số để tìm Fibonacci cuối 
    std::cout << "Enter a number (<2.147.483.647): ";               // cùng mà nhỏ hơn số nhập vào
    std::cin >> n;                                                  // tận dụng lại bộ nhớ
    std::cout<< "Wait . . ." << std::endl;
    for (int i = 0; i  < 40; i++)
    {
        arr1[i] = 0; arr2[i] = 0; arr3[i] = 0;                      // Khởi tạo tất cả các giá trị ban đầu là 0
    }
    arr2[39] = 1;                                                   // Khởi tạo số thứ 2 là 00...01
    int value_of_number = 0, ans = 0;
    while (value_of_number < n)
    {
        ans = value_of_number;                                      // Lưu lại biến từ trước, để xuất ra kết quả
        Fibonacci(0);                                               // Gọi hàm cộng nhưng không in
        value_of_number = 0;
        for (int i = 0; i  < 40; i++)
        {
            value_of_number += arr1[i]*pow(10, 39-i);               // Chuyển arr thành 1 số cụ thể để so sánh
        } 
    }
    
    std::cout << "The last number in the sequence is: " << ans << std::endl;
                                                                    // xuất kết quả là ans
}

void Fibonacci(int part)
{
    for (int k = 40 - 1; k >= 0; k--)                               // Cộng 2 số (mảng) 1 và 2 theo cách cộng của học sinh tiểu học
    {
        if (arr1[k] + arr2[k] + arr3[k] >= 10)                      // Nếu là phép cộng có dư
        {
            arr3[k] += (arr1[k] + arr2[k] - 10);                    // Làm theo tính chất của phép cộng có dư
            arr3[k - 1] += 1;
        }
        else                                                        // Không dư
        {
            arr3[k] += (arr1[k] + arr2[k]);
        }
    }

    bool write = false;                                             // Hàm để in ra con số đó
    for (int j = 0; j < 40; j++)
    {
        if (arr1[j] > 0 || j == 39)
            write = true;                                           // Khi dò từ 1 -> 40, nếu gặp số khác 0 là bắt đầu in
        if (write && part == 1)
            std::cout << arr1[j];
        arr1[j] = arr2[j];                                          // Gán các mảng ngược trở lại, 2 thành 1, 3 thành 2
        arr2[j] = arr3[j];
        arr3[j] = 0;                                                // Reset lại mảng 3
    }
}