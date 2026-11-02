# 08 — Trộn hai dãy đã sắp xếp

Bài dự phòng `08-merge-sorted` trong `curriculum.json`, chạy bù có giám sát ngày 2026-11-02 cho lịch 09:00.

## Hợp đồng

```cpp
std::vector<int> lab::merge_sorted(const std::vector<int>& first,
                                   const std::vector<int>& second);
```

Hai đầu vào phải có thứ tự **không giảm**. Đây là tiền điều kiện do người gọi đảm bảo, hàm không kiểm tra hay tự sắp xếp lại. Trả một vector mới có thứ tự không giảm, chứa đủ mọi phần tử kể cả các bản sao. Đầu vào không bị sửa; có thể truyền cùng một vector vào cả hai tham số và mọi phần tử sẽ xuất hiện hai lần.

Hai dãy rỗng cho kết quả rỗng. Nếu chỉ một dãy rỗng, kết quả là bản sao dãy còn lại. Hàm chỉ so sánh `int`, không cộng/trừ giá trị nên dùng được với số âm và cực trị. Nếu tổng số phần tử vượt `vector<int>::max_size()`, ném `std::length_error` trước khi cộng kích thước. Kích thước hợp lệ vẫn có thể gây `std::bad_alloc` khi hết bộ nhớ.

## Thuật toán và chứng minh

Dùng chỉ số `i`, `j` ở đầu hai dãy. So sánh hai phần tử hiện tại, đưa phần tử nhỏ hơn vào kết quả và tăng chỉ số tương ứng. Khi bằng nhau chọn bên thứ nhất; phần tử bên thứ hai vẫn được lấy ở lượt sau nên không mất bản sao. Khi một bên hết, chép phần còn lại của bên kia.

**Bất biến:** kết quả là dãy đã sắp xếp gồm đúng các phần tử đã tiêu thụ trong `[0, i)` và `[0, j)`; mọi phần tử chưa lấy đều không nhỏ hơn phần tử cuối đã lấy. Do hai đầu vào đã có thứ tự, phần tử nhỏ nhất chưa lấy luôn ở một trong hai đầu hiện tại. Chọn phần tử đó duy trì bất biến. Mỗi bước tiêu thụ một phần tử, vì thế thuật toán dừng sau khi đã lấy đủ `n + m` phần tử.

Đây là thao tác cốt lõi của merge sort. Khác phép hợp tập hợp, bài này giữ nguyên số lần xuất hiện.

## Độ phức tạp

O(n + m) thời gian, O(n + m) bộ nhớ cho kết quả và O(1) bộ nhớ phụ ngoài kết quả. Trường hợp cả hai dãy rỗng tốn O(1). `reserve` tránh tăng dung lượng lặp lại; kiểm tra kích thước trước phép cộng tránh tràn `size_t`.

## Ví dụ chạy được

Lưu thành `/tmp/merge-example.cpp`, chạy ở gốc repo:

```cpp
#include "lessons/08-merge-sorted/lesson.hpp"
#include <iostream>
int main() {
    const auto values = lab::merge_sorted({-5, 2, 2}, {-3, 2, 9, 12});
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i) std::cout << ' ';
        std::cout << values[i];
    }
    std::cout << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/merge-example.cpp -o /tmp/merge-example
/tmp/merge-example
```

Kết quả: `-5 -3 2 2 2 9 12`.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/08-merge-sorted/test.cpp -o /tmp/merge-test
/tmp/merge-test
make test
```

Test có kết quả tính tay, hai phía rỗng riêng rẽ, độ dài lệch nhau, phần tử lặp, số âm, cực trị và truyền cùng một vector hai lần. Với 625 cặp độ dài 0..24, sinh dữ liệu xác định rồi so sánh với cách nối hai dãy và `std::sort`. Mỗi ca kiểm tra cả việc không sửa đầu vào. Không dựng vector vượt `max_size` trong test vì cần lượng bộ nhớ không khả thi; nhánh phòng vệ được review. Mọi kiểm tra đều hoạt động khi bật `NDEBUG`.

## Bài tập

1. Mô phỏng `i`, `j` và kết quả cho `{-2, 3, 3}` và `{-2, 0, 4}`.
2. Viết bản trộn loại trùng, mô tả chính xác hợp đồng mới.
3. Trộn k dãy đã sắp xếp: so sánh trộn tuần tự và dùng heap theo tổng số phần tử.
