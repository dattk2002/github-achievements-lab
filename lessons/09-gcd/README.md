# 09 — Ước chung lớn nhất bằng thuật toán Euclid

Bài dự phòng `09-gcd` trong `curriculum.json`, chạy bù có giám sát ngày 2026-11-02 cho lịch 09:00.

## Hợp đồng

```cpp
unsigned long long lab::gcd(unsigned long long a, unsigned long long b);
```

Trả ước chung lớn nhất của hai số không âm, với quy ước `gcd(0, 0) = 0`. Nếu chỉ một số bằng 0, trả số còn lại. Hàm nhận tham số theo giá trị và không có tác dụng phụ. Không chuyển sang số có dấu; xử lý được toàn miền `unsigned long long`, kể cả giá trị lớn nhất.

Đầu vào không bao gồm số âm. Không tự chuyển số âm sang kiểu không dấu để tính GCD vì sẽ thay đổi giá trị bài toán.

## Thuật toán và bất biến

Lặp khi `b != 0`: tính `remainder = a % b`, rồi thay `(a, b)` bằng `(b, remainder)`. Khi `b == 0`, trả `a`. Kiểm tra điều kiện vòng lặp trước phép `%` nên không có chia cho 0.

Với `a = q*b + r`, một số chia hết cả `a` và `b` khi và chỉ khi nó chia hết cả `b` và `r`: từ hai số biết được số còn lại qua phép cộng/trừ bội. Vì vậy `gcd(a, b) = gcd(b, a % b)` là bất biến.

Mỗi lượt có `0 <= remainder < b`, nên đối số thứ hai giảm nghiêm ngặt trong các số tự nhiên cho tới 0. Khi đó ước chung lớn nhất là đối số thứ nhất. Trường hợp cả hai số bằng 0 bỏ qua vòng lặp và trả đúng quy ước 0.

Ví dụ tự tính: `(84, 30) -> (30, 24) -> (24, 6) -> (6, 0)`, kết quả 6. Không dùng vòng lặp trừ liên tiếp: `(ULLONG_MAX, 1)` chỉ cần một phép chia dư.

## Độ phức tạp

Với số nguyên kích thước máy cố định và xem phép chia dư là O(1): O(log(min(a, b) + 1)) bước khi hai số dương, O(1) nếu có số 0; O(1) bộ nhớ phụ. Trong tối đa hai lượt, số chia dương giảm ít nhất một nửa, dẫn tới giới hạn logarit. Các số Fibonacci liên tiếp tạo nhiều bước nên là ca kiểm thử hữu ích. Với số nguyên tùy ý độ dài, phải tính thêm chi phí phép chia theo số bit.

## Ví dụ chạy được

Lưu thành `/tmp/gcd-example.cpp`, chạy ở gốc repo:

```cpp
#include "lessons/09-gcd/lesson.hpp"
#include <iostream>
int main() {
    std::cout << lab::gcd(84, 30) << '\n';
    std::cout << lab::gcd(0, 27) << '\n';
    std::cout << lab::gcd(0, 0) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/gcd-example.cpp -o /tmp/gcd-example
/tmp/gcd-example
```

Kết quả:

```text
6
27
0
```

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/09-gcd/test.cpp -o /tmp/gcd-test
/tmp/gcd-test
make test
```

Kiểm tra kết quả tính tay, hai số 0, một số 0 ở cả hai vị trí, bằng nhau, nguyên tố cùng nhau và chia hết. Đối chiếu `std::gcd` trên toàn bộ 63.001 cặp trong `[0, 250]`, thêm các cặp chứa cực trị không dấu và cặp Fibonacci lớn nhất sinh được mà không tràn. Ca cực lớn với số 1 giúp phát hiện thuật toán trừ liên tiếp quá chậm. Test dùng kiểm tra trả mã lỗi, không dựa vào `assert`.

## Bài tập

1. Ghi các cặp trạng thái khi tính `gcd(144, 54)` và giải thích mỗi bước bảo toàn ước chung.
2. Tính LCM từ GCD nhưng chia trước khi nhân và phát hiện tràn kiểu không dấu; xử lý số 0.
3. Mở rộng Euclid để tìm hệ số Bézout: cần cân nhắc kiểu số nào cho các hệ số âm và tràn trung gian?
