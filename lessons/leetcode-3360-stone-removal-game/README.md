# LeetCode 3360 — Trò chơi lấy đá

- Đề gốc [Stone Removal Game](https://leetcode.com/problems/stone-removal-game/)
- Ngày nguồn (`source_date`) **2026-11-26**
- Độ khó **Easy**

## Hợp đồng và tiền điều kiện

`lab::Solution::canAliceWin(int n)` nhận số đá ban đầu với `1 <= n <= 50`
và trả về `true` nếu Alice thắng, `false` nếu Bob thắng. Alice đi trước.
Hai người luân phiên lấy đá theo thứ tự 10, 9, 8, …, mỗi lượt phải lấy đủ
số đá quy định. Người đến lượt mà thiếu đá để thực hiện lượt đó sẽ thua.

## Thuật toán và tính đúng đắn

Mô phỏng các lượt bắt buộc, bắt đầu với `take = 10`. Khi còn ít nhất
`take` viên, trừ số đó khỏi `n`, tăng bộ đếm lượt đã hoàn thành và giảm
`take` một đơn vị.

Trước mỗi lần kiểm tra điều kiện vòng lặp, `n` là số đá còn lại và
`take` là số đá cần cho lượt tiếp theo. Mỗi vòng thực hiện đúng một lượt
hợp lệ nên hai giá trị này tiếp tục đúng sau khi cập nhật. Tám lượt đầu
cần tổng cộng 52 viên, vì vậy trong phạm vi đề bài, vòng lặp luôn dừng
vì thiếu đá. Nếu số lượt đã hoàn thành là lẻ thì tới lượt Bob và Alice
thắng. Nếu số lượt là chẵn, kể cả 0, thì tới lượt Alice và Alice thua.

Vòng lặp thực hiện tối đa 7 lượt với đầu vào hợp lệ. Thời gian và bộ nhớ
phụ đều là **O(1)**.

## Ví dụ tự tạo

- `n = 18` → `true`. Alice lấy 10 viên, Bob còn 8 viên và cần 9 viên.
- `n = 19` → `false`. Alice lấy 10 viên, Bob lấy vừa đủ 9 viên, rồi
  Alice cần 8 viên khi đống đá đã hết.
- `n = 27` → `true`. Sau ba lượt lấy 10, 9 và 8 viên, Bob đến lượt
  với đống đá rỗng.

## Chạy và hiểu kiểm thử

Từ thư mục gốc repo, chạy `make test` hoặc chạy riêng bài này.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-3360-stone-removal-game/test.cpp -o /tmp/lesson-3360-test
/tmp/lesson-3360-test
```

Bộ kiểm thử tính tay tổng đá cần sau từng lượt, được các mốc 10, 19, 27,
34, 40, 45, 49 và 52. Chẳng hạn, từ 27 đến 33 viên đủ cho đúng ba lượt
vì lượt thứ tư đòi tổng cộng 34 viên. Từ các mốc này, bộ kiểm thử dùng
bốn khoảng thắng cố định để đối chiếu cả 50 đầu vào. Phạm vi đó bao gồm
hai đầu miền và cả hai phía của mỗi mốc đổi người thắng. Mỗi sai lệch
được in cùng giá trị đầu vào, và dù bật `NDEBUG`, chương trình vẫn trả
mã thoát khác 0 nếu có sai lệch.

## Tự luyện

1. Liệt kê từng lượt với `n = 44` và `n = 45`. Vì sao thêm một viên
   lại làm Alice thua?
2. Viết công thức cho tổng số đá cần để hoàn thành `k` lượt đầu tiên.
3. Thử giải bài bằng cách tra các mốc tổng đá và dùng bộ kiểm thử hiện
   có để đối chiếu kết quả.
