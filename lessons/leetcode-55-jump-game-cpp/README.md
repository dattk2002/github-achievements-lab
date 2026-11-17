# LeetCode 55 — Jump Game (C++17)

Nguồn: [Jump Game trên LeetCode](https://leetcode.com/problems/jump-game/),
độ khó Medium. Tóm tắt, ví dụ, lời giải và kiểm thử được tự viết.

## Hợp đồng

`lab::Solution::canJump(std::vector<int>& nums)` cho biết có thể đi từ chỉ
số 0 tới chỉ số cuối hay không. Tại `i`, được nhảy về phía trước từ 1 tới
`nums[i]` ô, không nhất thiết nhảy hết độ dài. Đầu vào được giữ nguyên.

Miền của nguồn: `1 <= n <= 10000`, mỗi bước thuộc `[0, 100000]`. Bài học
mở rộng: mảng rỗng trả `false`, một phần tử không âm trả `true` vì đã ở
đích. Mọi số âm đều gây `std::invalid_argument`, kể cả phần tử nằm sau
một đoạn không thể tới được; kiểm tra toàn bộ trước khi tìm đường.
Giới hạn kích thước theo nguồn là tiền điều kiện, không được kiểm tra.

## Thuật toán tham lam và bất biến

Giữ `farthest`: chỉ số xa nhất đã biết có thể tới. Ban đầu là 0. Duyệt `i`
theo thứ tự tăng, chỉ khi `i <= farthest`. Từ `i`, mở rộng biên tới
`max(farthest, i + nums[i])`. Nếu độ dài nhảy ít nhất là `last - i`, có
thể tới đích và trả `true`. So sánh khoảng cách trước phép cộng tránh
tràn số khi bước nhảy lớn. Nếu hết các chỉ số tới được thì trả `false`.

Bất biến: mọi chỉ số trong `[0, farthest]` đều tới được, vì một bước nhảy
cho phép chọn **mọi** khoảng cách không vượt quá giới hạn. Khi xét một
chỉ số trong đoạn đó, mọi ô mới từ bước nhảy của nó cũng tới được.
Ngược lại, nếu ô kế tiếp vượt `farthest`, không ô nào đã tới được có cạnh
đi tới nó; không có cách vượt khoảng trống. Vì vậy, thuật toán trả `true`
đúng khi tồn tại đường đi tới đích. Đây là mở rộng một biên khả thi, không
phải luôn chọn cú nhảy xa nhất làm đường đi thực tế.

Ví dụ `[2, 0, 2, 0, 0]`: từ ô 0, biên là 2; ô 1 không mở rộng được nhưng
ô 2 đưa biên tới 4. Với `[1, 0, 2]`, biên dừng ở 1 nên không tới ô 2.

## Độ phức tạp

`O(n)` thời gian, kể cả kiểm tra số âm; `O(1)` bộ nhớ phụ. Không sửa mảng,
không dựng bảng đường đi và không dùng đệ quy.

## Ví dụ chạy được

Lưu thành `/tmp/lc55-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> nums{2, 0, 2, 0, 0};
    std::cout << std::boolalpha << lab::Solution{}.canJump(nums) << '\n'; // true
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-55-jump-game-cpp /tmp/lc55-example.cpp -o /tmp/lc55-example
/tmp/lc55-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-55-jump-game-cpp/test.cpp -o /tmp/lc55-test
/tmp/lc55-test
make test
make test-all
```

## Biên và kiểm thử

87.381 mảng dài `0..8` với bước nhảy `0..3` được so với oracle đánh dấu
từng cạnh tiến hợp lệ, không dùng biên tham lam. Có thêm mảng 10.000 ô,
đích vừa đủ, số 0 chặn đường, bước `INT_MAX`, đầu vào âm và kiểm tra mảng
không bị thay đổi. Test dùng mã thoát khác 0 khi sai, kể cả với `NDEBUG`.

## Bài tập

1. Lưu một đường đi hợp lệ mà không biến thành thuật toán thử mọi đường.
2. Tìm số bước nhảy ít nhất và giải thích vì sao cần thêm trạng thái.
3. Nếu mỗi ô chỉ cho phép nhảy đúng một độ dài, bất biến trên sai ở đâu?
