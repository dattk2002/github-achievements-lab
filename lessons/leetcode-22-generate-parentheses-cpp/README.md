# LeetCode 22: Generate Parentheses — Sinh ngoặc bằng tiền tố hợp lệ

Nguồn: [LeetCode 22: Generate Parentheses](https://leetcode.com/problems/generate-parentheses/), Medium.
Bài bổ sung ngày **2026-11-28**, không phải nhãn Daily. Ví dụ, lời giải và giải thích tự viết.

## Hợp đồng

`lab::Solution::generateParenthesis(int n)` trả mọi chuỗi ngoặc tròn cân
bằng có đúng `n` cặp, không trùng nhau. Mỗi tiền tố có số ngoặc mở ít nhất
bằng số ngoặc đóng; cả chuỗi có hai số bằng nhau. Thứ tự output không quan
trọng. Tiền điều kiện `1 <= n <= 8`; không hứa xử lý số âm hay ngoài miền.
Trạng thái nằm trong lần gọi, nên dùng lại cùng một đối tượng là an toàn.

## Thuật toán

Lưu đường đi `path`, số ngoặc đã mở `opened` và đã đóng `closed`.
Chỉ thêm `(` nếu `opened < n`; chỉ thêm `)` nếu `closed < opened`.
Khi `closed == n`, sao chép `path` vào kết quả. Sau mỗi lần đệ quy, xóa ký
tự vừa thêm để trở lại trạng thái của nhánh cha.

Bất biến là `0 <= closed <= opened <= n`. Nó luôn đúng từ trạng thái rỗng
và được hai điều kiện rẽ nhánh bảo toàn. Không cần tạo mọi chuỗi độ dài
`2n` rồi mới loại chuỗi sai.

## Tính đúng đắn

Theo bất biến, không tiền tố nào đóng nhiều hơn mở. Khi `closed == n`,
bất biến buộc `opened == n`, nên chuỗi dài đúng `2n` và cân bằng.
Ngược lại, ký tự kế tiếp của bất kỳ chuỗi hợp lệ nào cũng được một trong
hai điều kiện cho phép. Đi theo từng ký tự của chuỗi đó sẽ đến một lá được
xuất. Mỗi đường đi là một chuỗi quyết định duy nhất, nên không bị trùng.

## Độ phức tạp

Gọi `C_n = binom(2n,n)/(n+1)` là số Catalan. Sao chép mỗi kết quả dài `2n`
tốn O(n), cho thời gian **O(n*C_n)** và bộ nhớ output **O(n*C_n)**.
Độ sâu đệ quy và đường đi tốn **O(n)** bộ nhớ phụ. Mỗi tiền tố hợp lệ đều
có thể mở rộng tới một kết quả, nên số nút của cây tìm kiếm không vượt
quá tổng độ dài các đường tới lá, cùng bậc cận trên nêu trên.

## Ví dụ tự xây dựng

Với hai cặp, có `'(())'` và `'()()'`. Không được sinh `')(()'` dù tổng
số ngoặc mở và đóng bằng nhau: ngay tiền tố đầu đã âm.

## Chạy ví dụ

Tại thư mục bài học:

```sh
cat > /tmp/lc22-example.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    for (const auto& text : lab::Solution{}.generateParenthesis(2))
        std::cout << text << '\n';
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/lc22-example.cpp -o /tmp/lc22-example
/tmp/lc22-example
```

Kết quả:

```text
(())
()()
```

## Kiểm thử và trường hợp biên

Với từng `n=1..8`, oracle liệt kê toàn bộ `2^(2n)` chuỗi nhị phân, ánh xạ
thành dấu ngoặc rồi lọc theo định nghĩa tiền tố cân bằng. So toàn bộ tập
chuỗi, tính duy nhất và số Catalan `1,2,5,14,42,132,429,1430`.

Cùng một `Solution` chạy từ `n=1` đến `8` rồi quay lại `1`; test bắt dữ liệu
cũ còn sót. Những lỗi cho đóng khi `closed == opened`, thiếu `pop_back` hoặc
dừng sớm đều làm tập kết quả khác oracle. Test không phụ thuộc thứ tự output.

## Bài tập tự luyện

1. Tính số chuỗi mà không liệt kê bằng quy hoạch động Catalan.
2. Chỉ sinh chuỗi có độ sâu lồng nhau không quá `k`; thêm bất biến nào?
3. Mở rộng tới hai loại ngoặc và giải thích tại sao chỉ đếm số lượng
   từng loại là chưa đủ để bảo đảm thứ tự đóng đúng.

## Chạy kiểm thử

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/lc22-test
/tmp/lc22-test
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/lc22-ndebug
/tmp/lc22-ndebug
```

Từ gốc repo chạy `make test` hoặc `make test-all`. Test dùng mã thoát lỗi,
không dùng `assert`, nên vẫn kiểm tra đầy đủ khi bật `NDEBUG`.
