# LeetCode 62 — Unique Paths: DP một hàng

Nguồn: [Unique Paths](https://leetcode.com/problems/unique-paths/), Medium.
Bài bổ sung ngày **2026-11-18**, không phải nhãn Daily. Tóm tắt, ví dụ,
kiểm thử và diễn giải dưới đây được tự viết.

## Hợp đồng

`lab::Solution::uniquePaths(int m, int n)` trả số đường từ góc trên trái đến
góc dưới phải của lưới `m × n`, mỗi bước chỉ sang phải hoặc xuống dưới.
Hai đường khác nhau khi chuỗi bước khác nhau. Lưới `1 × 1` có một đường
không cần bước nào. Không có vật cản.

Miền nguồn: `1 <= m,n <= 100`, đáp án không quá `2 000 000 000`.
Hàm ném `std::invalid_argument` nếu kích thước ngoài miền; ném
`std::overflow_error` nếu số đường vượt giới hạn đáp án. Không dùng số thực
hay tính giai thừa vì các giá trị trung gian có thể quá lớn.

## Thuật toán và vì sao đúng

Đường tới ô `(r,c)` phải đến từ ô trên hoặc ô trái; hai tập đường này
không giao nhau. Vì thế `ways(r,c) = ways(r-1,c) + ways(r,c-1)`.
Hàng đầu và cột đầu đều có đúng một đường.

Chỉ giữ một hàng `paths`, khởi tạo toàn `1`. Duyệt trái sang phải:
trước khi cập nhật cột `c`, `paths[c]` là số đường từ ô trên, còn
`paths[c-1]` đã là số đường từ ô trái của hàng hiện tại. Cộng hai giá trị
bảo toàn bất biến. Sau hàng cuối, phần tử cuối là đáp án.

Đổi vai hai chiều để vector dài `min(m,n)`; đổi tên bước phải/xuống là một
song ánh giữa hai tập đường. Để an toàn ngay cả khi người gọi đưa lưới có
đáp án vượt hợp đồng, mỗi phép cộng bão hòa ở `2 000 000 001`. Với các số
không âm, `min(C,a+b) = min(C,min(C,a)+min(C,b))`, nên vẫn nhận biết chính
xác kết quả có vượt giới hạn hay không; phép cộng trung gian dùng `long long`.

Thời gian **O(mn)**, bộ nhớ phụ **O(min(m,n))**. Không liệt kê từng đường.

## Ví dụ chạy được

Lưới `4 × 4` cần ba bước phải và ba bước xuống: chọn ba trong sáu vị trí,
nên có `20` đường. Một hàng dài bất kỳ chỉ có một đường.

Chạy từ thư mục bài học:

```sh
cat > /tmp/lc62-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    lab::Solution solution;
    std::cout << solution.uniquePaths(4,4) << '\n';
    std::cout << solution.uniquePaths(1,8) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc62-example.cpp -o /tmp/lc62-example
/tmp/lc62-example
```

Kết quả:

```text
20
1
```

## Kiểm thử và trường hợp biên

`test.cpp` kiểm tra `1 × 1`, lưới một chiều dài 100, đối xứng hai chiều,
`17 × 17`, kích thước sai và lưới vượt giới hạn đáp án. Oracle độc lập
đếm hoán vị bước bằng hệ số nhị thức cho cả 10 000 cặp kích thước. Oracle
chỉ tính tới lúc vượt ngưỡng nên không tràn `long long`.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc62-test
/tmp/lc62-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc62-ndebug
/tmp/lc62-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Kiểm thử dùng mã thoát
khác 0 khi sai, không phụ thuộc `assert`.

## Bài tập tự luyện

1. Chứng minh hệ số nhị thức dùng trong oracle là `C(m+n-2,m-1)`.
2. Vì sao đổi vòng lặp cột sang phải-trái làm sai DP một hàng?
3. Nếu có vật cản, trạng thái tại ô bị chặn phải được cập nhật thế nào?
