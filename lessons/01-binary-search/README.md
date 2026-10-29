# 01 — Tìm kiếm nhị phân: tìm lần xuất hiện đầu tiên

## Mục tiêu

Tìm vị trí đầu tiên của một giá trị trong vector số nguyên **đã sắp xếp tăng dần**.
Nếu không tìm thấy, trả về `std::nullopt`. Vị trí bắt đầu từ 0.

```cpp
lab::binary_search_first({1, 2, 2, 2, 8}, 2); // 1
lab::binary_search_first({1, 2, 2, 2, 8}, 3); // std::nullopt
```

## Ý tưởng và bất biến

Giữ khoảng nửa mở `[left, right)` chứa vị trí cần tìm. Nếu phần tử giữa nhỏ
hơn mục tiêu, bỏ nửa trái; ngược lại, thu hẹp về trái để giữ cơ hội tìm thấy
lần xuất hiện đầu tiên. Khi hai biên gặp nhau, kiểm tra vị trí đó có hợp lệ
và chứa đúng mục tiêu hay không.

- Không truy cập `values[0]` khi vector rỗng.
- Dùng `left + (right - left) / 2` để tránh cộng trực tiếp hai chỉ số lớn.
- Không trừ 1 từ chỉ số không dấu ở biên trái.
- Không tự sắp xếp đầu vào: sắp xếp sẽ đổi chỉ số và tốn thêm thời gian.

**Độ phức tạp:** `O(log n)` thời gian, `O(1)` bộ nhớ phụ.

## Chạy kiểm thử

Tại thư mục gốc repo, chạy `make test`. Bài này kiểm tra đầu vào rỗng,
một phần tử, hai biên, giá trị âm, phần tử trùng và số nguyên cực trị.
Ngoài các ví dụ cụ thể, kiểm thử còn đối chiếu với `std::find` trên mọi
vector độ dài tối đa 6 sinh từ các giá trị `{-1, 0, 1}` rồi sắp xếp.

## Tự luyện

1. Vì sao trả về ngay khi gặp `values[middle] == target` có thể sai yêu cầu?
2. Thay điều kiện để tìm vị trí cuối cùng; viết ví dụ có thể phân biệt hai hàm.
3. Nếu dữ liệu chưa sắp xếp và chỉ tìm một lần, khi nào tìm kiếm tuyến tính hợp lý hơn?
