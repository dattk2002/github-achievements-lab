# LeetCode 42: Trapping Rain Water (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/trapping-rain-water/). Độ khó: Hard.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::trap(std::vector<int>& height)` trả tổng thể tích nước giữ lại
sau mưa khi mỗi cột có bề rộng 1. Nước tại vị trí `i` bằng
`min(cao_nhất_bên_trái, cao_nhất_bên_phải) - height[i]`, trong đó hai miền
cực đại đều gồm chính vị trí `i`. Hàm không sửa đầu vào.

Nguồn quy định `1 <= n <= 20000`, `0 <= height[i] <= 100000`. Đây là tiền điều
kiện, hàm không xác thực. Mở rộng riêng: mảng rỗng trả `0`. Một hoặc hai cột
không giữ được nước. Chặn trên là `19998 * 100000 = 1999800000`, vừa `int` 32 bit.

## Hai đầu với hai mực chắn

`left_max` và `right_max` là độ cao lớn nhất ở phần đã xử lý bên trái và phải,
khởi đầu bằng 0. Mỗi bước xử lý phía có cực đại nhỏ hơn: cập nhật cực đại với
cột hiện tại rồi cộng hiệu giữa cực đại và độ cao cột, sau đó tiến con trỏ.
Chỉ số là số nguyên có dấu để đầu phải có thể giảm về `-1` an toàn.

Với `[4,1,2,0,3]`, các cột bên trong giữ lần lượt `2,1,3` đơn vị nước,
tổng `6`. Hai đầu không giữ nước. Cần cộng nước ở từng vị trí, thay vì lấy
một diện tích duy nhất giữa hai cột.

### Vì sao đúng?

Giả sử `left_max <= right_max`. Nếu cột trái hiện tại không vượt `left_max`,
phía phải đã có chắn cao ít nhất `left_max`, còn cực đại thật bên trái chính
là `left_max`. Mực nước tại đây được xác định hoàn toàn bởi chắn trái ấy.
Nếu cột hiện tại cao hơn `left_max`, nó lập cực đại mới ở bên trái nên không
giữ nước tại chính nó, bất kể các cột chưa xét. Cả hai trường hợp đều đúng với
hiệu sau khi cập nhật cực đại. Phía phải có lập luận đối xứng. Mỗi cột được xử
lý đúng một lần, nên tổng thu được là tổng thể tích cần tìm.

## Độ phức tạp

Thời gian `O(n)`, bộ nhớ phụ `O(1)`; không sao chép hoặc thay đổi mảng gốc.

## Ví dụ chạy được

Lưu thành `/tmp/lc-42-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> height{4,1,2,0,3};
    std::cout << lab::Solution{}.trap(height) << '\n'; // 6
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-42-trapping-rain-water-cpp /tmp/lc-42-example.cpp -o /tmp/lc-42-example
/tmp/lc-42-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-42-trapping-rain-water-cpp/test.cpp -o /tmp/lc-42-test
/tmp/lc-42-test
make test
make test-all
```

## Biên và kiểm thử

Oracle độc lập quét toàn bộ bên trái và bên phải của mỗi vị trí, đối chiếu
5461 mảng độ dài `0..6` trên `{0,1,3,5}`. Các ca riêng gồm dãy tăng/giảm,
hai hố nước, nhiều cột bằng nhau, đầu vào ngắn và 20000 cột tạo bể có thể tích
`1999800000`. Mọi ca kiểm tra đầu vào giữ nguyên. Kiểm tra dùng mã thoát khác 0,
hoạt động cả khi định nghĩa `NDEBUG`.

## Bài tập

1. Viết phương án lưu hai mảng cực đại và so sánh chi phí bộ nhớ.
2. Nếu bề rộng mỗi cột khác nhau, công thức cộng thể tích thay đổi thế nào?
3. Tìm phản ví dụ cho cách chỉ dựa vào hai cột kề một vị trí để tính nước.
