# LeetCode 131 — Tách chuỗi thành các đoạn đối xứng

Nguồn công khai: [LeetCode 131: Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-08**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`std::vector<std::vector<std::string>> lab::Solution::partition(std::string s)` trả mọi cách tách s thành các đoạn **liên tiếp, không rỗng và đối xứng**. Ghép các đoạn theo thứ tự phải khôi phục đúng s. Mỗi cách tách xuất hiện đúng một lần; thứ tự giữa các cách không bắt buộc. Các đoạn bằng nhau ở vị trí khác nhau vẫn hợp lệ.

Bài gốc: chuỗi dài 1..16, chỉ gồm chữ thường tiếng Anh. Đây là tiền điều kiện, không kiểm tra lại. Bản này mở rộng chuỗi rỗng thành một cách tách rỗng (`{{}}`), không phải không có cách nào. Chuỗi nhận theo giá trị, không sửa biến của người gọi.

## Bảng đối xứng và quay lui

Tính trước `palindrome[left][right]`: hai ký tự đầu/cuối phải bằng nhau, và đoạn giữa phải đối xứng; đoạn dài 1 hoặc 2 không cần tra đoạn giữa. Duyệt left giảm dần để hàng chứa đoạn giữa đã được tính khi cần. Bảng tốn O(n²) thời gian/bộ nhớ.

Quay lui từ vị trí begin chưa được tách. Thử mọi end từ begin tới cuối chuỗi; nếu đoạn `[begin,end]` đối xứng thì đưa vào đường hiện tại, đệ quy từ end+1, rồi gỡ đoạn vừa thêm. Khi begin bằng n, sao chép đường đi vào kết quả.

Bất biến: các đoạn trên đường hiện tại đều không rỗng, đối xứng và phủ chính xác tiền tố `[0,begin)`. Mỗi lựa chọn hợp lệ mở rộng bất biến; đến cuối tạo một cách tách hợp lệ. Mọi cách tách có một đoạn đầu kết thúc tại một end được thử, rồi phần còn lại được đệ quy bao phủ. Hai chuỗi lựa chọn điểm cắt khác nhau không thể tạo cùng một vector đoạn, nên không cần `set` để loại trùng trong lời giải. Thao tác pop sau mỗi nhánh phục hồi đúng tiền tố cho nhánh kế tiếp.

Có tối đa 2^(n-1) cách chọn cắt giữa các ký tự, đạt được khi mọi ký tự bằng nhau. Tính cả sao chép chuỗi kết quả, thời gian xấu nhất O(n²+n·2^n). Bộ nhớ phụ O(n²+n) ngoài kết quả, gồm bảng, stack, đường đi và bản sao tham số. Kết quả có thể cần O(n·2^n) bộ nhớ. Với n=16 ký tự giống nhau có 32768 cách tách.

## Ví dụ chạy được

Lưu thành `/tmp/palindrome-partition-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-131-palindrome-partitioning-cpp/lesson.hpp"
#include <iostream>
int main() {
    lab::Solution solution;
    for (const auto& pieces : solution.partition("noon")) {
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            if (i) std::cout << '|';
            std::cout << pieces[i];
        }
        std::cout << '\n';
    }
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/palindrome-partition-example.cpp -o /tmp/palindrome-partition-example
/tmp/palindrome-partition-example
```

Bản cài đặt này in:

```text
n|o|o|n
n|oo|n
noon
```

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-131-palindrome-partitioning-cpp/test.cpp -o /tmp/palindrome-partition-test
/tmp/palindrome-partition-test
make test-all
```

Oracle thử mọi mặt nạ điểm cắt và kiểm tra đối xứng trực tiếp, không dùng bảng DP của lời giải. Đối chiếu toàn bộ 255 chuỗi độ dài 0..7 trên `{a,b}` bằng tập kết quả, nên không phụ thuộc thứ tự sinh. Còn kiểm tra không lặp, mọi đoạn không rỗng/đối xứng và ghép lại đúng nguồn. Chuỗi 16 chữ `a` phải có 32768 kết quả hợp lệ, khác nhau; đây là toàn bộ số mặt nạ có thể có. Test trả mã 1 khi sai, không phụ thuộc `assert` hay `NDEBUG`.

## Bài tập

1. Chỉ đếm số cách tách mà không liệt kê: thay quay lui bằng DP theo vị trí để tiết kiệm bộ nhớ kết quả.
2. Chỉ trả cách tách có ít đoạn nhất; trạng thái/truy vết cần thêm gì?
3. Bỏ bảng đối xứng rồi kiểm tra từng đoạn trực tiếp: thời gian thay đổi ra sao và khi nào đánh đổi này có ích?
