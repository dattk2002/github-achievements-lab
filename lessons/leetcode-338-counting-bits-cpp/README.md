# LeetCode 338 — Counting Bits (C++17)

Nguồn: [Counting Bits trên LeetCode](https://leetcode.com/problems/counting-bits/),
độ khó Easy. Nội dung giảng giải, ví dụ và kiểm thử được tự viết.

## Hợp đồng

`lab::Solution::countBits(int n)` trả `std::vector<int>` dài `n + 1`.
Phần tử thứ `i` là số bit 1 trong biểu diễn nhị phân của `i`, gồm cả số 0.
Mỗi lần gọi trả một vector độc lập. Không dùng hàm đếm bit dựng sẵn.

Nguồn giới hạn `0 <= n <= 100000`. Số âm gây `std::invalid_argument`;
giới hạn trên là tiền điều kiện, không được kiểm tra. Việc cấp phát phải
nằm trong khả năng của hệ thống.

## Quy hoạch động theo bit cuối

Với `i > 0`, bỏ bit cuối bằng `i >> 1`. Phần còn lại nhỏ hơn `i`, nên
kết quả của nó đã có. Bit vừa bỏ bằng `i & 1`:

```text
counts[0] = 0
counts[i] = counts[i >> 1] + (i & 1)
```

Chứng minh bằng quy nạp: cơ sở 0 không có bit 1. Giả sử mọi số nhỏ hơn
`i` đã đúng. Các bit của `i` gồm các bit của `i >> 1` nối thêm bit cuối,
nên công thức đếm đúng từng bit đúng một lần. Duyệt tăng dần bảo đảm phụ
thuộc đã được tính trước. Dùng `std::size_t` cho kích thước và chỉ số;
chuyển `n` sang kiểu đó trước khi cộng 1.

Ví dụ `6 = 110₂` lấy kết quả của `3 = 11₂` cộng 0, được 2. `7 = 111₂`
lấy kết quả của 3 cộng 1, được 3; `8 = 1000₂` lại chỉ có một bit 1.

## Độ phức tạp

`O(n + 1)` thời gian và dung lượng kết quả; `O(1)` bộ nhớ phụ ngoài vector
trả về. Đếm lại từng bit của từng số sẽ tốn `O(n log n)` thời gian.

## Ví dụ chạy được

Lưu thành `/tmp/lc338-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
int main() {
    for (int count : lab::Solution{}.countBits(8)) std::cout << count << ' ';
    std::cout << '\n'; // 0 1 1 2 1 2 2 3 1
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-338-counting-bits-cpp /tmp/lc338-example.cpp -o /tmp/lc338-example
/tmp/lc338-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-338-counting-bits-cpp/test.cpp -o /tmp/lc338-test
/tmp/lc338-test
make test
make test-all
```

## Biên và kiểm thử

Kiểm tra toàn bộ vector của mỗi `n` từ 0 tới 256 và của `n = 100000`.
Oracle chia từng số cho 2, đếm số dư 1 từ đầu, không tái sử dụng bảng DP.
Ca cố định qua ranh giới `7 -> 8` bắt lỗi số lẻ/chẵn và lũy thừa của 2.
Có kiểm tra số âm và thay đổi kết quả một lần gọi không ảnh hưởng lần
gọi sau. Mọi lỗi trả mã thoát khác 0 ngay cả khi định nghĩa `NDEBUG`.

## Bài tập

1. Chứng minh công thức `counts[i] = counts[i & (i - 1)] + 1`.
2. Tính tổng số bit 1 trong toàn bộ khoảng `[0, n]`.
3. Nếu chỉ cần đếm một số thay vì cả khoảng, lựa chọn thuật toán đổi ra sao?
