# LeetCode 64: Minimum Path Sum (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/minimum-path-sum/). Độ khó: Medium.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::minPathSum(std::vector<std::vector<int>>& grid)` trả tổng nhỏ
nhất trên đường từ ô trên trái đến ô dưới phải, mỗi bước chỉ đi xuống hoặc
sang phải. Tính cả ô đầu và ô cuối. Hàm không thay đổi lưới.

Nguồn quy định lưới chữ nhật, `1 <= m,n <= 200`, `0 <= grid[i][j] <= 200`.
Giới hạn kích thước và giá trị là tiền điều kiện. Quy tắc mở rộng có kiểm tra:
lưới rỗng, hàng đầu rỗng hoặc các hàng khác độ dài ném `std::invalid_argument`
trước khi chạy DP, không sửa đầu vào. Mọi đường có `m+n-1` ô, tổng tối đa
`399*200=79800`, vừa `int` 32 bit.

## Quy hoạch động một hàng

Gọi `D[r][c]` là tổng nhỏ nhất để đến ô `(r,c)`. Hàng đầu chỉ có một đường đi
sang phải, cột đầu chỉ có một đường đi xuống. Với ô bên trong:

```text
D[r][c] = min(D[r-1][c], D[r][c-1]) + grid[r][c]
```

Lưu một vector `cost` theo cột. Khởi tạo tổng dồn của hàng đầu. Với mỗi hàng
sau, cập nhật `cost[0]` rồi quét từ trái sang phải: `cost[c]` trước khi ghi đè
là ô phía trên, `cost[c-1]` đã cập nhật là ô bên trái. Kết quả ở cuối vector.

Với `[[1,7,2],[2,3,4]]`, đường xuống, phải, phải có tổng `1+2+3+4=10`.
Chọn ô kề nhỏ hơn ở mỗi bước không phải một thuật toán đúng nói chung.

### Vì sao đúng?

Mọi đường đến một ô trong lưới chỉ có thể đi từ trên hoặc từ trái. Nếu đoạn
đến ô trước chưa tối ưu, thay nó bằng đường tốt hơn sẽ giảm tổng của cả đường.
Vì vậy chọn tổng nhỏ hơn của hai ô trước rồi cộng ô hiện tại là đủ, và cả hai
lựa chọn đều tạo đường hợp lệ. Hàng/cột đầu là cơ sở, quy nạp theo `r+c`
chứng minh bảng đúng. Thứ tự cập nhật một hàng giữ nguyên hai giá trị phụ
thuộc cần dùng, nên tối ưu bộ nhớ không làm thay đổi kết quả.

## Độ phức tạp

Thời gian `O(mn)`, bộ nhớ phụ `O(n)` theo số cột. Không sao chép toàn bộ lưới
và không dùng chính lưới đầu vào làm vùng nhớ DP.

## Ví dụ chạy được

Lưu thành `/tmp/lc-64-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<int>> grid{{1,7,2},{2,3,4}};
    std::cout << lab::Solution{}.minPathSum(grid) << '\n'; // 10
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-64-minimum-path-sum-cpp /tmp/lc-64-example.cpp -o /tmp/lc-64-example
/tmp/lc-64-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-64-minimum-path-sum-cpp/test.cpp -o /tmp/lc-64-test
/tmp/lc-64-test
make test
make test-all
```

## Biên và kiểm thử

Oracle liệt kê đệ quy mọi đường sang phải/xuống, không ghi nhớ bảng DP.
Đối chiếu toàn bộ 21297 lưới có `1..3` hàng, `1..3` cột trên `{0,1,4}`.
Kiểm tra riêng một ô, một hàng, một cột, toàn 0, lưới không vuông và lưới
200x200 toàn 200 cho kết quả `79800`. Các lưới sai cấu trúc phải ném ngoại lệ.
Mỗi ca xác nhận đầu vào giữ nguyên; kiểm tra lỗi không dùng `assert`, nên
vẫn thoát khác 0 với `NDEBUG`.

## Bài tập

1. Lưu thêm lựa chọn để khôi phục một đường đi tối ưu.
2. Tìm phản ví dụ cho quy tắc luôn đi vào ô kề có giá trị nhỏ hơn.
3. Nếu cho phép đi chéo xuống phải, sửa công thức và trạng thái bộ nhớ ra sao?
