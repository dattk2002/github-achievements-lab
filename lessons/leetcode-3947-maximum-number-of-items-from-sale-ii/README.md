# LeetCode 3947: Maximum Number of Items From Sale II — Đếm lượt nhận quà và mua theo giá

Nguồn: [LeetCode 3947: Maximum Number of Items From Sale II](https://leetcode.com/problems/maximum-number-of-items-from-sale-ii/), Medium.
LeetCode Daily ngày **2026-11-28**. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::maximumSaleItems(std::vector<std::vector<int>>& items, int budget)`
trả tổng số bản mua và bản được tặng lớn nhất trong ngân sách. Mỗi hàng là
`{factor, price}`; có vô hạn bản mua của mỗi loại. Một bản mua được tặng tối đa
một bản của loại khác có factor là bội factor của nó. Mỗi cặp có hướng `(i,j)`
chỉ cho một quà; nhiều loại khác nhau có thể cùng tặng loại `j`. Quà không
sinh thêm quà. Hàm giữ nguyên `items`.

Tiền điều kiện: `1 <= n <= 100000`, mỗi hàng có hai số nguyên,
`1 <= factor <= n`, `1 <= price, budget <= 1000000000`.
Không kiểm tra đầu vào ngoài miền này.

## Từ quan hệ chia hết tới các lượt mua hai bản

Gọi `d[i]` là số chỉ số `j != i` mà `factor[j]` chia hết cho `factor[i]`.
Nếu mua `x` bản của loại `i`, nhận được tối đa `min(x,d[i])` quà. Cận này
đạt được bằng cách gán mỗi bản mua cho một đích khác nhau. Các nguồn độc
lập, vì một đích được nhận quà nhiều lần từ những nguồn khác nhau.

Đếm tần suất từng factor. Với mỗi `f`, cộng tần suất các bội `f,2f,...` rồi
trừ đúng **một** để loại chỉ số đang xét. Hai loại có factor giống nhau vẫn
có thể tặng nhau. Không trừ cả tần suất của factor đó.

Có thể xem loại `i` là tối đa `d[i]` lượt mua giá `price[i]`, mỗi lượt thu
hai bản; phần còn lại là mua một bản. Đặt `q` là giá rẻ nhất. Mọi lượt một
bản có thể mua ở giá `q`, nên lượt hai bản đắt hơn `2q` không cần chọn.
Sắp các nhóm lượt hai bản theo giá tăng dần; mua nhiều nhất trong giới hạn
của nhóm và ngân sách còn lại. Sau cùng mua bản lẻ giá `q`.

## Vì sao tham lam vẫn đúng khi có tiền dư?

Gọi `S(t)` là tổng giá của `t` lượt hai bản rẻ nhất có giá không quá `2q`.
Nếu dùng đúng `t` lượt như vậy, không có cách chọn lượt nào có chi phí thấp
hơn `S(t)`. Tổng số bản tối ưu ứng với lựa chọn này là

`G(t) = 2t + floor((B - S(t)) / q)`.

Thêm một lượt có giá `p <= 2q` làm tăng hai bản và làm giảm số bản lẻ tối đa
hai. Vì vậy `G(t+1) >= G(t)` khi cả hai lựa chọn đều đủ tiền. Chọn số lượt
hai bản lớn nhất mua được theo thứ tự giá chính là một nghiệm tối ưu.
Lượt giá đúng `2q` có thể dùng hoặc bỏ mà không cải thiện được đáp án.

Không cần mở rộng mỗi nhóm thành từng lượt: lấy
`min(d[i], remaining / price[i])` trong một phép tính. Số lượt tiềm năng có
thể gần `n²`, nhưng không lưu tổng này. Tích tiền đã mua bị chặn bởi ngân
sách còn lại; `total` dùng `long long`. Kết quả không quá `2B <= 2e9`, vừa `int`.

## Độ phức tạp

Sàng bội tốn `sum(n/f) = O(n log n)`, sắp xếp `O(n log n)`, duyệt mua `O(n)`.
Bộ nhớ phụ **O(n)**. Không có vòng lặp theo số tiền hoặc số bản mua.

## Ví dụ tự xây dựng

Với `items = {{1,4},{2,3},{3,8}}`, ngân sách `12`, loại factor `1` có hai
đích nhận quà. Mua hai bản loại này hết `8`, nhận hai quà; mua thêm một bản
loại giá `3`. Tổng cộng **5** bản, còn dư `1`.

## Chạy ví dụ

Tại thư mục bài học:

```sh
cat > /tmp/lc3947-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::vector<int>> items{{1,4},{2,3},{3,8}};
    std::cout << lab::Solution{}.maximumSaleItems(items, 12) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc3947-example.cpp -o /tmp/lc3947-example
/tmp/lc3947-example
```

Kết quả:

```text
5
```

## Kiểm thử và trường hợp biên

Oracle liệt kê trực tiếp mọi vector số lượng mua đủ tiền, đếm đích bằng
hai vòng lặp chia hết, không dùng sàng hoặc tham lam. Test xét **21552**
cặp cấu hình/ngân sách với `n=1..3`, factor trong `[1,n]`, giá `1..4`, ngân
sách `1..12`; thêm 500 ca seed cố định. Có ca không đủ tiền, một loại không
tự tặng, trùng factor, hết lượt quà, giá ở hai phía `2q`, quà không sinh quà.

Biên lớn: 100000 loại có cùng factor và giá `1`, ngân sách `1e9`, đáp án
`2e9`; giá `1e9`; toàn factor phân biệt. Các ca này bảo vệ phép nhân, giới
hạn bộ nhớ và việc không lặp theo ngân sách. Mọi ca xác minh input bất biến.

## Bài tập tự luyện

1. Tìm trường hợp mua nhiều bản nhất theo giá đơn thuần bỏ lỡ quà có lợi.
2. Chứng minh tại sao quà phát sinh thêm quà sẽ làm mô hình `min(x,d[i])` sai.
3. Xây dựng cách kiểm tra đáp án bằng tìm kiếm nhị phân và tổng giá tiền tố.

## Chạy kiểm thử

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc3947-test
/tmp/lc3947-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc3947-ndebug
/tmp/lc3947-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Test dùng mã thoát lỗi,
không dùng `assert`, nên vẫn kiểm tra đầy đủ khi bật `NDEBUG`.
