# LeetCode 15 — Ba phần tử có tổng bằng 0

Nguồn công khai: [LeetCode 15: 3Sum](https://leetcode.com/problems/3sum/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-05**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`std::vector<std::vector<int>> lab::Solution::threeSum(std::vector<int>& nums)` trả mọi bộ ba **giá trị khác nhau theo bộ**, có tổng 0 và có thể chọn từ ba chỉ số phân biệt của đầu vào. Các giá trị trong một bộ được phép bằng nhau nếu có đủ bản sao trong mảng. Không trả lặp cùng một bộ; thứ tự các bộ không phải yêu cầu. Hàm giữ nguyên `nums`.

Bài gốc: `3 <= nums.size() <= 3000`, `-100000 <= nums[i] <= 100000`. Tổng ba phần tử trong `[-300000, 300000]`, an toàn với `int` 32 bit. Bản này mở rộng mảng có ít hơn ba phần tử thành kết quả rỗng; các cận khác là tiền điều kiện, không được kiểm tra lại.

## Thuật toán và chứng minh

Sắp xếp **bản sao** đầu vào. Cố định chỉ số `i`, đặt `left = i+1`, `right = n-1`, rồi so sánh tổng ba giá trị với 0. Nếu tổng âm, tăng `left`; nếu dương, giảm `right`. Nếu bằng 0, lưu bộ ba và bỏ qua mọi bản sao của hai giá trị vừa lấy.

Với `i` cố định, nếu tổng âm thì mọi cặp dùng `left` hiện tại cùng một chỉ số không lớn hơn `right` đều không đủ lớn; bỏ `left` là an toàn. Tương tự, nếu tổng dương, mọi cặp dùng `right` hiện tại cùng chỉ số không nhỏ hơn `left` đều quá lớn. Hai con trỏ chỉ bỏ các ứng viên không thể tạo đáp án, nên không bỏ sót bộ nào. Điều kiện `i < left < right` bảo đảm ba chỉ số phân biệt.

Bỏ các `i` trùng giá trị với `i-1` tránh lặp lại cùng bài toán hai con trỏ. Sau một đáp án, bỏ các giá trị trùng ở hai đầu tránh ghi lại cùng bộ ba. Các bản sao cần thiết như `{-2, 1, 1}` vẫn có thể được chọn khi hai chỉ số khác nhau.

Độ phức tạp: O(n²) thời gian, gồm O(n log n) sắp xếp và tối đa O(n) dịch con trỏ cho mỗi `i`. O(n) bộ nhớ phụ cho bản sao, ngoài O(R) kết quả với R bộ ba (mỗi bộ ba có kích thước cố định). Không loại trùng đầu vào vì điều đó sẽ làm mất số lần xuất hiện cần thiết.

## Ví dụ chạy được

Lưu thành `/tmp/three-sum-example.cpp`, chạy ở gốc repo:

```cpp
#include "lessons/leetcode-15-3sum-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{-5, -2, 0, 2, 3, 5};
    lab::Solution solution;
    for (const auto& triple : solution.threeSum(nums)) {
        std::cout << triple[0] << ',' << triple[1] << ',' << triple[2] << '\n';
    }
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/three-sum-example.cpp -o /tmp/three-sum-example
/tmp/three-sum-example
```

Bản cài đặt này in:

```text
-5,0,5
-5,2,3
-2,0,2
```

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-15-3sum-cpp/test.cpp -o /tmp/three-sum-test
/tmp/three-sum-test
make test-all
```

Test so tập bộ ba với oracle duyệt ba chỉ số `i<j<k`, sắp xếp từng bộ và loại trùng bằng `std::set`. Còn kiểm tra số kết quả bằng kích thước tập, nên kết quả lặp không bị che giấu. Vét cạn 19.531 mảng độ dài 0..6 trên `{-2,-1,0,1,2}`; thêm cực trị, không có đáp án, cần hai bản sao, và 3000 số 0 chỉ tạo một bộ. Mọi ca kiểm tra đầu vào không đổi. Lỗi trả mã 1 cả khi bật `NDEBUG`, không dựa vào `assert`.

## Bài tập

1. Tổng mục tiêu đổi từ 0 sang một số `long long`: cần thay kiểu trung gian và điều kiện nào?
2. Vì sao dùng `set` để loại trùng **đầu vào** sai? Tạo một ví dụ ngắn nhất.
3. Mở rộng sang 4Sum, giải thích độ phức tạp và cách tránh tràn số khi cộng nhiều giá trị.
