# C++ — Đoạn con ngắn nhất đạt tổng mục tiêu

Nguồn: [LeetCode 209 — Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/).
Đây là bài bổ sung ngày 30/10/2026, không phải LeetCode Daily.
Lời giải, ví dụ và kiểm thử được tự viết; không chép đề hoặc editorial.

## Hợp đồng

`lab::min_subarray_len(target, nums)` trả độ dài nhỏ nhất của một đoạn
liên tiếp có tổng **ít nhất** `target`, hoặc 0 nếu không có đoạn phù hợp.
`target` phải dương, mọi phần tử phải dương, và tổng toàn mảng phải nằm
trong miền `int64_t`. Không sửa đầu vào, không kiểm tra dữ liệu sai hợp
đồng. Bản học tập hỗ trợ thêm mảng rỗng và tổng vượt miền `int` 32 bit.

Ví dụ tự tạo: với `target = 9`, `nums = {2, 1, 5, 2, 8}`, đáp án là 2
nhờ đoạn `{2, 8}`; với `target = 8`, đáp án là 1 nhờ phần tử cuối.

## Cửa sổ trượt và tính đúng

Mở rộng mép phải để cộng một phần tử. Khi tổng đủ lớn, ghi nhận độ dài
rồi liên tục bỏ phần tử bên trái cho đến khi tổng không còn đủ.
Tất cả phần tử dương nên bỏ bên trái luôn làm tổng giảm, thêm bên phải
luôn làm tổng tăng. Mỗi cửa sổ hợp lệ được thu hẹp hết mức cho mép phải
đó. Những mép trái đã bỏ không cần xét lại: chúng đã cho một đoạn hợp lệ
ngắn hơn mọi đoạn tương lai có cùng mép trái. Do đó giá trị nhỏ nhất thu
được là đáp án toàn cục.

Mỗi phần tử được cộng và trừ nhiều nhất một lần: thời gian **O(n)**,
bộ nhớ phụ **O(1)**. Tổng dùng `int64_t`; chỉ số và độ dài dùng `size_t`.
Nếu cho phép số âm, bất biến đơn điệu không còn đúng và thuật toán này
không áp dụng được.

## Chạy và kiểm thử

Từ gốc repo, với compiler C++17, Python và Make:

```sh
make test-core
```

Ví dụ dùng helper trong một chương trình đặt cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
int main() {
    std::cout << lab::min_subarray_len(9, {2, 1, 5, 2, 8}) << '\n'; // 2
}
```

Test không dùng `assert`, nên vẫn hoạt động với `-DNDEBUG`. Có trường hợp
đúng bằng mục tiêu, không đạt được, đáp án 1, rỗng, 2.000 mảng ngẫu nhiên
so với oracle duyệt mọi đoạn, 100.000 phần tử và tổng lớn hơn 32 bit.

## Tự luyện

1. Trả thêm hai chỉ số biên của đoạn ngắn nhất, xử lý trường hợp hòa.
2. Giải bằng tổng tiền tố và tìm kiếm nhị phân O(n log n).
3. Tìm phản ví dụ khi đầu vào chứa số âm.
