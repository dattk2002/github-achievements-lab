# 05 — Kiểm tra ngoặc cân bằng bằng ngăn xếp

Bài `05-balanced-brackets` trong [curriculum](../../curriculum.json),
thực hiện trong lượt chạy bù ngày 01/11/2026. Bài phân biệt việc đếm đủ
số ngoặc với yêu cầu đóng đúng loại, đúng thứ tự lồng nhau.

## Hợp đồng

```cpp
bool lab::balanced_brackets(std::string_view text);
```

Chỉ ba loại `()`, `[]`, `{}` tham gia kiểm tra. Mọi byte khác đều được
bỏ qua, gồm chữ, khoảng trắng và byte null nếu chúng nằm trong độ dài
của `string_view`. Chuỗi rỗng hợp lệ. Hàm không sửa hay giữ lại đầu vào.
Mỗi ngoặc đóng phải khớp ngoặc mở gần nhất chưa được đóng; cuối chuỗi
không được còn ngoặc mở dư.

Đây là bộ kiểm tra chuỗi byte theo quy tắc trên. Nó không phân tích
chuỗi ký tự, escape hay comment của một ngôn ngữ lập trình: ngoặc nằm
giữa dấu nháy vẫn tham gia kiểm tra. Người gọi phải giữ vùng nhớ của
`string_view` tồn tại trong suốt lời gọi.

## Thuật toán và bất biến

Dùng `std::string pending` như một ngăn xếp chứa **ngoặc đóng đang chờ**.
Gặp `(` thì đẩy `)`; tương tự cho hai loại còn lại. Gặp ngoặc đóng,
ngăn xếp phải khác rỗng và đỉnh phải đúng ký tự đó, rồi mới lấy đỉnh ra.
Ký tự không phải ngoặc không làm thay đổi ngăn xếp.

Bất biến sau mỗi tiền tố hợp lệ: từ đáy đến đỉnh ngăn xếp là các ngoặc
đóng cần dùng cho những ngoặc mở chưa ghép, theo thứ tự lồng từ ngoài
vào trong. Do đó đỉnh phải được đóng trước. Sai loại hoặc ngăn xếp rỗng
khi gặp ngoặc đóng chứng minh ngay rằng chuỗi không hợp lệ. Nếu đọc
hết, chuỗi hợp lệ khi và chỉ khi không còn ngoặc nào đang chờ.

Chỉ đếm số ngoặc là chưa đủ: `([)]` có số lượng từng loại bằng nhau
nhưng đóng sai thứ tự. Không gọi `back()` hoặc `pop_back()` trên
ngăn xếp rỗng.

**Độ phức tạp:** `O(n)` thời gian theo phân tích khấu hao của thao tác
đẩy vào chuỗi; bộ nhớ phụ `O(d)` với `d` là độ sâu ngoặc lớn nhất,
xấu nhất `O(n)`. Cấu trúc lặp không tiêu tốn ngăn xếp lời gọi khi lồng sâu.
Cấp phát chuỗi vẫn chịu giới hạn bộ nhớ của môi trường.

## Ví dụ tự chạy

Đặt `example.cpp` cạnh `lesson.hpp`:

```cpp
#include "lesson.hpp"
#include <iostream>

int main() {
    std::cout << std::boolalpha;
    std::cout << lab::balanced_brackets("a{b[c(d)e]f}g") << '\n';
    std::cout << lab::balanced_brackets("([)]") << '\n';
    std::cout << lab::balanced_brackets(std::string_view("(\0]", 3)) << '\n';
}
```

Chạy `g++ -std=c++17 example.cpp -o /tmp/brackets-example` rồi
`/tmp/brackets-example`: kết quả `true`, `false`, `false`.
Độ dài tường minh trong ví dụ cuối bảo đảm `]` sau byte null vẫn được
đọc. Nếu chỉ tạo `string_view` từ con trỏ C không có độ dài, việc xác
định độ dài dừng tại byte null đầu tiên.

## Kiểm thử

Từ gốc repo: `make test`, hoặc chạy riêng:

```sh
g++ -std=c++17 -DNDEBUG -Wall -Wextra -Werror -pedantic lessons/05-balanced-brackets/test.cpp -o /tmp/brackets-test
/tmp/brackets-test
```

Các ca bao phủ rỗng, không có ngoặc, các nhóm nối tiếp, ngoặc lồng,
đóng dư, mở dư, sai loại, giao nhau, ký tự bỏ qua và byte null. Chuỗi
20.000 tầng kiểm tra cách xử lý lồng sâu bằng vòng lặp.

Để đối chiếu độc lập, kiểm thử lọc ký tự không phải ngoặc rồi liên tục
xóa các cặp kề nhau `()`, `[]`, `{}`; chuỗi hợp lệ phải rút về rỗng.
Cách tham chiếu này chậm hơn nhưng không dùng ngăn xếp. Nó được chạy
trên mọi chuỗi độ dài 0–6 từ bảng ký tự `()[]{}x`. Kiểm thử trả mã khác
0 khi sai, kể cả khi định nghĩa `NDEBUG`.

## Tự luyện

1. Nêu bất biến nếu ngăn xếp lưu ngoặc **mở** thay vì ngoặc đóng đang chờ.
2. Mở rộng kết quả để trả vị trí lỗi đầu tiên. Với ngoặc mở dư ở cuối,
   bạn muốn báo vị trí nào? Viết hợp đồng trước khi sửa mã.
3. Nếu chỉ kiểm tra một loại ngoặc `()`, khi nào có thể thay ngăn xếp
   bằng một bộ đếm? Vì sao cách đó chưa đủ với ba loại?
