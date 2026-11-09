# LeetCode 1606 — Máy chủ xử lý nhiều yêu cầu nhất

Nguồn: [Find Servers That Handled Most Number of Requests](https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/).
Ngày nguồn (`source_date`): **2026-11-09**. Độ khó: **Hard**.
Tóm tắt, ví dụ, lời giải và kiểm thử dưới đây được tự viết cho C++17.

## Hợp đồng và tiền điều kiện

```cpp
std::vector<int> lab::Solution::busiestServers(
    int k, std::vector<int>& arrival, std::vector<int>& load);
```

Có `k` máy, ID từ `0` đến `k-1`, mỗi máy chỉ nhận một yêu cầu tại một
thời điểm. Với yêu cầu thứ `i`, bắt đầu tìm từ ID `i % k`, đi theo chiều
tăng ID và quay về 0 khi cần; giao việc cho máy rảnh đầu tiên. Nếu không
có máy rảnh thì bỏ yêu cầu. Chỉ số `i` vẫn tăng dù yêu cầu bị bỏ.
Máy kết thúc công việc tại thời điểm `t` có thể nhận việc mới ngay tại `t`.
Trả về tất cả ID có số yêu cầu nhận thành công lớn nhất, không so sánh
tổng thời gian làm việc. Bài gốc cho phép thứ tự bất kỳ; hàm này trả ID tăng dần.

Tiền điều kiện: `1 <= k <= 100000`, hai mảng cùng độ dài `n` với
`1 <= n <= 100000`, `arrival` tăng nghiêm ngặt và mọi phần tử của cả hai
mảng nằm trong `[1, 1000000000]`. Hàm giữ nguyên hai mảng, không lưu trạng
thái giữa các lần gọi và không kiểm tra dữ liệu ngoài hợp đồng.

## Thuật toán

Duy trì ba cấu trúc:

- `available`: `std::set<int>` chứa ID máy rảnh theo thứ tự tăng.
- `busy`: min-heap các cặp `(thời điểm hoàn tất, ID)`.
- `count`: số yêu cầu mỗi máy đã nhận.

Ban đầu mọi máy đều rảnh. Với mỗi yêu cầu `i`:

1. Lấy khỏi heap **tất cả** công việc có thời điểm hoàn tất không lớn hơn
   `arrival[i]`, đưa các máy tương ứng trở lại tập rảnh.
2. Nếu tập rảnh trống, bỏ yêu cầu này.
3. Dùng `lower_bound(i % k)` để tìm ID rảnh nhỏ nhất không dưới điểm bắt
   đầu. Nếu không có, chọn phần tử đầu tập để quay vòng.
4. Xóa máy đã chọn khỏi tập rảnh, tăng bộ đếm và đưa thời điểm
   `arrival[i] + load[i]` vào heap.

Thời điểm hoàn tất dùng `long long` và ép kiểu trước phép cộng.
Với ràng buộc hiện tại, tổng tối đa là `2 * 10^9`; kiểu rộng giúp phép
cộng thời gian rõ ràng, không phụ thuộc kiểu `int` của phép tính trung gian.

### Vì sao đúng?

Trước bước chọn máy, tập rảnh chứa đúng các máy có thể nhận việc: ban đầu
điều này đúng; vòng lặp giải phóng lấy hết và chỉ lấy các máy đã hoàn tất;
mỗi máy vừa nhận việc bị xóa khỏi tập và có đúng một sự kiện trong heap.
Do đó tập trống tương đương mọi máy đều bận, nên bỏ yêu cầu là đúng.

Khi tập không trống, `lower_bound` chọn máy đầu tiên trong đoạn từ
`i % k` đến `k-1`. Nếu đoạn đó không có máy rảnh, phần tử nhỏ nhất của
tập là máy đầu tiên gặp sau khi quay về 0. Đây chính là quy tắc phân công.
Mỗi lần nhận việc chỉ tăng đúng một bộ đếm, vì vậy cuối cùng các ID có
bộ đếm cực đại chính là toàn bộ máy bận rộn nhất.

### Độ phức tạp

