# LeetCode 221: Maximal Square (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/maximal-square/). Độ khó: Medium.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::maximalSquare(std::vector<std::vector<char>>& matrix)` trả
**diện tích**, không phải độ dài cạnh, của hình vuông lớn nhất chỉ chứa `'1'`.
Các ô phải liên tiếp theo hàng và cột. Không có ô `'1'` thì kết quả `0`.
Hàm giữ nguyên ma trận.

Nguồn cho ma trận chữ nhật `1 <= m,n <= 300`, mỗi ô là ký tự `'0'` hoặc `'1'`.
Giới hạn kích thước và miền ký tự là tiền điều kiện. Mở rộng riêng: ma trận
rỗng hoặc chữ nhật có 0 cột trả `0`; ma trận có các hàng khác độ dài ném
`std::invalid_argument`, kể cả khi hàng đầu rỗng. Cạnh tối đa 300 nên diện
tích không vượt `90000`, vừa `int`.

## DP theo góc dưới phải

Đặt `D[r][c]` là cạnh hình vuông toàn 1 lớn nhất có góc dưới phải tại ô đó.
Nếu ô hiện tại là 0, trạng thái bằng 0. Nếu là 1:

```text
D[r][c] = 1 + min(D[r-1][c], D[r][c-1], D[r-1][c-1])
```

Thêm hàng/cột biên ảo bằng 0. Chỉ lưu vector `side` gồm một hàng và một cột
ảo. Trước khi ghi đè, lưu giá trị phía trên vào `above`; biến `diagonal` giữ
ô chéo cũ. Sau cập nhật, gán `diagonal=above`, kể cả khi ô hiện tại là 0.
Lấy cạnh lớn nhất rồi bình phương để trả diện tích.

Ma trận `1110 / 1111 / 0111 / 0111` có hình vuông 3x3 ở ba hàng cuối,
ba cột cuối; kết quả là `9`.

### Vì sao đúng?

Một hình vuông cạnh `t` kết thúc tại ô 1 đòi hỏi cả ba ô trên, trái, chéo
đều kết thúc được hình vuông ít nhất cạnh `t-1`, nên cạnh mới không vượt
`1+min(...)`. Ngược lại, ba hình vuông cạnh bằng giá trị nhỏ nhất ấy kết hợp
với ô hiện tại phủ kín một hình vuông lớn hơn một cạnh. Vì vậy công thức vừa
là chặn trên vừa đạt được. Cơ sở biên ảo bằng 0 và quy nạp theo thứ tự quét
chứng minh mọi trạng thái đúng. Biến chéo và vector một hàng giữ nguyên các
phụ thuộc, nên đáp án là bình phương cạnh lớn nhất tìm thấy.

## Độ phức tạp

Thời gian `O(mn)` trong miền nguồn. Với mở rộng 0 cột, có thêm `O(m)` để kiểm
tra hình dạng; viết chung là `O(m(n+1))`. Bộ nhớ phụ `O(n+1)`, không sao chép
ma trận hoặc dùng đầu vào làm vùng nhớ DP.

## Ví dụ chạy được

Lưu thành `/tmp/lc-221-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<char>> matrix{
        {'1','1','1','0'}, {'1','1','1','1'},
        {'0','1','1','1'}, {'0','1','1','1'}};
    std::cout << lab::Solution{}.maximalSquare(matrix) << '\n'; // 9
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-221-maximal-square-cpp /tmp/lc-221-example.cpp -o /tmp/lc-221-example
/tmp/lc-221-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-221-maximal-square-cpp/test.cpp -o /tmp/lc-221-test
/tmp/lc-221-test
make test
make test-all
```

## Biên và kiểm thử

Oracle duyệt mọi góc trên trái, mọi cạnh và kiểm tra từng ô trong hình vuông,
không dùng công thức DP. Đối chiếu 682 ma trận nhị phân với `1..3` hàng,
`1..3` cột. Các ca riêng phân biệt cạnh và diện tích, kiểm tra số 0 làm ngắt
hình vuông, một hàng/cột, ma trận 300x300 toàn 1/toàn 0, ma trận rỗng, 0 cột
và hàng lệch độ dài. Mọi ca xác nhận đầu vào không đổi. Test báo sai bằng mã
thoát khác 0 cả trong chế độ `NDEBUG`.

## Bài tập

1. Trả thêm tọa độ góc trên trái của một hình vuông tối ưu.
2. Vì sao không thể bỏ trạng thái chéo khỏi công thức?
3. Nếu cần hình chữ nhật toàn 1 lớn nhất, DP cạnh vuông này còn dùng được không?
