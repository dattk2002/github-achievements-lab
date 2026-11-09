# LeetCode 11 — Container With Most Water (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/container-with-most-water/).
Ví dụ, diễn giải và mã dưới đây được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::maxArea(std::vector<int>& height)` trả về diện tích lớn nhất
`(j-i) * min(height[i], height[j])` với `i < j`. Hai đường thẳng đứng cùng trục
hoành tạo thành bình; không được nghiêng đường thẳng. Hàm giữ nguyên đầu vào.

Theo nguồn: `2 <= n <= 100000`, `0 <= height[i] <= 10000`. Các giới hạn này
là tiền điều kiện, hàm không xác thực. Mở rộng riêng: mảng rỗng hoặc một phần tử
trả về `0` vì không có cặp cột. Diện tích tối đa `99999 * 10000 = 999990000`
vừa kiểu `int` 32 bit.

## Hai con trỏ

Đặt `left` ở đầu và `right` ở cuối. Tính diện tích của cặp hiện tại, cập nhật
kết quả rồi bỏ cột thấp hơn; nếu bằng nhau, bỏ cột bên trái. Dừng khi hai con trỏ
gặp nhau. Mỗi bước giảm chiều rộng ít nhất một.

Với `[3,8,2,7,4,8]`, cặp chỉ số `1,5` chứa được `4 * 8 = 32` đơn vị diện tích.
Cặp ngoài cùng chỉ chứa `5 * 3 = 15`: rộng nhất chưa chắc là tốt nhất.

### Vì sao đúng?

Giả sử `height[left] <= height[right]`. Với mọi `k` nằm giữa hai đầu,
cặp `(left,k)` có chiều rộng nhỏ hơn và chiều cao không vượt `height[left]`.
Nó không thể tốt hơn cặp `(left,right)` đã được ghi nhận. Vì vậy bỏ `left`
không làm mất đáp án chưa xét tốt hơn. Lập luận đối xứng cho đầu phải.
Lặp lại việc loại bỏ an toàn cho đến khi hết cặp, biến `best` chứa cực đại.

## Độ phức tạp

Thời gian `O(n)`, bộ nhớ phụ `O(1)`. Đầu vào được truyền tham chiếu nhưng không sửa.

## Ví dụ chạy được

Lưu thành `/tmp/container-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> height{3,8,2,7,4,8};
    std::cout << lab::Solution{}.maxArea(height) << '\n'; // 32
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-11-container-with-most-water-cpp /tmp/container-example.cpp -o /tmp/container-example
/tmp/container-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-11-container-with-most-water-cpp/test.cpp -o /tmp/container-test
/tmp/container-test
make test
make test-all
```

## Biên và kiểm thử

`test.cpp` dùng kiểm tra tường minh, vẫn trả mã lỗi khi bật `NDEBUG`.
Oracle duyệt mọi cặp cho toàn bộ 5461 mảng độ dài `0..6` trên `{0,1,3,5}`.
Có ca hai cột cao ở giữa, hai đầu bằng nhau, toàn số 0, đầu vào ngắn mở rộng,
100000 cột và kết quả gần một tỷ. Mỗi ca kiểm tra đầu vào không thay đổi.

## Bài tập

1. Chứng minh quy tắc bỏ đầu phải khi hai chiều cao bằng nhau cũng đúng.
2. Tìm phản ví dụ cho cách luôn bỏ cột cao hơn.
3. Trả thêm một cặp chỉ số tối ưu và nêu cách xử lý nhiều đáp án bằng nhau.
