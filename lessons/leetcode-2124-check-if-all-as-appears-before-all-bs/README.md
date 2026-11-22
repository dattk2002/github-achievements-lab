# LeetCode 2124 — Kiểm tra thứ tự của các ký tự a và b

Ngày nguồn (`source_date`) **2026-11-22**. Độ khó **Easy**.
[Đề bài gốc trên LeetCode](https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/)

## Hợp đồng

`bool lab::Solution::checkString(std::string s)` trả về `true` nếu chuỗi
gồm một đoạn toàn `a` nối tiếp một đoạn toàn `b`. Mỗi đoạn có thể rỗng,
nên chuỗi chỉ chứa một loại ký tự cũng hợp lệ.

Tiền điều kiện là `1 <= s.size() <= 100` và mỗi ký tự là `a` hoặc `b`.

## Thuật toán và tính đúng đắn

Duyệt chuỗi từ trái sang phải với cờ `seen_b` ban đầu bằng `false`.
Gặp `b` thì đặt cờ thành `true`. Gặp `a` khi cờ đã bật thì trả về
`false` ngay. Nếu duyệt hết chuỗi, trả về `true`.

Trước khi xét mỗi ký tự, cờ cho biết phần đã duyệt có chứa `b` hay
không. Nếu cờ đã bật khi xét một ký tự `a`, ký tự đó đứng sau ít nhất
một `b`, đủ để kết luận sai thứ tự. Nếu tồn tại bất kỳ cặp sai thứ tự
nào, lượt duyệt sẽ phát hiện vi phạm muộn nhất khi đến ký tự `a` của
cặp đó.

Với `n = s.size()`, lượt duyệt tốn **O(n)** thời gian trong trường hợp
xấu nhất và **O(1)** bộ nhớ phụ. Giao diện nhận chuỗi theo giá trị nên
khi truyền một biến chuỗi, việc sao chép đối số tốn thêm **O(n)** thời
gian và bộ nhớ.

## Ví dụ và cách chạy

Đặt chương trình ví dụ cạnh `lesson.hpp` và biên dịch với C++17.

```cpp
#include "lesson.hpp"
#include <iostream>

int main() {
    lab::Solution solution;
    std::cout << std::boolalpha
              << solution.checkString("aabbbb") << '\n'
              << solution.checkString("abbaab") << '\n';
}
```

Dòng đầu in `true` vì hai ký tự `a` đến trước cả bốn ký tự `b`.
Dòng sau in `false` vì ký tự `a` ở chỉ số 3 đứng sau ký tự `b` ở chỉ
số 1, tính từ 0.

Chạy toàn bộ kiểm thử từ thư mục gốc bằng `make test`. Để chạy riêng
bài này với `NDEBUG`, chạy trong thư mục bài học.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lesson-2124-test
/tmp/lesson-2124-test
```

## Kiểm thử

Bộ kiểm thử dùng 11 đáp án xác định trực tiếp từ vị trí các ký tự.
Chuỗi một ký tự và chuỗi đồng nhất kiểm tra trường hợp một trong hai
đoạn rỗng. Cặp `ab` và `ba` kiểm tra hai thứ tự có thể có với đúng một
ký tự mỗi loại. Các chuỗi dài 100 ký tự kiểm tra một thứ tự hợp lệ và
hai vi phạm được phát hiện ở đầu hoặc cuối lượt duyệt. Khi kết quả sai,
bộ kiểm thử in đầu vào, giá trị mong đợi và giá trị thực tế, rồi thoát
với mã khác 0 ngay cả khi định nghĩa `NDEBUG`.

## Bài tập

1. Chứng minh rằng một chuỗi sai thứ tự luôn chứa hai ký tự liền kề
   `ba`. Viết một lời giải dựa trên nhận xét đó.
2. Sửa thuật toán để trả về chỉ số của ký tự `a` đầu tiên đứng sau một
   ký tự `b`, hoặc `-1` nếu chuỗi hợp lệ. Thêm ca kiểm thử cho cả hai
   loại kết quả.
