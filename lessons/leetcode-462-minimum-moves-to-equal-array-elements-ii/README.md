# LeetCode 462 — Số bước tối thiểu để các phần tử bằng nhau II

Nguồn: [Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/).
Ngày nguồn (`source_date`): **2026-11-02**. Độ khó: **Medium**.
Bài học dùng C++17; phần tóm tắt, ví dụ, giải thích và kiểm thử được tự viết.

## Hợp đồng

`lab::Solution::minMoves2(std::vector<int>& nums)` trả về số bước ít nhất
để đưa mọi phần tử về cùng một giá trị nguyên. Một bước tăng hoặc giảm
**đúng một phần tử** đi 1. Hàm giữ nguyên mảng đầu vào.

Tiền điều kiện: `1 <= nums.size() <= 100000`, mỗi phần tử thuộc
`[-1000000000, 1000000000]`, đáp án không vượt `2147483647`.
Mảng rỗng và dữ liệu ngoài hợp đồng không được hỗ trợ hoặc kiểm tra.
Kiểu trả về là `int`, theo giao diện bài gốc trên môi trường có `int` 32 bit.

## Thuật toán và chứng minh

Nếu chọn đích chung `t`, phần tử `x` cần ít nhất `|x - t|` bước.
Ta đạt đúng số đó bằng cách di chuyển thẳng từ `x` đến `t`; vì từng bước
chỉ tác động một phần tử, tổng chi phí là `sum |x - t|`.

Sắp xếp các giá trị thành `a[0] <= ... <= a[n-1]`. Ghép hai đầu thành
các cặp `(a[i], a[n-1-i])`. Với một cặp `(u, v)`, `u <= v`, bất kỳ đích
`t` nào cũng có chi phí `|u-t| + |v-t| >= v-u`. Dấu bằng xảy ra khi
`u <= t <= v`. Một trung vị nằm trong mọi khoảng của các cặp, nên đồng
thời đạt cận dưới của tất cả các cặp.

Nếu `n` lẻ, phần tử giữa còn lại có chi phí 0 khi chọn chính nó làm đích.
Nếu `n` chẵn, mọi số nguyên giữa hai phần tử giữa đều tối ưu. Vì vậy chọn
`a[n/2]` luôn đúng. Trung bình cộng không có tính chất tối ưu này: với
`{0, 0, 12}`, chọn 0 tốn 12 bước, còn chọn trung bình 4 tốn 16 bước.

Triển khai sao chép mảng, dùng `std::sort`, lấy trung vị rồi cộng khoảng
cách. Thời gian **O(n log n)**, bộ nhớ phụ **O(n)** do bản sao; không sửa
thứ tự của `nums`. Không mô phỏng từng bước. Chuyển sang `std::int64_t`
trước phép trừ và cộng dồn, sau đó chuyển về `int` theo bảo đảm đáp án.
Không dùng tổng toàn bộ phần tử kiểu `int`: tổng đó có thể tràn dù
đáp án là 0, chẳng hạn mảng lớn gồm các giá trị bằng một tỷ.

## Ví dụ tự tạo

- `{8, 2, 5}`: chọn 5, chi phí `3 + 3 + 0 = 6`.
- `{9, -3, 6, 0}`: hai phần tử giữa sau sắp xếp là 0 và 6.
  Chọn 6 tốn `3 + 9 + 0 + 6 = 18`; chọn 0 cũng tốn 18.
- `{-8, -3, -1}`: chọn -3, chi phí `5 + 0 + 2 = 7`.
- Một phần tử hoặc mọi phần tử đã bằng nhau: đáp án 0.

Chương trình ví dụ đặt cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nums{8, 2, 5};
    lab::Solution solution;
    std::cout << solution.minMoves2(nums) << '\n'; // 6
}
```

Từ thư mục gốc repo, chạy toàn bộ kiểm thử được hỗ trợ bởi sandbox:

```sh
make test
```

Hoặc chạy riêng bài này, kể cả khi vô hiệu hóa `assert`:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-462-minimum-moves-to-equal-array-elements-ii/test.cpp \
  -o /tmp/lesson-462-test
/tmp/lesson-462-test
```

## Thiết kế kiểm thử

Kiểm tra tường minh và `std::exit(EXIT_FAILURE)` bảo đảm lỗi trả mã khác 0
ngay cả khi có `NDEBUG`. Mỗi ca cũng xác nhận đầu vào không đổi.
Test đầu `{0, 0, 12}` đã thất bại với hàm tạm trả 0 trước khi viết lời giải.

Các kết quả cố định tính tay bao phủ số âm, hai phía của 0, phần tử lặp,
độ dài chẵn/lẻ, thứ tự giảm, một phần tử, hai đầu miền giá trị và đáp án
sát giới hạn. Với `{-1000000000, 0, 1000000000, 147483647}`, hai cặp đầu-cuối
có tổng độ rộng `2000000000 + 147483647 = 2147483647`.
Các mảng dài 100000 kiểm tra giới hạn kích thước, giá trị lớn đồng nhất,
ngoại lệ ở đầu/cuối và hai nhóm bằng nhau: 50000 cặp `(-7, 11)` cần 900000 bước.

Ngoài ra, duyệt đủ **19530** mảng độ dài 1 đến 6 với giá trị từ -2 đến 2.
Oracle thử mọi đích nguyên từ min đến max và lấy tổng khoảng cách nhỏ nhất,
không sắp xếp hay chọn trung vị. Đích ngoài khoảng này luôn có thể kéo vào
khoảng để giảm chi phí, nên việc vét cạn là đầy đủ. Oracle chỉ dùng cho
mảng nhỏ; đây không phải lời giải cho giới hạn lớn.

## Tự luyện

1. Tự chứng minh chính xác tập hợp các đích tối ưu khi độ dài chẵn và lẻ.
2. Thay sắp xếp bằng `std::nth_element`: thời gian trung bình thay đổi
   thế nào, và vì sao không được gọi đó là bảo đảm tuyến tính tệ nhất?
3. Nếu được sửa trực tiếp đầu vào, có thể bỏ bản sao như thế nào? Cần sửa
   hợp đồng và kiểm thử nào?
4. Nếu mỗi phần tử có chi phí di chuyển riêng, trung vị thông thường còn
   tối ưu không? Thử một phản ví dụ rồi tìm hiểu trung vị có trọng số.
