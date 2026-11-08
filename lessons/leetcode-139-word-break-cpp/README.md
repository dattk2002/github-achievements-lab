# LeetCode 139 — Tách chuỗi thành các từ trong từ điển

Nguồn công khai: [LeetCode 139: Word Break](https://leetcode.com/problems/word-break/). Độ khó: Medium. Đối chiếu nguồn ngày **2026-11-08**. Đây là bài C++17 bổ sung theo yêu cầu, không gán nhãn Daily. Tóm tắt, lời giải, ví dụ và giải thích được tự viết.

## Hợp đồng

`bool lab::Solution::wordBreak(std::string s, std::vector<std::string>& wordDict)` trả liệu có thể ghép toàn bộ s từ các từ trong từ điển, đúng thứ tự ký tự, không bỏ hoặc thêm ký tự. Một từ được dùng nhiều lần; không có giới hạn 0/1 theo mục từ. Hàm không sửa từ điển; chuỗi s nhận theo giá trị như giao diện gốc.

Bài gốc: s dài 1..300, từ điển có 1..1000 từ phân biệt, mỗi từ dài 1..20; mọi ký tự là chữ thường tiếng Anh. Các điều kiện này là tiền điều kiện, không kiểm tra lại. Bản này mở rộng chuỗi rỗng thành `true` (ghép 0 từ), và từ điển rỗng chỉ ghép được chuỗi rỗng. Không dùng từ rỗng trong hợp đồng.

## Quy hoạch động theo tiền tố và chứng minh

`reachable[end]` cho biết có thể tách tiền tố `[0,end)` hay không. Khởi tạo `reachable[0]=true`. Với mỗi end từ 1 tới n, thử từng từ w: nếu độ dài w không vượt end, tiền tố trước nó đạt được và đoạn s kết thúc tại end bằng w, đánh dấu end đạt được.

Nếu đánh dấu end, một cách tách hợp lệ của tiền tố ngắn hơn cộng thêm w tạo cách tách hợp lệ của tiền tố hiện tại. Ngược lại, mọi cách tách một tiền tố không rỗng đều có từ cuối cùng w; phần trước w phải là một tiền tố đạt được đã tính, vì từ dài ít nhất 1. Quy nạp theo end chứng minh cả hai chiều. Đáp án là `reachable[n]`.

Dùng `std::string::compare` trên đoạn của s để tránh tạo một chuỗi con mới trong mỗi lần thử. Không chọn tham lam từ dài nhất: với `cars` và `{car, ca, rs}`, chọn `car` sẽ kẹt, còn `ca|rs` thành công. Mảng DP giữ đủ các vị trí bắt đầu khả thi.

Với n ký tự, D từ và chiều dài từ tối đa L, thời gian xấu nhất O(nDL), vì so một từ có thể tốn O(L). Chính xác hơn có thể chặn bởi O(n × tổng độ dài các từ) khi từ điển không rỗng. Từ điển rỗng chỉ tốn O(n) cho mảng và vòng lặp. Bộ nhớ phụ O(n+1), gồm DP và bản sao tham số s; không sao chép từ điển.

## Ví dụ chạy được

Lưu thành `/tmp/word-break-example.cpp`, chạy từ gốc repo:

```cpp
#include "lessons/leetcode-139-word-break-cpp/lesson.hpp"
#include <iostream>
int main() {
    std::vector<std::string> words{"grid", "path"};
    lab::Solution solution;
    std::cout << std::boolalpha << solution.wordBreak("gridpathgrid", words) << '\n';
    std::cout << solution.wordBreak("gridpaths", words) << '\n';
}
```

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -I. /tmp/word-break-example.cpp -o /tmp/word-break-example
/tmp/word-break-example
```

Kết quả:

```text
true
false
```

Ca đầu dùng từ `grid` hai lần; ca sau thừa ký tự `s`.

## Kiểm thử và ca biên

```sh
g++ -std=c++17 -Wall -Wextra -Werror -pedantic -DNDEBUG lessons/leetcode-139-word-break-cpp/test.cpp -o /tmp/word-break-test
/tmp/word-break-test
make test-all
```

Oracle đệ quy thử mọi vị trí cắt rồi tra `set` từ điển, không dùng mảng DP của lời giải. Đối chiếu 255 chuỗi nhị phân dài 0..7 với toàn bộ 64 tập con của `{a,b,aa,ab,ba,bb}` (16320 ca). Có ca tham lam sai, dùng lại từ, không có cách tách, chuỗi/từ điển rỗng; thêm chuỗi dài 300, từ dài 20 và từ điển đúng 1000 từ phân biệt. Test kiểm tra từ điển không đổi và dùng `exit(1)` khi sai, không dựa vào `assert`.

## Bài tập

1. Trả một cách tách bằng cách lưu từ cuối hoặc vị trí tiền nhiệm cho mỗi tiền tố đạt được.
2. Nếu một từ chỉ được dùng tối đa một lần, vì sao chỉ vị trí end không đủ làm trạng thái?
3. So sánh duyệt từ điển hiện tại với dùng trie để dò các từ bắt đầu tại từng vị trí.
