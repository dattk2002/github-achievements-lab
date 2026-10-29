import assert from 'node:assert/strict';
import test from 'node:test';
import { lengthOfLongestSubstring } from './solution.mts';

function oracle(s: string): number {
  const points = Array.from(s);
  let best = 0;
  for (let start = 0; start < points.length; start++) {
    const seen = new Set<string>();
    for (let end = start; end < points.length; end++) {
      if (seen.has(points[end])) break;
      seen.add(points[end]);
      best = Math.max(best, end - start + 1);
    }
  }
  return best;
}

test('empty, repeated, distinct, spaces and punctuation', () => {
  for (const [input, expected] of [
    ['', 0], ['zzzz', 1], ['qwerty', 6], ['a a!', 3], ['ab!c!d', 4],
  ] as const) {
    assert.equal(lengthOfLongestSubstring(input), expected, input);
  }
});

test('left edge never moves backward after an old duplicate', () => {
  assert.equal(lengthOfLongestSubstring('tmmzuxt'), 5);
  assert.equal(lengthOfLongestSubstring('abba'), 2);
});

test('Unicode code points, including surrogate pairs and combining marks', () => {
  assert.equal(lengthOfLongestSubstring('😀a😀b'), 3);
  assert.equal(lengthOfLongestSubstring('😀😃😄'), 3);
  assert.equal(lengthOfLongestSubstring('e\u0301e'), 2);
});

test('all strings over a small alphabet through length seven against brute force', () => {
  let level = [''];
  for (let length = 0; length <= 7; length++) {
    for (const s of level) assert.equal(lengthOfLongestSubstring(s), oracle(s), s);
    level = level.flatMap((prefix) => ['a', 'b', 'c'].map((c) => prefix + c));
  }
});

test('seeded randomized Unicode strings against brute force', () => {
  let state = 3;
  const next = () => (state = (Math.imul(state, 1664525) + 1013904223) >>> 0);
  const alphabet = ['a', ' ', '!', '😀', 'é', '\u0301'];
  for (let trial = 0; trial < 1000; trial++) {
    const length = next() % 15;
    let s = '';
    for (let i = 0; i < length; i++) s += alphabet[next() % alphabet.length];
    assert.equal(lengthOfLongestSubstring(s), oracle(s), s);
  }
});

test('one hundred thousand input characters', () => {
  assert.equal(lengthOfLongestSubstring('x'.repeat(100_000)), 1);
  assert.equal(lengthOfLongestSubstring('abcd'.repeat(25_000)), 4);
});
