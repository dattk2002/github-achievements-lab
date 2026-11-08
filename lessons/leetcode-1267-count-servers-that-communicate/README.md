# LeetCode 1267 — Đếm máy chủ có thể liên lạc

Nguồn: [Count Servers that Communicate](https://leetcode.com/problems/count-servers-that-communicate/).
Ngày nguồn (`source_date`): **2026-11-08**. Độ khó: **Medium**.
Bài học C++17 với tóm tắt, ví dụ, lời giải và kiểm thử tự viết.

## Hợp đồng và tiền điều kiện

`lab::Solution::countServers(std::vector<std::vector<int>>& grid)` trả về số
máy chủ có ít nhất một máy chủ khác cùng hàng hoặc cùng cột. Ô bằng 1 chứa
máy chủ, ô bằng 0 không chứa máy chủ. Khoảng cách và các ô trống ở giữa
không cản liên lạc. Chỉ chung đường chéo thì không đủ điều kiện.
Đếm máy chủ, không đếm cặp hay nhóm máy chủ.

Ma trận phải hình chữ nhật, có `1 <= m, n <= 250`, mọi ô thuộc `{0, 1}`.
Hàm giữ nguyên đầu vào dù tham số là tham chiếu không const để phù hợp
giao diện bài gốc. Không kiểm tra dữ liệu ngoài hợp đồng; ma trận rỗng,
hàng dài ngắn khác nhau hoặc giá trị khác 0/1 không được hỗ trợ.
Đáp án tối đa là `250 * 250 = 62500`, nằm trong kiểu `int`.

## Thuật toán và tính đúng đắn

1. Duyệt ma trận, lưu số máy chủ ở mỗi hàng trong `row_count` và mỗi cột
   trong `col_count`.
2. Duyệt lại. Với mỗi ô chứa máy chủ, tăng kết quả nếu số máy ở hàng đó
   lớn hơn 1 **hoặc** số máy ở cột đó lớn hơn 1.

Sau lượt đầu, mỗi máy chủ đã đóng góp đúng một lần vào bộ đếm hàng và
bộ đếm cột tương ứng. Với máy chủ tại `(r, c)`, `row_count[r] > 1` nghĩa là
có máy chủ khác cùng hàng vì bản thân nó đã chiếm một đơn vị; lập luận
tương tự áp dụng cho cột. Do đó điều kiện ở lượt hai là cần và đủ để máy
chủ này liên lạc được. Mỗi ô chỉ được xét một lần ở lượt hai, nên máy có
cả bạn cùng hàng lẫn bạn cùng cột cũng chỉ được tính một lần. Ô trống
không bao giờ được tính.

Thời gian **O(mn)** qua hai lượt duyệt; bộ nhớ phụ **O(m + n)** cho hai
mảng đếm. Không cần dựng đồ thị, tìm thành phần liên thông hay sửa ma trận.

## Ví dụ tự tạo

```text
1 0 1 0
0 1 0 0
```

Hai máy ở hàng đầu liên lạc được dù có ô trống ở giữa; máy ở hàng sau
không chung hàng/cột với chúng. Kết quả là **2**.

```text
0 1 0
1 1 1
0 1 0
```

Cả năm máy đều có bạn cùng hàng hoặc cột. Máy ở tâm chỉ tính một lần,
vì vậy kết quả là **5**. Một ma trận chỉ có một máy cho kết quả **0**.

Chương trình ví dụ đặt cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> grid{{1, 0, 1, 0}, {0, 1, 0, 0}};
    lab::Solution solution;
    std::cout << solution.countServers(grid) << '\n'; // 2
}
```

## Chạy và hiểu kiểm thử

Từ thư mục gốc repo:

```sh
make test
# Chạy riêng, kể cả khi NDEBUG được định nghĩa:
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-1267-count-servers-that-communicate/test.cpp \
  -o /tmp/lesson-1267-test
/tmp/lesson-1267-test
```

Bộ test dùng kiểm tra tường minh và `std::exit(EXIT_FAILURE)`, không phụ
thuộc `assert`. Test được viết trước lời giải; bản khung trả 0 thất bại
với hàng `{1, 0, 0, 1, 1}` có đáp án tính tay là 3.

Các ca cố định bắt lỗi tự liên lạc, chỉ xét ô kề nhau, dùng AND thay OR,
đếm trùng tại giao điểm hoặc tính cả ô trống. Có ma trận một ô, một hàng,
một cột, đường chéo cô lập, nhóm liên lạc kèm máy cô lập, và ma trận
250×250 toàn 0/toàn 1/đường chéo. Kiểm tra đầu vào không đổi và gọi lại
cùng đối tượng với kích thước khác để bắt trạng thái lưu sót.

Ngoài ra, duyệt mọi ma trận nhị phân với từng kích thước từ 1×1 đến 3×4.
Oracle độc lập liệt kê các cặp máy chủ phân biệt, đánh dấu hai đầu nếu
cùng hàng hoặc cột, rồi đếm số máy đã đánh dấu. Cách này kiểm tra trực tiếp
quan hệ liên lạc, không dùng lại bộ đếm hàng/cột của lời giải. Oracle chỉ
chạy trên lưới nhỏ vì có chi phí bình phương theo số máy chủ.

## Tự luyện

1. Tạo phản ví dụ cho điều kiện `row_count[r] > 1 && col_count[c] > 1`.
2. Chứng minh có thể lấy tổng số máy trừ số máy cô lập để ra cùng đáp án.
3. Nếu đầu vào chỉ là danh sách tọa độ máy chủ trên lưới rất lớn, hãy đề
   xuất cấu trúc lưu số lượng theo hàng/cột mà không cấp phát cả ma trận.
