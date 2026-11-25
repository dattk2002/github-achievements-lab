# LeetCode 3934 — Smallest Unique Subarray (C++17)

Ngày nguồn `2026-11-25`. Độ khó **Hard**. [Đề bài gốc trên LeetCode](https://leetcode.com/problems/smallest-unique-subarray/).

## Hợp đồng

`lab::Solution::smallestUniqueSubarray(std::vector<int>& nums)` trả về độ dài
nhỏ nhất của một đoạn liên tiếp không rỗng có dãy giá trị xuất hiện đúng một
lần. Hai vị trí bắt đầu khác nhau được tính là hai lần xuất hiện nếu các giá
trị tương ứng bằng nhau, kể cả khi hai đoạn chồng lấp.

Đầu vào phải thỏa `1 <= nums.size() <= 100000` và `1 <= nums[i] <= 100000`.
Hàm giữ nguyên đầu vào. Đáp án luôn tồn tại vì cả mảng chỉ xuất hiện một lần.

## Thuật toán

Mỗi đoạn bắt đầu ở vị trí `i` là một tiền tố của hậu tố `nums[i..n-1]`.
Sắp xếp các hậu tố theo thứ tự từ điển để tạo mảng hậu tố. Mọi hậu tố có
chung một tiền tố tạo thành một khoảng liên tiếp trong thứ tự này. Vì vậy,
nếu một tiền tố xuất hiện ở hậu tố khác thì ít nhất một trong hai hậu tố
kề với hậu tố đang xét cũng có tiền tố đó.

1. Tạo mảng hậu tố bằng kỹ thuật nhân đôi. Xem như có một phần tử canh nhỏ
   hơn mọi giá trị ở cuối mảng và sắp xếp các phép xoay của mảng mở rộng.
   Khi so sánh hai hậu tố, phần tử canh khiến hậu tố ngắn hơn đứng trước
   nếu nó là tiền tố của hậu tố dài hơn. Do đó thứ tự các phép xoay cũng
   cho thứ tự hậu tố sau khi bỏ vị trí canh.
2. Ban đầu xếp hạng theo một phần tử. Khi đã có hạng cho các khối dài
   `width`, thứ tự các khối dài gấp đôi do cặp hạng của hai nửa quyết định.
   Dịch các vị trí đã sắp xếp lùi `width` theo vòng để có thứ tự theo hạng
   nửa sau. Dùng counting sort ổn định theo hạng nửa đầu rồi gán hạng mới.
   Dừng khi các hạng phân biệt hoặc độ dài khối đã phủ cả mảng mở rộng.
3. Dùng thuật toán Kasai để tính `lcp[r]`, độ dài tiền tố chung của hai
   hậu tố hạng `r-1` và `r`. Duyệt các vị trí bắt đầu theo thứ tự trong
   mảng gốc. Nếu hai hậu tố vừa khớp `h > 0` phần tử, bỏ phần tử đầu
   của cả hai vẫn giữ thứ tự từ điển và còn ít nhất `h-1` phần tử
   khớp. Hậu tố kề trước tại vị trí mới cũng khớp ít nhất chừng đó,
   vì vậy có thể tiếp tục so từ `h-1`. Khi không có hậu tố kề trước,
   đặt lại độ dài khớp về 0.
4. Với hậu tố hạng `r`, đặt `k = max(lcp[r], lcp[r+1])`, coi LCP
   với hàng xóm vắng mặt bằng 0. Mọi tiền tố có độ dài từ 1 đến `k`
   đều lặp lại, còn tiền tố dài `k+1` xuất hiện đúng một lần nếu nó
   vừa trong hậu tố. Bỏ qua ứng viên vượt độ dài hậu tố và lấy ứng
   viên nhỏ nhất còn lại.

Sắp xếp ban đầu mất `O(n log n)`. Mỗi vòng nhân đôi mất `O(n)` và
có `O(log n)` vòng. Bước Kasai mất `O(n)` vì độ dài khớp giảm tối đa
một đơn vị ở mỗi bước bình thường, và gặp hạng 0 tối đa một lần.
Tổng thời gian `O(n log n)`, bộ nhớ phụ `O(n)`. So sánh dựa trên hạng
chính xác của các khối.

## Ví dụ tự xây dựng

- Với `[4,9,4,9,4]`, cả hai giá trị đơn đều lặp. Các đoạn dài 2 là
  `[4,9]` và `[9,4]`, mỗi dạng xuất hiện hai lần. Đoạn `[9,4,9]`
  xuất hiện một lần nên đáp án là 3.
- Với `[8,4,8,9,4]`, giá trị 9 xuất hiện một lần nên đáp án là 1.
- Với `[6,6,6,6,6]`, mỗi đoạn độ dài `k` có `6-k` lần xuất hiện.
  Chỉ độ dài 5 cho đúng một lần xuất hiện.

Chạy từ thư mục gốc kho mã để thử ví dụ đầu tiên rồi chạy bộ kiểm thử:

```sh
d=lessons/leetcode-3934-smallest-unique-subarray
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I"$d" -x c++ -o /tmp/lc3934-example - <<'CPP'
#include "lesson.hpp"
#include <iostream>

int main() {
    std::vector<int> nums{4, 9, 4, 9, 4};
    std::cout << lab::Solution{}.smallestUniqueSubarray(nums) << '\n'; // 3
}
CPP
/tmp/lc3934-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG "$d/test.cpp" -o /tmp/lc3934-test
/tmp/lc3934-test
```

## Kiểm thử

Bộ kiểm thử đếm trực tiếp các đoạn theo nội dung để đối chiếu toàn bộ
9.840 mảng độ dài từ 1 đến 8 trên tập `{1,37,100000}`. Các ca tính tay
bao gồm mảng một phần tử, đoạn lặp chồng lấp và mảng hằng ở kích thước
tối đa. Với mảng xen kẽ 100.000 phần tử, từ bốn cửa sổ trở lên thì mỗi
kiểu đoạn theo tính chẵn lẻ của vị trí đầu xuất hiện ít nhất hai lần.
Khi còn ba cửa sổ, đoạn ở giữa xuất hiện đúng một lần, cho đáp án 99.998.

Mỗi ca dùng lại cùng đối tượng và kiểm tra mảng đầu vào giữ nguyên.
Khi kết quả sai, chương trình in tên ca và thoát với mã khác 0, kể cả
khi biên dịch với `NDEBUG`.

## Bài tập

1. Liệt kê các hậu tố của `[4,9,4,9,4]` theo thứ tự từ điển rồi tính
   LCP giữa từng cặp kề nhau.
2. Tìm một hậu tố mà cả hậu tố đó cũng xuất hiện ở vị trí khác. Giải
   thích điều kiện lọc ứng viên ở bước cuối.
3. Mở rộng hàm để trả về vị trí bắt đầu nhỏ nhất trong số các đoạn đạt
   độ dài tối ưu.
