# LeetCode 79: Word Search — Tìm đường không dùng lại ô

Nguồn: [LeetCode 79: Word Search](https://leetcode.com/problems/word-search/), Medium.
Bài bổ sung ngày **2026-11-28**, không phải nhãn Daily. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::exist(std::vector<std::vector<char>>& board, std::string word)`
cho biết có đường ghép đúng `word` hay không. Mỗi bước sang một ô chung
cạnh trên/dưới/trái/phải, không đi chéo, không dùng một ô hai lần trong
cùng đường. Phân biệt hoa/thường. Hàm giữ nguyên bảng cả khi tìm được từ.

Tiền điều kiện: bảng chữ nhật kích thước mỗi chiều `1..6`, từ dài `1..15`,
bảng và từ chỉ chứa chữ cái tiếng Anh hoa/thường. Không truyền bảng hoặc
từ rỗng; lời giải không xác minh đầu vào ngoài hợp đồng.

## Tỉa nhánh và tìm kiếm

Nếu từ dài hơn tổng số ô, trả `false`. Đếm ký tự trên bảng và trong từ:
thiếu bất kỳ ký tự nào thì không có đường. Hai phép kiểm tra này là điều
kiện cần, không đủ: vị trí kề nhau vẫn phải được kiểm tra.

Nếu ký tự cuối hiếm hơn ký tự đầu trên bảng, đảo bản sao của từ để thử từ
đầu hiếm hơn. Mọi đường hợp lệ đi ngược lại cũng hợp lệ, nên thao tác này
không đổi đáp án. Nó chỉ giảm một số nhánh, không đổi cận xấu nhất.

Từ mỗi ô, DFS khớp ký tự ở chỉ số hiện tại. Bỏ nhánh ngoài bảng, ô đã dùng
hoặc ký tự không khớp. Khi khớp ký tự cuối, thành công. Nếu chưa, đánh dấu
ô trong bảng `used` riêng, thử bốn hàng xóm, rồi xóa dấu **kể cả khi một
nhánh thành công**. Không ghi ký tự đánh dấu vào bảng đầu vào.

## Bất biến và tính đúng đắn

Khi tìm ký tự tiếp theo, các ô được đánh dấu chính là đường đang thử:
kề cạnh, khác nhau và khớp tiền tố của từ. Mỗi bước DFS bảo toàn bất biến.
Do thử mọi ô đầu và mọi bước kề hợp lệ, bất kỳ đường tồn tại nào cũng được
xét. Hoàn nguyên dấu sau khi quay lui cho phép một ô được thử lại ở nhánh
khác; đó là điều cần thiết, khác với cấm dùng lại trong một đường.

## Độ phức tạp

Đặt `R,C` là kích thước bảng, `L` là độ dài từ. Bước đầu có tối đa bốn
hướng, những bước tiếp theo không thể quay lại ô trước nên có tối đa ba.
Thời gian xấu nhất **O(R*C*3^L)**; tỉa nhánh tần suất không loại được cận
mũ. Bộ nhớ phụ **O(R*C + L)** cho bảng dấu, bản sao từ và stack đệ quy.

## Ví dụ tự xây dựng

Bảng hai hàng `CAT`, `RRE` có đường `C -> A -> T -> E -> R` cho từ `CATER`.
Với bảng một hàng `AB`, từ `ABA` không hợp lệ vì cần quay về ô `A` đã dùng.

## Chạy ví dụ

Tại thư mục bài học:

```sh
cat > /tmp/lc79-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::vector<char>> board{{'C','A','T'},{'R','R','E'}};
    std::cout << std::boolalpha << lab::Solution{}.exist(board, "CATER") << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc79-example.cpp -o /tmp/lc79-example
/tmp/lc79-example
```

Kết quả:

```text
true
```

## Kiểm thử và trường hợp biên

Oracle không dùng DFS: liệt kê các trạng thái đường theo từng độ dài,
mỗi trạng thái có ô cuối và bitmask ô đã dùng. Kiểm tra mọi hàng xóm bằng
khoảng cách Manhattan. Test đối chiếu **12348** cặp bảng/từ: mọi bảng nhị
phân kích thước từ `1x1` tới `2x3`, mọi từ nhị phân độ dài `1..6`.

Các ca cố định bắt việc dùng lại ô, đi chéo, phân biệt hoa/thường, phải
quay lui qua nhánh thất bại và từ dài hơn số ô. Bảng `6x6` và từ dài 15
kiểm tra giới hạn trên, có cả trường hợp thiếu ký tự. Mỗi ca gọi hai lần
và xác minh bảng không đổi sau cả kết quả `true` và `false`.

## Bài tập tự luyện

1. Bỏ hoàn nguyên `used` và tìm bảng nhỏ làm các nhánh sau thất bại sai.
2. Tạo bảng có đủ tần suất nhưng không có đường cho từ cần tìm.
3. Nếu tìm nhiều từ trên cùng bảng, Trie có thể chia sẻ công việc thế nào?

## Chạy kiểm thử

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc79-test
/tmp/lc79-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc79-ndebug
/tmp/lc79-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Test dùng mã thoát lỗi,
không dùng `assert`, nên vẫn kiểm tra đầy đủ khi bật `NDEBUG`.
