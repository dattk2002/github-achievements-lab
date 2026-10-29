# Java — Đếm đảo

Nguồn: [LeetCode 200 — Number of Islands](https://leetcode.com/problems/number-of-islands/).
Đây là bài bổ sung theo yêu cầu, không phải Daily. Lời giải, ví dụ và kiểm
thử được tự viết; không sao chép toàn bộ đề hoặc editorial.

## Hợp đồng

`new Solution().numIslands(grid)` đếm các nhóm ô `'1'` nối nhau qua **cạnh**.
Chạm góc không nối hai đảo. Đầu vào là mảng chữ nhật khác `null`, các hàng
khác `null`, chỉ chứa `'0'` hoặc `'1'`, tối đa 300 × 300. Bản học tập hỗ
trợ thêm mảng rỗng hoặc không có cột. Hàm không sửa đầu vào; dữ liệu sai
hợp đồng không được xác thực.

Ví dụ tự tạo:

```java
char[][] grid = {"11001".toCharArray(), "01001".toCharArray(), "00110".toCharArray()};
System.out.println(new Solution().numIslands(grid)); // 3
```

## Thuật toán và tính đúng

Duyệt từng ô. Khi gặp đất chưa thăm, tăng số đảo và dùng BFS đánh dấu toàn
bộ đất có thể tới được qua bốn hướng. Đánh dấu ngay khi **thêm vào hàng
đợi** để một ô không được thêm nhiều lần. Chỉ các ô thuộc cùng thành phần
liên thông mới được BFS này đánh dấu; mọi ô trong thành phần đều sẽ tới
được. Do đó mỗi đảo làm bộ đếm tăng đúng một lần.

Chỉ số một chiều `r * columns + c` giúp dùng hàng đợi `int[]` và mảng
`boolean[]`. Hàng đợi được dùng lại giữa các đảo. BFS tránh đệ quy sâu
trên một đảo lớn; mảng `visited` giữ nguyên nội dung lưới của người gọi.

Thời gian **O(rows × columns)**; bộ nhớ phụ **O(rows × columns)**.
Đừng bỏ kiểm tra biên cột khi di chuyển trên chỉ số một chiều: cuối một
hàng không nối với đầu hàng tiếp theo.

## Chạy và kiểm thử

Từ gốc repo, với JDK 17+ có module `jdk.compiler` và Make:

```sh
make test-java
```

Make gọi trình biên dịch qua module của JDK, bật `-Xlint:all -Werror`, rồi
chạy `Test`; không phụ thuộc việc `javac` có nằm trong PATH hay không.
Các kiểm tra ném `AssertionError` trực tiếp, nên không cần tùy chọn `-ea`.

Có trường hợp rỗng, một ô, chạm góc, một hàng/cột, kiểm tra không sửa dữ
liệu, 1.000 lưới ngẫu nhiên so với oracle gộp nhãn thành phần độc lập và
hai lưới 300 × 300 (toàn đất, bàn cờ 45.000 đảo).

## Tự luyện

1. Thêm yêu cầu trả diện tích đảo lớn nhất.
2. So sánh bộ nhớ khi được phép đánh dấu trực tiếp trên lưới đầu vào.
3. Nếu tám hướng đều được tính là kết nối, ví dụ chạm góc thay đổi ra sao?
