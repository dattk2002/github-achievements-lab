# LeetCode 97: Interleaving String (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/interleaving-string/). Độ khó: Medium.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::isInterleave(std::string s1, std::string s2, std::string s3)`
trả `true` nếu có thể ghép toàn bộ ký tự của hai chuỗi đầu để tạo chuỗi thứ ba,
giữ nguyên thứ tự tương đối trong từng chuỗi nguồn. Không được bỏ hoặc dùng
lặp một ký tự nguồn. Các tham số nhận theo giá trị, không sửa chuỗi của bên gọi.

Nguồn cho độ dài `s1,s2` trong `0..100`, `s3` trong `0..200`, chỉ gồm chữ cái
thường tiếng Anh. Đây là tiền điều kiện không xác thực. Chuỗi rỗng thuộc miền
nguồn; ba chuỗi rỗng cho `true`. Tổng độ dài hai nguồn khác độ dài đích thì
trả `false` ngay, trước mọi truy cập theo chỉ số.

## Quy hoạch động một hàng

`D[i][j]` biểu diễn hai tiền tố nguồn dài `i,j` có tạo được tiền tố đích dài
`i+j` hay không. Cơ sở `D[0][0]=true`. Để đến `(i,j)`, ký tự cuối cùng phải
lấy từ một trong hai nguồn:

```text
D[i][j] = (i>0 và D[i-1][j] và s1[i-1]==s3[i+j-1])
        hoặc (j>0 và D[i][j-1] và s2[j-1]==s3[i+j-1])
```

Đổi chỗ hai bản sao nguồn nếu cần để chuỗi ngắn hơn làm cột. Khởi tạo hàng
`i=0` rồi quét các hàng còn lại từ trái sang phải. Khi cập nhật `possible[j]`,
giá trị cũ là ô phía trên; `possible[j-1]` đã cập nhật là ô bên trái. Mỗi hàng
cũng phải cập nhật cột 0 cho trường hợp chỉ lấy từ nguồn thứ nhất.

`"ab"` và `"cd"` tạo được `"acbd"`, nhưng không tạo được `"abdc"` vì `d`
đứng trước `c`. Khi cả hai nguồn cùng bắt đầu bằng một ký tự, chọn tham lam
một nguồn có thể thất bại; DP giữ cả hai khả năng.

### Vì sao đúng?

Xét ký tự cuối của một phép ghép hợp lệ. Nó phải là ký tự cuối của một trong
hai tiền tố nguồn đã dùng; bỏ ký tự ấy để lại đúng một trạng thái tiền nhiệm
trong công thức. Ngược lại, từ một tiền nhiệm hợp lệ có ký tự cuối khớp đích,
thêm ký tự đó tạo một phép ghép hợp lệ. Hai chiều này cùng cơ sở rỗng chứng
minh bảng đúng bằng quy nạp theo `i+j`. Quét trái sang phải bảo toàn đủ hai
trạng thái tiền nhiệm nên việc cuộn bảng thành một hàng không đổi đáp án.

## Độ phức tạp

Với `n,m` là độ dài nguồn: thời gian `O((n+1)(m+1))` khi tổng độ dài khớp,
bộ nhớ DP `O(min(n,m)+1)`. Tính cả ba bản sao chuỗi của API nhận theo giá trị,
bộ nhớ bổ sung là `O(n+m+|s3|+1)`. Không dùng đệ quy trong lời giải.

## Ví dụ chạy được

Lưu thành `/tmp/lc-97-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::cout << std::boolalpha
              << lab::Solution{}.isInterleave("ab","cd","acbd") << '\n'; // true
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-97-interleaving-string-cpp /tmp/lc-97-example.cpp -o /tmp/lc-97-example
/tmp/lc-97-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-97-interleaving-string-cpp/test.cpp -o /tmp/lc-97-test
/tmp/lc-97-test
make test
make test-all
```

## Biên và kiểm thử

Oracle đệ quy thử mọi cách lấy ký tự tiếp theo từ một trong hai nguồn, không
lưu bảng DP. Đối chiếu 7225 bộ chuỗi nhị phân với mỗi nguồn dài `0..3` và đích
có tổng độ dài tương ứng. Có ca ký tự đầu trùng, cùng tập ký tự nhưng sai thứ
tự, sai tổng độ dài, nguồn rỗng và hai nguồn dài 100. Test dùng mã thoát khác 0
khi sai lệch, vẫn phát hiện lỗi khi định nghĩa `NDEBUG`.

## Bài tập

1. Lưu thêm lựa chọn để khôi phục một cách ghép hợp lệ.
2. Tìm phản ví dụ cho cách luôn ưu tiên lấy từ nguồn thứ nhất khi cả hai khớp.
3. Thay giá trị đúng/sai bằng số cách ghép và thảo luận giới hạn số học.
