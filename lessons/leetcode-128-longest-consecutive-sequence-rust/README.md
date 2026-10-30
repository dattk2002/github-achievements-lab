# Rust — Dãy số liên tiếp dài nhất

Nguồn: [LeetCode 128 — Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/).
Đây là bài bổ sung ngày 30/10/2026, không phải Daily. Mã, ví dụ, kiểm
thử và giải thích được tự viết; không chép toàn bộ đề hoặc editorial.

## Hợp đồng

`longest_consecutive(nums: &[i32]) -> usize` trả độ dài lớn nhất của một
tập giá trị liên tiếp, bất kể vị trí của chúng trong mảng. Số trùng chỉ
được tính một lần; mảng rỗng trả 0. Hàm mượn slice bất biến và không sửa
đầu vào. Bài gốc có tối đa 100.000 phần tử; bản học tập hỗ trợ toàn miền
`i32`, kể cả hai cực trị. Kết quả dùng `usize` cho độ dài; khi thích ứng
với chữ ký LeetCode có thể ép sang `i32` vì độ dài trong giới hạn 100.000.

Ví dụ tự tạo: `[9, 5, 7, 6, 6, -2, -1, 0]` trả 3. Có hai dãy đạt độ
dài đó là `5, 6, 7` và `-2, -1, 0`; đây không phải đoạn con liên tiếp
theo chỉ số trong mảng ban đầu.

## Hash set và tính đúng

Đưa các giá trị vào `HashSet` để loại trùng. Với mỗi giá trị x, chỉ bắt
đầu đếm tiến nếu x - 1 không có trong tập. Khi đó x là đầu một dãy tối
đại. Tăng dần cho đến giá trị đầu tiên không có trong tập. Mỗi dãy có
đúng một đầu, nên cách này liệt kê mọi dãy tối đại và không quét lại từ
từng phần tử bên trong dãy.

Phải duyệt **tập đã loại trùng**, không duyệt lại mảng gốc để tìm đầu:
nhiều bản sao của cùng một đầu dãy có thể gây quét lặp tốn kém.
`checked_sub` và `checked_add` xử lý biên `i32` mà không tràn hay nối sai
`i32::MAX` với `i32::MIN`.

Thời gian **O(n) kỳ vọng** khi thao tác hash trung bình O(1), không phải
cam kết O(n) trong mọi trường hợp xấu nhất. Bộ nhớ phụ **O(n)** cho cách
cài đặt này: dù tập chỉ có u giá trị khác nhau, `collect()` có thể dự
trữ dung lượng theo số phần tử n của slice đầu vào trước khi loại trùng.

## Chạy và kiểm thử

Từ gốc repo, với rustc 1.58+ (edition 2021) và Make:

```sh
make test-rust
# Hoặc: make test-rust RUSTC=/path/to/rustc
```

Ví dụ dùng trong chương trình đặt cạnh `solution.rs`:

```rust
mod solution;
fn main() {
    println!("{}", solution::longest_consecutive(&[5, 2, 4, 1, 3])); // 5
}
```

Không cần crate ngoài. 4 nhóm test gồm rỗng, số âm, trùng, cực trị `i32`,
1.000 mảng ngẫu nhiên so với oracle sắp xếp rồi loại trùng, dãy đảo thứ
tự dài 100.000 và nhiều số trùng. Oracle dùng hiệu `i64` để kiểm tra
tính liên tiếp, không dùng hash set.

## Tự luyện

1. Trả thêm giá trị đầu và cuối của dãy tốt nhất.
2. So sánh với thuật toán sắp xếp O(n log n) trong dữ liệu thực tế.
3. Thử API nhận luồng số: làm sao cập nhật đáp án mà không quét lại tất cả?
