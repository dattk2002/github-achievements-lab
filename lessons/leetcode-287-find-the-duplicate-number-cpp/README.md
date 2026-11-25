# LeetCode 287 — Find the Duplicate Number: tìm lối vào chu trình

Nguồn: [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/), Medium.
Bài bổ sung ngày **2026-11-25**. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::findDuplicate(std::vector<int>& nums)` trả giá trị duy nhất
xuất hiện nhiều hơn một lần. Có `n+1` phần tử, mỗi phần tử thuộc `[1,n]`,
`1 <= n <= 100000`. Giá trị lặp có thể xuất hiện hơn hai lần; một số giá
trị khác có thể vắng mặt. Hàm giữ nguyên vector, dùng O(1) bộ nhớ phụ.

Các điều kiện trên là tiền điều kiện. Không truyền vector rỗng, số ngoài
miền hay nhiều giá trị lặp khác nhau; hàm không xác minh những trường hợp
này. Giá trị cũng là chỉ số hợp lệ, nên không trừ `1` khi truy cập mảng.

## Xem mảng như đồ thị hàm

Đặt cạnh `i -> nums[i]` trên các đỉnh `0..n`. Mỗi đỉnh có đúng một cạnh
đi ra. Bắt đầu từ `0`, đường đi hữu hạn phải gặp lại một đỉnh, tạo một
đoạn đuôi rồi đi mãi trong chu trình. Không cạnh nào trỏ về `0`, vì giá
trị nhỏ nhất là `1`, nên đoạn đuôi có độ dài ít nhất một.

Đỉnh đầu chu trình có hai đỉnh trước khác nhau: một ở đuôi và một trong
chu trình. Vì cả hai cùng trỏ tới nó, chỉ số của đỉnh đó xuất hiện ít
nhất hai lần trong `nums`. Chỉ có một giá trị lặp theo hợp đồng, nên lối
vào chu trình chính là đáp án cần tìm.

## Hai pha Floyd

Pha 1 bắt đầu `slow = fast = 0`, dùng vòng `do/while` để bảo đảm có di
chuyển. Mỗi lượt `slow` đi một cạnh, `fast` đi hai cạnh. Sau khi vào chu
trình, khoảng cách tương đối thay đổi một cạnh mỗi lượt nên chúng gặp
nhau trong nhiều nhất một vòng chu trình.

Gọi độ dài đuôi là `mu`, chu trình là `lambda`, số bước của con trỏ chậm
khi gặp là `t`. Cả hai đã vào chu trình, và chênh lệch số bước bằng `t`
là bội của `lambda`. Pha 2 đặt `entry = 0`, giữ `slow` ở điểm gặp, rồi
cho cả hai đi một cạnh mỗi lượt. Sau `mu` bước, `entry` đến lối vào;
`slow` cũng đến đó vì `(t + mu - mu) mod lambda = 0`. Trước thời điểm này,
`entry` ở đuôi còn `slow` trong chu trình, nên không thể gặp sớm hơn.

Thời gian **O(n)**, bộ nhớ phụ **O(1)**. Chỉ đọc mảng; không sắp xếp,
đánh dấu âm hay tạo bảng tần suất trong lời giải chính.

## Ví dụ chạy được

`[2,4,1,3,4]` tạo đường `0 -> 2 -> 1 -> 4 -> 4`. Lối vào là `4`, cũng
là giá trị xuất hiện hai lần. Chạy tại thư mục bài học:

```sh
cat > /tmp/lc287-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<int> values{2,4,1,3,4};
    std::cout << lab::Solution{}.findDuplicate(values) << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc287-example.cpp -o /tmp/lc287-example
/tmp/lc287-example
```

Kết quả: `4`.

## Kiểm thử và trường hợp biên

Oracle đếm tần suất cho mọi mảng thuộc `[1,n]^(n+1)` với `n = 1..5`, chỉ
giữ các mảng có đúng một giá trị lặp. Có 5841 mảng hợp lệ, bao gồm cả các
giá trị lặp hơn hai lần. Mọi ca kiểm tra đầu vào không bị thay đổi.

Các ca lớn có `n = 100000`: đuôi dài dẫn tới chu trình một đỉnh, chu
trình dài, một hoán vị seed cố định và toàn phần tử bằng `n`. Các ca này
bắt lỗi trả luôn điểm gặp pha 1, khởi tạo sai và đệ quy quá sâu.

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc287-test
/tmp/lc287-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc287-ndebug
/tmp/lc287-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Test dùng mã thoát lỗi,
không dùng `assert`, nên vẫn có hiệu lực với `NDEBUG`.

## Bài tập tự luyện

1. Tìm một mảng mà điểm gặp pha 1 khác giá trị lặp.
2. Giải bằng tìm kiếm nhị phân trên miền giá trị và chứng minh O(n log n).
3. Nếu cho phép nhiều giá trị lặp khác nhau, lập luận nào còn đúng và
   phần hợp đồng nào cần được thay đổi?
