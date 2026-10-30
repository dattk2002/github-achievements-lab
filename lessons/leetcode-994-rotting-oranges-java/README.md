# Java — Cam thối và BFS nhiều nguồn

Nguồn: [LeetCode 994 — Rotting Oranges](https://leetcode.com/problems/rotting-oranges/).
Đây là bài bổ sung ngày 30/10/2026, không phải Daily. Mã, ví dụ, kiểm thử
và giải thích được tự viết; không sao chép toàn bộ đề hoặc editorial.

## Hợp đồng

`new Solution().orangesRotting(grid)` nhận lưới chữ nhật khác `null`,
các hàng khác `null`, giá trị ô là 0 (trống), 1 (cam tươi), 2 (cam thối).
Mỗi phút, cam thối lây qua bốn cạnh sang cam tươi kề nó. Trả số phút đến
khi không còn cam tươi, hoặc -1 nếu bất khả thi. Không có cam tươi thì
trả 0. Lưới tối đa 10 × 10 theo bài gốc; bản học tập hỗ trợ thêm lưới
rỗng hoặc không có cột. Hàm không sửa đầu vào; không xác thực dữ liệu
sai hợp đồng.

Ví dụ tự tạo: `{{2, 1, 1, 1, 2}}` cần 2 phút, vì hai nguồn lây đồng
thời từ hai đầu. `{{2, 0}, {0, 1}}` trả -1: chạm góc không truyền bệnh.

## Thuật toán và tính đúng

Đưa **tất cả** cam thối ban đầu vào hàng đợi, đếm số cam tươi. Mỗi lượt
BFS xử lý đúng một lớp: chụp lại `layerEnd = tail` trước khi lây. Cam vừa
bị lây được thêm sau ranh giới này nên chỉ lây tiếp ở phút sau, không
làm cả chuỗi bị thối ngay trong cùng một phút.

BFS nhiều nguồn thăm ô theo khoảng cách nhỏ nhất đến một nguồn. Một ô
được đánh dấu ngay lúc thêm vào hàng đợi, nên không bị đếm hai lần.
Lớp cuối cùng làm hết cam tươi chính là thời điểm cần tìm. Nếu hết hàng
đợi mà vẫn còn cam tươi, các ô đó không có đường đi từ bất kỳ nguồn nào.

Dùng bản sao lưới để đánh dấu và `int[]` làm hàng đợi; bộ nhớ và thời
gian đều **O(rows × columns)**. Mỗi ô vào hàng đợi nhiều nhất một lần.

## Chạy và kiểm thử

Từ gốc repo, với JDK 17+ có module `jdk.compiler` và Make:

```sh
make test-java
```

Ví dụ lời gọi:

```java
System.out.println(new Solution().orangesRotting(new int[][] {{2, 1, 1, 1, 2}})); // 2
```

Kiểm thử ném `AssertionError` trực tiếp, không cần `-ea`. Có nhiều nguồn,
một hàng/cột, cam bị cô lập, không còn cam tươi, lưới rỗng, kiểm tra không
sửa đầu vào, hai lưới 10 × 10 và 1.000 lưới ngẫu nhiên so với oracle mô
phỏng toàn lưới theo từng phút bằng bản sao, không dùng hàng đợi BFS.

## Tự luyện

1. Trả thêm thời điểm bị lây của từng ô.
2. Nếu mỗi loại ô có thời gian lây khác nhau, vì sao BFS lớp không đủ?
3. So sánh với bài đếm đảo: điểm khởi đầu và ý nghĩa một lớp BFS khác gì?
