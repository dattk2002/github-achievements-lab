# LeetCode 3420: Count Non-Decreasing Subarrays After K Operations

- Nguồn: [LeetCode 3420](https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/)
- Ngày nguồn (`source_date`): **2026-11-13**
- Độ khó (`difficulty`): **Hard**
- Ngôn ngữ: C++17, thư viện chuẩn; lời giải và nội dung giải thích do Codex hỗ trợ.

## Hợp đồng

```cpp
long long lab::Solution::countNonDecreasingSubarrays(
    std::vector<int>& nums, int k);
```

Đếm các đoạn con liên tiếp, không rỗng có thể trở thành không giảm bằng tối đa
`k` lần tăng một phần tử lên một đơn vị. Mỗi đoạn có ngân sách riêng; các phép
tăng không ảnh hưởng đoạn khác. Hàm giữ nguyên `nums` dù nhận tham chiếu khả biến
để tương thích giao diện yêu cầu.

Tiền điều kiện: `1 <= nums.size() <= 100000`, `1 <= nums[i] <= 1000000000`,
`1 <= k <= 1000000000`. Hàm giả định đầu vào hợp lệ, không kiểm tra hay quy định
hành vi cho dữ liệu ngoài miền này.

## Từ chi phí tối thiểu đến cửa sổ trượt

Với một đoạn `[l,r]`, giá trị nhỏ nhất có thể đặt tại vị trí `j` là
`M[j] = max(nums[l], ..., nums[j])`. Không thể đặt thấp hơn vì chỉ được tăng;
đặt đúng `M[j]` tạo thành dãy không giảm. Do đó chi phí tối ưu là

```text
C(l,r) = tổng (M[j] - nums[j]), với l <= j <= r.
```

Quét độc lập tất cả đoạn theo công thức này mất O(n²). Để dùng được cho
100.000 phần tử, ta giữ cửa sổ `[left,right]` và quét `left` từ phải sang trái.
Khi thêm phần tử bên trái, các cực đại tiền tố nhỏ hơn nó phải được nâng lên.

### Biểu diễn bằng deque

Deque lưu chỉ số bắt đầu các khối cực đại tiền tố của cửa sổ:

- Chỉ số tăng từ đầu đến cuối deque.
- Giá trị `nums[index]` không giảm theo thứ tự đó. Các khối bằng nhau có thể
  được giữ riêng để cập nhật đơn giản.
- Khối bắt đầu tại `p` kết thúc ngay trước chỉ số tiếp theo, hoặc tại `right`
  nếu đó là khối cuối. Mọi vị trí trong khối có giá trị đích `nums[p]`.
- `cost` luôn bằng chi phí tối thiểu của toàn cửa sổ.

Khi thêm `left`, lần lượt lấy khối đầu có chiều cao nhỏ hơn `nums[left]` ra.
Nếu khối là `[p,q)`, cộng
`1LL * (q-p) * (nums[left]-nums[p])` vào `cost`. Sau khi xử lý các khối thấp,
đưa `left` vào đầu deque. Các khối vừa lấy ra được biểu diễn bằng khối mới.

Nếu `cost > k`, bỏ phần tử ở `right`. Chi phí giảm đúng bằng
`nums[blocks.back()] - nums[right]`: chiều cao khối cuối trừ giá trị gốc của
phần tử bị bỏ. Nếu chỉ số bắt đầu khối cuối bằng `right`, bỏ cả chỉ số đó.
Sau đó giảm `right` và tiếp tục tới khi cửa sổ hợp lệ.

### Vì sao đếm đúng?

1. Công thức cực đại tiền tố cho chi phí nhỏ nhất, nên `cost <= k` tương đương
   đoạn có thể sửa bằng ngân sách cho phép.
2. Thêm bên trái chỉ nâng các khối thấp đầu deque; bỏ bên phải không đổi cực
   đại tiền tố của các vị trí còn lại. Hai thao tác bảo toàn các bất biến trên.
3. Với `left` cố định, kéo dài đoạn không làm giảm chi phí. Các điểm kết thúc
   hợp lệ vì thế tạo thành một khoảng liên tiếp bắt đầu ở `left`.
4. Một điểm kết thúc đã bị loại ở bước trước vẫn không hợp lệ sau khi thêm
   phần tử bên trái: thêm bên trái không thể giảm chi phí sửa phần đoạn cũ.
   Vì vậy không cần tăng lại `right`. Sau vòng thu hẹp, `right` là điểm kết thúc
   hợp lệ lớn nhất, đóng góp đúng `right-left+1` đoạn.

