# github-achievements-lab
Sandbox for co-authored pull requests and GitHub Discussions practice.

## C++ learning track

Mỗi bài học là một thay đổi hoàn chỉnh: mã C++17, kiểm thử chạy được và
giải thích tiếng Việt. Nội dung được tự viết để học thuật toán, kiểm thử và
quy trình Git; không sao chép hoặc tự nộp bài lên nền tảng luyện tập khác.

- [01 — Tìm kiếm nhị phân](lessons/01-binary-search/README.md)
- [Danh sách chủ đề và yêu cầu](curriculum.json)

Yêu cầu: GCC hoặc Clang hỗ trợ C++17, Python 3.9+, Git và Make.

```sh
make test
```

Lệnh trên biên dịch từng bài với cảnh báo được xem là lỗi, chạy kiểm thử
C++, rồi chạy các kiểm thử bảo vệ quy trình tự động.

## Daily workflow

Lượt chạy hằng ngày lúc **09:00 Asia/Ho_Chi_Minh** ưu tiên bài công khai từ
[LeetCode Daily](https://leetcode.com/problemset/), dự phòng bằng một bài chưa
hoàn thành trong `curriculum.json`. Hiện dùng C++17 để giữ bộ kiểm thử thống
nhất; có thể mở rộng ngôn ngữ khi có nhu cầu. Codex viết bài và kiểm thử; một lượt
Codex độc lập review trước khi công cụ tạo PR, đợi CI thành công và squash
merge. Commit giữ dòng đồng tác giả Codex. Tối đa một bài mỗi lượt, không tạo
thay đổi chỉ để đủ số PR hoặc contribution. Bài có link nguồn và ngày Daily,
nhưng lời giải, kiểm thử và giải thích được tự viết. Không chép toàn bộ đề,
editorial hay lời giải mẫu; không nộp lên LeetCode. Bài Premium, nguồn không
truy cập được hoặc bài đã làm sẽ dùng danh sách dự phòng. Không còn bài phù
hợp thì dừng.

Xem [hướng dẫn vận hành](automation/README.md) để kiểm tra, dừng lịch hoặc
xử lý một lượt bị lỗi. Công cụ chạy trên máy đã cài lịch: máy phải đang
bật, có mạng và còn đăng nhập Codex/GitHub CLI.

GitHub quyết định điều kiện và thời điểm cấp achievements. Có đồng tác
giả và PR được merge không phải cam kết huy hiệu sẽ cập nhật ngay.
