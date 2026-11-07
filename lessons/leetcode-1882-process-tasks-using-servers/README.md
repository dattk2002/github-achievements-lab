# LeetCode 1882 — Phân công tác vụ cho máy chủ

Nguồn: [Process Tasks Using Servers](https://leetcode.com/problems/process-tasks-using-servers/).
Ngày nguồn (`source_date`): **2026-11-07**. Độ khó: **Medium**.
Tóm tắt, ví dụ, thuật toán và kiểm thử dưới đây được tự viết bằng C++17.

## Hợp đồng và tiền điều kiện

```cpp
std::vector<int> lab::Solution::assignTasks(
    std::vector<int>& servers, std::vector<int>& tasks);
```

Máy `i` có trọng số `servers[i]`. Tác vụ `j` đến tại giây `j`, cần
`tasks[j]` giây xử lý. Các tác vụ chờ được phục vụ theo thứ tự đến (FIFO).
Khi có việc chờ, chọn máy rảnh có trọng số nhỏ nhất; nếu hòa, chọn chỉ số
nhỏ nhất. Tác vụ bắt đầu lúc `t` giải phóng máy ngay tại `t + tasks[j]`.
Mọi máy kết thúc cùng lúc đều được xem là rảnh trước khi chọn máy tiếp theo.
Hàm trả chỉ số máy cho từng tác vụ theo thứ tự ban đầu và giữ nguyên hai
mảng đầu vào; chữ ký tham chiếu tương thích giao diện gốc.

Đầu vào hợp lệ thỏa `1 <= servers.size(), tasks.size() <= 200000` và
`1 <= servers[i], tasks[j] <= 200000`. Ban đầu mọi máy đều rảnh.
Không hỗ trợ hay kiểm tra dữ liệu ngoài hợp đồng, chẳng hạn mảng rỗng.

## Thuật toán: hai hàng đợi ưu tiên

Một heap không đủ để biểu diễn đồng thời ưu tiên chọn máy và thời điểm
máy được giải phóng. Dùng hai min-heap, với thứ tự từ điển:

- `free`: cặp `(trọng số, chỉ số)` của các máy rảnh.
- `busy`: bộ ba `(thời điểm kết thúc, trọng số, chỉ số)` của các máy bận.

Ban đầu đưa mọi máy vào `free`, đặt đồng hồ `time = 0`. Với mỗi tác vụ `j`:

1. Đặt `time = max(time, j)` để không xử lý trước thời điểm đến.
2. Nếu `free` rỗng, nâng `time` tới ít nhất thời điểm kết thúc nhỏ nhất
   trong `busy`. Không cần đếm từng giây chờ.
3. Chuyển **tất cả** máy có thời điểm kết thúc `<= time` từ `busy` sang
   `free`, kể cả máy kết thúc đúng lúc tác vụ đến.
4. Lấy đầu `free` làm đáp án; đưa máy đó vào `busy` với thời điểm kết thúc
   mới là `time + tasks[j]`.

Không cần lưu hàng đợi tác vụ riêng: vòng lặp duyệt `j` tăng dần chính là
FIFO. Khi có việc tồn đọng, `time` có thể lớn hơn nhiều so với `j` và phải
được giữ nguyên cho tác vụ tiếp theo, trừ khi cần chờ máy.

Nếu `free` rỗng thì `busy` chắc chắn không rỗng vì có ít nhất một máy.
Bước 2 trước bước 3 vẫn đúng khi một máy đã kết thúc: phép `max` không
đẩy đồng hồ lùi lại, và bước 3 thu hồi máy đó ngay.

### Vì sao đúng?

Quy nạp theo số tác vụ đã phân công. Mỗi máy xuất hiện trong đúng một heap;
`busy` lưu đúng thời điểm kết thúc của lần phân công gần nhất. Trước bước
chọn máy, bước 3 đảm bảo `free` chứa chính xác mọi máy rảnh tại `time`.

Tác vụ `j` chỉ được xét sau mọi tác vụ trước nó. Nếu có máy rảnh khi tác vụ
đã đến và các tác vụ trước đã được phân công, nó được phục vụ ngay. Nếu
không có máy rảnh, không thể bắt đầu sớm hơn lần kết thúc gần nhất;
nhảy đến thời điểm đó vì vậy chọn đúng thời điểm bắt đầu sớm nhất.
Thu hồi toàn bộ các máy đã kết thúc rồi lấy cặp nhỏ nhất trong `free`
đảm bảo đúng cả ưu tiên trọng số và chỉ số. Cập nhật thời điểm kết thúc
giữ bất biến cho vòng sau; do đó mọi phần tử đáp án đều đúng.

### Độ phức tạp và kiểu thời gian

Đặt `n` là số máy, `m` là số tác vụ. Khởi tạo heap bằng từng lần chèn tốn
`O(n log(n+1))`. Mỗi tác vụ lấy một máy, thêm một sự kiện; tổng số sự kiện
được thu hồi không quá `m`. Tổng thời gian **O((n+m) log(n+1))**.
Hai heap có tổng cộng `n` máy, nên bộ nhớ phụ **O(n)**; tính cả đáp án
là **O(n+m)**.

Thời điểm kết thúc có thể đạt `200000 * 200000 = 40000000000`, vượt `int`
32 bit. Đồng hồ và khóa thời gian trong `busy` dùng `long long` ngay từ
phép cộng. Trọng số, chỉ số và thời lượng đầu vào vẫn dùng `int`.

## Ví dụ tự tạo

Với `servers = {5,1}`, `tasks = {4,3,1,1,1}`:

| Tác vụ | Đến lúc | Bắt đầu | Máy | Kết thúc |
| --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 4 |
| 1 | 1 | 1 | 0 | 4 |
| 2 | 2 | 4 | 1 | 5 |
| 3 | 3 | 4 | 0 | 5 |
| 4 | 4 | 5 | 1 | 6 |

Tại giây 4, cả hai máy cùng rảnh. Tác vụ 2 đang đứng đầu hàng chờ nên lấy
máy 1 nhẹ hơn; tác vụ 3 lấy máy 0 ngay cùng giây đó. Đáp án là
`{1,0,1,0,1}`. Chỉ lấy một máy kết thúc đầu tiên mà chưa thu hồi cả nhóm
có thể phá vỡ ưu tiên trọng số.

Ví dụ chạy độc lập từ thư mục gốc repo (chỉ tạo chương trình trong `/tmp`):

```sh
cat > /tmp/example-1882.cpp <<'CPP'
#include "lessons/leetcode-1882-process-tasks-using-servers/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> servers{5,1}, tasks{4,3,1,1,1};
    lab::Solution solution;
    for (int server : solution.assignTasks(servers, tasks))
        std::cout << server << ' '; // 1 0 1 0 1
    std::cout << '\n';
}
CPP
g++ -std=c++17 -I. /tmp/example-1882.cpp -o /tmp/example-1882
/tmp/example-1882
```

## Kiểm thử

```sh
make test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-1882-process-tasks-using-servers/test.cpp \
  -o /tmp/lesson-1882-test
/tmp/lesson-1882-test
```

Test được viết trước thuật toán. Bản tạm trả vector rỗng đã thất bại
ở ca nhỏ nhất với mã thoát 1 khi bật `NDEBUG`. Bộ kiểm tra dùng điều kiện
và `std::exit(EXIT_FAILURE)`, không dựa vào `assert`; đồng thời kiểm tra
hai đầu vào không đổi.

Các đáp án tính tay bắt lỗi ưu tiên sai giữa trọng số/chỉ số, máy rảnh chờ
lần đến tiếp theo, giải phóng đúng giây đến, hàng chờ tồn đọng và nhiều máy
kết thúc đồng thời. Trường hợp một máy bao phủ kích thước nhỏ nhất và
thời lượng lớn nhất.

Có 2000 ca nhỏ ngẫu nhiên với seed 1882. Oracle độc lập tiến từng giây,
quét mọi máy để chọn máy rảnh tốt nhất và xử lý hết việc có thể trong giây
đó; không dùng heap hoặc nhảy sự kiện như lời giải.

Các ca biên lớn có 200000 tác vụ dài 200000 giây: hai máy cùng trọng số
phải luân phiên `0,1,0,1,...` do máy 0 bắt đầu trước máy 1 một giây;
một máy luôn trả 0 và tích lũy tới 40 tỷ giây. Ca 200000 máy và 200000 tác
vụ dài một giây có duy nhất máy cuối nhẹ nhất: máy này được tái sử dụng
đúng mỗi giây, nên mọi đáp án là 199999. Các ca này kiểm tra tràn số và
khả năng xử lý giới hạn kích thước mà không mô phỏng từng giây.

## Bài tập tự luyện

1. Tạo ca mà chọn máy kết thúc sớm nhất mà bỏ qua các máy rảnh khác cho
   kết quả sai. Vì sao hai thứ tự ưu tiên cần tách riêng?
2. Dùng bảng ví dụ để chỉ ra lỗi khi chỉ thu hồi một máy kết thúc cùng lúc.
3. Sửa thuật toán để trả thêm thời điểm bắt đầu của mỗi tác vụ. Kiểu dữ
   liệu nào cần dùng và vì sao?
4. Nếu thời điểm đến tùy ý nhưng đã tăng dần, cần thay đổi bước nào?
   Nếu không tăng dần, cần giữ lại thông tin gì để khôi phục thứ tự đáp án?
