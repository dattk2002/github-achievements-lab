# LeetCode 91 — Đếm cách giải mã và kiểm soát tràn số

Nguồn công khai: [LeetCode 91: Decode Ways](https://leetcode.com/problems/decode-ways/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-08**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::numDecodings(std::string s)` đếm cách tách chuỗi chữ số thành các mã 1..26, tương ứng A..Z. Một nhóm có một hoặc hai chữ số; 0 không tự tạo mã, và nhóm hai chữ số phải thuộc 10..26, không có số 0 đầu.

Bài gốc: độ dài 1..100, chỉ có chữ số và **đáp án cuối** vừa số nguyên 32 bit. Bản này trả 0 cho chuỗi rỗng, ném `std::invalid_argument` nếu có ký tự không phải chữ số, và `std::overflow_error` nếu đáp án cuối vượt `int` 32 bit. Cận độ dài không được kiểm tra lại. Chuỗi nhận theo giá trị như giao diện gốc.

## DP hai trạng thái và chứng minh

Gọi D(i) là số cách giải mã i chữ số đầu. D(0)=1 là một cách hoàn thành tiền tố rỗng để dùng trong truy hồi; đây khác quy ước API trả 0 khi đầu vào rỗng. D(1) bằng 0 nếu ký tự đầu là 0, ngược lại bằng 1.

Với mỗi ký tự tiếp theo, nếu nó khác 0 thì có thể đứng một mình, đóng góp D(i-1). Nếu hai chữ số cuối tạo số từ 10 tới 26 thì có thể ghép đôi, đóng góp D(i-2). Hai nhóm cách này khác nhau ở nhóm mã cuối, nên không trùng và bao phủ mọi cách giải mã. Chỉ giữ hai trạng thái trước, không cần bảng đầy đủ.

### Vì sao cần giới hạn từng trạng thái?

Cam kết đáp án cuối vừa 32 bit không bảo đảm mọi D(i) đều vừa: số 0 có thể buộc ghép đôi hoặc làm toàn bộ chuỗi không giải được. Ví dụ 46 chữ số `1` rồi `0` có đáp án 1836311903, dù số cách của tiền tố 46 chữ số đã vượt `int`. Chuỗi 98 chữ số `1` rồi `30` có đáp án 0 dù tiền tố có rất nhiều cách.

Đặt C=`INT_MAX+1` và lưu `min(D(i),C)` trong `std::int64_t`. Truy hồi chỉ dùng phép cộng các số không âm và chọn/bỏ một trạng thái, nên:

```text
min(a+b,C) = min(min(a,C)+min(b,C),C)
```

Do đó quy nạp bảo đảm mỗi trạng thái lưu chính xác giá trị thật đã chặn tại C. Nếu đáp án cuối nhỏ hơn C, giá trị vẫn chính xác; nếu bằng C thì biết đã vượt cam kết và ném ngoại lệ. Không ném chỉ vì một tiền tố vượt cận. Mỗi phép cộng tối đa 2C, an toàn với 64 bit trên môi trường `int` 32 bit của bài. Cách này tránh cả tràn số trung gian lẫn việc từ chối nhầm một đáp án cuối hợp lệ.

Thời gian O(n), O(1) bộ nhớ trạng thái. Tham số theo giá trị có thêm O(n) bản sao khi gọi bằng chuỗi lvalue, nên tổng bộ nhớ API có thể là O(n).

## Ví dụ chạy được

Lưu thành `/tmp/decode-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-91-decode-ways-cpp/lesson.hpp"
#include <iostream>
int main() {
    lab::Solution solution;
    std::cout << solution.numDecodings("121") << '\n';
    std::cout << solution.numDecodings("210") << '\n';
    std::cout << solution.numDecodings("301") << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/decode-example.cpp -o /tmp/decode-example
/tmp/decode-example
```

Kết quả:

```text
3
1
0
```

`121` tách thành `1|2|1`, `12|1`, `1|21`; `210` chỉ có `2|10`.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-91-decode-ways-cpp/test.cpp -o /tmp/decode-test
/tmp/decode-test
make test-all
```

Oracle đệ quy liệt kê cách lấy một/hai chữ số, không dùng DP cuộn hay giới hạn số đếm. Đối chiếu 21845 chuỗi độ dài 0..7 trên `{0,1,2,7}`; thêm biên 26/27, số 0 đầu/giữa/cuối, chuỗi rỗng và ký tự sai. Các ca 45 chữ số `1`, 46 chữ số `1` rồi `0`, 98 chữ số `1` rồi `30` kiểm tra cận và việc không từ chối nhầm khi chỉ trung gian lớn. 100 chữ số `1` phải ném ngoại lệ vì đáp án vượt cam kết. Test dùng `exit(1)`, không phụ thuộc `assert` hay `NDEBUG`.

## Bài tập

1. Vì sao bỏ kiểm tra số 0 sẽ đếm thừa cho `100` và `301`?
2. Nếu yêu cầu số cách modulo M, có thể thay chặn tại C bằng phép toán nào? Vì sao không còn kiểm tra vượt `int` như hiện tại?
3. Mở rộng để trả một cách giải mã hợp lệ mà không liệt kê mọi cách.
