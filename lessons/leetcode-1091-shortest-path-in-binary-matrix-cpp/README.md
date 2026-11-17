# LeetCode 1091 — Shortest Path in Binary Matrix (C++17)

Nguồn: [Shortest Path in Binary Matrix trên LeetCode](https://leetcode.com/problems/shortest-path-in-binary-matrix/),
độ khó Medium. Tóm tắt, lời giải, ví dụ và test được tự viết.

## Hợp đồng

`lab::Solution::shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid)`
trả độ dài đường ngắn nhất từ góc trên trái tới góc dưới phải của ma
trận vuông. Chỉ đi qua ô 0, mỗi bước tới một trong **tám** ô kề, gồm
cả đường chéo. Độ dài tính bằng **số ô** trên đường, nên một ô trống có
độ dài 1. Không có đường hoặc đầu/đích bị chặn thì trả `-1`. Hàm giữ
nguyên ma trận đầu vào.

Nguồn giới hạn cạnh `1..100`, mỗi ô là 0 hoặc 1. Giới hạn cạnh tối đa
là tiền điều kiện không kiểm tra. Mở rộng: ma trận rỗng trả `-1`;
không vuông hoặc có giá trị khác 0/1 gây `std::invalid_argument`.
Kiểm tra toàn bộ đầu vào trước khi kết luận đầu/đích bị chặn. `{{}}`
không phải ma trận rỗng hợp lệ vì có một hàng nhưng không có cột.

## BFS với khoảng cách riêng

Xem mỗi ô trống như một đỉnh, hai ô trống kề theo tám hướng có cạnh
trọng số 1. Khởi tạo khoảng cách toàn bộ là `-1`, riêng ô đầu là 1,
đưa ô đầu vào hàng đợi. Mỗi lần lấy một ô ra:

1. Nếu là đích, trả khoảng cách đang lưu.
2. Xét tám hướng, bỏ ô ngoài biên, bị chặn hoặc đã có khoảng cách.
3. Đánh dấu ô mới bằng khoảng cách hiện tại cộng 1 ngay **trước** khi
   đưa vào hàng đợi để không thêm một ô nhiều lần.

Chứng minh: hàng đợi BFS xử lý khoảng cách không giảm. Khi một ô được
khám phá từ khoảng cách `d`, mọi đường ngắn hơn tới ô ấy phải đi qua
một lớp trước đó và đã khám phá nó rồi. Vì vậy lần đánh dấu đầu tiên
cho khoảng cách ngắn nhất. Khởi tạo bằng 1 chuyển cách đếm cạnh sang
cách đếm ô. Nếu hết hàng đợi, mọi ô tới được đã xét mà chưa gặp đích,
nên không tồn tại đường hợp lệ.

Ví dụ `[[0,1,1],[0,0,1],[1,0,0]]` đi chéo `(0,0) -> (1,1) -> (2,2)`,
độ dài 3. Hai ô sát đường chéo có thể bị chặn; quy tắc bài này vẫn
cho phép bước chéo, không yêu cầu các ô cạnh bên cũng trống.

## Độ phức tạp

Thời gian `O(n²)`, gồm xác thực và tối đa tám cạnh mỗi ô. Bộ nhớ phụ
`O(n²)` cho bảng khoảng cách và hàng đợi. Dùng bảng riêng để giữ nguyên
đầu vào và có thể gọi lại cùng ma trận.

## Ví dụ chạy được

Lưu thành `/tmp/lc1091-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<int>> grid{{0, 1, 1}, {0, 0, 1}, {1, 0, 0}};
    std::cout << lab::Solution{}.shortestPathBinaryMatrix(grid) << '\n'; // 3
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-1091-shortest-path-in-binary-matrix-cpp /tmp/lc1091-example.cpp -o /tmp/lc1091-example
/tmp/lc1091-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-1091-shortest-path-in-binary-matrix-cpp/test.cpp -o /tmp/lc1091-test
/tmp/lc1091-test
make test
make test-all
```

## Biên và kiểm thử

Oracle dựng đồ thị rồi dùng Floyd–Warshall, không dùng BFS. So sánh
trên cả 530 ma trận nhị phân vuông cạnh `1..3`. Test riêng gồm một ô,
đầu/đích bị chặn, bước chéo qua hai ô cạnh bên bị chặn, đường vòng
dài 6, ma trận trống `100 x 100` có đáp án 100, hàng tường kín không
thể vượt, ma trận sai dạng và giá trị không nhị phân. Mỗi ca kiểm tra
đầu vào không đổi; mọi lỗi trả mã thoát khác 0 ngay cả với `NDEBUG`.

## Bài tập

1. Dùng thông tin cha để khôi phục một đường đi ngắn nhất.
2. Nếu chỉ cho bốn hướng, đáp án của ví dụ thay đổi thế nào?
3. Nếu mỗi ô có chi phí dương khác nhau, khi nào phải dùng Dijkstra?
