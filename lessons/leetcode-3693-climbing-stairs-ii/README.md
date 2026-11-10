# LeetCode 3693: Climbing Stairs II — C++17

Nguồn: [Climbing Stairs II](https://leetcode.com/problems/climbing-stairs-ii/).
Ngày nguồn (`source_date`): 2026-11-10. Độ khó: Medium.
Phần diễn giải, ví dụ và lời giải dưới đây được viết riêng cho bài học.

## Hợp đồng và tiền điều kiện

`lab::Solution::climbStairs(int n, std::vector<int>& costs)` trả về chi phí
nhỏ nhất để đi từ bậc 0 đến đúng bậc n. Mỗi lần tiến 1, 2 hoặc 3 bậc;
đáp tại bậc j sau bước nhảy dài d phải trả `costs[j-1] + d*d`.
Không trả phí ở bậc 0, không trả phí cho bậc bị bỏ qua, có trả phí bậc cuối.
Vector C++ đánh chỉ số từ 0, khác cách đánh số bậc từ 1 trong đề.

Tiền điều kiện: `1 <= n == costs.size() <= 100000` và
`1 <= costs[i] <= 10000`. Hàm không sửa vector và không kiểm tra dữ liệu
ngoài miền này. Chữ ký dùng tham chiếu không const để giữ giao diện gốc.

## Thuật toán

Gọi `D[j]` là chi phí tối ưu đến bậc j, với `D[0] = 0`:

```text
D[j] = costs[j-1] + min(D[j-d] + d*d), 1 <= d <= min(3,j)
```

Quét j tăng dần. Chỉ cần ba trạng thái gần nhất, lưu trong mảng vòng
`recent[k % 3]`. Tính xong toàn bộ ứng viên mới ghi `D[j]`, vì ô sắp ghi
cũng đang giữ `D[j-3]`. Ở những bậc đầu chỉ đọc trạng thái có chỉ số không âm;
các ô khởi tạo khác chưa được xem là trạng thái hợp lệ.

### Chứng minh

Bước nhảy cuối của mọi đường tới j có độ dài d thuộc 1..3 và d không vượt j.
Phần đường trước đó kết thúc tại j-d. Nếu phần này chưa tối ưu, thay bằng
đường rẻ hơn tới j-d sẽ giảm tổng phí mà vẫn giữ bước nhảy cuối hợp lệ.
Vì vậy mọi lời giải tối ưu được công thức xét đến. Ngược lại, mỗi ứng viên
trong công thức ghép một đường hợp lệ với một bước nhảy hợp lệ.
Từ cơ sở D[0], quy nạp theo j cho thấy mọi D[j] đều đúng. Mảng vòng giữ
đủ các tiền nhiệm cho đến khi đọc xong, nên kết quả không đổi.

Thời gian `O(n)`, bộ nhớ phụ `O(1)`. Một đường chỉ nhảy từng bậc tốn tối đa
`10001*n <= 1000100000`. Mỗi ứng viên trung gian không vượt
`10001*(j-d) + 10000 + d*d <= 10001*j`, nên cả phép cộng cũng vừa `int`
32 bit. Giá trị vô cực chỉ dùng để khởi tạo biến lấy min, không đem cộng.

## Ví dụ tự xây dựng

- `costs = [1,10000,1]`: đường `0 → 1 → 3` tốn `(1+1)+(1+4)=7`;
  nhảy thẳng tới 3 tốn 10, còn ghé bậc 2 rất đắt.
- `costs = [2,2]`: hai bước đơn tốn 6, bằng một bước đôi tốn 6.
- `costs = [1,100,100,1]`: chọn `0 → 1 → 4`, tổng `2+10=12`.

Lưu ví dụ sau thành `/tmp/lc3693-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> costs{1,10000,1};
    std::cout << lab::Solution{}.climbStairs(3, costs) << '\n'; // 7
}
```

Chạy từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-3693-climbing-stairs-ii /tmp/lc3693-example.cpp -o /tmp/lc3693-example
/tmp/lc3693-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-3693-climbing-stairs-ii/test.cpp -o /tmp/lc3693-test
/tmp/lc3693-test
make test
```

## Kiểm thử và các biên dễ sai

Bộ kiểm thử dùng kiểm tra tường minh và `EXIT_FAILURE`, không dùng `assert`,
nên lỗi vẫn trả mã khác 0 khi định nghĩa `NDEBUG`. Mỗi ca kiểm tra cả việc
bảo toàn đầu vào. Các ca tay bắt lỗi lệch chỉ số, thiếu phí bậc cuối,
quên bước nhảy dài 3, chọn tham lam và xử lý sai các bậc đầu.

Oracle độc lập duyệt tiến mọi đường hoàn chỉnh, cộng phí từng lần đáp,
không dùng bảng DP hay ghi nhớ. Đối chiếu toàn bộ 3279 vector độ dài 1..7
trên tập giá trị `{1,4,10000}`.

Hai ca n=100000 kiểm tra vòng lặp lớn và số học:

- Toàn 1: mỗi bước dài d tốn `1+d*d >= 2*d`; nhảy đơn đạt cận 200000.
- Toàn 10000: cần ít nhất 33334 lần đáp. Với số lần này, tổng bình phương
  nhỏ nhất đạt bởi 33332 bước dài 3 và hai bước dài 2; kết quả
  `33334*10000 + 33332*9 + 2*4 = 333639996`.
  Với k lần đáp, bất đẳng thức `d*d >= 5*d-6` cho d=1..3 cho cận tổng
  `10000*k + 5*n - 6*k = 9994*k + 5*n`. Cấu hình trên đạt cận tại
  k=33334; cận tăng theo k, nên thêm lần đáp không cải thiện kết quả.

## Bài tập

1. Dùng bảng D đầy đủ và lưu tiền nhiệm để khôi phục một đường tối ưu.
2. Cho phép bước nhảy dài tối đa K: sửa công thức, thời gian và bộ nhớ.
3. Tìm phản ví dụ cho cách luôn chọn bước nhảy có phí tức thời thấp nhất.
