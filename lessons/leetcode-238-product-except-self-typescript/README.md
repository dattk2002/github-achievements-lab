# TypeScript — Tích mọi phần tử trừ chính nó

Nguồn: [LeetCode 238 — Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/).
Đây là bài bổ sung ngày 30/10/2026, không phải Daily. Lời giải, ví dụ và
kiểm thử được tự viết; không chép toàn bộ đề hoặc editorial.

## Hợp đồng

`productExceptSelf(nums: readonly number[]): number[]` trả mảng mới có
phần tử thứ i bằng tích tất cả phần tử ngoài vị trí i, không sửa đầu vào
và không dùng phép chia. Theo bài gốc, đầu vào là số nguyên nhỏ và mọi
tích tiền tố, hậu tố, đáp án đều nằm trong miền số nguyên có dấu 32 bit.
Nhờ đó các phép nhân này chính xác trong kiểu `number` của JavaScript.
Không áp dụng hợp đồng này cho số thực, NaN, Infinity hoặc tích quá lớn;
hàm không tự xác thực chúng. Bản học tập hỗ trợ thêm `[] -> []` và mảng
một phần tử `[x] -> [1]`, theo quy ước tích rỗng bằng 1.

Ví dụ tự tạo: `[2, 3, 5] -> [15, 10, 6]`, `[0, -2, 5] -> [-10, 0, 0]`.

## Tiền tố, hậu tố và tính đúng

Lượt trái sang phải lưu tại `answer[i]` tích các phần tử **trước** i.
Lượt phải sang trái nhân nó với tích các phần tử **sau** i. Hai phần
không giao nhau và phủ đúng mọi chỉ số ngoài i, nên tích cuối là đáp án.
Cập nhật tích chạy sau khi ghi kết quả để không nhân nhầm chính phần tử i.

Không cần chia tổng tích cho `nums[i]`, vì vậy một hoặc nhiều số 0 đều
được xử lý tự nhiên. Chuẩn hóa kết quả bằng 0 về `+0` để API không trả
`-0`, vốn là một giá trị phân biệt được trong JavaScript.

Thời gian **O(n)**, bộ nhớ phụ **O(1)** ngoài mảng đầu ra O(n).

## Chạy và kiểm thử

Từ gốc repo, với Node.js 24+ và Make:

```sh
make test-typescript
```

Ví dụ gọi trong tệp `.mts` đặt cạnh `solution.mts`:

```typescript
import { productExceptSelf } from './solution.mts';
console.log(productExceptSelf([2, 3, 5])); // [15, 10, 6]
```

Dùng Node type stripping như các bài TypeScript trước: chạy kiểm thử
hành vi, không thay thế kiểm tra kiểu tĩnh bằng `tsc`. Không cần package
ngoài. Có 4 nhóm test: số âm và số 0, rỗng/một phần tử, mảng bị freeze để
kiểm tra không sửa đầu vào, 1.000 bộ ngẫu nhiên so với phép nhân trực tiếp
O(n²) và 100.000 phần tử có một số 0 ở giữa.

## Tự luyện

1. Viết bản dùng `bigint` khi tích không còn nằm trong miền an toàn.
2. Trả kết quả theo modulo; vì sao cách không chia vẫn hữu ích?
3. Đếm số 0 trước có giúp rút ngắn một số trường hợp không?
