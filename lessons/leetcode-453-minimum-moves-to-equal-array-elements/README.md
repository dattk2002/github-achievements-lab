# LeetCode 453 — Số bước tối thiểu để các phần tử bằng nhau

Nguồn: [Minimum Moves to Equal Array Elements](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/).
Ngày nguồn (`source_date`): **2026-11-01**. Độ khó: **Medium**.
Bài học C++17; tóm tắt, lời giải, ví dụ và kiểm thử được tự viết.

## Hợp đồng

`lab::Solution::minMoves(std::vector<int>& nums)` trả về số bước ít nhất
để mọi phần tử bằng nhau. Mỗi bước tăng đúng `n - 1` phần tử lên một đơn vị.
Giữ giao diện lớp của bài gốc trong namespace `lab`; hàm không sửa đầu vào.

Tiền điều kiện: `1 <= n <= 100000`, mỗi giá trị thuộc
`[-1000000000, 1000000000]`, đáp án nằm trong số nguyên có dấu 32 bit.
Không kiểm tra dữ liệu ngoài hợp đồng; mảng rỗng không được hỗ trợ.
Với một phần tử, mảng đã bằng nhau và đáp án là 0.

## Ý tưởng và chứng minh

Một bước bỏ qua phần tử ở vị trí `j` tương đương với tăng tất cả phần tử
lên 1 rồi giảm riêng phần tử `j` đi 1. Cộng cùng một số vào cả mảng không
ảnh hưởng việc các phần tử có bằng nhau hay không. Vì thế có thể giải
bài toán tương đương: mỗi bước giảm đúng một phần tử đi 1.

Gọi `m` là giá trị nhỏ nhất ban đầu. Trong mô hình giảm, mức chung cuối
cùng `t` không thể lớn hơn `m`. Để đi đến mức `t`, phần tử `x` phải giảm
`x - t` lần, nên tổng số bước là `sum(x - t)`. Tổng này nhỏ nhất khi chọn
mức hợp lệ lớn nhất, tức `t = m`. Mức đó đạt được bằng cách lần lượt giảm
mỗi phần tử về `m`; từng bước đều tương ứng với một bước hợp lệ của bài gốc.
Do đó đáp án là `sum(x - m)`. Mức chung trong mảng gốc có thể lớn hơn `m`;
`m` chỉ là đích của mô hình tương đương.

Triển khai tìm min trong một lượt rồi cộng các khoảng cách trong lượt sau.
Thời gian **O(n)**, bộ nhớ phụ **O(1)**. Ép sang `std::int64_t` trước phép
trừ và cộng dồn; không dùng tổng `int` của toàn mảng, vì tổng này có thể
vượt 32 bit dù đáp án nhỏ. Chỉ chuyển về `int` khi trả kết quả theo bảo đảm
của đề. Không cần sắp xếp hay mô phỏng từng bước.

## Ví dụ tự tạo và cách chạy

Với `{4, 6, 6}`, đáp án là 4. Một chuỗi bước hợp lệ:

```text
{4,6,6} -> {5,6,7} -> {6,7,7} -> {7,7,8} -> {8,8,8}
```

Với `{-5, -2, 0}`, cần `0 + 3 + 5 = 8` bước trong mô hình giảm.
Với `{7, 7, 7, 7}`, không cần bước nào.

Chương trình ví dụ đặt cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> nums{4, 6, 6};
    lab::Solution solution;
    std::cout << solution.minMoves(nums) << '\n'; // 4
}
```

Chạy kiểm thử từ thư mục gốc repo:

```sh
make test
# Hoặc chạy riêng bài này, kể cả khi tắt assert:
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-453-minimum-moves-to-equal-array-elements/test.cpp \
  -o /tmp/lesson-453-test
/tmp/lesson-453-test
```

## Kiểm thử

Bộ test báo lỗi và thoát khác 0 bằng kiểm tra tường minh, không dùng
`assert`. Các đáp án cố định được tính tay: số âm, một phần tử, toàn bộ
bằng nhau, min lặp lại, hai đầu miền giá trị, đáp án `2147483647`.
Mảng 100000 phần tử kiểm tra giới hạn kích thước, tổng dương/âm vượt 32 bit
và việc min nằm cuối mảng. Mỗi lần gọi cũng kiểm tra đầu vào không đổi.

Ngoài ra, duyệt hết 340 mảng có độ dài 1 đến 4, giá trị từ -1 đến 2.
Oracle BFS thực hiện trực tiếp mọi lựa chọn tăng `n - 1` phần tử và lấy
khoảng cách đầu tiên đến trạng thái bằng nhau, không dùng công thức lời giải.
Oracle sắp xếp và trừ min để gộp các trạng thái chỉ khác thứ tự hoặc phép
tịnh tiến; các phép này bảo toàn bước đi và đích. BFS chỉ dành cho mảng nhỏ,
không phải thuật toán dùng cho giới hạn lớn.

## Tự luyện

1. Chứng minh mức chung cuối cùng trong mảng gốc là `m + số_bước`.
2. Vì sao chọn trung vị thay cho min có thể sai? Tự tạo một phản ví dụ.
3. Nếu bỏ bảo đảm đáp án 32 bit, cần đổi kiểu trả về và những test nào?
