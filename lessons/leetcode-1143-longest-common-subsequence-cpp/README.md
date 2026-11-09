# LeetCode 1143 — Longest Common Subsequence (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/longest-common-subsequence/).
Bài học sử dụng ví dụ và cách giải thích tự viết.

## Hợp đồng

`lab::Solution::longestCommonSubsequence(std::string text1, std::string text2)`
trả độ dài dãy con chung dài nhất. Dãy con được phép bỏ ký tự nhưng phải giữ thứ
tự; không bắt buộc liền nhau như chuỗi con. Hàm nhận chuỗi theo giá trị nên không
sửa chuỗi của bên gọi.

Nguồn yêu cầu độ dài mỗi chuỗi `1..1000`, chỉ gồm chữ cái thường tiếng Anh.
Đây là tiền điều kiện, không kiểm tra lỗi. Mở rộng riêng: cho phép chuỗi rỗng,
trả `0`. Kết quả không vượt `1000`, vừa `int`.

## Quy hoạch động hai hàng

Đặt `D[i][j]` là độ dài LCS của hai tiền tố dài `i` và `j`.
Hàng hoặc cột rỗng có giá trị `0`.

- Nếu hai ký tự cuối bằng nhau: `D[i][j] = D[i-1][j-1] + 1`.
- Nếu khác nhau: `D[i][j] = max(D[i-1][j], D[i][j-1])`.

Chỉ cần hàng trước và hàng hiện tại. Đổi chỗ hai chuỗi cục bộ để chuỗi ngắn hơn
làm cột, đặt `current[0] = 0` ở mỗi hàng, ghi đè mọi ô từ trái sang phải rồi đổi
hai vector. Khi kết thúc, ô cuối hàng trước là đáp án.

`"axbycz"` và `"abc"` có LCS `"abc"` dài `3`, dù các ký tự không liền nhau.
`"stone"` và `"tones"` có LCS `"tone"` dài `4`.

### Vì sao công thức đúng?

Khi ký tự cuối khác nhau, một dãy chung không thể dùng cả hai ký tự cuối tại cùng
vị trí ghép; ít nhất một bên bị bỏ, tạo đúng hai bài toán con trong phép `max`.
Khi bằng nhau, có thể ghép ký tự đó sau LCS của hai tiền tố ngắn hơn để đạt
`D[i-1][j-1]+1`. Ngược lại, nếu nghiệm dùng ký tự cuối thì bỏ cặp ghép ấy còn một
dãy chung của hai tiền tố ngắn hơn. Nếu nghiệm bỏ một đầu cuối, xóa nhiều nhất
một ký tự khỏi nó cũng thu được dãy chung của hai tiền tố ngắn hơn, nên không
thể vượt giới hạn trên ấy. Cơ sở rỗng và quy nạp theo `i+j` chứng minh bảng đúng.
Hai hàng luôn giữ đúng các ô phụ thuộc, nên việc cuộn hàng giữ nguyên kết quả.

## Độ phức tạp

Với `n,m` là độ dài hai chuỗi: thời gian `O((n+1)(m+1))`, thường viết `O(nm)`
cho chuỗi không rỗng; bảng phụ `O(min(n,m)+1)`. Tính cả hai bản sao tham số
của API nhận theo giá trị, bộ nhớ bổ sung tổng cộng là `O(n+m+1)`.

## Ví dụ chạy được

Lưu thành `/tmp/lcs-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
int main() {
    std::cout << lab::Solution{}.longestCommonSubsequence("axbycz", "abc") << '\n'; // 3
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-1143-longest-common-subsequence-cpp /tmp/lcs-example.cpp -o /tmp/lcs-example
/tmp/lcs-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-1143-longest-common-subsequence-cpp/test.cpp -o /tmp/lcs-test
/tmp/lcs-test
make test
make test-all
```

## Biên và kiểm thử

Oracle duyệt mọi tập chỉ số của chuỗi thứ nhất, tìm từng dãy con trong chuỗi
thứ hai bằng quét tuyến tính; không dùng công thức DP. So sánh mọi cặp trong
63 chuỗi nhị phân độ dài `0..5`, tổng 3969 cặp. Có ca lặp ký tự, không có ký tự
chung, hai chiều rỗng, hai chuỗi dài 1000 giống/khác nhau và chuỗi xen kẽ lệch
một vị trí có đáp án `999`. Kiểm thử trả mã lỗi tường minh kể cả với `NDEBUG`.

## Bài tập

1. Lưu bảng đầy đủ và truy vết để trả một dãy con tối ưu.
2. Vì sao cập nhật một hàng từ phải sang trái không đủ cho công thức hiện tại?
3. Phân biệt LCS với đoạn chung liên tiếp dài nhất bằng một phản ví dụ.
