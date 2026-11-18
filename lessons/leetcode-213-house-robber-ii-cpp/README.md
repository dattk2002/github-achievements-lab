# LeetCode 213 — House Robber II: bỏ một đầu của vòng

Nguồn: [House Robber II](https://leetcode.com/problems/house-robber-ii/), Medium.
Bài bổ sung ngày **2026-11-18**, lời giải và ví dụ tự viết.

## Hợp đồng

`lab::Solution::rob(std::vector<int>& nums)` tìm tổng lớn nhất khi chọn các
vị trí trên một vòng tròn mà không chọn hai vị trí kề nhau. Phần tử đầu
và cuối cũng kề nhau. Một phần tử chỉ có thể được chọn một lần; riêng
vòng một nhà vẫn chọn được nhà đó.

Miền nguồn: 1–100 phần tử, mỗi giá trị từ `0` tới `1000`. Đây là tiền
điều kiện, không có kiểm tra miền giá trị trong hàm. Tổng không quá
`100000`, vừa `int`. Mở rộng: vector rỗng trả `0`. Hàm giữ nguyên `nums`.

## Từ vòng tròn về hai đoạn thẳng

Với ít nhất hai nhà, lời giải hợp lệ không thể chứa đồng thời hai đầu.
Vì vậy mọi lời giải thuộc ít nhất một trong hai trường hợp:

- Bỏ nhà cuối, giải đoạn nửa mở `[0, size-1)`.
- Bỏ nhà đầu, giải đoạn nửa mở `[1, size)`.

Ngược lại, tập nhà không kề nhau trong mỗi đoạn trên luôn hợp lệ trên
vòng vì đã bỏ ít nhất một đầu. Lấy giá trị lớn hơn của hai bài toán đoạn
thẳng là đủ; tập lời giải có thể giao nhau nhưng lấy max không đếm trùng.

Trên đoạn thẳng, khi gặp giá trị `v`, hoặc bỏ nó và giữ tổng tốt nhất
trước đó, hoặc lấy nó và cộng vào tổng tốt nhất trước nhà liền trước:
`current = max(one_back, two_back + v)`. Trước mỗi bước, `one_back` và
`two_back` lần lượt là tối ưu của tiền tố dài hơn và ngắn hơn một nhà.
Tính `current` trước khi dịch hai biến sẽ bảo toàn bất biến này.

Xử lý riêng rỗng và một nhà trước khi tách đoạn. Với hai nhà, hai đoạn
đều dài một, nên đáp án là phần tử lớn hơn, không phải tổng của chúng.

Thời gian **O(n)** qua hai lượt tuyến tính, bộ nhớ phụ **O(1)**. Không
sao chép đoạn con, không thay đổi vector gốc.

## Ví dụ chạy được

Vòng `[8,1,1,8]` không cho lấy cả hai số `8`. Chọn nhà đầu cùng nhà thứ
ba, hoặc nhà thứ hai cùng nhà cuối, đạt `9`.
Chạy từ thư mục bài học:

```sh
cat > /tmp/lc213-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> values{8,1,1,8};
    std::cout << lab::Solution{}.rob(values) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc213-example.cpp -o /tmp/lc213-example
/tmp/lc213-example
```

Kết quả:

```text
9
```

## Kiểm thử và trường hợp biên

Test cố định gồm rỗng, một nhà, hai nhà, toàn số 0, vòng lẻ và hai đầu có
giá trị lớn. Oracle độc lập liệt kê mọi tập con và loại tập có cặp kề
nhau, kể cả cặp cuối–đầu. Đối chiếu toàn bộ 21 845 vector độ dài 0–7 với
giá trị 0–3. Ca 100 nhà toàn `1000` có đáp án `50000`; mọi ca đều kiểm tra
đầu vào không đổi. Oracle chỉ chạy trên vector nhỏ, tránh dịch bit quá rộng.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc213-test
/tmp/lc213-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc213-ndebug
/tmp/lc213-ndebug
```

Từ gốc repo: `make test` hoặc `make test-all`. Test dùng mã thoát thay vì
`assert`, nên vẫn bắt lỗi khi có `NDEBUG`.

## Bài tập tự luyện

1. Vì sao không thể giải đoạn thẳng trước rồi chỉ bỏ một đầu nếu bị trùng?
2. Nếu cho phép giá trị âm và được chọn tập rỗng, ca một nhà cần đổi gì?
3. Mở rộng để trả cả chỉ số nhà đã chọn và nêu chi phí bộ nhớ.
