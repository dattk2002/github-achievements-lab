# LeetCode 3041 — Chọn nhiều phần tử liên tiếp nhất sau khi tăng giá trị

- Ngày Daily **2026-11-20**, độ khó **Hard**. [Đề gốc trên LeetCode](https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/)
- C++17, giao diện `lab::Solution::maxSelectedElements`.

## Hợp đồng và tiền điều kiện

Mỗi vị trí có thể giữ nguyên hoặc tăng thêm 1. Hãy chọn một số vị trí
sao cho các giá trị sau điều chỉnh, khi sắp tăng dần, chênh nhau đúng 1
ở mọi cặp kề nhau. Hàm trả về số vị trí lớn nhất có thể chọn.

Đầu vào hợp lệ có từ 1 đến 100.000 phần tử, mỗi giá trị từ 1 đến
1.000.000. Bản cài đặt sắp xếp một bản sao để giữ nguyên `nums`.

## Quy hoạch động theo giá trị cuối

Sắp xếp theo giá trị gốc. Gọi `dp[t]` là độ dài lớn nhất của dãy liên
tiếp kết thúc tại `t` từ các vị trí đã xét. Khóa chưa có mang giá trị 0.

Với mỗi giá trị gốc `x`, cập nhật theo thứ tự sau.

1. Tăng `x` thành `x+1`. Đặt `dp[x+1] = max(dp[x+1], dp[x]+1)`.
2. Giữ nguyên `x`. Đặt `dp[x] = max(dp[x], dp[x-1]+1)`.

Khi trạng thái đứng trước có độ dài 0, phép cộng 1 bắt đầu một dãy
mới. Lấy giá trị lớn nhất qua các lần cập nhật.

### Vì sao đúng?

Nếu hai vị trí có giá trị gốc `a > b`, giá trị cuối của vị trí mang
`a` ít nhất là `a`, còn giá trị cuối của vị trí mang `b` nhiều nhất
là `b+1 <= a`. Do đó thứ tự tăng nghiêm ngặt của các giá trị cuối
không thể đảo thứ tự các giá trị gốc khác nhau. Với các vị trí có
cùng giá trị gốc, ta có thể đổi vai trò của chúng để vị trí đi trước
trong bản sắp xếp nhận giá trị cuối nhỏ hơn.

Vì vậy, sau khi xét `x`, một dãy tối ưu hoặc bỏ qua vị trí mới, hoặc
dùng nó làm phần tử cuối. Nếu dùng nó để kết thúc ở `t`, dãy trước
đó phải kết thúc ở `t-1` hoặc rỗng. Hai công thức xét đủ các khả năng
này và giữ lại kết quả cũ qua phép `max`. Cập nhật `x+1` trước giúp
bước đó đọc `dp[x]` của lượt trước. Nếu cập nhật ngược, một vị trí có
thể bị dùng cả ở `x` lẫn ở `x+1`.

## Độ phức tạp

Với `n` phần tử, sắp xếp tốn `O(n log n)`. Mỗi lượt truy cập một số
cố định khóa trong `std::map`, có tối đa `3n` khóa. Tổng thời gian là
`O(n log n)`, bộ nhớ phụ là `O(n)` cho bảng trạng thái và bản sao.

## Ví dụ và cách chạy

- `[9, 5, 7, 7]` → `4`. Tăng `5` thành `6` và một số `7`
  thành `8` để chọn đủ `[6, 7, 8, 9]`.
- `[6, 6, 6, 6]` → `2`. Hai giá trị cuối có thể xuất hiện là `6`
  và `7`, mỗi giá trị được chọn một lần.
- `[1000000, 999999, 1000000]` → `3`. Tăng một số `1000000`
  thành `1000001` để nối dài dãy.

Chạy từ thư mục gốc của kho mã nguồn.

```bash
g++ -std=c++17 -DNDEBUG -Wall -Wextra -Werror -pedantic \
  lessons/leetcode-3041-maximize-consecutive-elements-in-an-array-after-modification/test.cpp \
  -o /tmp/leetcode-3041-test
/tmp/leetcode-3041-test
```

Bộ kiểm thử bao gồm mảng một phần tử, giá trị trùng, khoảng trống,
giới hạn giá trị và giới hạn số phần tử. Với mọi mảng độ dài 1 đến 5
lấy giá trị từ 1 đến 4, bộ đối chiếu thử mọi cách tăng, loại giá trị
trùng rồi đo đoạn liên tiếp dài nhất. Cách này tính kết quả kỳ vọng
trực tiếp từ các mảng đã điều chỉnh. Khi sai, chương trình trả mã 1.

## Bài tập

1. Tính tay các trạng thái cho `[4, 4, 6]` và chỉ ra cách chọn tối ưu.
2. Dùng đầu vào `[2]` để giải thích kết quả sai khi đảo hai phép cập nhật.
3. Thay `std::map` bằng bảng chỉ số trực tiếp. Phân tích thời gian và
   bộ nhớ theo cả số phần tử lẫn giá trị lớn nhất.
