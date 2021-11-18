/*
Chương trình chuyển đổi 1 số thực được nhập từ bàn phím
sang mã nhị phân 32bits theo tiêu chuẩn IEEE-754
Người viết: Vũ Đức Cường       MSSV: 20202313
Viện Điện, trường Điện - Điện tử
Ngày chỉnh sửa cuối cùng: 11/17/2021
*/

#include <iostream>
#include <math.h>
#include <string.h>
#include <unistd.h>

void num2S(float input_number);                                     // Hàm chuyển từ số sang chuỗi S
void num2E(float input_number);                                     // Hàm chuyển từ số sang chuỗi E
void num2M(float input_number);                                     // Hàm chuyển từ số sang chuỗi M

int main()
{
    float input_number;
    std::cout << "Your number: ";
    std::cin >> input_number;
    std::cout << "Please wait a moment . . ." << std::endl;
    sleep(1);
    std::cout << "OK done! " << std::endl;
    sleep(1);
    std::cout << "Answer: " << std::endl; 
    std::cout << "------- " << std::endl; 
    num2S(input_number);
    num2E(input_number);
    num2M(input_number);
    std::cout << std:: endl << "- --------------- ---------------------------------------------";
    std::cout << std:: endl << "S      E                                 M                     " << std::endl;
    system("pause");
}

void num2S(float input_number)                                      // Mảng của phần S
{
    if (input_number > 0)
        std::cout << "0 ";                                          // Nếu số dương thì xuất ra 0
    else
        std::cout << "1 ";                                          // Nếu số âm thì xuất ra 1
}

void num2E(float input_number)                                      // Mảng của phần E
{
    input_number = abs(input_number);
    int e = 127 +  (int)(log((int)input_number)/log(2));            // Tính số e
    int arrE[8];
    for (int i = 7; i >= 0; i--){
        if (e <= 0)
        {
            arrE[i] = 0;                                            // Thuật toán chuyển từ 1 số nguyên sang dãy nhị phân
        }
        else
        {
            arrE[i] = e / pow(2,i);                                 // Giá trị của arr chỉ có thể là 0, hoặc 1
        }                                                           // nên ta sẽ chạy 1 vòng for để trừ dần, viết từng bit một
        e = e - arrE[i]*pow(2,i);                            
    }
    for (int i = 7; i >= 0; i--)
        std::cout << arrE[i] << " ";                                // Chuỗi tạo ra bị ngược so với chuỗi đúng, nên ta sẽ đảo ngược nó lại
}

void num2M(float input_number)                                      // Mảng của phần M
{
    input_number = abs(input_number);
    int int_part = input_number;                                    // Chuyển đổi phần nguyên sang nhị phân
    int len_arrInt = (int)(log(int_part)/log(2)) + 1;               // Độ dài của dãy nhị phân bằng phân nguyên 
    int arrInt[len_arrInt], inverted_arrInt[len_arrInt];            // của log cơ số 2 số đó cộng thêm với 1
    for (int i=len_arrInt-1; i>=0; i--){
        if (int_part <= 0)
            arrInt[i] = 0;                                          // Thuật toán chuyển từ 1 số nguyên sang dãy nhị phân
        else
            arrInt[i] = int_part / pow(2,i);                        // Giá trị của arr chỉ có thể là 0, hoặc 1
                                                                    // nên ta sẽ chạy 1 vòng for để trừ dần, viết từng bit một
        int_part = int_part - arrInt[i]*pow(2,i);                            
    }
    for (int i = len_arrInt - 1; i >= 0; i--)
        inverted_arrInt[len_arrInt - 1 - i] = arrInt [i];           // Chuỗi tạo ra bị ngược so với chuỗi đúng, nên ta sẽ đảo ngược nó lại

    float dec_part = input_number - int(input_number);              // Chuyển đổi số phần thập phân
    int len_arrDec = 32 - 8 - 1 - ( len_arrInt - 1);                // Độ dài của dãy thập phân
    int arrDec[len_arrDec];                                         // Chuỗi của dãy thập phân
    for (int i = 0; i < len_arrDec; i++)
    {
        dec_part = dec_part * 2;                                    // Thuật toán chuyển đổi phần dãy thập phân
        if (dec_part < 1)                                           // Ex: 0.6875*2 = 1.375 > 1      -> bit 1
        {                                                           // (1.375 - 1) * 2 = 0.75 < 1    -> bit 0
            arrDec[i] = 0;                                          // (0.75 * 2) = 1.5 > 1          -> bit 1
        }                                                           // (1.5 - 1) * 2  = 1            -> bit 1 ...     
        else
        {
            arrDec[i] = 1;
            dec_part = dec_part - 1;
        }
    }

    int result[24];                                                 // Ghép nối chuỗi bằng hàm memcpy trong thư viện string.h
    memcpy(result, inverted_arrInt, sizeof(inverted_arrInt));  
    memcpy(&result[len_arrInt], arrDec, sizeof(arrDec)); 

    for (int i = 1; i < 24; i++)
        std::cout << result[i] << " ";                              // Xuất mảng, mỗi phần tử các nhau 1 space
}