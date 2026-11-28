# LeetCode 90: Subsets II — Backtracking tập con không trùng

Nguồn: [LeetCode 90: Subsets II](https://leetcode.com/problems/subsets-ii/), Medium.
Bài bổ sung ngày **2026-11-28**, không phải nhãn Daily. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::subsetsWithDup(std::vector<int>& nums)` trả mọi tập con
khác nhau của một đa tập số nguyên. Mỗi giá trị được chọn tối đa bằng số
lần nó có trong input. Có tập rỗng, không có kết quả lặp; thứ tự các tập
con không quan trọng. Hàm sắp xếp một bản sao và giữ nguyên input.

Tiền điều kiện theo nguồn: `1 <= nums.size() <= 10`, giá trị trong `[-10,10]`.
Không có cam kết kiểm tra dữ liệu ngoài miền. Mỗi lần gọi có trạng thái riêng.

## Thuật toán và bất biến

Sắp xếp bản sao để những giá trị bằng nhau đứng liền nhau. `path` là tập
con hiện tại; `begin` là chỉ số đầu tiên còn được chọn. Mỗi lần vào hàm
đệ quy, đưa một bản sao `path` vào kết quả, kể cả lúc `path` rỗng.

Duyệt `i` từ `begin`. Nếu `i > begin` và giá trị bằng phần tử liền trước,
bỏ qua nhánh đó: một nhánh cùng độ sâu đã chọn giá trị này. Nếu không,
thêm giá trị vào `path`, đệ quy từ `i+1`, rồi lấy phần tử vừa thêm ra.

Điều kiện **`i > begin`**, thay vì chỉ `i > 0`, rất quan trọng. Nó cho
phép chọn bản thứ hai của cùng một giá trị ở độ sâu tiếp theo. Nếu luôn
bỏ phần tử bằng phần tử trước, các tập con như `[3,3]` sẽ biến mất.

## Tính đúng đắn

Chỉ số tăng nghiêm ngặt nên một phần tử không bị chọn lại. Sắp xếp giúp
mỗi tập con có một biểu diễn không giảm. Trong các vị trí mang cùng giá
trị ở một độ sâu, chọn vị trí đầu tiên cho phép tạo mọi số lượng cần có
ở những độ sâu tiếp theo; các vị trí còn lại chỉ tạo kết quả đã có.
Bởi vậy không mất tập con hợp lệ và không sinh hai nhánh cho cùng tập con.
Thao tác lấy phần tử ra khôi phục `path` trước khi xét nhánh kế tiếp.

## Độ phức tạp

Nếu có `U` tập con phân biệt, thời gian bị chặn bởi **O(n log n + nU)**,
bao gồm sao chép kết quả. Trường hợp mọi phần tử khác nhau: `U=2^n`, thành
**O(n*2^n)**. Bộ nhớ phụ **O(n)** cho bản sao đã sắp, đường đi và stack;
bộ nhớ kết quả tối đa **O(nU)**. Đây là bài liệt kê, không thể bỏ qua chi
phí xuất kết quả.

## Ví dụ tự xây dựng

Input `[3,1,3]` có sáu tập con:
`[]`, `[1]`, `[1,3]`, `[1,3,3]`, `[3]`, `[3,3]`.
Số lượng bằng `(1+1)*(2+1)=6` vì có hai lựa chọn số bản của `1` và ba của `3`.

## Chạy ví dụ

Tại thư mục bài học:

```sh
cat > /tmp/lc90-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> values{3,1,3};
    std::cout << lab::Solution{}.subsetsWithDup(values).size() << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc90-example.cpp -o /tmp/lc90-example
/tmp/lc90-example
```

Kết quả:

```text
6
```

## Kiểm thử và trường hợp biên

Oracle duyệt mọi bitmask vị trí, chuẩn hóa mỗi tập con bằng sắp xếp rồi
dùng `std::set` khử trùng. Đây là cách khác với việc loại nhánh trong lời
giải. Test so tập kết quả đầy đủ, kiểm tra không có phần tử lặp và input
không đổi cho **3279** mảng độ dài `1..7` trên `{-1,0,1}`.

Biên gồm một phần tử, số âm/dương cực trị theo đề, mười phần tử bằng
nhau (11 tập con), mười phần tử khác nhau (1024 tập con), cùng một đối
tượng được gọi nhiều lần. Việc bỏ toàn bộ giá trị trùng hoặc quên hoàn
nguyên `path` đều bị oracle phát hiện.

## Bài tập tự luyện

1. Chứng minh `U = product(frequency[value] + 1)`.
2. Viết bản đệ quy theo nhóm giá trị và số bản được chọn, rồi so với oracle.
3. Điều chỉnh bài để chỉ liệt kê tập con có tổng bằng một số cho trước;
   vì sao có số âm thì không thể dừng chỉ dựa vào tổng hiện tại quá lớn?

## Chạy kiểm thử

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc90-test
/tmp/lc90-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc90-ndebug
/tmp/lc90-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Test dùng mã thoát lỗi,
không dùng `assert`, nên vẫn kiểm tra đầy đủ khi bật `NDEBUG`.
