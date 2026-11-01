# 02 — Tìm kiếm tuyến tính và đếm phép so sánh

Đây là bài `02-linear-search` trong [curriculum của repo](../../curriculum.json),
được thực hiện trong lượt chạy bù ngày 01/11/2026. Bài rèn cách diễn đạt
chi phí thuật toán bằng một đại lượng quan sát được.

## Hợp đồng

```cpp
lab::SearchResult lab::linear_search(const std::vector<int>& values, int target);
```

Kết quả gồm `index` kiểu `std::optional<std::size_t>` và `comparisons` kiểu
`std::size_t`. Chỉ số bắt đầu từ 0, luôn là lần xuất hiện **đầu tiên**.
Không có kết quả thì `index == std::nullopt`. Đầu vào không bị sửa và
không cần sắp xếp; số âm, phần tử trùng và mọi giá trị `int` đều hợp lệ.

`comparisons` chỉ đếm phép `values[i] == target`, không đếm điều kiện vòng
lặp hay kiểm tra kích thước. Nếu tìm thấy ở chỉ số `i`, số phép so sánh
là `i + 1`; nếu không thấy thì bằng `values.size()`. Vector rỗng trả về
`{std::nullopt, 0}`.

## Thuật toán và tính đúng

Duyệt từ trái sang phải, kiểm tra từng phần tử và trả về ngay khi bằng
mục tiêu. Trước lần lặp có chỉ số `i`, các phần tử trong `[0, i)` đều đã
được kiểm tra và khác mục tiêu. Do đó một phần tử khớp tại `i` chắc chắn
là lần xuất hiện đầu tiên. Nếu hết vòng lặp, mọi phần tử đã được kiểm tra
nên kết quả vắng mặt là đúng.

Không thực hiện phép trừ trên giá trị phần tử nên cả `INT_MIN` và
`INT_MAX` đều được xử lý giống các giá trị khác.

**Độ phức tạp:** tốt nhất `O(1)` khi khớp ngay đầu; xấu nhất `O(n)` khi
khớp cuối hoặc không có. Bộ nhớ phụ `O(1)`.

## Ví dụ tự chạy

Đặt `example.cpp` cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>

int main() {
    const auto found = lab::linear_search({9, -2, 9, 0}, -2);
    if (found.index) std::cout << *found.index << ' ' << found.comparisons << '\n';
    const auto missing = lab::linear_search({9, -2, 9, 0}, 7);
    std::cout << missing.index.has_value() << ' ' << missing.comparisons << '\n';
}
```

Biên dịch bằng `g++ -std=c++17 example.cpp -o /tmp/linear-example`, chạy
`/tmp/linear-example` sẽ in `1 2` rồi `0 4`.

Với cùng vector, tìm `9` cho chỉ số `0` và một phép so sánh; không trả về
chỉ số `2` dù giá trị ở đó cũng bằng `9`.

## So với tìm kiếm nhị phân

[Bài 01](../01-binary-search/README.md) cần dữ liệu tăng dần và dùng
`O(log n)` thời gian mỗi truy vấn. Tìm tuyến tính dùng được trực tiếp
với dữ liệu chưa sắp xếp. Sắp xếp chỉ để tìm một lần sẽ phát sinh chi phí
và thay đổi vị trí ban đầu; đó không phải là thao tác miễn phí.

## Kiểm thử

Từ gốc repo: `make test`. Chạy riêng, kể cả khi tắt `assert`:

```sh
g++ -std=c++17 -DNDEBUG -Wall -Wextra -Werror -pedantic lessons/02-linear-search/test.cpp -o /tmp/linear-test
/tmp/linear-test
```

Kiểm thử bao phủ rỗng, một phần tử, khớp đầu/giữa/cuối, không thấy,
trùng lặp, số cực trị và tính bất biến đầu vào. Các vector chưa sắp xếp
độ dài 0–7 trên `{-1, 0, 1}` được đối chiếu với `std::find`; cả chỉ số
lẫn số phép so sánh phải đúng. Lỗi trả mã thoát khác 0 dù có `NDEBUG`.

## Tự luyện

1. Viết biến thể tìm lần xuất hiện cuối cùng. Số phép so sánh có còn
   bằng `index + 1` không? Đưa ví dụ phân biệt.
2. Nếu cần tìm hàng nghìn lần trên cùng dữ liệu, khi nào nên giữ một
   bản đã sắp xếp? Phân tích cả chi phí chuẩn bị và yêu cầu giữ chỉ số gốc.
3. Đếm thêm phép kiểm tra vòng lặp và giải thích vì sao phải định nghĩa
   chính xác đang đếm loại thao tác nào.
