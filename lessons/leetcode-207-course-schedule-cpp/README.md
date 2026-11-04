# LeetCode 207 — Phát hiện chu trình bằng sắp xếp topo

Nguồn công khai: [LeetCode 207: Course Schedule](https://leetcode.com/problems/course-schedule/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-04**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`bool lab::Solution::canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites)` trả liệu có thứ tự học hết mọi môn thỏa điều kiện tiên quyết. Mỗi cặp `{a, b}` nghĩa là phải học `b` trước `a`, biểu diễn cạnh có hướng `b -> a`. Hàm giữ nguyên danh sách đầu vào.

Theo bài gốc: `1 <= numCourses <= 2000`, có tối đa 5000 cặp, mỗi cặp đúng hai chỉ số trong `[0, numCourses)`, và các cặp không trùng nhau. Danh sách rỗng hợp lệ: mọi môn đều có thể học. Một môn tự yêu cầu chính nó tạo chu trình và trả `false`.

Bản này ném `std::invalid_argument` khi số môn không dương, cặp không có đúng hai phần tử hoặc chỉ số nằm ngoài miền. Không kiểm tra lại các cận trên hay tính duy nhất của cặp; hợp đồng về kích thước bảo đảm các bộ đếm `int` không tràn. Đầu vào sai cấu trúc không bị coi là một đồ thị có chu trình.

## Thuật toán Kahn và chứng minh

Xây danh sách các môn phụ thuộc trực tiếp vào từng môn, cùng `indegree` là số điều kiện tiên quyết chưa được gỡ. Ban đầu đưa **mọi** môn có indegree bằng 0 vào hàng đợi, gồm cả môn cô lập.

Mỗi lượt lấy một môn sẵn sàng khỏi hàng đợi, tăng số môn đã học và giảm indegree của các môn phụ thuộc nó. Môn nào vừa về 0 được đưa vào hàng đợi. Kết thúc trả `completed == numCourses`.

**Bất biến:** indegree của mỗi môn chưa học bằng số cạnh đi vào từ các môn chưa học; mọi môn trong hàng đợi không còn điều kiện chưa hoàn thành. Vì vậy mỗi môn được lấy ra đều có thể học hợp lệ.

Nếu học được hết, thứ tự lấy ra là một thứ tự hợp lệ. Nếu còn môn nhưng hàng đợi rỗng, mọi môn còn lại đều có ít nhất một cạnh đi vào từ phần còn lại. Lần ngược các cạnh trong đồ thị hữu hạn phải gặp lại một môn, tạo chu trình. Các môn trong chu trình không thể có môn đầu tiên được học. Do đó trả `false` chính xác khi không thể hoàn thành.

Phải tính mọi thành phần liên thông; chỉ bắt đầu từ môn 0 có thể bỏ sót chu trình ở thành phần khác. Dùng hàng đợi, không đệ quy, nên không gặp độ sâu call stack với chuỗi tiên quyết dài.

Độ phức tạp: O(V + E) thời gian và O(V + E) bộ nhớ phụ cho đồ thị, bộ đếm và hàng đợi. Mỗi môn vào hàng đợi tối đa một lần, mỗi cạnh được xét một lần khi gỡ.

## Ví dụ chạy được

Lưu thành `/tmp/course-example.cpp`, chạy từ gốc repo:

```cpp
#include "lessons/leetcode-207-course-schedule-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::vector<int>> prerequisites{{2, 0}, {2, 1}, {4, 2}};
    lab::Solution solution;
    std::cout << std::boolalpha << solution.canFinish(5, prerequisites) << '\n';
    prerequisites.push_back({0, 4});
    std::cout << solution.canFinish(5, prerequisites) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/course-example.cpp -o /tmp/course-example
/tmp/course-example
```

Kết quả:

```text
true
false
```

Ca thứ hai có chu trình `0 -> 2 -> 4 -> 0`. Môn 3 cô lập không ảnh hưởng chu trình này.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-207-course-schedule-cpp/test.cpp -o /tmp/course-test
/tmp/course-test
make test-all
```

Test dùng điều kiện và `exit(1)`, hoạt động khi có `NDEBUG`. Có đồ thị không cạnh, self-loop, nhiều thành phần với chu trình riêng, cấu trúc hình thoi, chuỗi 2000 môn và đồ thị không chu trình đúng 5000 cạnh. Vét cạn toàn bộ 4.165 đồ thị không có self-loop với 1..4 môn; oracle thử mọi hoán vị và kiểm tra mọi cặp tiên quyết, độc lập với Kahn. Kiểm tra loại ngoại lệ cho số môn không dương, cặp sai độ dài và chỉ số sai; mọi ca hợp lệ đều kiểm tra danh sách đầu vào không đổi.

## Bài tập

1. Trả thêm một thứ tự học hợp lệ, hoặc báo không có; vì sao thứ tự có thể không duy nhất?
2. Thay hàng đợi bằng min-heap để ưu tiên mã môn nhỏ nhất khi có nhiều lựa chọn; độ phức tạp đổi ra sao?
3. Viết DFS ba màu và giải thích vì sao gặp cạnh tới một môn đã hoàn thành khác với gặp cạnh tới môn đang trên đường DFS.
