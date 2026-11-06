# LeetCode 2747 — Đếm máy chủ không nhận yêu cầu

Nguồn: [Count Zero Request Servers](https://leetcode.com/problems/count-zero-request-servers/).
Ngày nguồn (`source_date`): **2026-11-06**. Độ khó: **Medium**.
Bài học C++17 với tóm tắt, ví dụ, lời giải và kiểm thử tự viết.

## Hợp đồng và tiền điều kiện

`lab::Solution::countServers(n, logs, x, queries)` trả về một `std::vector<int>`
theo đúng thứ tự truy vấn. Với thời điểm `q`, đếm các máy chủ không có log
nào trong đoạn **đóng** `[q-x, q]`. Mỗi log có dạng `{mã máy chủ, thời điểm}`;
nhiều yêu cầu của cùng máy chủ vẫn chỉ làm máy đó được tính hoạt động một lần.
Hàm giữ nguyên cả `logs` và `queries`, dù chữ ký nhận tham chiếu không const
để tương thích giao diện gốc.

Dữ liệu hợp lệ phải thỏa:

- `1 <= n <= 100000`; mã máy chủ thuộc `[1, n]`.
- Số log và số truy vấn đều từ 1 đến 100000; mỗi log có đúng hai số nguyên.
- Thời điểm log thuộc `[1, 1000000]`.
- `1 <= x <= 100000` và `x < queries[i] <= 1000000`.

Không yêu cầu đầu vào có thứ tự; log và truy vấn có thể lặp.
Không kiểm tra hoặc hỗ trợ dữ liệu ngoài hợp đồng. Các bộ đếm và phép trừ
thời gian đều nằm trong miền `int` 32 bit theo các giới hạn trên.

## Thuật toán: xử lý ngoại tuyến và cửa sổ trượt

Quét toàn bộ log cho từng truy vấn tốn `O(LQ)`, quá lớn khi cả hai đạt 100000.
Thay vào đó:

1. Sao chép và sắp xếp log theo thời điểm. Sắp xếp các chỉ số truy vấn theo
   giá trị thời gian; giữ chỉ số để ghi đáp án về vị trí gốc.
2. Duy trì hai con trỏ `left`, `right` và số log hiện có của mỗi máy chủ
   trong đoạn chỉ số nửa mở `[left, right)`.
3. Với truy vấn `q`, thêm mọi log chưa xét có thời điểm `<= q`. Khi bộ đếm
   của một máy chuyển từ 0 lên 1, tăng số máy hoạt động `active`.
4. Loại mọi log trong cửa sổ có thời điểm **nhỏ hơn** `q-x`. Khi bộ đếm
   chuyển từ 1 về 0, giảm `active`. Không loại log đúng tại `q-x`.
5. Ghi `n-active` vào vị trí ban đầu của truy vấn.

Thêm trước rồi loại giúp cả bước nhảy lớn giữa hai truy vấn hoạt động đúng:
những log mới thêm nhưng đã quá cũ cũng được loại ngay. Truy vấn trùng nhau
không làm thay đổi cửa sổ. Không thể chỉ dùng cờ boolean cho từng máy:
loại một log không có nghĩa máy hết hoạt động nếu còn log khác trong đoạn.

### Vì sao đúng?

Các truy vấn được xét tăng dần, nên cả hai biên thời gian đều không lùi.
Sau bước thêm, `right` nằm ngay sau mọi log có thời điểm `<= q`.
Sau bước loại, `left` bỏ qua chính xác các log có thời điểm `< q-x`.
Vì log đã được sắp xếp, `[left, right)` chứa đúng các log trong đoạn cần hỏi.

Mỗi lần thêm hoặc loại cập nhật đúng một bộ đếm. Bởi vậy `frequency[s]`
luôn bằng số log còn lại của máy `s`, và `active` đếm chính xác số bộ đếm
khác 0. Có `n` máy tất cả, nên `n-active` là đáp án. Ghi theo chỉ số gốc
khôi phục đúng thứ tự người gọi yêu cầu.

### Độ phức tạp

Đặt `L = logs.size()`, `Q = queries.size()`. Sắp xếp tốn
`O(L log L + Q log Q)`; mỗi log được thêm và loại nhiều nhất một lần,
quét truy vấn tốn `O(Q)`, khởi tạo bộ đếm tốn `O(n)`.
Tổng thời gian **O(L log L + Q log Q + L + Q + n)**,
bộ nhớ phụ **O(L + Q + n)**, gồm bản sao log, chỉ số truy vấn,
bộ đếm và đáp án.

## Ví dụ tự tạo và cách chạy

Có 5 máy, log `{{4,11}, {2,10}, {1,6}, {3,5}}`, `x=4`:

| Truy vấn | Đoạn xét | Máy có yêu cầu | Số máy im lặng |
| --- | --- | --- | --- |
| 11 | [7,11] | 2, 4 | 3 |
| 10 | [6,10] | 1, 2 | 3 |
| 20 | [16,20] | không có | 5 |

Chương trình sau có thể lưu cạnh `lesson.hpp`, biên dịch bằng
`g++ -std=c++17 example.cpp -o /tmp/example-2747` rồi chạy `/tmp/example-2747`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> logs{{4,11}, {2,10}, {1,6}, {3,5}};
    std::vector<int> queries{11,10,20};
    lab::Solution solution;
    for (int value : solution.countServers(5, logs, 4, queries))
        std::cout << value << ' '; // 3 3 5
    std::cout << '\n';
}
```

Từ thư mục gốc repo:

```sh
make test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-2747-count-zero-request-servers/test.cpp \
  -o /tmp/lesson-2747-test
