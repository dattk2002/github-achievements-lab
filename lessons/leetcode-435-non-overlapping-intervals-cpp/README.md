# LeetCode 435 — Non-overlapping Intervals (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/non-overlapping-intervals/).
Diễn giải, ví dụ và lời giải được viết riêng.

## Hợp đồng

`lab::Solution::eraseOverlapIntervals(std::vector<std::vector<int>>& intervals)`
trả số khoảng ít nhất phải bỏ để các khoảng còn lại không chồng lấn. Hai khoảng
chạm đầu mút như `[1,4]` và `[4,7]` được giữ cùng nhau. Hàm không sửa mảng gốc.

Nguồn cho `1 <= n <= 100000`, mỗi khoảng có hai phần tử và
`-50000 <= start < end <= 50000`. Giới hạn số lượng và miền giá trị là tiền điều
kiện. Riêng cấu trúc mỗi khoảng được kiểm tra: sai số phần tử hoặc `start >= end`
thì ném `std::invalid_argument`, trước khi sắp xếp; đầu vào vẫn giữ nguyên.
Mở rộng: mảng rỗng trả `0`.

## Tham lam theo thời điểm kết thúc

Bỏ ít nhất tương đương giữ nhiều nhất. Sao chép rồi sắp xếp theo `end` tăng dần,
hòa thì theo `start` tăng dần. Giữ khoảng đầu tiên. Chỉ giữ khoảng tiếp theo nếu
`start >= last_end` của khoảng đã giữ gần nhất. Kết quả là `n - kept`.

Với `[[0,10],[1,2],[2,3],[3,4]]`, bỏ khoảng dài `[0,10]`, giữ ba khoảng còn lại,
kết quả `1`. Chọn khoảng bắt đầu sớm nhất sẽ không tối ưu ở ví dụ này.

### Chứng minh bằng đổi chỗ

Gọi `g` là khoảng kết thúc sớm nhất, `o` là khoảng đầu trong một nghiệm giữ nhiều
khoảng nhất. Vì `end(g) <= end(o)`, thay `o` bằng `g` vẫn cho phép giữ mọi khoảng
sau `o`. Do đó tồn tại nghiệm tối ưu bắt đầu bằng `g`. Sau khi chọn `g`, bài toán
còn lại chỉ gồm các khoảng có `start >= end(g)`, áp dụng lại lập luận trên.
Quy nạp cho thấy số khoảng giữ là lớn nhất, nên số bị loại là nhỏ nhất.

## Độ phức tạp

`O(n log n)` thời gian, `O(n)` bộ nhớ phụ để giữ nguyên đầu vào; bản sao chứa
hai số mỗi khoảng. Sắp xếp dùng thêm `O(log n)` ngăn xếp. Kết quả không quá `n`
nên vừa kiểu `int`.

## Ví dụ chạy được

Lưu thành `/tmp/interval-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<int>> intervals{{0,10},{1,2},{2,3},{3,4}};
    std::cout << lab::Solution{}.eraseOverlapIntervals(intervals) << '\n'; // 1
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-435-non-overlapping-intervals-cpp /tmp/interval-example.cpp -o /tmp/interval-example
/tmp/interval-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-435-non-overlapping-intervals-cpp/test.cpp -o /tmp/interval-test
/tmp/interval-test
make test
make test-all
```

## Biên và kiểm thử

Oracle độc lập thử mọi tập con, sắp theo đầu mút bắt đầu rồi kiểm tra tính hợp lệ;
so sánh với toàn bộ 9331 danh sách dài `0..5` từ sáu khoảng nhỏ, có trùng lặp.
Kiểm tra riêng khoảng lồng nhau, mảng chưa sắp, chạm đầu mút, đầu vào lỗi,
100000 khoảng trùng và 100000 khoảng nối tiếp bao phủ miền `[-50000,50000]`.
Mỗi ca xác nhận không sửa đầu vào. Kiểm tra lỗi dùng mã thoát khác 0,
không phụ thuộc `assert` hay `NDEBUG`.

## Bài tập

1. Tìm phản ví dụ nếu sắp theo độ dài thay vì kết thúc.
2. Trả thêm chỉ số gốc của những khoảng được giữ.
3. Nếu mỗi khoảng có lợi ích khác nhau, tại sao cần quy hoạch động thay cho quy tắc này?
