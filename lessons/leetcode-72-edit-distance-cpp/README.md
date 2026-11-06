# LeetCode 72 — Khoảng cách chỉnh sửa với bộ nhớ hai hàng

Nguồn công khai: [LeetCode 72: Edit Distance](https://leetcode.com/problems/edit-distance/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-06**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::minDistance(std::string word1, std::string word2)` trả số phép **chèn, xóa hoặc thay một ký tự** ít nhất để biến word1 thành word2; mỗi phép tốn 1. Hoán đổi hai ký tự kề nhau không phải một phép riêng. Ví dụ `ab` thành `ba` tốn 2, không phải 1.

Bài gốc cho phép chuỗi rỗng, mỗi chuỗi dài 0..500 và gồm chữ thường tiếng Anh. Đây là các tiền điều kiện, không kiểm tra lại. Nhận chuỗi theo giá trị như giao diện gốc, nên không sửa biến của người gọi. Đáp án không vượt độ dài lớn hơn của hai chuỗi (tối đa 500), dùng `int` an toàn.

## Quy hoạch động và chứng minh

Gọi D(i,j) là chi phí ít nhất để biến i ký tự đầu của word1 thành j ký tự đầu của word2. D(0,j)=j vì cần chèn j ký tự; D(i,0)=i vì cần xóa i ký tự.

Ở ô còn lại, xét bước cuối: xóa ký tự cuối của tiền tố nguồn (D(i-1,j)+1), chèn ký tự cuối của đích (D(i,j-1)+1), hoặc ghép/thay hai ký tự cuối (D(i-1,j-1) cộng 0 nếu bằng nhau, 1 nếu khác). Lấy nhỏ nhất của ba khả năng. Các khả năng bao phủ bước cuối của mọi phương án tối ưu, và nối bước đó vào một phương án tối ưu của tiền tố tạo đúng chi phí tương ứng. Quy nạp theo i+j chứng minh công thức.

Chỉ cần hàng trước và phần bên trái của hàng hiện tại. Khởi tạo hàng trước 0..|word2|; mỗi hàng mới gán ô đầu bằng i, tính từ trái sang phải rồi hoán đổi hai vector. Đổi hai chuỗi trước khi tính để chuỗi ngắn hơn nằm ở cột, vì với chi phí chèn/xóa bằng nhau, khoảng cách đối xứng.

Với độ dài m,n: O((m+1)(n+1)) thời gian, bao gồm cả ca có một chuỗi rỗng; O(min(m,n)+1) bộ nhớ hai hàng bên trong. Giao diện theo giá trị có thêm bản sao O(m+n) khi nhận chuỗi lvalue, nên tổng bộ nhớ API có thể là O(m+n+1). Không lưu toàn ma trận khi chỉ cần khoảng cách.

## Ví dụ chạy được

Lưu thành `/tmp/edit-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-72-edit-distance-cpp/lesson.hpp"
#include <iostream>
int main() {
    lab::Solution solution;
    std::cout << solution.minDistance("stone", "tones") << '\n';
    std::cout << solution.minDistance("", "mint") << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/edit-example.cpp -o /tmp/edit-example
/tmp/edit-example
```

Kết quả:

```text
2
4
```

Ca đầu có thể xóa `s` đầu rồi chèn `s` cuối; ca sau cần chèn bốn ký tự.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-72-edit-distance-cpp/test.cpp -o /tmp/edit-test
/tmp/edit-test
make test-all
```

Oracle đệ quy thử trực tiếp ba phép sửa, không dùng bảng hay hai hàng DP, chỉ chạy trên chuỗi ngắn. Đối chiếu mọi cặp trong 31 chuỗi độ dài 0..4 trên `{a,b}` (961 cặp). Ca cố định kiểm tra riêng chèn/xóa/thay, hai chuỗi rỗng, một chuỗi rỗng và không coi transposition là một phép. Chuỗi dài 500 kiểm tra cận, cần 500 lần thay, xóa hết và chỉ thay ký tự cuối. Test dùng `exit(1)` khi sai, không phụ thuộc `assert` hay `NDEBUG`.

## Bài tập

1. Trả lại dãy phép sửa tối ưu: lưu cả ma trận hoặc dùng chia để trị để truy vết với bộ nhớ thấp hơn.
2. Nếu chi phí chèn và xóa khác nhau, vì sao không thể tùy ý đổi hai chuỗi như hiện tại?
3. Thêm phép hoán đổi kề nhau: viết rõ hợp đồng mới trước khi đổi công thức và bổ sung test `ab` thành `ba`.
