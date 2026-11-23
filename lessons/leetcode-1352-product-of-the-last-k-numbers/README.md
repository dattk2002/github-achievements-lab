# LeetCode 1352 — Tích của k số cuối

Ngày nguồn (`source_date`) **2026-11-23**. Độ khó **Medium**.
[Đề bài gốc trên LeetCode](https://leetcode.com/problems/product-of-the-last-k-numbers/)

## Hợp đồng

`lab::ProductOfNumbers` khởi tạo một luồng rỗng. `add(int num)` nối
một số vào cuối luồng. `getProduct(int k)` trả về tích của đúng
`k` số cuối và giữ nguyên luồng.

Mỗi số thuộc đoạn `[0, 100]`. Mỗi truy vấn có `1 <= k <= 40000` và
luồng đã nhận ít nhất `k` số. Tổng số lần gọi hai phương thức tối đa
là 40000 trên một đối tượng. Đề bảo đảm tích của mọi đoạn liên tiếp
vừa trong số nguyên có dấu 32 bit.

## Thuật toán và tính đúng đắn

Gọi `m` là số phần tử kể từ số 0 gần nhất, hoặc độ dài luồng nếu
chưa gặp số 0. Lưu `prefix[0] = 1` và duy trì `prefix[i]` bằng
tích của `i` số đầu trong đoạn hiện tại, với `1 <= i <= m`.

Khi thêm số dương, nhân `prefix[m]` với số mới để có
`prefix[m + 1]`. Khi thêm số 0, đặt `m = 0`. Các ô ngoài đoạn
`[0, m]` được giữ lại để ghi đè khi đoạn sau lớn dần.

Nếu `k > m`, hậu tố cần tính chứa số 0 nên tích bằng 0. Nếu
`k <= m`, `prefix[m]` bằng tích của `m - k` số đầu nhân với
tích cần tìm. Chia cho `prefix[m - k]` cho kết quả chính xác vì
mẫu là tích các số dương, hoặc là 1 khi `k = m`. Mỗi phép nhân
tạo tích của một đoạn liên tiếp nên nằm trong giới hạn đã cho.

Truy vấn tốn **O(1)** thời gian. Thêm số tốn **O(1)** thời gian
khấu hao do vector đôi lúc phải cấp phát lại. Thêm số 0 chỉ đổi độ
dài đoạn nên tốn **O(1)** ngay cả trong trường hợp xấu nhất. Bộ nhớ
là **O(L + 1)** với `L` là độ dài đoạn không chứa số 0 dài nhất
đã xuất hiện.

## Ví dụ và cách chạy

Đặt chương trình ví dụ cạnh `lesson.hpp` và biên dịch với C++17.

```cpp
#include "lesson.hpp"
#include <iostream>

int main() {
    lab::ProductOfNumbers stream;
    stream.add(8);
    stream.add(0);
    stream.add(3);
    stream.add(7);
    std::cout << stream.getProduct(2) << '\n';  // 21
    std::cout << stream.getProduct(3) << '\n';  // 0
    stream.add(2);
    std::cout << stream.getProduct(2) << '\n';  // 14
}
```

Chạy `make test` từ thư mục gốc. Để chạy riêng bài này, dùng
các lệnh sau trong thư mục bài học.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lesson-1352-test
/tmp/lesson-1352-test
```

## Kiểm thử

Các đáp án được tính từ dữ liệu đầu vào. Bộ kiểm thử kiểm tra truy
vấn một phần tử và cả luồng, hai số 0 liên tiếp, hậu tố gồm toàn bộ
đoạn sau số 0 gần nhất, và hậu tố dài hơn đoạn đó đúng một phần tử. Một ca đạt tích 2.100.000.000 bằng
bốn số 100 nhân với 21. Ca dài nhất thêm 39.999 số 1 rồi truy
vấn toàn bộ, dùng đúng 40.000 lượt gọi. Khi có sai lệch, chương
trình in giá trị mong đợi và thực tế rồi thoát với mã khác 0
ngay cả khi bật `NDEBUG`.

## Bài tập

1. Viết lời giải lưu cả luồng và nhân trực tiếp `k` số cuối. Dùng
   lời giải đó làm đối chứng trên nhiều luồng ngắn có số 0.
2. Thêm ca kiểm thử cho luồng bắt đầu bằng số 0, sau đó thêm một số
   dương. Tính tay hai truy vấn tương ứng với `k = 1` và `k = 2`.
