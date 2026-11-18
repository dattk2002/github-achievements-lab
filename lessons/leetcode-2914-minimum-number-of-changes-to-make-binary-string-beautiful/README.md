# LeetCode 2914 — Minimum Number of Changes to Make Binary String Beautiful (C++17)

Ngày nguồn (`source_date`) **2026-11-18**. Độ khó **Medium**. [Bài gốc trên LeetCode](https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/)

## Hợp đồng

`lab::Solution::minChanges(std::string s)` trả về số bit ít nhất cần đổi để
có thể chia toàn bộ chuỗi thành các đoạn liên tiếp đồng nhất có độ dài chẵn.
Đầu vào chỉ gồm `0` và `1`, với độ dài chẵn từ 2 đến 100 000. Hàm giả định
các tiền điều kiện này được thỏa mãn.

## Thuật toán và chứng minh

Xét các cặp cố định bắt đầu ở chỉ số 0, 2, 4, … Mọi ranh giới của một
phân hoạch hợp lệ đều nằm sau một tiền tố dài chẵn, vì độ dài tiền tố
là tổng độ dài các đoạn đã đi qua. Do đó, hai bit trong mỗi cặp cố định
phải nằm cùng một đoạn và phải bằng nhau. Mỗi cặp khác bit buộc phải
đổi ít nhất một bit.

Quét từ trái sang phải với bước nhảy 2 và cộng một cho mỗi cặp khác bit.
Để đạt đúng số lần đổi đã đếm, có thể đổi bit thứ hai của từng cặp khác
bit thành giá trị của bit thứ nhất. Sau đó dùng từng cặp làm một đoạn
dài 2. Các cặp rời nhau nên mỗi lần đổi chỉ tác động đến một cặp.
Cận dưới vì thế đạt được, và số đếm chính là đáp án tối ưu.

Với `n = s.size()`, thời gian là `O(n)` và phần quét dùng `O(1)` bộ nhớ
phụ. Chữ ký truyền chuỗi theo giá trị giữ dạng giao diện của đề. Khi gọi
bằng một biến chuỗi, việc sao chép đối số cần thêm `O(n)` bộ nhớ.

## Ví dụ tự xây dựng

- `000111` cần 1 lần đổi. Đổi bit ở chỉ số 2 để được `00|11|11`.
- `00111100` cần 0 lần đổi vì đã có thể chia thành `00|1111|00`.
- `010101` cần 3 lần đổi. Mỗi cặp có hai bit khác nhau, và đổi ba bit 1
  thành 0 tạo ra một chuỗi đồng nhất dài chẵn.

Chạy ví dụ đầu từ thư mục gốc của kho mã.

```sh
lesson=lessons/leetcode-2914-minimum-number-of-changes-to-make-binary-string-beautiful
g++ -std=c++17 -I"$lesson" -x c++ - -o /tmp/lc2914-example <<'CPP'
#include "lesson.hpp"
#include <iostream>

int main() {
    std::cout << lab::Solution{}.minChanges("000111") << '\n';
}
CPP
/tmp/lc2914-example
```

## Kiểm thử

Bộ kiểm thử xét chuỗi độ dài tối thiểu 2, chuỗi có nhiều đoạn đồng nhất,
cặp sai ở cuối chuỗi, và hai chuỗi dài 100 000. Chuỗi dài toàn bit 1
có đáp án 0, còn chuỗi xen kẽ đạt đáp án lớn nhất là 50 000.

Để tính đáp án độc lập cho 340 chuỗi độ dài 2, 4, 6 và 8, bộ kiểm thử
liệt kê mọi chuỗi đích và giữ những chuỗi mà mọi dãy bit giống nhau
liên tiếp tối đại đều có độ dài chẵn. Tiêu chí này đúng vì mỗi dãy tối
đại là hợp của các đoạn cùng bit trong một phân hoạch hợp lệ. Ngược lại,
nếu mọi dãy tối đại có độ dài chẵn thì có thể dùng chính chúng làm các
đoạn. Với mỗi chuỗi đầu vào, lấy khoảng cách Hamming nhỏ nhất đến các
chuỗi đích được giữ lại. Khi kết quả sai, chương trình in thông tin ca
lỗi và thoát với mã khác 0 kể cả khi có `NDEBUG`.

```sh
make test
```

## Bài tập

1. Hãy sửa thuật toán để trả về một chuỗi đẹp đạt số lần đổi tối ưu.
2. Tìm một chuỗi có độ dài chẵn cho thấy đếm số lần đổi bit giữa mọi
   vị trí kề nhau có thể cho đáp án sai.
3. Nếu mỗi vị trí có một chi phí đổi bit riêng không âm, hãy tìm công thức
   tính tổng chi phí tối ưu và giải thích vì sao quyết định ở mỗi cặp vẫn
   độc lập.
