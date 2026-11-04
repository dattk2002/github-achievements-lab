# LeetCode 53 — Đoạn con liên tiếp có tổng lớn nhất

Nguồn công khai: [LeetCode 53: Maximum Subarray](https://leetcode.com/problems/maximum-subarray/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-04**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::maxSubArray(std::vector<int>& nums)` trả tổng lớn nhất của một đoạn **liên tiếp, không rỗng**. Hàm giữ nguyên đầu vào.

Theo bài gốc: `1 <= nums.size() <= 100000`, mỗi phần tử trong `[-10000, 10000]`. Tổng và trung gian của lời giải nằm trong miền `int` 32 bit (giá trị lớn nhất 1.000.000.000). Ngoài hợp đồng, bản này ném `std::invalid_argument` với vector rỗng; không kiểm tra các giới hạn còn lại. Số âm không có nghĩa được chọn đoạn rỗng: `{-8, -2, -5}` phải cho -2, không phải 0.

## Thuật toán Kadane và chứng minh

Giữ `ending_here`: tổng tốt nhất của đoạn kết thúc **đúng tại vị trí hiện tại**, cùng `best`: tổng tốt nhất trên mọi đoạn đã xét. Khởi tạo cả hai bằng phần tử đầu tiên.

Tại phần tử `x`, một đoạn kết thúc ở đây hoặc bắt đầu mới tại `x`, hoặc kéo dài đoạn tốt nhất kết thúc ở vị trí trước. Vì vậy cập nhật `ending_here = max(x, ending_here + x)`, rồi `best = max(best, ending_here)`. Không thể bỏ qua một phần tử giữa đoạn.

Bất biến đúng ở phần tử đầu. Hai khả năng trên bao phủ mọi đoạn kết thúc ở vị trí mới và chọn đúng tổng tốt nhất; cập nhật `best` bao phủ cả đoạn đã có lẫn đoạn vừa kết thúc. Khi duyệt hết, mọi vị trí kết thúc đã được xét, nên `best` là đáp án. Khởi tạo từ phần tử đầu giúp xử lý đúng trường hợp tất cả đều âm.

Độ phức tạp: O(n) thời gian, O(1) bộ nhớ phụ, không sao chép hay sắp xếp mảng.

## Ví dụ chạy được

Lưu mã sau vào `/tmp/max-subarray-example.cpp`, chạy từ gốc repo:

```cpp
#include "lessons/leetcode-53-maximum-subarray-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{-4, 6, -1, 3, -8, 2};
    lab::Solution solution;
    std::cout << solution.maxSubArray(nums) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/max-subarray-example.cpp -o /tmp/max-subarray-example
/tmp/max-subarray-example
```

Kết quả: `8`, từ đoạn `{6, -1, 3}`. Nếu cộng mọi phần tử dương mà bỏ các số âm ở giữa, ta đã giải một bài khác.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-53-maximum-subarray-cpp/test.cpp -o /tmp/max-subarray-test
/tmp/max-subarray-test
make test-all
```

Test dùng `exit(1)` nên vẫn phát hiện lỗi khi có `NDEBUG`. Có dãy toàn âm, một phần tử, toàn 0, đoạn tốt nhất phải bắt đầu lại và số lớn. Vét cạn 19.530 dãy độ dài 1..6 trên tập `{-3, -1, 0, 2, 4}`, đối chiếu cách cộng từng đoạn O(n²) độc lập. Mảng 100.000 phần tử ở hai đầu miền giá trị kiểm tra giới hạn; mọi ca hợp lệ đều kiểm tra đầu vào không đổi. Vector rỗng kiểm tra đúng loại ngoại lệ.

## Bài tập

1. Mở rộng để trả cả hai chỉ số của đoạn tối ưu; quy định rõ cách chọn khi nhiều đoạn cùng tổng.
2. Vì sao khởi tạo `best = 0` sai trên dãy toàn âm? Tạo một test ngắn nhất để bắt lỗi.
3. Viết cách chia để trị, so sánh thời gian và bộ nhớ với Kadane; thử mở rộng sang đoạn con vòng tròn.
