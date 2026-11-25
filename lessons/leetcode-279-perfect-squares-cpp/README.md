# LeetCode 279 — Perfect Squares: quy hoạch động theo tổng

Nguồn: [Perfect Squares](https://leetcode.com/problems/perfect-squares/), Medium.
Bài bổ sung ngày **2026-11-25**. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::numSquares(int n)` trả số lượng số chính phương dương ít
nhất có tổng bằng `n`. Có thể dùng lại một số chính phương nhiều lần.
Miền nguồn là `1 <= n <= 10000`; bản lab mở rộng `n = 0` thành tổng rỗng,
trả `0`. Giá trị ngoài `[0,10000]` gây `std::invalid_argument`.

## Thuật toán và tính đúng

Đặt `best[s]` là số số hạng ít nhất để tạo tổng `s`. Bắt đầu với
`best[0] = 0`. Với mỗi tổng tăng dần, thử từng bình phương `r*r <= s`:

```text
best[s] = min(best[s], best[s - r*r] + 1)
```

Chọn số hạng cuối là `r*r` thì phần còn lại có tổng nhỏ hơn `s`, nên đã
được giải trước. Mọi cách tạo `s` đều có một số hạng cuối như vậy; thử hết
các bình phương không bỏ sót lời giải. Ngược lại, ghép một bình phương vào
lời giải của tổng nhỏ hơn luôn tạo được `s`. Theo quy nạp, lấy nhỏ nhất
cho kết quả tối ưu.

Khởi tạo ô chưa giải bằng `n+1`, lớn hơn mọi đáp án hợp lệ vì luôn có thể
dùng `s` số `1`. Giới hạn `n` được kiểm tra trước khi cấp phát; phép nhân
trong vòng lặp và các giá trị DP đều vừa `int`.

Thời gian **O(n sqrt(n))**, bộ nhớ phụ **O(n)**. Không cần căn bậc hai dấu
phẩy động, bảng băm hay định lý số học để triển khai.

## Ví dụ chạy được

Với `18`, chọn `9 + 9`, cần hai số hạng. Không thể dùng một số hạng vì
`18` không phải số chính phương. Chạy tại thư mục bài học:

```sh
cat > /tmp/lc279-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::cout << lab::Solution{}.numSquares(18) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc279-example.cpp -o /tmp/lc279-example
/tmp/lc279-example
```

Kết quả: `2`.

## Kiểm thử và trường hợp biên

`test.cpp` kiểm tra tổng rỗng, số `1`, bình phương lớn nhất trong miền,
các số cần bốn số hạng và đầu vào không hợp lệ. Oracle độc lập dùng BFS:
đỉnh là tổng, mỗi cạnh cộng một bình phương; khoảng cách từ `0` là số số
hạng ít nhất. Đối chiếu mọi `n` từ `0` đến `500` với bảng khoảng cách này.
Các ca `9999` và `10000` kiểm tra sát giới hạn.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc279-test
/tmp/lc279-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc279-ndebug
/tmp/lc279-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Kiểm thử dùng mã thoát
khác `0` khi sai, không dựa vào `assert`.

## Bài tập tự luyện

1. Lưu thêm số hạng cuối để khôi phục một phân tích tối ưu của `n`.
2. Chạy BFS trực tiếp cho một đầu vào và so sánh bộ nhớ với DP.
3. Vì sao chỉ trừ bình phương lớn nhất hiện tại có thể cho lời giải sai?
   Dùng `18` để kiểm chứng.
