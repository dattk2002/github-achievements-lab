# LeetCode 152: Maximum Product Subarray (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/maximum-product-subarray/). Độ khó: Medium.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::maxProduct(std::vector<int>& nums)` trả tích lớn nhất trong
mọi đoạn con **liên tiếp không rỗng**. Không được chọn tập phần tử rời nhau
hoặc mặc định chọn đoạn rỗng. Hàm giữ nguyên đầu vào.

Nguồn cho `1 <= n <= 20000`, `-10 <= nums[i] <= 10` và đảm bảo tích của **mọi**
đoạn con vừa số nguyên có dấu 32 bit. Các giới hạn đó là tiền điều kiện;
hàm không kiểm tra tràn số cho dữ liệu ngoài miền này. Mở rộng riêng: mảng
rỗng ném `std::invalid_argument`. Mảng một phần tử âm phải trả chính số âm đó.

## Giữ cả cực đại và cực tiểu kết thúc tại đây

Đặt `largest`, `smallest` là tích lớn nhất, nhỏ nhất của đoạn kết thúc tại vị
trí trước. Với giá trị mới `x`, mọi đoạn kết thúc tại đây là đoạn chỉ có `x`
hoặc nối `x` vào một đoạn trước đó. Hai giá trị cần xét khi nối là
`largest*x` và `smallest*x`. Lấy cực đại và cực tiểu của ba ứng viên này cùng
`x`, rồi cập nhật kết quả toàn cục từ cực đại mới.

Phải tính hai tích bằng trạng thái **cũ** trước khi ghi đè. Khi `x` âm, nhân
với tích nhỏ nhất có thể tạo tích lớn nhất. Khi `x=0`, cả hai trạng thái về 0,
đồng thời `x` ở bước sau cho phép bắt đầu đoạn mới.

Với `[-3,2,-4,0,5]`, đoạn `[-3,2,-4]` cho tích `24`. Chỉ giữ tích lớn nhất
ở mỗi bước sẽ bỏ mất tích âm cần dùng khi gặp `-4`.

### Chứng minh

Cơ sở một phần tử có hai cực trị đều bằng `nums[0]`. Giả sử hai cực trị trước
đúng. Mọi đoạn kết thúc tại vị trí mới thuộc đúng một trong hai loại: bắt đầu
mới hoặc nối đoạn cũ. Nhân với một số cố định là hàm đơn điệu tăng, giảm hoặc
hằng tùy dấu, nên cực trị của các tích nối luôn nằm ở một trong hai cực trị
cũ. Ba ứng viên vì thế đủ để tìm cả cực đại lẫn cực tiểu mới. Quy nạp cho các
vị trí rồi lấy cực đại toàn cục bao phủ mọi đoạn con không rỗng.

## Độ phức tạp

Thời gian `O(n)`, bộ nhớ phụ `O(1)`. Mọi tích trung gian đều là tích một đoạn
con, nên vừa `int` 32 bit theo đúng cam kết của nguồn.

## Ví dụ chạy được

Lưu thành `/tmp/lc-152-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> nums{-3,2,-4,0,5};
    std::cout << lab::Solution{}.maxProduct(nums) << '\n'; // 24
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-152-maximum-product-subarray-cpp /tmp/lc-152-example.cpp -o /tmp/lc-152-example
/tmp/lc-152-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-152-maximum-product-subarray-cpp/test.cpp -o /tmp/lc-152-test
/tmp/lc-152-test
make test
make test-all
```

## Biên và kiểm thử

Oracle nhân trực tiếp từng đoạn con cho 97655 mảng độ dài `1..7` trên
`{-2,-1,0,1,2}`. Các ca cố định kiểm tra một số âm, hai số âm, số 0 ngăn đoạn,
30 số 2 cho `1073741824`, 20000 số 1/0/-1 và lỗi mảng rỗng. Mọi dữ liệu hợp lệ
đều thỏa điều kiện tích 32 bit của nguồn. Mảng đầu vào được kiểm tra giữ nguyên;
phát hiện sai lệch bằng mã thoát khác 0 cả trong bản `NDEBUG`.

## Bài tập

1. Trả thêm chỉ số đầu/cuối của một đoạn tối ưu.
2. Tìm phản ví dụ cho cách chỉ giữ `largest`.
3. Nếu bỏ cam kết giới hạn tích của nguồn, cần thay đổi hợp đồng số học thế nào?
