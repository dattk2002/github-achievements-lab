# LeetCode 3789: Minimum Cost to Acquire Required Items — C++17

Nguồn: [Minimum Cost to Acquire Required Items](https://leetcode.com/problems/minimum-cost-to-acquire-required-items/).
Ngày nguồn (`source_date`): 2026-11-11. Độ khó: Medium.
Tóm tắt, ví dụ và lập luận dưới đây được viết riêng cho bài học.

## Hợp đồng và tiền điều kiện

```cpp
long long lab::Solution::minimumCost(int cost1, int cost2, int costBoth,
                                    int need1, int need2);
```

Có thể mua không giới hạn món riêng cho từng nhu cầu hoặc món chung đóng góp
một đơn vị vào cả hai nhu cầu. Hàm trả tổng chi phí nhỏ nhất để đáp ứng **ít nhất**
`need1` và `need2`; được phép mua dư, kể cả khi một nhu cầu bằng 0.

Tiền điều kiện: `1 <= cost1, cost2, costBoth <= 1000000` và
`0 <= need1, need2 <= 1000000000`. Hàm giả định đầu vào hợp lệ, không kiểm tra
ngoài miền này. Các tham số truyền theo giá trị.

## Thuật toán: xét ba điểm gãy

Giả sử mua `x` món chung. Do giá đều dương, số món riêng cần mua tốt nhất là
đúng phần còn thiếu. Chi phí tương ứng:

```text
F(x) = x*costBoth
     + max(0, need1-x)*cost1
     + max(0, need2-x)*cost2
```

Đặt `a = min(need1,need2)`, `b = max(need1,need2)`.
Chỉ cần tính `F(0)`, `F(a)`, `F(b)` và trả giá trị nhỏ nhất.
Không lặp đến số nhu cầu, vốn có thể lên tới một tỷ.

### Vì sao đúng?

Với một số món chung cố định, mua ít hơn phần thiếu sẽ không hợp lệ, mua
nhiều hơn chỉ tăng phí. Vì vậy F bao quát phương án tốt nhất cho mỗi x.

Trên đoạn nguyên `[0,a]`, mỗi món chung mới thay thế hai món riêng nên
F có mức thay đổi cố định `costBoth-cost1-cost2`. Trên `[a,b]`, nó chỉ thay
thế món riêng của nhu cầu lớn hơn, nên mức thay đổi vẫn cố định. Một hàm
tuyến tính trên đoạn đạt giá trị nhỏ nhất tại một đầu đoạn; nếu mức thay
đổi bằng 0, mọi điểm cùng giá. Sau b, cả hai nhu cầu đã đủ, mỗi món chung
mới chỉ cộng thêm `costBoth > 0`, nên không thể cải thiện.
Do đó một nghiệm tối ưu nằm trong `{0,a,b}`. Lập luận vẫn đúng khi hai
điểm trùng nhau hoặc nhu cầu bằng 0.

Thời gian `O(1)`, bộ nhớ phụ `O(1)`.
Dùng `long long` ngay từ trước phép nhân: riêng `10^9 * 10^6` đã vượt
`int` 32 bit. Với `0 <= x <= b`, từng tích không quá `10^15`, tổng thô
không quá `3*10^15`, an toàn trong số nguyên có dấu 64 bit. Chi phí tối ưu
không quá `10^15`, vì mua b món chung luôn là một phương án hợp lệ.

## Ví dụ tự xây dựng

- Giá `(7,4,8)`, nhu cầu `(4,2)`: không mua chung tốn 36;
  mua hai món chung và hai món riêng loại 1 tốn `16+14=30`;
  mua bốn món chung tốn 32. Kết quả là 30.
- Giá `(9,6,2)`, nhu cầu `(4,1)`: bốn món chung tốn 8, dù nhu cầu thứ
  hai bị vượt ba đơn vị. Dừng ở một món chung sẽ bỏ lỡ nghiệm tối ưu.
- Giá `(8,3,2)`, nhu cầu `(0,5)`: năm món chung tốn 10, rẻ hơn năm món
  riêng loại 2 tốn 15. Nhu cầu bằng 0 không cấm đóng góp dư.

Lưu chương trình sau thành `/tmp/lc3789-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
int main() {
    std::cout << lab::Solution{}.minimumCost(7, 4, 8, 4, 2) << '\n'; // 30
}
```

Chạy từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-3789-minimum-cost-to-acquire-required-items /tmp/lc3789-example.cpp -o /tmp/lc3789-example
/tmp/lc3789-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-3789-minimum-cost-to-acquire-required-items/test.cpp -o /tmp/lc3789-test
/tmp/lc3789-test
make test
```

## Kiểm thử và biên dễ sai

`test.cpp` kiểm tra tường minh và thoát bằng `EXIT_FAILURE` khi sai,
không dùng `assert`, nên vẫn phát hiện lỗi khi có `NDEBUG`.
Các đáp án tay bao phủ: không mua chung, mua đến nhu cầu nhỏ hơn, mua dư
đến nhu cầu lớn hơn, đổi vai hai loại, hai nhu cầu bằng nhau, một hoặc cả
hai bằng 0, giá hòa và các cận số học lớn.

Ví dụ cận lớn: mọi giá bằng một triệu và hai nhu cầu bằng một tỷ cho kết
quả `10^15`; giá riêng 999999 với nhu cầu `(10^9,0)` cho kết quả
`999999000000000`. Các ca này bắt lỗi nhân bằng `int` trước khi chuyển kiểu.

Oracle độc lập thử mọi bộ số lượng mua `(a,b,both)`, chỉ giữ bộ đủ hai nhu
cầu rồi lấy chi phí nhỏ nhất, không dùng công thức ba điểm gãy.
Chặn `a <= need1`, `b <= need2`, `both <= max(need1,need2)` là đủ: vượt
các chặn này có thể bỏ món thừa mà không mất tính hợp lệ, do giá dương.
Kiểm tra toàn bộ 7776 đầu vào với ba giá trong `1..6` và hai nhu cầu trong
`0..5`, bao gồm nhiều trường hợp hòa giá và mua dư.

## Bài tập

1. Viết lời giải tương đương bằng cách định giá phần nhu cầu chung và phần
   chênh lệch; chứng minh khi nào nên dùng món chung cho phần chênh lệch.
2. Trả thêm số món từng loại trong một phương án tối ưu. Quy định cách chọn
   khi có nhiều phương án cùng giá.
3. Nếu chỉ được mua tối đa K món chung, tập điểm cần xét thay đổi thế nào?
4. Tìm phản ví dụ cho quy tắc luôn ngừng mua món chung khi nhu cầu nhỏ hơn đã đủ.
