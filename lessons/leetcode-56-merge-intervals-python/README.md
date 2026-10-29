# Python — Gộp khoảng

Nguồn: [LeetCode 56 — Merge Intervals](https://leetcode.com/problems/merge-intervals/).
Đây là bài bổ sung theo yêu cầu, không phải Daily của ngày 29/10/2026.
Mã, ví dụ và giải thích được tự viết; không chép toàn bộ đề hoặc editorial.

## Hợp đồng

`merge_intervals(intervals)` nhận danh sách các khoảng **đóng** `[start, end]`,
mỗi đầu mút là số nguyên và `start <= end`. Hàm trả danh sách tăng dần các
khoảng đã gộp, không còn giao nhau. Hai khoảng chạm đầu mút cũng được gộp.
Hàm không sửa dữ liệu đầu vào; các hàng đầu ra cũng là các danh sách mới.
Bản học tập hỗ trợ thêm danh sách rỗng và đầu mút âm. Đầu vào sai hợp đồng
không được kiểm tra; không nên dùng như bộ xác thực dữ liệu bên ngoài.

```python
from solution import merge_intervals

print(merge_intervals([[9, 12], [2, 5], [4, 8], [8, 9], [3, 3]]))
# [[2, 12]]
```

## Ý tưởng và tính đúng

Sắp xếp khoảng theo đầu trái rồi duyệt từ trái sang phải. Nếu khoảng mới
bắt đầu sau đầu phải của khoảng cuối trong kết quả, nó mở một nhóm mới.
Nếu không, chỉ cần kéo đầu phải hiện tại ra xa hơn khi cần.

Sau mỗi bước, kết quả biểu diễn chính xác hợp của phần đã duyệt. Các nhóm
trước nhóm cuối không thể bị một khoảng tương lai nối lại: đầu trái tương
lai không nhỏ hơn đầu trái hiện tại. Vì vậy chỉ cần xét nhóm cuối.
Dùng `max` để một khoảng nằm hoàn toàn bên trong không làm nhóm bị co lại.

Thời gian **O(n log n)**; bộ nhớ phụ **O(n)** cho bản sắp xếp và kết quả.
Không dùng `intervals.sort()` để giữ nguyên thứ tự đầu vào.

## Chạy và kiểm thử

Từ thư mục gốc repo, với Python 3.9+:

```sh
make test-python
```

Kiểm thử có khoảng lồng nhau, chạm đầu mút, khoảng điểm, số âm, đầu vào
không theo thứ tự, tính độc lập của đầu ra và 10.000 khoảng rời nhau.
500 bộ ngẫu nhiên dùng oracle phủ điểm nguyên và nửa nguyên trên miền nhỏ,
thay vì lặp lại thuật toán sắp xếp rồi gộp.

## Tự luyện

1. Nếu khoảng là nửa mở `[start, end)`, điều kiện gộp cần thay đổi thế nào?
2. Thử tính tổng độ dài được phủ mà không liệt kê từng điểm.
3. Viết phiên bản tại chỗ và giải thích rõ hợp đồng về việc sửa đầu vào.
