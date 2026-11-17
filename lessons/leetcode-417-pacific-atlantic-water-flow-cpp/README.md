# LeetCode 417 — Pacific Atlantic Water Flow (C++17)

Nguồn: [Pacific Atlantic Water Flow trên LeetCode](https://leetcode.com/problems/pacific-atlantic-water-flow/),
độ khó Medium. Phần giảng giải, lời giải, ví dụ và test được tự viết.

## Hợp đồng

`lab::Solution::pacificAtlantic(std::vector<std::vector<int>>& heights)`
trả các tọa độ `[hàng, cột]` có đường nước chảy tới **cả hai** đại dương.
Pacific giáp trên/trái; Atlantic giáp dưới/phải. Mỗi bước chỉ tới một
trong bốn ô kề có độ cao bằng hoặc thấp hơn. Hai đường ra biển có thể khác
nhau. Không đi chéo, không sửa đầu vào, không trả trùng tọa độ.

Nguồn giới hạn `1 <= số hàng, số cột <= 200`, độ cao trong `[0,100000]`.
Các giới hạn này là tiền điều kiện không được kiểm tra. Mở rộng: ma trận
rỗng hoặc chữ nhật có 0 cột trả rỗng. Hàng dài ngắn khác nhau gây
`std::invalid_argument`, kể cả khi hàng đầu rỗng. Kết quả của bản cài đặt
này theo thứ tự hàng rồi cột; đề gốc không yêu cầu thứ tự.

## Đảo cạnh và BFS nhiều nguồn

Nếu chạy tìm đường từ từng ô thì cùng một vùng bị duyệt rất nhiều lần.
Thay vào đó, đảo mọi cạnh dòng nước. Từ một ô thấp, ta có thể đi ngược tới
ô kề bằng hoặc cao hơn. Chạy hai BFS:

- Khởi tạo đồng thời các ô ở cạnh trên/trái để tìm vùng Pacific.
- Khởi tạo đồng thời các ô ở cạnh dưới/phải để tìm vùng Atlantic.
- Lấy giao hai tập ô đã tới.

Đánh dấu ngay khi đưa vào hàng đợi. Góc chung của hai cạnh khởi tạo chỉ
được thêm một lần trong mỗi BFS. Điều kiện `>=` cho phép đi trên cao
nguyên; dùng `>` sẽ bỏ sai các đường qua ô bằng độ cao. BFS lặp tránh
tràn ngăn xếp trên ma trận lớn.

Chứng minh: đảo thứ tự một đường đi xuống từ ô `x` ra biển cho một đường
đi lên từ biên về `x`, và ngược lại. BFS nhiều nguồn duyệt đúng tất cả ô
có đường đi ngược từ một biên của đại dương đó. Vì vậy, một ô được đánh
dấu ở cả hai BFS đúng khi có đường nước đi tới từng đại dương.

Ví dụ `[[1,2],[4,3]]` trả `[[0,1],[1,0],[1,1]]`: ô cao 3 ở dưới phải
chảy ra Atlantic trực tiếp, và lên ô cao 2 để tới Pacific. Ô cao 1 ở trên
trái không thể chảy lên các ô cao hơn để tới Atlantic.

## Độ phức tạp

Với `R` hàng, `C` cột, mỗi BFS đưa một ô vào hàng đợi nhiều nhất một lần,
kiểm tra tối đa bốn cạnh. Thời gian `O(RC)`, bộ nhớ phụ `O(RC)` cho hai
tập đánh dấu và hàng đợi, cộng kết quả tối đa `O(RC)`.

## Ví dụ chạy được

Lưu thành `/tmp/lc417-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<int>> heights{{1, 2}, {4, 3}};
    for (const auto& cell : lab::Solution{}.pacificAtlantic(heights))
        std::cout << cell[0] << ',' << cell[1] << '\n'; // 0,1 rồi 1,0 rồi 1,1
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-417-pacific-atlantic-water-flow-cpp /tmp/lc417-example.cpp -o /tmp/lc417-example
/tmp/lc417-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-417-pacific-atlantic-water-flow-cpp/test.cpp -o /tmp/lc417-test
/tmp/lc417-test
make test
make test-all
```

## Biên và kiểm thử

Oracle chạy dòng nước **xuôi** từ từng ô, kiểm tra có chạm từng nhóm biên
hay không, không dùng BFS ngược từ biển. So sánh trên toàn bộ 21.297 ma
trận kích thước `1..3` mỗi chiều, độ cao `0..2`. Có thêm cao nguyên và mặt
dốc `200 x 200`, một hàng, một cột, ma trận rỗng, hàng lệch và kiểm tra
không thay đổi độ cao. So sánh toàn bộ danh sách tọa độ sau sắp xếp để
bắt cả kết quả thiếu, thừa và trùng. Không dùng `assert` nên `NDEBUG`
không vô hiệu hóa test.

## Bài tập

1. Trả hai bản đồ boolean thay cho danh sách giao nhau.
2. Khôi phục một đường chảy từ một ô hợp lệ ra mỗi đại dương.
3. Nếu thêm một vùng hồ bên trong, khởi tạo BFS ngược từ đâu?
