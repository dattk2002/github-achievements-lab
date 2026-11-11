# LeetCode 973: K Closest Points to Origin (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/k-closest-points-to-origin/). Độ khó: Medium.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::kClosest(std::vector<std::vector<int>>& points, int k)` trả
`k` điểm gần gốc tọa độ nhất theo khoảng cách Euclid, mỗi điểm được tính theo
một vị trí trong đầu vào. Thứ tự kết quả không được bảo đảm. Hàm tạo bản sao
các điểm kết quả, giữ nguyên đầu vào.

Nguồn yêu cầu `1 <= k <= n <= 10000`, mỗi điểm có hai tọa độ nguyên trong
`[-10000,10000]`, và bảo đảm tập đáp án duy nhất nếu bỏ qua thứ tự. Giới hạn
kích thước và miền tọa độ là tiền điều kiện. Mở rộng riêng khi có hòa ở ranh
giới chọn: ưu tiên điểm có chỉ số đầu vào nhỏ hơn; các vị trí trùng tọa độ vẫn
được tính riêng. `k < 1`, `k > n`, mảng rỗng hoặc điểm không có đúng hai tọa độ
ném `std::invalid_argument` trước khi xử lý heap. Không xác thực tính duy nhất
của đáp án vì đã có quy tắc hòa cho mở rộng.

## Heap cực đại giới hạn k điểm

So sánh bình phương khoảng cách `x*x+y*y`, không cần căn bậc hai. Dùng khóa
`(distance_squared,index)`: khóa nhỏ hơn tốt hơn. Duyệt từng điểm, thêm khóa
vào heap cực đại rồi bỏ khóa lớn nhất nếu heap có hơn `k` phần tử. Cuối cùng
lấy các điểm theo chỉ số còn trong heap. Khi hòa khoảng cách, chỉ số lớn hơn
bị loại trước, đúng quy tắc mở rộng.

Với `[(3,4),(0,1),(-2,0),(1,-1)]`, `k=2`, hai điểm được chọn là `(0,1)` và
`(1,-1)`, có bình phương khoảng cách 1 và 2.

### Vì sao đúng?

Bất biến: sau mỗi tiền tố, heap chứa `min(k,số_điểm_đã_xét)` khóa nhỏ nhất.
Thêm một điểm mới tạo tập ứng viên cũ cộng điểm đó. Nếu vượt `k`, bỏ khóa
lớn nhất chính là bỏ phần tử tệ nhất trong tập; những điểm đã loại trước đó
không thể tốt hơn các khóa đang giữ và không cần xét lại. Bất biến đúng từ
heap rỗng và được duy trì sau mỗi bước, nên cuối dãy giữ đúng `k` điểm cần
chọn. Hàm căn bậc hai tăng trên số không âm nên xếp theo bình phương cho cùng
thứ tự khoảng cách.

## Độ phức tạp

Thời gian `O(n log(k+1))`, gồm cả lấy kết quả khỏi heap; bộ nhớ phụ `O(k)`
cho heap, thêm `O(k)` cho đầu ra. Heap tạm thời chứa tối đa `k+1` khóa.
Bình phương khoảng cách tối đa `200000000` theo nguồn; mã dùng `long long`
trước phép nhân để phép tính rõ ràng và an toàn, không dùng số thực.

## Ví dụ chạy được

Lưu thành `/tmp/lc-973-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    std::vector<std::vector<int>> points{{3,4},{0,1},{-2,0},{1,-1}};
    auto result = lab::Solution{}.kClosest(points,2);
    std::sort(result.begin(),result.end());
    for (const auto& p : result) std::cout << p[0] << ',' << p[1] << ' ';
    std::cout << '\n'; // 0,1 1,-1
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-973-k-closest-points-to-origin-cpp /tmp/lc-973-example.cpp -o /tmp/lc-973-example
/tmp/lc-973-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-973-k-closest-points-to-origin-cpp/test.cpp -o /tmp/lc-973-test
/tmp/lc-973-test
make test
make test-all
```

## Biên và kiểm thử

Oracle sắp toàn bộ chỉ số theo khoảng cách/chỉ số, lấy `k` đầu; kết quả hai
phía được chuẩn hóa theo tọa độ rồi so sánh **đa tập**, không giả định thứ tự
và không bỏ mất điểm trùng. Đối chiếu 44790 trường hợp: mọi mảng dài `1..5`
từ sáu điểm nhỏ với mọi `k`. Dữ liệu hòa/trùng ở đây còn kiểm tra quy tắc mở
rộng ngoài cam kết đáp án duy nhất của nguồn. Có ca tọa độ ±10000, 10000 điểm,
`k=1`, `k=n`, đầu vào lỗi và đầu vào không bị thay đổi. Test dùng mã thoát khác
0, không phụ thuộc `assert` hay `NDEBUG`.

## Bài tập

1. So sánh heap với sắp xếp toàn bộ khi `k` gần bằng `n`.
2. Thay khoảng cách bằng Manhattan và chỉ ra phần nào của thuật toán giữ nguyên.
3. Xử lý luồng điểm vô hạn với bộ nhớ `O(k)`; cần giữ thêm gì để trả tọa độ?
