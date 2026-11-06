# LeetCode 76 — Cửa sổ ngắn nhất chứa đủ ký tự

Nguồn công khai: [LeetCode 76: Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/). Độ khó: Hard. Đối chiếu nguồn ngày **2026-11-06**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`std::string lab::Solution::minWindow(std::string s, std::string t)` trả đoạn liên tiếp ngắn nhất của s chứa đủ **số lần xuất hiện** của từng ký tự trong t, hoặc chuỗi rỗng nếu không có. Phân biệt chữ hoa/thường; không yêu cầu các ký tự xuất hiện theo thứ tự của t. Với nhiều đoạn tối ưu, bản này chọn đoạn ở bên trái nhất.

Bài gốc có `1 <= s.size(), t.size() <= 100000`, chỉ gồm chữ cái tiếng Anh hoa/thường. Các cận kích thước là tiền điều kiện, không kiểm tra lại. Bản này mở rộng t rỗng thành kết quả rỗng và xử lý chuỗi theo byte, kể cả byte null/0xff. Đây không phải bộ xử lý ký tự Unicode. Chỉ số bảng đếm chuyển sang `unsigned char` để không truy cập âm trên máy có `char` có dấu.

Giao diện giữ dạng nhận chuỗi **theo giá trị** như bài gốc; biến của người gọi không bị sửa. Số đếm và biến `missing` dùng `int` an toàn trong cận 100000 ký tự.

## Cửa sổ trượt và chứng minh

Khởi tạo `required[c]` bằng số lần cần byte c, `missing = t.size()`. Khi thêm một byte vào cửa sổ, nếu số cần còn dương thì giảm `missing`; sau đó giảm `required[c]`. Số đếm âm biểu diễn các bản sao dư.

Khi `missing == 0`, cửa sổ đã đủ mọi byte. Ghi lại nếu ngắn hơn kết quả trước, rồi thử bỏ byte ở đầu trái. Tăng `required[c]`; nếu nó trở thành dương thì vừa làm thiếu một bản sao, nên tăng `missing` và dừng thu hẹp.

Bất biến: `required[c]` bằng số lần c cần trong t trừ số lần c có trong cửa sổ; `missing` bằng tổng các phần thiếu dương. Vì vậy cửa sổ hợp lệ chính xác khi `missing == 0`. Với mỗi đầu phải, vòng thu hẹp thử các đầu trái hợp lệ tới khi việc bỏ thêm làm thiếu ký tự. Một đầu trái đã bỏ chỉ có thể tạo cửa sổ dài hơn khi đầu phải tăng, nên không cần quay lại. Mọi ứng viên có thể cải thiện kết quả đều được xét. Chỉ thay kết quả khi ngắn hơn giữ lại đoạn trái nhất nếu hòa độ dài.

Mỗi đầu trái/phải chỉ tăng tối đa |s| lần. Thời gian O(|s|+|t|), kể cả sao chép tham số và tạo chuỗi kết quả. Bộ đếm nội bộ O(1) với 256 ô; kết quả cần O(W) cho độ dài W. Khi gọi bằng chuỗi lvalue, giao diện theo giá trị còn dùng O(|s|+|t|) bộ nhớ bản sao, nên không gọi toàn bộ API là O(1) bộ nhớ.

## Ví dụ chạy được

Lưu thành `/tmp/window-example.cpp`, chạy từ gốc repo:

```cpp
#include "lessons/leetcode-76-minimum-window-substring-cpp/lesson.hpp"
#include <iostream>
int main() {
    lab::Solution solution;
    std::cout << solution.minWindow("qxaabrcaabz", "aabc") << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/window-example.cpp -o /tmp/window-example
/tmp/window-example
```

Kết quả: `caab`. Một lần xuất hiện của `a` không đủ thay cho hai lần mà t yêu cầu.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-76-minimum-window-substring-cpp/test.cpp -o /tmp/window-test
/tmp/window-test
make test-all
```

Oracle thử mọi đầu trái, dùng `multiset` riêng rồi mở rộng tới cửa sổ đầu tiên đủ ký tự, không dùng các biến đếm trượt của lời giải. Đối chiếu 364 chuỗi nguồn dài 0..5 với 40 chuỗi đích dài 0..3 trên `{a,b,c}`: 14560 cặp, gồm cả các trường hợp hòa độ dài. Có ký tự lặp, phân biệt hoa/thường, không có đáp án, chuỗi rỗng, byte null/0xff và hai ca dài 100000. Test dùng điều kiện và `exit(1)`, không dựa vào `assert`, nên vẫn hoạt động với `NDEBUG`.

## Bài tập

1. Trả cặp chỉ số thay cho bản sao đoạn con và nhận đầu vào bằng tham chiếu hằng; tổng bộ nhớ của API đổi thế nào?
2. Nếu cần đếm mọi cửa sổ ngắn nhất, phải đổi cách lưu kết quả và quy tắc hòa ra sao?
3. Thiết kế phiên bản theo Unicode code point; vì sao chỉ tăng bảng từ 128 lên 256 ô không giải quyết được UTF-8?
