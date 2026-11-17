# LeetCode 347 — Top K Frequent Elements (C++17)

Nguồn: [Top K Frequent Elements trên LeetCode](https://leetcode.com/problems/top-k-frequent-elements/),
độ khó Medium. Tóm tắt, ví dụ, thuật toán và kiểm thử được tự viết.

## Hợp đồng

`lab::Solution::topKFrequent(std::vector<int>& nums, int k)` trả `k` giá trị
**phân biệt** có tần suất lớn nhất. Thứ tự kết quả không được bảo đảm.
Đầu vào giữ nguyên. Nguồn có `1 <= n <= 100000`, giá trị trong
`[-10000, 10000]`, `1 <= k <= số giá trị phân biệt`, bảo đảm tập kết quả
duy nhất. Kích thước và miền giá trị là tiền điều kiện không kiểm tra.

Mở rộng của bài học: `k = 0` trả vector rỗng, kể cả khi `nums` rỗng;
`k < 0` hoặc `k` vượt số giá trị phân biệt gây `std::invalid_argument`.
Nếu đồng hạng tại ranh giới, chọn tùy ý cho đủ `k`: mọi giá trị được chọn
phải có tần suất không thấp hơn mọi giá trị bị bỏ. Không cam kết cùng một
tập đồng hạng giữa các thư viện hoặc lần thực thi.

## Đếm và chia bucket theo tần suất

1. Dùng `unordered_map<int, size_t>` đếm số lần mỗi giá trị xuất hiện.
2. Tạo `n + 1` bucket. Đưa mỗi giá trị vào bucket có chỉ số bằng tần suất.
3. Duyệt bucket từ `n` về 1, lấy các giá trị cho tới khi đủ `k`.

Sau bước đếm, mỗi giá trị phân biệt xuất hiện đúng một lần trong đúng
bucket của nó. Khi lấy ở bucket `f`, mọi bucket có tần suất lớn hơn đã
được xét. Vì vậy không bỏ một giá trị phổ biến hơn để lấy một giá trị
kém phổ biến. Dừng ngay khi đủ `k` xử lý cả trường hợp đồng hạng mà không
sinh kết quả trùng hoặc quá dài.

Ví dụ `[8, -2, 8, 5, -2, 8, 5, 8]` có tần suất `8:4`, `-2:2`, `5:2`.
Với `k = 1`, kết quả là `[8]`. Với `k = 2`, `[8, -2]` hoặc `[5, 8]`
đều hợp lệ theo mở rộng đồng hạng. Không cần sắp xếp toàn bộ mảng.

## Độ phức tạp

Gọi `u` là số giá trị phân biệt. Thời gian **kỳ vọng** `O(n)` do bảng băm;
không phải bảo đảm xấu nhất. Khi nhiều khóa va chạm, phần bảng băm có thể
tốn `O(nu)`. Bucket được dựng và duyệt trong `O(n + u)`; tổng bộ nhớ phụ
`O(n + u) = O(n)`, ngoài kết quả `O(k)`.

## Ví dụ chạy được

Lưu thành `/tmp/lc347-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> nums{8, -2, 8, 5, -2, 8, 5, 8};
    for (int value : lab::Solution{}.topKFrequent(nums, 1)) std::cout << value << '\n'; // 8
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-347-top-k-frequent-elements-cpp /tmp/lc347-example.cpp -o /tmp/lc347-example
/tmp/lc347-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-347-top-k-frequent-elements-cpp/test.cpp -o /tmp/lc347-test
/tmp/lc347-test
make test
make test-all
```

## Biên và kiểm thử

12.355 ca sinh từ mọi mảng dài `0..7` trên `{-1,0,1}`, với mọi `k` hợp lệ.
Oracle dùng `std::map`, kiểm tra tập kết quả có đủ phần tử, không trùng,
không có giá trị lạ và so mọi cặp được chọn/bị bỏ theo tần suất. Test không
phụ thuộc thứ tự hoặc cách phá đồng hạng. Có thêm 100.000 phần tử, 20.001
khóa phân biệt, `INT_MIN`/`INT_MAX`, `k` sai và kiểm tra không sửa đầu vào.
Test vẫn thất bại với mã thoát khác 0 khi bật `NDEBUG`.

## Bài tập

1. So sánh bộ nhớ bucket với min-heap kích thước `k`.
2. Nếu buộc ưu tiên giá trị nhỏ khi đồng hạng, độ phức tạp thay đổi thế nào?
3. Thiết kế cách cập nhật khi dữ liệu đến từng phần và chỉ cần `k` nhỏ.
