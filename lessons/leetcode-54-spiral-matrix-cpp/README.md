# LeetCode 54 — Duyệt ma trận theo đường xoắn ốc

Nguồn công khai: [LeetCode 54: Spiral Matrix](https://leetcode.com/problems/spiral-matrix/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-08**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`std::vector<int> lab::Solution::spiralOrder(std::vector<std::vector<int>>& matrix)` trả các giá trị theo chiều kim đồng hồ, bắt đầu tại góc trên trái, mỗi ô đúng một lần. Hàm không sửa ma trận; các giá trị trùng vẫn được giữ theo từng vị trí.

Bài gốc có 1..10 hàng và 1..10 cột, ma trận chữ nhật, giá trị trong `[-100,100]`. Bản này mở rộng ma trận không hàng hoặc chữ nhật có 0 cột thành vector rỗng. Ma trận răng cưa ném `std::invalid_argument`, kể cả khi hàng đầu rỗng nhưng hàng sau không rỗng. Các cận kích thước/giá trị khác là tiền điều kiện, không được xác minh lại; trong cận gốc, chỉ số `int` và tích số ô đều an toàn.

## Bốn biên và chứng minh

Giữ hình chữ nhật ô chưa thăm bằng `top`, `bottom`, `left`, `right`. Mỗi lượt đọc cạnh trên từ trái sang phải rồi tăng top; đọc cạnh phải từ trên xuống dưới rồi giảm right. Nếu còn hàng, đọc cạnh dưới từ phải sang trái rồi giảm bottom. Nếu còn cột, đọc cạnh trái từ dưới lên trên rồi tăng left.

Bất biến: trước mỗi lượt, mọi ô chưa xuất hiện nằm đúng trong hình chữ nhật còn lại, các ô bên ngoài đã xuất hiện đúng một lần theo đường xoắn ốc. Mỗi cạnh được đọc rồi gỡ khỏi hình chữ nhật trước khi đọc cạnh tiếp, tránh lặp góc. Kiểm tra còn hàng/cột trước hai cạnh sau tránh đọc lại khi lớp cuối chỉ có một hàng, một cột hoặc một ô. Sau một vòng, bất biến được duy trì với hình chữ nhật nhỏ hơn; khi hai biên vượt nhau thì mọi ô đã được đọc.

Thuật toán làm việc theo vị trí, không dùng giá trị để đánh dấu. Không cần ma trận visited và không đổi đầu vào. Với kích thước m×n hợp lệ của bài, thời gian O(mn), O(1) bộ nhớ phụ ngoài O(mn) kết quả. Kiểm tra chữ nhật thêm O(m); với phần mở rộng 0 cột, chỉ bước kiểm tra này tốn O(m).

## Ví dụ chạy được

Lưu thành `/tmp/spiral-example.cpp`, chạy từ gốc repo:

```cpp
#include "lessons/leetcode-54-spiral-matrix-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::vector<int>> matrix{{2,4,6,8}, {10,12,14,16}, {18,20,22,24}};
    lab::Solution solution;
    const auto result = solution.spiralOrder(matrix);
    for (std::size_t i = 0; i < result.size(); ++i) {
        if (i) std::cout << ',';
        std::cout << result[i];
    }
    std::cout << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/spiral-example.cpp -o /tmp/spiral-example
/tmp/spiral-example
```

Kết quả: `2,4,6,8,16,24,22,20,18,10,12,14`.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-54-spiral-matrix-cpp/test.cpp -o /tmp/spiral-test
/tmp/spiral-test
make test-all
```

Oracle dùng hướng di chuyển và ma trận visited: rẽ khi gặp biên hoặc ô đã thăm, khác thuật toán thu hẹp hình chữ nhật. Đối chiếu mọi kích thước 1..10 hàng/cột (100 hình dạng) với giá trị riêng cho từng ô, nên phát hiện được thiếu/lặp vị trí. Có ví dụ tính tay 3×4, một hàng, một cột, giá trị âm/cực trị, ma trận rỗng/0 cột và ma trận răng cưa. Kiểm tra không sửa đầu vào và dùng điều kiện trả mã 1 khi sai cả với `NDEBUG`.

## Bài tập

1. Bắt đầu tại góc trên phải hoặc đi ngược chiều kim đồng hồ: thứ tự đọc biên đổi thế nào?
2. Tạo ma trận m×n chứa các số theo thứ tự xoắn ốc thay vì đọc ma trận có sẵn.
3. Thiết kế iterator sinh từng ô mà không lưu toàn bộ vector kết quả; trạng thái nào cần được giữ?
