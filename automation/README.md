# Lịch học C++ với Codex

## Quyền và phạm vi

Lịch đã được chủ repo cho phép dùng tài khoản `dattk2002` để tạo và merge
PR cho bài học thực tế, tối đa một bài mỗi ngày lúc 09:00 giờ Việt Nam.
Ưu tiên bài công khai của LeetCode Daily đúng ngày, không trùng bài đã làm.
Nếu nguồn không truy cập được, bài Premium hoặc đã làm, dùng danh sách dự
phòng hữu hạn gồm 10 chủ đề C++. Không tự gia hạn danh sách dự phòng, nộp
bài lên dịch vụ khác hoặc thay đổi repo khác. Nguồn Daily là GraphQL công
khai của LeetCode, có thể đổi schema hoặc ngừng truy cập; lỗi sẽ được ghi
log và dùng phương án dự phòng. Chỉ đăng lời giải/kiểm thử/giải thích tự viết,
link nguồn và tóm tắt ngắn, không chép nguyên đề hoặc editorial.

`daily.py` là mã nguồn của bộ điều khiển. Bản được cài trên máy nằm tại:

```text
~/.local/share/github-achievements-lab/daily.py
~/.local/share/github-achievements-lab/sources.py
~/.local/share/github-achievements-lab/checkout/
~/.local/share/github-achievements-lab/state.json
```

Bản đã cài không tự thay thế từ repo; cập nhật bộ điều khiển cần được
kiểm tra lại rồi cài chủ động. Codex dùng phiên đăng nhập ChatGPT hiện có;
mỗi lượt có một phiên triển khai và một phiên review, tiêu thụ hạn mức
Codex của tài khoản. Không lưu token trong repo hay crontab.

## Các chốt kiểm tra

1. Khóa tiến trình để hai lượt không chạy đồng thời; tối đa một lượt merge/ngày.
2. Xác minh đúng tài khoản, mọi URL fetch/push của origin; `main` phải khớp
   chính xác với base vừa fetch. Kiểm tra lại toàn bộ diff so với base trước push.
3. Dừng khi có công việc dở, PR hằng ngày còn mở hoặc trạng thái lần trước chưa rõ.
4. Worker chỉ tạo ba file của bài đang chọn; cấm đổi workflow, bộ điều khiển,
   curriculum hoặc bài cũ. Worker không có mạng trong sandbox.
5. Chạy `make test` trong bubblewrap: repo chỉ đọc, không có thư mục home/token,
   không có mạng, `/tmp` tạm và PID namespace riêng, giới hạn bộ nhớ/kích thước
   file đầu ra. Máy chạy lịch cần Linux với bubblewrap và util-linux.
   Kiểm tra diff và review độc lập ở chế độ chỉ đọc.
6. Ghi trạng thái trước khi push/tạo PR/merge; một thao tác ghi chỉ được gọi một lần.
7. Chờ CI thành công trên đúng commit, kiểm tra base chưa đổi rồi merge với
   `--match-head-commit`. Nếu base đổi thì dừng để kiểm tra lại.
8. Giữ trailer Codex trong squash commit và xác minh PR thực sự `MERGED`.

Nếu một bước lỗi hoặc hết thời gian, giữ nguyên checkout, branch, PR và
trạng thái để kiểm tra. Lượt sau không tự phát lại thao tác ghi chưa rõ kết quả.
Không dùng `git reset --hard` hay tự động xóa công việc.

## Kiểm tra mà không tạo PR

```sh
python3 ~/.local/share/github-achievements-lab/daily.py --check
crontab -l
```

`--check` có thể tạo thư mục trạng thái và file khóa cục bộ, nhưng không sửa
repo, tạo PR hay gọi Codex. Checkout chưa cài thì chỉ in thông báo.

## Dừng lịch

Chạy `crontab -e`, xóa dòng có nhãn `github-achievements-lab-daily`.
Các cron job khác phải được giữ nguyên. Máy tắt lúc 09:00 thì cron bỏ lỡ
lượt đó; không chạy bù hàng loạt.

## Xử lý lượt bị dừng

Xem `daily.log`, `YYYY-MM-DD-implementation.log`, `YYYY-MM-DD-review.log`
và `state.json` trong thư mục trạng thái. Kiểm tra PR/branch trên GitHub
trước khi quyết định tiếp tục; không xóa trạng thái rồi chạy lại một cách
mù quáng. Mã nguồn và kiểm thử được bảo toàn để người dùng hoặc Codex
trong phiên có giám sát sửa tiếp. Không tự thêm bài khác khi còn bài dở.
