# LeetCode 560 — Đếm đoạn con tổng k bằng tần suất tổng tiền tố

Nguồn công khai: [LeetCode 560: Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-05**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::subarraySum(std::vector<int>& nums, int k)` đếm số đoạn **liên tiếp, không rỗng** có tổng bằng k. Các đoạn khác chỉ số được tính riêng dù có cùng giá trị. Hàm giữ nguyên đầu vào.

Bài gốc: `1 <= nums.size() <= 20000`, `-1000 <= nums[i] <= 1000`, `-10000000 <= k <= 10000000`. Có tối đa n(n+1)/2 =200010000 đoạn, vừa `int` 32 bit. Dùng `long long` cho tổng tiền tố và khóa tra cứu. Bản này trả 0 cho mảng rỗng; không kiểm tra các cận còn lại. Không được cho đầu vào vượt cận rồi giả định kiểu kết quả vẫn đủ chứa mọi đoạn.

## Thuật toán và chứng minh

Gọi P[j] là tổng j phần tử đầu tiên, với P[0]=0. Tổng đoạn từ i tới j-1 là P[j]-P[i], bằng k khi P[i]=P[j]-k. Vì vậy khi biết tổng hiện tại, chỉ cần đếm có bao nhiêu tổng tiền tố **trước đó** bằng `prefix-k`.

Giữ bảng băm `frequency` ánh xạ mỗi tổng tiền tố sang số lần đã xuất hiện. Ban đầu đặt `frequency[0]=1` để đếm được đoạn bắt đầu từ chỉ số 0. Với mỗi phần tử: cộng vào tổng; cộng `frequency[prefix-k]` vào đáp án nếu khóa tồn tại; sau đó mới tăng `frequency[prefix]`.

**Bất biến:** trước khi ghi tổng hiện tại, bảng chứa đúng các tổng tiền tố ở vị trí kết thúc trước đó, mỗi lần xuất hiện là một vị trí bắt đầu riêng. Mỗi lần tìm thấy một tổng phù hợp tạo đúng một đoạn kết thúc ở phần tử hiện tại. Duyệt mọi vị trí kết thúc đếm mỗi đoạn đúng một lần. Ghi tổng hiện tại sau bước đếm loại đoạn rỗng, đặc biệt quan trọng khi k=0.

Không thể chỉ lưu sự tồn tại của một tổng: với nhiều số 0 hoặc các cặp triệt tiêu, một tổng xuất hiện nhiều lần và tạo nhiều đoạn hợp lệ. Sliding window điều chỉnh theo dấu tổng không phù hợp khi có số âm, vì mở rộng cửa sổ không nhất thiết làm tổng tăng.

Độ phức tạp: kỳ vọng O(n) thời gian với tra cứu/cập nhật bảng băm trung bình O(1), nhưng xấu nhất O(n²) nếu nhiều va chạm. O(n) bộ nhớ cho tối đa n+1 tổng tiền tố. `reserve` giảm tái cấp phát bảng, không biến giới hạn kỳ vọng thành bảo đảm xấu nhất.

## Ví dụ chạy được

Lưu thành `/tmp/subarray-count-example.cpp`, chạy tại gốc repo:

```cpp
#include "lessons/leetcode-560-subarray-sum-equals-k-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> nums{4, -4, 4, 0};
    lab::Solution solution;
    std::cout << solution.subarraySum(nums, 4) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/subarray-count-example.cpp -o /tmp/subarray-count-example
/tmp/subarray-count-example
```

Kết quả: `5`. Các đoạn chỉ số đóng là `[0,0]`, `[0,2]`, `[0,3]`, `[2,2]`, `[2,3]`.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-560-subarray-sum-equals-k-cpp/test.cpp -o /tmp/subarray-count-test
/tmp/subarray-count-test
make test-all
```

Oracle cộng trực tiếp từng đoạn O(n²). Vét cạn 19.531 mảng độ dài 0..6 trên `{-2,-1,0,1,2}` và mọi k từ -4 tới 4. Có ca triệt tiêu, một phần tử, số 0 và giữ nguyên dữ liệu. Mảng 20000 số 0 phải cho 200010000, bắt lỗi không giữ tần suất hoặc đếm đoạn rỗng. Mảng 20000 số 1000 với k=10000000, và tương tự số âm, đều có 10001 đoạn. Test trả mã 1 khi sai kể cả khi có `NDEBUG`.

## Bài tập

1. Thay đếm số đoạn bằng tìm đoạn dài nhất có tổng k: cần giữ tần suất hay vị trí nào của mỗi tổng?
2. Nếu cần bảo đảm O(n log n) xấu nhất, có thể thay cấu trúc nào cho bảng băm?
3. Với dữ liệu theo luồng và chỉ xét cửa sổ gần nhất, phải loại tổng tiền tố cũ ra khỏi bảng vào lúc nào?
