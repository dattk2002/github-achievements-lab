# LeetCode 785: Is Graph Bipartite? (C++17)

Nguồn: [bài công khai trên LeetCode](https://leetcode.com/problems/is-graph-bipartite/). Độ khó: Medium.
Diễn giải, ví dụ, lời giải và kiểm thử được viết riêng cho bài học.

## Hợp đồng

`lab::Solution::isBipartite(std::vector<std::vector<int>>& graph)` trả `true`
nếu chia được các đỉnh thành hai nhóm sao cho mỗi cạnh nối hai nhóm khác
nhau. Đầu vào là danh sách kề với chỉ số đỉnh `0..n-1`, có thể không liên
thông. Các đỉnh cô lập được phép ở một trong hai nhóm. Hàm giữ nguyên đồ thị.

Theo nguồn: `1 <= n <= 100`, đồ thị vô hướng, không tự khuyên, không lặp hàng
xóm, mọi chỉ số hàng xóm hợp lệ. Số đỉnh, tính vô hướng và tính đơn là tiền
điều kiện không được kiểm tra. Mở rộng: đồ thị rỗng trả `true`; tự khuyên
trả `false`. Chỉ số hàng xóm âm hoặc `>=n` được kiểm tra trên toàn đồ thị
trước BFS và ném `std::invalid_argument`; không sửa đầu vào.

## BFS tô hai màu cho mọi thành phần

Khởi tạo màu mỗi đỉnh là `-1` (chưa tô). Với **mỗi** đỉnh chưa tô, bắt đầu
một BFS mới, tô màu 0 rồi đưa vào hàng đợi. Khi xét cạnh `(u,v)`:

- Nếu `v` chưa tô, gán `color[v]=1-color[u]` và đưa vào hàng đợi.
- Nếu `v` đã cùng màu `u`, trả `false` ngay.
- Nếu khác màu, cạnh đó đã hợp lệ.

Nếu duyệt xong mọi thành phần mà không gặp xung đột thì trả `true`.
Đồ thị hình sao có tâm 0 và các lá `1,2,3,4` tô được hai màu: tâm một nhóm,
các lá nhóm kia. Tam giác `0-1-2-0` thì không tô được hai màu.

### Chứng minh

BFS gán màu luân phiên theo cây duyệt. Trong một thành phần liên thông, màu
của đỉnh xuất phát quyết định màu của mọi đỉnh theo các cạnh cây; một cách tô
hai màu hợp lệ bất kỳ phải khớp cách tô này hoặc đảo toàn bộ hai màu. Vì vậy,
nếu gặp cạnh có hai đầu cùng màu, không có cách phân nhóm hợp lệ nào cho
thành phần đó. Ngược lại, nếu không có xung đột, mỗi cạnh đã được kiểm tra
và có hai đầu khác màu, nên màu đã gán trực tiếp tạo ra một phân hoạch hợp
lệ. Vòng lặp ngoài kiểm tra cả thành phần rời rạc và đỉnh cô lập, nên kết
luận đúng cho toàn đồ thị.

## Độ phức tạp

Thời gian `O(V+E)`, kể cả bước xác thực hàng xóm. Với đồ thị vô hướng, tổng
số mục danh sách kề là `2E`. Bộ nhớ phụ `O(V)` cho màu và hàng đợi; mỗi đỉnh
được đưa vào hàng đợi nhiều nhất một lần. Không dùng đệ quy.

## Ví dụ chạy được

Lưu thành `/tmp/lc-785-example.cpp`:

```cpp
#include "lesson.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<int>> graph{{1,2,3,4},{0},{0},{0},{0}};
    std::cout << std::boolalpha << lab::Solution{}.isBipartite(graph) << '\n'; // true
}
```

Từ gốc kho mã:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -Ilessons/leetcode-785-is-graph-bipartite-cpp /tmp/lc-785-example.cpp -o /tmp/lc-785-example
/tmp/lc-785-example
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-785-is-graph-bipartite-cpp/test.cpp -o /tmp/lc-785-test
/tmp/lc-785-test
make test
make test-all
```

## Biên và kiểm thử

Oracle thử mọi phân hoạch nhị phân của các đỉnh, kiểm tra trực tiếp mọi cạnh,
không dùng BFS hoặc tô màu lan truyền. Đối chiếu toàn bộ 33868 đồ thị vô hướng
đơn có `0..6` đỉnh. Các ca riêng gồm chuỗi 100 đỉnh, đồ thị hai phía đầy đủ
50x50 rồi thêm cạnh tạo chu trình lẻ, tam giác nằm trong thành phần khác,
đỉnh cô lập, tự khuyên mở rộng và chỉ số không hợp lệ. Mỗi ca kiểm tra đầu vào
không đổi; test vẫn báo lỗi bằng mã thoát khác 0 khi bật `NDEBUG`.

## Bài tập

1. Trả thêm hai nhóm đỉnh nếu tồn tại.
2. Dùng thông tin cha BFS để khôi phục một chu trình lẻ khi có xung đột.
3. So sánh BFS với DSU có lưu quan hệ chẵn/lẻ khi các cạnh được thêm dần.
