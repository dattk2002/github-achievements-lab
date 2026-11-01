# 04 — Hai con trỏ tìm cặp có tổng cho trước

Bài `04-two-sum-sorted` trong [curriculum](../../curriculum.json), thực
hiện trong lượt chạy bù ngày 01/11/2026. Ta tận dụng thứ tự của dãy để
loại trừ nhiều cặp ứng viên sau mỗi phép so sánh.

## Hợp đồng

```cpp
std::optional<std::pair<std::size_t, std::size_t>> lab::two_sum_sorted(
    const std::vector<int>& values, long long target);
```

Đầu vào phải **đã sắp xếp tăng không giảm**; hàm không kiểm tra và
không tự sắp xếp. Trả một cặp chỉ số bắt đầu từ 0, `i < j`, có
`values[i] + values[j] == target`; không có cặp thì `std::nullopt`.
Chấp nhận bất kỳ cặp hợp lệ nào khi có nhiều đáp án, không cam kết cặp
nhỏ nhất theo thứ tự từ điển. Đầu vào không bị sửa.

Hai phần tử có thể bằng nhau nhưng phải ở hai vị trí khác nhau. Vì thế
`{4}` với mục tiêu `8` không có đáp án, còn `{4, 4}` có cặp `(0, 1)`.
Vector rỗng hoặc chỉ có một phần tử được trả về ngay.

`target` có thể là bất kỳ giá trị `long long`. Trên nền tảng của repo
với `int` 32 bit và `long long` ít nhất 64 bit, tổng của hai `int` luôn
biểu diễn được bằng `long long`; ép kiểu **trước khi cộng** tránh tràn
`int`. Không tính `target - values[i]`, nên cả mục tiêu cực trị cũng an toàn.

## Thuật toán và tính đúng

Đặt `left = 0`, `right = n - 1`, chỉ lặp khi `left < right`.

- Tổng bằng mục tiêu: trả cặp hiện tại.
- Tổng nhỏ hơn mục tiêu: với phần tử tại `left`, mọi phần tử còn lại
  trong khoảng đều không lớn hơn `values[right]`. Không cặp nào dùng
  `left` có thể đủ tổng, nên tăng `left`.
- Tổng lớn hơn mục tiêu: mọi phần tử còn lại đều không nhỏ hơn
  `values[left]`. Không cặp nào dùng `right` có thể đạt tổng, nên giảm `right`.

Bất biến: nếu có đáp án chưa bị tìm thấy thì một cặp như vậy vẫn nằm
giữa hai biên hiện tại. Mỗi bước chỉ loại bỏ một đầu đã chứng minh không
thể góp vào đáp án. Khi hai biên gặp nhau, không còn hai chỉ số phân biệt.
Kiểm tra kích thước trước khi tính `n - 1` tránh tràn dưới với vector rỗng.

**Độ phức tạp:** `O(n)` thời gian, `O(1)` bộ nhớ phụ. Mỗi bước dịch
một biên vào trong; không có vòng lặp duyệt lại toàn bộ phần còn lại.

## Ví dụ tự chạy

Đặt `example.cpp` cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>

int main() {
    const auto pair = lab::two_sum_sorted({-8, -3, 1, 6, 9}, -2);
    if (pair) std::cout << pair->first << ' ' << pair->second << '\n';
    std::cout << lab::two_sum_sorted({4}, 8).has_value() << '\n';
}
```

Chạy `g++ -std=c++17 example.cpp -o /tmp/two-sum-example` rồi
`/tmp/two-sum-example`: kết quả `0 3` rồi `0`. Cặp thứ nhất dùng
`-8 + 6 = -2`. Với dãy trên và mục tiêu `4`, không có cặp hợp lệ.

## Kiểm thử

Từ gốc repo: `make test`, hoặc chạy riêng:

```sh
g++ -std=c++17 -DNDEBUG -Wall -Wextra -Werror -pedantic lessons/04-two-sum-sorted/test.cpp -o /tmp/two-sum-test
/tmp/two-sum-test
```

Kiểm thử bao phủ rỗng, một phần tử không được tái sử dụng, phần tử
trùng, toàn số 0, số âm, cặp ở hai đầu, không có đáp án và tổng vượt
giới hạn `int`. Mục tiêu `LLONG_MIN`/`LLONG_MAX` phải trả không thấy.
Các vector độ dài 0–6 sinh từ `{-2, -1, 0, 1}` được sắp xếp rồi đối
chiếu với thuật toán duyệt mọi cặp `O(n²)`. Kiểm thử xác minh sự tồn tại,
chỉ số, tổng và đầu vào không đổi; không ép hàm chọn một đáp án cụ thể.
Lỗi trả mã thoát khác 0 dù có `NDEBUG`.

## Tự luyện

1. Tại sao không được dịch cả hai biên khi tổng nhỏ hơn mục tiêu?
   Tìm một phản ví dụ.
2. Nếu đầu vào chưa sắp xếp nhưng phải trả chỉ số gốc, hãy so sánh cách
   dùng bảng băm với sắp xếp các cặp `(giá trị, chỉ số)`.
3. Yêu cầu đếm mọi cặp chỉ số thay vì tìm một cặp thay đổi cách xử lý
   phần tử trùng như thế nào? Bắt đầu với `{2, 2, 2, 2}` và mục tiêu `4`.
