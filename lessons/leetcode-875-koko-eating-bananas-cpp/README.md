# LeetCode 875: Koko Eating Bananas (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/koko-eating-bananas/). Độ khó: Medium.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::minEatingSpeed(std::vector<int>& piles, int h)` trả tốc độ
nguyên dương nhỏ nhất để ăn hết mọi đống trong nhiều nhất `h` giờ. Trong một
giờ chỉ ăn từ một đống, tối đa `speed` quả; nếu ăn hết sớm cũng không chuyển
sang đống khác trong giờ đó. Hàm không sửa mảng gốc.

Nguồn cho `1 <= n <= 10000`, `n <= h <= 1000000000`,
`1 <= piles[i] <= 1000000000`. Giới hạn kích thước, miền giá trị và cận trên
của `h` là tiền điều kiện. Mở rộng có kiểm tra: mảng rỗng hoặc `h < n` ném
`std::invalid_argument` vì mỗi đống không rỗng cần ít nhất một giờ.

## Tìm kiếm nhị phân trên đáp án

Với tốc độ `s`, số giờ cần là tổng `ceil(pile/s)`. Tính bằng phép chia nguyên
`(pile+s-1)/s`, chuyển `pile` sang `long long` trước khi cộng. Tổng giờ có thể
đến `10^13`, nên cũng dùng `long long`, không dùng phép chia số thực.

Tìm tốc độ đầu tiên khả thi trong `[1,max(piles)]`. Đặt
`mid = low + (high-low)/2`. Nếu tổng giờ không vượt `h`, giữ `high=mid`;
nếu chưa đủ nhanh, đặt `low=mid+1`. Dừng khi hai cận bằng nhau.

Ví dụ `[4,9,15]`, `h=8`: tốc độ 4 cần `1+3+4=8` giờ; tốc độ 3 cần
`2+3+5=10` giờ, nên đáp án là `4`.

### Vì sao đúng?

Khi tốc độ tăng, số giờ của mỗi đống không tăng, do đó tính khả thi đơn điệu.
Tốc độ `max(piles)` dùng đúng `n` giờ nên khả thi. Bất biến giữ tốc độ tối ưu
trong `[low,high]`. Nếu `mid` khả thi, đáp án không thể lớn hơn `mid`; nếu
không, mọi tốc độ nhỏ hơn hoặc bằng `mid` cũng không khả thi. Hai phép cập
nhật giữ bất biến và làm đoạn tìm kiếm ngắn đi. Lúc `low=high`, đó chính là
tốc độ khả thi nhỏ nhất.

## Độ phức tạp

Với `M=max(piles)`, thời gian `O(n log(M+1))`, bộ nhớ phụ `O(1)`; tối đa khoảng
30 lần quét khi `M <= 10^9`. Đáp án vừa `int`, còn tổng giờ dùng `long long`.

## Ví dụ chạy được

Lưu thành `/tmp/lc-875-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> piles{4,9,15};
    std::cout << lab::Solution{}.minEatingSpeed(piles,8) << '\n'; // 4
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-875-koko-eating-bananas-cpp /tmp/lc-875-example.cpp -o /tmp/lc-875-example
/tmp/lc-875-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-875-koko-eating-bananas-cpp/test.cpp -o /tmp/lc-875-test
/tmp/lc-875-test
make test
make test-all
```

## Biên và kiểm thử

Oracle thử tốc độ lần lượt từ 1, mô phỏng từng giờ bằng trừ số quả còn lại,
không dùng tìm kiếm nhị phân hoặc phép chia làm tròn của lời giải. Toàn bộ
1092 mảng dài `1..6` trên `{1,4,9}` được thử với mọi `h` từ `n` đến `sum+2`,
tổng 25331 trường hợp. Có ca kết quả cần làm tròn lên, một đống, tốc độ tối
thiểu 1, lỗi đầu vào, 10000 đống mỗi đống `10^9` với `h=n` và `h=10^9`.
Mỗi ca kiểm tra đầu vào giữ nguyên; test vẫn báo lỗi bằng mã thoát khác 0
khi bật `NDEBUG`.

## Bài tập

1. Chứng minh cận dưới `ceil(sum(piles)/h)` và dùng nó thu hẹp tìm kiếm.
2. Dừng sớm phép cộng giờ khi đã vượt `h`; giải thích vì sao không đổi đáp án.
3. Điều gì thay đổi nếu được ăn nhiều đống trong cùng một giờ?
