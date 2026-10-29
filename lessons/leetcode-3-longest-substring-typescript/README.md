# TypeScript — Chuỗi con không lặp

Nguồn: [LeetCode 3 — Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/).
Đây là bài bổ sung theo yêu cầu, không phải Daily. Mã, kiểm thử, ví dụ và
giải thích được tự viết, không sao chép toàn bộ đề hoặc editorial.

## Hợp đồng

`lengthOfLongestSubstring(s: string): number` trả độ dài lớn nhất của một
đoạn **liên tiếp** không chứa ký tự trùng. Chuỗi rỗng cho kết quả 0.
Bài gốc dùng chữ tiếng Anh, chữ số, dấu và khoảng trắng; bản học tập mở
rộng sang Unicode và đếm **code point**, không đếm UTF-16 code unit hay
cụm ký tự hiển thị (grapheme cluster). Vì thế `😀` dài 1, còn `e` kèm dấu
sắc kết hợp `\u0301` là 2 code point. Hàm không chuẩn hóa Unicode.

Ví dụ tự tạo:

```typescript
import { lengthOfLongestSubstring } from './solution.mts';

console.log(lengthOfLongestSubstring('ab!c!d')); // 4, đoạn 'ab!c'
console.log(lengthOfLongestSubstring('😀a😀b')); // 3, đoạn 'a😀b'
```

## Thuật toán và tính đúng

Dùng cửa sổ trượt `[left, right]` và `Map` lưu vị trí gần nhất của mỗi
code point. Nếu ký tự hiện tại đã xuất hiện tại `previous`, cập nhật
`left = max(left, previous + 1)`. Phép `max` rất quan trọng: ký tự trùng
ở trước cửa sổ không được làm mép trái chạy lùi, như với `abba`.

Sau cập nhật, cửa sổ không có ký tự trùng. Mép trái là vị trí sớm nhất
còn hợp lệ cho mép phải hiện tại, nên đây là đoạn dài nhất kết thúc tại
vị trí đó. Lấy giá trị lớn nhất qua mọi mép phải cho kết quả toàn cục.
`for...of` và bộ đếm riêng giữ cùng đơn vị code point cho mọi chỉ số.

Thời gian **O(n)** theo mô hình thao tác `Map` trung bình O(1); bộ nhớ
**O(k)** với k là số code point khác nhau đã gặp, tối đa n.

## Chạy và kiểm thử

Từ gốc repo, với Node.js 24+ và Make:

```sh
make test-typescript
```

Dùng tệp `.mts` để khai báo module TypeScript rõ ràng. Node chạy trực tiếp
bằng [type stripping](https://nodejs.org/docs/latest-v24.x/api/typescript.html),
không cần package ngoài. Lệnh này kiểm tra hành vi và cú pháp được hỗ trợ;
**không chạy kiểm tra kiểu tĩnh bằng `tsc`**.

6 nhóm kiểm thử gồm ví dụ biên, lỗi mép trái chạy lùi, emoji và dấu kết
hợp, toàn bộ 3.280 chuỗi trên bảng chữ cái `abc` có độ dài 0–7, 1.000
chuỗi Unicode ngẫu nhiên có seed so với brute force, và đầu vào 100.000
ký tự. Oracle thử từng đoạn và dùng `Set`, không dùng cửa sổ trượt.

## Tự luyện

1. Trả thêm đoạn chuỗi tốt nhất và quy tắc khi có nhiều đáp án bằng nhau.
2. Thay đổi hợp đồng để đếm grapheme cluster bằng `Intl.Segmenter`.
3. Tìm đoạn dài nhất có nhiều nhất hai ký tự khác nhau.