Mỗi yêu cầu tạo tối đa một sự kiện và mỗi sự kiện bị lấy ra tối đa một
lần. Cả heap và tập rảnh đều chứa tối đa `k` phần tử. Khởi tạo tập tốn
`O(k log(k+1))`; xử lý yêu cầu tốn `O(n log(k+1))`; quét kết quả tốn `O(k)`.
Tổng thời gian **O((n+k) log(k+1))**, bộ nhớ phụ **O(k)**, kể cả kết quả.
Dùng `log(k+1)` để công thức bao gồm cả `k=1`.

## Ví dụ tự tạo

Với `k=3`, `arrival=[1,2,3,4,5]`, `load=[3,10,10,1,1]`:

| i | Thời điểm | Bắt đầu từ | Máy nhận | Hoàn tất |
| --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 4 |
| 1 | 2 | 1 | 1 | 12 |
| 2 | 3 | 2 | 2 | 13 |
| 3 | 4 | 0 | 0 | 5 |
| 4 | 5 | 1 | 0 (quay vòng) | 6 |

Số việc là `[3,1,1]`, đáp án `[0]`. Ví dụ này thể hiện cả việc tái sử dụng
máy đúng thời điểm hoàn tất và tìm máy sau khi quay vòng.

Với `k=2`, `arrival=[1,2,3,4,5]`, `load=[100,100,1,1,1]`, hai máy nhận
hai yêu cầu đầu; ba yêu cầu sau bị bỏ. Số việc là `[1,1]`, đáp án `[0,1]`.

Chương trình chạy được nếu đặt cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> arrival{1, 2, 3, 4, 5};
    std::vector<int> load{3, 10, 10, 1, 1};
    lab::Solution solution;
    for (int id : solution.busiestServers(3, arrival, load)) {
        std::cout << id << '\n'; // 0
    }
}
```

## Kiểm thử

Từ gốc repo:

```sh
make test
# Chạy riêng với NDEBUG:
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-1606-find-servers-that-handled-most-number-of-requests/test.cpp \
  -o /tmp/lesson-1606-test
/tmp/lesson-1606-test
```

Test được viết trước lời giải. Bản khung trả `{}` đã thất bại ở ca một
yêu cầu, kỳ vọng `[0]`, với mã thoát khác 0. Bộ test dùng kiểm tra tường
minh và `std::exit(EXIT_FAILURE)`, không phụ thuộc `assert` hay `NDEBUG`.

Các đáp án cố định được suy ra từ lịch phân công: một máy, máy chưa từng
nhận việc, quay vòng, bỏ yêu cầu, bỏ qua máy ưu tiên đang bận, nhiều máy
hoàn tất đồng thời, thời gian gần `10^9`, cùng các ca `n` hoặc `k` đạt
100.000. Khi 100.000 yêu cầu có tải 1 được chia cho 7 máy, mỗi máy nhận
14.285 việc, năm máy đầu nhận thêm một việc nên đáp án là `[0,1,2,3,4]`.
Test cũng kiểm tra đầu vào không đổi và tái sử dụng cùng đối tượng.

Ngoài ra có 3.000 ca nhỏ với hạt giống cố định. Oracle độc lập quét trực
tiếp tối đa `k` máy theo vòng tròn cho mỗi yêu cầu, lưu thời điểm rảnh
trong mảng, không dùng heap hay tập có thứ tự. So sánh này giúp bắt lỗi
chọn máy, giải phóng thiếu máy hoặc dùng số việc đã nhận thay cho chỉ số
yêu cầu. Oracle tốn `O(nk)` nên chỉ dùng với dữ liệu nhỏ.

## Tự luyện

1. Tạo một lịch mà dùng `< arrival[i]` thay vì `<= arrival[i]` làm đổi đáp án.
2. Tạo phản ví dụ cho cách chọn máy có thời điểm hoàn tất sớm nhất thay
   vì máy rảnh đầu tiên theo vòng ID.
3. Nếu cần trả thêm số yêu cầu bị bỏ và số việc từng máy, hãy mô tả cách
   bổ sung mà không đổi độ phức tạp.