/tmp/lesson-2747-test
```

## Thiết kế kiểm thử

Test được viết trước; phiên bản tạm trả vector rỗng đã thất bại với mã 1
ở ca đầu, trước khi triển khai thuật toán. Kiểm tra dùng nhánh điều kiện
và `std::exit(EXIT_FAILURE)`, nên vẫn có hiệu lực khi định nghĩa `NDEBUG`.
Mỗi ca còn xác nhận hai mảng đầu vào không bị thay đổi.

Các đáp án cố định tính tay bao phủ hai đầu đoạn đóng, log ngay ngoài đoạn,
truy vấn đảo thứ tự và lặp, log trùng, một máy có nhiều log, một máy duy nhất,
tất cả máy hoạt động, cửa sổ không có yêu cầu, bước nhảy thời gian lớn,
`x=1`, `x=100000` và thời điểm 1000000. Chẳng hạn với log
`{{1,2},{1,3},{1,3},{2,4}}`, `x=2`, truy vấn 5 giữ máy 1 và 2 hoạt động;
truy vấn 6 chỉ giữ máy 2, nên trong tổng 3 máy đáp án lần lượt là 1 và 2.

Có thêm 2000 ca ngẫu nhiên với seed cố định. Oracle độc lập quét toàn bộ
log cho từng truy vấn, đánh dấu máy đã xuất hiện rồi đếm máy chưa đánh dấu;
không dùng sắp xếp hay hai con trỏ. Ca lớn có 100000 máy, 100000 log và
100000 truy vấn: đúng 50000 máy có hai yêu cầu ở hai biên đoạn
`[900000,1000000]`, nên mọi đáp án là 50000. Ca này cũng kiểm tra việc
đếm máy thay vì đếm log và khả năng xử lý kích thước tối đa.

## Bài tập tự luyện

1. Tạo phản ví dụ cho việc loại log bằng `time <= q-x` thay vì `<`.
2. Dùng ví dụ một máy có ba log để giải thích vì sao cờ boolean không đủ.
3. Nếu được phép sửa thứ tự `logs`, có thể tiết kiệm phần bộ nhớ nào?
4. Nếu truy vấn đến trực tuyến với thứ tự tùy ý, vì sao hai con trỏ hiện tại
   không còn dùng được? Đề xuất cách trả lời đúng trước khi tối ưu.
