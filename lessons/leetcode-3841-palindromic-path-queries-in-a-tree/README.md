# LeetCode 3841 — Truy vấn đường đi có thể sắp thành palindrome

- Nguồn: [Palindromic Path Queries in a Tree](https://leetcode.com/problems/palindromic-path-queries-in-a-tree/)
- Ngày bài Daily: **2026-10-29**. Độ khó: **Hard**.
- C++17, thư viện chuẩn; giao diện `lab::Solution::palindromePath`.

## Hợp đồng và tiền điều kiện

Trên cây vô hướng, mỗi đỉnh mang một chữ cái thường. Lệnh `update u c`
đổi chữ tại đỉnh `u`; lệnh `query u v` hỏi liệu các chữ trên đường đi duy nhất
nối hai đỉnh, **kể cả hai đầu**, có thể hoán vị thành palindrome hay không.
Trả về `std::vector<bool>` theo thứ tự các lệnh `query`; cập nhật không sinh
phần tử kết quả. Không cần chuỗi theo thứ tự đường đi vốn đã đối xứng.

Đầu vào hợp lệ: `1 <= n == s.size() <= 50000`, đúng `n-1` cạnh tạo thành cây,
chỉ số đỉnh thuộc `[0,n)`, các ký tự thuộc `a..z`, và từ 1 đến 50000 lệnh
đúng cú pháp trên. Hàm giả định các tiền điều kiện này, không kiểm tra đầu vào
sai. `edges` và `queries` nhận tham chiếu theo giao diện nguồn nhưng không bị
thay đổi; `s` truyền theo giá trị. Có thể gọi lại cùng một đối tượng `Solution`.

## Ý tưởng

Một tập chữ hoán vị được thành palindrome khi có **tối đa một** chữ xuất hiện
số lần lẻ: các chữ khác ghép thành từng cặp đối xứng, chữ lẻ nằm ở giữa.
Dùng mặt nạ 26 bit, bit `c-'a'` biểu diễn parity của chữ `c`. Ghép hai tập
chữ tương ứng phép XOR. Mặt nạ `m` có tối đa một bit bật khi
`(m & (m - 1)) == 0`. Kiểu `uint32_t` khiến phép trừ ở `m=0` được xác định.

Chọn gốc 0. Gọi `P(u)` là XOR các chữ từ gốc đến `u`, có chứa `u`.
Nếu `w = LCA(u,v)` thì mặt nạ đường đi là:

```text
P(u) XOR P(v) XOR bit(s[w])
```

Hai tiền tố triệt tiêu phần đường chung, kể cả `w`; thêm chữ hiện tại của
`w` đúng một lần để khôi phục đường đi cần hỏi. LCA được tính bằng bảng tổ
tiên nhảy `2^k` bước (binary lifting).

### Duy trì tiền tố sau cập nhật

Khi chữ ở `x` đổi từ `a` sang `b`, mỗi tiền tố của một đỉnh trong cây con
`x` đổi bởi `delta = bit(a) XOR bit(b)`; mọi tiền tố khác giữ nguyên.

1. DFS bằng ngăn xếp tường minh để tính `tin`, `tout`, tiền tố ban đầu và bảng
   tổ tiên. Mọi cây con là đoạn nửa mở `[tin[x], tout[x])`. Không đệ quy nên
   cây dây dài không làm tràn ngăn xếp lời gọi.
2. Fenwick lưu mảng hiệu XOR: cập nhật đoạn bằng cách XOR `delta` tại
   `tin[x]` và `tout[x]`. Khi `tout[x] == n`, điểm cuối nằm ngoài mảng và
   không cần ghi gì.
3. Tiền tố Fenwick đến `tin[u]`, XOR với tiền tố ban đầu của `u`, cho `P(u)`
   hiện tại. Sau cập nhật phải sửa cả `s[x]` để tính delta và chữ LCA về sau.

Bất biến Fenwick đúng lúc khởi tạo vì mọi delta bằng 0. Mỗi cập nhật tác
động chính xác các hậu duệ theo đoạn Euler, nên bất biến được giữ. Kết hợp
với công thức LCA và tiêu chuẩn số chữ lẻ chứng minh mọi kết quả trả về đúng.

## Độ phức tạp

Với `q` lệnh, tiền xử lý `O(n log n)`, mỗi cập nhật hoặc truy vấn
`O(log n)`; tổng `O((n+q) log n)` thời gian. Việc đọc chuỗi lệnh còn tốn
`O(L)` với `L` là tổng độ dài các lệnh. Bộ nhớ phụ `O(n log n)`, thêm
`O(q)` để chứa kết quả. Không đi lại toàn bộ đường đi mỗi khi hỏi.

## Ví dụ tự xây dựng, có thể chạy

```cpp
#include "lesson.hpp"
#include <iostream>

int main() {
    std::vector<std::vector<int>> edges{{0,1}, {1,2}, {2,3}};
    std::vector<std::string> commands{
        "query 0 3", "update 2 c", "query 0 3", "query 2 2"
    };
    lab::Solution solver;
    for (bool value : solver.palindromePath(4, edges, "aabb", commands))
        std::cout << std::boolalpha << value << '\n';
}
```

Kết quả: `true`, `false`, `true` trên ba dòng. Ban đầu có hai `a`, hai `b`
nên ghép cặp được; sau cập nhật thành `aacb`, hai chữ có số lần lẻ. Một đỉnh
luôn tạo được palindrome dù chữ của nó vừa đổi.

## Kiểm thử

Từ gốc kho chạy `make test`. Chạy riêng, kể cả khi tắt `assert`:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG \
  lessons/leetcode-3841-palindromic-path-queries-in-a-tree/test.cpp \
  -o /tmp/palindromic-path-test
/tmp/palindromic-path-test
```

Bộ kiểm thử dùng điều kiện và mã thoát thất bại, không dựa vào `assert`:

- Một đỉnh, chỉ cập nhật, cập nhật không đổi chữ, chữ `z` và đường hai đỉnh.
- LCA ở gốc hoặc bên trong nhánh, đường tổ tiên–hậu duệ, đảo hai đầu đường,
  đường chỉ có một đỉnh và chuỗi chỉ đối xứng sau hoán vị.
- 180 cây nhỏ với hạt giống cố định, mỗi cây 200 lệnh. Oracle độc lập dùng
  BFS tìm đường thực rồi đếm 26 chữ bằng số nguyên, không dùng LCA/Fenwick.
  Cùng đối tượng được gọi lại để bắt lỗi giữ trạng thái từ lần trước.
- Cây dây 50000 đỉnh với 50000 lệnh. Đổi gốc xen kẽ `a` và `z`: đường toàn
  cây có lần lượt hai chữ lẻ hoặc không có chữ lẻ. Kết quả suy ra trực tiếp
  từ số lượng ký tự, đồng thời kiểm tra giới hạn chiều sâu và số lệnh.

## Tự luyện

1. Vì sao bỏ chữ LCA trong công thức có thể sai ngay khi `u == v`?
2. Chứng minh hai điểm cập nhật của mảng hiệu XOR chỉ ảnh hưởng đoạn nửa mở.
3. Thay nhãn đỉnh bằng nhãn cạnh: công thức truy vấn phải đổi thế nào?
4. So sánh phương án này với heavy-light decomposition và cây đoạn XOR.