Mỗi đoạn được tính duy nhất tại bước có đầu trái của nó. Đoạn một phần tử có
chi phí 0 nên vòng thu hẹp luôn dừng trước khi làm cửa sổ rỗng.

## Độ phức tạp và số học

Mỗi chỉ số vào deque một lần, ra nhiều nhất một lần ở một trong hai đầu.
`right` chỉ giảm, tổng cộng tối đa n lần. Thời gian **O(n)** theo phân tích
khấu hao; bộ nhớ phụ **O(n)**. Không sửa hay sao chép mảng đầu vào trong lời giải.

Số đoạn có thể đạt `100000*100001/2 = 5000050000`. Chi phí tạm thời trước khi
thu hẹp có thể gần 10¹⁴, dù `k` chỉ đến 10⁹. Vì vậy cả chi phí, tích nâng khối
và kết quả đều phải dùng `long long`; ép sang 64 bit trước phép nhân.

## Ví dụ tự xây dựng

Với `nums = [5,2,4]`, có sáu đoạn không rỗng. Ba đoạn đơn và `[2,4]` không cần
thao tác. `[5,2]` cần 3 lần tăng; `[5,2,4]` cần `3+1=4` lần tăng.

| Ngân sách k | Số đoạn hợp lệ |
| --- | --- |
| 2 | 4 |
| 3 | 5 |
| 4 | 6 |

Chạy ví dụ từ thư mục gốc kho mã:

```bash
cat > /tmp/example-3420.cpp <<'CPP'
#include "lessons/leetcode-3420-count-non-decreasing-subarrays-after-k-operations/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{5, 2, 4};
    std::cout << lab::Solution{}.countNonDecreasingSubarrays(nums, 3) << '\n';
}
CPP
g++ -std=c++17 -I. /tmp/example-3420.cpp -o /tmp/example-3420
/tmp/example-3420
# Kết quả: 5
```

## Kiểm thử

```bash
make test
g++ -std=c++17 -O2 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-3420-count-non-decreasing-subarrays-after-k-operations/test.cpp \
  -o /tmp/test-3420
/tmp/test-3420
```

Bộ test dùng kiểm tra tường minh và `EXIT_FAILURE`, không dùng `assert` nên vẫn
báo lỗi khi bật `NDEBUG`. Test được viết trước; hàm khung trả 0 đã bị phát hiện
ở ca một phần tử trước khi triển khai thuật toán.

Các nhóm kiểm tra:

- Một phần tử ở hai biên giá trị, dãy tăng và dãy bằng nhau.
- Ngân sách vừa thiếu, đúng bằng, hoặc đủ cho toàn đoạn; đoạn giảm và đỉnh xen kẽ.
- Mọi mảng độ dài 1 đến 7 trên tập `{1,2,3}`, mỗi mảng với k từ 1 đến 12:
  **39.348** phép đối chiếu với bộ tính O(n²) duyệt từng đoạn và cộng thiếu hụt
  theo cực đại tiền tố, không dùng deque hay cửa sổ trượt.
- Mảng 100.000 phần tử: kết quả vượt 32 bit, deque dài, nhiều lần gộp khối,
  thu hẹp cửa sổ và chi phí trung gian lớn. Với dãy giảm đều, đoạn dài t tốn
  `t*(t-1)/2`, cho một công thức kỳ vọng độc lập.
- Mảng bắt đầu bằng 10⁹ rồi toàn số 1: chỉ hai đoạn bắt đầu tại vị trí đầu hợp
  lệ với k = 10⁹; tất cả đoạn trong phần đuôi hợp lệ. Ca này bắt lỗi tràn chi phí.
- Mọi lời gọi đều kiểm tra dữ liệu đầu vào không bị thay đổi.

## Bài tập

1. Mô phỏng deque, `cost` và `right` cho `[8,3,6,2,7]` với k = 5.
2. Giải thích vì sao dùng cửa sổ quét trái sang phải khó cập nhật khi bỏ một
   cực đại đầu đoạn; chỉ ra các phần tử có giá trị đích bị thay đổi.
3. Chứng minh giới hạn tổng số thao tác deque dù có hai vòng `while` lồng nhau.
4. Viết lời giải O(n log n) bằng tìm kiếm nhị phân và cấu trúc truy vấn phù hợp,
   rồi dùng oracle hiện tại để kiểm tra cách làm đó.
