# Python — Đổi tiền với ít đồng nhất

Nguồn: [LeetCode 322 — Coin Change](https://leetcode.com/problems/coin-change/).
Đây là bài bổ sung ngày 30/10/2026, không phải Daily. Mã, ví dụ, giải
thích và kiểm thử được tự viết; không chép toàn bộ đề hoặc editorial.

## Hợp đồng

`coin_change(coins, amount)` trả số đồng ít nhất để tạo đúng tổng
`amount`, được dùng mỗi mệnh giá không giới hạn lần. Không tạo được thì
trả -1; tổng 0 cần 0 đồng. `coins` phải chứa số nguyên dương, `amount`
là số nguyên không âm, tối đa 10.000 theo bài gốc. Hàm không sửa danh
sách đầu vào. Bản học tập chấp nhận thêm danh sách mệnh giá rỗng và các
mệnh giá trùng nhau. Đầu vào sai hợp đồng không được kiểm tra.

Ví dụ tự tạo: `[1, 3, 4]`, tổng 6 cần 2 đồng (3 + 3), trong khi chọn
tham lam đồng lớn nhất trước sẽ dùng 4 + 1 + 1, thành 3 đồng.

## Quy hoạch động và tính đúng

Đặt `dp[v]` là số đồng ít nhất cho tổng v. Khởi tạo `dp[0] = 0`; các
tổng khác chưa đạt được dùng lính canh `amount + 1`. Nếu có một cách
tạo v, lấy đồng cuối cùng c ra sẽ còn một cách tạo v - c. Thử mọi c
không lớn hơn v, lấy `min(dp[v - c] + 1)` sẽ tìm được cách tốt nhất.
Vì c dương, v - c luôn nhỏ hơn v: duyệt tổng tăng dần bảo đảm bài toán
con đã giải xong. Đây là bài đổi tiền không giới hạn, không phải bài chỉ
được dùng mỗi đồng một lần.

Loại mệnh giá lớn hơn tổng cần đổi và gộp các mệnh giá trùng để tránh
làm việc thừa; sắp xếp giúp dừng vòng trong sớm. Với m mệnh giá đầu vào,
k mệnh giá hữu ích khác nhau và A là tổng: thời gian **O(m + k log k + A×(k+1))**,
bộ nhớ phụ **O(A + k)**. Không đệ quy nên không phụ thuộc độ sâu stack.
Số hạng A vẫn có kể cả khi k bằng 0, vì cần tạo bảng và duyệt các tổng.

## Chạy và kiểm thử

Từ gốc repo, với Python 3.9+ và Make:

```sh
make test-python
```

Ví dụ dùng trong tệp đặt cạnh `solution.py`:

```python
from solution import coin_change
print(coin_change([1, 3, 4], 6))  # 2
```

5 test gồm phản ví dụ cho tham lam, dùng lại đồng, không đạt được tổng,
mệnh giá cực lớn, tổng 0, mệnh giá rỗng/trùng, giữ nguyên đầu vào,
tổng 10.000 và 500 bộ nhỏ ngẫu nhiên so với oracle BFS trên các tổng
có thể tới được. BFS tìm đường ít bước nhất, độc lập với bảng DP.

## Tự luyện

1. Trả thêm một danh sách đồng đạt đáp án tối ưu.
2. Đổi câu hỏi sang đếm số cách đổi tiền; thứ tự vòng lặp ảnh hưởng gì?
3. Nếu mệnh giá có thể bằng 0 hoặc âm, chứng minh trên hỏng ở đâu?
