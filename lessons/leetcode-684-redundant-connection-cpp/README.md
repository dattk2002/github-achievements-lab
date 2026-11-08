# LeetCode 684 — Tìm cạnh dư bằng cấu trúc hợp nhất tập hợp

Nguồn công khai: [LeetCode 684: Redundant Connection](https://leetcode.com/problems/redundant-connection/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-08**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`std::vector<int> lab::Solution::findRedundantConnection(std::vector<std::vector<int>>& edges)` trả cạnh cần bỏ để đồ thị còn là cây. Nếu có nhiều cạnh bỏ được, chọn cạnh xuất hiện **sau cùng trong thứ tự đầu vào**. Giữ nguyên danh sách đầu vào và thứ tự hai đỉnh của cạnh trả về.

Bài gốc: n bằng số cạnh, `3 <= n <= 1000`, các đỉnh được đánh số 1..n; mỗi cạnh đúng hai số `1 <= u < v <= n`, không lặp cạnh, đồ thị vô hướng liên thông. Vì có n đỉnh và n cạnh, đồ thị có đúng một chu trình. Bản này kiểm tra độ dài cạnh và miền chỉ số, ném `std::invalid_argument` khi sai; danh sách rỗng được mở rộng thành kết quả rỗng. Các cận còn lại, liên thông, không lặp và thứ tự u<v là tiền điều kiện, không được xác minh lại.

## DSU, bất biến và cách chọn cạnh cuối

Ban đầu mỗi đỉnh là một thành phần riêng. DSU lưu `parent` và kích thước thành phần. Hàm tìm gốc dùng path halving: nối một đỉnh lên ông của nó trong khi đi tới gốc. Khi ghép hai thành phần, gắn cây nhỏ vào cây lớn.

Duyệt cạnh theo thứ tự đầu vào. Nếu hai đầu thuộc hai gốc khác nhau, ghép chúng. Nếu cùng gốc, đã có một đường nối hai đầu bằng các cạnh trước đó; cạnh mới đóng chu trình, nên trả cạnh này.

Bất biến: trước mỗi cạnh chưa bị từ chối, hai đỉnh có cùng gốc khi và chỉ khi chúng đã được nối bởi các cạnh đã xử lý. Ghép hai thành phần duy trì bất biến; cạnh trong một thành phần tạo chu trình.

Trong đồ thị có đúng một chu trình, mọi cạnh trên chu trình đều có thể bỏ, còn cạnh ngoài chu trình là cầu nên không thể bỏ mà vẫn liên thông. Cạnh trên chu trình xuất hiện cuối cùng sẽ gặp các cạnh còn lại của chu trình đã có mặt, nên nó là lần đầu DSU phát hiện trùng gốc. Do đó trả lần phát hiện đầu tiên vẫn thỏa yêu cầu chọn **cạnh cuối trong chu trình**, không phải cạnh cuối toàn bộ danh sách. Sau chu trình có thể còn nhiều cạnh cầu.

Độ phức tạp khấu hao: O(n α(n)) thời gian với union by size và path halving, O(n) bộ nhớ phụ. α là hàm nghịch đảo Ackermann, tăng rất chậm; không cần xây danh sách kề trong lời giải.

## Ví dụ chạy được

Lưu thành `/tmp/redundant-example.cpp`, chạy từ gốc repo:

```cpp
#include "lessons/leetcode-684-redundant-connection-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::vector<int>> edges{{1,2}, {2,3}, {1,3}, {3,4}, {4,5}};
    lab::Solution solution;
    const auto answer = solution.findRedundantConnection(edges);
    std::cout << answer[0] << ',' << answer[1] << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/redundant-example.cpp -o /tmp/redundant-example
/tmp/redundant-example
```

Kết quả: `1,3`. Cạnh `{4,5}` đứng cuối danh sách nhưng là cầu, không phải đáp án.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-684-redundant-connection-cpp/test.cpp -o /tmp/redundant-test
/tmp/redundant-test
make test-all
```

Oracle thử bỏ từng cạnh và dùng BFS kiểm tra liên thông, chọn cạnh hợp lệ cuối cùng. Với n-1 cạnh còn lại, liên thông tương đương là cây. Test liệt kê mọi đồ thị đơn liên thông có n đỉnh/n cạnh với n=3..5, thử các thứ tự xoay và đảo của danh sách cạnh. Có cạnh cầu sau cạnh dư, danh sách rỗng, dữ liệu sai được hỗ trợ và chuỗi 1000 đỉnh cộng cạnh nối hai đầu. Mọi ca hợp lệ kiểm tra không sửa đầu vào; lỗi trả mã 1 cả khi có `NDEBUG`.

## Bài tập

1. Trả các cạnh của chu trình: DSU hiện tại có đủ thông tin đường đi không?
2. So sánh union by size với luôn gắn gốc thứ hai vào gốc thứ nhất trên một chuỗi thao tác xấu.
3. Nếu đồ thị có nhiều chu trình, yêu cầu bài toán và ý nghĩa của lần phát hiện đầu tiên phải thay đổi thế nào?
