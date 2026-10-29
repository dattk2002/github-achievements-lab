# Rust — Chờ ngày ấm hơn

Nguồn: [LeetCode 739 — Daily Temperatures](https://leetcode.com/problems/daily-temperatures/).
Đây là bài bổ sung theo yêu cầu, không phải Daily. Lời giải, ví dụ, giải
thích và kiểm thử được tự viết, không chép toàn bộ đề hoặc editorial.

## Hợp đồng

`daily_temperatures(temperatures: &[i32]) -> Vec<usize>` trả số ngày phải
chờ đến ngày đầu tiên trong tương lai có nhiệt độ **lớn hơn** ngày đang
xét. Không có ngày như vậy thì trả 0. Nhiệt độ bằng nhau không đủ điều
kiện. Hàm mượn một slice bất biến và không sửa dữ liệu của người gọi.

Bản học tập hỗ trợ cả đầu vào rỗng và toàn bộ miền `i32`; không tính hiệu
hai nhiệt độ nên tránh tràn số khi so sánh. LeetCode giới hạn 100.000
ngày và nhiệt độ 30–100. Để dùng chữ ký của nền tảng, có thể chuyển kết
quả bằng `.into_iter().map(|days| days as i32).collect::<Vec<i32>>()`:
khoảng chờ trong giới hạn đó luôn biểu diễn được bằng `i32`.

Ví dụ tự tạo:

```rust
mod solution;
use solution::daily_temperatures;

fn main() {
    println!("{:?}", daily_temperatures(&[65, 64, 64, 68, 63, 70]));
    // [3, 2, 1, 2, 1, 0]
}
```

## Ngăn xếp đơn điệu và tính đúng

Lưu chỉ số những ngày chưa tìm thấy ngày ấm hơn trong một `Vec<usize>`.
Nhiệt độ trên ngăn xếp không tăng từ đáy lên đỉnh. Khi gặp ngày mới, lấy
ra mọi ngày ở đỉnh lạnh hơn, điền khoảng chờ bằng hiệu chỉ số, rồi thêm
ngày mới vào ngăn xếp. Giữ lại các ngày có nhiệt độ bằng ngày mới.

Ngày được lấy ra không có ngày ấm hơn nào trước ngày hiện tại: nếu có,
nó đã được giải quyết khi duyệt ngày đó. Vì vậy ngày hiện tại là đáp án
gần nhất. Các ngày còn trong ngăn xếp sau vòng lặp không có đáp án và
giữ giá trị 0.

Mỗi chỉ số được thêm đúng một lần và lấy ra nhiều nhất một lần. Tổng
thời gian **O(n)** dù có vòng `while` lồng trong `for`; bộ nhớ phụ
**O(n)** cho kết quả và ngăn xếp. Dùng `usize` cho chỉ số và khoảng chờ;
`today - day` an toàn vì ngày đang chờ luôn nằm trước ngày hiện tại.

## Chạy và kiểm thử

Từ gốc repo, với Rust hỗ trợ edition 2021 (rustc 1.58+) và Make:

```sh
make test-rust
```

Không cần crate bên ngoài hoặc Cargo: Make biên dịch bằng `rustc --test`,
bật `-D warnings` và chạy test harness tích hợp. Có thể chỉ định compiler
riêng bằng `make test-rust RUSTC=/path/to/rustc`.

5 nhóm kiểm thử gồm nhiệt độ bằng nhau, tăng/giảm, rỗng, một phần tử,
giá trị biên `i32`, 1.000 mảng ngẫu nhiên có seed so với oracle duyệt
trực tiếp ngày tương lai, và hai trường hợp 100.000 ngày (tất cả bằng
nhau, chỉ ngày cuối nóng hơn). Assertion của Rust hoạt động cả khi tối ưu.

## Tự luyện

1. Nếu yêu cầu ngày có nhiệt độ lớn hơn **hoặc bằng**, sửa điều kiện nào?
2. Tìm khoảng chờ đến ngày lạnh hơn thay vì ấm hơn.
3. Thử giải bằng cách duyệt ngược, so sánh bất biến của ngăn xếp.
