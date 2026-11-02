# 07 — Insertion sort và bất biến vòng lặp

Bài dự phòng `07-insertion-sort` trong `curriculum.json`, chạy bù có giám sát ngày 2026-11-02 cho lịch 09:00.

## Hợp đồng

```cpp
void lab::insertion_sort(std::vector<int>& values);
```

Sắp xếp trực tiếp vector theo thứ tự không giảm, giữ nguyên mọi phần tử và số lần xuất hiện. Chấp nhận vector rỗng, số âm, phần tử trùng, `INT_MIN` và `INT_MAX`. Hàm không gọi `std::sort` và không tạo vector phụ. Vector đầu vào là nơi nhận kết quả.

## Thuật toán

Với vị trí `i` từ 1 đến hết dãy, giữ `values[i]` trong biến `key`. Dịch sang phải các giá trị trong tiền tố lớn hơn `key`, rồi đặt `key` vào chỗ trống. Chỉ so sánh giá trị, không trừ hai số nguyên nên tránh tràn ở các giá trị cực trị.

**Bất biến vòng ngoài:** trước mỗi lượt, đoạn `[0, i)` đã được sắp xếp và chứa đúng các phần tử của tiền tố ban đầu. Đoạn `[i, n)` chưa bị xử lý. Trong vòng trong, `key` vẫn nằm an toàn trong biến riêng; các phần tử lớn hơn nó đã dịch sang phải, chừa một vị trí để chèn.

Lượt đầu có tiền tố một phần tử nên bất biến đúng. Chèn `key` mở rộng tiền tố đã sắp xếp thêm một phần tử mà không mất hoặc tạo giá trị. Khi kết thúc, tiền tố là toàn dãy. Điều kiện `position > 0` được kiểm tra trước khi truy cập `position - 1`, tránh tràn chỉ số không dấu.

So sánh bằng `>` thay vì `>=` không đẩy các phần tử bằng `key` qua nó, nên thuật toán ổn định. Với API `int`, danh tính của các phần tử bằng nhau không quan sát được; muốn kiểm thử tính ổn định cần mở rộng sang bản ghi có khóa và nhãn.

## Độ phức tạp

- Dãy đã tăng: O(n) thời gian, vì mỗi lượt chỉ kiểm tra rồi chèn lại tại chỗ.
- Trung bình và xấu nhất: O(n²) thời gian; dãy giảm cần dịch tổng cộng `n(n-1)/2` phần tử.
- O(1) bộ nhớ phụ; không có đệ quy. Vector rỗng cần O(1) thời gian.

Thích hợp để học bất biến, dãy nhỏ hoặc gần có thứ tự; với dữ liệu lớn, thường cần thuật toán O(n log n).

## Ví dụ chạy được

Lưu thành `/tmp/insertion-example.cpp`, chạy ở gốc repo:

```cpp
#include "lessons/07-insertion-sort/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> values{6, -4, 6, 2, 0};
    lab::insertion_sort(values);
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i) std::cout << ' ';
        std::cout << values[i];
    }
    std::cout << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/insertion-example.cpp -o /tmp/insertion-example
/tmp/insertion-example
```

Kết quả: `-4 0 2 6 6`.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/07-insertion-sort/test.cpp -o /tmp/insertion-test
/tmp/insertion-test
make test
```

Bộ test đối chiếu kết quả với `std::sort`, chỉ dùng trong test. Có dãy rỗng, một phần tử, tăng, giảm, toàn phần tử bằng nhau, số âm và cực trị. Duyệt hết các dãy độ dài 0..7 trên tập `{-1, 0, 1}`, rồi thêm dãy sinh xác định dài tới 159 để kiểm tra mất phần tử, sai vị trí chèn và lỗi dịch chuyển. Kiểm tra thất bại trả mã 1 cả khi có `NDEBUG`.

## Bài tập

1. Đếm số lần so sánh và dịch trên `{5, 2, 4, 1}` bằng tay.
2. Thêm comparator cho bản ghi `{key, label}`, rồi chứng minh và kiểm tra tính ổn định.
3. Dùng binary search tìm vị trí chèn có giảm độ phức tạp xấu nhất của toàn bộ thuật toán không? Phân biệt chi phí so sánh và dịch phần tử.
