# LeetCode 300 — Độ dài dãy con tăng nghiêm ngặt

Nguồn công khai: [LeetCode 300: Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-06**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::lengthOfLIS(std::vector<int>& nums)` trả độ dài lớn nhất của một **dãy con tăng nghiêm ngặt**. Dãy con giữ thứ tự chỉ số nhưng không cần liên tiếp. Các giá trị bằng nhau không được nối thành một bước tăng. Hàm giữ nguyên đầu vào.

Bài gốc: `1 <= nums.size() <= 2500`, `-10000 <= nums[i] <= 10000`. Bản này trả 0 cho mảng rỗng; các cận khác là tiền điều kiện, không được kiểm tra lại. Lời giải chỉ so sánh giá trị, không cộng/trừ chúng; độ dài tối đa 2500 vừa kiểu `int`.

## Thuật toán tails và chứng minh

Duy trì `tails[l-1]`: giá trị kết thúc nhỏ nhất đạt được của một dãy con tăng độ dài l trong tiền tố đã xét. Với giá trị mới x, dùng `lower_bound` tìm vị trí đầu tiên có giá trị **không nhỏ hơn** x. Nếu không có thì thêm x vào cuối; nếu có thì thay giá trị ở vị trí đó bằng x.

Các giá trị tails tăng nghiêm ngặt. Nếu vị trí tìm được là p>0, có `tails[p-1] < x`, nên một dãy độ dài p đạt được trước đó có thể nối x để thành độ dài p+1. Nếu p=0, riêng x tạo dãy dài 1. Thay đuôi bằng giá trị nhỏ hơn hoặc bằng không làm giảm khả năng nối thêm về sau. Không thể tạo dãy dài hơn p+1 với x: dãy dài p+1 trước đó không có đuôi nhỏ hơn x, theo định nghĩa vị trí đầu tiên tìm được. Bất biến về đuôi tối thiểu được duy trì, nên kích thước tails cuối cùng là độ dài tối ưu.

Dùng `lower_bound` thay vì `upper_bound` là quan trọng: x bằng đuôi cũ chỉ thay đuôi, không làm tăng độ dài. Dãy `{2,2,2}` phải cho 1.

`tails` không nhất thiết tự nó là một dãy con của đầu vào. Với `{3,5,6,2,4}`, tails cuối là `{2,4,6}` nhưng 6 xuất hiện trước 2 và 4. Bài này chỉ trả độ dài; truy vết một dãy cần thông tin chỉ số và tiền nhiệm riêng.

Độ phức tạp: O(n log(n+1)) thời gian, O(n) bộ nhớ phụ. `push_back` có chi phí khấu hao; mỗi lượt tìm vị trí bằng binary search. Mảng rỗng mất O(1).

## Ví dụ chạy được

Lưu thành `/tmp/lis-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-300-longest-increasing-subsequence-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{3, 5, 6, 2, 4};
    lab::Solution solution;
    std::cout << solution.lengthOfLIS(nums) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lis-example.cpp -o /tmp/lis-example
/tmp/lis-example
```

Kết quả: `3`, ví dụ dãy con `{3,5,6}`.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-300-longest-increasing-subsequence-cpp/test.cpp -o /tmp/lis-test
/tmp/lis-test
make test-all
```

Oracle DP O(n²) tính độ dài tốt nhất kết thúc ở từng chỉ số, rồi lấy lớn nhất; khác cách giữ đuôi tối thiểu. Vét cạn 19531 mảng độ dài 0..6 trên `{-2,-1,0,1,2}`. Có mảng rỗng, một phần tử, các giá trị trùng, số âm/cực trị, giảm dần và tăng dần. Các mảng 2500 phần tử tăng, giảm và bằng nhau kiểm tra cận kích thước. Mọi ca xác nhận đầu vào không đổi; kiểm tra trả mã lỗi vẫn hoạt động khi bật `NDEBUG`.

## Bài tập

1. Trả một dãy con tăng tối ưu bằng cách lưu vị trí các đuôi và liên kết tiền nhiệm.
2. Chuyển sang dãy không giảm: cần đổi phép tìm vị trí nào và test nào sẽ phân biệt hai hợp đồng?
3. Đếm số dãy tăng dài nhất theo chỉ số; vì sao chỉ mảng tails hiện tại không đủ thông tin?
