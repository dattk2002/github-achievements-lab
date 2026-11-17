# LeetCode 518 — Coin Change II (C++17)

Nguồn: [Coin Change II trên LeetCode](https://leetcode.com/problems/coin-change-ii/),
độ khó Medium. Ví dụ, lời giải, giải thích và test được tự viết.

## Hợp đồng

`lab::Solution::change(int amount, std::vector<int>& coins)` trả số tổ hợp
có tổng bằng `amount`, dùng không giới hạn đồng của mỗi mệnh giá. Chỉ số
lượng mỗi mệnh giá quyết định một tổ hợp: `2+2+3` và `3+2+2` là một cách.
Đây là **đếm số cách**, khác bài 322 tìm số đồng ít nhất. Giữ nguyên cả
nội dung lẫn thứ tự của `coins`.

Nguồn có `0 <= amount <= 5000`, `1..300` mệnh giá phân biệt trong
`[1,5000]`, bảo đảm kết quả cuối vừa số nguyên có dấu 32 bit. Giới hạn
trên là tiền điều kiện không kiểm tra. Bài học kiểm tra `amount < 0`,
mệnh giá không dương hoặc lặp và ném `std::invalid_argument`. Mở rộng:
không có mệnh giá thì chỉ tổng 0 có một tổ hợp rỗng; kết quả vượt
`std::numeric_limits<int>::max()` gây `std::overflow_error`. Môi trường
GCC của repo dùng `int` 32 bit.

## Quy hoạch động theo mệnh giá

Sắp xếp bản sao để kiểm tra trùng, rồi khởi tạo `ways[0] = 1`, các tổng
khác là 0. Với từng mệnh giá `coin`, duyệt tổng **tăng dần** từ `coin`
tới `amount`, cập nhật:

```text
ways[sum] += ways[sum - coin]
```

Bất biến: sau mỗi vòng ngoài, `ways[s]` đếm các tổ hợp của `s` chỉ dùng
các mệnh giá đã xử lý. Tổ hợp không có đồng mới đã nằm trong `ways[s]`;
tổ hợp có đồng mới được tạo bằng cách thêm một đồng vào tổ hợp của
`s - coin`. Hai nhóm không giao nhau. Tổng duyệt tăng nên `ways[s-coin]`
có thể đã dùng đồng mới, cho phép dùng nhiều lần. Mệnh giá ở vòng ngoài
ngăn đếm lại cùng tổ hợp theo các thứ tự khác nhau. Duyệt tổng giảm sẽ
biến thành mỗi loại chỉ được dùng một lần.

Ví dụ với `{2,3,7}` và tổng 12 có 4 tổ hợp, viết dưới dạng số lượng theo
thứ tự ba mệnh giá: `(6,0,0)`, `(3,2,0)`, `(0,4,0)`, `(1,1,1)`.

## Tránh tràn ở tổng trung gian

Kết quả cuối vừa `int` không bảo đảm mọi tổng nhỏ hơn cũng vừa. Ví dụ
chỉ có mệnh giá chẵn thì một tổng lẻ vẫn có 0 cách, dù nhiều tổng chẵn
có số cách cực lớn. Vì vậy không được ném lỗi ngay khi một ô DP vượt hạn.

Lưu mỗi ô bằng `long long`, chặn tại `cap = INT_MAX + 1` sau mỗi lần cộng.
Vì mọi số đếm đều không âm, `min(cap, a+b)` cho cùng kết quả dù chặn
`a`, `b` trước đó: thông tin về giá trị chính xác dưới `cap` được giữ
nguyên. Mỗi phép cộng không vượt `2*cap`, vừa `long long` trên môi trường
repo. Chỉ kiểm tra ô `ways[amount]` khi kết thúc: bằng `cap` thì báo tràn,
nhỏ hơn thì là kết quả chính xác.

## Độ phức tạp

Gọi `A = amount`, `C = coins.size()`. Thời gian
`O(C log(C + 1) + C(A + 1) + A + 1)`, gồm sắp xếp, xác thực, DP và
khởi tạo vector. Bộ nhớ phụ `O(A + C + 1)` cho DP và bản sao mệnh giá.
Cách viết này tính cả trường hợp `A = 0` hoặc `C = 0`.

## Ví dụ chạy được

Lưu thành `/tmp/lc518-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> coins{2, 3, 7};
    std::cout << lab::Solution{}.change(12, coins) << '\n'; // 4
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-518-coin-change-ii-cpp /tmp/lc518-example.cpp -o /tmp/lc518-example
/tmp/lc518-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-518-coin-change-ii-cpp/test.cpp -o /tmp/lc518-test
/tmp/lc518-test
make test
make test-all
```

## Biên và kiểm thử

3.200 bộ mệnh giá/tổng được so với oracle đệ quy liệt kê mọi số lượng
từng loại, chạy cả hai thứ tự mệnh giá. Kiểm tra tổng 0, không có loại,
không thể đổi, dùng lặp đồng và tổng 5000. Có 300 mệnh giá chẵn `2..600`
với tổng 4999 để bắt tràn trung gian dù đáp án là 0; tổng 5000 trên cùng
tập để bắt tràn đáp án cuối. Có kiểm tra đối số sai, không sửa `coins`,
và mã thoát khác 0 khi lỗi ngay cả với `NDEBUG`.

## Bài tập

1. Đổi hai vòng lặp và tìm một ví dụ bị đếm thành hoán vị.
2. Tính theo modulo khi bài mới không bảo đảm kết quả vừa kiểu nguyên.
3. Nếu mỗi mệnh giá có số đồng hữu hạn, chuyển trạng thái thế nào?
