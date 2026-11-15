# LeetCode 1524: Number of Sub-arrays With Odd Sum — C++17

Nguồn: [Number of Sub-arrays With Odd Sum](https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/).
Ngày nguồn (`source_date`): 2026-11-15. Độ khó: Medium.
Phần diễn giải, ví dụ và lời giải dưới đây được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::numOfSubarrays(std::vector<int>& arr)` đếm các đoạn
liên tiếp, không rỗng có tổng lẻ và trả kết quả modulo `1.000.000.007`.
Hai đoạn có vị trí khác nhau được tính riêng dù chứa cùng giá trị.

Tiền điều kiện: `1 <= arr.size() <= 100000`, `1 <= arr[i] <= 100`.
Hàm không kiểm tra dữ liệu ngoài miền; không sửa mảng đầu vào.
Tham chiếu không const giữ dạng giao diện gốc. Mỗi lần gọi độc lập.

## Thuật toán và chứng minh

Gọi `P[k]` là tổng k phần tử đầu tiên, với `P[0] = 0`.
Tổng đoạn `[l,r]` là `P[r+1] - P[l]`; tổng này lẻ khi và chỉ khi
hai tiền tố có tính chẵn/lẻ khác nhau. Vì vậy chỉ cần lưu số tiền tố
chẵn và lẻ đã gặp, không cần lưu toàn bộ tổng.

Khởi tạo `counts = {1,0}` để tính cả tiền tố rỗng chẵn,
`parity = 0` và `answer = 0`. Với mỗi phần tử:

1. Cập nhật `parity` bằng XOR với phần dư của phần tử cho 2.
2. Cộng số tiền tố cũ có parity đối lập vào đáp án, rồi lấy modulo.
3. Ghi nhận tiền tố hiện tại vào `counts[parity]`.

Trước mỗi lần xử lý, hai bộ đếm chứa chính xác các tiền tố kết thúc
trước tiền tố mới. Bước 2 ghép mỗi tiền tố đối lập với tiền tố mới,
tạo đúng một đoạn tổng lẻ kết thúc tại phần tử hiện tại. Mọi đoạn
như vậy đều có đúng một tiền tố đầu và đều được đếm. Bước 3 giữ
bất biến cho lần sau. Mỗi đoạn có duy nhất một đầu phải nên không
bị đếm lặp. Phép lấy modulo bảo toàn phần dư của tổng số đoạn.

Thời gian `O(n)`, bộ nhớ phụ `O(1)`. Dùng `long long` cho bộ đếm
và đáp án để phép cộng an toàn. Số đoạn tổng lẻ có thể vượt `int`
32 bit: với 100.000 phần tử lẻ, số đoạn là `2.500.050.000`.
Lời giải không cộng tổng các giá trị, chỉ theo dõi parity.

## Ví dụ tự xây dựng

- `[8,3,6]`: các đoạn hợp lệ là `[3]`, `[8,3]`, `[3,6]`,
  `[8,3,6]`, nên đáp án là 4.
- `[3,7]`: chỉ hai đoạn một phần tử có tổng lẻ, đáp án là 2.
- `[3,3,3,3]`: bốn đoạn dài 1 và hai đoạn dài 3 cho đáp án 6.

Với `[8,3,6]`, bảng dưới ghi số tiền tố **sau** khi xử lý:

| Đã đọc | Parity mới | Số đoạn thêm | Tiền tố chẵn | Tiền tố lẻ | Đáp án |
|---|---|---|---|---|---|
| Chưa đọc | 0 | 0 | 1 | 0 | 0 |
| 8 | 0 | 0 | 2 | 0 | 0 |
| 3 | 1 | 2 | 2 | 1 | 2 |
| 6 | 1 | 2 | 2 | 2 | 4 |

Lưu ví dụ sau thành `/tmp/lc1524-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> arr{8, 3, 6};
    std::cout << lab::Solution{}.numOfSubarrays(arr) << '\n'; // 4
}
```

Chạy từ thư mục gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-1524-number-of-sub-arrays-with-odd-sum /tmp/lc1524-example.cpp -o /tmp/lc1524-example
/tmp/lc1524-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-1524-number-of-sub-arrays-with-odd-sum/test.cpp -o /tmp/lc1524-test
/tmp/lc1524-test
make test
```

## Kiểm thử và lỗi dễ gặp

Bộ kiểm thử dùng kiểm tra tường minh và `std::exit(EXIT_FAILURE)`,
không dùng `assert`, nên vẫn báo lỗi bằng mã thoát khác 0 khi có `NDEBUG`.
Giai đoạn đỏ chạy với hàm tạm trả 0 đã thất bại ở `[1]` (cần 1).

Các ca tính tay kiểm tra một phần tử ở cả hai parity, giá trị 1 và 100,
mảng toàn chẵn, toàn lẻ, đoạn bắt đầu từ vị trí 0 và các số chẵn nằm
giữa hai số lẻ. Mỗi lần gọi kiểm tra đầu vào không đổi, và dùng lại
một đối tượng để phát hiện trạng thái tồn dư giữa các lần gọi.

Oracle độc lập duyệt mọi cặp đầu trái/phải rồi cộng giá trị thật,
không dùng bộ đếm parity. Đối chiếu toàn bộ 21.844 mảng độ dài 1..7
trên tập `{1,2,99,100}` giúp bắt các lỗi cập nhật parity và bộ đếm.

Các ca n = 100.000 kiểm tra quy mô và modulo:

- Toàn 100 cho kết quả 0.
- Toàn 99: chỉ độ dài lẻ hợp lệ. Tổng số vị trí theo các độ dài đó
  là `100000 + 99998 + ... + 2 = 50000 × 50001 = 2500050000`,
  lấy modulo được `500049986`.
- Chỉ một số lẻ tại chỉ số 49999: đoạn hợp lệ phải chứa nó, có
  `50000 × 50001` cách chọn hai đầu, cùng phần dư trên.
- Chỉ phần tử đầu lẻ: có đúng 100.000 đoạn hợp lệ.

Quên tiền tố rỗng sẽ bỏ sót các đoạn bắt đầu ở chỉ số 0.
Đếm các tiền tố cùng parity lại cho số đoạn tổng chẵn.
Không lấy modulo hoặc tích lũy bằng kiểu quá nhỏ sẽ sai ở ca lớn.
Mảng rỗng, số 0 và số âm nằm ngoài tiền điều kiện của bài này.

## Bài tập

1. Sửa thuật toán để đếm đoạn có tổng chẵn, giải thích bất biến mới.
2. Chứng minh công thức đếm đoạn tổng lẻ khi mọi phần tử đều lẻ.
3. Mở rộng sang tổng đồng dư k modulo m; xác định bộ đếm cần dùng.
4. Viết phiên bản xử lý luồng, mỗi lần nhận một phần tử và trả tổng
   số đoạn lẻ đã gặp; phân biệt trạng thái luồng với API hiện tại.
