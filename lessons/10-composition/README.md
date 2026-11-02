# 10 — Composition: thay chính sách giảm giá

Một quầy thanh toán cần cộng giá các món rồi áp dụng phiếu giảm giá. Thay vì tạo lớp con cho từng loại phiếu, `Checkout` **chứa** một callable thực hiện chính sách. Đây là composition (kết hợp đối tượng).

## Hợp đồng và tiền điều kiện

```cpp
using lab::Cents;          // std::int64_t, đơn vị cent
using lab::DiscountPolicy; // std::function<Cents(Cents)>
// lab::Checkout checkout(policy); hoặc mặc định không giảm
// Cents checkout.total(const std::vector<Cents>& prices) const;
```

Giá mỗi món phải không âm, tổng phải biểu diễn được bằng `Cents`. Không dùng số thực nên cộng/trừ cent không gây sai số làm tròn. Chính sách nhận tổng trước giảm (`subtotal`), trả **số cent được giảm**, không phải số tiền còn trả. Giá trị trả về phải thuộc `[0, subtotal]`. Kết quả thanh toán bằng `subtotal - discount`.

- Callable rỗng: constructor ném `std::invalid_argument`.
- Giá âm hoặc giảm giá ngoài miền: `total` ném `std::invalid_argument`.
- Tổng vượt `std::numeric_limits<Cents>::max()`: ném `std::overflow_error`, kể cả khi định giảm toàn bộ.
- Giỏ hợp lệ: gọi chính sách đúng một lần, kể cả giỏ rỗng (subtotal bằng 0).
- Giỏ không hợp lệ: dừng tại lỗi đầu tiên khi duyệt, không gọi chính sách. Không cam kết ưu tiên lỗi âm nếu đã gặp tràn trước đó.
- Ngoại lệ từ callable được truyền ra ngoài. Callable tự chịu trách nhiệm tránh tràn trong phép tính riêng; checkout chỉ kiểm tra đầu vào và kết quả callable.

Giỏ rỗng được phép; phiếu cố định dương trên giỏ rỗng bị từ chối, không tự chặn về 0. Không có thao tác làm thay đổi vector giá.

## Thuật toán và tính đúng

Khởi tạo subtotal bằng 0. Với từng giá, từ chối số âm; trước khi cộng, kiểm tra `price > max - subtotal`. Do subtotal luôn trong `[0, max]`, phép trừ kiểm tra an toàn. Nếu không vượt ngưỡng, phép cộng vẫn nằm trong miền biểu diễn.

Bất biến: sau mỗi lượt, subtotal là tổng chính xác của phần giá đã duyệt và không âm. Khi hết vector, đây là tổng toàn giỏ. Gọi chính sách một lần rồi kiểm tra `0 <= discount <= subtotal`. Nhờ đó phép trừ cuối luôn an toàn và kết quả nằm trong `[0, subtotal]`. Không tính tổng trước rồi mới kiểm tra tràn: tràn số nguyên có dấu là hành vi không xác định trong C++.

Ví dụ tính tay: `800 + 625 = 1425` cent; phiếu 175 cent cho kết quả `1250`. Với chính sách `subtotal / 10`, giỏ `1000 + 239 = 1239` giảm 123 cent, còn `1116`; chia nguyên làm tròn xuống với số không âm.

## Sở hữu và vì sao không cần kế thừa

`Checkout` sở hữu `std::function` theo giá trị; constructor chuyển callable vào thành viên riêng. Lambda có capture theo giá trị mang theo bản sao dữ liệu: sửa biến phiếu bên ngoài sau khi tạo checkout không đổi phiếu đã lưu. Vector chỉ được mượn bằng tham chiếu const trong lúc gọi, không được lưu lại.

Capture bằng tham chiếu vẫn chỉ mượn đối tượng bên ngoài; người gọi phải giữ đối tượng đó sống đủ lâu. `const total` không đảm bảo chính sách thuần hoặc an toàn đa luồng: callable có thể có trạng thái hay tác dụng phụ. Không tự hoàn tác tác dụng phụ khi callable trả kết quả sai hoặc ném ngoại lệ.

Có thể tạo các checkout cùng kiểu với lambda không giảm, giảm cố định, hoặc giảm toàn bộ. Muốn đổi cấu hình, tạo checkout với callable khác; không cần setter. Quan hệ là “checkout có chính sách”, không phải “checkout là một loại chính sách”. Không có hành vi lớp cơ sở cần ghi đè nên không cần lớp cơ sở, hàm virtual hay cây kế thừa. `std::function` yêu cầu callable có thể sao chép trong C++17.

## Độ phức tạp

Với n món và chi phí gọi chính sách là T, thời gian O(n + T), bộ nhớ phụ khi tính tổng O(1), chưa tính tài nguyên do callable sử dụng. Lưu/copy callable có thể cấp phát và tốn chi phí theo dữ liệu capture; không coi mọi callable là O(1).

## Ví dụ chạy được

Lưu đoạn sau vào `/tmp/composition-example.cpp`, chạy lệnh từ gốc repo:

```cpp
#include "lessons/10-composition/lesson.hpp"
#include <iostream>

int main() {
    const lab::Checkout regular;
    const lab::Checkout coupon([](lab::Cents) { return lab::Cents{175}; });
    const lab::Checkout free([](lab::Cents subtotal) { return subtotal; });
    std::cout << regular.total({800, 625}) << '\n';
    std::cout << coupon.total({800, 625}) << '\n';
    std::cout << free.total({800, 625}) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/composition-example.cpp -o /tmp/composition-example
/tmp/composition-example
```

Kết quả:

```text
1425
1250
0
```

## Kiểm thử

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/10-composition/test.cpp -o /tmp/composition-test
/tmp/composition-test
make test
```

Test dùng kết quả tính tay, kiểm tra số lần gọi và loại ngoại lệ; không dùng `assert`, nên lỗi vẫn trả mã khác 0 khi có `NDEBUG`. Bao phủ không giảm, phiếu cố định, giảm toàn bộ, phần trăm làm tròn, capture theo giá trị, giỏ rỗng, giá 0, giá âm tới cực tiểu, callable rỗng, giảm âm/quá tổng, tổng đúng cực đại và vượt cực đại qua nhiều lần cộng. Kiểm tra cả việc không gọi chính sách nếu đầu vào lỗi và truyền ngoại lệ từ chính sách.

## Bài tập

1. Viết chính sách giảm 250 cent chỉ khi subtotal đạt 2000 cent. Tự tính kết quả tại 1999, 2000 và 2001.
2. Thiết kế giảm 15% làm tròn xuống mà không tính trực tiếp `subtotal * 15` có thể tràn. Chia thương và dư cho 100 trước khi nhân; chứng minh giới hạn từng phần.
3. Ghép hai phiếu: áp dụng độc lập trên tổng gốc hay tuần tự trên số còn lại? Viết hợp đồng trước, sau đó thêm test phân biệt hai cách và phát hiện tổng giảm vượt subtotal.
