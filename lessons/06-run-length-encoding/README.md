# 06 — Mã hóa theo đoạn liên tiếp (RLE)

Bài dự phòng `06-run-length-encoding` trong `curriculum.json`, chạy bù có giám sát ngày 2026-11-02 cho lịch 09:00. Đây là bài tự xây dựng theo curriculum, không gán ngày LeetCode Daily.

## Hợp đồng

```cpp
std::vector<std::pair<char, std::size_t>> lab::encode_runs(std::string_view input);
std::string lab::decode_runs(const std::vector<std::pair<char, std::size_t>>& runs);
```

Dữ liệu là **byte**, không phải ký tự Unicode. Mỗi cặp lưu giá trị byte và số lần lặp liên tiếp. `encode_runs` tạo các run có độ dài dương; hai run cạnh nhau luôn khác byte. Chuỗi rỗng cho vector rỗng. Hàm không sửa đầu vào và không giữ `string_view` sau khi trả về.

`decode_runs` nhận cả các run cùng byte liền nhau, ví dụ `{{'k', 1}, {'k', 2}}` thành `"kkk"`. Run độ dài 0 bị từ chối bằng `std::invalid_argument`. Nếu kích thước giải mã vượt `std::string::max_size()`, hàm ném `std::length_error` trước khi cấp phát chuỗi kết quả. Kích thước hợp lệ vẫn có thể quá lớn so với RAM và gây `std::bad_alloc`; đây không phải cam kết có thể giải mã mọi số đếm biểu diễn được.

Không dùng dấu phân cách hay quy ước ký tự kết thúc, nên chữ số, dấu câu và byte null đều được giữ chính xác. Kết quả là cấu trúc trong bộ nhớ, chưa phải định dạng file nén. RLE có thể tốn nhiều bộ nhớ hơn chuỗi gốc khi các byte thay đổi liên tục.

## Thuật toán và bất biến

Duyệt từng byte. Nếu vector chưa có run hoặc byte khác run cuối, thêm run mới với độ dài 1; nếu giống, tăng số đếm run cuối. Sau mỗi bước, giải mã các run đã tạo khôi phục đúng tiền tố đã duyệt, và run cuối chứa toàn bộ đoạn cùng byte ở cuối tiền tố đó. Do đó kết quả đầy đủ và không có hai run kề nhau cùng byte.

Giải mã dùng hai lượt: kiểm tra từng số đếm và cộng tổng bằng điều kiện `count > max_size - total` để tránh tràn số, rồi `reserve(total)` và nối từng run. Duyệt theo độ dài của `string_view` thay vì chờ byte null.

## Độ phức tạp

Với `n` byte, `r` run và `N` byte sau giải mã:

- Mã hóa: O(n) thời gian khấu hao, O(r) bộ nhớ kết quả; O(1) bộ nhớ phụ ngoài kết quả.
- Giải mã: O(r + N) thời gian, O(N) bộ nhớ kết quả và O(1) bộ nhớ phụ.

## Ví dụ chạy được

Lưu thành `/tmp/rle-example.cpp`, chạy từ thư mục gốc repo:

```cpp
#include "lessons/06-run-length-encoding/lesson.hpp"
#include <iostream>
int main() {
    const std::string text = "ppppqqp";
    const auto runs = lab::encode_runs(text);
    for (const auto& run : runs) std::cout << run.first << ':' << run.second << ' ';
    std::cout << '\n' << lab::decode_runs(runs) << '\n';
    const std::string binary("a\0\0", 3);
    std::cout << (lab::decode_runs(lab::encode_runs(binary)) == binary) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/rle-example.cpp -o /tmp/rle-example
/tmp/rle-example
```

Kết quả:

```text
p:4 q:2 p:1
ppppqqp
1
```

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/06-run-length-encoding/test.cpp -o /tmp/rle-test
/tmp/rle-test
make test
```

Test dùng điều kiện kiểm tra và `exit(1)`, không dựa vào `assert`. Có kiểm tra run chính xác, chuỗi rỗng, run cùng byte kề nhau, byte null/0xff, đủ 256 giá trị byte, run 100.000 byte, độ dài 0 và tổng quá lớn. 4.096 chuỗi nhị phân độ dài 12 kiểm tra khôi phục và cấu trúc run trực tiếp, giảm nguy cơ hai hàm cùng sai nhưng vẫn roundtrip thành công.

## Bài tập

1. Tính ngưỡng nào RLE có lợi nếu mỗi run tốn một byte dữ liệu và tám byte số đếm; vì sao kích thước thực tế của `pair` có thể khác?
2. Thiết kế bộ giải mã streaming với giới hạn đầu ra do người gọi đặt. Không cần cấp phát toàn bộ chuỗi.
3. Nếu muốn mã hóa theo ký tự Unicode thay vì byte UTF-8, hợp đồng và bộ kiểm thử phải đổi thế nào?
