# LeetCode 239: Sliding Window Maximum (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/sliding-window-maximum/). Độ khó: Hard.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::maxSlidingWindow(std::vector<int>& nums, int k)` trả cực đại
của từng cửa sổ liên tiếp dài `k`, theo thứ tự từ trái sang phải. Có đúng
`n-k+1` kết quả. Hàm giữ nguyên mảng gốc.

Nguồn cho `1 <= n <= 100000`, `-10000 <= nums[i] <= 10000`, `1 <= k <= n`.
Giới hạn `n` và giá trị phần tử là tiền điều kiện. Quy tắc mở rộng có kiểm tra:
`k < 1`, `k > n` hoặc mảng rỗng đều ném `std::invalid_argument`, trước khi cấp
phát kết quả. Số âm và phần tử trùng nhau được xử lý bình thường.

## Deque đơn điệu

Lưu **chỉ số** ứng viên trong deque, tăng dần theo chỉ số và giảm nghiêm ngặt
theo giá trị. Ở vị trí mới `i`:

1. Bỏ đầu deque nếu chỉ số đó đã nằm ngoài cửa sổ (`index + k <= i`).
2. Bỏ cuối deque khi giá trị cũ nhỏ hơn hoặc bằng `nums[i]`.
3. Thêm `i`. Khi đã đọc ít nhất `k` phần tử, giá trị ở đầu deque là kết quả.

Với `[4,1,7,3,8,2]`, `k=3`, kết quả `[7,7,8,8]`. Một ứng viên lớn hơn có thể
vẫn chưa hết hạn; phải kiểm tra chỉ số trước mỗi lần xuất kết quả.

### Chứng minh

Một chỉ số cũ có giá trị không lớn hơn phần tử mới sẽ hết hạn sớm hơn phần tử
mới. Trong mọi cửa sổ tương lai còn chứa chỉ số cũ ấy, phần tử mới cũng có mặt
và tốt ít nhất bằng nó, nên loại chỉ số cũ là an toàn. Các chỉ số hết hạn không
thuộc cửa sổ hiện tại hoặc tương lai. Sau hai phép loại bỏ, deque giữ đủ ứng
viên và giảm theo giá trị, nên đầu deque chứa cực đại. Bất biến đúng từ cửa sổ
đầu tiên và được giữ sau mỗi bước, chứng minh mọi kết quả đúng.

## Độ phức tạp

Mỗi chỉ số được thêm một lần và bị bỏ nhiều nhất một lần, tổng thời gian
`O(n)` dù có vòng lặp lồng nhau. Deque dùng `O(k)` bộ nhớ phụ; tính thêm vector
kết quả là `O(n-k+1)` bộ nhớ đầu ra, tổng `O(n)`.

## Ví dụ chạy được

Lưu thành `/tmp/lc-239-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> nums{4,1,7,3,8,2};
    for (int value : lab::Solution{}.maxSlidingWindow(nums,3)) std::cout << value << ' ';
    std::cout << '\n'; // 7 7 8 8
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-239-sliding-window-maximum-cpp /tmp/lc-239-example.cpp -o /tmp/lc-239-example
/tmp/lc-239-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-239-sliding-window-maximum-cpp/test.cpp -o /tmp/lc-239-test
/tmp/lc-239-test
make test
make test-all
```

## Biên và kiểm thử

Oracle quét từng phần tử của mỗi cửa sổ. Toàn bộ mảng dài `1..7` trên
`{-2,0,2}` được kiểm tra với mọi `k` hợp lệ: 21324 trường hợp. Có ca cực đại cũ
hết hạn trong dãy giảm, hòa giá trị, toàn âm, `k=1`, `k=n`, 100000 phần tử,
và mọi loại `k` không hợp lệ đã công bố. Mỗi ca xác nhận mảng gốc giữ nguyên.
Kiểm tra lỗi thoát khác 0, không phụ thuộc `assert` hay `NDEBUG`.

## Bài tập

1. Đổi deque để trả cực tiểu của mỗi cửa sổ.
2. Nếu cần chỉ số cực đại đầu tiên khi hòa, điều kiện loại ở đuôi thay đổi ra sao?
3. So sánh deque với multiset về thời gian và cách xử lý phần tử trùng.
