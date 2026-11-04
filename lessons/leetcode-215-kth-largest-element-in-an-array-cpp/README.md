# LeetCode 215 — Phần tử lớn thứ k bằng min-heap

Nguồn công khai: [LeetCode 215: Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-04**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::findKthLargest(std::vector<int>& nums, int k)` trả phần tử ở thứ hạng `k` khi xét các giá trị từ lớn xuống nhỏ. Các giá trị trùng vẫn chiếm nhiều thứ hạng. Ví dụ `{9, 7, 7, 3}` có phần tử lớn thứ ba là 7. Hàm giữ nguyên vector đầu vào.

Bài gốc có `1 <= k <= nums.size() <= 100000` và `-10000 <= nums[i] <= 10000`. Bản này ném `std::out_of_range` nếu `k <= 0` hoặc `k > nums.size()`, kể cả khi vector rỗng. Các giới hạn kích thước/giá trị còn lại là tiền điều kiện, không kiểm tra thêm. Lời giải chỉ so sánh, không cộng/trừ các giá trị.

## Thuật toán và bất biến

Giữ min-heap chứa tối đa `k` phần tử lớn nhất đã thấy. `std::priority_queue` với `std::greater<int>` đặt giá trị **nhỏ nhất trong heap** ở `top()`.

Nếu heap chưa đủ `k`, đưa phần tử mới vào. Nếu đã đủ và phần tử mới lớn hơn `top()`, bỏ `top()` rồi đưa phần tử mới vào; nếu không, giữ nguyên heap. Với giá trị mới bằng `top()`, thay một bản sao bằng một bản sao không đổi tập giá trị, nên có thể bỏ qua. Các bản sao đã có trong heap vẫn được giữ.

**Bất biến:** sau mỗi tiền tố, heap chứa `min(k, số phần tử đã duyệt)` giá trị lớn nhất của tiền tố, tính cả số lần xuất hiện. Khi chưa đủ, mọi giá trị đều phải có trong heap. Khi đã đủ, một giá trị không lớn hơn giá trị nhỏ nhất đang giữ không thể đẩy phần tử nào cần giữ ra; giá trị lớn hơn phải thay giá trị nhỏ nhất. Do đó bất biến được duy trì. Kết thúc, heap có đủ `k` phần tử, và phần tử nhỏ nhất trong đó chính là phần tử lớn thứ `k`.

Độ phức tạp: O(n log(k+1)) thời gian xấu nhất và O(k) bộ nhớ phụ. Viết `log(k+1)` để bao gồm `k=1`, khi thuật toán chỉ cần O(n). Không sắp xếp toàn mảng. Khi `k` gần `n`, heap dùng gần O(n) bộ nhớ; quickselect là hướng học khác với đánh đổi riêng.

## Ví dụ chạy được

Lưu thành `/tmp/kth-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-215-kth-largest-element-in-an-array-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{8, 2, 8, -3, 10};
    lab::Solution solution;
    std::cout << solution.findKthLargest(nums, 3) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/kth-example.cpp -o /tmp/kth-example
/tmp/kth-example
```

Kết quả: `8`; nếu loại trùng trước thì sẽ sai hợp đồng.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-215-kth-largest-element-in-an-array-cpp/test.cpp -o /tmp/kth-test
/tmp/kth-test
make test-all
```

Test trả mã 1 khi sai ngay cả khi có `NDEBUG`. Bao phủ số âm, bản sao, một phần tử, hai đầu miền giá trị, `k=1`, `k=n`, hạng âm/0/quá lớn và vector rỗng. Với 1.092 dãy độ dài 1..6 trên tập `{-2, 0, 5}`, kiểm tra mọi hạng bằng oracle sắp xếp giảm dần trên một bản sao. Mảng 100.000 phần tử có một ngoại lệ lớn kiểm tra hạng đầu, giữa và cuối. Mọi ca hợp lệ xác nhận không sửa đầu vào.

## Bài tập

1. Chuyển thành cấu trúc nhận từng số theo luồng và trả phần tử lớn thứ k sau mỗi lần thêm; khi chưa đủ k phần tử phải trả gì?
2. So sánh heap với quickselect về bộ nhớ, độ phức tạp kỳ vọng/xấu nhất và khả năng sửa đầu vào.
3. Nếu hỏi phần tử lớn thứ k **phân biệt**, cần thay hợp đồng và cấu trúc dữ liệu thế nào?
