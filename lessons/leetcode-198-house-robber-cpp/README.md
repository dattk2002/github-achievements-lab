# LeetCode 198 — Tổng lớn nhất khi không chọn hai vị trí kề nhau

Nguồn công khai: [LeetCode 198: House Robber](https://leetcode.com/problems/house-robber/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-04**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::rob(std::vector<int>& nums)` trả tổng lớn nhất khi chọn các vị trí sao cho không có hai vị trí kề nhau cùng được chọn. Hàm không sửa đầu vào. Đây là dãy thẳng: hai đầu dãy không kề nhau như trong biến thể vòng tròn.

Bài gốc có `1 <= nums.size() <= 100` và `0 <= nums[i] <= 400`. Đáp án không vượt 20.000 nên dùng `int` 32 bit an toàn. Bản này mở rộng vector rỗng thành kết quả 0; các giá trị ngoài giới hạn gốc không được kiểm tra. Có thể không chọn vị trí nào, hữu ích khi mọi giá trị đều bằng 0.

## Quy hoạch động và chứng minh

Gọi `D(i)` là tổng tốt nhất trên `i` phần tử đầu tiên. Với giá trị `x` ở vị trí cuối của tiền tố, có hai lựa chọn:

- Không chọn `x`: giữ `D(i-1)`.
- Chọn `x`: vị trí liền trước không được chọn, nên tổng là `D(i-2) + x`.

Vì mỗi phương án hợp lệ thuộc đúng một trong hai trường hợp, `D(i) = max(D(i-1), D(i-2) + x)`. Hai trạng thái trước khi duyệt phần tử đầu đều bằng 0, biểu diễn tiền tố rỗng.

Mỗi vòng giữ `previous` và `two_back` tương ứng hai tiền tố trước. Tính `current` trước khi cập nhật hai biến, để không vô tình dùng trạng thái đã chứa phần tử liền trước. Quy nạp theo độ dài tiền tố chứng minh biến `previous` cuối cùng là đáp án. Không cần lưu phương án hay bảng DP toàn bộ khi chỉ hỏi tổng.

Lựa chọn tham lam ở từng cặp có thể bỏ mất tổ hợp tốt về sau. Với `{4, 9, 5, 8}`, chọn 9 rồi 8 được 17; chọn theo tổng ở các chỉ số chẵn chỉ được 9. DP xét được cả hai kiểu quyết định.

Độ phức tạp: O(n) thời gian, O(1) bộ nhớ phụ; vector rỗng xử lý O(1).

## Ví dụ chạy được

Lưu thành `/tmp/robber-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-198-house-robber-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{6, 11, 4, 9};
    lab::Solution solution;
    std::cout << solution.rob(nums) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/robber-example.cpp -o /tmp/robber-example
/tmp/robber-example
```

Kết quả: `20`, chọn hai vị trí chứa 11 và 9.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-198-house-robber-cpp/test.cpp -o /tmp/robber-test
/tmp/robber-test
make test-all
```

Kiểm tra bằng điều kiện và `exit(1)`, không dựa vào `assert`. Có vector rỗng, một/hai phần tử, toàn 0, chọn được hai đầu dãy, và các lựa chọn khiến cách tham lam sai. Với 3.280 dãy độ dài 0..7 trên tập `{0, 1, 3}`, oracle liệt kê mọi tập con, loại tập có hai bit kề nhau và tính tổng trực tiếp. Đây là cách kiểm chứng độc lập với công thức DP. Mảng 99 và 100 phần tử đều bằng 400 kiểm tra chiều dài lẻ/chẵn và cận đáp án. Mọi ca kiểm tra dữ liệu không đổi.

## Bài tập

1. Lưu lại các vị trí được chọn; điều gì phải thêm vào bộ nhớ và hợp đồng khi có nhiều phương án tối ưu?
2. Giải biến thể các vị trí tạo thành vòng tròn; vì sao không thể gọi nguyên hàm này rồi sửa riêng hai đầu?
3. Nếu cấm chọn hai vị trí có khoảng cách nhỏ hơn 3, công thức truy hồi cần đổi ra sao?
