# LeetCode 740 — Delete and Earn: gom điểm theo giá trị

Nguồn: [Delete and Earn](https://leetcode.com/problems/delete-and-earn/), Medium.
Bài bổ sung ngày **2026-11-25**. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::deleteAndEarn(std::vector<int>& nums)` tìm điểm tối đa khi
lấy một giá trị `v` để nhận `v` điểm, đồng thời loại mọi phần tử bằng
`v-1` và `v+1`. Có thể tiếp tục lấy các bản sao còn lại của `v`.

Miền nguồn: 1–20000 phần tử, giá trị trong `[1,10000]`. Đây là tiền điều
kiện, hàm không kiểm tra đầu vào sai miền. Mở rộng vector rỗng trả `0`.
Hàm giữ nguyên vector. Tổng mọi điểm không quá `200000000`, vừa `int`.

## Từ phần tử sang trục giá trị

Nếu quyết định lấy `v`, mọi bản sao của nó đều có thể lấy tiếp mà không
tạo thêm xung đột. Vì các giá trị dương, lấy hết chúng không làm giảm
điểm. Gom chúng vào `points[v] = v * số_lần_xuất_hiện`.

Hai nhóm xung đột khi giá trị chênh đúng `1`; vị trí ban đầu trong vector
không ảnh hưởng. Duyệt toàn bộ trục từ `1` tới `M = max(nums)`, bao gồm
giá trị không xuất hiện với điểm `0`. Nhờ các ô trống này, hai giá trị có
khoảng cách lớn hơn `1` luôn có thể được chọn cùng nhau.

Gọi `best[v]` là tối ưu khi chỉ xét giá trị không quá `v`:

```text
best[v] = max(best[v-1], best[v-2] + points[v])
```

Mọi lời giải hoặc bỏ `v`, hoặc chọn `v` và bỏ `v-1`. Cả hai trường hợp
đều ghép được với tối ưu của phần còn lại, nên công thức đầy đủ và đúng.
Chỉ giữ hai kết quả trước bằng `two_back`, `one_back`; tính `current`
trước khi dịch hai biến để bảo toàn trạng thái.

Thời gian **O(n + M)**, bộ nhớ phụ **O(M)** cho bảng điểm, không phải
O(1) dù phần DP chỉ có hai biến. Vector rỗng được xử lý trước khi tìm max.

## Ví dụ chạy được

`[1,1,4,4,5]`: lấy hai số `1` và hai số `4`, được `10` điểm; nhóm `5`
bị loại. Khoảng trống giữa `1` và `4` cho phép lấy cả hai nhóm.
Chạy tại thư mục bài học:

```sh
cat > /tmp/lc740-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> values{1,1,4,4,5};
    std::cout << lab::Solution{}.deleteAndEarn(values) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc740-example.cpp -o /tmp/lc740-example
/tmp/lc740-example
```

Kết quả: `10`.

## Kiểm thử và trường hợp biên

Các ca cố định bắt lỗi không gom đủ bản sao, chọn hai giá trị kề nhau,
hoặc nhầm các nhóm cách xa thành kề nhau. Có vector rỗng, một phần tử,
hai giá trị ở hai đầu miền và 20000 bản sao của `10000`.

Oracle liệt kê tập con của các giá trị `1..8`, loại tập có hai giá trị
kề nhau, rồi cộng điểm. So sánh 2000 vector sinh bằng seed cố định với
oracle này; không dùng lại công thức DP. Mọi ca kiểm tra vector không đổi.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc740-test
/tmp/lc740-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc740-ndebug
/tmp/lc740-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Sai kết quả làm tiến
trình thoát khác `0`, kể cả khi định nghĩa `NDEBUG`.

## Bài tập tự luyện

1. Với giá trị rất lớn nhưng ít giá trị phân biệt, thay bảng điểm bằng
   danh sách nhóm đã sắp xếp; xử lý khoảng trống thế nào?
2. Khôi phục tập giá trị được chọn và nêu chi phí bộ nhớ.
3. Vì sao DP trên thứ tự phần tử ban đầu không giải đúng bài này?
