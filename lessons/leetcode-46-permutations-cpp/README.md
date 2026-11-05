# LeetCode 46 — Liệt kê hoán vị bằng quay lui

Nguồn công khai: [LeetCode 46: Permutations](https://leetcode.com/problems/permutations/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-05**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`std::vector<std::vector<int>> lab::Solution::permute(std::vector<int>& nums)` trả tất cả hoán vị của các giá trị đầu vào, mỗi hoán vị xuất hiện đúng một lần. Thứ tự các kết quả không bắt buộc. Hàm giữ nguyên đầu vào.

Bài gốc có `1 <= nums.size() <= 6`, các giá trị phân biệt trong `[-10, 10]`. Những điều kiện này là tiền điều kiện, không được kiểm tra lại. Bản này mở rộng mảng rỗng thành một hoán vị rỗng (`{{}}`), tương ứng có đúng một cách sắp xếp 0 phần tử. Nếu đầu vào có giá trị trùng, thuật toán theo chỉ số có thể sinh kết quả trùng và không còn thỏa hợp đồng bài gốc.

## Quay lui và chứng minh

Giữ `path` là tiền tố đang xây dựng, cùng `used[i]` cho biết phần tử tại chỉ số i đã xuất hiện trên đường hiện tại hay chưa. Nếu đường đủ n phần tử, sao chép nó vào kết quả. Nếu chưa đủ, thử từng chỉ số chưa dùng: đánh dấu, thêm giá trị, đệ quy, rồi bỏ giá trị cuối và gỡ dấu.

Bất biến: `path` chỉ chứa các giá trị thuộc các chỉ số phân biệt, và `used` khớp chính xác với các chỉ số đã chọn. Vì các giá trị đầu vào phân biệt, mọi lá có độ dài n là một hoán vị hợp lệ. Mỗi hoán vị có duy nhất một chuỗi lựa chọn chỉ số từ gốc tới lá, nên không có kết quả trùng. Thử đủ mọi chỉ số chưa dùng ở mỗi bước bao phủ mọi hoán vị.

Hai thao tác hoàn tác là thiết yếu: chúng phục hồi trạng thái của tiền tố trước khi thử nhánh kế tiếp. Trạng thái là biến cục bộ mỗi lần gọi API nên không bị sót từ lần gọi trước. Đệ quy chỉ đọc `nums`, không cần hoán đổi hay sắp xếp đầu vào.

Độ phức tạp: O(n × n!) thời gian, gồm sao chép n phần tử cho mỗi trong n! kết quả. O(n) bộ nhớ phụ cho đường đi, dấu đã dùng và stack; ngoài ra kết quả cần O(n × n!) bộ nhớ. Với n=6 có 720 hoán vị. Mảng rỗng có một kết quả và chi phí O(1).

## Ví dụ chạy được

Lưu thành `/tmp/permutation-example.cpp`, chạy ở gốc repo:

```cpp
#include "lessons/leetcode-46-permutations-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{-2, 4};
    lab::Solution solution;
    const auto result = solution.permute(nums);
    std::cout << result.size() << '\n';
    for (const auto& row : result) std::cout << row[0] << ',' << row[1] << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/permutation-example.cpp -o /tmp/permutation-example
/tmp/permutation-example
```

Bản cài đặt này in:

```text
2
-2,4
4,-2
```

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-46-permutations-cpp/test.cpp -o /tmp/permutation-test
/tmp/permutation-test
make test-all
```

Oracle sắp xếp bản sao rồi dùng `std::next_permutation`, khác cách quay lui của lời giải. So toàn bộ tập kết quả và kiểm tra không có phần tử trùng; nhờ đó không phụ thuộc thứ tự sinh. Có mảng rỗng, một phần tử, số âm, hai đầu miền giá trị, và mọi tập con của sáu giá trị phân biệt được đưa vào theo thứ tự đảo. Tập đủ sáu phần tử kiểm chứng đủ 720 hoán vị. Mọi ca kiểm tra không sửa đầu vào. Test không dựa vào `assert` và trả mã 1 cả khi bật `NDEBUG`.

## Bài tập

1. Liệt kê hoán vị khi có giá trị trùng mà không dùng `set` để lọc sau cùng; quy tắc bỏ nhánh phải đổi thế nào?
2. Truyền callback xử lý từng hoán vị thay vì giữ toàn bộ kết quả: bộ nhớ thay đổi ra sao?
3. Tìm hoán vị thứ k theo thứ tự từ điển mà không liệt kê mọi hoán vị trước nó; vai trò của giai thừa là gì?
