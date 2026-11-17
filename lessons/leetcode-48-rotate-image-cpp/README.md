# LeetCode 48 — Rotate Image (C++17)

Nguồn: [Rotate Image trên LeetCode](https://leetcode.com/problems/rotate-image/),
độ khó Medium. Ví dụ, lời giải và phần giảng giải được tự viết.

## Hợp đồng

`lab::Solution::rotate(std::vector<std::vector<int>>& matrix)` xoay ma
trận vuông 90 độ **theo chiều kim đồng hồ**, thay đổi trực tiếp đầu vào,
không trả giá trị và không cấp phát ma trận phụ trong lời giải.

Nguồn có cạnh `1..20`, giá trị ô trong `[-1000,1000]`. Bài học cũng nhận
ma trận rỗng như phép xoay không làm gì, nhận mọi giá trị `int` vì chỉ
hoán đổi ô. Kích thước tối đa theo nguồn là tiền điều kiện không kiểm
tra. Mọi ma trận không vuông, gồm `{{}}`, bị từ chối bằng
`std::invalid_argument`. Kiểm tra **tất cả** các hàng trước phép đổi
đầu tiên để đầu vào lỗi không bị sửa dở.

## Chuyển vị rồi đảo từng hàng

1. Chuyển vị qua đường chéo chính: hoán đổi `(r,c)` với `(c,r)` chỉ khi
   `c > r`. Mỗi cặp được đổi đúng một lần, đường chéo giữ nguyên.
2. Đảo thứ tự phần tử trong từng hàng bằng `std::reverse`.

Một phần tử ở `(r,c)` sau chuyển vị tới `(c,r)`, sau đảo hàng tới
`(c,n-1-r)`. Đây chính là ánh xạ tọa độ của phép xoay 90 độ theo chiều
kim đồng hồ. Hai bước đều là song ánh nên không mất hoặc lặp giá trị.
Nếu đổi mọi cặp cả hai phía đường chéo, phép chuyển vị sẽ tự triệt tiêu;
nếu đảo thứ tự hai bước, kết quả lại xoay ngược chiều.

Ví dụ `[[4,9],[-3,2]]` chuyển vị thành `[[4,-3],[9,2]]`, rồi đảo mỗi
hàng thành `[[-3,4],[2,9]]`. Không có phép cộng trên giá trị ô nên các
giá trị cực trị của `int` cũng an toàn.

## Độ phức tạp

Thời gian `O(n²)` với `n > 0`, bộ nhớ phụ `O(1)`. Không thay đổi kích
thước ma trận hoặc cấp phát bản sao trong `rotate`. Oracle trong test
cố ý dùng một ma trận riêng để kiểm chứng theo cách độc lập.

## Ví dụ chạy được

Lưu thành `/tmp/lc48-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<int>> matrix{{4, 9}, {-3, 2}};
    lab::Solution{}.rotate(matrix);
    for (const auto& row : matrix) {
        for (int value : row) std::cout << value << ' ';
        std::cout << '\n';
    } // -3 4 rồi 2 9, mỗi hàng trên một dòng
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-48-rotate-image-cpp /tmp/lc48-example.cpp -o /tmp/lc48-example
/tmp/lc48-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-48-rotate-image-cpp/test.cpp -o /tmp/lc48-test
/tmp/lc48-test
make test
make test-all
```

## Biên và kiểm thử

19.768 ma trận cạnh `0..3` trên tập giá trị `{-1,0,1}` được so với
oracle ghi từng ô vào tọa độ đích `(c,n-1-r)` trong ma trận mới. Mỗi ca
còn kiểm tra xoay bốn lần khôi phục ảnh ban đầu. Có thêm cạnh 20 với mọi
ô phân biệt, số cực trị, ma trận một ô, hàng lệch và chữ nhật không
vuông. Với đầu vào sai, test kiểm tra ngoại lệ và nội dung không đổi.
Không dùng `assert`; `NDEBUG` không bỏ qua kiểm thử.

## Bài tập

1. Viết phép xoay ngược chiều bằng hai phép biến đổi tại chỗ.
2. Xoay từng nhóm bốn ô theo lớp và so sánh số lần hoán đổi.
3. Với ma trận chữ nhật, kích thước đầu ra thay đổi ra sao?
