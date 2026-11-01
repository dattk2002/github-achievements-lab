# 03 — Tổng tiền tố và truy vấn đoạn có kiểm tra biên

Bài `03-prefix-sums` thuộc [curriculum](../../curriculum.json), thực hiện
trong lượt chạy bù ngày 01/11/2026. Mục tiêu là trả lời nhiều truy vấn
tổng trên một dãy cố định mà không cộng lại từng đoạn.

## Hợp đồng

```cpp
explicit lab::PrefixSums(const std::vector<int>& values);
long long lab::PrefixSums::range_sum(std::size_t begin, std::size_t end) const;
```

`range_sum(begin, end)` trả tổng của khoảng nửa mở `[begin, end)`.
Điều kiện hợp lệ: `0 <= begin <= end <= n`, với `n` là kích thước đầu vào.
Đoạn rỗng, kể cả `[n, n)`, có tổng 0. Đầu vào rỗng chỉ cho phép `[0, 0)`.
Đảo biên hoặc vượt kích thước ném `std::out_of_range` trước khi truy cập.
Tham số là chỉ số không dấu; giá trị âm được chuyển sang `size_t` thường
trở thành số rất lớn và cũng bị kiểm tra biên loại bỏ.

Đối tượng giữ bản tổng riêng, không tham chiếu vào vector ban đầu. Hàm
khởi tạo không sửa đầu vào; sửa hoặc hủy vector sau đó không đổi kết quả.

**Tiền điều kiện số học:** mọi tổng tiền tố và mọi tổng đoạn được hỏi
phải biểu diễn được bằng `long long`. Bài này kiểm tra biên chỉ số,
không cung cấp phát hiện tràn số học. Vi phạm tiền điều kiện có thể gây
tràn số nguyên có dấu. Dùng `long long` cho cả lưu trữ và phép cộng,
không cộng trong `int` rồi mới ép kiểu. Cấp phát vẫn chịu giới hạn bộ nhớ.

## Thuật toán và tính đúng

Lưu `prefix[0] = 0`, sau đó `prefix[i + 1] = prefix[i] + values[i]`.
Bất biến sau khi xử lý `i` phần tử: `prefix[i]` là tổng của `[0, i)`.
Bước cộng tiếp theo giữ bất biến, nên sau khi xây dựng nó đúng với mọi
chỉ số từ 0 đến `n`.

Hai tổng `prefix[end]` và `prefix[begin]` cùng chứa phần `[0, begin)`.
Lấy hiệu loại đúng phần chung đó, để lại tổng `[begin, end)`.
Khi hai biên bằng nhau, hiệu của một số với chính nó bằng 0.

**Độ phức tạp:** xây dựng `O(n)` thời gian theo phân tích khấu hao của
`vector::push_back`, lưu `n + 1` tổng nên tốn `O(n)` bộ nhớ; mỗi truy vấn
`O(1)` thời gian và bộ nhớ phụ. Dữ liệu thay đổi cần xây lại đối tượng;
đây không phải cấu trúc hỗ trợ cập nhật điểm nhanh.

## Ví dụ tự chạy

Đặt `example.cpp` cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    const lab::PrefixSums sums({7, -3, 9, -1});
    std::cout << sums.range_sum(1, 3) << '\n'; // -3 + 9 = 6
    std::cout << sums.range_sum(4, 4) << '\n'; // 0
    try { std::cout << sums.range_sum(3, 2); }
    catch (const std::out_of_range&) { std::cout << "invalid range\n"; }
}
```

Chạy `g++ -std=c++17 example.cpp -o /tmp/prefix-example` rồi
`/tmp/prefix-example`: kết quả lần lượt là `6`, `0`, `invalid range`.
Tổng cả dãy `[0, 4)` là `12`; phần tử tại chỉ số `3` không nằm trong `[1, 3)`.

## Kiểm thử

Từ gốc repo: `make test`, hoặc chạy riêng:

```sh
g++ -std=c++17 -DNDEBUG -Wall -Wextra -Werror -pedantic lessons/03-prefix-sums/test.cpp -o /tmp/prefix-test
/tmp/prefix-test
```

Các ca kiểm tra gồm đoạn toàn bộ, đoạn con, một phần tử, đoạn rỗng,
đầu vào rỗng, biên đảo/vượt phạm vi và chỉ số `size_t` cực đại. Kiểm thử
còn xác minh dữ liệu được giữ độc lập, tổng vượt `int` ở cả hai chiều,
và đối chiếu **mọi đoạn hợp lệ** của các vector độ dài 0–6 trên
`{-2, 0, 2}` với phép cộng trực tiếp dùng `std::accumulate(..., 0LL)`.
Kiểm thử trả mã khác 0 khi sai, kể cả với `NDEBUG`.

## Tự luyện

1. Viết công thức truy vấn nếu API dùng khoảng đóng `[left, right]`.
   Chọn các ví dụ để phát hiện lỗi lệch một đơn vị.
2. Với `q` truy vấn, so sánh `O(n + q)` của tổng tiền tố với `O(nq)`
   khi cộng trực tiếp. Khi nào chi phí lưu thêm mảng không đáng?
3. Nếu phải cập nhật một phần tử sau mỗi truy vấn, phần tổng nào bị ảnh
   hưởng? Tìm hiểu cây Fenwick như một bài mở rộng riêng.
