# LeetCode 743 — Thời gian lan truyền bằng Dijkstra

Nguồn công khai: [LeetCode 743: Network Delay Time](https://leetcode.com/problems/network-delay-time/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-06**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`int lab::Solution::networkDelayTime(std::vector<std::vector<int>>& times, int n, int k)` trả thời điểm sớm nhất mọi đỉnh nhận được tín hiệu từ nguồn k, hoặc -1 nếu có đỉnh không tới được. Mỗi cạnh `{u,v,w}` **có hướng** u→v và mất w đơn vị thời gian. Tín hiệu lan song song; kết quả là lớn nhất của các khoảng cách ngắn nhất từ k, không phải tổng trọng số các cạnh. Hàm giữ nguyên `times`.

Bài gốc: `1 <= k <= n <= 100`, 1..6000 cạnh, mỗi cạnh đúng ba số, hai đỉnh khác nhau trong 1..n, `0 <= w <= 100`, không có cặp (u,v) trùng. Bản này ném `std::invalid_argument` khi n không dương, nguồn sai miền, cạnh sai độ dài/chỉ số hoặc trọng số âm. Các cận trên, tính khác nhau của hai đầu và không trùng cặp vẫn là tiền điều kiện, không kiểm tra lại. Mở rộng danh sách cạnh rỗng: n=1 trả 0, n>1 trả -1.

Với trọng số không âm có thể bỏ chu trình khỏi một đường ngắn nhất, nên một đường ngắn nhất cần tối đa n-1 cạnh và dài không quá 9900. Khoảng cách/candidate dùng `int` 32 bit an toàn trong cận bài; giá trị vô cực `max()/4` lớn hơn mọi khoảng cách cần xét. Không cộng vào vô cực vì chỉ đưa khoảng cách hữu hạn vào heap.

## Thuật toán và chứng minh

Xây danh sách kề. Khởi tạo khoảng cách nguồn bằng 0, các đỉnh khác vô cực. Min-heap chứa cặp `(khoảng cách, đỉnh)`. Lấy bản ghi nhỏ nhất; nếu nó không khớp khoảng cách mới nhất thì bỏ vì đã cũ. Nếu còn hiệu lực, thử nới lỏng từng cạnh: nếu đi qua đỉnh hiện tại rẻ hơn, cập nhật và thêm bản ghi mới.

Khi một bản ghi hiệu lực được lấy ra, khoảng cách của đỉnh đó đã tối ưu. Nếu còn đường rẻ hơn qua phần đồ thị chưa xử lý, đỉnh đầu tiên chưa xử lý trên đường ấy phải có khoảng cách không lớn hơn giá trị đang lấy, do mọi trọng số không âm; điều này mâu thuẫn với việc heap chọn nhỏ nhất. Do đó nới lỏng các cạnh duy trì đúng các ứng viên cho Dijkstra. Cạnh 0 và chu trình tổng 0 vẫn hợp lệ; chỉ cập nhật khi tốt hơn nghiêm ngặt nên không lặp vô hạn.

Không có decrease-key: một đỉnh có thể có nhiều bản ghi, và kiểm tra bản ghi cũ tránh duyệt lại danh sách kề vô ích. Cuối cùng, nếu có khoảng cách vô cực thì trả -1, ngược lại lấy lớn nhất trong các đỉnh 1..n. Không tính ô chỉ số 0 vốn không phải đỉnh.

Với V=n, E là số cạnh, heap dạng thêm bản ghi mới có tối đa O(E+1) bản ghi được tạo. Thời gian O((V+E) log(E+2)), bộ nhớ phụ O(V+E) cho danh sách kề, khoảng cách và heap. Với đồ thị đơn của bài gốc, E<=V(V-1), cũng có thể viết O((V+E) log(V+1)).

## Ví dụ chạy được

Lưu thành `/tmp/network-example.cpp`, chạy ở gốc repo:

```cpp
#include "lessons/leetcode-743-network-delay-time-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::vector<int>> edges{{1,2,8}, {1,3,1}, {3,2,1}, {2,4,2}};
    lab::Solution solution;
    std::cout << solution.networkDelayTime(edges, 4, 1) << '\n';
    std::cout << solution.networkDelayTime(edges, 4, 4) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/network-example.cpp -o /tmp/network-example
/tmp/network-example
```

Kết quả:

```text
4
-1
```

Từ 1, đường qua 3 tới 2 chỉ tốn 2, tốt hơn cạnh trực tiếp tốn 8; đỉnh 4 nhận lúc 4. Từ 4 không đi ngược được các cạnh có hướng.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-743-network-delay-time-cpp/test.cpp -o /tmp/network-test
/tmp/network-test
make test-all
```

Oracle Floyd–Warshall độc lập, đối chiếu mọi nguồn của 729 đồ thị ba đỉnh: mỗi trong sáu cạnh có hướng có thể vắng, trọng số 0 hoặc 3. Có bản ghi heap cũ, chu trình 0, nguồn là đỉnh cuối, đỉnh không tới được và danh sách cạnh rỗng. Chuỗi 100 đỉnh đạt khoảng cách 9900; đồ thị 6000 cạnh 0 kiểm tra cận số cạnh. Test kiểm tra ngoại lệ cho dữ liệu sai đã hỗ trợ và xác nhận không sửa đầu vào. Mọi lỗi trả mã 1 cả khi có `NDEBUG`.

## Bài tập

1. Lưu đỉnh trước để khôi phục đường đi ngắn nhất tới một đích cụ thể; nhiều đường bằng nhau cần quy tắc gì?
2. Nếu mọi trọng số chỉ là 0 hoặc 1, thay heap bằng deque ra sao để đạt O(V+E)?
3. Tạo phản ví dụ có trọng số âm làm hỏng lập luận Dijkstra và so sánh với Bellman–Ford.
