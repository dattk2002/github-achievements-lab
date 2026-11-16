# LeetCode 2243: Calculate Digit Sum of a String — C++17

Nguồn: [Calculate Digit Sum of a String](https://leetcode.com/problems/calculate-digit-sum-of-a-string/).
Ngày nguồn (`source_date`): 2026-11-16. Độ khó: Easy.

## Hợp đồng

`lab::Solution::digitSum(std::string s, int k)` trả về chuỗi sau khi liên tục
thay mỗi nhóm liên tiếp tối đa k chữ số bằng biểu diễn thập phân của tổng
các chữ số trong nhóm. Chỉ thực hiện vòng mới khi độ dài hiện tại lớn hơn k.
Nhóm cuối có thể ngắn hơn k; kết quả các nhóm được nối theo thứ tự ban đầu.

Tiền điều kiện: `1 <= s.size() <= 100`, `2 <= k <= 100`, và s chỉ chứa
các ký tự `'0'` đến `'9'`. Không kiểm tra dữ liệu ngoài miền này.
Hàm nhận chuỗi theo giá trị nên không sửa chuỗi của bên gọi.

## Thuật toán và tính đúng

Trong mỗi vòng, tạo chuỗi `next` rỗng. Duyệt các vị trí đầu nhóm cách nhau k,
cộng `s[i] - '0'` trong phạm vi nhóm rồi nối `std::to_string(sum)` vào `next`.
Cuối vòng mới thay s bằng next. Không cập nhật s giữa vòng vì mọi nhóm phải
được xác định trên cùng chuỗi đầu vòng.

Sau khi xử lý j nhóm, next chính xác là phép nối biểu diễn tổng của j nhóm
đầu tiên: ban đầu đúng với chuỗi rỗng; mỗi bước nối đúng tổng nhóm kế tiếp.
Do đó toàn bộ vòng đúng. Quy nạp theo số vòng cho thấy s luôn là trạng thái
được yêu cầu. Khi vòng lặp dừng, độ dài không vượt k nên trả s là đúng.

Không được rút một tổng nhiều chữ số thành một chữ số ngay: tổng 24 phải
đóng góp chuỗi `"24"`. Tổng bằng 0 đóng góp `"0"`, không phải chuỗi rỗng.

### Kết thúc và độ phức tạp

Gọi n là độ dài ban đầu, R là số vòng thực hiện. Mỗi nhóm m chữ số có tổng
không quá 9m; biểu diễn tổng có không quá m chữ số. Vì vậy độ dài không tăng.
Đặc biệt k=2 có thể giữ nguyên độ dài trong một vòng, nên không thể lập luận
rằng mỗi vòng luôn giảm độ dài hay giảm ít nhất một nửa.

Xét thế năng `độ dài + tổng các chữ số`. Nếu có nhóm tổng ít nhất 10,
tổng chữ số của biểu diễn tổng nhỏ hơn tổng đó ít nhất 9, nên thế năng giảm.
Nếu không có nhóm như vậy, mỗi nhóm cho đúng một chữ số và độ dài giảm
(vì đang có độ dài > k và k >= 2). Thế năng nguyên không âm, ban đầu không
quá 10n, nên thuật toán kết thúc với R = O(n).

Mỗi vòng tốn O(độ dài hiện tại), kể cả chuyển tổng và nối chuỗi; do đó
thời gian O(nR), với cận trên bảo thủ O(n²). Khi không cần vòng nào, bản sao
đầu vào vẫn tốn O(n). Bộ nhớ phụ O(n) cho chuỗi đang xây dựng và bản sao s.
Tổng mỗi nhóm không quá 900 nên kiểu int đủ dùng.

## Ví dụ tự xây dựng

- `s="12345", k=3`: chia `123 | 45`, thu được `6 | 9`, trả `"69"`.
- `s="9876", k=3`: chia `987 | 6`, thu được `24 | 6`, trả `"246"`.
- `s="99999", k=2`: `99999 → 18189 → 999 → 189 → 99`.
- `s="0001", k=2`: kết quả `"01"`; không chuyển cả chuỗi sang số nguyên.
- `s="123456", k=3`: kết quả `"615"`, dừng ngay khi độ dài bằng k.

Lưu thành `/tmp/lc2243-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
int main() {
    std::cout << lab::Solution{}.digitSum("9876", 3) << '\n'; // 246
}
```

Chạy từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-2243-calculate-digit-sum-of-a-string /tmp/lc2243-example.cpp -o /tmp/lc2243-example
/tmp/lc2243-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-2243-calculate-digit-sum-of-a-string/test.cpp -o /tmp/lc2243-test
/tmp/lc2243-test
make test
```

## Kiểm thử

14 ca có kỳ vọng suy ra bằng tay, không gọi lại thuật toán để tính đáp án.
Kiểm tra tường minh và `EXIT_FAILURE` bảo đảm lỗi vẫn trả mã khác 0 với NDEBUG.
Các ca bắt lỗi bỏ nhóm cuối, mất chữ số của tổng, bỏ số 0, chỉ chạy một vòng,
và dùng điều kiện dừng sai tại độ dài bằng k. Có độ dài nhỏ nhất 1, lớn nhất
100, k nhỏ nhất 2 và lớn nhất 100, cùng trường hợp không thực hiện vòng nào.

Với 100 chữ số 9 và k=99, hai tổng là 891 và 9, nên kết quả `"8919"`.
Với k=2, các trạng thái đầu có dạng `(18)` lặp 50 lần, rồi 50 chữ số 9,
rồi `(18)` lặp 25 lần, rồi 25 chữ số 9. Tiếp theo số chữ số 9 lần lượt là
13, 7, 4; cuối cùng `9999 → 1818 → 99`. Với 100 số 0 và k=2,
độ dài lần lượt là `100 → 50 → 25 → 13 → 7 → 4 → 2`, kết quả `"00"`.

## Bài tập

1. Ghi lại trạng thái sau từng vòng mà không thay đổi cách tính nhóm.
2. Tìm một đầu vào có vòng đầu không giảm độ dài, giải thích vòng sau.
3. Chứng minh cận thời gian chặt hơn cận O(n²) bảo thủ ở trên.
4. Giải thích vì sao cho phép k=1 có thể làm thuật toán không kết thúc.
