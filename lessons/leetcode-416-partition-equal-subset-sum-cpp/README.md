# LeetCode 416 — Chia thành hai tập có tổng bằng nhau

Nguồn công khai: [LeetCode 416: Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-05**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`bool lab::Solution::canPartition(std::vector<int>& nums)` trả liệu có thể chia các phần tử thành hai nhóm có tổng bằng nhau, mỗi phần tử thuộc đúng một nhóm. Mỗi bản sao là một phần tử riêng, nhưng không được dùng một phần tử nhiều lần. Hàm giữ nguyên đầu vào.

Bài gốc có `1 <= nums.size() <= 200`, `1 <= nums[i] <= 100`. Tổng không vượt 20000, dùng `int` 32 bit an toàn. Vì các số dương, hai nhóm có tổng bằng nhau khi mảng không rỗng sẽ tự động đều không rỗng. Bản này trả `false` cho mảng rỗng; các cận khác và điều kiện số dương là tiền điều kiện, không được kiểm tra lại. Số âm không thuộc bài toán này.

## Quy hoạch động 0/1 và chứng minh

Gọi tổng là S. Nếu S lẻ thì không thể chia đôi. Nếu chẵn, bài toán tương đương tìm một tập con có tổng T = S/2: phần bù của nó cũng có tổng T.

`reachable[s]` biểu diễn liệu có thể tạo tổng s bằng các phần tử đã xét. Ban đầu chỉ `reachable[0] = true`, tương ứng không chọn gì. Với mỗi giá trị v, duyệt s **giảm dần** từ T tới v và cập nhật `reachable[s] = reachable[s] || reachable[s-v]`.

Bất biến sau mỗi phần tử: mỗi tổng đánh dấu đúng khi có một tập con của tiền tố đã xét tạo được nó. Công thức xét hai khả năng: không chọn phần tử mới, hoặc chọn nó đúng một lần và ghép với tập con trước đó có tổng s-v. Duyệt giảm bảo đảm `reachable[s-v]` vẫn thuộc trạng thái trước phần tử hiện tại, vì s-v nhỏ hơn s. Duyệt tăng có thể tái dùng cùng phần tử và sẽ giải nhầm bài toán không giới hạn số lần chọn.

Khi kết thúc, `reachable[T]` trả đúng khả năng chia. Ví dụ `{1, 2, 5}` có T=4 nhưng không có tập con hợp lệ; dùng một phần tử 2 hai lần sẽ tạo đáp án sai.

Độ phức tạp: O(nT) thời gian, O(T) trạng thái bộ nhớ phụ, T <=10000. `std::vector<bool>` lưu các cờ dạng bit. Tính tổng ban đầu O(n); trường hợp tổng lẻ kết thúc sớm sau bước này.

## Ví dụ chạy được

Lưu thành `/tmp/partition-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-416-partition-equal-subset-sum-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> first{2, 5, 7, 10};
    std::vector<int> second{2, 3, 7};
    lab::Solution solution;
    std::cout << std::boolalpha << solution.canPartition(first) << '\n';
    std::cout << solution.canPartition(second) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/partition-example.cpp -o /tmp/partition-example
/tmp/partition-example
```

Kết quả:

```text
true
false
```

Ca đầu có `{2,10}` và `{5,7}`, cùng tổng 12.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-416-partition-equal-subset-sum-cpp/test.cpp -o /tmp/partition-test
/tmp/partition-test
make test-all
```

Oracle liệt kê mọi tập con bằng bitmask và so tổng được chọn với phần bù, độc lập với DP. Vét cạn 3.279 mảng độ dài 1..7 trên `{1,2,4}`. Có mảng rỗng, một phần tử, tổng lẻ, bản sao, và các ca bắt lỗi tái dùng phần tử `{1,2,5}`, `{2,3,7}`. Kiểm tra 200 số 100 chia được, nhưng 199 số 100 không tạo tổng 9950 dù tổng chẵn; thêm 200 số 1. Mọi ca xác nhận không sửa dữ liệu và dùng điều kiện trả mã lỗi thay vì `assert`.

## Bài tập

1. Trả lại hai nhóm chỉ số khi có cách chia; cần lưu thông tin nào để truy vết?
2. Nếu cho phép số âm, vì sao mảng DP từ 0 tới T không còn đủ? Đề xuất miền trạng thái khác.
3. Dùng phép dịch bit trên bitset để cập nhật tập tổng đạt được; so sánh theo số phép toán máy với DP từng tổng.
