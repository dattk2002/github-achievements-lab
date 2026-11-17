# LeetCode 45 — Jump Game II (C++17)

Nguồn: [Jump Game II trên LeetCode](https://leetcode.com/problems/jump-game-ii/),
độ khó Medium. Diễn giải, ví dụ, lời giải và kiểm thử được tự viết.

## Hợp đồng

`lab::Solution::jump(std::vector<int>& nums)` trả số bước nhảy **ít nhất**
từ chỉ số 0 tới chỉ số cuối. Từ `i` được chọn độ dài tiến không vượt quá
`nums[i]`. Hàm giữ nguyên đầu vào. Khác bài 55 chỉ kiểm tra khả năng tới
đích, ở đây cần phân biệt đường đi ngắn với đường đi dài.

Nguồn có `1 <= n <= 10000`, `0 <= nums[i] <= 1000` và bảo đảm tới đích.
Kích thước theo nguồn là tiền điều kiện không kiểm tra. Mở rộng: mảng
rỗng hoặc không có đường đi trả `-1`; mảng một phần tử không âm trả 0.
Mọi giá trị âm đều gây `std::invalid_argument` trước khi tìm đường, kể
cả ô không tới được. Bước lớn hơn 1000, tới `INT_MAX`, cũng được xử lý.

## Tham lam theo lớp BFS

Giữ `layerEnd`: biên xa nhất tới được bằng số bước hiện tại. Trong khi
quét hết lớp, `farthest` thu thập biên xa nhất có thể tới bằng thêm một
bước. Khi `i == layerEnd`:

- Nếu biên không tiến, không thể tới đích.
- Nếu biên tiến, tăng bộ đếm bước và chuyển `layerEnd = farthest`.
- Nếu biên mới là chỉ số cuối, trả bộ đếm.

Để tránh tràn chỉ số, chặn khoảng nhảy bằng `last - i` **trước** khi cộng
vào `i`. Không cần hàng đợi vì các chỉ số tới được bằng tối đa một số
bước luôn tạo thành một đoạn liên tục từ 0.

Chứng minh: lớp ban đầu có biên 0 và cần 0 bước. Sau khi quét mọi ô của
lớp hiện tại, mọi bước nhảy từ chúng đã được xét; `farthest` vì vậy là
biên chính xác của lớp kế tiếp. Không có ô ngoài biên cũ tới được bằng
ít bước hơn. Khi đích lần đầu nằm trong lớp mới, số lớp đã chuyển chính
là số bước ít nhất. Nếu biên không đổi thì không có lớp tiếp theo.

Ví dụ `[2,0,3,0,0,1]`: từ 0 tới được đoạn `0..2` với một bước. Xét ô 2
đưa biên tới 5, nên cần hai bước, theo đường `0 -> 2 -> 5`.

## Độ phức tạp

`O(n)` thời gian, gồm xác thực toàn bộ đầu vào; `O(1)` bộ nhớ phụ.
Mỗi chỉ số chỉ được quét một lần, không thử riêng từng độ dài nhảy.

## Ví dụ chạy được

Lưu thành `/tmp/lc45-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> nums{2, 0, 3, 0, 0, 1};
    std::cout << lab::Solution{}.jump(nums) << '\n'; // 2
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-45-jump-game-ii-cpp /tmp/lc45-example.cpp -o /tmp/lc45-example
/tmp/lc45-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-45-jump-game-ii-cpp/test.cpp -o /tmp/lc45-test
/tmp/lc45-test
make test
make test-all
```

## Biên và kiểm thử

87.381 mảng dài `0..8` với giá trị `0..3` được so với oracle xét mọi cạnh
tiến và cập nhật khoảng cách nhỏ nhất, không dùng biên lớp tham lam.
Có thêm mảng 10.000 ô cần 9.999 bước, bước 1000 cần 10 bước, đoạn chặn
gần đích, `INT_MAX`, số âm và xác nhận đầu vào không đổi. Test trả mã
thoát khác 0 khi sai, kể cả với `NDEBUG`.

## Bài tập

1. Trả thêm một đường đi ngắn nhất và giải thích cách lưu cha.
2. So sánh bộ nhớ với BFS có hàng đợi trên cùng đồ thị chỉ số.
3. Nếu mỗi bước nhảy có giá khác nhau, vì sao đếm lớp không còn đủ?
