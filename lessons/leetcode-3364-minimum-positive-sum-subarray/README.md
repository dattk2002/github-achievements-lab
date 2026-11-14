# LeetCode 3364: Minimum Positive Sum Subarray — C++17

Nguồn: [Minimum Positive Sum Subarray](https://leetcode.com/problems/minimum-positive-sum-subarray/).
Ngày nguồn (`source_date`): 2026-11-14. Độ khó: Easy.
Diễn giải, ví dụ và lời giải dưới đây được viết riêng cho bài học.

## Hợp đồng và tiền điều kiện

`lab::Solution::minimumSumSubarray(std::vector<int>& nums, int l, int r)`
trả về tổng dương nhỏ nhất của một đoạn **liên tiếp** có độ dài trong
`[l,r]`. Nếu không có đoạn phù hợp, trả về `-1`. Tổng bằng 0 không hợp lệ.

Tiền điều kiện: `1 <= nums.size() <= 100`,
`1 <= l <= r <= nums.size()`, `-1000 <= nums[i] <= 1000`.
Hàm không kiểm tra đầu vào ngoài miền này và không sửa `nums`;
tham chiếu không const giữ dạng giao diện của bài gốc.

## Thuật toán: cố định đầu trái, mở rộng đầu phải

Với mỗi vị trí `start`, đặt `sum = 0`, rồi tăng độ dài từ 1 đến `r`,
dừng nếu chạm cuối mảng. Mỗi lần thêm phần tử mới vào `sum`:

- Chỉ xét ứng viên khi độ dài ít nhất `l` và `sum > 0`.
- Nếu chưa có đáp án (`best == -1`) hoặc tổng mới nhỏ hơn, cập nhật `best`.

Phải cộng cả các phần tử trước khi đạt độ dài `l`, vì chúng vẫn thuộc đoạn.
Không dừng khi tổng đang âm hoặc lớn hơn đáp án: phần tử tiếp theo có thể
mang dấu bất kỳ. Vì vậy cách co cửa sổ dựa trên tính đơn điệu của tổng
không áp dụng trực tiếp như với mảng toàn số dương.

### Vì sao đúng?

Sau bước độ dài `k`, biến `sum` bằng tổng chính xác của đoạn từ `start`
đến `start+k-1`: ban đầu bằng 0 và mỗi bước cộng đúng một phần tử kế tiếp.
Mọi đoạn có độ dài trong `[l,r]` có duy nhất một đầu trái và một độ dài,
nên được duyệt đúng một lần. Điều kiện cập nhật loại bỏ đúng những đoạn
không hợp lệ. Sau mỗi ứng viên, `best` là tổng dương nhỏ nhất đã gặp,
hoặc `-1` nếu chưa gặp tổng dương. Khi duyệt xong, đây là đáp án cần tìm.

Thời gian `O(n·r)`, tối đa `O(n²)`; bộ nhớ phụ `O(1)`.
Mọi tổng có trị tuyệt đối không vượt `100 × 1000 = 100000`, vừa `int`
32 bit. Không cần mảng tổng tiền tố trong lời giải chính.

## Ví dụ tự xây dựng

- `nums = [6,-4,3], l = 2, r = 3`: các tổng hợp lệ là 2, -1, 5;
  đáp án là 2 từ đoạn `[6,-4]`.
- `nums = [4,-6,3], l = 2, r = 3`: hai đoạn dài 2 đều âm;
  cả mảng có tổng 1, nên đáp án là 1.
- `nums = [5,-5,4], l = r = 2`: các tổng là 0 và -1,
  nên kết quả là -1, không phải 0.

Lưu chương trình sau thành `/tmp/lc3364-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nums{4, -6, 3};
    std::cout << lab::Solution{}.minimumSumSubarray(nums, 2, 3) << '\n'; // 1
}
```

Chạy từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-3364-minimum-positive-sum-subarray /tmp/lc3364-example.cpp -o /tmp/lc3364-example
/tmp/lc3364-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-3364-minimum-positive-sum-subarray/test.cpp -o /tmp/lc3364-test
/tmp/lc3364-test
make test
```

## Kiểm thử và các biên dễ sai

Bộ kiểm thử dùng điều kiện tường minh và `std::exit(EXIT_FAILURE)`,
không dùng `assert`, nên vẫn phát hiện lỗi khi có `NDEBUG`.
Mỗi lần gọi còn kiểm tra mảng đầu vào được giữ nguyên.

Các ca có đáp án tính tay bao phủ mảng một phần tử, số 0, toàn âm,
nghiệm ở độ dài `l` hoặc `r`, `l = r`, đoạn kết thúc ở phần tử cuối,
và việc loại bỏ tổng nhỏ hơn nhưng có độ dài ngoài miền.
Với 100 phần tử đều bằng 1000 và `l = r = 100`, chỉ có một đoạn,
tổng là 100000; nếu cho phép độ dài 1 thì đáp án là 1000.
Mảng 100 phần tử đều bằng -1000 không có nghiệm.

Oracle độc lập xây tổng tiền tố, rồi xét theo độ dài bằng hiệu hai tổng
tiền tố. Nó không gọi hàm lời giải hay dùng cách cộng dồn theo đầu trái.
Duyệt mọi mảng độ dài 1..6 trên tập `{-2,0,3}` và mọi cặp `l,r` hợp lệ
cho 19.956 lượt đối chiếu, bổ sung cho các ca giới hạn tính tay.

## Bài tập

1. Viết phiên bản dùng tổng tiền tố; so sánh thời gian và bộ nhớ phụ.
2. Trả thêm chỉ số hai đầu của một đoạn tối ưu; quy định cách phá hòa.
3. Tìm phản ví dụ cho việc dừng mở rộng ngay khi tổng không dương.
4. Nếu n rất lớn, thử dùng tập có thứ tự của các tổng tiền tố trong cửa
   sổ độ dài cho phép để đạt `O(n log n)`; chú ý tổng phải dương nghiêm ngặt.
