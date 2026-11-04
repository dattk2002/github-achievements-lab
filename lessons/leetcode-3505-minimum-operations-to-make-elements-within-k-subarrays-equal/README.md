# LeetCode 3505 — Chọn k đoạn có chi phí đồng nhất nhỏ nhất

- Nguồn: [Minimum Operations to Make Elements Within K Subarrays Equal](https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/)
- Ngày Daily được cung cấp: **2026-11-04**.
- Độ khó: **Hard**. C++17, chỉ dùng thư viện chuẩn.

## Hợp đồng

```cpp
lab::Solution solution;
long long answer = solution.minOperations(nums, x, k);
```

Mỗi thao tác tăng hoặc giảm một phần tử một đơn vị. Tìm chi phí nhỏ nhất
để có ít nhất `k` đoạn liên tiếp, mỗi đoạn dài đúng `x`, không chung chỉ số,
và các phần tử trong từng đoạn bằng nhau. Các đoạn có thể có giá trị đích
khác nhau và có thể nằm sát nhau; không bắt buộc phủ hết mảng.

Tiền điều kiện: `2 <= nums.size() <= 100000`, `-1000000 <= nums[i] <= 1000000`,
`2 <= x <= nums.size()`, `1 <= k <= 15`, `2 <= k*x <= nums.size()`.
Hàm không kiểm tra đầu vào ngoài miền này và không sửa `nums`.
Kết quả dùng `long long`: chẳng hạn chi phí có thể đạt `100000000000`.

## Từ trung vị đến cửa sổ trượt

Với một đoạn cố định, chi phí đưa mọi phần tử về `m` là tổng `|a[i]-m|`.
Ghép phần tử nhỏ nhất với lớn nhất, nhỏ nhì với lớn nhì, v.v. Với một cặp
`u <= v`, tổng khoảng cách đến đích luôn ít nhất `v-u`, và đạt mức đó khi
đích nằm trong `[u,v]`. Trung vị thuộc tất cả các khoảng của các cặp,
nên tối thiểu hóa tổng. Với độ dài chẵn, mọi số nguyên giữa hai trung vị
đều tối ưu; lời giải dùng trung vị dưới.

Duy trì hai `multiset` có tính cả số lần xuất hiện:

- `low` giữ nửa nhỏ, có số phần tử bằng `high` hoặc nhiều hơn một.
- Mọi phần tử của `low` không lớn hơn mọi phần tử của `high`.
- Lưu tổng `low_sum`, `high_sum` bằng `long long`.

Thêm phần tử theo ranh giới trung vị rồi cân bằng kích thước. Khi trượt,
xóa đúng một bản sao của phần tử rời cửa sổ rồi cân bằng lại. Chuyển phần
tử lớn nhất của `low` hoặc nhỏ nhất của `high` giữ nguyên thứ tự phân hoạch.
Nếu một giá trị có mặt ở cả hai phía, xóa bản sao ở phía nào cũng cho cùng
đa tập còn lại. Mỗi thời điểm lưu chi phí, hai tập chứa đúng `x` phần tử.

Với `m = max(low)`, chi phí cửa sổ là:

```text
m * |low| - low_sum + high_sum - m * |high|
```

Gọi `cost[s]` là chi phí đoạn bắt đầu tại `s`. Không sắp xếp lại từng cửa
sổ, nên bước này mất `O(n log x)` thời gian.

## Quy hoạch động chọn đoạn

Chỉ cần chọn **đúng k** đoạn: mọi lời giải có nhiều hơn k đoạn đều chứa
một tập con k đoạn hợp lệ với chi phí không lớn hơn. Ngược lại, đúng k
đoạn đã thỏa yêu cầu ít nhất k. Các đoạn không giao nhau nên chi phí cộng
được, không có một phần tử phải nhận hai giá trị đích khác nhau.

Đặt `D[t][i]` là chi phí nhỏ nhất chọn đúng `t` đoạn trong `i` phần tử đầu:

```text
D[0][i] = 0
D[t][i] = vô cùng nếu i < t*x
D[t][i] = min(D[t][i-1], D[t-1][i-x] + cost[i-x]) nếu i >= t*x
```

Một lời giải tối ưu hoặc không dùng chỉ số `i-1`, hoặc dùng đoạn cuối
`[i-x, i)`. Ở trường hợp sau, mọi đoạn trước phải nằm trong tiền tố dài
`i-x`. Hai trường hợp bao phủ mọi khả năng và đều xây dựng được lời giải
hợp lệ, chứng minh công thức bằng quy nạp. Kết quả là `D[k][n]`.

Chỉ giữ hai hàng DP. Dùng giá trị vô cùng `LLONG_MAX/4` để việc cộng chi
phí không tràn; mọi chi phí hữu hạn trong miền đề bài không quá `10^11`.

**Độ phức tạp:** `O(n log x + nk)` thời gian; `O(n + x) = O(n)` bộ nhớ
phụ cho chi phí, hai hàng DP và hai đa tập. Không dùng đệ quy trong lời giải.

## Ví dụ tự xây dựng

1. `nums = {-4, 7}, x = 2, k = 1`: chọn đích `0`, cần `4+7=11`
   thao tác. Mọi đích nguyên trong `[-4,7]` cũng tối ưu.
2. `nums = {9, 2, 2, 8, 8, -9}, x = 2, k = 2`: chọn các đoạn ở chỉ số
   `[1,3)` và `[3,5)`, không cần thao tác, đáp án `0`.
3. `nums = {1, 1, 2, 9}, x = 2, k = 2`: vì `k*x=n`, phải chọn hai cặp
   đầu và cuối, tổng chi phí `0+7=7`. Chọn riêng các cửa sổ rẻ nhất sẽ
   sai vì hai cửa sổ đầu giao nhau.

## Chạy thử và kiểm thử

Từ thư mục gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-3505-minimum-operations-to-make-elements-within-k-subarrays-equal/test.cpp \
  -o /tmp/lesson-3505
/tmp/lesson-3505
make test
```

`test.cpp` gọi giao diện trên trực tiếp và thoát với mã khác 0 nếu sai,
không dùng `assert`. Các ca cố định kiểm tra trung vị chẵn/lẻ, số âm,
trùng lặp, bỏ qua hai đầu, cấm giao nhau, cho phép sát nhau, `k*x=n`,
`x=n`, `k=15`, `n=100000`, và phép tính vượt 32 bit. Mỗi lần gọi cũng
kiểm tra đầu vào không bị sửa.

Oracle độc lập duyệt mọi tập chỉ số bắt đầu không giao nhau, rồi thử mọi
đích nguyên từ giá trị nhỏ nhất đến lớn nhất của từng đoạn. Oracle không
dùng trung vị hay DP. Bộ kiểm thử duyệt mọi mảng độ dài 2 đến 8 trên
`{-1,0,1}` và mọi cặp `(x,k)` hợp lệ: **105.849** trường hợp đối chiếu.
Bản khung trả 0 đã thất bại ở ca đầu (`11` so với `0`) trước khi cài đặt.

## Bài tập

1. Vì sao không thể chỉ lấy k cửa sổ có chi phí nhỏ nhất? Tự tạo một phản ví dụ.
2. Bổ sung truy vết để trả về chỉ số bắt đầu và trung vị cho từng đoạn.
   Phân tích phần bộ nhớ tăng thêm.
3. Nếu mỗi vị trí có trọng số thao tác riêng, trung vị thường còn đúng không?
   Hãy tìm ví dụ và đề xuất khái niệm trung vị có trọng số.
