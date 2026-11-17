# LeetCode 494 — Target Sum (C++17)

Nguồn: [Target Sum trên LeetCode](https://leetcode.com/problems/target-sum/),
độ khó Medium. Diễn giải, ví dụ, thuật toán và test được tự viết.

## Hợp đồng

`lab::Solution::findTargetSumWays(std::vector<int>& nums, int target)`
đếm cách gán một dấu `+` hoặc `-` cho **mỗi vị trí**, sao cho tổng có
dấu bằng `target`. Vị trí có giá trị bằng nhau vẫn được phân biệt;
`+0` và `-0` là hai lựa chọn. Không thay đổi đầu vào.

Nguồn có `1..20` vị trí không âm, tổng không vượt 1000, target thuộc
`[-1000,1000]`. Bài học kiểm tra số âm, hơn 20 vị trí hoặc tổng lớn hơn
1000 và ném `std::invalid_argument`, kể cả khi target nằm quá xa.
Mở rộng: mảng rỗng có một cách đạt 0 là biểu thức rỗng; mọi target `int`
đều được nhận, target ngoài `[-tổng,tổng]` trả 0. Các phép kiểm tra target
dùng `long long`, không lấy trị tuyệt đối của `INT_MIN`.

## Đổi bài toán thành đếm tập con

Gọi `S` là tổng đầu vào, `P` là tổng các vị trí được gán dấu cộng,
`N` là tổng các vị trí mang dấu trừ. Ta có:

```text
P + N = S
P - N = target
P = (S + target) / 2
```

Nếu target vượt miền hoặc `S + target` lẻ thì không có cách. Ngược lại,
mỗi tập vị trí có tổng `P` tương ứng đúng một cách gán dấu: những vị trí
trong tập mang dấu cộng, phần còn lại mang dấu trừ.

Khởi tạo `ways[0] = 1`. Xử lý từng vị trí có giá trị `v`, duyệt tổng
**giảm dần** từ `P` tới `v`, cộng `ways[s-v]` vào `ways[s]`. Bất biến:
sau khi xử lý `i` vị trí, bảng đếm đúng các tập con từ `i` vị trí đó.
Một tập hoặc không chọn vị trí mới, hoặc chọn nó đúng một lần; duyệt
giảm giữ vế phải ở lớp cũ. Riêng `v = 0`, mỗi ô tự cộng chính nó, nhân
đôi số cách đúng với hai lựa chọn dấu. Dùng biến vòng lặp có dấu để
vòng lặp dừng được sau tổng 0.

Ví dụ `[0,0,1]`, target 1: số 1 phải mang dấu cộng, mỗi số 0 có hai
lựa chọn, nên có `2 * 2 = 4` cách. Với `[1,2,3]`, target 0 có hai cách
`+1+2-3` và `-1-2+3`.

## Độ phức tạp và số học

Với `n` vị trí và mục tiêu tập con `P`, thời gian `O(n(P+1)+1)`, bộ nhớ
phụ `O(P+1)`. Khi bị loại bởi miền hoặc tính chẵn lẻ, chỉ mất `O(n)`.
Vì đã giới hạn `n <= 20`, mọi ô đếm không vượt `2^20 = 1048576`, vừa
`int` 32 bit của môi trường repo. Tổng được cộng trong `long long`
trước khi xác thực để tránh tràn từ các giá trị `int` không hợp lệ.

## Ví dụ chạy được

Lưu thành `/tmp/lc494-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> nums{0, 0, 1};
    std::cout << lab::Solution{}.findTargetSumWays(nums, 1) << '\n'; // 4
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-494-target-sum-cpp /tmp/lc494-example.cpp -o /tmp/lc494-example
/tmp/lc494-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-494-target-sum-cpp/test.cpp -o /tmp/lc494-test
/tmp/lc494-test
make test
make test-all
```

## Biên và kiểm thử

Oracle liệt kê trực tiếp mọi bộ dấu bằng bitmask, không đếm tập con
bằng DP. Có 15.309 ca target trên mọi mảng dài `0..6`, giá trị `0..2`,
gồm target trong miền và ngay ngoài miền. Thêm 20 số 0 cho 1.048.576
cách, 20 số 1 đạt 0 cho 184.756 cách, tổng 1000, `INT_MIN`, `INT_MAX`,
đầu vào sai và kiểm tra không sửa mảng. Test vẫn trả mã thoát khác 0 khi
sai với `NDEBUG`.

## Bài tập

1. Viết DP theo tổng có dấu và so sánh kích thước bảng với phép biến đổi.
2. Khôi phục một bộ dấu thay vì đếm mọi cách.
3. Nếu cho phép số âm trong đầu vào, cần sửa hợp đồng hoặc mô hình ra sao?
