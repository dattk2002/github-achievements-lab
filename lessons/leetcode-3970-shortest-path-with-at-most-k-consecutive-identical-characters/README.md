# LeetCode 3970 — Đường đi ngắn nhất với giới hạn chữ liên tiếp

- Nguồn: [Shortest Path With At Most K Consecutive Identical Characters](https://leetcode.com/problems/shortest-path-with-at-most-k-consecutive-identical-characters/).
- Ngày Daily: **2026-10-30**; độ khó: **Medium**.
- C++17, thư viện chuẩn; giao diện `lab::Solution::shortestPath`.

## Hợp đồng và tiền điều kiện

Tìm tổng trọng số nhỏ nhất từ đỉnh `0` đến `n-1` trong đồ thị có hướng.
Khi đọc nhãn các đỉnh theo hành trình, kể cả hai đầu, mỗi đoạn chữ giống
nhau liên tiếp dài không quá `k`. Có thể đi lại đỉnh để đổi nhãn rồi quay
về. Trả `-1` nếu không có hành trình hợp lệ; nếu `n=1`, kết quả là `0`.

Giả định đầu vào hợp lệ, không kiểm tra dữ liệu sai:

- `1 <= n == labels.size() <= 50000`, nhãn thuộc `a..z`.
- `0 <= edges.size() <= 50000`; mỗi cạnh có đúng ba số `{u,v,w}`,
  `0 <= u,v < n`, `u != v`, `1 <= w <= 10000`.
- `1 <= k <= 50`. Cạnh song song không bị loại trừ.

Hàm nhận `edges` bằng tham chiếu nhưng không sửa nó; nhãn truyền theo giá
trị. Không lưu trạng thái giữa các lần gọi. Kiểu kết quả `int` giữ giao diện
nguồn; tính khoảng cách và cộng trọng số bằng `long long` để tránh tràn
trong các trạng thái trung gian.

## Thuật toán: Dijkstra trên trạng thái mở rộng

Chỉ biết đỉnh hiện tại chưa đủ: cùng đến `u`, một hành trình có đoạn cuối
ngắn hơn có thể đi tiếp trong khi hành trình rẻ hơn lại bị chặn.
Dùng trạng thái `(u,r)`, trong đó `r` là độ dài đoạn nhãn giống nhau ở cuối.
Nhãn cuối chính là `labels[u]`, nên không cần lưu thêm chữ.

1. Khởi tạo `dist[0][1]=0`: nhãn đỉnh xuất phát đã được tính một lần.
2. Với cạnh `u -> v` trọng số `w`, đặt `r'=r+1` nếu hai nhãn giống nhau,
   ngược lại đặt `r'=1`. Bỏ cạnh nếu `r'>k`.
3. Nếu `dist[u][r]+w` tốt hơn `dist[v][r']`, cập nhật và đưa vào heap nhỏ nhất.
4. Bỏ bản ghi heap cũ nếu chi phí không còn bằng khoảng cách đang lưu.
   Khi lấy ra trạng thái đích hợp lệ đầu tiên, trả chi phí đó.
5. Heap cạn mà chưa lấy ra đích thì trả `-1`.

### Vì sao đúng?

Mỗi hành trình hợp lệ trong đồ thị ban đầu sinh đúng một chuỗi trạng thái
bắt đầu ở `(0,1)`, với cùng tổng trọng số. Quy tắc chuyển trạng thái chỉ
cho phép những bước giữ giới hạn `k`; ngược lại, mỗi đường trong đồ thị
trạng thái mô tả một hành trình hợp lệ. Vì vậy hai bài toán tối ưu tương đương.
Mọi trọng số đều dương, nên Dijkstra chốt đúng khoảng cách khi lấy một bản
ghi còn hiệu lực ra khỏi heap. Đích có thể mang bất kỳ `r` nào; bản ghi đích
đầu tiên có chi phí nhỏ nhất trong tất cả các trạng thái đích.

Chu trình không nhất thiết vô ích: nhãn khác có thể đặt lại bộ đếm. Vì thế
không dùng một cờ `visited[u]` chung và không giới hạn hành trình thành
đường đơn trên các đỉnh gốc.

## Độ phức tạp

Đặt `m=edges.size()`. Có tối đa `nk` trạng thái và `mk` chuyển trạng thái.
Với heap lưu cả bản ghi cũ, thời gian là
`O(nk + m + (mk+1) log(mk+2))`, bộ nhớ phụ
`O(nk + m + mk)` gồm bảng khoảng cách, danh sách kề và heap.
Đây là cận xấu nhất; không tạo sẵn các cạnh của đồ thị mở rộng.

## Ví dụ tự xây dựng, chạy được

Với nhãn `"aaba"`, cạnh `0->1` giá 1, `1->2` giá 2,
`2->1` giá 2 và `1->3` giá 1, lấy `k=2`:

- Đi thẳng `0->1->3` tạo `"aaa"`, không hợp lệ.
- Đi `0->1->2->1->3` tạo `"aabaa"`, giá `1+2+2+1=6`, hợp lệ.
- Không có cách khác đến đích rẻ hơn: phải qua nhánh đổi nhãn trước khi
  dùng cạnh cuối. Ví dụ này yêu cầu thăm đỉnh 1 hai lần.

Chạy từ thư mục bài học:

```sh
cat > /tmp/demo-3970.cpp <<'CPP'
#include "lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::vector<int>> edges{{0,1,1},{1,2,2},{2,1,2},{1,3,1}};
    lab::Solution solution;
    std::cout << solution.shortestPath(4, edges, "aaba", 2) << '\n'; // 6
}
CPP
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/demo-3970.cpp -o /tmp/demo-3970
/tmp/demo-3970
```

## Kiểm thử

```sh
# Từ thư mục bài học; NDEBUG không vô hiệu hóa các kiểm tra.
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG test.cpp -o /tmp/test-3970
/tmp/test-3970
# Từ gốc kho mã:
make test
```

Các kiểm tra dùng so sánh tường minh và `EXIT_FAILURE`, không dùng `assert`.
Kết quả cố định được tính bằng tay: đồ thị rỗng, chiều cạnh, đếm nhãn đầu,
đúng/vượt giới hạn, đường vòng, hai bộ đếm tại cùng đỉnh, chu trình cần thiết,
cạnh song song, trọng số và bản ghi heap cũ. Có ca `k=50`, `n=50000`,
`m=50000`, trọng số 10000 và chuỗi xen kẽ cho tổng `499990000`.
Cũng kiểm tra không sửa cạnh và gọi lại cùng đối tượng.

250 đồ thị nhỏ với seed cố định được đối chiếu bằng oracle độc lập:
duyệt chi phí nguyên tăng dần, đánh dấu trạng thái đạt được ở đúng chi phí,
không dùng Dijkstra hay heap. Với trọng số từ 1 đến 3, chỉ cần xét đến
`3*(nk-1)`: đường tối ưu trong đồ thị trạng thái không lặp trạng thái vì
trọng số dương. Oracle kiểm tra cả đồ thị có chu trình và trường hợp vô nghiệm.

## Bài tập

1. Lưu trạng thái trước đó để khôi phục một hành trình tối ưu. Vì sao chỉ
   lưu đỉnh trước đó là chưa đủ?
2. Chứng minh khi nào một trạng thái có thể bị loại nếu cùng đỉnh đã có
   trạng thái vừa rẻ hơn vừa có bộ đếm nhỏ hơn.
3. Nếu mọi cạnh có trọng số 1, thay Dijkstra bằng BFS và phân tích lại
   thời gian, bộ nhớ.
