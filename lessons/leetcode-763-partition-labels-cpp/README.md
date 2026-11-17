# LeetCode 763 — Partition Labels (C++17)

Nguồn: [Partition Labels trên LeetCode](https://leetcode.com/problems/partition-labels/),
độ khó Medium. Lời giải, ví dụ và phần giảng giải được tự viết.

## Hợp đồng

`lab::Solution::partitionLabels(const std::string& text)` chia chuỗi
thành **nhiều đoạn liên tiếp nhất**, sao cho mỗi chữ cái chỉ xuất hiện
trong một đoạn. Trả độ dài các đoạn theo thứ tự từ trái sang phải;
ghép lại phải được toàn bộ chuỗi ban đầu, không bỏ ký tự.

Nguồn có độ dài `1..500`, chỉ gồm chữ thường tiếng Anh `a..z`.
Giới hạn độ dài là tiền điều kiện không kiểm tra. Mở rộng: chuỗi rỗng
trả vector rỗng; byte ngoài `a..z`, gồm chữ hoa, byte null và byte cao,
gây `std::invalid_argument`. Kiểm tra bảng chữ cái trước khi dùng ký tự
làm chỉ số. Hàm nhận tham chiếu const, không sao chép hoặc sửa chuỗi.

## Tham lam theo lần xuất hiện cuối

Quét lần đầu để ghi vị trí cuối của mỗi chữ trong bảng 26 ô. Quét lần
hai, giữ `end` là vị trí xa nhất bắt buộc thuộc đoạn đang mở. Với mỗi
ký tự tại `i`, cập nhật `end = max(end, last[text[i]])`. Khi `i == end`,
mọi chữ đã gặp trong đoạn đều không còn xuất hiện phía sau, nên đóng
đoạn và bắt đầu đoạn mới ở `i+1`.

Chứng minh: một đoạn chứa ký tự tại `i` phải chứa cả lần xuất hiện cuối
của ký tự ấy, nên không được kết thúc trước biên `end`. Nếu đang quét
thêm một chữ có lần cuối xa hơn, biên lại phải mở rộng. Lúc tới `end`,
không chữ trong đoạn còn ở bên phải: cắt tại đây hợp lệ và là điểm cắt
sớm nhất có thể. Cắt sớm nhất không làm mất cách chia phần còn lại,
nên lặp lại cho số đoạn tối đa. Bảng chữ cuối không phải số lần xuất
hiện; chỉ đếm tần suất sẽ không biết được điểm cắt.

Ví dụ `abacddce`: đoạn `aba` dài 3 phải giữ cả hai chữ `a`. Đoạn tiếp
theo mở ở `c`, kéo tới chữ `c` cuối sau hai chữ `d`, thành `cddc` dài 4.
Đoạn cuối `e` dài 1. Kết quả là `[3,4,1]`.

## Độ phức tạp

Hai lượt quét và bước xác thực tốn `O(n+26)`, thường viết `O(n)`.
Bộ nhớ phụ `O(26)` ngoài kết quả `O(p)`, với `p <= 26` vì mỗi đoạn
phải chứa ít nhất một chữ cái riêng. Không dùng đệ quy hoặc bảng theo
mọi cặp vị trí.

## Ví dụ chạy được

Lưu thành `/tmp/lc763-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
int main() {
    for (int length : lab::Solution{}.partitionLabels("abacddce"))
        std::cout << length << ' ';
    std::cout << '\n'; // 3 4 1
}
```

Từ gốc repo:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-763-partition-labels-cpp /tmp/lc763-example.cpp -o /tmp/lc763-example
/tmp/lc763-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-763-partition-labels-cpp/test.cpp -o /tmp/lc763-test
/tmp/lc763-test
make test
make test-all
```

## Biên và kiểm thử

Oracle thử mọi tập vị trí cắt rồi loại trường hợp một chữ thuộc nhiều
đoạn, chọn phân hoạch có số đoạn lớn nhất. Đối chiếu 3.280 chuỗi dài
`0..7` trên `{a,b,c}`, không dùng bảng vị trí cuối làm oracle. Có thêm
500 ký tự giống nhau, chuỗi xen kẽ dài 500, đủ 26 chữ phân biệt, chữ
lặp ở hai đầu và byte không hợp lệ. Test báo sai bằng mã thoát khác 0,
không phụ thuộc `assert` nên vẫn hoạt động khi có `NDEBUG`.

## Bài tập

1. Trả các khoảng nửa mở `[begin,end)` thay vì độ dài.
2. Cho bảng chữ cái Unicode lớn hơn: thay bảng 26 ô bằng cấu trúc nào?
3. Nếu chỉ được đọc chuỗi một lần từ luồng, có thể đóng đoạn sớm chắc
   chắn không? Hãy chỉ ra thông tin còn thiếu.
