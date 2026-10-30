import assert from 'node:assert/strict';
import test from 'node:test';
import { productExceptSelf } from './solution.mts';

function oracle(nums: readonly number[]): number[] {
  return nums.map((_, excluded) => {
    let product = 1;
    for (let i = 0; i < nums.length; i++) if (i !== excluded) product *= nums[i];
    return product === 0 ? 0 : product;
  });
}

test('prefixes and suffixes, negatives, one zero and multiple zeros', () => {
  const cases: [number[], number[]][] = [
    [[2, 3, 5], [15, 10, 6]], [[-2, 3, -4], [-12, 8, -6]],
    [[0, -2, 5], [-10, 0, 0]], [[0, 2, 0], [0, 0, 0]],
    [[-1, -1, -1, -1], [-1, -1, -1, -1]], [[], []], [[7], [1]],
  ];
  for (const [input, expected] of cases) assert.deepEqual(productExceptSelf(input), expected);
});

test('input stays unchanged and output has independent storage', () => {
  const input = Object.freeze([2, 4, 6]);
  const output = productExceptSelf(input);
  assert.deepEqual(output, [24, 12, 8]);
  output[0] = 999;
  assert.deepEqual(input, [2, 4, 6]);
});

test('one thousand seeded arrays agree with direct multiplication', () => {
  let state = 238;
  const next = () => (state = (Math.imul(state, 1664525) + 1013904223) >>> 0);
  for (let trial = 0; trial < 1000; trial++) {
    const length = next() % 10;
    const input = Array.from({ length }, () => (next() % 7) - 3);
    assert.deepEqual(productExceptSelf(input), oracle(input), JSON.stringify(input));
  }
});

test('one hundred thousand elements with an isolated zero', () => {
  const input = Array<number>(100_000).fill(1);
  input[50_000] = 0;
  const output = productExceptSelf(input);
  assert.equal(output.length, input.length);
  for (let i = 0; i < output.length; i++) assert.equal(output[i], i === 50_000 ? 1 : 0);
});
