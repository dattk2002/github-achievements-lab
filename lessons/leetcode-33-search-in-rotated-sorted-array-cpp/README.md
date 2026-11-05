# LeetCode 33 — Tìm kiếm nhị phân trên mảng tăng đã xoay

Nguồn công khai: [LeetCode 33: Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-05**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::search(std::vector<int>& nums, int target)` trả chỉ số của `target` trong **mảng đầu vào hiện tại**, hoặc -1 nếu không có. Không trả chỉ số trước khi xoay và không sửa `nums`.

Bài gốc: mảng tăng nghiêm ngặt có thể đã xoay, mọi giá trị phân biệt, `1 <= nums.size() <= 5000`, phần tử và mục tiêu nằm trong `[-10000, 10000]`. Bản này trả -1 cho mảng rỗng; không xác minh lại tính tăng/xoay/phân biệt hay các cận khác. Đầu vào trùng giá trị thuộc bài toán khác và có thể phá điều kiện nhận biết nửa đã sắp xếp. Chỉ số `int` đủ chứa miền kích thước đã cho.

## Thuật toán và bất biến

Duy trì khoảng chỉ số đóng `[left, right]`. Tính `middle = left + (right-left)/2`; nếu trúng mục tiêu thì trả ngay. Vì mảng phân biệt và chỉ có một điểm xoay, ít nhất một trong hai nửa có thứ tự tăng:

- Nếu `nums[left] <= nums[middle]`, nửa trái tăng. Mục tiêu thuộc nửa này khi `nums[left] <= target < nums[middle]`.
- Nếu không, nửa phải tăng. Mục tiêu thuộc nửa này khi `nums[middle] < target <= nums[right]`.

Chọn nửa có thể chứa mục tiêu và bỏ vị trí giữa vừa kiểm tra. Bất biến là: nếu mục tiêu có mặt và chưa được tìm thấy, chỉ số của nó vẫn nằm trong khoảng đang xét. Nửa tăng có thể kiểm tra miền giá trị trực tiếp; nếu mục tiêu không nằm trong miền ấy thì chỉ nửa còn lại có thể chứa nó. Mỗi bước giữ nguyên bất biến và giảm ít nhất gần một nửa khoảng. Khi `left > right`, không còn ứng viên nên trả -1.

Dấu bằng ở hai đầu miền và việc loại riêng `middle` tránh mất phần tử ở biên hoặc vòng lặp không tiến triển. Mảng chưa xoay vẫn thỏa cùng lập luận.

Độ phức tạp: O(log n) thời gian, O(1) bộ nhớ phụ. Mảng rỗng xử lý O(1).

## Ví dụ chạy được

Lưu thành `/tmp/rotated-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-33-search-in-rotated-sorted-array-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{9, 12, 16, -7, -3, 2, 5};
    lab::Solution solution;
    std::cout << solution.search(nums, 2) << '\n';
    std::cout << solution.search(nums, 8) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/rotated-example.cpp -o /tmp/rotated-example
/tmp/rotated-example
```

Kết quả:

```text
5
-1
```

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-33-search-in-rotated-sorted-array-cpp/test.cpp -o /tmp/rotated-test
/tmp/rotated-test
make test-all
```

Oracle là `std::find`, đối chiếu chính xác chỉ số chứ không chỉ kiểm tra có/không. Với mọi độ dài 1..60, thử mọi vị trí xoay và mọi mục tiêu nguyên từ dưới phần tử nhỏ nhất tới trên phần tử lớn nhất, gồm cả các khoảng trống giữa giá trị. Có mảng rỗng, một/hai phần tử, không xoay, hai đầu miền và mảng 5000 phần tử. Kiểm tra đầu vào không đổi; điều kiện trả mã 1 khi sai vẫn hoạt động với `NDEBUG`.

## Bài tập

1. Tách cách tìm điểm xoay rồi binary search; so sánh chứng minh và số lần truy cập.
2. Nếu có phần tử trùng, tại sao đôi lúc không thể loại nửa mảng và có thể phải mất O(n)?
3. Sửa hàm để trả vị trí chèn theo thứ tự **trước khi xoay**; cần quy định gì khi mục tiêu đã tồn tại?
