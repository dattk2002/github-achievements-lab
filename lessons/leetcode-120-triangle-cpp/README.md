# LeetCode 120 — Triangle: quy hoạch động từ đáy

Nguồn: [Triangle](https://leetcode.com/problems/triangle/), Medium.
Bài bổ sung ngày **2026-11-18**. Nội dung là tóm tắt và lời giải tự viết.

## Hợp đồng

`lab::Solution::minimumTotal(std::vector<std::vector<int>>& triangle)` trả
tổng nhỏ nhất của đường đi từ đỉnh tới hàng đáy. Từ cột `c` chỉ được sang
cột `c` hoặc `c+1` của hàng ngay dưới. Giá trị có thể âm; hàm giữ nguyên
đầu vào dù giao diện tham chiếu giống cách gọi trên LeetCode.

Miền nguồn: 1–200 hàng, hàng chỉ số `r` có `r+1` phần tử, mỗi phần tử
trong `[-10000,10000]`. Trong miền này, tổng nằm trong `[-2000000,2000000]`
nên `int` đủ. Số hàng và miền giá trị là tiền điều kiện của bài học;
hàm kiểm tra riêng hình dạng và ném `std::invalid_argument` nếu sai.
Mở rộng tiện dụng: tam giác rỗng trả `0`. Không hứa hỗ trợ số nguyên hay
kích thước vượt miền đã nêu.

## Thuật toán, bất biến và tính đúng

Gọi `best[c]` là tổng nhỏ nhất từ ô cột `c` của hàng đang xét xuống đáy.
Ở đáy, tổng chính là giá trị của ô. Nếu đã biết kết quả của hàng dưới,
ô `(r,c)` chỉ có hai lựa chọn đầu tiên, nên:

`best_new[c] = triangle[r][c] + min(best_old[c], best_old[c+1])`.

Sao chép hàng đáy vào vector phụ, rồi lần lượt xử lý các hàng phía trên.
Trong mỗi hàng, duyệt cột **từ trái sang phải**: hai phần tử cần đọc chưa
bị ghi đè; sau khi ghi `best[c]`, vòng sau chỉ đọc `best[c+1]` và
`best[c+2]`. Phần đuôi dư không còn được dùng. Quy nạp từ hàng đáy chứng
minh mỗi trạng thái tối ưu, nên `best[0]` cuối cùng là đáp án.

Số âm không phá vỡ truy hồi: đồ thị luôn đi xuống, không có chu trình.
Chọn ô nhỏ nhất tại mỗi hàng một cách tham lam có thể bỏ lỡ hậu tố tốt hơn.

Với `h` hàng: thời gian **O(h²)**, bộ nhớ phụ **O(h)**, đầu vào không đổi.

## Ví dụ chạy được

Tam giác `[[5],[9,2],[1,-4,8]]` có đường `5 → 2 → -4`, tổng `3`.
Chạy từ thư mục bài học:

```sh
cat > /tmp/lc120-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::vector<int>> triangle{{5},{9,2},{1,-4,8}};
    std::cout << lab::Solution{}.minimumTotal(triangle) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc120-example.cpp -o /tmp/lc120-example
/tmp/lc120-example
```

Kết quả:

```text
3
```

## Kiểm thử và trường hợp biên

Bộ test có một ô âm, rỗng, nhiều đường cùng tổng, hỗn hợp dấu và các
hình dạng thiếu/thừa phần tử. 1 080 tam giác sinh xác định được đối chiếu
với oracle đệ quy duyệt mọi đường, không dùng DP một hàng. Hai tam giác
200 hàng toàn `10000` hoặc `-10000` kiểm tra giới hạn tổng. Các ca hợp lệ
và sai hình dạng đều kiểm tra dữ liệu không bị sửa.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc120-test
/tmp/lc120-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc120-ndebug
/tmp/lc120-ndebug
```

Từ gốc repo: `make test` hoặc `make test-all`. Sai kết quả sẽ kết thúc bằng
mã khác 0 ngay cả khi định nghĩa `NDEBUG`.

## Bài tập tự luyện

1. Tìm tam giác mà chọn phần tử nhỏ hơn ở mỗi bước không tối ưu toàn cục.
2. Đổi vòng cột sang phải-trái và tìm phản ví dụ làm lộ việc ghi đè trạng thái.
3. Nếu cần trả cả đường đi, cần lưu thêm dữ liệu gì và tốn bao nhiêu bộ nhớ?
