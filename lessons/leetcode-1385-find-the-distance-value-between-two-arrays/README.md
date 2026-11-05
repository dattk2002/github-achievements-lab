# LeetCode 1385 — Đếm phần tử cách xa mảng còn lại

Nguồn: [Find the Distance Value Between Two Arrays](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/).
Ngày nguồn (`source_date`): **2026-11-05**. Độ khó: **Easy**.
Bài học dùng C++17; phần tóm tắt, ví dụ và giải thích được tự viết.

## Hợp đồng và tiền điều kiện

```cpp
int lab::Solution::findTheDistanceValue(
    std::vector<int>& arr1, std::vector<int>& arr2, int d);
```

Hàm đếm số vị trí trong `arr1` có giá trị cách **mọi** phần tử của `arr2`
xa hơn `d`. Chỉ cần tồn tại một giá trị cách không quá `d` thì vị trí đó
bị loại. Hai phần tử bằng nhau ở hai vị trí vẫn được tính riêng.
Hàm giữ nguyên cả hai mảng, dù giao diện nhận tham chiếu không hằng.

Tiền điều kiện: mỗi mảng có từ 1 đến 500 phần tử; giá trị thuộc
`[-1000, 1000]`; `0 <= d <= 100`. Không kiểm tra dữ liệu ngoài hợp đồng.
Kết quả thuộc `[0, arr1.size()]`. Khoảng cách đúng bằng `d` cũng bị loại;
khi `d = 0`, chỉ giá trị trùng với phần tử của `arr2` mới bị loại.

## Thuật toán và tính đúng đắn

Với mỗi giá trị `x` trong `arr1`, ban đầu coi nó đủ điều kiện.
Duyệt `arr2`; nếu gặp `y` thỏa `abs(x - y) <= d`, đánh dấu loại và dừng
vòng lặp trong. Nếu duyệt xong mà không bị loại, tăng bộ đếm một lần.

Sau mỗi phần tử đã xét trong `arr2`, cờ còn đúng khi và chỉ khi chưa gặp
phần tử nào vi phạm điều kiện khoảng cách. Gặp một vi phạm là đủ để loại
`x`, nên dừng sớm không thay đổi kết quả. Nếu không gặp vi phạm sau toàn
bộ mảng, mọi khoảng cách đều lớn hơn `d`, đúng điều kiện cần đếm.
Vòng ngoài xử lý mỗi vị trí đúng một lần, nên bộ đếm cuối cùng là đáp án.

Với `n = arr1.size()` và `m = arr2.size()`, thời gian xấu nhất **O(nm)**,
bộ nhớ phụ **O(1)**. Tối đa 250000 phép so sánh là phù hợp giới hạn.
Không cần sắp xếp hay sao chép mảng. Hiệu thuộc `[-2000, 2000]`, nên
phép trừ và trị tuyệt đối an toàn với `int` trong hợp đồng này.

## Ví dụ tự tạo và cách chạy

Với `arr1 = {-6, 0, 5, 12}`, `arr2 = {-4, 8}`, `d = 2`:

- `-6` bị loại vì cách `-4` đúng 2 đơn vị.
- `0` có các khoảng cách 4 và 8, nên được tính.
- `5` có các khoảng cách 9 và 3, nên được tính.
- `12` có các khoảng cách 16 và 4, nên được tính.

Kết quả là **3**. Với `{2, 2, 3, -1}`, `{2, 2, -1}` và `d = 0`,
chỉ vị trí mang giá trị 3 được tính, nên kết quả là **1**.

Chương trình ví dụ đặt cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a{-6, 0, 5, 12};
    std::vector<int> b{-4, 8};
    lab::Solution solution;
    std::cout << solution.findTheDistanceValue(a, b, 2) << '\n'; // 3
}
```

Từ thư mục gốc repo:

```sh
make test
# Chạy riêng, kể cả khi định nghĩa NDEBUG:
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-1385-find-the-distance-value-between-two-arrays/test.cpp \
  -o /tmp/lesson-1385-test
/tmp/lesson-1385-test
```

## Kiểm thử

15 ca có đáp án tính độc lập bằng tay, không gọi lại thuật toán để tạo
kết quả mong đợi. Chúng kiểm tra dấu biên ở cả hai phía, khoảng cách lớn
hơn ngưỡng đúng một đơn vị, số âm, phần tử trùng, `d = 0`, `d = 100`,
mảng một phần tử, hai đầu miền giá trị và kết quả bằng 0 hoặc bằng `n`.
Phần tử gây loại nằm đầu hoặc cuối `arr2` giúp phát hiện việc chỉ xét một
phần mảng hay ghi đè sai cờ. Hai ca kích thước 500 kiểm tra toàn bộ được
đếm và trường hợp chỉ phần tử cuối gây loại. Mọi ca đều kiểm tra đầu vào
không đổi. Kiểm tra tường minh và `EXIT_FAILURE` bảo đảm lỗi trả mã khác 0
ngay cả với `NDEBUG`; không dùng `assert`.

Bộ test được viết trước lời giải; bản khung trả 0 đã thất bại ở ca đầu
với đáp án mong đợi 3 trước khi thay bằng thuật toán hoàn chỉnh.

## Bài tập

1. Tạo phản ví dụ cho cách chỉ so sánh với phần tử đầu của `arr2`.
2. Nếu tăng kích thước lên 100000, hãy sắp xếp bản sao của `arr2` và dùng
   tìm kiếm nhị phân để kiểm tra đoạn `[x-d, x+d]`. Phân tích độ phức tạp.
3. Nếu giá trị có thể là mọi số nguyên 32 bit, cần đổi kiểu ở bước nào
   để tránh tràn khi tính khoảng cách? Viết thêm ca kiểm thử tương ứng.
