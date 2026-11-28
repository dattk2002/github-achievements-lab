# LeetCode 153: Find Minimum in Rotated Sorted Array — Tìm kiếm nhị phân quanh điểm xoay

Nguồn: [LeetCode 153: Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/), Medium.
Bài bổ sung ngày **2026-11-28**, không phải nhãn Daily. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::findMin(std::vector<int>& nums)` trả phần tử nhỏ nhất của
mảng tăng nghiêm ngặt đã được xoay vòng. Một vòng xoay đầy đủ cho mảng
ban đầu cũng là input hợp lệ. Hàm giữ nguyên mảng và chạy O(log n).

Tiền điều kiện: độ dài `1..5000`, phần tử phân biệt thuộc `[-5000,5000]`,
mảng là một phép xoay của dãy tăng nghiêm ngặt. Không truyền mảng rỗng,
mảng tùy ý hoặc giá trị lặp; không quét xác thực vì sẽ mất yêu cầu logarit.

## Thuật toán

Giữ đoạn đóng `[left,right]` chứa vị trí nhỏ nhất. Khi còn ít nhất hai
phần tử, lấy `middle = left + (right-left)/2` rồi so `nums[middle]` với
`nums[right]`.

- Nếu lớn hơn, điểm xoay và giá trị nhỏ nhất nằm bên phải `middle`:
  đặt `left = middle + 1`.
- Nếu không lớn hơn, giữ `middle` vì nó có thể chính là nhỏ nhất:
  đặt `right = middle`.

Khi hai biên gặp nhau, trả phần tử tại đó. Không cần xác định số lần xoay.
Công thức trung điểm tránh cộng trực tiếp hai chỉ số lớn.

## Bất biến và kết thúc

Ban đầu cả mảng chứa giá trị nhỏ nhất. Khi `nums[middle] > nums[right]`,
hai đầu so sánh thuộc hai phía của điểm giảm, nên không vị trí nào tới
`middle` là nhỏ nhất. Khi `nums[middle] < nums[right]`, đoạn từ `middle`
đến `right` tăng, nên nhỏ nhất ở `middle` hoặc phía trái. Vì phần tử phân
biệt và `middle < right`, đây là hai khả năng đầy đủ.

Mỗi cập nhật giữ vị trí nhỏ nhất và thu ngắn đoạn còn nhiều nhất khoảng
một nửa. Cuối cùng chỉ còn một ứng viên, chính là đáp án.
Không thay `right=middle` bằng `middle-1`: điều đó có thể loại mất đáp án.

## Độ phức tạp

Thời gian **O(log n)**, bộ nhớ phụ **O(1)**. Không sắp xếp lại hoặc sao chép
mảng trong lời giải. Mảng một phần tử không vào vòng lặp.

## Ví dụ tự xây dựng

Với `[9,12,-4,0,3]`, đầu tiên `middle=2`, giá trị `-4 < 3`, giữ đoạn `[0,2]`.
Tiếp đó `12 > -4`, chuyển `left` tới `2`. Giá trị nhỏ nhất là **-4**.

## Chạy ví dụ

Tại thư mục bài học:

```sh
cat > /tmp/lc153-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> values{9,12,-4,0,3};
    std::cout << lab::Solution{}.findMin(values) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc153-example.cpp -o /tmp/lc153-example
/tmp/lc153-example
```

Kết quả:

```text
-4
```

## Kiểm thử và trường hợp biên

Oracle dùng `std::min_element`, độc lập với quyết định chia đôi. Test xét
**11325** phép xoay: mọi vị trí xoay cho từng độ dài `1..150`, thêm 500 dãy
thưa ngẫu nhiên seed cố định chứa số âm/dương. Mọi ca xác minh input không đổi.

Biên riêng gồm singleton, hai phần tử ở cả hai thứ tự, chưa xoay, cực tiểu
ở hai đầu hoặc giữa. Dãy độ dài 5000 được thử ở các điểm xoay sát biên và
ở giữa. Thay sai một trong hai cập nhật biên sẽ bị các phép xoay đầy đủ phát
hiện. Các test hành vi không thay thế lập luận độ phức tạp ở trên.

## Bài tập tự luyện

1. Điều chỉnh hàm để trả chỉ số nhỏ nhất thay vì giá trị.
2. Nếu cho phép phần tử lặp, vì sao phép so với đầu phải có thể không
   quyết định được nửa cần giữ và cận thời gian có thể thành O(n)?
3. Từ bài này xây dựng cách tìm một target trong mảng xoay có phần tử phân biệt.

## Chạy kiểm thử

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc153-test
/tmp/lc153-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc153-ndebug
/tmp/lc153-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Test dùng mã thoát lỗi,
không dùng `assert`, nên vẫn kiểm tra đầy đủ khi bật `NDEBUG`.
