# LeetCode 678 — Valid Parenthesis String: khoảng số ngoặc mở

Nguồn: [Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/), Medium.
Bài bổ sung ngày **2026-11-25**. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::checkValidString(const std::string& s)` trả `true` nếu có
cách thay mỗi `*` bằng `(`, `)` hoặc chuỗi rỗng để có dãy ngoặc hợp lệ.
Ngoặc đóng phải ghép với ngoặc mở đứng trước nó.

Miền nguồn: độ dài 1–100, chỉ gồm `(`, `)`, `*`. Đây là tiền điều kiện,
không kiểm tra ký tự ngoài miền. Bản lab mở rộng chuỗi rỗng thành `true`.
Hàm không sao chép hay thay đổi chuỗi đầu vào.

## Bất biến khoảng khả thi

Sau mỗi tiền tố, xét số ngoặc mở chưa được đóng trong mọi cách thay `*`
mà chưa tạo tiền tố âm. Tập số này là một khoảng nguyên `[low, high]`.
Ban đầu chỉ có `0`.

- Gặp `(`: dịch cả hai đầu lên `1`.
- Gặp `)`: dịch cả hai đầu xuống `1`.
- Gặp `*`: có thể giảm `1`, giữ nguyên hoặc tăng `1`, nên giảm `low` và
  tăng `high`.

Dịch một khoảng giữ tính liên tục. Với `*`, hợp của ba khoảng dịch cũng
liên tục vì chúng chạm hoặc chồng nhau; điều này đúng cả khi khoảng ban
đầu chỉ có một phần tử. Loại giá trị âm bằng `low = max(low, 0)`.
Nếu `high < 0` thì không còn cách nào tránh được ngoặc đóng thừa, trả
`false` ngay. Việc chặn `low` ở `0` chỉ loại các cách không hợp lệ, không
thêm trạng thái mới.

Kết thúc, có cách đóng hết ngoặc chính xác khi khoảng chứa `0`, tức
`low == 0`. Chỉ kiểm tra tổng số ngoặc cuối cùng sẽ bỏ sót thứ tự: `)*`
không hợp lệ dù tổng có thể bằng `0`.

Thời gian **O(n)**, bộ nhớ phụ **O(1)**. Với tối đa 100 ký tự, hai biên
đều vừa `int`. Không cần liệt kê các cách thay sao trong lời giải chính.

## Ví dụ chạy được

`(*()*)` hợp lệ khi cho cả hai dấu sao rỗng, thu được `(())`.
Chạy tại thư mục bài học:

```sh
cat > /tmp/lc678-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::cout << std::boolalpha
              << lab::Solution{}.checkValidString("(*()*)") << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc678-example.cpp -o /tmp/lc678-example
/tmp/lc678-example
```

Kết quả: `true`.

## Kiểm thử và trường hợp biên

Oracle đệ quy thử từng cách thay `*`, loại nhánh có số ngoặc mở âm, rồi
kiểm tra số ngoặc mở cuối bằng `0`. So sánh mọi chuỗi trên bảng chữ
`()*` có độ dài 0–9: tổng cộng 29524 chuỗi. Oracle không dùng hai biên.

Ca riêng kiểm tra tiền tố đóng thừa, sao đứng trước ngoặc mở không thể
đóng nó, chuỗi rỗng và một ký tự. Ca độ dài 100 gồm toàn sao, đủ sao để
đóng, thiếu hai sao, và toàn ngoặc đóng.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc678-test
/tmp/lc678-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc678-ndebug
/tmp/lc678-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Kiểm thử không dùng
`assert`, nên `NDEBUG` không vô hiệu hóa việc bắt lỗi.

## Bài tập tự luyện

1. Dùng hai stack để trả một cách thay dấu sao cụ thể.
2. Nếu dấu sao chỉ được thay bằng một ngoặc, tập số ngoặc mở khả thi có
   còn là khoảng nguyên liên tục không? Tìm phản ví dụ.
3. So sánh với DP lưu toàn bộ số ngoặc mở khả thi sau mỗi tiền tố.
