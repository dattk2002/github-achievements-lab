# LeetCode 309 — Best Time to Buy and Sell Stock with Cooldown (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/).
Diễn giải, ví dụ và lời giải dưới đây được viết riêng.

## Hợp đồng

`lab::Solution::maxProfit(std::vector<int>& prices)` trả lợi nhuận tối đa khi mua
bán nhiều lần, chỉ giữ tối đa một cổ phiếu và sau mỗi ngày bán phải nghỉ trọn
một ngày trước khi mua lại. Không có phí giao dịch. Có thể không giao dịch,
cho kết quả `0`; cổ phiếu chưa bán không được tính là lợi nhuận cuối cùng.
Hàm không thay đổi mảng giá.

Theo nguồn: `1 <= n <= 5000`, `0 <= prices[i] <= 1000`; đây là tiền điều kiện
không kiểm tra. Mở rộng riêng: mảng rỗng trả `0`. Mỗi lần bán lãi tối đa `1000`,
số lần bán không vượt `floor(n/2)`, nên lợi nhuận không quá `2500000`, vừa `int`.

## Ba trạng thái cuối ngày

- `held`: lợi nhuận tốt nhất khi đang giữ một cổ phiếu.
- `sold`: lợi nhuận tốt nhất khi vừa bán trong ngày này.
- `rest`: không giữ cổ phiếu và không bán trong ngày này, gồm cả ngày nghỉ bắt buộc.

Ngày đầu: `held = -prices[0]`, `rest = 0`, `sold` bất khả thi được biểu diễn
bằng `numeric_limits<int>::min()/4`. Với giá `p` của ngày kế tiếp:

```text
next_held = max(held, rest - p)
next_sold = held + p
next_rest = max(rest, sold)
```

Mọi vế phải phải đọc trạng thái của **ngày trước**. Sau ngày vừa bán, chỉ có thể
chuyển sang `rest`, không được mua ngay ngày kế tiếp. Chỉ ngày tiếp theo nữa
mới dùng được `rest` để mua. Kết quả là `max(rest,sold)`.

Với `[2,5,1,2,6]`, mua ngày 0 giá 2, bán ngày 1 giá 5, nghỉ ngày 2,
mua ngày 3 giá 2, bán ngày 4 giá 6: tổng lãi `3+4=7`.
Cộng mọi chênh lệch tăng sẽ bỏ qua điều kiện nghỉ và có thể cho kết quả sai.

### Chứng minh

Ba trạng thái phân hoạch mọi lịch giao dịch hợp lệ theo trạng thái cuối ngày.
Giữ cổ phiếu hôm nay chỉ có thể do giữ từ hôm qua hoặc mua từ trạng thái nghỉ;
vừa bán chỉ có thể từ trạng thái đang giữ; nghỉ chỉ có thể từ nghỉ hoặc vừa bán
hôm qua. Các phép chuyển đều hợp lệ và liệt kê đủ khả năng. Lấy `max` giữ lịch
tốt nhất cho từng trạng thái. Cơ sở ngày đầu đúng, nên quy nạp theo ngày cho
mọi trạng thái tối ưu. Bỏ `held` khi kết thúc vì còn cổ phiếu chưa thanh toán.

Giá trị bất khả thi chỉ được dùng trong phép `max` với `rest`, không được cộng
trực tiếp với giá; các phép tính tiền còn lại nằm trong giới hạn `int` của nguồn.

## Độ phức tạp

Thời gian `O(n)`, bộ nhớ phụ `O(1)`; không tạo bản sao đầu vào.

## Ví dụ chạy được

Lưu thành `/tmp/cooldown-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> prices{2,5,1,2,6};
    std::cout << lab::Solution{}.maxProfit(prices) << '\n'; // 7
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-309-best-time-to-buy-and-sell-stock-with-cooldown-cpp /tmp/cooldown-example.cpp -o /tmp/cooldown-example
/tmp/cooldown-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-309-best-time-to-buy-and-sell-stock-with-cooldown-cpp/test.cpp -o /tmp/cooldown-test
/tmp/cooldown-test
make test
make test-all
```

## Biên và kiểm thử

Oracle độc lập chọn mọi cặp ngày mua/bán rồi đệ quy từ ngày `sell+2`, liệt kê
các lịch giao dịch thay vì dùng DP. Kiểm tra toàn bộ 3280 mảng dài `0..7` trên
`{0,1,3}`. Có ca nghỉ ngăn giao dịch hấp dẫn, giá giảm, không giao dịch, giá 0,
đầu vào ngắn mở rộng và 5000 ngày. Với 1250 nhóm `[0,1000,0,0]`, mỗi nhóm có
một đỉnh giá và đủ thời gian nghỉ, tổng tối ưu `1250000`. Mỗi ca kiểm tra đầu
vào giữ nguyên. Test vẫn thoát lỗi khác 0 khi có sai lệch với `NDEBUG`.

## Bài tập

1. Thêm phí cố định cho mỗi lần bán: thay phép chuyển nào?
2. Tổng quát hóa nghỉ `k` ngày; mô tả trạng thái và chi phí bộ nhớ.
3. Truy vết một lịch giao dịch tối ưu, kể cả khi nhiều lịch cùng lợi nhuận.
