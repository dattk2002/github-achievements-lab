# LeetCode 621 — Task Scheduler: tần suất và khung thời gian

Nguồn: [Task Scheduler](https://leetcode.com/problems/task-scheduler/), Medium.
Bài bổ sung ngày **2026-11-18**; không tự nộp lên LeetCode. Ví dụ, lời giải
và diễn giải được tự viết.

## Hợp đồng

`lab::Solution::leastInterval(std::vector<char>& tasks, int n)` trả số
khoảng thời gian nhỏ nhất để chạy hết các tác vụ. Một khoảng chạy một tác
vụ hoặc nghỉ. Có thể đổi thứ tự tùy ý. Giữa hai lần chạy cùng nhãn phải
có ít nhất `n` khoảng khác: chênh lệch thời điểm chạy ít nhất `n+1`.

Miền nguồn: 1–10000 tác vụ, nhãn `A`–`Z`, `0 <= n <= 100`. Giới hạn số
lượng là tiền điều kiện. Hàm ném `std::invalid_argument` cho nhãn hay
cooldown không hợp lệ; không sửa đầu vào. Mở rộng: danh sách rỗng trả `0`
với cooldown hợp lệ. Kết quả và biểu thức trung gian nằm trong `int`;
trường hợp 10000 tác vụ cùng nhãn, `n=100`, cần `1009900` khoảng.

## Công thức và giải thích tính tối ưu

Gọi `N` là số tác vụ, `f` là tần suất lớn nhất, `k` là số nhãn đạt `f`.
Nếu có tác vụ, đáp án là:

`max(N, (f-1)*(n+1) + k)`.

Có hai cận dưới. Phải chạy đủ `N` tác vụ nên cần ít nhất `N` khoảng.
Với mỗi nhãn có tần suất `f`, lần cuối không thể sớm hơn thời điểm
`(f-1)*(n+1)` nếu đánh số thời điểm từ 0. Có `k` lần cuối của các nhãn
này, chiếm các khoảng khác nhau, nên phải kéo dài thêm ít nhất `k` khoảng.

Để chứng minh đạt được cận, dùng một cách dựng lịch phụ (hàm không cần
thực hiện cách dựng này). Đặt `L=n+1`. Mỗi lượt sắp nhãn còn lại theo
tần suất giảm dần, hòa thì theo thứ tự chữ cái cố định. Chạy tối đa `L`
nhãn đầu, mỗi nhãn một lần, rồi giảm tần suất. Nếu còn tác vụ, điền nghỉ
cho lượt đủ `L` khoảng; lượt cuối kết thúc ngay khi hết tác vụ.

Lịch này hợp lệ: nếu một nhãn xuất hiện ở hai lượt liên tiếp, vị trí
trong lượt sau không thể sớm hơn lượt trước. Mọi nhãn đứng trước nó ở
lượt trước đều được giảm một lần như nó, vẫn còn nếu nó còn, và vẫn
đứng trước theo cùng quy tắc so sánh. Nhãn mới có thể đẩy nó về sau.
Vì vậy hai lần chạy cách nhau ít nhất `L`. Nếu bỏ qua ít nhất một lượt,
khoảng cách tối thiểu còn lớn hơn hoặc bằng `L+1`.

Kiểm tra độ dài bằng quy nạp trên số tác vụ còn lại. Gọi cận trên trạng
thái hiện tại là `F=max(N,(f-1)*L+k)`, và `q` là số nhãn còn tác vụ.
Nếu chạy xong ngay trong một lượt thì mọi nhãn có một bản sao và
`q<=L`, do đó `F=q`. Nếu còn tác vụ, lượt tốn đúng `L`:

- Khi `q<L`, mọi nhãn được giảm một lần. Cận khung chi phối tổng số
  tác vụ cả trước và sau lượt, vì `N <= (f-1)*q+k`. Tần suất cực đại
  giảm một, số nhãn cực đại vẫn là `k`, nên `F` giảm đúng `L`.
- Khi `q>=L`, tổng số tác vụ giảm đúng `L`. Nếu `k>L`, còn nhãn cực
  đại chưa chạy: `f` giữ nguyên, `k` giảm `L`, nên cận khung cũng giảm `L`.
  Nếu `k<=L`, `f` giảm một. Không có nhãn mới hòa cực đại thì cận khung
  giảm `L`. Nếu có nhãn mới hòa, đặt `t` là số nhãn ban đầu có `f-1`
  bản sao và `s=L-k`; trường hợp này có `t>s`. Sau lượt số nhãn cực đại
  là `k'=k+t-s`. Trước lượt `N >= k*f+t*(f-1)`, sau lượt
  `N' >= k'*(f-1)+s*(f-2)`. Hai bất đẳng thức lần lượt cho
  `N >= (f-1)*L+k` và `N' >= (f-2)*L+k'`. Vì vậy tổng số tác vụ chi
  phối cả hai trạng thái, và `F` vẫn giảm đúng `L`.

Theo quy nạp, cách dựng có độ dài đúng `F`, bằng cận dưới đã chứng minh.
Hàm chỉ cần công thức để trả độ dài, không cần mô phỏng từng nhịp.

Đếm vào mảng 26 phần tử, tìm `f` và `k`. Thời gian **O(N+26)**, bộ nhớ
phụ **O(26) = O(1)**. Rỗng được xử lý trước để không đếm 26 tần suất 0.

## Ví dụ chạy được

Với `AAAABBC`, `n=2`: `f=4`, `k=1`, khung dài `10`, lớn hơn `N=7`.
Một lịch đạt cận: `A B C A B _ A _ _ A`, trong đó `_` là nghỉ.
Chạy từ thư mục bài học:

```sh
cat > /tmp/lc621-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<char> tasks{'A','A','A','A','B','B','C'};
    std::cout << lab::Solution{}.leastInterval(tasks,2) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc621-example.cpp -o /tmp/lc621-example
/tmp/lc621-example
```

Kết quả:

```text
10
```

## Kiểm thử và trường hợp biên

Oracle độc lập duyệt mọi hoán vị phân biệt của tập tác vụ nhỏ. Với mỗi
thứ tự, chạy sớm nhất có thể bằng cách theo dõi thời điểm nhãn được phép
chạy lại. Với thứ tự cố định, trì hoãn một tác vụ không thể giúp kết
thúc sớm hơn; duyệt mọi thứ tự vì thế cho tối ưu toàn cục, không dùng
công thức tần suất. Đối chiếu 108 tổ hợp: ba nhãn có 0–2 bản sao và
cooldown 0–3.

Test còn có rỗng, `n=0`, một nhãn lặp, nhiều nhãn cùng cực đại, 26 nhãn,
10000 tác vụ và cooldown 100; kiểm tra lỗi nhãn/cooldown và giữ nguyên
đầu vào. Với 26 nhãn cùng lặp 300 lần, cooldown 25 vừa đủ để không nghỉ,
còn cooldown 26 cần thêm khoảng nghỉ.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc621-test
/tmp/lc621-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc621-ndebug
/tmp/lc621-ndebug
```

Từ gốc repo: `make test` hoặc `make test-all`. Test thất bại trả mã khác 0
kể cả khi bật `NDEBUG`.

## Bài tập tự luyện

1. Tìm ca cho thấy bỏ `k` và chỉ cộng `1` làm công thức sai.
2. Viết bộ dựng lịch bằng heap và hàng đợi cooldown, rồi đối chiếu độ dài.
3. Nếu mỗi nhãn có cooldown riêng, vì sao công thức hiện tại không còn đủ?
